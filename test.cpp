#include "common.hpp"
#include "siglent.hpp"

#include <chrono>
#include <thread>
#include <iomanip>
#include <iostream>
#include <string>

#include "secrets.hpp"

int main()
{
    Siglent device(secrets::ip, secrets::port);
    device.Connect();

    std::cout << std::setprecision(5);

    std::cout << "Manufacturer: " << device.Manufacturer() << "\n";
    std::cout << "Product: " << device.Product() << "\n";
    std::cout << "Serial Number: " << device.SerialNumber() << "\n";
    std::cout << "Software Version: " << device.SoftwareVersion() << "\n";
    std::cout << "Hardware Version: " << device.HardwareVersion() << "\n";

    std::cout << "Address: " << device.IP() << ":" << device.Port() << "\n\n";

    device.Output(true);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    float voltage = device.Voltage();
    std::cout << "Voltage (V): " << voltage << "\n";

    float current = device.Current();
    std::cout << "Current (A): " << current << "\n";

    float power = device.Power();
    std::cout << "Power (W): " << power << "\n";

    return 0;
}