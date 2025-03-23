#include <iostream>
#include <vector>
typedef uint8_t u8;
typedef  uint16_t u16;
using namespace std;
static std::vector<u8>memory(4096);
u8 v[0xf];//1 byte each
u16 index;//AKA I
u16 pc;//program counter
u8 sp;//stack pointer
u8 *PSA = &memory[0x200];//program start address
u8 sound_timer;
u8 delay_timer;
//fontset size = 80 bytes, 4 bits wide, 5 bits high each
vector<u8> fontset=getfont();
int main(){
  std::cout << static_cast<int> fontset;
	return 0;
}
