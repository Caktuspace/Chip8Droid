#include "header.h"

void main(int argc,char **argv)
{
//	glutInit(&argc, argv);  
	setupGraphic();

	chip8_reset();
	chip8_loadGame("C:\\Users\\quentin\\Documents\\Visual Studio 2010\\Projects\\tst2\\Debug\\TICTAC");

	display();
//	glutMainLoop();
}

void display()
{
	for (;;)
	{
		execute();
	}
}
