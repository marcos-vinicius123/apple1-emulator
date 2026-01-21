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

    mos6502.pc += addr_mode_to_bytes(mode);
}

//Loads value into the X register
void Opcodes::LDX(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    mos6502.x = get_value(mos6502, rom, mode);

    mos6502.set_negative(mos6502.x>>7);
    mos6502.set_zero(mos6502.x==0);

    mos6502.pc += addr_mode_to_bytes(mode);
}

//Loads value into the Y register
void Opcodes::LDY(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    mos6502.y = get_value(mos6502, rom, mode);

    mos6502.set_negative(mos6502.y>>7);
    mos6502.set_zero(mos6502.y==0);

    mos6502.pc += addr_mode_to_bytes(mode);
}

//Stores the Accumulator in ROM
void Opcodes::STA(Mos6502 &mos6502, Rom &rom, Adress_modes mode)  {
    rom.write(get_adress(mos6502, rom, mode), mos6502.ac);

    mos6502.pc += addr_mode_to_bytes(mode);
}

//Stores the X register in ROM
void Opcodes::STX(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
   rom.write(get_adress(mos6502, rom, mode), mos6502.x);

   mos6502.pc += addr_mode_to_bytes(mode);
}

//Stores the Y register in ROM
void Opcodes::STY(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    rom.write(get_adress(mos6502, rom, mode), mos6502.y);

    mos6502.pc += addr_mode_to_bytes(mode);
}

//Transfers the Accumulator to the X register
void Opcodes::TAX(Mos6502 &mos6502, Rom &rom) {
    mos6502.x = mos6502.ac;

    mos6502.set_negative(mos6502.x>>7);
    mos6502.set_zero(mos6502.x==0);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Transfers the Accumulator to the Y register
void Opcodes::TAY(Mos6502 &mos6502, Rom &rom) {
    mos6502.y = mos6502.ac;

    mos6502.set_negative(mos6502.y>>7);
    mos6502.set_zero(mos6502.y==0);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Transfers the Stack Pointer to the X register
void Opcodes::TSX(Mos6502 &mos6502, Rom &rom) {
    mos6502.x = mos6502.sp;

    mos6502.set_negative(mos6502.x>>7);
    mos6502.set_zero(mos6502.x==0);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Transfers the X register to the Accumulator
void Opcodes::TXA(Mos6502 &mos6502, Rom &rom) {
    mos6502.ac = mos6502.x;

    mos6502.set_negative(mos6502.ac>>7);
    mos6502.set_zero(mos6502.ac==0);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Transfers the X register to the Stack Pointer
void Opcodes::TXS(Mos6502 &mos6502, Rom &rom) {
    mos6502.sp = mos6502.x;

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Transfers the Y register to the Accumulator
void Opcodes::TYA(Mos6502 &mos6502, Rom &rom) {
    mos6502.ac = mos6502.y;

    mos6502.set_negative(mos6502.ac>>7);
    mos6502.set_zero(mos6502.ac==0);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Stack instructions

//Pushes the Accumulator
void Opcodes::PHA(Mos6502  &mos6502, Rom &rom) {
    rom.push(mos6502, mos6502.ac);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Pushes the Status register
void Opcodes::PHP(Mos6502  &mos6502, Rom &rom) {
    uint8_t value = mos6502.sr.to_byte();
    value |= 0b00110000;
    rom.push(mos6502, value);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Pulls the Accumulator
void Opcodes::PLA(Mos6502  &mos6502, Rom &rom) {
    mos6502.ac = rom.pull(mos6502);

    mos6502.set_negative(mos6502.ac>>7);
    mos6502.set_zero(mos6502.ac==0);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Pulls the Status register
void Opcodes::PLP(Mos6502  &mos6502, Rom &rom) {
    mos6502.sr.from_byte(rom.pull(mos6502)|0x20);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Decrement and increment instructions

//Decrements ROM
void Opcodes::DEC(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint16_t addr = get_adress(mos6502, rom, mode);
    rom.write(addr, rom.read(addr)-1);

    mos6502.set_negative(rom.read(addr)>>7);
    mos6502.set_zero(rom.read(addr)==0);

    mos6502.pc += addr_mode_to_bytes(mode);
}

//Decrements the X register
void Opcodes::DEX(Mos6502 &mos6502,  Rom &rom) {
    mos6502.x--;

    mos6502.set_negative(mos6502.x>>7);
    mos6502.set_zero(mos6502.x==0);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Decrements the Y register
void Opcodes::DEY(Mos6502 &mos6502, Rom &rom) {
    mos6502.y--;

    mos6502.set_negative(mos6502.y>>7);
    mos6502.set_zero(mos6502.y==0);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Increments ROM
void Opcodes::INC(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint16_t addr = get_adress(mos6502, rom, mode);
    rom.write(addr, rom.read(addr)+1);

    mos6502.set_negative(rom.read(addr)>>7);
    mos6502.set_zero(rom.read(addr)==0);

    mos6502.pc += addr_mode_to_bytes(mode);
}

//Increments the X register
void Opcodes::INX(Mos6502 &mos6502,  Rom &rom) {
    mos6502.x++;

    mos6502.set_negative(mos6502.x>>7);
    mos6502.set_zero(mos6502.x==0);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Increments the Y register
void Opcodes::INY(Mos6502 &mos6502, Rom &rom) {
    mos6502.y++;

    mos6502.set_negative(mos6502.y>>7);
    mos6502.set_zero(mos6502.y==0);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
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

    mos6502.pc += addr_mode_to_bytes(mode);
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

    mos6502.pc += addr_mode_to_bytes(mode);
}

//Logical operations instructions

//Binary and with the Accumulator
void Opcodes::AND(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    mos6502.ac &= get_value(mos6502, rom, mode);

    mos6502.set_negative(mos6502.ac>>7);
    mos6502.set_zero(mos6502.ac==0);

    mos6502.pc += addr_mode_to_bytes(mode);
}

//Binary exclusive or with the Accumulator
void Opcodes::EOR(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    mos6502.ac ^= get_value(mos6502, rom, mode);

    mos6502.set_negative(mos6502.ac>>7);
    mos6502.set_zero(mos6502.ac==0);

    mos6502.pc += addr_mode_to_bytes(mode);
}

//Binary or with the Accumulator
void Opcodes::ORA(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    mos6502.ac |= get_value(mos6502, rom, mode);

    mos6502.set_negative(mos6502.ac>>7);
    mos6502.set_zero(mos6502.ac==0);

    mos6502.pc += addr_mode_to_bytes(mode);
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

    mos6502.pc += addr_mode_to_bytes(mode);
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

    mos6502.pc += addr_mode_to_bytes(mode);
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

    mos6502.pc += addr_mode_to_bytes(mode);
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

    mos6502.pc += addr_mode_to_bytes(mode);
}

//Flag instructions

//Clears the carry flag
void Opcodes::CLC(Mos6502 &mos6502, Rom &rom) {
    mos6502.set_carry(false);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Clears the decimal flag
void Opcodes::CLD(Mos6502 &mos6502, Rom &rom) {
    mos6502.set_decimal(false);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//TODO:implement delay
//Clears the interrupt flag
void Opcodes::CLI(Mos6502 &mos6502, Rom &rom) {
    mos6502.set_interrupt(false);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Clears the overflow flag
void Opcodes::CLV(Mos6502 &mos6502, Rom &rom) {
    mos6502.set_overflow(false);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Sets the carry flag
void Opcodes::SEC(Mos6502 &mos6502, Rom &rom) {
    mos6502.set_carry(true);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Sets the decimal flag
void Opcodes::SED(Mos6502 &mos6502, Rom &rom) {
    mos6502.set_decimal(true);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//TODO:implement delay
//Sets the interrupt flag
void Opcodes::SEI(Mos6502 &mos6502, Rom &rom) {
    mos6502.set_interrupt(true);

    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}

//Comparisions instructions

//Compare with the Accumulator
void Opcodes::CMP(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint8_t value = get_value(mos6502, rom, mode);
    uint16_t result = mos6502.ac - value;

    mos6502.set_zero(value==mos6502.ac);
    mos6502.set_carry(mos6502.ac>=value);
    mos6502.set_negative(result & 0x80);

    mos6502.pc += addr_mode_to_bytes(mode);
}

//Compare with the X register
void Opcodes::CPX(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint8_t value = get_value(mos6502, rom, mode);
    uint16_t result = mos6502.x - value;

    mos6502.set_zero(value==mos6502.x);
    mos6502.set_carry(mos6502.x>=value);
    mos6502.set_negative(result & 0x80);

    mos6502.pc += addr_mode_to_bytes(mode);
}

//Compare with the Y register
void Opcodes::CPY(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint8_t value = get_value(mos6502, rom, mode);
    uint16_t result = mos6502.y - value;

    mos6502.set_zero(value==mos6502.y);
    mos6502.set_carry(mos6502.y>=value);
    mos6502.set_negative(result & 0x80);

    mos6502.pc += addr_mode_to_bytes(mode);
}

//Bit test instruction

//Bitwise comparasion with the Accumulator
void Opcodes::BIT(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
    uint8_t value = get_value(mos6502, rom, mode);
    uint8_t result = mos6502.ac & value;

    mos6502.set_zero(result==0);
    mos6502.set_negative(value>>7);
    mos6502.set_overflow(value & 0x40);

    mos6502.pc += addr_mode_to_bytes(mode);
}


//Conditional branch instructions

//Branch on carry clear
void Opcodes::BCC(Mos6502 &mos6502, Rom &rom) {
    int8_t offset = get_value(mos6502, rom, Adress_modes::immediate);

    mos6502.pc += 2; 
    mos6502.pc += offset * !mos6502.get_carry();
}

//Branch on carry set
void Opcodes::BCS(Mos6502 &mos6502, Rom &rom) {
    int8_t offset = get_value(mos6502, rom, Adress_modes::immediate);

    mos6502.pc += 2; 
    mos6502.pc += offset * mos6502.get_carry();
}

//Branch on zero set
void Opcodes::BEQ(Mos6502 &mos6502, Rom &rom) {
    int8_t offset = get_value(mos6502, rom, Adress_modes::immediate);

    mos6502.pc += 2; 
    mos6502.pc += offset * mos6502.get_zero();
}

//Branch on negative set
void Opcodes::BMI(Mos6502 &mos6502, Rom &rom) {
    int8_t offset = get_value(mos6502, rom, Adress_modes::immediate);

    mos6502.pc += 2; 
    mos6502.pc += offset * mos6502.get_negative();
}
//Branch on zero clear
void Opcodes::BNE(Mos6502 &mos6502, Rom &rom) {
    int8_t offset = get_value(mos6502, rom, Adress_modes::immediate);

    mos6502.pc += 2; 
    mos6502.pc += offset * !mos6502.get_zero();
}

//Branch on negative clear
void Opcodes::BPL(Mos6502 &mos6502, Rom &rom) {
    int8_t offset = get_value(mos6502, rom, Adress_modes::immediate);

    mos6502.pc += 2; 
    mos6502.pc += offset * !mos6502.get_negative();
}

//Branch on overflow clear
void Opcodes::BVC(Mos6502 &mos6502, Rom &rom) {
    int8_t offset = get_value(mos6502, rom, Adress_modes::immediate);

    mos6502.pc += 2; 
    mos6502.pc += offset * !mos6502.get_overflow();
}

//Branch on overflow set
void Opcodes::BVS(Mos6502 &mos6502, Rom &rom) {
    int8_t offset = get_value(mos6502, rom, Adress_modes::immediate);

    mos6502.pc += 2; 
    mos6502.pc += offset * mos6502.get_overflow();
}

//Jumps and subroutines instructions

//Jump
void Opcodes::JMP(Mos6502 &mos6502, Rom &rom, Adress_modes mode) {
     uint16_t address = get_adress(mos6502, rom, Adress_modes::absolute);

     if (mode==Adress_modes::indirect) {
        uint8_t low = rom.read(address);
        uint8_t high = rom.read((address & 0xff00) | ((address+1) & 0x00ff));
        address = (high << 8) | low;
     }

     mos6502.pc = address;
}

//Jump subroutine
void Opcodes::JSR(Mos6502 &mos6502, Rom &rom) {
    uint16_t return_addr = mos6502.pc+2;
    uint16_t sub_addr = get_adress(mos6502, rom, Adress_modes::absolute);

    rom.push(mos6502, return_addr>>8);
    rom.push(mos6502, return_addr&0x00ff);

    mos6502.pc = sub_addr;
}

//Return from subroutine
void Opcodes::RTS(Mos6502 &mos6502, Rom &rom) {
    uint8_t low = rom.pull(mos6502);
    uint8_t high = rom.pull(mos6502);
    
    mos6502.pc = ((high << 8) | low) + 1;
}

//Interrupts instructions

//Break / software interrupt
void Opcodes::BRK(Mos6502 &mos6502, Rom &rom) {
    mos6502.pc += 2;
    rom.push(mos6502, mos6502.pc>>8);
    rom.push(mos6502, mos6502.pc&0x00ff);
    rom.push(mos6502, mos6502.sr.to_byte() | 0b00110000);

    mos6502.set_interrupt(true);
    mos6502.pc = rom.read_address(0xfffe); //new program counter from the IRQ vector
}

//Return from interrupt
void Opcodes::RTI(Mos6502 &mos6502, Rom &rom) {
    mos6502.sr.from_byte(rom.pull(mos6502));
    mos6502.set_break(false);
    mos6502.set_unused(true);
    mos6502.pc = rom.pull(mos6502) | (rom.pull(mos6502)<<8);
}

//Other instruction
void Opcodes::NOP(Mos6502 &mos6502, Rom &rom) {
    mos6502.pc += addr_mode_to_bytes(Adress_modes::implied);
}