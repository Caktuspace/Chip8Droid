LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := Chip8

LOCAL_CFLAGS := -DANDROID_NDK

LOCAL_SRC_FILES := \
    game.c \
	graphic.c \
    input.c \
    app-android.c \
    

LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog

include $(BUILD_SHARED_LIBRARY)
