/*
 * IShareDriver.h
 *
 *  Created on: 2022-8-9
 *      Author: admin
 */

#ifndef ISHAREDRIVER_H_
#define ISHAREDRIVER_H_

#include <string>

enum SharePlatform
{
	SharePlatform_All,
	SharePlatform_Wechat,
	SharePlatform_Weibo,
	SharePlatform_Douyin,
	SharePlatform_QQ
};

struct ScreenInfo
{
	ScreenInfo()
	: ScreenX(0)
	, ScreenY(0)
	, ScreenWidth(0)
	, ScreenHeight(0)
	, ImagePath("")
	{

	}

	ScreenInfo(int i_x, int i_y, int i_width, int i_height, const std::string& i_imagePath)
	: ScreenX(i_x)
	, ScreenY(i_y)
	, ScreenWidth(i_width)
	, ScreenHeight(i_height)
	, ImagePath(i_imagePath)
	{

	}

	int ScreenX;
	int ScreenY;
	int ScreenWidth;
	int ScreenHeight;
	std::string ImagePath;
};

class IShareDriver
{
public:
    static IShareDriver* CreateShareDriver();

    virtual ~IShareDriver() {}

    virtual void Initialize() = 0;

    virtual void Share(SharePlatform i_platform, ScreenInfo i_info) = 0;

    virtual bool IsClientInstalled(SharePlatform i_platform) = 0;

    virtual void SaveScreenImageToGallery(ScreenInfo i_info) = 0;

    virtual void SaveScreenImageToLocal(ScreenInfo i_info) = 0;

    virtual bool DeleteLocalImage(ScreenInfo i_info) = 0;
};


#endif /* ISHAREDRIVER_H_ */
