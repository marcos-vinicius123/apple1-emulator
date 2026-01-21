#pragma once
#include <cstdint>
#include "adress_modes.h"
#include "status_register.h"

class Rom;

class Mos6502 {
    public:
        void step(Rom &rom);
        void reset(Rom &rom);

        void set_negative(bool value);
        void set_overflow(bool value);
        void set_unused(bool value);
        void set_break(bool value);
        void set_decimal(bool value);
        void set_interrupt(bool value);
        void set_zero(bool value);
        void set_carry(bool value);

        bool get_negative();
        bool get_overflow();
        bool get_unused();
        bool get_break();
        bool get_decimal();
        bool get_interrupt();
        bool get_zero();
        bool get_carry();

        uint16_t pc;
        uint8_t ac, x, y, sp;
        StatusRegister sr;
};