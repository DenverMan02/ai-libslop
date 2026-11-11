/*
 * sdkhelper.h
 *
 *  Created on: 2014-7-22
 *      Author: lizheng
 */

#ifndef SDK_HELPER_H_
#define SDK_HELPER_H_
#include "core.h"
#include "SexyURL.h"


class SDKHelper : public LazySingleton<SDKHelper>
{
public:
	SDKHelper();
    NSString* DateToString(NSDate* date);
    NSDate* StringToDate(NSString* str);
    bool IsTimeExpired(NSDate* date);
    bool IsTimeExpired(NSString* str);
};


#endif /* SDK_HELPER_H_ */
