#include "device.h"
#include <ncurses.h>

class Display : Device {
    private:
        void display_char(uint8_t value) {

            //prepare value
            addch(value);
            line_count++;
            if (line_count==40) {
                addch('\n');
                line_count = 0;
            }
        }

        int line_count = 0;
        bool ready = true;
        int timer = 0;
    
    public:
        uint8_t read(uint16_t addr) override {

        }

        void write(uint16_t addr, uint8_t value) override {
            if (addr==0xd012) {
                display_char(value);
                ready = false;
            }
        }

        bool handles_addr(uint16_t addr) override {
            return (addr==0xd012 or addr==0xd013);
        }

        void update() override {

        }
};