LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := libLunaEngine
LOCAL_SRC_FILES := libLunaEngine.a

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libangelscript
LOCAL_SRC_FILES := angelscriptd.a

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libfreetype2
LOCAL_SRC_FILES := libfreetype2-static.a

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libNativeActivity
LOCAL_SRC_FILES := libNativeActivity.a

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE    := DungeonGame
LOCAL_CPPFLAGS  := -std=c++11 -pthread -frtti -fexceptions -fpermissive
LOCAL_CPPFLAGS  += -D_ANDROID -DNULL=0
LOCAL_CFLAGS  	+= -D_ANDROID -DNULL=0
LOCAL_LDLIBS    := -llog -landroid -lEGL -lGLESv2

LOCAL_WHOLE_STATIC_LIBRARIES := libLunaEngine libfreetype2 libangelscript libNativeActivity

FILE_LIST := $(wildcard $(LOCAL_PATH)/../../../Source/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Source/**/*.cpp)
FILE_LIST += $(wildcard $(LOCAL_PATH)/../../../Source/**/**/*.cpp)

LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../../LunaEngine/Engine/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Source

LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)
#LOCAL_SRC_FILES := DungeonGame.cpp

include $(BUILD_SHARED_LIBRARY)
