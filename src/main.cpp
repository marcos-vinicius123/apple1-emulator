#include <iostream>
#include <filesystem>
#include "mos_6502.h"
#include "rom.h"

int main(int, char**){
    std::cout << std::filesystem::current_path() << "\n";
    Mos6502 mos6502 = Mos6502();
    Rom rom = Rom();
    rom.load_file("roms/wozmon.bin", 0xff00);
    mos6502.reset(rom);

    char input;
    while (input!='q') {
        mos6502.step(rom);
        // if (std::cin.get()=='q') {
        //     break;
        // }
    }
}