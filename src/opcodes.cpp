#include "main.h"
#include <iostream>
#include <random> // For random number generation

void vm::OP_00ee() {
  if (sp == 0) {
    std::cerr << "stack underflow on RET\n";
    return;
  }
  // pop address from stack
  pc = stack[--sp];
  std::cout << "Returning to address: " << pc << "\n";
  std::cout << "stack after RET: ";
}

void vm::OP_1nnn(uint16_t address) {
  pc = address;
}

void vm::OP_2nnn(uint16_t address) {
  if (sp >= 16) {
    std::cerr << "stack overflow on CALL\n";
    return;
  }
  // push current pc onto stack then jump
  stack[sp++] = pc;
  pc = address;
    std::cout << "Calling address: " << address << "\n";
    std::cout << "stack after CALL: ";
    print_stack();
}

void vm::OP_3xkk(uint8_t r_x, uint8_t byte) {
  if (v[r_x] == byte) {
    pc += 2;
  }
}

void vm::OP_4xkk(uint8_t r_x, uint8_t byte) {
    if (v[r_x] !=byte) {
        pc += 2;
    }
}

// skip next instruction if vx = vy;
void vm::OP_5xy0(uint8_t r_x, uint8_t r_y) {
    if (v[r_x] == v[r_y]) {
        pc += 2;
    }
}

// set Vx = kk
void vm::OP_6xkk(uint8_t r_x, uint8_t byte) {
    v[r_x] = byte;
}

// set Vx += kk
void vm::OP_7xkk(uint8_t r_x, uint8_t byte) {
    v[r_x] += byte;
}

// set Vx = Vy
void vm::OP_8xy0(uint8_t r_x, uint8_t r_y) {
    v[r_x] = v[r_y];
}

// set Vx = Vx OR Vy
void vm::OP_8xy1(uint8_t r_x, uint8_t r_y) {
    v[r_x] = v[r_x] | v[r_y];
}

// set Vx = Vx AND Vy
void vm::OP_8xy2(uint8_t r_x, uint8_t r_y) {
    v[r_x] &= v[r_y];
}

// set Vx = Vx XOR Vy
void vm::OP_8xy3(uint8_t r_x, uint8_t r_y) {
    v[r_x] ^= v[r_y];
}

// set Vx += Vy, set VF = carry
void vm::OP_8xy4(uint8_t r_x, uint8_t r_y) {
    uint16_t sum = uint16_t(v[r_x]) + uint16_t(v[r_y]);
    v[0xF] = (sum > 0xFF) ? 1 : 0;
    v[r_x] = uint8_t(sum & 0xFF);
}

// set Vx -= Vy, set VF = NOT borrow
void vm::OP_8xy5(uint8_t r_x, uint8_t r_y) {
    v[0xF] = (v[r_x] > v[r_y]) ? 1 : 0;
    v[r_x] -= v[r_y];
}

// set Vx >>= 1, set VF = LSB before shift
void vm::OP_8xy6(uint8_t r_x) {
    v[0xf] = v[r_x] & 0x1;
    v[r_x] >>= 1;
}

// set Vx = Vy - Vx, set VF = NOT borrow
void vm::OP_8xy7(uint8_t r_x, uint8_t r_y) {
    v[0xf] = v[r_y] > v[r_x] ? 1 : 0;
    v[r_x] = v[r_y] - v[r_x];
}

// set Vx <<= 1, set VF = MSB before shift
void vm::OP_8xyE(uint8_t r_x) {
    v[0xf] = v[r_x] >> 7;
    v[r_x] <<= 1;
}

// skip next instruction if Vx != Vy
void vm::OP_9xy0(uint8_t r_x, uint8_t r_y) {
    if (v[r_x] != v[r_y]) pc += 2;
}

// set I = nnn
void vm::OP_Annn(uint16_t address) {
    i = address;
}

// jump to address nnn + V0
void vm::OP_Bnnn(uint16_t address) {
    pc = (address + v[0x0]);
}

// set Vx = random byte AND kk
void vm::OP_Cxkk(uint8_t r_x, uint8_t byte) {

    std::random_device rd; 
    // Seed a Mersenne Twister engine with the random device
    std::mt19937 gen(rd()); 
    // Define a uniform integer distribution for the desired range
    std::uniform_int_distribution<> distrib(0, 127); 

    v[r_x] = distrib(gen) & byte;
}

// draw sprite
// void vm::OP_Dxyn(uint8_t r_x, uint8_t r_y, uint8_t nibble);
// skip next instruction if key with the value of Vx is pressed
// void vm::OP_Ex9E(uint8_t r_x);
// skip next instruction if key with the value of Vx is not pressed
// void vm::OP_ExA1(uint8_t r_x);

// set Vx = delay timer value
void vm::OP_Fx07(uint8_t r_x) {
    v[r_x] = delay_timer;
}

// wait for a key press, store the value of the key in Vx
// void vm::OP_Fx0A(uint8_t r_x);

// set delay timer = Vx
void vm::OP_Fx15(uint8_t r_x) {
    delay_timer = v[r_x];
}

// set sound timer = Vx
void vm::OP_Fx18(uint8_t r_x) {
    sound_timer = v[r_x];
}

// set I += Vx
void vm::OP_Fx1E(uint8_t r_x){
    i += v[r_x];
}

// set I = location of sprite for digit Vx
// void vm::OP_Fx29(uint8_t r_x);
// store BCD representation of Vx in memory locations I, I+1, and I+2
void vm::OP_Fx33(uint8_t r_x) {
    uint8_t n = v[r_x];
    int m = 2;
    while (n > 0) {
        memory[i+m] = n % 10;
        n /= 10;
        m--;
    }
}

// store registers V0 through Vx in memory starting  at location I
void vm::OP_Fx55(uint8_t r_x) {
    for (int m = 0; m <= r_x; m++) {
        memory[i+m] = v[m];
    }
}
// read registers V0 through Vx from memory starting at location I
void vm::OP_Fx65(uint8_t r_x) {
    for (int m = 0; m <= r_x; m++) {
        v[m] = memory[i+m] ;
    }
}
