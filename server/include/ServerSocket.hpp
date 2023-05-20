#pragma once

#include "Socket.hpp"

/**
 * This class is a concrete implementation of the socket to be used as
 * a Server SocketPRUEBA
*/
class ServerSocket : public Socket
{
public:
    /**
     * This is the constructor of the class, use this if you want to
     * create a Server Socket
    */
    ServerSocket(const int port);
    
    /**
     * This is the empty constructor, use it if you want to create a Socket
     * without predefined configuration
    */
    ServerSocket(){};
    virtual ~ServerSocket();

    /**
     * Override of the << parameter, this is used to receive the messages
     * from the clients
     * 
     * @param message This string holds the message from the client
    */
    const ServerSocket &operator<<(const std::string &message) const;
    
    /**
     * Override of the << parameter, this is used to send the messages
     * to the clients
     * 
     * @param This string contains the message to be sent to the client
    */
    const ServerSocket &operator>>(std::string &message) const;

    /**
     * Accepts the incomming connections
     * 
     * @param socket Socket to receive the connection
    */
    void Accept(ServerSocket &socket);
};
