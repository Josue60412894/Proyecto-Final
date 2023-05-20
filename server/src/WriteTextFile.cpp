
#include <iostream>
#include <memory>
#include "WriteTextFile.hpp"
#include <string>
#include <fstream>
#include <ctime>

void write_file(std::string filename, std::string texto){
   
   // fecha actual del sistema
   time_t now = time(0);
   
   // convierte a string el timestamp
   std::string dt = ctime(&now);

   //remueve el \n al final del timestamp
   dt = dt.substr(0,dt.length()-1);

    // Crea un archivo y lo abre para agregar un string
    ofstream MyFile(filename, std::ios_base::app | std::ios_base::out);

      
      MyFile << dt + " - " + texto + "\n";
   // Close the file
   MyFile.close();

}