LOCAL_PATH := $(call my-dir)

# 全局配置
# ========================================================
ROOT_DIR := $(LOCAL_PATH)
###################################
# Switch On/Off

#SEXY_USE_WWISE := yes
#SEXY_USE_LUA   := yes
#PVZ2_PROFILE := 1
#USE_HIGH_RESOURCE := 1
###################################
SEXY_CFLAGS := -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -DWANTS_RENDER_TARGET_ALPHA_DISABLED -ffast-math
SEXY_CPPFLAGS := -std=gnu++11 -Wno-invalid-offsetof
ifeq ($(PVZ2_PROFILE), 1)
SEXY_CFLAGS += -DPVZ2_PROFILE
endif
SEXY_CFLAGS += -DOPTIMIZE_ANIM_DRAW
ifeq ($(TARGET_ARCH_ABI), arm64-v8a)
#for arm64-v8a compile warning: -fprefetch-loop-arrays not supported for this target
SEXY_CFLAGS_OPT := -O2 -fPIC -flto -fno-inline -fno-omit-frame-pointer -fmove-loop-invariants -freg-struct-return -fno-rtti -fno-exceptions
else
SEXY_CFLAGS_OPT := -O2 -fPIC -flto -fno-inline -fno-omit-frame-pointer -fprefetch-loop-arrays -fmove-loop-invariants -freg-struct-return -fno-rtti -fno-exceptions
endif
ifeq ($(NDK_APP_OPTIM),debug)
$(warning  NDK_APP_OPTIM = $(NDK_APP_OPTIM))
#注意： ndk-build NDK_DEBUG=1 编译方式 运行崩溃；就是因为这里，修改如下可行
#SEXY_CFLAGS +=  -DNDEBUG -DWANTS_DEBUG_DRAW_ENABLED -DWANTS_ASSERT_ENABLED
SEXY_CFLAGS += -DNDEBUG -DRELEASEFINAL -DRELEASE_FINAL
else
ifeq ($(PVZ2_PROFILE), 1)
SEXY_CFLAGS += -DNDEBUG -DRELEASEFINAL -DRELEASE_FINAL $(SEXY_CFLAGS_OPT)
else
SEXY_CFLAGS += -DNDEBUG -DRELEASEFINAL -DRELEASE_FINAL -DWANTS_CHEATS_DISABLED $(SEXY_CFLAGS_OPT)
endif
endif
ifeq ($(USE_HIGH_RESOURCE), 1)
SEXY_CFLAGS += -DWANTS_USE_HIGH_RESOURCE
endif
ifeq ($(SEXY_USE_LUA),yes)
SEXY_CFLAGS += -DLUA_COMPILE
endif


# Prebuild Shared library
# ========================================================
include $(CLEAR_VARS)
# 赋值给NDK编译系统
LOCAL_MODULE := pvz2c
LOCAL_MODULE_FILENAME := libSrc
LOCAL_ARM_MODE := arm
#Note that you can use both relative (to LOCAL_PATH) and absolute file paths.
$(info  TARGET_ARCH_ABI = $(TARGET_ARCH_ABI))
LOCAL_SRC_FILES  := ../../prebuild/libs/$(TARGET_ARCH_ABI)/libSrc.so
#$(warning  LOCAL_SRC_FILES = $(LOCAL_SRC_FILES))
LOCAL_C_INCLUDES := # no need due to "Prebuild Shared library"
LOCAL_EXPORT_C_INCLUDES :=	$(ROOT_DIR)/../../prebuild/header \
							$(ROOT_DIR)/../../prebuild/header/SexyAppFramework \
							$(ROOT_DIR)/../../prebuild/header/SexyAppFramework/EATech/EAText/1.09.07/include \
							$(ROOT_DIR)/../../prebuild/header/SexyAppFramework/EATech/EASTL/1.17.00/include \
							$(ROOT_DIR)/../../prebuild/header/SexyAppFramework/EATech/EABase/2.06.01/include/Common \
							$(ROOT_DIR)/../../prebuild/header/SexyAppFramework/EATech/EAStdC/1.10.02/include \
							$(ROOT_DIR)/../../prebuild/header/SexyAppFramework/EATech/FontFusion/4.5a.06/core \
							$(ROOT_DIR)/../../prebuild/header/SexyAppFramework/EATech/EAIO/2.17.03/include \
							$(ROOT_DIR)/../../prebuild/header/SexyAppFramework/EATech/coreallocator/1.03.11/include \
							$(ROOT_DIR)/../../prebuild/header/SexyAppFramework/EATech/EAThread/1.22.05/include \
							$(ROOT_DIR)/../../prebuild/header/SexyAppFramework/EATech/PPMalloc/1.20.03/include \
							$(ROOT_DIR)/../../prebuild/header/pvz \
							$(ROOT_DIR)/../../prebuild/header/pvz/UIEditor \
							$(ROOT_DIR)/../../prebuild/header/pvz/TodLib \
							$(ROOT_DIR)/../../prebuild/header/pvz/gameNetWork \
							$(ROOT_DIR)/../../prebuild/header/pvz/PVP \
							$(ROOT_DIR)/../../prebuild/header/pvz/dnode \
							$(ROOT_DIR)/../../prebuild/header/pvz/Social/Widgets \
							$(ROOT_DIR)/../../prebuild/header/pvz/Social/Data \
							$(ROOT_DIR)/../../prebuild/header/SexyAppFramework/EATech/EATrace/2.09.07/include \

LOCAL_CFLAGS := $(SEXY_CFLAGS) -D_USE_WIDE_STRING=1 -DGL_GLEXT_PROTOTYPES -D_STLP_HAS_WCHAR_T
LOCAL_CFLAGS += -ffunction-sections -fdata-sections
LOCAL_EXPORT_CFLAGS := $(LOCAL_CFLAGS)
LOCAL_CPP_FEATURES :=# rtti exceptions
LOCAL_CPPFLAGS := $(SEXY_CPPFLAGS) -DWANTS_PRIMETEXT -DWIDGETS_USE_PRIMETEXT -DPRIME_FOR_PVZ2 -DWANTS_WWISE_ENABLED
LOCAL_EXPORT_CPPFLAGS := $(LOCAL_CPPFLAGS)

LOCAL_LDLIBS := -llog -ldl
#This variable is typically useful when module foo is a static library and has code that depends on a system library. You can then use LOCAL_EXPORT_LDLIBS to to export the dependency. 
LOCAL_EXPORT_LDLIBS := $(LOCAL_LDLIBS)
ifeq ($(TARGET_ARCH_ABI), arm64-v8a)
#for arm64-v8a compile error ld.exe: unrecognized option '--icf=safe'
LOCAL_LDFLAGS := -Wl,--gc-sections
else
LOCAL_LDFLAGS := -Wl,--gc-sections,--icf=safe
endif
LOCAL_EXPORT_LDFLAGS := $(LOCAL_LDFLAGS)
LOCAL_SHARED_LIBRARIES :=
LOCAL_STATIC_LIBRARIES :=
LOCAL_WHOLE_STATIC_LIBRARIES :=
LOCAL_SHORT_COMMANDS := false

include $(PREBUILT_SHARED_LIBRARY)
