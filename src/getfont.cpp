#include <fstream>
#include <iostream>
#include <vector>
std::vector<uint8_t> getfont()
{
	std::ifstream fontfile("fontset.txt");
	if (!fontfile)
	{
		std::cout << "Error opening file" << std::endl;
		return {};
	}
	std::vector<uint8_t> fontset;
	uint8_t chbuf[8];
	uint8_t number;
	char ch;
	int count = 0;
	while (fontfile.get(ch))
	{
		if (ch == '\n')
		{
			count = 0;
			continue;
		}
		while (count < 8)
		{
			
			if (ch == '0' || ch == '1')
			{
				chbuf[count] = (uint8_t) (ch-0);
				count++;
			}
		}
		
	}
return fontset;
}
