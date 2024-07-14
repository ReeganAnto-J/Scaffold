#include <stdio.h> // popen()
#include <sys/types.h> //mkdir()
#include <sys/stat.h> //mkdir()
#include <stdlib.h> // system()
#include <string.h>

#include "../ansicolor.h"

extern int MAX_PATH;
extern int MAX_NAME;
extern int MAX_DIR;

void java_gitignore(const char* const, const char* const, struct bit8colors);
int _javaScaffold_console(const char* const, struct bit8colors);

// Scaffolds java project takes the directory to be created, the type of project and ansi color object
int javaScaffold(const char* const currentDirectory, int flag, struct bit8colors colors){
    enum flags{// Types of projects that can be built using java
        java_list,
        java_console
    };

    FILE *fptr;
    char package_path[MAX_PATH];

    // Checking if jdk exists
    printf("Testing for JDK in path: \n");
    fptr = popen("java --version", "r");
    if(fptr == NULL){
        printf("\033[38;5;%d;1mCannot find JDK path!\nExiting...\n\033[0m",colors.red);
        return 0;
    }
    fgets(package_path, MAX_PATH, fptr);
    pclose(fptr);
    printf("%s\n",package_path);
    printf("\033[38;5;%dmJDK available ┗(^o^ )┓三\n\n\033[0m",colors.green);

    // Listing all the project types that can be made with java
    if(flag == java_list){
        printf("Add these flags a the end to build:\n");
        printf("--console A simple java console application\n");
    }

    // To build console project
    if(flag == java_console){
        return(_javaScaffold_console(currentDirectory, colors));
    }

    return 0;
}

// Local function which is used to build Java console project
int _javaScaffold_console(const char* const currentDirectory, struct bit8colors colors){
    FILE* fptr;

    char projname[MAX_NAME];
    char projdir[MAX_DIR];
    char tmp[MAX_DIR];
    
    char packagePath[MAX_PATH];
    
    int err = 0;

    // To build the root folder
    printf("Please enter your project name: ");
    scanf("%s", projname);
    strcpy(projdir,currentDirectory);
    strcat(projdir,projname);
    printf("Building root folder... \n");
    err = mkdir(projdir, 0775);
    if(err){
        printf("\n\033[38;5;%d;1mUnable to build root folder!\nExiting...\n\n\033[0m",colors.red);
        return 0;
    }
    printf("\033[38;5;%dmDone\n\n\033[0m",colors.green);
    strcpy(tmp,projdir);
    strcat(tmp,"/");

    // To build directories
    printf("Building obj and bin directories...\n");
    strcpy(projdir,tmp);
    strcat(projdir,"obj");
    err = mkdir(projdir, 0775);
    if(err) printf("\n\033[38;5;%d;1mUnable to obj directory\n\n\033[0m",colors.red);
    else printf("obj folder created, place your compiled files in obj dir\n");
    strcpy(projdir,tmp);
    strcat(projdir,"lib");
    err = mkdir(projdir, 0775);
    if(err){
        printf("\n\033[38;5;%d;1mUnable to bin directory\nExiting...\n\n\033[0m",colors.red);
        return 0;
    } 
    else printf("Add your external libraries in lib dir\n\n");

    // To build main.java
    printf("Building Main.java\n");
    strcpy(projdir, tmp);
    strcat(projdir,"Main.java");
    fptr = fopen(projdir,"w");
    if(fptr != NULL){
        fprintf(fptr,"import java.io.*;\n");
        fprintf(fptr,"import java.util.*;\n");
        fprintf(fptr,"import java.text.*;\n");
        fprintf(fptr,"import java.math.*;\n");
        fprintf(fptr,"import java.util.regex.*;\n\n");
        fprintf(fptr,"public class Main {\n");
        fprintf(fptr,"\tpublic static Scanner sc = new Scanner(System.in);\n");
        fprintf(fptr,"\tpublic static void main(String args[] ) {\n");
        fprintf(fptr,"\t\tSystem.out.println(\"Hello, World!\");\n");
        fprintf(fptr,"\t}\n}\n");
        fclose(fptr);
        printf("\033[38;5;%dmDone\n\n\033[0m",colors.green);
    } else {
        printf("\n\033[38;5;%d;1mUnable to create Main.java\nExiting...\n\n\033[0m",colors.red);
        return 0;
    }

    // To check for git to initialize and add .gitignore
    java_gitignore(projname, tmp, colors);

    // To check for make and build makefile
    char make_ready = 0;
    printf("Checking for make... \n");
    fptr = popen("make --version", "r");
    if(fptr == NULL){
        printf("\033[38;5;%d;1mCannot find make path!\nSkipping make initialization...\n\n\033[0m",colors.red);
        pclose(fptr);
    } else {
        fgets(packagePath, MAX_PATH, fptr);
        pclose(fptr);
        printf("%s",packagePath);
        printf("Make available, creating makefile... \n");
        strcpy(projdir, tmp);
        strcat(projdir,"Makefile");
        fptr = fopen(projdir,"w");
        if(fptr != NULL){
            fprintf(fptr, "OBJ_DIR = ./obj/\n");
            fprintf(fptr, "LIB_DIR = ./lib/\n\n");
            fprintf(fptr, "run:\n\t@java Main.java\n\n");
            fprintf(fptr, "clean:\n\trm $(OBJ_DIR)*.class");
            fclose(fptr);
            make_ready = 1;
            printf("\033[38;5;%dmDone\n\n\033[0m",colors.green);
        } else printf("\033[38;5;%d;1mUnable to build makefile!\nSkipping...\n\n\033[0m", colors.red);
    }

    printf("\033[1mPerforming final tests on project...\033[0m\n");
    if(make_ready){
        strcpy(packagePath,"cd ./");
        strcat(packagePath,projname);
        strcat(packagePath,";make run");
        err = system(packagePath);
        if(err){
            printf("\033[38;5;%d;1mCannot verify project...\033[0m\n",colors.red);
        } else printf("\033[38;5;%d;1m\nProject ready!\n\033[0m",colors.green);
    } else {
        strcpy(packagePath,"cd ./");
        strcat(packagePath,projname);
        strcat(packagePath,";java Main.java");
        err = system(packagePath);
        if(err){
            printf("\033[38;5;%d;1mCannot verify project...\033[0m\n",colors.red);
        } else printf("\033[38;5;%d;1m\nProject ready!\n\033[0m",colors.green);
    }

    printf("\033[1mALL CLEAR\n\n\033[0m");
    
    return 0;
}

void java_gitignore(const char* const projname, const char* const tmp, struct bit8colors colors){
    // To check for git to initialize and add .gitignore

    FILE* fptr;

    char projdir[MAX_DIR];
    char packagePath[MAX_PATH];

    int err;

    printf("Checking for git... \n");
    fptr = popen("git --version", "r");
    if(fptr == NULL){
        printf("\033[38;5;%d;1mCannot find git path!\nSkipping git initialization...\n\n\033[0m",colors.red);
        pclose(fptr);
    } else {
        fgets(packagePath, MAX_PATH, fptr);
        pclose(fptr);
        printf("%s",packagePath);
        printf("Git available, proceeding initialization... \n");
        strcpy(packagePath,"cd ./");
        strcat(packagePath,projname);
        strcat(packagePath,";git init");
        err = system(packagePath);
        if(!err){
            printf("Adding gitignore... \n");
            strcpy(projdir, tmp);
            strcat(projdir,".gitignore");
            fptr = fopen(projdir,"w");
            if(fptr != NULL){
                fprintf(fptr, "# Compiled class file\n*.class\n\n# Log file\n*.log\n\n");
                fprintf(fptr, "# BlueJ files\n*.ctxt\n\n# Mobile Tools for Java (J2ME)\n.mtj.tmp/\n\n");
                fprintf(fptr, "# Package Files #\n*.jar\n*.war\n*.nar\n*.ear\n*.zip\n*.tar.gz\n*.rar\n\n");
                fprintf(fptr, "# virtual machine crash logs, see http://www.java.com/en/download/help/error_hotspot.xml\n");
                fprintf(fptr, "hs_err_pid*\nreplay_pid*");
                fclose(fptr);
                printf("\033[38;5;%dmDone\n\n\033[0m",colors.green);
            } else printf("\033[38;5;%d;1mUnable to add gitignore!\nSkipping...\n\n\033[0m", colors.red);
        } else  printf("\033[38;5;%d;1mUnable to initialize git!\nSkipping...\n\n\033[0m",colors.red);
    }
}