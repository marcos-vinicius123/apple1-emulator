#include <filesystem>
#include <ncurses.h>
#include "mos_6502.h"
#include "rom.h"

int main(int, char**){
    initscr();
    noecho();
    cbreak();
    nodelay(stdscr, TRUE);   // non-blocking input
    keypad(stdscr, TRUE);

    printw(std::filesystem::current_path().c_str());
    refresh();
    
    Mos6502 mos6502 = Mos6502();
    Rom rom = Rom();
    rom.load_file("roms/wozmon.bin", 0xff00);
    mos6502.reset(rom);

    int ch;
    while (ch!='q') {
        mos6502.step(rom);
        ch = getch();
        napms(10);
        // if (std::cin.get()=='q') {
        //     break;
        // }
    }
    endwin();
}