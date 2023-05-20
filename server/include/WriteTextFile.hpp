#pragma once
#include <string>
#include <memory> // para smart pointers
using namespace std;

/**
 * @brief Escribe una linea en un archivo de texto junto con la fecha/hora
 * @param filename Indica el nombre del archivo .txt
 * @param lista Indicar nota a ingresar en el archivo .txt
 * 
*/

void write_file(std::string filename, std::string texto);