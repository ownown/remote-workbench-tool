#ifndef _OWN_DEVICE_HPP_
#define _OWN_DEVICE_HPP_

#include <string>

#include <arpa/inet.h>

class Device
{
private:
    bool m_is_open;
    bool m_is_connected;
    int m_sock;
    struct sockaddr_in *m_addr;
    std::string m_ip;
    unsigned int m_port;
protected:
    void Open();
    void Close();
    void ConnectToDevice();

    void Write(std::string command);
    std::string Read(unsigned int buffer_size = 64);
public:
    Device(const std::string ip, const unsigned int port);
    ~Device();

    std::string IP();
    void        IP(std::string ip);

    unsigned int    Port();
    void            Port(unsigned int port);
};

#endif // _OWN_DEVICE_HPP_