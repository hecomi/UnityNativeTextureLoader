TOP_LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

include $(TOP_LOCAL_PATH)/libpng-android/jni/Android.mk
include $(CLEAR_VARS)

LOCAL_PATH := $(TOP_LOCAL_PATH)

NDK_APP_DST_DIR := ../../../Assets/NativeTextureLoader/Plugins/Android
LOCAL_MODULE    := libNativeTextureLoader
LOCAL_C_INCLUDES := $(LOCAL_PATH)/libpng-android/jni/.
LOCAL_SRC_FILES  := $(wildcard ../src/*.cpp)
LOCAL_CFLAGS     := -std=c++14
LOCAL_LDLIBS     := -llog -landroid -lGLESv1_CM -lGLESv2
LOCAL_STATIC_LIBRARIES := libpng

include $(BUILD_SHARED_LIBRARY)
