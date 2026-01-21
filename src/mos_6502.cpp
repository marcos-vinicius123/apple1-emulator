#include <cstdint>
#include "mos_6502.h"
#include "rom.h"
#include "adress_modes.h"
#include "opcodes.h"

void Mos6502::step(Rom &rom) {
    uint8_t opcode = rom.read(pc);

    switch (opcode) {
        case 0x0:
            
            break;
        
        default:
            break;
    }
}

void Mos6502::reset(Rom &rom) {
    pc = rom.read_address(0xfffc);
    sp = 0xfd;
    set_interrupt(true);
    set_decimal(false);
    set_break(false);

    ac = x = y = 0;
}

void Mos6502::set_negative(bool value) {
    sr.negative = value;
}

void Mos6502::set_overflow(bool value) {
    sr.overflow = value;
}

void Mos6502::set_unused(bool value) {
    sr.unused = value;
}

void Mos6502::set_break(bool value) {
    sr.break_ = value;
}

void Mos6502::set_decimal(bool value) {
    sr.decimal = value;
}

void Mos6502::set_interrupt(bool value) {
    sr.interrupt = value;
}

void Mos6502::set_zero(bool value) {
    sr.zero = value;
}

void Mos6502::set_carry(bool value) {
    sr.carry = value;
}

bool Mos6502::get_negative() {
    return sr.negative;
}

bool Mos6502::get_overflow() {
    return sr.overflow;
}

bool Mos6502::get_unused() {
    return sr.unused;
}

bool Mos6502::get_break() {
    return sr.break_;
}

bool Mos6502::get_decimal() {
    return sr.decimal;
}

bool Mos6502::get_interrupt() {
    return sr.interrupt;
}

bool Mos6502::get_zero() {
    return sr.zero;
}

bool Mos6502::get_carry() {
    return sr.carry;
}