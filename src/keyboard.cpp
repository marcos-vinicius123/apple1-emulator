#include "device.h"
#include <ncurses.h>

class Keyboard : public Device {
    private:

        int line_count = 0;
        bool ready = true;
        int timer = 0;
        int ch;
        bool has_key = false;
    
    public:
        uint8_t read(uint16_t addr) override {
            if (addr==0xd010) {
                has_key = false;
                return ch | 0x80;
            } else {
                return 0x80*has_key;
            }
        }

        void write(uint16_t addr, uint8_t value) override {

        }

        bool handles_addr(uint16_t addr) override {
            return (addr==0xd010 or addr==0xd011);
        }

        void update() override {
            int character = getch();

            if (character!=ERR) {
                if (character>='a' and character<='z') {
                    ch = character-'a'+'A';
                } else if (character == KEY_ENTER or character == '\n') {
                    ch = 0x0d;
                }else if (character == KEY_BACKSPACE) {
                    stop = true;
                } else {
                    ch = character;
                }
                has_key = true;
            }
        }

        bool stop = false;
};