#include "constants.h"
#include "main.h"
#include <iostream>
#include <random> // For random number generation

// clear the display
void vm::OP_00e0() {
  memset(displayBuffer, 0, sizeof(displayBuffer));
    // for (size_t i = 0; i < DISPLAY_WIDTH * DISPLAY_HEIGHT; ++i) {
    //     displayBuffer[i] = 0;
    // }
}

// pop address from stack
void vm::OP_00ee() {
  if (sp == 0) {
    std::cerr << "stack underflow on RET\n";
    return;
  }
  pc = stack[--sp];
}

void vm::OP_1nnn() {
  pc = nnn;
}

// push current pc onto stack then jump
void vm::OP_2nnn() {
  if (sp >= 16) {
    std::cerr << "stack overflow on CALL\n";
    return;
  }
  stack[sp++] = pc;
  pc = nnn;
    std::cout << "Calling address: " << nnn << "\n";
    std::cout << "stack after CALL: ";
    print_stack();
}

// skip next instruction if Vx == kk
void vm::OP_3xkk() {
  if (v[vx] == kk) {
    pc += 2;
  }
}

// skip next instruction if Vx != kk
void vm::OP_4xkk() {
    if (v[vx] != kk) {
        pc += 2;
    }
}

// skip next instruction if vx = vy;
void vm::OP_5xy0() {
    if (v[vx] == v[vy]) {
        pc += 2;
    }
}

// set Vx = kk
void vm::OP_6xkk() {
    v[vx] = kk;
}

// set Vx += kk
void vm::OP_7xkk() {
    v[vx] += kk;
}

// set Vx = Vy
void vm::OP_8xy0() {
    v[vx] = v[vy];
}

// set Vx = Vx OR Vy
void vm::OP_8xy1() {
    v[vx] = v[vx] | v[vy];
}

// set Vx = Vx AND Vy
void vm::OP_8xy2() {
    v[vx] &= v[vy];
}

// set Vx = Vx XOR Vy
void vm::OP_8xy3() {
    v[vx] ^= v[vy];
}

// set Vx += Vy, set VF = carry
void vm::OP_8xy4() {
    uint16_t sum = uint16_t(v[vx]) + uint16_t(v[vy]);
    v[0xF] = (sum > 0xFF) ? 1 : 0;
    v[vx] = uint8_t(sum & 0xFF);
}

// set Vx -= Vy, set VF = NOT borrow
void vm::OP_8xy5() {
    v[0xF] = (v[vx] > v[vy]) ? 1 : 0;
    v[vx] -= v[vy];
}

// set Vx >>= 1, set VF = LSB before shift
void vm::OP_8xy6() {
    v[0xf] = v[vx] & 0x1;
    v[vx] >>= 1;
}

// set Vx = Vy - Vx, set VF = NOT borrow
void vm::OP_8xy7() {
    v[0xf] = v[vy] > v[vx] ? 1 : 0;
    v[vx] = v[vy] - v[vx];
}

// set Vx <<= 1, set VF = MSB before shift
void vm::OP_8xyE() {
    v[0xf] = v[vx] >> 7;
    v[vx] <<= 1;
}

// skip next instruction if Vx != Vy
void vm::OP_9xy0() {
    if (v[vx] != v[vy]) pc += 2;
}

// set I = nnn
void vm::OP_Annn() {
    i = nnn;
}

// jump to address nnn + V0
void vm::OP_Bnnn() {
    pc = (nnn + v[0x0]);
}

// set Vx = random byte AND kk
void vm::OP_Cxkk() {

    std::random_device rd; 
    // Seed a Mersenne Twister engine with the random device
    std::mt19937 gen(rd()); 
    // Define a uniform integer distribution for the desired range
    std::uniform_int_distribution<> distrib(0, 127); 

    v[vx] = distrib(gen) & kk;
}

// draw sprite
void vm::OP_Dxyn() {
    // read n bytes from I
    v[0xf] = 0;
    uint8_t x = v[vx] % DISPLAY_WIDTH;
    uint8_t y = v[vy] % DISPLAY_HEIGHT;
    for (unsigned int row = 0; row < n; ++row) {
        uint8_t spritebyte = memory[i + row];
        for (int col = 0; col < 8; ++col) {
            // check if the bit at position col is set
            uint8_t spritePixel = spritebyte & (0x80 >> col);
            uint32_t* screenPixel = &displayBuffer[(y + row) * DISPLAY_WIDTH + (x + col)];
            
            if (spritePixel) {
                if (*screenPixel == 0xFFFFFFFF) {
                    v[0xf] = 1;
                }
                *screenPixel ^= 0xFFFFFFFF;
            }
        }
    }
}
// skip next instruction if key with the value of Vx is pressed
void vm::OP_Ex9E() {
    if (key[v[vx]]) {
        pc += 2;
    }
}

// skip next instruction if key with the value of Vx is not pressed
void vm::OP_ExA1() {
    if (!key[v[vx]]) {
        pc += 2;
    }
}

// set Vx = delay timer value
void vm::OP_Fx07() {
    v[vx] = delay_timer;
}

// wait for a key press, store the value of the key in Vx
void vm::OP_Fx0A() {
    // Wait for a key press
    if (key[0]) {
        v[vx] = 0;
    }
    else if (key[1]) {
        v[vx] = 1;
    }
    else if (key[2]) {
        v[vx] = 2;
    }
    else if (key[3]) {
        v[vx] = 3;
    }
    else if (key[4]) {
        v[vx] = 4;
    }
    else if (key[5]) {
        v[vx] = 5;
    }
    else if (key[6]) {
        v[vx] = 6;
    }
    else if (key[7]) {
        v[vx] = 7;
    }
    else if (key[8]) {
        v[vx] = 8;
    }
    else if (key[9]) {
        v[vx] = 9;
    }
    else if (key[10]) {
        v[vx] = 10;
    }
    else if (key[11]) {
        v[vx] = 11;
    }
    else if (key[12]) {
        v[vx] = 12;
    }
    else if (key[13]) {
        v[vx] = 13;
    }
    else if (key[14]) {
        v[vx] = 14;
    }
    else if (key[15]) {
        v[vx] = 15;
    }
    else {
        // No key pressed, do not advance PC
        pc-=2;
    }
}

// set delay timer = Vx
void vm::OP_Fx15() {
    delay_timer = v[vx];
}

// set sound timer = Vx
void vm::OP_Fx18() {
    sound_timer = v[vx];
}

// set I += Vx
void vm::OP_Fx1E(){
    i += v[vx];
}

// set I = location of sprite for digit Vx
void vm::OP_Fx29() {
    i = FONT_START_ADDRESS + (v[vx] * 5);
}
// store BCD representation of Vx in memory locations I, I+1, and I+2
void vm::OP_Fx33() {
    uint8_t n = v[vx];
    int m = 2;
    while (n >= 0) {
        memory[i+m] = n % 10;
        n /= 10;
        m--;
    }
}

// store registers V0 through Vx in memory starting  at location I
void vm::OP_Fx55() {
    for (int m = 0; m <= vx; m++) {
        memory[i+m] = v[m];
    }
}
// read registers V0 through Vx from memory starting at location I
void vm::OP_Fx65() {
    for (int m = 0; m <= vx; m++) {
        v[m] = memory[i+m] ;
    }
}
