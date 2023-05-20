#include <iostream>
#include <sqlite3.h>
#include "SQLiteManagement.hpp"
#include "SQLiteMenu.hpp"
#include "WriteTextFile.hpp"
#include <string>
#include <list>
#include <fstream>

void menu(SQLiteDB &newdb, std::list<std::string> &registeredUsers, std::list<std::string> &activeUsers)
{

    // Menu de interaccion con la base de datos
    while (true)
    {

        int opcion;

        std::cout << "\n*******************************************" << std::endl;
        std::cout << "*                 - MENU -                *" << std::endl;
        std::cout << "*   [1] - Abrir base de datos             *" << std::endl;
        std::cout << "*   [2] - Crear tablas PERSON & ORDERS    *" << std::endl;
        std::cout << "*   [3] - Mostrar Sesiones Activas        *" << std::endl;
        std::cout << "*   [4] - Ver todos los usuarios          *" << std::endl;
        std::cout << "*   [5] - Ver todas las ordenes           *" << std::endl;
        std::cout << "*   [6] - Imprimir actividades de usuario *" << std::endl;
        std::cout << "******************************************\n"<< std::endl;
        std::cout << "Acontiunacion escriba el número de opcion a elegir:\n"<< std::endl;

        std::cout << "--> ";
        std::cin >> opcion;

        switch (opcion)
        {
        case 1:

            newdb.OpenDb();

            break;

        case 2:

            newdb.CreateTable();

            break;

        case 3:

            for (const auto &value : activeUsers)
            {
                std::cout << value << " ";
            }
            break;

        case 4:

            newdb.Select("PERSON");

            write_file("SQLiteStatusLog.txt", "LECTURA DE TODA LA TABLA DE PERSON");

            break;

        case 5:

            newdb.Select("ORDERS");

            write_file("SQLiteStatusLog.txt", "LECTURA DE TODA LA TABLA DE ORDERS");

            break;

        case 6:

            ///// Solicitud de nombre 
            std::string name;
            std::cout << "Inserte Nombre del usuario:\n"
                      << std::endl;
            std::cout << "--> ";
            std::cin >> name;

            //Creacion del file name y abre el del stream
            std::string filename = "logs_" + name + ".txt";
            std::ifstream file(filename);

            //verifica si el archivo se pudo abrir
            if (!file.is_open())
            {
                std::cout << "Failed to open the file: " << filename << std::endl;
                return;
            }

            std::list<std::string> lines;

            std::string line;

            // Se almacenan todas las lineas del fichero en la lista LINES
            while (std::getline(file, line))
            {
                lines.push_back(line);
            }

            //Impresion de todos los items en la lista 

            for (const auto &line : lines)
            {
                std::cout << line << std::endl;
            }

            file.close();
            break;

        }
    }
}