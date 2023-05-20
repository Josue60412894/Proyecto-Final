// Implementation of the ServerSocket class

#include "ServerSocket.hpp"
#include "SocketException.hpp"

ServerSocket::ServerSocket(const int port)
{
    if (!Socket::Create())
    {
        throw SocketException("Could not create server socket.");
    }

    if (!Socket::Bind(port))
    {
        throw SocketException("Could not bind to port.");
    }

    if (!Socket::Listen())
    {
        throw SocketException("Could not listen to socket.");
    }
}

ServerSocket::~ServerSocket()
{
}

const ServerSocket &ServerSocket::operator<<(const std::string &s) const
{
    if (!Socket::Send(s))
    {
        throw SocketException("Could not write to socket.");
    }

    return *this;
}

const ServerSocket &ServerSocket::operator>>(std::string &s) const
{
    if (!Socket::Recv(s))
    {
        throw SocketException("Could not read from socket.");
    }

    return *this;
}

void ServerSocket::Accept(ServerSocket &sock)
{
    if (!Socket::Accept(sock))
    {
        throw SocketException("Could not accept socket.");
    }
}
