#pragma once
#include <cstdint>

class Mos6502;

class Rom {
    public:
        uint8_t read(uint16_t addr);
        uint16_t read_address(uint16_t addr);
        void write(uint16_t addr, uint8_t byte);
        void write_address(uint16_t addr, uint16_t address);

        void push(Mos6502 &mos6502, uint8_t value);
        uint8_t pull(Mos6502 &Mos6502);

    private:
        uint8_t rom[0x10000];
};