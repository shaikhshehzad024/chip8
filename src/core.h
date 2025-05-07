#include <cstdint>
using namespace std;
class Chip8 {
public:
  uint8_t memory[4096];
  uint8_t reg[16]; // 1 byte each
  uint16_t index;  // AKA I
  uint16_t pc;     // program counter
  uint16_t stack[16];
  uint8_t sp; // stack pointer
  uint8_t sound_timer;
  uint8_t delay_timer;
  uint8_t keypad[16];
  uint32_t videobuffer[64 * 32];
  uint16_t opcode;

public:
  void LoadROM(const char *filename);
  //fetch
  //decode
  //execute
};
