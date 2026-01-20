#include <cstdint>
#include "rom.h"
#include "mos_6502.h"

uint8_t Rom::read(uint16_t addr) {
    return rom[addr];
}

uint16_t Rom::read_address(uint16_t addr) {
    return (rom[addr+1] << 8) | rom[addr];
}

void Rom::write(uint16_t addr, uint8_t byte) {
    rom[addr] = byte;
}

void Rom::write_address(uint16_t addr, uint16_t address) {
    rom[addr] = address & 0xff;
    rom[addr+1] = address >> 8;
}

void Rom::push(Mos6502 &mos6502, uint8_t value) {
    rom[mos6502.sp + 0x100] = value;
    mos6502.sp--;
}

uint8_t Rom::pull(Mos6502 &mos6502) {
    return rom[++mos6502.sp + 0x100];
}