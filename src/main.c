/***********************************************************************************\

Project Name: Programming Environment Scaffolder
Project Author: Reegan Anto.J
Version: 0.0
Date Created: 11th July 2024
Last Modified: 11th July 2024

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

int getCurretWorkingDir();
int java_scaffold(const char* const);

const int MAX_PATH = 255;

int main(){
    // To get the directory on which the program is running on
    char currentDirectory[MAX_PATH];
    int err = getCurretWorkingDir(currentDirectory);
    if(err) {
        printf("Please run this program on a directory with shorter length\n");
        printf("Limit 255!");
        exit(1);
    }

    // To choose what type of scaffolding the user needs
    int ch;
    printf("1. Java\n");
    scanf("%d",&ch);
    switch(ch){
        case 1:
            err = java_scaffold(currentDirectory);
            printf("\033[0m");
            if(err) exit(1);
            break;
    }
}

int java_scaffold(const char* const){
    FILE *fp;

    // To print a cool java ascii script
    {
        // Ref: http://www.patorjk.com/software/taag/#p=display&f=Impossible&t=JAVA
        printf("\033[32;1;5m");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("|             _        _      _          _       _          |\n");
        printf("|            /\\ \\     / /\\   /\\ \\    _ / /\\     / /\\        |\n");
        printf("|            \\ \\ \\   / /  \\  \\ \\ \\  /_/ / /    / /  \\       |\n");
        printf("|            /\\ \\_\\ / / /\\ \\  \\ \\ \\ \\___\\/    / / /\\ \\      |\n");
        printf("|           / /\\/_// / /\\ \\ \\ / / /  \\ \\ \\   / / /\\ \\ \\     |\n");
        printf("|  _       / / /  / / /  \\ \\ \\\\ \\ \\   \\_\\ \\ / / /  \\ \\ \\    |\n");
        printf("| /\\ \\    / / /  / / /___/ /\\ \\\\ \\ \\  / / // / /___/ /\\ \\   |\n");
        printf("| \\ \\_\\  / / /  / / /_____/ /\\ \\\\ \\ \\/ / // / /_____/ /\\ \\  |\n");
        printf("| / / /_/ / /  / /_________/\\ \\ \\\\ \\ \\/ // /_________/\\ \\ \\ |\n");
        printf("|/ / /__\\/ /  / / /_       __\\ \\_\\\\ \\  // / /_       __\\ \\_\\|\n");
        printf("|\\/_______/   \\_\\___\\     /____/_/ \\_\\/ \\_\\___\\     /____/_/|\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\033[0m");
    }
    // To check if jdk exists
    printf("Testing for JDK in path: ");
    fp = popen("java --version", "r");
    if(fp == NULL){
        printf("Cannot find java path!\nExiting...");
        return 1;
    }
    char jdk_path[MAX_PATH];
    fgets(jdk_path, MAX_PATH, fp);
    printf("%s\n",jdk_path);
    pclose(fp);
    printf("\033[32;1m");
    printf("\aJDK available ┗(^o^ )┓三\n\n");
    printf("\033[0m");
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