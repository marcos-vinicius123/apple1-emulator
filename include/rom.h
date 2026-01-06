#pragma once
#include <cstdint>

class Rom {
    public:
        uint8_t read(uint16_t addr);
        uint16_t read_address(uint16_t addr);
        void write(uint16_t addr, uint8_t byte);
        void write_address(uint16_t addr, uint16_t address);

    private:
        uint8_t rom[0x10000];
};