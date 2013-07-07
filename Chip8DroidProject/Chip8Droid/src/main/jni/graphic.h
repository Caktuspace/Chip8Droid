#ifndef _GRAPHIC_H_
#define _GRAPHIC_H_

// Display size
#define SCREEN_WIDTH 64
#define SCREEN_HEIGHT 32

void display(void);
void reshape_window(GLsizei w, GLsizei h);

// Use new drawing method
char screenData[SCREEN_HEIGHT][SCREEN_WIDTH][3];

int Draw_flag;

void setupGraphic(void);
void drawGraphic(void);
void updateQuads(void);
void drawPixel(int x, int y, float rgb);

#endif
