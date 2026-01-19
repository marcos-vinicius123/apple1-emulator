#include <cstdint>
#include "mos_6502.h"
#include "rom.h"
#include "adress_modes.h"
#include "opcodes.h"

void Mos6502::step(Rom &rom) {
    uint8_t opcode = rom.read(pc);

    switch (opcode) {
        case 0x0:
            /* code */
            break;
        
        default:
            break;
    }
}

void Mos6502::set_negative(bool value) {
    sr.negative = value;
}

void Mos6502::set_overflow(bool value) {
    sr.overflow = value;
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