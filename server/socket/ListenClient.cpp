#include "ServerSocket.hpp"
#include "SocketException.hpp"
#include "listen_client.hpp"
#include "WriteTextFile.hpp"
#include "RequestHandler.hpp"
#include "SQLiteManagement.hpp"
#include "SQLiteMenu.hpp"
#include "WriteTextFile.hpp"
#include<vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <thread>         // std::thread

void ListenSocket1(SQLiteDB& newdb, std::list<std::string>& registeredUsers, std::list<std::string>& activeUsers){
//void ListenSocket1(){

    const int kPort = 6336;
    const std::string kIp = "127.0.0.1";
    try
    {
        //Create the socket
        ServerSocket server{kPort};
      
        write_file("SocketStatusLog.txt","Server is running: " + server.get_addr_str() + ":" + std::to_string(kPort));
        
        while (true)
        {
            write_file("SocketStatusLog.txt","Listening connection: " + server.get_addr_str() + ":" + std::to_string(kPort));

            ServerSocket new_sock;
         
            server.Accept(new_sock);
        
            try
            {
                std::string data;
                // Receive the message
                new_sock >> data;
                write_file("SocketStatusLog.txt",data);
                
                /////////**********///////////////////////////////////////
                //Crea una clase para procesar el string entrante
                NewRequest incomingString;
                char delimeter = ',';
                
                //Despedaza el string entrante usando el delimitador y almacena los valores en una lista
                incomingString.SplitString(data,delimeter);
                
                //Ejecuta la acción usando el metodo ChooseAction y retorna un string para escritura en el socket
                std::string retorno = incomingString.ChooseAction(newdb, activeUsers);
                 /////////**********///////////////////////////////////////
            
                // Send the message back
                new_sock << retorno;
                 
            }
            catch (SocketException &)
            {
                //std::cout << " " <<  <<std::endl;
                write_file("SocketStatusLog.txt","Something is wrong: " + new_sock.get_addr_str());
            }
        }
    }
    catch (SocketException &e)
   {
        std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
        write_file("SocketStatusLog.txt","SocketStatusLog.txt " + e.description() + "\nExiting.\n");
    }

    return;
}

