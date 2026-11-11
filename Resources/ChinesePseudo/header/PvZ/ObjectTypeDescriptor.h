//
//  ObjectTypeDescriptor.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/3/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __OBJECTTYPEDESCRIPTOR_H__
#define __OBJECTTYPEDESCRIPTOR_H__

#include "Precompile.h"
#include "RtObject.h"
#include "ReflectionBuilder.h"

using Sexy::RtWeakPtr;
using Sexy::RtObject;
using Sexy::RtClass;

typedef RtWeakPtr<const class ObjectTypeDescriptor> ObjectTypeDescriptorPtr;

class ObjectTypeDescriptor : public RtObject
{
public: 
	RT_CLASS_DEFINE(ObjectTypeDescriptor, RtObject, RtClass)
	{
		REFLECTION_CLASSBUILDER_BEGIN(ObjectTypeDescriptor);
		REFLECTION_CLASSBUILDER_RTCLASS_BIND;
		
			REFLECTION_CLASSBUILDER_FIELD(std::string, TypeName);
		
		REFLECTION_CLASSBUILDER_END(ObjectTypeDescriptor);
	}
	
	std::string TypeName;
};

#endif // __OBJECTTYPEDESCRIPTOR_H__
