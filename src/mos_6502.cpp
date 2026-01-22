#include <cstdint>
#include <cstdio>
#include "mos_6502.h"
#include "rom.h"
#include "adress_modes.h"
#include "opcodes.h"

void Mos6502::step(Rom &rom) {
    uint8_t opcode = rom.read(pc);
    Opcodes opcodes;

    // printf("PC: 0x%04X  OPCODE: 0x%02X\n", pc, rom.read(pc));

    switch (opcode) {
        case 0x00:
            opcodes.BRK(*this, rom);
            break;

        case 0x01:
            opcodes.ORA(*this, rom, x_indirect);
            break;

        case 0x05:
            opcodes.ORA(*this, rom, zero_page);
            break;

        case 0x06:
            opcodes.ASL(*this, rom, zero_page);
            break;

        case 0x08:
            opcodes.PHP(*this, rom);
            break;

        case 0x09:
            opcodes.ORA(*this, rom, immediate);
            break;

        case 0x0A:
            opcodes.ASL(*this, rom, Adress_modes::accumulator);
            break;

        case 0x0D:
            opcodes.ORA(*this, rom, absolute);
            break;

        case 0x0E:
            opcodes.ASL(*this, rom, absolute);
            break;


        case 0x10:
            opcodes.BPL(*this, rom);
            break;

        case 0x11:
            opcodes.ORA(*this, rom, y_indirect);
            break;

        case 0x15:
            opcodes.ORA(*this, rom, zero_page_x);
            break;

        case 0x16:
            opcodes.ASL(*this, rom, zero_page_x);
            break;

        case 0x18:
            opcodes.CLC(*this, rom);
            break;

        case 0x19:
            opcodes.ORA(*this, rom, absolute_y);
            break;

        case 0x1D:
            opcodes.ORA(*this, rom, absolute_x);
            break;

        case 0x1E:
            opcodes.ASL(*this, rom, absolute_x);
            break;


        case 0x20:
            opcodes.JSR(*this, rom);
            break;

        case 0x21:
            opcodes.AND(*this, rom, x_indirect);
            break;

        case 0x24:
            opcodes.BIT(*this, rom, zero_page);
            break;

        case 0x25:
            opcodes.AND(*this, rom, zero_page);
            break;

        case 0x26:
            opcodes.ROL(*this, rom, zero_page);
            break;

        case 0x28:
            opcodes.PLP(*this, rom);
            break;

        case 0x29:
            opcodes.AND(*this, rom, immediate);
            break;

        case 0x2A:
            opcodes.ROL(*this, rom, accumulator);
            break;

        case 0x2C:
            opcodes.BIT(*this, rom, absolute);
            break;

        case 0x2D:
            opcodes.AND(*this, rom, absolute);
            break;

        case 0x2E:
            opcodes.ROL(*this, rom, absolute);
            break;


        case 0x30:
            opcodes.BMI(*this, rom);
            break;

        case 0x31:
            opcodes.AND(*this, rom, y_indirect);
            break;

        case 0x35:
            opcodes.AND(*this, rom, zero_page_x);
            break;

        case 0x36:
            opcodes.ROL(*this, rom, zero_page_x);
            break;

        case 0x38:
            opcodes.SEC(*this, rom);
            break;

        case 0x39:
            opcodes.AND(*this, rom, absolute_y);
            break;

        case 0x3D:
            opcodes.AND(*this, rom, absolute_x);
            break;

        case 0x3E:
            opcodes.ROL(*this, rom, absolute_x);
            break;


        case 0x40:
            opcodes.RTI(*this, rom);
            break;

        case 0x41:
            opcodes.EOR(*this, rom, x_indirect);
            break;

        case 0x45:
            opcodes.EOR(*this, rom, zero_page);
            break;

        case 0x46:
            opcodes.LSR(*this, rom, zero_page);
            break;

        case 0x48:
            opcodes.PHA(*this, rom);
            break;

        case 0x49:
            opcodes.EOR(*this, rom, immediate);
            break;

        case 0x4A:
            opcodes.LSR(*this, rom, accumulator);
            break;

        case 0x4C:
            opcodes.JMP(*this, rom, absolute);
            break;

        case 0x4D:
            opcodes.EOR(*this, rom, absolute);
            break;

        case 0x4E:
            opcodes.LSR(*this, rom, absolute);
            break;

        case 0x50:
            opcodes.BVC(*this, rom);
            break;

        case 0x51:
            opcodes.EOR(*this, rom, y_indirect);
            break;

        case 0x55:
            opcodes.EOR(*this, rom, zero_page_x);
            break;

        case 0x56:
            opcodes.LSR(*this, rom, zero_page_x);
            break;

        case 0x58:
            opcodes.CLI(*this, rom);
            break;

        case 0x59:
            opcodes.EOR(*this, rom, absolute_y);
            break;

        case 0x5D:
            opcodes.EOR(*this, rom, absolute_x);
            break;

        case 0x5E:
            opcodes.LSR(*this, rom, absolute_x);
            break;


        case 0x60:
            opcodes.RTS(*this, rom);
            break;

        case 0x61:
            opcodes.ADC(*this, rom, x_indirect);
            break;

        case 0x65:
            opcodes.ADC(*this, rom, zero_page);
            break;

        case 0x66:
            opcodes.ROR(*this, rom, zero_page);
            break;

        case 0x68:
            opcodes.PLA(*this, rom);
            break;

        case 0x69:
            opcodes.ADC(*this, rom, immediate);
            break;

        case 0x6A:
            opcodes.ROR(*this, rom, accumulator);
            break;

        case 0x6C:
            opcodes.JMP(*this, rom, indirect);
            break;

        case 0x6D:
            opcodes.ADC(*this, rom, absolute);
            break;

        case 0x6E:
            opcodes.ROR(*this, rom, absolute);
            break;


        case 0x70:
            opcodes.BVS(*this, rom);
            break;

        case 0x71:
            opcodes.ADC(*this, rom, y_indirect);
            break;

        case 0x75:
            opcodes.ADC(*this, rom, zero_page_x);
            break;

        case 0x76:
            opcodes.ROR(*this, rom, zero_page_x);
            break;

        case 0x78:
            opcodes.SEI(*this, rom);
            break;

        case 0x79:
            opcodes.ADC(*this, rom, absolute_y);
            break;

        case 0x7D:
            opcodes.ADC(*this, rom, absolute_x);
            break;

        case 0x7E:
            opcodes.ROR(*this, rom, absolute_x);
            break;

        case 0x81:
            opcodes.STA(*this, rom, x_indirect);
            break;

        case 0x84:
            opcodes.STY(*this, rom, zero_page);
            break;

        case 0x85:
            opcodes.STA(*this, rom, zero_page);
            break;

        case 0x86:
            opcodes.STX(*this, rom, zero_page);
            break;

        case 0x88:
            opcodes.DEY(*this, rom);
            break;

        case 0x8A:
            opcodes.TXA(*this, rom);
            break;

        case 0x8C:
            opcodes.STY(*this, rom, absolute);
            break;

        case 0x8D:
            opcodes.STA(*this, rom, absolute);
            break;

        case 0x8E:
            opcodes.STX(*this, rom, absolute);
            break;


        case 0x90:
            opcodes.BCC(*this, rom);
            break;

        case 0x91:
            opcodes.STA(*this, rom, y_indirect);
            break;

        case 0x94:
            opcodes.STY(*this, rom, zero_page_x);
            break;

        case 0x95:
            opcodes.STA(*this, rom, zero_page_x);
            break;

        case 0x96:
            opcodes.STX(*this, rom, zero_page_y);
            break;

        case 0x98:
            opcodes.TYA(*this, rom);
            break;

        case 0x99:
            opcodes.STA(*this, rom, absolute_y);
            break;

        case 0x9A:
            opcodes.TXS(*this, rom);
            break;

        case 0x9D:
            opcodes.STA(*this, rom, absolute_x);
            break;


        case 0xA0:
            opcodes.LDY(*this, rom, immediate);
            break;

        case 0xA1:
            opcodes.LDA(*this, rom, x_indirect);
            break;

        case 0xA2:
            opcodes.LDX(*this, rom, immediate);
            break;

        case 0xA4:
            opcodes.LDY(*this, rom, zero_page);
            break;

        case 0xA5:
            opcodes.LDA(*this, rom, zero_page);
            break;

        case 0xA6:
            opcodes.LDX(*this, rom, zero_page);
            break;

        case 0xA8:
            opcodes.TAY(*this, rom);
            break;

        case 0xA9:
            opcodes.LDA(*this, rom, immediate);
            break;

        case 0xAA:
            opcodes.TAX(*this, rom);
            break;

        case 0xAC:
            opcodes.LDY(*this, rom, absolute);
            break;

        case 0xAD:
            opcodes.LDA(*this, rom, absolute);
            break;

        case 0xAE:
            opcodes.LDX(*this, rom, absolute);
            break;


        case 0xB0:
            opcodes.BCS(*this, rom);
            break;

        case 0xB1:
            opcodes.LDA(*this, rom, y_indirect);
            break;

        case 0xB4:
            opcodes.LDY(*this, rom, zero_page_x);
            break;

        case 0xB5:
            opcodes.LDA(*this, rom, zero_page_x);
            break;

        case 0xB6:
            opcodes.LDX(*this, rom, zero_page_y);
            break;

        case 0xB8:
            opcodes.CLV(*this, rom);
            break;

        case 0xB9:
            opcodes.LDA(*this, rom, absolute_y);
            break;

        case 0xBA:
            opcodes.TSX(*this, rom);
            break;

        case 0xBC:
            opcodes.LDY(*this, rom, absolute_x);
            break;

        case 0xBD:
            opcodes.LDA(*this, rom, absolute_x);
            break;

        case 0xBE:
            opcodes.LDX(*this, rom, absolute_y);
            break;


        case 0xC0:
            opcodes.CPY(*this, rom, immediate);
            break;

        case 0xC1:
            opcodes.CMP(*this, rom, x_indirect);
            break;

        case 0xC4:
            opcodes.CPY(*this, rom, zero_page);
            break;

        case 0xC5:
            opcodes.CMP(*this, rom, zero_page);
            break;

        case 0xC6:
            opcodes.DEC(*this, rom, zero_page);
            break;

        case 0xC8:
            opcodes.INY(*this, rom);
            break;

        case 0xC9:
            opcodes.CMP(*this, rom, immediate);
            break;

        case 0xCA:
            opcodes.DEX(*this, rom);
            break;

        case 0xCC:
            opcodes.CPY(*this, rom, absolute);
            break;

        case 0xCD:
            opcodes.CMP(*this, rom, absolute);
            break;

        case 0xCE:
            opcodes.DEC(*this, rom, absolute);
            break;


        case 0xD0:
            opcodes.BNE(*this, rom);
            break;

        case 0xD1:
            opcodes.CMP(*this, rom, y_indirect);
            break;

        case 0xD5:
            opcodes.CMP(*this, rom, zero_page_x);
            break;

        case 0xD6:
            opcodes.DEC(*this, rom, zero_page_x);
            break;

        case 0xD8:
            opcodes.CLD(*this, rom);
            break;

        case 0xD9:
            opcodes.CMP(*this, rom, absolute_y);
            break;

        case 0xDD:
            opcodes.CMP(*this, rom, absolute_x);
            break;

        case 0xDE:
            opcodes.DEC(*this, rom, absolute_x);
            break;


        case 0xE0:
            opcodes.CPX(*this, rom, immediate);
            break;

        case 0xE1:
            opcodes.SBC(*this, rom, x_indirect);
            break;

        case 0xE4:
            opcodes.CPX(*this, rom, zero_page);
            break;

        case 0xE5:
            opcodes.SBC(*this, rom, zero_page);
            break;

        case 0xE6:
            opcodes.INC(*this, rom, zero_page);
            break;

        case 0xE8:
            opcodes.INX(*this, rom);
            break;

        case 0xE9:
            opcodes.SBC(*this, rom, immediate);
            break;

        case 0xEA:
            opcodes.NOP(*this, rom);
            break;

        case 0xEC:
            opcodes.CPX(*this, rom, absolute);
            break;

        case 0xED:
            opcodes.SBC(*this, rom, absolute);
            break;

        case 0xEE:
            opcodes.INC(*this, rom, absolute);
            break;


        case 0xF0:
            opcodes.BEQ(*this, rom);
            break;

        case 0xF1:
            opcodes.SBC(*this, rom, y_indirect);
            break;

        case 0xF5:
            opcodes.SBC(*this, rom, zero_page_x);
            break;

        case 0xF6:
            opcodes.INC(*this, rom, zero_page_x);
            break;

        case 0xF8:
            opcodes.SED(*this, rom);
            break;

        case 0xF9:
            opcodes.SBC(*this, rom, absolute_y);
            break;

        case 0xFD:
            opcodes.SBC(*this, rom, absolute_x);
            break;

        case 0xFE:
            opcodes.INC(*this, rom, absolute_x);
            break;
            
        default:
            // illegal opcode
            opcodes.NOP(*this, rom);
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