#APP_ABI := armeabi armeabi-v7a arm64-v8a x86 x86_64
#APP_ABI := armeabi-v7a arm64-v8a
APP_ABI := $(strip $(TARGET))
NDK_TOOLCHAIN_VERSION := 4.9
APP_STL := gnustl_static
APP_PLATFORM := android-14

APP_DEBUG := $(strip $(NDK_DEBUG))
ifeq ($(APP_DEBUG),1)
  APP_OPTIM := debug
else
  APP_OPTIM := release
endif

APP_CPPFLAGS := -std=c++11 -fsigned-char
APP_CFLAGS :=
