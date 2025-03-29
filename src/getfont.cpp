#include <fstream>
#include <iostream>
#include <vector>
std::vector<uint8_t> getfont() {
  std::ifstream fontfile("fontset.txt");
  if (!fontfile) {
    std::cout << "Error opening file" << std::endl;
    return {};
  }
  std::vector<uint8_t> fontset;
  char bits[4];
  char ch;
  int count = 0;
  while (fontfile.get(ch)) {
    if (ch == '\n') {
      count = 0;
      continue;
    }
    if (ch == '0' || ch == '1') {
      bits[count++] = ch;
      if (count == 4) {
        uint8_t number = ((bits[0] & 1) << 3) | ((bits[1] & 1) << 2) |
                         ((bits[2] & 1) << 1) | ((bits[3] & 1) << 0);
        number *= 10;
        std::cout << static_cast<int>(number) << std::endl;
        fontset.push_back(number);
        count = 0;
      }
    }
  }
  return fontset;
}
