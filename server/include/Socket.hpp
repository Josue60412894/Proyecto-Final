// Definition of the Socket class

#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>

const int kMaxHostName = 256;
const int kMaxConnections = 8;
const int kMaxRecv = 512;

/**
 * This is the parent Socket class, used to create the infra
 * required to support Server and Client sockets
*/
class Socket
{
public:
  Socket();
  virtual ~Socket();

  /**
   * This will create the socket
   */
  bool Create();

  /**
   * This is used to bind the server to a specific port
   *
   * @param port Port where the server will be running
   */
  bool Bind(const int port);

  /**
   * This will set the socket to listen the specified connections
   *
   */
  bool Listen() const;

  /**
   * Accepts the incomming connections
   *
   * @param socket Socket to receive the connection
   */
  bool Accept(Socket &socket) const;

  /**
   * This function is used to create a Client Socket connection
   * (not needed if you are creating a Server Socket)
   * @param host IP of the server socket link the connection
   * @param port Port where the server is listenning
  */
  bool Connect(const std::string host, const int port);

  /**
   * This is used to send a message
   * 
   * @param message message to send
   */
  bool Send(const std::string) const;

  /**
   * This is used to receive a message
   * 
   * @param message this will stores the incomming message
   */
  int Recv(std::string &message) const;

  void SetNonBlocking(const bool);

  /**
   * Verifies if is a valid socket
   */
  bool IsValid() const;

  /**
   * Returns the ip addres as a string
   */
  const std::string get_addr_str() const;

  /**
   * Returns the sockaddr_in connection
   */
  const sockaddr_in get_addr() const;

private:
  int m_sock_;
  sockaddr_in m_addr_;
  int famili_sock_;
};

inline const std::string Socket::get_addr_str() const
{
  std::string address = inet_ntoa(this->m_addr_.sin_addr);
  return address;
}

inline const sockaddr_in Socket::get_addr() const
{
  return this->m_addr_;
}

inline bool Socket::IsValid() const
{
  return this->m_sock_ != -1;
}
