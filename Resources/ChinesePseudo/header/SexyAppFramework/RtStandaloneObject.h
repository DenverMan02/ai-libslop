
#ifndef SexyAppFramework_Prime_RtStandaloneObject_h
#define SexyAppFramework_Prime_RtStandaloneObject_h

#include "RtDb.h"
#include "RtObject.h"

namespace Sexy
{
	
	class RtStandaloneObject
		: public RtObject
	{
		typedef RtObject super;
		void InitWithTableIndex( uint32 tableIndex );
		RtId mStandaloneId;
	public:
		RT_CLASS_DEFINE_ABSTRACT( RtStandaloneObject, RtObject, RtClass ); 
        
		RtStandaloneObject();
		RtStandaloneObject( uint32 tableIndex );
		~RtStandaloneObject();
		RtId StandaloneId();
	};
	
}

#endif
