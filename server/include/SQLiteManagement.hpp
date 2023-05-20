#pragma once
#include <string>
#include <memory> // para smart pointers
#include <list>
using namespace std;
// namespace SQLite

class SQLiteDB // declaracion de la clase SQLiteDB para crear un objeto de base de datos
{
public:
    /**
     * @brief Abrir una nueva de base de datos
     */
    int OpenDb();

    /**
     * @brief Se crean las tablas USERS, ACTIVE_USERS y ORDERS
     *
     */
    int CreateTable();

    /**
     * @brief Imprime todos datos extraidos de la interface de SQLite
     * @return Retorna el dato solicitado
     */
    static int CallBackAll(void *data, int argc, char **argv, char **azColName);

    /**
     * @brief Imprime todos datos extraidos de la interface de SQLite
     * @return Retorna el dato solicitado
     */
    static int CallBackColmnList(void *data, int argc, char **argv, char **colName);

    /**
     * @brief Retorna un solo dato string extraido de la interface de SQLite
     * @return Retorna el dato solicitado
     */
    static int CallBackSingleValue(void *data, int argc, char **argv, char **azColName);

    /**
     * @brief Agrega un nuevo usuario en la tabla USERS
     * @param table Indicar el nombre de la tabla
     * @param name1 indicar el valor del Nombre a ingresar
     * @param password1 indicar el valor del passowrd a ingresar
     * @param phone indicar el valor del passowrd a ingresar
     * @param ID indicar el valor del passowrd a ingresar
     */
    bool AddUser(std::string table, std::string name1, std::string password1, std::string phone, std::string ID);

    /**
     * @brief Inserta una entrada en la tabla ACTIVE_USERS para registrar los usuarios conectados activamente
     * @param table Indicar el nombre de la tabla
     * @param name1 indicar el valor del Nombre a ingresar
     */
    bool AddActiveUser(std::string table, std::string name1);

    /**
     * @brief Imprime todos los datos de la tabla PERSONA
     */
    int Select(std::string table);

    /**
     * @brief Elimina una linea en la tabla
     * @param table Indicar el nombre de la tabla
     * @param column indicar el nombre de la columna a buscar
     * @param valuematch indicar el valor a buscar en la columna para eliminar ese row
     */
    std::string DeleteEntry(std::string table, std::string column, std::string valuematch);

    /**
     * @brief Muestra una celda especifica dentro de una tabla
     * @param column Indicar el nombre de la columna a mostrar
     * @param table indicar el nombre de la tabla
     * @param matchcolumn indicar el nombre de la columna donde se buscara una match
     * @param valuematch indicar el valor a matchear en la co
     */
    std::string SelectSingleValue(std::string column, std::string table, std::string matchcolumn, std::string valuematch);

    /**
     * @brief Muestra una celda especifica dentro de una tabla
     * @param column Indicar el nombre de la columna a mostrar
     * @param table indicar el nombre de la tabla
     * @param matchcolumn indicar el nombre de la columna donde se buscara una match
     * @param valuematch indicar el valor a matchear en la co
     */
    std::string SelectRSingleValue(std::string column, std::string table, std::string matchcolumn, std::string valuematch);

    /**
     * @brief Nombre de la base de datos
     */
    const char *DataBaseName;

private:
};

void output_file();
