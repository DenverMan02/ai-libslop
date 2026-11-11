#ifndef __D3DOBJECTLISTENER_H__
#define __D3DOBJECTLISTENER_H__

#include "RtId.h"

namespace Sexy
{

class D3DObject;
class DeviceImage;

class D3DObjectListener 
{
public:	
	virtual void			D3DObjectPreLoad(D3DObject* theObject) {}
	virtual void			D3DObjectHandleProperty(D3DObject* theObject, const std::string& theObjectName, const std::string& theSetName, const std::string& thePropertyName, const std::string& thePropertyValue) {}
	virtual RtId			D3DObjectLoadTex(D3DObject* theObject, const std::string& theObjectName, const std::string& theSetName, const std::string& theTexType, const std::string& theFileName) { return RtId(); }

	virtual void			D3DObjectPreDraw(D3DObject* theObject) {}
	virtual void			D3DObjectPostDraw(D3DObject* theObject) {}
	virtual void			D3DObjectPreDrawSet(D3DObject* theObject, const std::string& theObjectName, const std::string& theSetName, bool hasBump) {}
	virtual void			D3DObjectPostDrawSet(D3DObject* theObject, const std::string& theObjectName, const std::string& theSetName) {}	

	virtual void			D3DObjectPreDeleted(D3DObject* theObject) {}
};

}

#endif __D3DOBJECTLISTENER_H__