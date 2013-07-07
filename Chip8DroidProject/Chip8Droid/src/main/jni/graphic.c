#include "header.h"

float modifier_width = 15;
float modifier_height = 12.5;

// Window size
int display_width = 800;
int display_height = 480;

void setupGraphic() {

	// Setup OpenGL        
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	//glClearColor(1,1,1,1);
	glClearColor(0.4f, 0.4f, 0.4f, 1);
	glColor4f(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
}

void reshape_window(GLsizei w, GLsizei h) {
	glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(0, w, h, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, w, h);

	// Resize quad
	display_width = w;
	modifier_width = (float) w / (float) SCREEN_WIDTH;
	display_height = h;
	modifier_height  = (float) h / (float) SCREEN_HEIGHT;
}

void drawPixel(int x, int y, float rgb)
{
	GLfloat vertexCoord[9] = {
			(x * modifier_width) + modifier_width, (y * modifier_height) + 0.0f, 0.0,
			(x * modifier_width) + 0.0f, (y * modifier_height) + 0.0f, 0.0,
			(x * modifier_width) + 0.0f, (y * modifier_height) + modifier_height, 0.0,
	};
	GLfloat vertexCoord2[9] = {
			(x * modifier_width) + modifier_width, (y * modifier_height) + 0.0f, 0.0,
			(x * modifier_width) + modifier_width, (y * modifier_height) + modifier_height, 0.0,
			(x * modifier_width) + 0.0f, (y * modifier_height) + modifier_height, 0.0,
		};
	GLfloat colorCoord[12] = {
				rgb, rgb, rgb, 1.0,
				rgb, rgb, rgb, 1.0,
				rgb, rgb, rgb, 1.0,
		};

	glVertexPointer(3, GL_FLOAT, 0, vertexCoord);
	glColorPointer(4, GL_FLOAT, 0, colorCoord);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glVertexPointer(3, GL_FLOAT, 0, vertexCoord2);
	glColorPointer(4, GL_FLOAT, 0, colorCoord);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

void updateQuads (void)
{
	int y = 0;
	int x = 0;
	// Draw
	for (y = 0; y < 32; ++y)
		for (x = 0; x < 64; ++x)
		{
			if(Chip8_display[x][y] == 0)
				drawPixel(x, y, 0);
			else
				drawPixel(x, y, 1);

		}
}
