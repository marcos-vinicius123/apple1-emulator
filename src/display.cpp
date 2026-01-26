#include "device.h"
#include <ncurses.h>

class Display : public Device {
    private:
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

        int line_count = 0;
        bool ready = true;
        int timer = 0;
    
    public:
        uint8_t read(uint16_t addr) override {
            if (addr==0xd012) {
                return ready ? 0x0 : 0x80;
            } else {
                return ready ? 0x0 : 0x80;
            }
        }

        void write(uint16_t addr, uint8_t value) override {
            if (addr==0xd012 and ready) {
                display_char(value);
                ready = false;
                timer = 2;
            }
        }

        bool handles_addr(uint16_t addr) override {
            return (addr==0xd012 or addr==0xd013);
        }

        void update() override {
            if (timer) {
                timer--;
                if (timer==0) {
                    ready = true;
                }
            }
        }
};