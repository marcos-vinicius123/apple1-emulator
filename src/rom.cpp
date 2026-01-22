#include <cstdint>
#include <iostream>
#include <fstream>
#include "rom.h"
#include "mos_6502.h"
#include "device_manager.h"

Rom::Rom() {
    for (auto &v : rom) {
        v = 0xea;
    }
}

uint8_t Rom::read(uint16_t addr) {
    uint8_t value;
    if (device_manager.read(addr, value)) {
        return value;
    }
    return rom[addr];
}

uint16_t Rom::read_address(uint16_t addr) {
    return (read(addr+1) << 8) | read(addr);
}

void Rom::write(uint16_t addr, uint8_t value) {
    if (!device_manager.write(addr, value)) {
        rom[addr] = value;
    }
}

void Rom::write_address(uint16_t addr, uint16_t address) {
    write(addr, address & 0xff);
    write(addr+1, address >> 8);
}

void Rom::push(Mos6502 &mos6502, uint8_t value) {
    rom[mos6502.sp + 0x100] = value;
    mos6502.sp--;
}

uint8_t Rom::pull(Mos6502 &mos6502) {
    return rom[++mos6502.sp + 0x100];
}

void Rom::load_file(std::string filename, uint16_t address) {
    std::ifstream file(filename, std::ios::binary);

    uint8_t byte;
    int count = 0;

    if (!file) {
        std::cerr << "failed to  open file: " << filename << "\n";
    }

    while (file.read(reinterpret_cast<char*>(&byte), 1)) {
        rom[address+count] = byte;
        count++;
    }
}

void Rom::display_char(uint8_t value) {
    char ch  = value &0x7f;

    if (ch==0x0d) {
        ch = '\n';
    } else if (ch < 0x20) {
        ch = ' ';
    }

    std::cout << ch;
    std::cout.flush();
}