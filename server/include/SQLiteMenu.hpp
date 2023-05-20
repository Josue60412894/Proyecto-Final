#pragma once
#include <string>
#include <memory> // para smart pointers
#include <list>
using namespace std;

/**
 * @brief Void Loop para correr el SQLite menu en un thread separado
 * 
*/
void menu(SQLiteDB& newdb, std::list<std::string>& registeredUsers, std::list<std::string>& activeUsers);
