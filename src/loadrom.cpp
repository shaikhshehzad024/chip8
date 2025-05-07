#include "core.h"
#include <fstream>

const unsigned int START_ADDRESS = 0x200;

void Chip8::LoadROM(char const *filename) {
  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  if (file.is_open()) {

    std::streampos size = file.tellg(); // get file size
    char *buffer = new char[size];      // create a buffer with that size

    file.seekg(0, std::ios::beg); // go to beginning of buffer
    file.read(buffer, size);      // fill the buffer
    file.close();

    for (long i = 0; i < size; ++i) {
      memory[START_ADDRESS + i] = buffer[i];
    }
    delete[] buffer;
  }
}
