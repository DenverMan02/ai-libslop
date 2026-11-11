//
//  StreamingMusicList.h
//  PlantsVersusZombies2
//
//  Created by Todd Gilbertsen on 5/14/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__StreamingMusicList__
#define __PlantsVersusZombies2__StreamingMusicList__

#include "ObjectTypeDescriptor.h"
#include "Precompile.h"
#include "RtObject.h"

struct StreamingMusicGroup
{
	std::string					streamingPath;
    std::string                 groupName;
    std::vector<std::string>    fileIds;
};

class StreamingMusicList : public ObjectTypeDescriptor
{
public:
	RT_CLASS_DEFINE(StreamingMusicList, ObjectTypeDescriptor, RtClass);
    
	// Default values
	StreamingMusicList()
	{
	}

	std::vector<StreamingMusicGroup> groups;
};
typedef RtWeakPtr<class StreamingMusicList> StreamingMusicListPtr;

#endif /* defined(__PlantsVersusZombies2__StreamingMusicList__) */
