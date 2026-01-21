#pragma once
#include <cstdint>

struct StatusRegister {
    bool negative = false;
    bool overflow = false;
    bool unused = true;
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

    void from_byte(uint8_t byte) {
        carry = byte & 0x01;
        zero = (byte >> 1) & 0x01;
        interrupt = (byte >> 2) & 0x01;
        decimal = (byte >> 3) & 0x01;
        break_ = (byte >> 4) & 0x01;
        unused = true;  // Always 1
        overflow = (byte >> 6) & 0x01;
        negative = (byte >> 7) & 0x01;
    }
};