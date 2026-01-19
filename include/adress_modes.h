#pragma once

enum Adress_modes {
    accumulator,
    absolute,
    absolute_x,
    absolute_y,
    immediate,
    implied,
    indirect,
    x_indirect,
    y_indirect,
    relative,
    zero_page,
    zero_page_x,
    zero_page_y
};

//receives a adress mode and returns how much to increment the program counter.
inline int addr_mode_to_bytes(Adress_modes mode) {
    switch (mode)
    {
    case Adress_modes::accumulator:
        return 1;
        break;
    
    case Adress_modes::absolute:
        return 3;
        break;
    
    case Adress_modes::absolute_x:
        return 3;
        break;
    
    case Adress_modes::absolute_y:
        return 3;
        break;
    
    case Adress_modes::immediate:
        return 2;
        break;
    
    case Adress_modes::implied:
        return 1;
        break;
    
    case Adress_modes::indirect:
        return 2;
        break;
    
    case Adress_modes::x_indirect:
        return 2;
        break;
    
    case Adress_modes::y_indirect:
        return 2;
        break;
    
    case  Adress_modes::relative:
        return 2;
        break;
    
    case Adress_modes::zero_page:
        return 2;
        break;
    
    case Adress_modes::zero_page_x:
        return 2;
        break;

    case Adress_modes::zero_page_y:
        return 2;
        break;

    default:
        return 0;
        break;
    }
}