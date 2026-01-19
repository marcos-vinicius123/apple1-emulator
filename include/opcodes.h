#pragma once
#include "adress_modes.h"

class Mos6502;
class Rom;

class Opcodes {
    public:
        void ADC(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void AND(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void ASL(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void BCC(Mos6502 &mos6502, Rom &rom);
        void BCS(Mos6502 &mos6502, Rom &rom);
        void BEQ(Mos6502 &mos6502, Rom &rom);
        void BIT(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void BMI(Mos6502 &mos6502, Rom &rom);
        void BNE(Mos6502 &mos6502, Rom &rom);
        void BPL(Mos6502 &mos6502, Rom &rom);
        void BRK(Mos6502 &mos6502, Rom &rom);
        void BVC(Mos6502 &mos6502, Rom &rom);
        void BVS(Mos6502 &mos6502, Rom &rom);
        void CLC(Mos6502 &mos6502, Rom &rom);
        void CLD(Mos6502 &mos6502, Rom &rom);
        void CLI(Mos6502 &mos6502, Rom &rom);
        void CLV(Mos6502 &mos6502, Rom &rom);
        void CMP(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void CPX(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void CPY(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void DEC(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void DEX(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void DEY(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void EOR(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void INC(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void INX(Mos6502 &mos6502, Rom &rom);
        void INY(Mos6502 &mos6502, Rom &rom);
        void JMP(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void JSR(Mos6502 &mos6502, Rom &rom);
        void LDA(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void LDX(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void LDY(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void LSR(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void NOP(Mos6502 &mos6502, Rom &rom);
        void ORA(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void PHA(Mos6502 &mos6502, Rom &rom);
        void PHP(Mos6502 &mos6502, Rom &rom);
        void PLA(Mos6502 &mos6502, Rom &rom);
        void PLP(Mos6502 &mos6502, Rom &rom);
        void ROL(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void ROR(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void RTI(Mos6502 &mos6502, Rom &rom);
        void RTS(Mos6502 &mos6502, Rom &rom);
        void SBC(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void SEC(Mos6502 &mos6502, Rom &rom);
        void SED(Mos6502 &mos6502, Rom &rom);
        void SEI(Mos6502 &mos6502, Rom &rom);
        void STA(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void STX(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void STY(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
        void TAX(Mos6502 &mos6502, Rom &rom);
        void TAY(Mos6502 &mos6502, Rom &rom);
        void TSX(Mos6502 &mos6502, Rom &rom);
        void TXA(Mos6502 &mos6502, Rom &rom);
        void TXS(Mos6502 &mos6502, Rom &rom);
        void TYA(Mos6502 &mos6502, Rom &rom);


        //returns the value stored in the &rom based on the adress mode
        uint8_t get_value(Mos6502 &mos6502, Rom &rom, Adress_modes mode);

        //returns the adress based on the adress mode.
        uint16_t get_adress(Mos6502 &mos6502, Rom &rom, Adress_modes mode);
    };