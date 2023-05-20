// SocketException class

#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <list>
#include <SQLiteManagement.hpp>

class NewRequest
{

public:
    /**
     * @brief Divide el string entrante de datos con un delimitador
     * @param strToSplit Indica el string a dividir
     * @param delimeter delimitador
     * @return Retorna el dato solicitado
     */
    void SplitString(std::string strToSplit, char delimeter);

    /**
     * @brief Analiza el primer valor del vector data para seleccionar la accion del usuario
     * @param newdb Indica SQlite Database para interacturar
     */
    std::string ChooseAction(SQLiteDB newdb, std::list<std::string>& activeUsers);

    /**
     * @brief Agrega un usuario nuevo a la tabla USERS. Si el usuario ya existe entonces no se agrega
     * @param newdb Indica SQlite Database para interacturar
     * @return Retorna un string con el texto de si el usuario fue agregado o no
     */
    std::string AddUser(SQLiteDB newdb);

    /**
     * @brief Remover Usuario
     * @param newdb Indica SQlite Database para interacturar
     */
    bool RemoveUser(SQLiteDB newdb);

    /**
     * @brief Accion de loguear un usuario. Se verifica si el password ingresado es el correcto.Si todo es correcto se agrega a la tabla ACTIVE_USERS
     * @param newdb Indica SQlite Database para interacturar
     */
    std::string LoginUser(SQLiteDB newdb, std::list<std::string>& activeUsers);

    /**
     * @brief Remueve  usuario de la lista de usuario activos. Y retorna una valor de confirmacion
     * @param newdb Indica SQlite Database para interacturar
     * @return Retorna un string con el texto de si el usuario fue logueado o no
     */
    std::string LogoutUser(SQLiteDB newdb, std::list<std::string>& activeUsers);

    /**
     * @brief Agrega una orden a la tabla ORDERS
     * @param newdb Indica SQlite Database para interacturar
     * @return Retorna un string con el texto de si el usuario fue deslogueado  o no
     */
    bool AddOrder(SQLiteDB newdb);

    /**
     * @brief Remueve una orden de la tabla ORDERS
     * @param newdb Indica SQlite Database para interacturar
     */
    bool DeleteOrder(SQLiteDB newdb);

    /**
     * @brief Muestra  todas lasordenes de un 1 usuario
     * @param newdb Indica SQlite Database para interacturar
     */
    bool ViewOrders(SQLiteDB newdb);

    std::vector<std::string> data; // vector para guardar el string del incoming request del client

private:
};