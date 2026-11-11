#pragma once

#ifndef NULL_ANTI_HACK_H_INCLUDED

#define NULL_ANTI_HACK_H_INCLUDED



#include "IAntiHackDriver.h"

#include <string>

namespace Sexy 

{

	class NullAntiHackDriver : public IAntiHackDriver

	{

	public:

		NullAntiHackDriver();

		virtual ~NullAntiHackDriver();



		virtual bool IsPackageHacked();

		virtual void EncodeBuffer(Buffer& inBuffer,Buffer& outBuffer);

		virtual void DecodeBuffer(Buffer& inBuffer,Buffer& outBuffer);

	};







}





#endif



