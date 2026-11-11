#pragma once

#ifndef BASE_ANTI_HACK_H_INCLUDED

#define BASE_ANTI_HACK_H_INCLUDED



#include "IAntiHackDriver.h"

#include <string>

namespace Sexy 

{

	class BaseAntiHackDriver : public IAntiHackDriver

	{

	public:

		BaseAntiHackDriver();

		virtual~ BaseAntiHackDriver();



		//is some one hacked the game package

 		virtual bool IsPackageHacked();

 		virtual void EncodeBuffer(Buffer& inBuffer,Buffer& outBuffer);

 		virtual void DecodeBuffer(Buffer& inBuffer,Buffer& outBuffer);



 		std::string	 mSalt;////Salt for key

	private:

 		void GenerateKeyIV(const char* pKey, std::string &strKey, std::string &strIV);

	};



}





#endif



