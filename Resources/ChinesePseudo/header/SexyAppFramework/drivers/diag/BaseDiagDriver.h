#ifndef BASEDIAGDRIVER_H_INCLUDED
#define BASEDIAGDRIVER_H_INCLUDED

#include "IDiagDriver.h"

namespace Sexy
{
	class BaseDiagDriver : public IDiagDriver
	{
	protected:
		BaseDiagDriver();
		~BaseDiagDriver();

		const char* EnsureInfoStringCapacity(size_t length);

		char* mInfoString;
		size_t mInfoStringCapacity;

	public:
		const char* GetInfoStringSafe(EInfoStringType inType);
        
        virtual double GetInfoNumber(EInfoNumberType inType);
	};
};

#endif
