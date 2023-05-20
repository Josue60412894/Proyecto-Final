#include "ServerSocket.hpp"
#include "Socket.hpp"
#include "SocketException.hpp"
#include "listen_client.hpp"
#include "SQLiteManagement.hpp"
#include "SQLiteMenu.hpp"
#include "WriteTextFile.hpp"
#include <list>
#include <string>
#include <iostream>
#include <thread> // std::thread
using namespace std;



int main(int argc, char *argv[])
{

  SQLiteDB newdb;

  newdb.DataBaseName = "OrderHandlerUC.db";


  std::string search_result;

  
  std::list<std::string> UsuariosRegistrados;

  std::list<std::string> UsuariosActivos;


  //std::thread first(ListenSocket1); // spawn new thread that calls first()
  
  std::thread first(ListenSocket1, std::ref(newdb), std::ref(UsuariosRegistrados), std::ref(UsuariosActivos)); // spawn new thread that calls first()
  
  std::thread second(menu, std::ref(newdb), std::ref(UsuariosRegistrados), std::ref(UsuariosActivos));   // spawn new thread that calls second(0)

  // synchronize threads:
  first.join();  // pauses until first finishes
  second.join(); // pauses until second finishes

  std::cout << "socket 1 and menu completed.\n";

  return 0;
}