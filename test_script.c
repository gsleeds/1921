#include <stdio.h>
#include <stdlib.h>

void executeMaze(char* inputFile){
    char command[100];
    sprintf(command, "./maze %s", inputFile);
    system(command);
}

void testSuccess(){
    printf("Test: Successful traversal\n");
    executeMaze("valid_maze.txt");
}

void 