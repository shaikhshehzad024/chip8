#include <unordered_map>
#include <cstdint>
#include <string>
#include <unordered_map>

#include "main.h"

using std::string;

std::unordered_map<string, uint8_t> keyMap = {
    {"1", 0x1},
    {"2", 0x2},
    {"3", 0x3},
    {"4", 0xC},
    {"q", 0x4},
    {"w", 0x5},
    {"e", 0x6},
    {"r", 0xD},
    {"a", 0x7},
    {"s", 0x8},
    {"d", 0x9},
    {"f", 0xE},
    {"z", 0xA},
    {"x", 0x0},
    {"c", 0xB},
    {"v", 0xF}
};

void vm::setKey(int index, bool pressed) {
  if (index >= 0 && index < 16)
    key[index] = pressed ? 1 : 0;
}