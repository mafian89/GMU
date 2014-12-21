LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)
 
LOCAL_MODULE    := testNativeRenderer
LOCAL_CFLAGS    := -Wall -Wextra
LOCAL_SRC_FILES := \
	Renderer.c \
	logic.cpp \
	FileUtils.cpp \
	ShadersUtils.cpp
LOCAL_LDLIBS := -lGLESv2 -landroid -llog
 
include $(BUILD_SHARED_LIBRARY)