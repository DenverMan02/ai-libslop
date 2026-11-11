#pragma once

#ifndef IANTI_HACK_H_INCLUDED

#define IANTI_HACK_H_INCLUDED



#include <string>

#include "Buffer.h"



namespace Sexy 

{

 	class IAntiHackDriver

 	{

 	public:

 		static  IAntiHackDriver*	CreateAntiHackDriver();

 		virtual ~IAntiHackDriver(){}



 		//is some one hacked the game package

 		virtual bool IsPackageHacked() = 0;

 		//we do Encryption

 		virtual void EncodeBuffer(Buffer& inBuffer,Buffer& outBuffer) = 0;

 		virtual void DecodeBuffer(Buffer& inBuffer,Buffer& outBuffer) = 0;

 	};



}





#endif



