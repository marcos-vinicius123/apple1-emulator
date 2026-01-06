#include <cstdint>
#include "opcodes.h"
#include "mos_6502.h"
#include "rom.h"
#include "adress_modes.h"

// transfer instructions

//Loads value into the Accumulator
void Opcodes::LDA(Mos6502 mos6502, Rom rom, Adress_modes mode) {
    uint8_t value;
    switch (mode) {
    case Adress_modes::immediate:
        value = rom.read(mos6502.pc+1);
        break;
    
    case Adress_modes::zero_page:
        value = rom.read(rom.read(mos6502.pc+1));
        break;
    
    case Adress_modes::zero_page_x:
        value = rom.read(rom.read(mos6502.pc+1)+mos6502.x);
        break;
    
    case Adress_modes::absolute:
        value = rom.read(rom.read_address(mos6502.pc+1));
        break;
    
    case Adress_modes::absolute_x:
        value = rom.read(rom.read_address(mos6502.pc+1)+mos6502.x);
        break;
    
    case Adress_modes::absolute_y:
        value = rom.read(rom.read_address(mos6502.pc+1)+mos6502.y);
        break;
    
    case Adress_modes::x_indirect:
        value = rom.read(rom.read_address(rom.read(mos6502.pc+1)+mos6502.x));
        break;

    case Adress_modes::y_indirect:
        value = rom.read(rom.read_address(rom.read(mos6502.pc+1))+mos6502.y);
        break;

    default:
        break;

    mos6502.ac = value;
    mos6502.set_negative(value>>7);
    mos6502.set_zero(value==0);
    }
}

//Loads value into register X
void Opcodes::LDX(Mos6502 mos6502, Rom rom, Adress_modes mode) {
    uint8_t value;

    switch (mode) {
    case Adress_modes::immediate:
        value = rom.read(mos6502.pc+1);
        break;
    
    case Adress_modes::zero_page:
        value = rom.read(rom.read(mos6502.pc+1));
        break;
    
    case Adress_modes::zero_page_y:
        value = rom.read(rom.read(mos6502.pc+1)+mos6502.y);
        break;
    
    case Adress_modes::absolute:
        value = rom.read(rom.read_address(mos6502.pc+1));
        break;
    
    case Adress_modes::absolute_y:
        value = rom.read(rom.read_address(mos6502.pc+1)+mos6502.y);
    
    default:
        break;
    }

    mos6502.x = value;
    mos6502.set_negative(value>>7);
    mos6502.set_zero(value==0);
}

//Loads value into register Y
void Opcodes::LDY(Mos6502 mos6502, Rom rom, Adress_modes mode) {
    uint8_t value;

    switch (mode) {
    case Adress_modes::immediate:
        value = rom.read(mos6502.pc+1);
        break;
    
    case Adress_modes::zero_page:
        value = rom.read(rom.read(mos6502.pc+1));
        break;
    
    case Adress_modes::zero_page_x:
        value = rom.read(rom.read(mos6502.pc+1)+mos6502.x);
        break;
    
    case Adress_modes::absolute:
        value = rom.read(rom.read_address(mos6502.pc+1));
        break;
    
    case Adress_modes::absolute_x:
        value = rom.read(rom.read_address(mos6502.pc+1)+mos6502.x);
    
    default:
        break;
    }

    mos6502.y = value;
    mos6502.set_negative(value>>7);
    mos6502.set_zero(value==0);
}

//Stores the Accumulator in ROM
void Opcodes::STA(Mos6502 mos6502, Rom  rom, Adress_modes mode)  {
    switch (mode) {
    case Adress_modes::zero_page:
        rom.write(rom.read(mos6502.pc+1), mos6502.ac);
        break;
    
    case Adress_modes::zero_page_x:
        rom.write(rom.read(mos6502.pc+1)+mos6502.x, mos6502.ac);
        break;
    
    case Adress_modes::absolute:
        rom.write(rom.read_address(mos6502.pc+1), mos6502.ac);
        break;
    
    case Adress_modes::absolute_x:
        rom.write(rom.read_address(mos6502.pc+1)+mos6502.x, mos6502.ac);
        break;
    
    case Adress_modes::absolute_y:
        rom.write(rom.read_address(mos6502.pc+1)+mos6502.y, mos6502.ac);
        break;

    case Adress_modes::x_indirect:
        rom.write(rom.read_address(rom.read(mos6502.pc+1)+mos6502.x), mos6502.ac);
        break;

    case Adress_modes::y_indirect:
        rom.write(rom.read_address(rom.read(mos6502.pc+1))+mos6502.y, mos6502.ac);
        break;

    default:
        break;
    }
}

//Stores the X register in ROM
void Opcodes::STX(Mos6502 mos6502, Rom rom, Adress_modes mode) {
    switch (mode) {
    case Adress_modes::zero_page:
        rom.write(rom.read(mos6502.pc+1), mos6502.x);
        break;
    
    case Adress_modes::zero_page_y:
        rom.write(rom.read(mos6502.pc+1)+mos6502.y, mos6502.x);
        break;
    
    case Adress_modes::absolute:
        rom.write(rom.read_address(mos6502.pc+1), mos6502.x);
        break;
    
    default:
        break;
    }
}

//Stores the Y register in ROM
void Opcodes::STY(Mos6502 mos6502, Rom rom, Adress_modes mode) {
    switch (mode) {
    case Adress_modes::zero_page:
        rom.write(rom.read(mos6502.pc+1), mos6502.y);
        break;
    
    case Adress_modes::zero_page_x:
        rom.write(rom.read(mos6502.pc+1)+mos6502.x, mos6502.y);
        break;
    
    case Adress_modes::absolute:
        rom.write(rom.read_address(mos6502.pc+1), mos6502.y);
        break;
    
    default:
        break;
    }
}