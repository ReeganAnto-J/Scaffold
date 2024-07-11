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

const int MAX_PATH = 255;

int getCurretWorkingDir();

int main(){
    // To get the directory on which the program is running on
    char currentDirectory[MAX_PATH];
    int err = getCurretWorkingDir(currentDirectory);
    if(err) exit(1);
}

int getCurretWorkingDir(char* pwd){
    getcwd(pwd, MAX_PATH);
    if(strlen(pwd) == 0){
        printf("Path length exceeded!\nTry running on different directory!");
        return 1;
    }
    return 0;
}