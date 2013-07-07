#ifndef _REGISTER_H_
#define _REGISTER_H_

typedef struct
{
	unsigned char	reg_V[16];
	int		reg_I : 16;
	unsigned char	delay;
	unsigned char 	sound;
	int		reg_PC : 16;
	int		reg_SP : 16;
}	registers;

registers Chip8_cpu;
unsigned short Chip8_pile[16];

#endif /* _REGISTER_H_ */