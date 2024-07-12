/***********************************************************************************\

Project Name: Programming Environment Scaffolder
Project Author: Reegan Anto.J
Version: 0.0
Date Created: 11th July 2024
Last Modified: 12th July 2024

Intro:
    This project is used to setup project environment for the programming language
    and the type of project structure the user requires

main.c:
    This is the root file of this project

\***********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int getCurretWorkingDir(char* pwd);
int info();
int help();
int verbose();
int java_scaffold(const char* const, int flag);

const int MAX_PATH = 255;
const char* const version = "Version 0.0";
enum bit8colors{
    blue = 21,
    green = 34,
    cyan = 39,
    purple = 56,
    red = 196,
    yellow = 226,
    orange = 202,
    grey = 244,
    def = 0
};

int main(int argc, char** argv){
    // To get the directory on which the program is running on
    char currentDirectory[MAX_PATH];
    int err = getCurretWorkingDir(currentDirectory);
    if(err) {
        printf("Please run this program on a directory with shorter length\n");
        printf("Limit 255!\n");
        exit(1);
    }

    // To check if the user has entered sufficient number of flags
    if(argc < 2){
        int err =  info(def);
        printf("Enter scaffold --help or scaffold -h for more details\n\n");
        exit(err);
    }

    // To get single flag inputs
    if(argc == 2){
        if(argv[1][0] == '-' && strlen(argv[1]) == 2){
            if(strlen(argv[1]) != 2){
                printf("Invalid flag!\n");
                exit(help());
            }
            if(argv[1][1] == 'h'){
                exit(help());
            } else if(argv[1][1] == 'i'){
                exit(info(def));
            }else if(argv[1][1] == 'v'){
                printf("Project by Reegan Anto.J\n");
                printf("%s\n",version);
                exit(verbose());
            }
        }
        if(strlen(argv[1]) > 2){
            if(strcmp(argv[1],"--help") == 0){
                exit(help());
            }
            if(strcmp(argv[1],"--java") == 0){
                info(green);
                return(java_scaffold(currentDirectory, 0));
            }
        }
        printf("Check below for all valid flags\n");
        int err = help();
        exit(err);
    }

    // To get double flag inputs

    // To set back terminal to default
    printf("\033[0m");
}

int info(int code){
    // To print a cool opening title screen
    // Ref: http://www.patorjk.com/software/taag/#p=display&h=0&v=3&f=Speed&t=SCAFFOLD
    printf("\033[38;5;%dm",code);
    if(code == def)printf("\033[0m");
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
    printf("\033[1m--cpp\033[0m To list all the java project types\n");
    printf("\033[1m--python\033[0m To list all the java project types\n");
    printf("\033[1m--go\033[0m To list all the java project types\n");
    printf("\033[1m--rust\033[0m To list all the java project types\n");
    printf("\033[1m--js\033[0m To list all the javascript project types\n");
    return 0;
}

int verbose(){
    return 0;
}

int java_scaffold(const char* const, int flag){
    enum flags{
        list
    };

    FILE *fp;
    printf("Testing for JDK in path: ");
    fp = popen("java --version", "r");
    if(fp == NULL){
        printf("\033[38;5;%d;1mCannot find JDK path!\nExiting...\n\033[0m",red);
        return 1;
    }
    char jdk_path[MAX_PATH];
    fgets(jdk_path, MAX_PATH, fp);
    pclose(fp);
    printf("%s\n",jdk_path);
    printf("JDK available ┗(^o^ )┓三\n\n");

    if(flag == list){
        printf("Add these flags a the end for additional functions:\n");
        printf("--base A base java class\n");
    }

    return 0;
}

int getCurretWorkingDir(char* pwd){
    getcwd(pwd, MAX_PATH);
    if(strlen(pwd) == 0){
        printf("Path length exceeded!\nTry running on different directory!");
        return 1;
    }
    return 0;
}