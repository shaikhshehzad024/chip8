#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
std::vector<uint8_t> getfont() {
  std::ifstream fontfile("fontset.txt");
  if (!fontfile) {
    std::cout << "Error opening file" << std::endl;
    return {};
  }
  std::vector<uint8_t> fontset;
  std::string line;
  while (std::getline(fontfile, line)) {
    if (line.length() == 8) {
      uint8_t value = static_cast<uint8_t>(std::bitset<8>(line).to_ulong());
      fontset.push_back(value);
    }
  }
  fontfile.close();
  return fontset;
}
int main (int argc, char *argv[]) {
  std::vector<uint8_t> font=getfont();
  for(uint8_t i: font){
    std::cout<<(int)i<<std::endl;
  }
  return 0;
}
