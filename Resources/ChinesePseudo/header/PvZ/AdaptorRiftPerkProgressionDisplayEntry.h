//
//  AdaptorRiftPerkProgressionDisplayEntry.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 8/13/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef AdaptorRiftPerkProgressionDisplayEntry_h
#define AdaptorRiftPerkProgressionDisplayEntry_h

#include "Curve.h"
#include "HotUIAdaptor.h"
#include "RtObject.h"

struct RiftPerkDisplayEntryData
{
	RiftPerkDisplayEntryData()
	{
		IsEarned = false;
		Threshold = 0;
		Perk = "";
		Icon = "";
		Level = 0;
	}
	
	bool IsEarned;
	int Threshold;
	int Level;
	std::string Perk;
	std::string Icon;
};

class AdaptorRiftPerkProgressionDisplayEntry : public HotUIAdaptor
{
	RT_CLASS_DEFINE(AdaptorRiftPerkProgressionDisplayEntry, HotUIAdaptor, RtClass);
public:
	virtual ~AdaptorRiftPerkProgressionDisplayEntry() {}
	void Update() override;
	void SetData(const RiftPerkDisplayEntryData& i_newData);
	RiftPerkDisplayEntryData GetData() { return m_data; }
	
	void SetAppearObtained(bool i_showObtained);
	void PlayEntryEarnedAnimation();
	
protected:
	virtual void refresh();
	
	Curve<float> m_glowraySizeCurve;
	RiftPerkDisplayEntryData m_data;
};


#endif /* AdaptorRiftPerkProgressionDisplayEntry_h */
