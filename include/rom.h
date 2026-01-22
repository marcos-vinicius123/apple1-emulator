#pragma once
#include <cstdint>
#include <string>

class Mos6502;

class Rom {
    public:
        Rom();
        uint8_t read(uint16_t addr);
        uint16_t read_address(uint16_t addr);
        void write(uint16_t addr, uint8_t byte);
        void write_address(uint16_t addr, uint16_t address);

        void push(Mos6502 &mos6502, uint8_t value);
        uint8_t pull(Mos6502 &Mos6502);

        void load_file(std::string filename, uint16_t address);

        void display_char(uint8_t value);

    private:
        uint8_t rom[0x10000];
        uint8_t test_code[10] = {'F', 'F', '0', '0', '.', 'F', 'F', 'F', 'F', 0x0d};
        int current = 0;
};