#include <stdio.h> // popen()
#include <sys/types.h> //mkdir()
#include <sys/stat.h> //mkdir()
#include <stdlib.h> // system()
#include <string.h>

#include "../ansicolor.h"

extern int MAX_PATH;
extern int MAX_NAME;
extern int MAX_DIR;

void go_gitignore(const char* const, const char* const, struct bit8colors);

int _goScaffold_console(const char* const, struct bit8colors);

// Scaffolds go project takes the directory to be created, the type of project and ansi color object
int goScaffold(const char* const currentDirectory, int flag, struct bit8colors colors){
    enum flags{// Types of projects that can be built using go
        go_list,
        go_console
    };

    FILE *fptr;
    char package_path[MAX_PATH];

    if(flag != go_list){
        // Checking if GO exists
        printf("Testing for GO in path: \n");
        fptr = popen("go version", "r");
        if(fptr == NULL){
            printf("\033[38;5;%d;1mCannot find GO path!\nExiting...\n\033[0m",colors.red);
            return 0;
        }
        package_path[0] = '\0';
        fgets(package_path, MAX_PATH, fptr);
        pclose(fptr);
        if(strlen(package_path) == 0){
            printf("\033[38;5;%d;1mCannot find GO path!\nExiting...\n\033[0m",colors.red);
            return 0;
        }
        printf("%s\n",package_path);
        printf("\033[38;5;%dmGO available ⊹⋛⋋( ՞ਊ ՞)⋌⋚⊹\n\n\033[0m",colors.cyan);
    }

    // Listing all the project types that can be made with go
    if(flag == go_list){
        printf("Add these flags a the end to build:\n");
        printf("\033[1m--console\033[0m To build go console app\n");
    }

    // To build console project
    if(flag == go_console){
        return(_goScaffold_console(currentDirectory, colors));
    }

    printf("\033[0m");
    return 0;
}

// Local function which is used to build go console project
int _goScaffold_console(const char* const currentDirectory, struct bit8colors colors){
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

    // To build go.mod file
    {
        char modinit[MAX_PATH];
        char initcommand[MAX_DIR];

        printf("Building mod file...\n\n");
        printf("Please enter your github handle\n");
        printf("Note - the project name will be added at the end automatically!\neg:~~> github.com/ReeganAnto-J/\n\n==> ");
        scanf("%s", modinit);
        strcpy(initcommand, "cd ");
        strcat(initcommand, tmp);
        strcat(initcommand, ";go mod init ");
        strcat(initcommand, modinit);
        strcat(initcommand,projname);
        strcat(initcommand, "; cd ..");
        
        err = system(initcommand);
        if(err){
            printf("\n\033[38;5;%d;1mUnable to build mod file\nExiting...\n",colors.red);
            return 0;
        }else printf("\033[38;5;%dmDone\n\n\033[0m",colors.green);
    }

    // To build directories
    printf("Building required directories...\n");
    strcpy(projdir,tmp);
    strcat(projdir,"src");
    err = mkdir(projdir, 0775);
    if(err){
        printf("\n\033[38;5;%d;1mUnable to src directory\nExiting...\n\n\033[0m",colors.red);
        return 0;
    } 
    else printf("src folder created\n");

    // To build main.go
    printf("Building main.go\n");
    strcpy(projdir, tmp);
    strcat(projdir,"src/main.go");
    fptr = fopen(projdir,"w");
    if(fptr != NULL){
        fprintf(fptr,"package main\n\n");
        fprintf(fptr,"import \"fmt\"\n\n");
        fprintf(fptr,"func main() {\n\tfmt.Println(\"Hello world!\")\n}");
        fclose(fptr);
        printf("\033[38;5;%dmDone\n\n\033[0m",colors.green);
    } else {
        printf("\n\033[38;5;%d;1mUnable to create main.c\nExiting...\n\n\033[0m",colors.red);
        return 0;
    }

    // To check for git to initialize and add .gitignore
    go_gitignore(projname, tmp, colors);

    // To check for make and build makefile
    char make_ready = 0;
    printf("Checking for make... \n");
    fptr = popen("make --version", "r");
    if(fptr == NULL){
        printf("\033[38;5;%d;1mCannot find make path!\nSkipping make initialization...\n\n\033[0m",colors.red);
    } else {
        packagePath[0] = '\0';
        fgets(packagePath, MAX_PATH, fptr);
        pclose(fptr);
        if(strlen(packagePath) == 0){
            printf("\033[38;5;%d;1mCannot find make path!\nSkipping make initialization...\n\n\033[0m",colors.red);
        } else {
            printf("%s",packagePath);
            printf("Make available, creating makefile... \n");
            strcpy(projdir, tmp);
            strcat(projdir,"Makefile");
            fptr = fopen(projdir,"w");
            if(fptr != NULL){
                fprintf(fptr, "SOURCE_FILES = ./src/*.go\n\n");
                fprintf(fptr, "run:\n\t@go run $(SOURCE_FILES)\n\n");
                fclose(fptr);
                make_ready = 1;
                printf("\033[38;5;%dmDone\n\n\033[0m",colors.green);
            } else printf("\033[38;5;%d;1mUnable to build makefile!\nSkipping...\n\n\033[0m", colors.red);
        }
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
        strcpy(packagePath,"cd ./src");
        strcat(packagePath,projname);
        strcat(packagePath,";go run main.go");
        err = system(packagePath);
        if(err){
            printf("\033[38;5;%d;1mCannot verify project...\033[0m\n",colors.red);
        } else printf("\033[38;5;%d;1m\nProject ready!\n\033[0m",colors.green);
    }

    printf("\033[1mALL CLEAR\n\n\033[0m");
    
    return 0;
}

void go_gitignore(const char* const projname, const char* const tmp, struct bit8colors colors){
    // To check for git to initialize and add .gitignore

    FILE* fptr;

    char projdir[MAX_DIR];
    char packagePath[MAX_PATH];

    int err;

    printf("Checking for git... \n");
    fptr = popen("git --version", "r");
    if(fptr == NULL){
        printf("\033[38;5;%d;1mCannot find git path!\nSkipping git initialization...\n\n\033[0m",colors.red);
        return;
    }
    fgets(packagePath, MAX_PATH, fptr);
    pclose(fptr);
    if(strlen(packagePath) == 0){
        printf("\033[38;5;%d;1mCannot find git path!\nSkipping git initialization...\n\n\033[0m",colors.red);
        return;
    }
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
            fprintf(fptr, "# Binaries for programs and plugins\n*.exe\n*.exe~\n*.dll\n*.so\n*.dylib\n\n");
            fprintf(fptr, "# Test binary, built with `go test -c`\n*.test\n\n");
            fprintf(fptr, "# Output of the go coverage tool, specifically when used with LiteIDE\n*.out\n\n");
            fprintf(fptr, "# Dependency directories (remove the comment below to include it)\n# vendor/\n\n");
            fprintf(fptr, "# Go workspace file\ngo.work\ngo.work.sum\n\n");
            fprintf(fptr, "# env file\n.env");
            fclose(fptr);
            printf("\033[38;5;%dmDone\n\n\033[0m",colors.green);
        } else printf("\033[38;5;%d;1mUnable to add gitignore!\nSkipping...\n\n\033[0m", colors.red);
    } else  printf("\033[38;5;%d;1mUnable to initialize git!\nSkipping...\n\n\033[0m",colors.red);
}