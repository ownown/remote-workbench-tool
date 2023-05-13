#include  "device.hpp"

#include <arpa/inet.h>
#include <unistd.h>

#include <iostream>
#include <string>

#include "common.hpp"
#include "own_errors.hpp"

Device::Device(const std::string ip, const unsigned int port)
    : m_ip(ip), m_port(port), m_is_open(false), m_is_connected(false)
{
    m_addr = new struct sockaddr_in;
    Open();
}

Device::~Device()
{
    delete m_addr;
    close(m_sock);
}

void Device::ConnectToDevice()
{
    if (!m_is_open)
    {
        Open();
    }

    int status;
    if ((status = connect(m_sock, (struct sockaddr *)m_addr, sizeof(*m_addr))) < 0)
    {
        throw SocketError("Failed to connect to " + m_ip + ":" + std::to_string(m_port) + ": status code " + std::to_string(status));
    }
    m_is_connected = true;
}

void Device::Open()
{
    if (m_is_open)
    {
        Close();
    }

    if ((m_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        throw SocketError("Socket creation error");
    }

    m_addr->sin_family = AF_INET;
    m_addr->sin_port = htons(m_port);

    if (inet_pton(AF_INET, m_ip.c_str(), &m_addr->sin_addr) <= 0)
    {
        throw SocketError("Invalid address/address not supported: " + m_ip + ":" + std::to_string(m_port));
    }

    m_is_open = true;
}

void Device::Close()
{
    close(m_sock);
    m_is_open = false;
    m_is_connected = false;
}

std::string Device::IP()
{
    return m_ip;
}

void Device::IP(std::string ip)
{
    m_ip = ip;

    bool was_connected = m_is_connected;
    Close();
    Open();
    if (was_connected)
    {
        ConnectToDevice();
    }
}

unsigned int Device::Port()
{
    return m_port;
}

void Device::Port(unsigned int port)
{
    m_port = port;
    bool was_connected = m_is_connected;
    Close();
    Open();
    if (was_connected)
    {
        ConnectToDevice();
    }
}


void Device::Write(std::string command)
{
    if (!m_is_open)
    {
        throw SocketError("Socket not opened");
    }

    if (!m_is_connected)
    {
        throw ConnectionError("Not connected");
    }

    ssize_t status = send(m_sock, command.c_str(), command.length(), 0);
    if (status <= 0)
    {
        throw WriteError("Failed to write command \"" + command + "\": status code: " + std::to_string(status));
    }
}

std::string Device::Read(unsigned int buffer_size)
{
    if (!m_is_connected)
    {
        throw ConnectionError("Not connected");
    }

    std::string buffer(buffer_size, 0);
    int read_len = read(m_sock, &buffer[0], buffer_size);
    buffer.resize(read_len);
    buffer.shrink_to_fit();
    common::trim(buffer);
    return buffer;
}
