#ifndef __POPANIMLISTENER_H__
#define __POPANIMLISTENER_H__

#include "Common.h"
#include "Color.h"

namespace Sexy
{

class PASpriteInst;
class PAObjectInst;
class PATransform;
class Graphics;
class Image;

class PopAnimListener
{
public:
	virtual ~PopAnimListener() {}
	virtual void			PopAnimPlaySample(const std::string& theSampleName, int thePan, double theVolume, double theNumSteps) {}
	virtual void			PopAnimStopped(int theId) {}
	virtual void			PopAnimCommand(int theId, const std::string& theCommand, const std::string& theParam) {}
	virtual bool			PopAnimCommand(int theId, PASpriteInst* theSpriteInst, const std::string& theCommand, const std::string& theParam) { PopAnimCommand(theId, theCommand, theParam); return false; }
};

}

#endif //__POPANIMLISTENER_H__
