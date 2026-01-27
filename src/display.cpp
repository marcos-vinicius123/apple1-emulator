#include "device.h"
#include <ncurses.h>
#include <chrono>

class Display : public Device {
    private:
        bool is_ready() {
            return std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - timer).count()>16;
        }

        void display_char(uint8_t value) {

            //prepare value
            value &= 0x7f;
            if (value==0x0d) {
                addch('\n');
            } else if (value>=0x20 and value <= 0x5f) {
                addch(value);
            }
            // else {
            //     addch(' ');
            // }
            refresh();
            // line_count++;
            // if (line_count==40) {
            //     addch('\n');
            //     line_count = 0;
            // }
        }
        using clock = std::chrono::steady_clock;
        clock::time_point timer = clock::now();
    
    public:
        uint8_t read(uint16_t addr) override {
            if (addr==0xd012) {
                return is_ready() ? 0x0 : 0x80;
            } else {
                return is_ready() ? 0x0 : 0x80;
            }
        }

        void write(uint16_t addr, uint8_t value) override {
            if (addr==0xd012 and is_ready()) {
                display_char(value);
                timer = clock::now();
            }
        }

        bool handles_addr(uint16_t addr) override {
            return (addr==0xd012 or addr==0xd013);
        }

};