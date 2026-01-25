#include <filesystem>
#include <ncurses.h>
#include "mos_6502.h"
#include "rom.h"
#include "display.cpp"
#include "device_manager.h"

int main(int, char**){
    initscr();
    resizeterm(24, 40);
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);   // non-blocking input
    keypad(stdscr, TRUE);
    scrollok(stdscr, FALSE);
    
    Mos6502 mos6502 = Mos6502();
    Rom rom = Rom();
    rom.load_file("roms/wozmon.bin", 0xff00);
    mos6502.reset(rom);

    Display display;
    device_manager.add_device(&display);

    int ch;
    while (ch!=KEY_BACKSPACE) {
        mos6502.step(rom);
        ch = getch();
        device_manager.update_devices();
        napms(10);
        // if (std::cin.get()=='q') {
        //     break;
        // }
    }
    endwin();
}