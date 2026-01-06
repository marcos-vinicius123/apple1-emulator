#pragma once
#include <cstdint>
#include "adress_modes.h"
#include "status_register.h"

class Mos6502 {
    public:
        void step(Rom rom);
        void set_negative(bool value);
        void set_overflow(bool value);
        void set_break(bool value);
        void set_decimal(bool value);
        void set_interrupt(bool value);
        void set_zero(bool value);
        void set_carry(bool value);
        uint16_t pc;
        uint8_t ac, x, y, sp;
        StatusRegister sr;
};