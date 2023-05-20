#include <iostream>
#include <sqlite3.h>
#include "RequestHandler.hpp"
#include "WriteTextFile.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <list>

using namespace std;

void NewRequest::SplitString(std::string strToSplit, char delimeter)
{

    std::vector<std::string> tmp;

    stringstream ss(strToSplit);

    string token;
    while (getline(ss, token, delimeter))
    {

        this->data.push_back(token);
    }

    // Print the contents of the vector for debugin
    /*
    for (const auto &tmp1 : this->data)
    {
        std::cout << tmp1 << std::endl;
    }
    */
}

std::string NewRequest::ChooseAction(SQLiteDB newdb, std::list<std::string> &activeUsers)
{

    if (this->data[0] == "ADD_USER")
    {
        return AddUser(newdb);
    }
    else if (this->data[0] == "LOGIN_USER")
    {
        return LoginUser(newdb, activeUsers);
    }
    else if (this->data[0] == "LOGOUT_USER")
    {

        return LogoutUser(newdb, activeUsers); // deletes user from the table of users currently logged in
    }
    else if (this->data[0] == "LOG_EVENT")
    {
        write_file("logs_" + this->data[1] + ".txt", this->data[2]); // log action in logs_NAME.txt
    }

    return "Error";
}

std::string NewRequest::AddUser(SQLiteDB newdb)
{

    std::cout << "ADD USER" << std::endl;

    if (newdb.AddUser("PERSON", this->data[1], this->data[2], this->data[3], this->data[4]) == false) // add new User (must be unique)
    {
        write_file("logs_" + this->data[1] + ".txt", "Se agregó usuario a la tabla USERS " + this->data[1]); // log action in logs_NAME.txt

        return "Usuario agregado con Exito";
    }

    return "Usuario no pudo ser agregado";
}

std::string NewRequest::LoginUser(SQLiteDB newdb, std::list<std::string> &activeUsers)

{

    std::string RetrievedPassword = newdb.SelectSingleValue("PASSWORD", "PERSON", "NAME", this->data[1]);

    if (RetrievedPassword == this->data[2]) // compares entered password agains password in the records
    {

        // newdb.AddActiveUser("ACTIVE_USERS", this->data[1]); // adds Name to the table of active USERS

        write_file("logs_" + this->data[1] + ".txt", "Loging de " + this->data[1]); // log action in logs_NAME.txt

        activeUsers.push_back(this->data[1]);

        return "acceso permitido";
    }
    return "acceso denegado";
}

std::string NewRequest::LogoutUser(SQLiteDB newdb, std::list<std::string> &activeUsers)
{
    activeUsers.remove(this->data[1]);

    write_file("logs_" + this->data[1] + ".txt", "Logout de " + this->data[1]); // log action in logs_NAME.txt

    return "Usuario desconectado";
}