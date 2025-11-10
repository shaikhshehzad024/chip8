#include "main.h"

vm_result vm::vm_interpret(const uint8_t *program, size_t size) {
  // load program once
  load_program(program, size);
  while (true) {
    if (pc + 1 >= sizeof(memory)) {
      return ERROR_INVALID_OPCODE;
    }

    uint16_t instruction = (uint16_t(memory[pc]) << 8) | uint16_t(memory[pc + 1]);
    uint8_t vx = (instruction & 0x0F00) >> 8;
    uint8_t vy = (instruction & 0x00F0) >> 4;
    uint8_t kk = instruction & 0x00FF;
    uint8_t n = instruction & 0x000F;
    switch (instruction & 0xf000) {
    case 0x0000: {
      switch (instruction) {
      case 0x00ee:
        OP_00ee();
        break;
      default:
        return ERROR_INVALID_OPCODE;
      }
    }
    case 0x1000:
      OP_1nnn(instruction & 0x0fff);
      break;
    case 0x2000:
      OP_2nnn(instruction & 0x0fff);
      break;
    case 0x3000:
      OP_3xkk(vx, kk); // skip next instruction if Vx == kk
      break;
    case 0x4000:
      OP_4xkk(vx, kk); // skip next instruction if Vx != kk
      break;
    case 0x5000:
      OP_5xy0(vx, vy); // skip next instruction if vx = vy;
      break;
    case 0x6000:
      OP_6xkk(vx, kk); // set Vx = kk
      break;
    case 0x7000:
      OP_7xkk(vx, kk); // set Vx += kk
      break;
    case 0x8000: {
      switch (instruction) {
        case 0x0001:
          OP_8xy1(vx, vy); // set Vx = Vx OR Vy
          break;
        case 0x0002:
          OP_8xy2(vx, vy); // set Vx = Vx AND Vy
          break;
        case 0x0003:
          OP_8xy3(vx, vy); // set Vx = Vx XOR Vy
          break;
        case 0x0004:
          OP_8xy4(vx, vy); // set Vx += Vy, set VF = carry
          break;
        case 0x0005:
          OP_8xy5(vx, vy); // set Vx -= Vy, set VF = NOT borrow
          break;
        case 0x0006:
          OP_8xy6(vx);              // set Vx >>= 1, set VF = LSB before shift
          break;
        case 0x0007:
          OP_8xy7(vx, vy); // set Vx = Vy - Vx, set VF = NOT borrow
          break;
        case 0x000E:
          OP_8xyE(vx);              // set Vx <<= 1, set VF = MSB before shift
          break;
        default:
          return ERROR_INVALID_OPCODE;
      }
      break;
      case 0x9000:
        OP_9xy0(vx, vy); // skip next instruction if Vx != Vy
        break;
      case 0xA000:
        OP_Annn(instruction & 0x0FFF); // set I = nnn
        break;
      case 0xB000:
        OP_Bnnn(instruction & 0x0FFF);       // jump to address nnn + V0
        break;
      case 0xC000:
        OP_Cxkk(vx, kk); // set Vx = random byte AND kk
        break;
      case 0xD000:
        // void OP_Dxyn(uint8_t r_x, uint8_t r_y, uint8_t nibble); // draw sprite
        break;
      case 0xE000: {
        switch (instruction & 0x00FF) {
          case 0x009E:
            // void OP_Ex9E(uint8_t r_x);       // skip next instruction if key with the value of Vx is pressed
            break;
          case 0x00A1:
            // void OP_ExA1(uint8_t r_x);       // skip next instruction if key with the value of Vx is not pressed
            break;
          default:
            return ERROR_INVALID_OPCODE;
        }
      }
      break;
      case 0xF000:
        switch (instruction & 0x00FF)
        {
        case 0x0007:
          OP_Fx07(vx); // set Vx = delay timer value
          break;
        case 0x000A:
          // void OP_Fx0A(uint8_t r_x);       // wait for a key press, store the value of the key in Vx
          break;
        case 0x0015:
          OP_Fx15(vx); // set delay timer = Vx
          break;
        case 0x0018:
          OP_Fx18(vx); // set sound timer = Vx
          break;
        case 0x001E:
          OP_Fx1E(vx); // set I += Vx
          break;
        case 0x0029:
          // void OP_Fx29(uint8_t r_x);       // set I = location of sprite for digit Vx
          break;
        case 0x0033:
          OP_Fx33(vx); // store BCD representation of Vx in memory locations I, I+1, and I+2
        case 0x0055:
          OP_Fx55(vx); // store registers V0 through Vx in memory starting  at location I
          break;
        case 0x0065:
          OP_Fx65(vx); // read registers V0 through Vx from memory starting at location I
          break;
        default:
          return ERROR_INVALID_OPCODE;
        }
    }
    default:
      return ERROR_INVALID_OPCODE;
    }
    pc += 2;
  }
  return SUCCESS;
}