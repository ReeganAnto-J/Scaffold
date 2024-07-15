#include <stdio.h> // popen()
#include <sys/types.h> //mkdir()
#include <sys/stat.h> //mkdir()
#include <stdlib.h> // system()
#include <string.h>

#include "../ansicolor.h"

extern int MAX_PATH;
extern int MAX_NAME;
extern int MAX_DIR;

void ccpp_gitignore(const char* const, const char* const, struct bit8colors);

int _cScaffold_console(const char* const, struct bit8colors);
int _cppScaffold_console(const char* const, struct bit8colors);

// Scaffolds c/cpp project takes the directory to be created, the type of project and ansi color object
int ccppScaffold(const char* const currentDirectory, int flag, struct bit8colors colors){
    enum flags{// Types of projects that can be built using c/c++
        ccpp_list,
        c_console,
        cpp_console
    };

    FILE *fptr;
    char package_path[MAX_PATH];

    // Checking if GCC exists
    printf("Testing for GCC in path: \n");
    fptr = popen("gcc --version", "r");
    if(fptr == NULL){
        printf("\033[38;5;%d;1mCannot find GCC path!\nExiting...\n\033[0m",colors.red);
        return 0;
    }
    fgets(package_path, MAX_PATH, fptr);
    pclose(fptr);
    printf("%s\n",package_path);
    printf("\033[38;5;%dmGCC available (-‿◦☀)\n\n\033[0m",colors.blue);

    // Listing all the project types that can be made with c/c++
    if(flag == ccpp_list){
        printf("Add these flags a the end to build:\n");
        printf("\033[1m--c-console\033[0m To build c console app\n");
        printf("\033[1m--cpp-console\033[0m To build c++ console app\n");
    }

    // To build console project
    if(flag == c_console){
        return(_cScaffold_console(currentDirectory, colors));
    }
    if(flag == cpp_console){
        return(_cppScaffold_console(currentDirectory, colors));
    }

    printf("\033[0m");
    return 0;
}

// Local function which is used to build c console project
int _cScaffold_console(const char* const currentDirectory, struct bit8colors colors){
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
    printf("Building required directories...\n");
    strcpy(projdir,tmp);
    strcat(projdir,"src");
    err = mkdir(projdir, 0775);
    if(err){
        printf("\n\033[38;5;%d;1mUnable to src directory\nExiting...\n\n\033[0m",colors.red);
        return 0;
    } 
    else printf("src folder created\n");
    strcpy(projdir,tmp);
    strcat(projdir,"bin");
    err = mkdir(projdir, 0775);
    if(err){
        printf("\n\033[38;5;%d;1mUnable to bin directory\nExiting...\n\n\033[0m",colors.red);
        return 0;
    } 
    else printf("bin folder created\n");
    strcpy(projdir,tmp);
    strcat(projdir,"src/lib");
    err = mkdir(projdir, 0775);
    if(err) printf("\n\033[38;5;%d;1mUnable to lib directory\nSkipping...\n\n\033[0m",colors.red);
    else printf("Add your external libraries in lib dir\n\n");

    // To build main.c
    printf("Building main.c\n");
    strcpy(projdir, tmp);
    strcat(projdir,"src/main.c");
    fptr = fopen(projdir,"w");
    if(fptr != NULL){
        fprintf(fptr,"#include <stdio.h>\n");
        fprintf(fptr,"#include <stdlib.h>\n");
        fprintf(fptr,"#include <string.h>\n\n");
        fprintf(fptr,"int main() {\n");
        fprintf(fptr,"\tprintf(\"Hello, World!\\n\");\n");
        fprintf(fptr,"}\n");
        fclose(fptr);
        printf("\033[38;5;%dmDone\n\n\033[0m",colors.green);
    } else {
        printf("\n\033[38;5;%d;1mUnable to create main.c\nExiting...\n\n\033[0m",colors.red);
        return 0;
    }

    // To check for git to initialize and add .gitignore
    ccpp_gitignore(projname, tmp, colors);

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
            fprintf(fptr, "CC = gcc\n\nBUILD_FLAGS = -O2 -Wall\n\nSOURCE_FILES = ./src/*.c\n\n");
            fprintf(fptr, "BUILD_PATH = ./bin/%s\n\n",projname);
            fprintf(fptr, "build:\n\t@$(CC) $(BUILD_FLAGS) $(SOURCE_FILES) -o $(BUILD_PATH)\n\n");
            fprintf(fptr, "run: build\n\t@$(BUILD_PATH)\n\n");
            fprintf(fptr, "clean:\n\trm $(BUILD_PATH)");
            fclose(fptr);
            make_ready = 1;
            printf("\033[38;5;%dmDone\n\n\033[0m",colors.green);
        } else printf("\033[38;5;%d;1mUnable to build makefile!\nSkipping...\n\n\033[0m", colors.red);
    }

    printf("\033[1mPerforming final tests on project...\033[0m\n");
    if(make_ready){
        strcpy(packagePath,"cd ./");
        strcat(packagePath,projname);
        strcat(packagePath,";make run;make clean");
        err = system(packagePath);
        if(err){
            printf("\033[38;5;%d;1mCannot verify project...\033[0m\n",colors.red);
        } else printf("\033[38;5;%d;1m\nProject ready!\n\033[0m",colors.green);
    } else {
            printf("\033[38;5;%d;1mCannot verify project without make...\033[0m\n",colors.red);
    }

    printf("\033[1mALL CLEAR\n\n\033[0m");
    
    return 0;
}

// Local function which is used to build cpp console project
int _cppScaffold_console(const char* const currentDirectory, struct bit8colors colors){
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
    printf("Building required directories...\n");
    strcpy(projdir,tmp);
    strcat(projdir,"src");
    err = mkdir(projdir, 0775);
    if(err){
        printf("\n\033[38;5;%d;1mUnable to src directory\nExiting...\n\n\033[0m",colors.red);
        return 0;
    } 
    else printf("src folder created\n");
    strcpy(projdir,tmp);
    strcat(projdir,"bin");
    err = mkdir(projdir, 0775);
    if(err){
        printf("\n\033[38;5;%d;1mUnable to bin directory\nExiting...\n\n\033[0m",colors.red);
        return 0;
    } 
    else printf("bin folder created\n");
    strcpy(projdir,tmp);
    strcat(projdir,"src/lib");
    err = mkdir(projdir, 0775);
    if(err) printf("\n\033[38;5;%d;1mUnable to lib directory\nSkipping...\n\n\033[0m",colors.red);
    else printf("Add your external libraries in lib dir\n\n");

    // To build main.c
    printf("Building main.cpp\n");
    strcpy(projdir, tmp);
    strcat(projdir,"src/main.cpp");
    fptr = fopen(projdir,"w");
    if(fptr != NULL){
        fprintf(fptr,"#include <iostream>\n");
        fprintf(fptr,"#include <string>\n\n");
        fprintf(fptr,"int main() {\n");
        fprintf(fptr,"\tstd::cout << \"Hello, World!\" << std::endl;\n");
        fprintf(fptr,"}\n");
        fclose(fptr);
        printf("\033[38;5;%dmDone\n\n\033[0m",colors.green);
    } else {
        printf("\n\033[38;5;%d;1mUnable to create main.cpp\nExiting...\n\n\033[0m",colors.red);
        return 0;
    }

    // To check for git to initialize and add .gitignore
    ccpp_gitignore(projname, tmp, colors);

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
            fprintf(fptr, "CC = g++\n\nBUILD_FLAGS = -O2 -Wall\n\nSOURCE_FILES = ./src/*.cpp\n\n");
            fprintf(fptr, "BUILD_PATH = ./bin/%s\n\n",projname);
            fprintf(fptr, "build:\n\t@$(CC) $(BUILD_FLAGS) $(SOURCE_FILES) -o $(BUILD_PATH)\n\n");
            fprintf(fptr, "run: build\n\t@$(BUILD_PATH)\n\n");
            fprintf(fptr, "clean:\n\trm $(BUILD_PATH)");
            fclose(fptr);
            make_ready = 1;
            printf("\033[38;5;%dmDone\n\n\033[0m",colors.green);
        } else printf("\033[38;5;%d;1mUnable to build makefile!\nSkipping...\n\n\033[0m", colors.red);
    }

    printf("\033[1mPerforming final tests on project...\033[0m\n");
    if(make_ready){
        strcpy(packagePath,"cd ./");
        strcat(packagePath,projname);
        strcat(packagePath,";make run;make clean");
        err = system(packagePath);
        if(err){
            printf("\033[38;5;%d;1mCannot verify project...\033[0m\n",colors.red);
        } else printf("\033[38;5;%d;1m\nProject ready!\n\033[0m",colors.green);
    } else {
            printf("\033[38;5;%d;1mCannot verify project without make...\033[0m\n",colors.red);
    }

    printf("\033[1mALL CLEAR\n\n\033[0m");
    
    return 0;
}

void ccpp_gitignore(const char* const projname, const char* const tmp, struct bit8colors colors){
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
                fprintf(fptr, "# Prerequisites\n*.d\n\n# Object files\n*.o\n*.ko\n*.obj\n*.elf\n\n");
                fprintf(fptr, "# Linker output\n*.ilk\n*.map\n*.exp\n\n# Precompiled Headers\n*.gch\n*.pch\n\n");
                fprintf(fptr, "# Libraries\n*.lib\n*.a\n*.la\n*.lo\n\n# Shared objects (inc. Windows DLLs)\n*.dll\n*.so\n*.so.*\n*.dylib\n\n");
                fprintf(fptr, "# Executables\n*.exe\n*.out\n*.app\n*.i*86\n*.x86_64\n*.hex\n\n# Debug files\n*.dSYM/\n*.su\n*.idb\n*.pdb\n\n");
                fprintf(fptr, "# Kernel Module Compile Results\n*.mod*\n*.cmd\n.tmp_versions/\nmodules.order\nModule.symvers\nMkfile.old\ndkms.conf");
                fclose(fptr);
                printf("\033[38;5;%dmDone\n\n\033[0m",colors.green);
            } else printf("\033[38;5;%d;1mUnable to add gitignore!\nSkipping...\n\n\033[0m", colors.red);
        } else  printf("\033[38;5;%d;1mUnable to initialize git!\nSkipping...\n\n\033[0m",colors.red);
    }
}