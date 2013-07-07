#include "header.h"

int gAppAlive = 1;

static int sWindowWidth = 320;
static int sWindowHeight = 480;
static int sDemoStopped = 0;
static int initialized = 0;

/* Call to initialize the graphics state */
void Java_com_chip8_emulator_Chip8Renderer_nativeInit(JNIEnv* env,
		jobject thiz, jstring filename) {
	if (initialized == 0) {
		const char *str1 = (*env)->GetStringUTFChars(env, filename, 0);
		__android_log_print(ANDROID_LOG_INFO, "Chip8Emulator",
				"load rom path/name : %s", str1);
		__android_log_print(ANDROID_LOG_INFO, "Chip8Emulator", "reset");
		chip8_reset();
		__android_log_print(ANDROID_LOG_INFO, "Chip8Emulator", "load game",
				str1);
		chip8_loadGame(str1);
		gAppAlive = 1;
		sDemoStopped = 0;
		initialized = 1;
	}
}

void Java_com_chip8_emulator_Chip8Renderer_nativeInitGL(JNIEnv* env) {
	__android_log_print(ANDROID_LOG_INFO, "Chip8Emulator", "setup graphic");
	setupGraphic();
}

void Java_com_chip8_emulator_Chip8GLSurfaceView_nativePlayGame(JNIEnv* env) {
	__android_log_print(ANDROID_LOG_INFO, "Chip8Emulator", "play game");
	execute();
}

void Java_com_chip8_emulator_Chip8Renderer_nativeResize(JNIEnv* env,
		jobject thiz, jint w, jint h) {
	sWindowWidth = w;
	sWindowHeight = h;
	__android_log_print(ANDROID_LOG_INFO, "Chip8Emulator", "resize w=%d h=%d",
			w, h);
	reshape_window(sWindowWidth, sWindowHeight);
}

/* This is called to indicate to the render loop that it should
 * stop as soon as possible.
 */
void Java_com_chip8_emulator_Chip8GLSurfaceView_nativePause(JNIEnv* env) {
	__android_log_print(ANDROID_LOG_INFO, "Chip8Emulator", "pause");
	sDemoStopped = !sDemoStopped;
}

/* Call to render the next GL frame */
void Java_com_chip8_emulator_Chip8Renderer_nativeRender(JNIEnv* env) {
	if (Draw_flag == 1) {
		__android_log_print(ANDROID_LOG_INFO, "Chip8Emulator", "render");
		// Clear framebuffer
		glClear(GL_COLOR_BUFFER_BIT);
		updateQuads();

		// Processed frame
		Draw_flag = 0;
	}
}
