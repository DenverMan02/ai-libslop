#ifndef __WG_COMMON_H__
#define __WG_COMMON_H__

#include <string>

#include <vector>
#include "WGPublicDefine.h"

#ifdef ANDROID
#include <android/log.h>
#define LOGD(fmt, ...)   __android_log_print(ANDROID_LOG_INFO, "WeGame  ~!!@", fmt, __VA_ARGS__)
#endif

typedef struct {
	int type;
	std::string value;
	int expiration;
} TokenRet;

typedef struct{
public:
	int flag; //返回标记，标识成功和失败类型
	std::string desc; //返回描述
	int platform; //当前登录的平台
	std::string open_id;
	std::vector<TokenRet> token;
	std::string user_id; //用户ID，先保留，等待和微信协商
	std::string pf;
	std::string pf_key;
} LoginRet;

typedef struct {
	int flag; //错误码
	int platform; //被什么平台唤起
	std::string open_id; //传递的openid
	std::string media_tag_name; // 标识消息来源, 对应微信消息的mediaTagName
	std::string desc; //结果描述（保留）
} WakeupRet;

typedef struct {
	int platform; //平台类型
	int flag; //操作结果
	std::string desc; //结果描述（保留）
} ShareRet;

typedef struct {
    std::string ip;
    int port;
} SchedulingInfo;

#endif
