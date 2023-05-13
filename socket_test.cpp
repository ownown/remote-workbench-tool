#include <iostream>
#include <string>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>


#define SIGLENT_IP "192.168.1.144"
#define SIGLENT_PORT 5025

int main()
{
    struct sockaddr_in addr;
    std::string cmd = "MEAS:VOLT?";

    int fd;
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        std::cerr << "Socket creation error\n";
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(SIGLENT_PORT);

    if (inet_pton(AF_INET, SIGLENT_IP, &addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address/Address not supported: " << SIGLENT_IP << "\n";
        return -1;
    }

    int status;
    if ((status = connect(fd, (struct sockaddr *)&addr, sizeof(addr))) < 0)
    {
        std::cerr << "Connection failed\n";
        return -1;
    }

    send(fd, cmd.c_str(), cmd.length(), 0);


    const int buffer_size = 1024;
    std::string buffer(buffer_size,0);

    int read_len = read(fd, &buffer[0], buffer_size);
    std::cout << buffer;
    close(fd);
}