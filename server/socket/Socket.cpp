// Implementation of the Socket class.

#include "Socket.hpp"
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>

Socket::Socket() : m_sock_{-1}, famili_sock_{AF_INET}
{
    memset(&m_addr_,
           0,
           sizeof(m_addr_));
}

Socket::~Socket()
{
    if (IsValid())
    {
        ::close(m_sock_);
    }
}

bool Socket::Create()
{
    m_sock_ = socket(this->famili_sock_,
                     SOCK_STREAM,
                     0);

    if (!IsValid())
    {
        return false;
    }

    // TIME_WAIT - argh
    int on = 1;
    if (setsockopt(m_sock_, SOL_SOCKET, SO_REUSEADDR, (const char *)&on, sizeof(on)) == -1)
    {
        return false;
    }
    return true;
}

bool Socket::Bind(const int port)
{

    if (!IsValid())
    {
        return false;
    }

    m_addr_.sin_family = this->famili_sock_;
    m_addr_.sin_addr.s_addr = INADDR_ANY;
    m_addr_.sin_port = htons(port);

    int bind_return = ::bind(m_sock_,
                             (struct sockaddr *)&m_addr_,
                             sizeof(m_addr_));

    if (bind_return == -1)
    {
        return false;
    }

    return true;
}

bool Socket::Listen() const
{
    if (!IsValid())
    {
        return false;
    }

    int listen_return = ::listen(m_sock_, kMaxConnections);

    if (listen_return == -1)
    {
        return false;
    }

    return true;
}

bool Socket::Accept(Socket &new_socket) const
{
    int addr_length = sizeof(m_addr_);
    new_socket.m_sock_ = ::accept(m_sock_, (sockaddr *)&m_addr_, (socklen_t *)&addr_length); 
    if (new_socket.m_sock_ <= 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Socket::Send(const std::string s) const
{
    int status = ::send(m_sock_, s.c_str(), s.size(), MSG_NOSIGNAL);
    if (status == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int Socket::Recv(std::string &output_message) const
{
    auto buffer_size{kMaxRecv + 1};
    char buffer[buffer_size];

    output_message = "";

    memset(buffer, 0, buffer_size);

    auto recv_status = ::recv(m_sock_, buffer, kMaxRecv, 0);

    if (recv_status == -1)
    {
        std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
    }
    else if (recv_status == 0)
    {
        return 0;
    }
    else
    {
        output_message = buffer;
    }
    return recv_status;
}

bool Socket::Connect(const std::string host, const int port)
{
    if (!IsValid())
    {
        return false;
    }

    m_addr_.sin_family = this->famili_sock_;
    m_addr_.sin_port = htons(port);

    auto status = inet_pton(this->famili_sock_, host.c_str(), &m_addr_.sin_addr);

   std::cout << "IP: " << this->get_addr_str() << std::endl;

    if (errno == EAFNOSUPPORT)
    {
        return false;
    }

    status = ::connect(m_sock_, (sockaddr *)&m_addr_, sizeof(m_addr_));

    return status == 0;
}

void Socket::SetNonBlocking(const bool block)
{
    int opts;

    opts = fcntl(m_sock_,
                 F_GETFL);

    if (opts < 0)
    {
        return;
    }

    if (block)
    {
        opts = (opts | O_NONBLOCK);
    }
    else
    {
        opts = (opts & ~O_NONBLOCK);
    }

    fcntl(m_sock_, F_SETFL, opts);
}
