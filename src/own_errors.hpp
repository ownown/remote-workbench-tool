#ifndef _OWN_ERRORS_HPP_
#define _OWN_ERRORS_HPP_

#include <exception>
#include <string>

class SocketError: public std::exception
{
private:
    std::string m_msg;
public:
    SocketError(std::string msg): m_msg(msg) {}
    const char *what()
    {
        std::string out = "Socket Error: " + m_msg;
        return out.c_str();
    }
};

class ConnectionError: public std::exception
{
private:
    std::string m_msg;
public:
    ConnectionError(std::string msg): m_msg(msg) {}
    const char *what()
    {
        std::string out = "Connection Error: " + m_msg;
        return out.c_str();
    }
};

class WriteError: public std::exception
{
private:
    std::string m_msg;
public:
    WriteError(std::string msg): m_msg(msg) {}
    const char *what()
    {
        std::string out = "Write Error: " + m_msg;
        return out.c_str();
    }
};


class ReadError: public std::exception
{
private:
    std::string m_msg;
public:
    ReadError(std::string msg): m_msg(msg) {}
    const char *what()
    {
        std::string out = "Read Error: " + m_msg;
        return out.c_str();
    }
};

#endif // _OWN_ERRORS_HPP_