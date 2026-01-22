#pragma once
#include <cstdint>
#include <vector>

class Device;

class DeviceManager {
    public:
        bool read(uint16_t addr, uint8_t &value);
        bool write(uint16_t addr, uint8_t value);
        void add_device(Device *device);

    private:
        std::vector<Device*> devices;
};

extern DeviceManager device_manager;