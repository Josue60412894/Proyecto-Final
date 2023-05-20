#pragma once
#include <string>
#include <memory> // para smart pointers
#include <list>
#include <iostream>
#include <thread> // std::thread
#include <SQLiteManagement.hpp>


using namespace std;


/**
 * @brief Void loop para correr la rutina de recepción en Socket en un thread unico
 * @param newdb Indica SQlite Database para interacturar
 * 
*/
 void ListenSocket1(SQLiteDB& newdb, std::list<std::string>& registeredUsers, std::list<std::string>& activeUsers);
