#include "header.h"

void keyboardDown(unsigned char key, int x, int y)
{
	if(key == 27)    // esc
		exit(0);

	if(key == '&')		Chip8_keyboard[0x1] = 1;
	else if(key == 'é')	Chip8_keyboard[0x2] = 1;
	else if(key == '"')	Chip8_keyboard[0x3] = 1;
	else if(key == '\'')	Chip8_keyboard[0xC] = 1;

	else if(key == 'a')	Chip8_keyboard[0x4] = 1;
	else if(key == 'z')	Chip8_keyboard[0x5] = 1;
	else if(key == 'e')	Chip8_keyboard[0x6] = 1;
	else if(key == 'r')	Chip8_keyboard[0xD] = 1;

	else if(key == 'q')	Chip8_keyboard[0x7] = 1;
	else if(key == 's')	Chip8_keyboard[0x8] = 1;
	else if(key == 'd')	Chip8_keyboard[0x9] = 1;
	else if(key == 'f')	Chip8_keyboard[0xE] = 1;

	else if(key == 'w')	Chip8_keyboard[0xA] = 1;
	else if(key == 'x')	Chip8_keyboard[0x0] = 1;
	else if(key == 'c')	Chip8_keyboard[0xB] = 1;
	else if(key == 'v')	Chip8_keyboard[0xF] = 1;

	//printf("Press key %c\n", key);
}

void keyboardUp(unsigned char key, int x, int y)
{
	if(key == '&')		Chip8_keyboard[0x1] = 0;
	else if(key == 'é')	Chip8_keyboard[0x2] = 0;
	else if(key == '"')	Chip8_keyboard[0x3] = 0;
	else if(key == '\'')	Chip8_keyboard[0xC] = 0;

	else if(key == 'a')	Chip8_keyboard[0x4] = 0;
	else if(key == 'z')	Chip8_keyboard[0x5] = 0;
	else if(key == 'e')	Chip8_keyboard[0x6] = 0;
	else if(key == 'r')	Chip8_keyboard[0xD] = 0;

	else if(key == 'q')	Chip8_keyboard[0x7] = 0;
	else if(key == 's')	Chip8_keyboard[0x8] = 0;
	else if(key == 'd')	Chip8_keyboard[0x9] = 0;
	else if(key == 'f')	Chip8_keyboard[0xE] = 0;

	else if(key == 'w')	Chip8_keyboard[0xA] = 0;
	else if(key == 'x')	Chip8_keyboard[0x0] = 0;
	else if(key == 'c')	Chip8_keyboard[0xB] = 0;
	else if(key == 'v')	Chip8_keyboard[0xF] = 0;
}