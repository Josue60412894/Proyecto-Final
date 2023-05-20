#include <iostream>
#include <sqlite3.h>
#include "SQLiteManagement.hpp"
#include <string>
#include <fstream>
#include <ctime>
#include <list>
using namespace std;
// using namespace SQLite;

int SQLiteDB::OpenDb()
{

    sqlite3 *DB;
    int exit = 0;
    exit = sqlite3_open(this->DataBaseName, &DB);

    if (exit)
    {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return (-1);
    }
    else
        //std::cout << "Opened Database Successfully!" << std::endl;
    sqlite3_close(DB);
    return (0);
}

int SQLiteDB::CreateTable()
{
    sqlite3 *DB;

    // Creacion de tabla para almacenar usuarios
    std::string sql = "CREATE TABLE PERSON("
                      "NAME           TEXT    NOT NULL, "
                      "PASSWORD           TEXT    NOT NULL, "
                      "PHONE           TEXT    NOT NULL, "
                      "ID          TEXT     NOT NULL, "
                      "UNIQUE(ID)); "
                      "CREATE TABLE ORDERS("
                      "USER_NAME          TEXT    NOT NULL, "
                      "ITEM_ID           TEXT    NOT NULL, "
                      "ITEM_DESCRIPTION           TEXT    NOT NULL, "
                      "PRICE           TEXT    NOT NULL, "
                      "DATE           TEXT    NOT NULL);";

    // Creacion de tabla para almacenar usuarios actualmente conectados
    int exit = 0;
    exit = sqlite3_open(this->DataBaseName, &DB);
    char *messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    /*
        sql = "CREATE TABLE ACTIVE_USERS("
                          "PASSWORD           TEXT    NOT NULL, "
                          "UNIQUE(NAME));";

         exit = 0;
        exit = sqlite3_open(this->DataBaseName, &DB);
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    */

    if (exit != SQLITE_OK)
    {
        std::cerr << "Error Create Table" << std::endl;
        sqlite3_free(messaggeError);
    }
    else
        std::cout << "Table created Successfully" << std::endl;
    sqlite3_close(DB);
    return (0);
}

int SQLiteDB::CallBackAll(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char *)data);

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL1");
    }
    printf("\n");
    return 0;
}

int SQLiteDB::CallBackSingleValue(void *data, int argc, char **argv, char **azColName)
{

    if (argc > 0 && argv[0])
    {
        string &search_result = *static_cast<string *>(data);
        search_result = argv[0];
    }
    return 0;
}

bool SQLiteDB::AddUser(std::string table, std::string name1, std::string password1, std::string phone, std::string ID)
{
    sqlite3 *DB;
    char *messaggeError;
    int exit = sqlite3_open(this->DataBaseName, &DB);

    string sql("INSERT INTO " + table + " VALUES('" + name1 + "', '" + password1 + "','" + phone + "','" + ID + "');");

    /*
    string sql("INSERT INTO PERSON VALUES(1, 'STEVE', 'GATES', 30, 'PALO ALTO', 1000.0);"
               "INSERT INTO PERSON VALUES(2, 'BILL', 'ALLEN', 20, 'SEATTLE', 300.22);");

   */

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messaggeError);
        return true;
    }
    else
        std::cout << "Records created Successfully!" << std::endl;

    sqlite3_close(DB);
    return false;
}

bool SQLiteDB::AddActiveUser(std::string table, std::string name1)
{
    sqlite3 *DB;
    char *messaggeError;
    int exit = sqlite3_open(this->DataBaseName, &DB);

    string sql("INSERT INTO " + table + " VALUES('" + name1 + "');");

    /*
    string sql("INSERT INTO PERSON VALUES(1, 'STEVE', 'GATES', 30, 'PALO ALTO', 1000.0);"
               "INSERT INTO PERSON VALUES(2, 'BILL', 'ALLEN', 20, 'SEATTLE', 300.22);");

   */

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Error Insert" << std::endl;
        sqlite3_free(messaggeError);
        return true;
    }
    else
        //std::cout << "Records created Successfully!" << std::endl;

    sqlite3_close(DB);
    return false;
}

int SQLiteDB::Select(std::string table)
{
    sqlite3 *DB;
    int exit = 0;
    exit = sqlite3_open(this->DataBaseName, &DB);
    string data("CALLBACK FUNCTION");

    string sql("SELECT * FROM " + table + ";");
    if (exit)
    {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return (-1);
    }
    else
        std::cout << "Opened Database Successfully!" << std::endl;

    int rc = sqlite3_exec(DB, sql.c_str(), SQLiteDB::CallBackAll, (void *)data.c_str(), NULL);

    if (rc != SQLITE_OK)
        cerr << "Error SELECT" << endl;
    else
    {
        cout << "Operation OK!" << endl;
    }

    sqlite3_close(DB);
    return (0);
}

std::string SQLiteDB::SelectSingleValue(std::string column, std::string table, std::string matchcolumn, std::string valuematch)
{
    sqlite3 *DB;
    int exit = 0;
    exit = sqlite3_open(this->DataBaseName, &DB);
    string data("CALLBACK FUNCTION");
    string sql("SELECT " + column + " FROM " + table + " WHERE " + matchcolumn + " = '" + valuematch + "'");
    // string sql("SELECT SURNAME FROM PERSON WHERE NAME = 'Juan'");
    if (exit)
    {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return "error";
    }
    else
        //std::cout << "Opened Database Successfully!" << std::endl;

    std::string search_result;

    // int rc = sqlite3_exec(DB, sql.c_str(), SQLiteDB::callback, (void *)data.c_str(), NULL);
    int rc = sqlite3_exec(DB, sql.c_str(), SQLiteDB::CallBackSingleValue, &search_result, NULL);

    if (rc != SQLITE_OK)
        cerr << "Error SELECT" << endl;
    else
    {
        if (!search_result.empty())
        {
            // std::cout << "Search result: " << search_result << std::endl;
            return search_result;
        }
        else
        {
            //std::cout << "No matching rows found." << std::endl;
            return "nothing";
        }

        //std::cout << "Operation OK!" << std::endl;
    }

    sqlite3_close(DB);

    return search_result;
}

