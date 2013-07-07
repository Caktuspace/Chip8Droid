#ifndef _MEMORY_H_
#define _MEMORY_H_

static unsigned char Memory[4096];

#define START_ADDRESS 0x200
#define STOP_ADDRESS  0xfff

#define read_mem(addr)		(Memory[(addr) & 4095])
#define write_mem(addr,val)	(Memory[(addr) & 4095] = (val))

#endif /* _MEMORY_H_ */