/***********************************************************************************\

Project Name: Programming Environment Scaffolder
Project Author: Reegan Anto.J
Version: 0.0

Intro:
    This project is used to setup project environment for the programming language
    and the type of project structure the user requires

main.c:
    This is the root file of this project

\***********************************************************************************/

#include <stdio.h>
#include <unistd.h> // getcwd()
#include <string.h>

#include "ansicolor.h"
#include "scaffold.h"

int getCurretWorkingDir(char*);
int info();
int help();
int verbose();

const int MAX_DIR = 512; // Max length allowed for any directory
const int MAX_PATH = 256; // Max length allowed for path
const int MAX_NAME = 32; // Max length allowed for project name
const char* const version = "Version 0.0";

int main(int argc, char** argv){

    struct bit8colors colors; // Stores the ANSI code for colors
    colors.blue = 21;
    colors.green = 34;
    colors.cyan = 39;
    colors.purple = 56;
    colors.red = 196;
    colors.yellow = 226;
    colors.orange = 202;
    colors.grey = 244;
    colors.def = 0;


    // To get the directory on which the program is running on
    char currentDirectory[MAX_PATH];
    int err = getCurretWorkingDir(currentDirectory);
    if(err) {
        printf("Please run this program on a directory with shorter length\n");
        printf("Limit 255!\n");
        printf("\033[0m");
        return 0;
    }
    strcat(currentDirectory,"/");

    // To check if the user has entered sufficient number of flags
    if(argc < 2){
        int err =  info(colors.def);
        printf("Enter scaffold \033[1m--help\033[0m or scaffold \033[1m-h\033[0m for more details\n\n");
        printf("\033[0m");
        return err;
    }

    // To get single flag inputs
    if(argc == 2){
        if(argv[1][0] == '-' && strlen(argv[1]) == 2){
            if(strlen(argv[1]) != 2){
                printf("Invalid flag!\n");
                printf("\033[0m");
                return help();
            }
            if(argv[1][1] == 'h'){
                printf("\033[0m");
                return help();
            } else if(argv[1][1] == 'i'){
                printf("\033[0m");
                return info(colors.def);
            }else if(argv[1][1] == 'v'){
                printf("Project by Reegan Anto.J\n");
                printf("%s\n",version);
                printf("\033[0m");
                return verbose();
            }
        }
        if(strlen(argv[1]) > 2){
            if(strcmp(argv[1],"--help") == 0){
                printf("\033[0m");
                return help();
            }
            if(strcmp(argv[1],"--java") == 0){
                info(colors.green);
                printf("\033[0m");
                return javaScaffold(currentDirectory, 0, colors);
            }
            if(strcmp(argv[1],"--cc") == 0){
                info(colors.blue);
                printf("\033[0m");
                return ccppScaffold(currentDirectory, 0, colors);
            }
            if(strcmp(argv[1],"--go") == 0){
                info(colors.blue);
                printf("\033[0m");
                return goScaffold(currentDirectory, 0, colors);
            }
        }
        printf("Check below for all valid flags\n");
        int err = help();
        printf("\033[0m");
        return err;
    }

    // To get double flag inputs
    if(argc == 3){
        if(strcmp(argv[1],"--java") == 0 && strcmp(argv[2],"--help") == 0){
            info(colors.green);
            return javaScaffold(currentDirectory, 0, colors);
        }
        if(strcmp(argv[1],"--java") == 0 && strcmp(argv[2],"--console") == 0){
            info(colors.green);
            return javaScaffold(currentDirectory, 1, colors);
        }
        if(strcmp(argv[1],"--cc") == 0 && strcmp(argv[2],"--help") == 0){
            info(colors.blue);
            return ccppScaffold(currentDirectory, 0, colors);
        }
        if(strcmp(argv[1],"--cc") == 0 && strcmp(argv[2],"--c-console") == 0){
            info(colors.blue);
            return ccppScaffold(currentDirectory, 1, colors);
        }
        if(strcmp(argv[1],"--cc") == 0 && strcmp(argv[2],"--cpp-console") == 0){
            info(colors.blue);
            return ccppScaffold(currentDirectory, 2, colors);
        }
        if(strcmp(argv[1],"--go") == 0 && strcmp(argv[2],"--help") == 0){
            info(colors.cyan);
            return goScaffold(currentDirectory, 0, colors);
        }
        if(strcmp(argv[1],"--go") == 0 && strcmp(argv[2],"--console") == 0){
            info(colors.cyan);
            return goScaffold(currentDirectory, 1, colors);
        }
        printf("Check below for all valid flags\n");
        int err = help();
        printf("\033[0m");
        return err;
    }

    // To set back terminal to default
    printf("\033[0m");
    return 1;
}

int info(int code){
    // To print a cool opening title screen
    // Ref: http://www.patorjk.com/software/taag/#p=display&h=0&v=3&f=Speed&t=SCAFFOLD
    printf("\033[38;5;%dm",code);
    if(code == 0)printf("\033[0m");
    printf("________________________ ___________________________ ______ ________ \n");
    printf("__  ___/__  ____/___    |___  ____/___  ____/__  __ \\___  / ___  __ \\\n");
    printf("_____ \\ _  /     __  /| |__  /_    __  /_    _  / / /__  /  __  / / /\n");
    printf("____/ / / /___   _  ___ |_  __/    _  __/    / /_/ / _  /____  /_/ / \n");
    printf("/____/  \\____/   /_/  |_|/_/       /_/       \\____/  /_____//_____/  \n\n");

    printf("        THE FASTEST WAY TO START DEVELOPING YOUR PROJECT\n");
    printf("                           Reegan Anto.J\n");
    printf("                                v0.0\n\n");
    printf("\033[0m");
    return 0;
}

int help(){
    printf("%s\n",version);
    printf("Basic flags:\n");
    printf("\033[1m-i\033[0m info\n");
    printf("\033[1m-h\033[0m help\n");
    printf("\033[1m-v\033[0m verbose\n\n");
    printf("Use these tags for more info on the project:\n");
    printf("\033[1m--java\033[0m To list all the java project types\n");
    printf("\033[1m--cc\033[0m To list all the c/c++ project types\n");
    printf("\033[1m--python\033[0m To list all the python project types\n");
    printf("\033[1m--go\033[0m To list all the go project types\n");
    return 0;
}

int verbose(){
    return 0;
}

int getCurretWorkingDir(char* pwd){
    getcwd(pwd, MAX_PATH-1);
    if(strlen(pwd) == 0){
        printf("Path length exceeded!\nTry running on different directory!");
        return 1;
    }
    return 0;
}