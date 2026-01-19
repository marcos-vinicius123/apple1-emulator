#pragma once
#include <cstdint>

struct StatusRegister {
    bool negative = false;
    bool overflow = false;
    bool unused = false;
    bool break_ = false;
    bool decimal = false;
    bool interrupt = false;
    bool zero = false;
    bool carry = false;

    uint8_t to_byte() {
        return (carry << 0) | (zero << 1) | (interrupt << 2) | 
               (decimal << 3) | (break_ << 4) | (unused << 5) |
               (overflow << 6) | (negative << 7);
    }

    static StatusRegister from_byte(uint8_t byte) {
        StatusRegister reg;
        reg.carry = byte & 0x01;
        reg.zero = (byte >> 1) & 0x01;
        reg.interrupt = (byte >> 2) & 0x01;
        reg.decimal = (byte >> 3) & 0x01;
        reg.break_ = (byte >> 4) & 0x01;
        reg.unused = (byte >> 5) & 0x01;  // Always 0
        reg.overflow = (byte >> 6) & 0x01;
        reg.negative = (byte >> 7) & 0x01;
        return reg;
    }
};