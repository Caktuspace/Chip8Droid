#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

static __inline void sys_addr(int addr)
{
	Chip8_cpu.reg_PC = addr;
};

static __inline void clear_screen(void)
{
	memset(Chip8_display, 0, sizeof(Chip8_display));
};

static __inline void ret(void)
{
	--Chip8_cpu.reg_SP;
	Chip8_cpu.reg_PC = Chip8_pile[Chip8_cpu.reg_SP];
};

static __inline void jump(int addr)
{
	Chip8_cpu.reg_PC = addr;
};

static __inline void call(int addr)
{
	// printf ("addr = %d, sp = %d, pc = %d\n", addr, Chip8_cpu.reg_SP, Chip8_cpu.reg_PC);
	Chip8_pile[Chip8_cpu.reg_SP] = Chip8_cpu.reg_PC;
	++Chip8_cpu.reg_SP;
	Chip8_cpu.reg_PC = addr;
};

static __inline void se(int vx, unsigned char byte)
{
	if (Chip8_cpu.reg_V[vx] == byte)
		Chip8_cpu.reg_PC += 2;
};

static __inline void sne(int vx, unsigned char byte)
{
	if (Chip8_cpu.reg_V[vx] != byte)
		Chip8_cpu.reg_PC += 2;
};

static __inline void se2(int vx, int vy)
{
	if (Chip8_cpu.reg_V[vx] == Chip8_cpu.reg_V[vy])
		Chip8_cpu.reg_PC += 2;
};

static __inline void ld(int vx, unsigned char byte)
{
	Chip8_cpu.reg_V[vx] = byte;
};

static __inline void add(int vx, unsigned char byte)
{
	Chip8_cpu.reg_V[vx] += byte;
};

static __inline void ld2(int vx, int vy)
{
	Chip8_cpu.reg_V[vx] = Chip8_cpu.reg_V[vy];
};

static __inline void or(int vx, int vy)
{
	Chip8_cpu.reg_V[vx] |= Chip8_cpu.reg_V[vy];
};

static __inline void and(int vx, int vy)
{
	Chip8_cpu.reg_V[vx] &= Chip8_cpu.reg_V[vy];
};

static __inline void xor(int vx, int vy)
{
	Chip8_cpu.reg_V[vx] ^= Chip8_cpu.reg_V[vy];
};

static __inline void add2(int vx, int vy)
{
	Chip8_cpu.reg_V[vx] += Chip8_cpu.reg_V[vy];
	if (Chip8_cpu.reg_V[vx] + Chip8_cpu.reg_V[vy] > 255)
		Chip8_cpu.reg_V[15] = 1;
	else
		Chip8_cpu.reg_V[15] = 0;
};

static __inline void sub(int vx, int vy)
{
	if (Chip8_cpu.reg_V[vx] > Chip8_cpu.reg_V[vy])
		Chip8_cpu.reg_V[15] = 1;
	else
		Chip8_cpu.reg_V[15] = 0;
	Chip8_cpu.reg_V[vx] -= Chip8_cpu.reg_V[vy];
};

static __inline void shr(int vx, int vy)
{
	if ((Chip8_cpu.reg_V[vx] & 0x01) == 1)
		Chip8_cpu.reg_V[15] = 1;
	else
		Chip8_cpu.reg_V[15] = 0;
	Chip8_cpu.reg_V[vx] = Chip8_cpu.reg_V[vx] >> 1;
};

static __inline void subn(int vx, int vy)
{
	if (Chip8_cpu.reg_V[vx] < Chip8_cpu.reg_V[vy])
		Chip8_cpu.reg_V[15] = 1;
	else
		Chip8_cpu.reg_V[15] = 0;
	Chip8_cpu.reg_V[vx] = Chip8_cpu.reg_V[vy] - Chip8_cpu.reg_V[vx];
};

static __inline void shl(int vx, int vy)
{
	if ((Chip8_cpu.reg_V[vx] & 0x80) == 1)
		Chip8_cpu.reg_V[15] = 1;
	else
		Chip8_cpu.reg_V[15] = 0;
	Chip8_cpu.reg_V[vx] = Chip8_cpu.reg_V[vx] << 1;
};

static __inline void sne2(int vx, int vy)
{
	if (Chip8_cpu.reg_V[vx] != Chip8_cpu.reg_V[vy])
		Chip8_cpu.reg_PC += 2;
};

static __inline void ld_I(int addr)
{
	Chip8_cpu.reg_I = addr;
};

static __inline void jp_v0(int addr)
{
	Chip8_cpu.reg_PC = Chip8_cpu.reg_V[0] + addr;
};

static __inline void rnd(int vx, unsigned char byte)
{
	unsigned char random = rand();
	Chip8_cpu.reg_V[vx] = random & byte;
};

static __inline void drw(int vx, int vy, int nibble)
{
	unsigned short x = Chip8_cpu.reg_V[vx];
	unsigned short y = Chip8_cpu.reg_V[vy];
	unsigned short height = nibble;
	unsigned short pixel;
	int yline;
	int xline;

	Chip8_cpu.reg_V[0xF] = 0;
	for (yline = 0; yline < height; yline++)
	{
		pixel = Memory[Chip8_cpu.reg_I + yline];
		for(xline = 0; xline < 8; xline++)
		{
			if((pixel & (0x80 >> xline)) != 0)
			{
				if(Chip8_display[x + xline][y + yline] == 1)
				{
					Chip8_cpu.reg_V[0xF] = 1;                                    
				}
				Chip8_display[x + xline][y + yline] ^= 1;
			}
		}
	}
};

static __inline void skp(int vx)
{
	if (Chip8_keyboard[Chip8_cpu.reg_V[vx]] == 1)
		Chip8_cpu.reg_PC += 2;
};

static __inline void sknp(int vx)
{
	if (Chip8_keyboard[Chip8_cpu.reg_V[vx]] == 0)
		Chip8_cpu.reg_PC += 2;
};

static __inline void ld_vx_dt(int vx)
{
	Chip8_cpu.reg_V[vx] = Chip8_cpu.delay;
};

static __inline void ld_vx_k(int vx)
{
	Chip8_cpu.reg_V[vx] = getchar();
};

static __inline void ld_dt(int vx)
{
	Chip8_cpu.delay = Chip8_cpu.reg_V[vx];
};

static __inline void ld_st(int vx)
{
	Chip8_cpu.sound = Chip8_cpu.reg_V[vx];
};

static __inline void add_i(int vx)
{
	Chip8_cpu.reg_I += Chip8_cpu.reg_V[vx];
};

static __inline void ld_f(int vx)
{
	Chip8_cpu.reg_I = Chip8_cpu.reg_V[vx] * 5;
};

static __inline void ld_b(int vx)
{
	Memory[Chip8_cpu.reg_I] = Chip8_cpu.reg_V[vx] / 100;
	Memory[Chip8_cpu.reg_I + 1] = (Chip8_cpu.reg_V[vx] / 10) % 10;
	Memory[Chip8_cpu.reg_I + 2] = Chip8_cpu.reg_V[vx] % 10;
};

static __inline void ld_store(int vx)
{
	int i;
	for (i = 0; i <= vx; ++i, Chip8_cpu.reg_I += sizeof(unsigned char))
	{
		write_mem(Chip8_cpu.reg_I, Chip8_cpu.reg_V[i]);
	}
};

static __inline void ld_read(int vx)
{
	int i;
	for (i = 0; i <= vx; ++i, Chip8_cpu.reg_I += sizeof(unsigned char))
	{
		Chip8_cpu.reg_V[i] = read_mem(Chip8_cpu.reg_I);
	}
};
#endif /* _INSTRUCTION_H_ */