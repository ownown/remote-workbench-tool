#include "own_errors.hpp"
#include "siglent.hpp"

#include <iomanip>
#include <iostream>
#include <string>

void Siglent::Connect()
{
    ConnectToDevice();
    DeviceDetails();
}

void Siglent::DeviceDetails()
{
    Write("*IDN?");
    std::string out = Read();

    // From https://java2blog.com/cpp-split-string-by-comma/#Using_the_stdstringerase_and_stdstringfind_function
    size_t pos = 0;
    std::string delimiter = ",";
    std::string token;

    pos = out.find(delimiter);
    if (pos == std::string::npos)
    {
        throw ReadError("Failed to get device details at manufacturer");
    }
    m_manufacturer = out.substr(0, pos);
    out.erase(0, pos + delimiter.length());

    pos = out.find(delimiter);
    if (pos == std::string::npos)
    {
        throw ReadError("Failed to get device details at product");
    }
    m_product = out.substr(0, pos);
    out.erase(0, pos + delimiter.length());

    pos = out.find(delimiter);
    if (pos == std::string::npos)
    {
        throw ReadError("Failed to get device details at serial number");
    }
    m_serial_number = out.substr(0, pos);
    out.erase(0, pos + delimiter.length());

    pos = out.find(delimiter);
    if (pos == std::string::npos)
    {
        throw ReadError("Failed to get device details at software version");
    }
    m_software_version = out.substr(0, pos);
    out.erase(0, pos + delimiter.length());

    m_hardware_version = out;
}

std::string Siglent::Manufacturer()
{
    return m_manufacturer;
}

std::string Siglent::Product()
{
    return m_product;
}

std::string Siglent::SerialNumber()
{
    return m_serial_number;
}

std::string Siglent::SoftwareVersion()
{
    return m_software_version;
}

std::string Siglent::HardwareVersion()
{
    return m_hardware_version;
}


float Siglent::Voltage()
{
    Write("MEAS:VOLT?");
    return std::stof(Read());
}

void Siglent::Voltage(float voltage)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(3) << voltage;
    std::string command = "CH1:VOLT " + ss.str();
    std::cout << command << "\n";
    Write(command);
}

float Siglent::Current()
{
    Write("MEAS:CURR?");
    return std::stof(Read());
}

void Siglent::Current(float current)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(3) << current;
    std::string command = "CH1:CURR " + ss.str();
    std::cout << command << "\n";
    Write(command);
}

float Siglent::Power()
{
    Write("MEAS:POWE?");
    return std::stof(Read());
}

void Siglent::Output(bool enable)
{
    std::string command = "OUTP CH1,";
    if (enable)
    {
        command += "ON";
    }
    else
    {
        command += "OFF";
    }

    Write(command);
}