#include <cstdint>
#include "opcodes.h"
#include "mos_6502.h"
#include "rom.h"
#include "adress_modes.h"

uint8_t Opcodes::get_value(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    switch (mode) {
        case Adress_modes::absolute:
            return rom.read(rom.read_address(mos6502.pc+1));

        case Adress_modes::absolute_x:
            return rom.read(rom.read_address(mos6502.pc+1)+mos6502.x);
        
        case Adress_modes::absolute_y:
            return rom.read(rom.read_address(mos6502.pc+1)+mos6502.y);
            
        case Adress_modes::immediate:
            return rom.read(mos6502.pc+1);

        case Adress_modes::x_indirect: {
            uint8_t ptr, zp;
            zp = rom.read(mos6502.pc+1);
            ptr = (zp+mos6502.x)&0xff;
            uint16_t address = (rom.read((ptr+1)&0xff) << 8) | rom.read(ptr);
            return rom.read(address);
        }

        case Adress_modes::y_indirect: {
            uint8_t zp = rom.read(mos6502.pc+1);
            uint16_t address = (rom.read((zp+1)&0xff) << 8) | rom.read(zp);
            return rom.read(address+mos6502.y);
        }

        case Adress_modes::zero_page:
            return rom.read(rom.read(mos6502.pc+1));
        
        case Adress_modes::zero_page_x:
            return rom.read((rom.read(mos6502.pc+1)+mos6502.x)&0xff);
        
        case Adress_modes::zero_page_y:
            return rom.read((rom.read(mos6502.pc+1)+mos6502.y)&0xff);

        default:
            return 0;
    }
}

uint16_t Opcodes::get_adress(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    switch (mode) {
        case Adress_modes::absolute:
            return rom.read_address(mos6502.pc+1);

        case Adress_modes::absolute_x:
            return rom.read_address(mos6502.pc+1)+mos6502.x;
        
        case Adress_modes::absolute_y:
            return rom.read_address(mos6502.pc+1)+mos6502.y;
            
        case Adress_modes::immediate:
            return mos6502.pc+1;

        case Adress_modes::x_indirect: {
            uint8_t ptr, zp;
            zp = rom.read(mos6502.pc+1);
            ptr = (zp+mos6502.x)&0xff;
            uint16_t address = (rom.read((ptr+1)&0xff) << 8) | rom.read(ptr);
            return address;
        }

        case Adress_modes::y_indirect: {
            uint8_t zp = rom.read(mos6502.pc+1);
            uint16_t address = (rom.read((zp+1)&0xff) << 8) | rom.read(zp);
            return address+mos6502.y;
        }

        case Adress_modes::zero_page:
            return rom.read(mos6502.pc+1);
        
        case Adress_modes::zero_page_x:
            return (rom.read(mos6502.pc+1)+mos6502.x)&0xff;
        
        case Adress_modes::zero_page_y:
            return (rom.read(mos6502.pc+1)+mos6502.y)&0xff;

        default:
            return 0;
    }
}

//Transfer instructions

//Loads value into the Accumulator
void Opcodes::LDA(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    mos6502.ac = get_value(mos6502, rom, mode);

    mos6502.set_negative(mos6502.ac>>7);
    mos6502.set_zero(mos6502.ac==0);
}

//Loads value into the X register
void Opcodes::LDX(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    mos6502.x = get_value(mos6502, rom, mode);

    mos6502.set_negative(mos6502.x>>7);
    mos6502.set_zero(mos6502.x==0);
}

//Loads value into the Y register
void Opcodes::LDY(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    mos6502.y = get_value(mos6502, rom, mode);

    mos6502.set_negative(mos6502.y>>7);
    mos6502.set_zero(mos6502.y==0);
}

//Stores the Accumulator in ROM
void Opcodes::STA(Mos6502 &mos6502, Rom &rom, Adress_modes mode)  {
    rom.write(get_adress(mos6502, rom, mode), mos6502.ac);
}

//Stores the X register in ROM
void Opcodes::STX(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
   rom.write(get_adress(mos6502, rom, mode), mos6502.x);
    
}

//Stores the Y register in ROM
void Opcodes::STY(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    rom.write(get_adress(mos6502, rom, mode), mos6502.y);
}

//Transfers the Accumulator to the X register
void Opcodes::TAX(Mos6502 &mos6502, Rom &rom) {
    mos6502.x = mos6502.ac;

    mos6502.set_negative(mos6502.x>>7);
    mos6502.set_zero(mos6502.x==0);
}

//Transfers the Accumulator to the Y register
void Opcodes::TAY(Mos6502 &mos6502, Rom &rom) {
    mos6502.y = mos6502.ac;

    mos6502.set_negative(mos6502.y>>7);
    mos6502.set_zero(mos6502.y==0);
}

//Transfers the Stack Pointer to the X register
void Opcodes::TSX(Mos6502 &mos6502, Rom &rom) {
    mos6502.x = mos6502.sp;

    mos6502.set_negative(mos6502.x>>7);
    mos6502.set_zero(mos6502.x==0);
}

//Transfers the X register to the Accumulator
void Opcodes::TXA(Mos6502 &mos6502, Rom &rom) {
    mos6502.ac = mos6502.x;

    mos6502.set_negative(mos6502.ac>>7);
    mos6502.set_zero(mos6502.ac==0);
}

//Transfers the X register to the Stack Pointer
void Opcodes::TXS(Mos6502 &mos6502, Rom &rom) {
    mos6502.sp = mos6502.x;
}

//Transfers the Y register to the Accumulator
void Opcodes::TYA(Mos6502 &mos6502, Rom &rom) {
    mos6502.ac = mos6502.y;

    mos6502.set_negative(mos6502.ac>>7);
    mos6502.set_zero(mos6502.ac==0);
}

//Stack instructions

//Pushes the Accumulator
void Opcodes::PHA(Mos6502  &mos6502, Rom &rom) {
    rom.push(mos6502, mos6502.ac);
}

//Pushes the Status register
void Opcodes::PHP(Mos6502  &mos6502, Rom &rom) {
    rom.push(mos6502, mos6502.sr.to_byte());
}

//Pulls the Accumulator
void Opcodes::PLA(Mos6502  &mos6502, Rom &rom) {
    mos6502.ac = rom.pull(mos6502);

    mos6502.set_negative(mos6502.ac>>7);
    mos6502.set_zero(mos6502.ac==0);
}

//Pulls the Status register
void Opcodes::PLP(Mos6502  &mos6502, Rom &rom) {
    mos6502.sr.from_byte(rom.pull(mos6502));
}