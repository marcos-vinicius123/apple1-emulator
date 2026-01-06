#include <cstdint>
#include "rom.h"

uint8_t Rom::read(uint16_t addr) {
    return rom[addr];
}

uint16_t Rom::read_address(uint16_t addr) {
    return (rom[addr+1] << 8) || rom[addr];
}

void Rom::write(uint16_t addr, uint8_t byte) {
    rom[addr] = byte;
}

void Rom::write_address(uint16_t addr, uint16_t address) {
    rom[addr] = address & 0xff;
    rom[addr+1] = address >> 8;
}