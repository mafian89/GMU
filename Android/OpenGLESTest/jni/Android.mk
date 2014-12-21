LOCAL_PATH := $(call my-dir)
 
include $(CLEAR_VARS)
 
LOCAL_MODULE    := testNativeRenderer
LOCAL_CFLAGS    := -Wall -Wextra
LOCAL_SRC_FILES := \
	Renderer.c \
	logic.cpp \
	FileUtils.cpp
LOCAL_LDLIBS := -lGLESv2 -landroid
 
include $(BUILD_SHARED_LIBRARY)