#include "header.h"

void chip8_reset(void)
{
	int i = 0;
	int j = 0;
	unsigned int iseed = (unsigned int)time(NULL);
	srand (iseed);
	memset(&Chip8_cpu, 0, sizeof(Chip8_cpu));
	memset(Chip8_keyboard, 0, sizeof(Chip8_keyboard));
	memset(Chip8_display, 0, sizeof(Chip8_display));

	Chip8_cpu.reg_SP = 0x0;
	Chip8_cpu.reg_PC = 0x200;
	Chip8_cpu.reg_I = 0;
	Draw_flag = 1;

	Memory[0] = 0xF0;
	Memory[1] = 0x90;
	Memory[2] = 0x90;
	Memory[3] = 0x90;
	Memory[4] = 0xF0;

	Memory[5] = 0x20;
	Memory[6] = 0x60;
	Memory[7] = 0x20;
	Memory[8] = 0x20;
	Memory[9] = 0x70;

	Memory[10] = 0xF0;
	Memory[11] = 0x10;
	Memory[12] = 0xF0;
	Memory[13] = 0x80;
	Memory[14] = 0xF0;

	Memory[15] = 0xF0;
	Memory[16] = 0x10;
	Memory[17] = 0xF0;
	Memory[18] = 0x10;
	Memory[19] = 0xF0;

	Memory[20] = 0x90;
	Memory[21] = 0x90;
	Memory[22] = 0xF0;
	Memory[23] = 0x10;
	Memory[24] = 0x10;

	Memory[25] = 0xF0;
	Memory[26] = 0x80;
	Memory[27] = 0xF0;
	Memory[28] = 0x10;
	Memory[29] = 0xF0;

	Memory[30] = 0xF0;
	Memory[31] = 0x80;
	Memory[32] = 0xF0;
	Memory[33] = 0x90;
	Memory[34] = 0xF0;

	Memory[35] = 0xF0;
	Memory[36] = 0x10;
	Memory[37] = 0x20;
	Memory[38] = 0x40;
	Memory[39] = 0x40;

	Memory[40] = 0xF0;
	Memory[41] = 0x90;
	Memory[42] = 0xF0;
	Memory[43] = 0x90;
	Memory[44] = 0xF0;

	Memory[45] = 0xF0;
	Memory[46] = 0x90;
	Memory[47] = 0xF0;
	Memory[48] = 0x10;
	Memory[49] = 0xF0;

	Memory[50] = 0xF0;
	Memory[51] = 0x90;
	Memory[52] = 0xF0;
	Memory[53] = 0x90;
	Memory[54] = 0x90;

	Memory[55] = 0xE0;
	Memory[56] = 0x90;
	Memory[57] = 0xE0;
	Memory[58] = 0x90;
	Memory[59] = 0xE0;

	Memory[60] = 0xF0;
	Memory[61] = 0x80;
	Memory[62] = 0x80;
	Memory[63] = 0x80;
	Memory[64] = 0xF0;

	Memory[65] = 0xE0;
	Memory[66] = 0x90;
	Memory[67] = 0x90;
	Memory[68] = 0x90;
	Memory[69] = 0xE0;

	Memory[70] = 0xF0;
	Memory[71] = 0x80;
	Memory[72] = 0xF0;
	Memory[73] = 0x80;
	Memory[74] = 0xF0;

	Memory[75] = 0xF0;
	Memory[76] = 0x80;
	Memory[77] = 0xF0;
	Memory[78] = 0x80;
	Memory[79] = 0x80;
}

void chip8_loadGame(const char* gameName)
{
	int i = 0x200;
	FILE* file;
	unsigned char buffer;
	
	file = fopen(gameName, "rb");
	// printf("loading the game\n");
	while (fread(&buffer, sizeof(unsigned char), 1, file) > 0)
	{
		Memory[i] = buffer;
		++i;
	}
	// printf("Game loaded\n");
}

void execute(void)
{
	unsigned short opcode = (Memory[Chip8_cpu.reg_PC] << 8) | Memory[Chip8_cpu.reg_PC + 1];

	// printf("executing an instruction : PC = %d\n", Chip8_cpu.reg_PC);
	switch ((opcode & 0xF000) >> 12)
	{
	case 0x0:
		if ((opcode & 0x00FF) == 0xE0)
		{
			// printf("clear_screen\n");
			clear_screen();
			Draw_flag = 1;
			Chip8_cpu.reg_PC += 2;
		}
		else if ((opcode & 0x00FF) == 0xEE)
		{
			// printf("ret\n");
			ret();
			Chip8_cpu.reg_PC += 2;
		}
		else
		{
			// printf("sys_addr : addr = %d\n", (opcode & 0x0FFF));
			sys_addr((opcode & 0x0FFF));
		}
		break;
	case 0x1:
		// printf("jump\n");
		jump((opcode & 0x0FFF));
		break;
	case 0x2:
		// printf("call\n");
		call((opcode & 0x0FFF));
		break;
	case 0x3:
		// printf("se\n");
		se((opcode & 0x0F00) >> 8, (opcode & 0x00FF));
		Chip8_cpu.reg_PC += 2;
		break;
	case 0x4:
		// printf("sne\n");
		sne((opcode & 0x0F00) >> 8, (opcode & 0x00FF));
		Chip8_cpu.reg_PC += 2;
		break;
	case 0x5:
		// printf("se2\n");
		se2((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
		Chip8_cpu.reg_PC += 2;
		break;
	case 0x6:
		// printf("ld\n");
		ld((opcode & 0x0F00) >> 8, (opcode & 0x00FF));
		Chip8_cpu.reg_PC += 2;
		break;
	case 0x7:
		// printf("add\n");
		add((opcode & 0x0F00) >> 8, (opcode & 0x00FF));
		Chip8_cpu.reg_PC += 2;
		break;
	case 0x8:
		switch (opcode & 0x000F)
		{
		case 0x0:
			// printf("ld2\n");
			ld2((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0x1:
			// printf("or\n");
			or((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0x2:
			// printf("and\n");
			and((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0x3:
			// printf("xor\n");
			xor((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0x4:
			// printf("add2\n");
			add2((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0x5:
			// printf("sub\n");
			sub((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0x6:
			// printf("shr\n");
			shr((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0x7:
			// printf("subn\n");
			subn((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0xE:
			// printf("shl\n");
			shl((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
			Chip8_cpu.reg_PC += 2;
			break;
		}
		break;
	case 0x9:
		// printf("sne2\n");
		sne2((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4);
		Chip8_cpu.reg_PC += 2;
		break;
	case 0xA:
		// printf("ld_I\n");
		ld_I((opcode & 0x0FFF));
		Chip8_cpu.reg_PC += 2;
		break;
	case 0xB:
		// printf("jp_v0\n");
		jp_v0((opcode & 0x0FFF));
		Chip8_cpu.reg_PC += 2;
		break;
	case 0xC:
		// printf("rnd\n");
		rnd((opcode & 0x0F00) >> 8, (opcode & 0x00FF));
		Chip8_cpu.reg_PC += 2;
		break;
	case 0xD:
		// printf("drw\n");
		drw((opcode & 0x0F00) >> 8, (opcode & 0x00F0) >> 4, (opcode & 0x000F));
		Draw_flag = 1;
		Chip8_cpu.reg_PC += 2;
		break;
	case 0xE:
		// printf("skp sknp\n");
		if ((opcode & 0x00FF) == 0x9E)
			skp((opcode & 0x0F00) >> 8);
		else if ((opcode & 0x00FF) == 0xA1)
			sknp((opcode & 0x0F00) >> 8);
		Chip8_cpu.reg_PC += 2;
		break;
	case 0xF:
		switch ((opcode & 0x00FF))
		{
		case 0x07:
			// printf("ld_vx_dt\n");
			ld_vx_dt((opcode & 0x0F00) >> 8);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0x0A:
			// printf("ld_vx_k\n");
			ld_vx_k((opcode & 0x0F00) >> 8);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0x15:
			// printf("ld_dt\n");
			ld_dt((opcode & 0x0F00) >> 8);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0x18:
			// printf("ld_st\n");
			ld_st((opcode & 0x0F00) >> 8);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0x1E:
			// printf("add_i\n");
			add_i((opcode & 0x0F00) >> 8);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0x29:
			// printf("ld_f\n");
			ld_f((opcode & 0x0F00) >> 8);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0x33:
			// printf("ld_b\n");
			ld_b((opcode & 0x0F00) >> 8);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0x55:
			// printf("ld_store\n");
			ld_store((opcode & 0x0F00) >> 8);
			Chip8_cpu.reg_PC += 2;
			break;
		case 0x65:
			// printf("ld_read\n");
			ld_read((opcode & 0x0F00) >> 8);
			Chip8_cpu.reg_PC += 2;
			break;
		}
		break;
	default:
		printf("unknown instruction\n");
	}
	if (Chip8_cpu.delay > 0)
		--Chip8_cpu.delay;
	if (Chip8_cpu.sound > 0)
	{
		--Chip8_cpu.sound;
	}
	// printf("instruction executed\n");
}
