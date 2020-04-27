#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

char cmd[50];

int main() {
    sqlite3 *db;
    char *ErrorMessage = NULL;
    int connect;
    printf("Welcome to password manager!\n");
    printf("Developer: Tarak Mustafa (D3VBG)\n");
    printf("HELP: help\n");
    printf("Write: ");
    scanf("%s",cmd);
    if(strcmp(cmd, "help") == 0){
        printf("install - install the requirements for password manager");
    }else if (strcmp(cmd, "install") == 0){
        system("sudo apt-get update");
        system("sudo apt-get upgrade");
        system("sudo apt-get install sqlite3");
        system("sudo apt-get install libsqlite3-dev");
    }else if (strcmp(cmd, "setup") == 0){
        connect = sqlite3_open("pass.db", &db);
        if (connect){
            fprintf(stderr, "Open database: %s\n", sqlite3_errmsg(db));
            return (0);
        }else{
            fprintf(stderr, "Database is opened successfully\n");
        }
        sqlite3_close(db);
    }
    return 0;
}
