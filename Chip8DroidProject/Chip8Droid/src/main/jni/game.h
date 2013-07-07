#ifndef _GAME_H_
#define _GAME_H_

int Draw_flag;

void chip8_reset(void);
void chip8_loadGame(const char* gameName);
void execute(void);

void display(void);

#endif