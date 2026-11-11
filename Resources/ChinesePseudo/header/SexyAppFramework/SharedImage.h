#ifndef __SHARED_IMAGE_H__
#define __SHARED_IMAGE_H__

#include "Common.h"
#include "RtDb.h"

namespace Sexy
{

class Image;
class DeviceImage;
class MemoryImage;

/*
class SharedImage
{
public:
	DeviceImage*				mImage;
	int						mRefCount;		
	bool					mLoading;

	SharedImage();

	RA_METAMETHOD_TOSTRING(ToString);
};
*/

//typedef std::map<std::pair<std::string, std::string>, SharedImage> SharedImageMap;
typedef std::map<std::pair<std::string, std::string>, RtId> SharedImageMap;

/*
class SharedImageRef
{
public:
	SharedImage*			mSharedImage;
	MemoryImage*			mUnsharedImage;
	bool					mOwnsUnshared;

public:
	SharedImageRef();
	SharedImageRef(const SharedImageRef& theSharedImageRef);
	SharedImageRef(SharedImage* theSharedImage);
	~SharedImageRef();

	void					Release();

	SharedImageRef&			operator=(const SharedImageRef& theSharedImageRef);
	SharedImageRef&			operator=(SharedImage* theSharedImage);
	SharedImageRef&			operator=(MemoryImage* theUnsharedImage);
	MemoryImage*			operator->();
	operator Image*();
	operator MemoryImage*();
	operator DeviceImage*();

	RA_METAMETHOD_TOSTRING(ToString);
};
*/

}

#endif //__SHARED_IMAGE_H__
