#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>
#include "main.h"
#include "constants.h"

void vm::LoadROM(char const* filename)
{
		std::ifstream file(filename, std::ios::binary | std::ios::ate);
		if (!file.is_open()) {
				std::cerr << "LoadROM: failed to open '" << filename << "'\n";
				return;
		}

		std::streamsize size = file.tellg();
		if (size <= 0) {
				std::cerr << "LoadROM: file empty or tellg failed for '" << filename << "'\n";
				return;
		}

		if (static_cast<size_t>(size) > (sizeof(memory) - START_ADDRESS)) {
				std::cerr << "LoadROM: ROM too large to fit in memory (" << size << " bytes)\n";
				return;
		}

		std::vector<uint8_t> buffer(static_cast<size_t>(size));
		file.seekg(0, std::ios::beg);
		if (!file.read(reinterpret_cast<char*>(buffer.data()), size)) {
				std::cerr << "LoadROM: failed to read file '" << filename << "'\n";
				return;
		}
		file.close();

		// Copy into emulator memory at START_ADDRESS
		std::memcpy(&memory[START_ADDRESS], buffer.data(), static_cast<size_t>(size));
		std::cout << "ROM loaded successfully from LoadROM (" << size << " bytes)\n";
}

void vm::load_program(const uint8_t *program, size_t size) {
	if (!program || size == 0) return;
	if (size > (sizeof(memory) - 0x200)) {
		std::cerr << "load_program: program too large (" << size << " bytes)\n";
		return;
	}
	std::memcpy(&memory[0x200], program, size);
	std::cout << "Program loaded successfully from load_program (" << size << " bytes)\n";
}