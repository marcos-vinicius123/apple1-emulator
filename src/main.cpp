#include <filesystem>
#include <ncurses.h>
#include "mos_6502.h"
#include "rom.h"
#include "display.cpp"
#include "keyboard.cpp"
#include "device_manager.h"

int main(int, char**){
    initscr();
    resizeterm(24, 40);
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);   // non-blocking input
    keypad(stdscr, TRUE);
    scrollok(stdscr, FALSE);
    scrollok(stdscr, TRUE);
    mousemask(0, nullptr);
    mouseinterval(0);
    
    Mos6502 mos6502 = Mos6502();
    Rom rom = Rom();
    rom.load_file("roms/wozmon.bin", 0xff00);
    rom.load_file("roms/replica1.bin", 0xe000);
    mos6502.reset(rom);

    Display display;
    Keyboard keyboard;
    device_manager.add_device(&display);
    device_manager.add_device(&keyboard);

    while (!keyboard.stop) {
        for (int i=0; i<1000; i++) {
            mos6502.step(rom);
        }
        device_manager.update_devices();
        napms(10);
        // if (std::cin.get()=='q') {
        //     break;
        // }
    }
    endwin();
}