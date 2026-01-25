#include <cstdint>
#include "device_manager.h"
#include "device.h"

bool DeviceManager::read(uint16_t addr, uint8_t &value) {
    for (auto dev : devices) {
        if (dev->handles_addr(addr)) {
            value = dev->read(addr);
            return true;
        }
    }
    return false;
}

bool DeviceManager::write(uint16_t addr, uint8_t value) {
    for (auto dev : devices) {
        if (dev->handles_addr(addr)) {
            dev->write(addr, value);
            return true;
        }
    }
    return false;
}

void DeviceManager::add_device(Device *device) {
    devices.push_back(device);
}

void DeviceManager::update_devices() {
    for (auto dev : devices) {
        dev->update();
    }
}

DeviceManager device_manager;