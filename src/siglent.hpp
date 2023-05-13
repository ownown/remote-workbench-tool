#ifndef _SIGLENT_HPP_
#define _SIGLENT_HPP_

#include <string>

#include <arpa/inet.h>

#include "device.hpp"

class Siglent: public Device
{
private:
    std::string m_manufacturer;
    std::string m_product;
    std::string m_serial_number;
    std::string m_software_version;
    std::string m_hardware_version;

    void DeviceDetails();
public:
    Siglent(const std::string ip, const unsigned int port): Device(ip, port) {}

    void Connect();

    std::string Manufacturer();
    std::string Product();
    std::string SerialNumber();
    std::string SoftwareVersion();
    std::string HardwareVersion();

    float Voltage();
    void Voltage(float voltage);

    float Current();
    void Current(float current);

    float Power();

    void Output(bool enable);
};

#endif // _SIGLENT_HPP_