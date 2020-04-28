#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stdbool.h>

char cmd[50];

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i < argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int main() {
    sqlite3 *db;
    char *ErrorMessage = NULL;
    int connect;
    char *sql;
    const char* data = "Callback function called";
    connect = sqlite3_open("passwords.db", &db);
    printf("Welcome to password manager!\n");
    printf("Developer: Tarak Mustafa (D3VBG)\n");
    printf("HELP: help\n");

    while (true) {
        printf("Write: ");
        scanf("%s", cmd);
        if (strcmp(cmd, "help") == 0) {
            printf("install - installs the requirements for password manager\n");
            printf("setup - creating a database\n");
            printf("add - to add new website and password\n");
        } else if (strcmp(cmd, "install") == 0) {
            system("sudo apt-get update");
            system("sudo apt-get upgrade");
            system("sudo apt-get install sqlite3");
            system("sudo apt-get install libsqlite3-dev");
        } else if (strcmp(cmd, "setup") == 0) {
            if (connect) {
                fprintf(stderr, "Open database: %s\n", sqlite3_errmsg(db));
                return (0);
            } else {
                fprintf(stderr, "Database is opened successfully\n");
            }

            sql = "CREATE TABLE PASSWORDS("  \
            "ID INTEGER PRIMARY KEY AUTOINCREMENT," \
            "WEBSITE        CHAR(2000)," \
            "PASSWORD         CHAR(50) );";

            connect = sqlite3_exec(db, sql, callback, 0, &ErrorMessage);

            if (connect != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", ErrorMessage);
                sqlite3_free(ErrorMessage);
            } else {
                fprintf(stdout, "Table create successfully\n");
            }
            sqlite3_close(db);
        } else if (strcmp(cmd, "add") == 0) {
            char website[2000];
            char password[50];
            printf("Website: ");
            scanf("%s", website);
            printf("Password: ");
            scanf("%s", password);


            if (connect) {
                fprintf(stderr, "Open database: %s\n", sqlite3_errmsg(db));
                return (0);
            } else {
                fprintf(stderr, "Database is opened successfully\n");
            }

            char InsertSql[128];

            sprintf(InsertSql, "INSERT INTO PASSWORDS (WEBSITE,PASSWORD) VALUES ('%s','%s')", website, password);

            connect = sqlite3_exec(db, InsertSql, callback, 0, &ErrorMessage);

            if (connect != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", ErrorMessage);
                sqlite3_free(ErrorMessage);
            } else {
                fprintf(stdout, "password for %s saved in database\n", website);
            }
            sqlite3_close(db);
        } else if (strcmp(cmd, "get") == 0) {
            if (connect) {
                fprintf(stderr, "Cant open database: %s\n", sqlite3_errmsg(db));
                return (0);
            } else {
                fprintf(stderr, "Opened database successfully\n");
            }


            sql = "SELECT * FROM PASSWORDS";

            connect = sqlite3_exec(db, sql, callback, (void *) data, &ErrorMessage);

            if (connect != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", ErrorMessage);
                sqlite3_free(ErrorMessage);
            } else {
                fprintf(stdout, "Opened database successfully\n");
            }
            sqlite3_close(db);
        } else if (strcmp(cmd, "update") == 0) {
            char id[50];
            char new_pass[50];

            printf("Which ID?: ");
            scanf("%s", id);
            printf("New password: ");
            scanf("%s", new_pass);


            if (connect) {
                fprintf(stderr, "Cant open database: %s\n", sqlite3_errmsg(db));
                return (0);
            } else {
                fprintf(stdout, "Operation done successfully\n");
            }

            char UpdateSql[128];

            sprintf(UpdateSql, "UPDATE PASSWORDS SET PASSWORD = '%s' WHERE ID=%s;", new_pass, id);

            connect = sqlite3_exec(db, UpdateSql, callback, (void *) data, &ErrorMessage);

            if (connect != SQLITE_OK) {
                fprintf(stderr, "SQL error: %s\n", ErrorMessage);
                sqlite3_free(ErrorMessage);
            } else {
                fprintf(stdout, "Operation done successfully\n");
            }
            sqlite3_close(db);
        }else if(strcmp(cmd, "delete") == 0){
            char id[50];
            printf("Which ID?: ");
            scanf("%s", id);

            if (connect){
                fprintf(stderr, "Cant open database: %s\n", sqlite3_errmsg(db));
                return (0);
            }else{
                fprintf(stderr, "Opened database successfully\n");
            }
            char DeleteSql[128];

            sprintf(DeleteSql, "DELETE FROM PASSWORDS WHERE ID=%s;",id);

            connect = sqlite3_exec(db, DeleteSql, callback, (void*)data, &ErrorMessage);

            if(connect != SQLITE_OK){
                fprintf(stderr, "SQL error: %s\n", ErrorMessage);
                sqlite3_free(ErrorMessage);
            }else{
                fprintf(stdout, "Operation done successfully\n");
            }
            sqlite3_close(db);
        }
    }//while shit
}
