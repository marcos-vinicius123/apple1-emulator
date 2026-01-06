#include <cstdint>
#include "rom.h"

uint8_t Rom::read(uint16_t addr)
{
    return rom[addr];
}

void Rom::write(uint16_t addr, uint8_t byte) {
    rom[addr] = byte;
}