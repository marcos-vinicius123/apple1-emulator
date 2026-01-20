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
    uint8_t value = mos6502.sr.to_byte();
    value |= 0b00110000;
    rom.push(mos6502, value);
}

//Pulls the Accumulator
void Opcodes::PLA(Mos6502  &mos6502, Rom &rom) {
    mos6502.ac = rom.pull(mos6502);

    mos6502.set_negative(mos6502.ac>>7);
    mos6502.set_zero(mos6502.ac==0);
}

//Pulls the Status register
void Opcodes::PLP(Mos6502  &mos6502, Rom &rom) {
    mos6502.sr.from_byte(rom.pull(mos6502)|0x20);
}

//Decrement and increment instructions

//Decrements ROM
void Opcodes::DEC(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint16_t addr = get_adress(mos6502, rom, mode);
    rom.write(addr, rom.read(addr)-1);

    mos6502.set_negative(rom.read(addr)>>7);
    mos6502.set_zero(rom.read(addr)==0);
}

//Decrements the X register
void Opcodes::DEX(Mos6502 &mos6502,  Rom &rom) {
    mos6502.x--;

    mos6502.set_negative(mos6502.x>>7);
    mos6502.set_zero(mos6502.x==0);
}

//Decrements the Y register
void Opcodes::DEY(Mos6502 &mos6502, Rom &rom) {
    mos6502.y--;

    mos6502.set_negative(mos6502.y>>7);
    mos6502.set_zero(mos6502.y==0);
}

//Increments ROM
void Opcodes::INC(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint16_t addr = get_adress(mos6502, rom, mode);
    rom.write(addr, rom.read(addr)+1);

    mos6502.set_negative(rom.read(addr)>>7);
    mos6502.set_zero(rom.read(addr)==0);
}

//Increments the X register
void Opcodes::INX(Mos6502 &mos6502,  Rom &rom) {
    mos6502.x++;

    mos6502.set_negative(mos6502.x>>7);
    mos6502.set_zero(mos6502.x==0);
}

//Increments the Y register
void Opcodes::INY(Mos6502 &mos6502, Rom &rom) {
    mos6502.y++;

    mos6502.set_negative(mos6502.y>>7);
    mos6502.set_zero(mos6502.y==0);
}


//Arithmetic instructions

//TODO: Implement decimal mode support in both the ADC and SBC instructions
//Add with carry  
void Opcodes::ADC(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint8_t value = get_value(mos6502, rom, mode);
    uint16_t sum = mos6502.ac + value + mos6502.get_carry();
    mos6502.set_carry(sum>0xff);
    mos6502.set_overflow(~(mos6502.ac ^ value) & (mos6502.ac ^ sum) & 0x80);
    mos6502.ac = sum & 0xff;
    mos6502.set_zero(mos6502.ac==0);
    mos6502.set_negative(mos6502.ac>>7);
}

//Subtract with carry
void Opcodes::SBC(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint8_t value = ~get_value(mos6502, rom, mode);
    uint16_t sum = mos6502.ac + value + mos6502.get_carry();
    mos6502.set_carry(sum>0xff);
    mos6502.set_overflow(~(mos6502.ac ^ value) & (mos6502.ac ^ sum) & 0x80);
    mos6502.ac = sum & 0xff;
    mos6502.set_zero(mos6502.ac==0);
    mos6502.set_negative(mos6502.ac>>7);
}

//Logical operations instructions

//Binary and with the Accumulator
void Opcodes::AND(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    mos6502.ac &= get_value(mos6502, rom, mode);

    mos6502.set_negative(mos6502.ac>>7);
    mos6502.set_zero(mos6502.ac==0);
}

//Binary exclusive or with the Accumulator
void Opcodes::EOR(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    mos6502.ac ^= get_value(mos6502, rom, mode);

    mos6502.set_negative(mos6502.ac>>7);
    mos6502.set_zero(mos6502.ac==0);
}

//Binary or with the Accumulator
void Opcodes::ORA(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    mos6502.ac |= get_value(mos6502, rom, mode);

    mos6502.set_negative(mos6502.ac>>7);
    mos6502.set_zero(mos6502.ac==0);
}

//Shift and rotate instructions

//Arithmetic shift left
void Opcodes::ASL(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint8_t value = mode==Adress_modes::accumulator ? mos6502.ac : get_value(mos6502, rom, mode);
    
    mos6502.set_carry(value >> 7);
    value <<= 1;
    mos6502.set_negative(value >> 7);
    mos6502.set_zero(value==0);

    if (mode==Adress_modes::accumulator) {
        mos6502.ac = value;
    } else {
        rom.write(get_adress(mos6502, rom, mode), value);
    }
}

//Logical shift right
void Opcodes::LSR(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint8_t value = mode==Adress_modes::accumulator ? mos6502.ac : get_value(mos6502, rom, mode);
    
    mos6502.set_carry(value & 0x1);
    value >>= 1;
    mos6502.set_negative(false);
    mos6502.set_zero(value==0);

    if (mode==Adress_modes::accumulator) {
        mos6502.ac = value;
    } else {
        rom.write(get_adress(mos6502, rom, mode), value);
    }
}

//Rotate left
void Opcodes::ROL(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint8_t value = mode==Adress_modes::accumulator ? mos6502.ac : get_value(mos6502, rom, mode);
    bool old_carry = mos6502.get_carry();

    mos6502.set_carry(value>>7);
    value <<= 1;
    value |= old_carry;

    mos6502.set_negative(value>>7);
    mos6502.set_zero(value==0);

    if (mode==Adress_modes::accumulator) {
        mos6502.ac = value;
    } else {
        rom.write(get_adress(mos6502, rom, mode), value);
    }
}

//Rotate right
void Opcodes::ROR(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint8_t value = mode==Adress_modes::accumulator ? mos6502.ac : get_value(mos6502, rom, mode);
    bool old_carry = mos6502.get_carry();

    mos6502.set_carry(value&0x1);
    value >>= 1;
    value |= (uint8_t)old_carry<<7;

    mos6502.set_negative(value>>7);
    mos6502.set_zero(value==0);

    if (mode==Adress_modes::accumulator) {
        mos6502.ac = value;
    } else {
        rom.write(get_adress(mos6502, rom, mode), value);
    }
}

//Flag instructions

//Clears the carry flag
void Opcodes::CLC(Mos6502 &mos6502, Rom &rom) {
    mos6502.set_carry(false);
}

//Clears the decimal flag
void Opcodes::CLD(Mos6502 &mos6502, Rom &rom) {
    mos6502.set_decimal(false);
}

//TODO:implement delay
//Clears the interrupt flag
void Opcodes::CLI(Mos6502 &mos6502, Rom &rom) {
    mos6502.set_interrupt(false);
}

//Clears the overflow flag
void Opcodes::CLV(Mos6502 &mos6502, Rom &rom) {
    mos6502.set_overflow(false);
}

//Sets the carry flag
void Opcodes::SEC(Mos6502 &mos6502, Rom &rom) {
    mos6502.set_carry(true);
}

//Sets the decimal flag
void Opcodes::SED(Mos6502 &mos6502, Rom &rom) {
    mos6502.set_decimal(true);
}

//TODO:implement delay
//Sets the interrupt flag
void Opcodes::SEI(Mos6502 &mos6502, Rom &rom) {
    mos6502.set_interrupt(true);
}

//Comparisions instructions

//Compare with the Accumulator
void Opcodes::CMP(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint8_t value = get_value(mos6502, rom, mode);
    uint16_t result = mos6502.ac - value;

    mos6502.set_zero(value==mos6502.ac);
    mos6502.set_carry(mos6502.ac>=value);
    mos6502.set_negative(result & 0x80);
}

//Compare with the X register
void Opcodes::CPX(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint8_t value = get_value(mos6502, rom, mode);
    uint16_t result = mos6502.x - value;

    mos6502.set_zero(value==mos6502.x);
    mos6502.set_carry(mos6502.x>=value);
    mos6502.set_negative(result & 0x80);
}

//Compare with the Y register
void Opcodes::CPY(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint8_t value = get_value(mos6502, rom, mode);
    uint16_t result = mos6502.y - value;

    mos6502.set_zero(value==mos6502.y);
    mos6502.set_carry(mos6502.y>=value);
    mos6502.set_negative(result & 0x80);
}

//Bit test instruction

//Bitwise comparasion with the Accumulator
void Opcodes::BIT(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint8_t value = get_value(mos6502, rom, mode);
    uint8_t result = mos6502.ac & value;

    mos6502.set_zero(result==0);
    mos6502.set_negative(value>>7);
    mos6502.set_overflow(value & 0x40);
}