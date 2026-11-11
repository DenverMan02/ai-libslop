//
//  AdaptorRiftDifficultyInfoWidget.h
//  PlantsVersusZombies2Framework
//
//  Created by Moss, Evelyn on 9/18/19.
//  Copyright © 2019 PopCap Games. All rights reserved.
//

#ifndef AdaptorRiftDifficultyInfoWidget_h
#define AdaptorRiftDifficultyInfoWidget_h

//#include "AdaptorLevelZombieResistanceItem.h"
#include "AdaptorRiftLevelDifficultyEntry.h"
#include "HotUIAdaptor.h"
#include "RtDb.h"

class AdaptorRiftDifficultyInfoWidget : public HotUIAdaptor
{
public:
	RT_CLASS_DEFINE(AdaptorRiftDifficultyInfoWidget, HotUIAdaptor, RtClass);
	
	AdaptorRiftDifficultyInfoWidget()
	: m_parent(nullptr) {}
	~AdaptorRiftDifficultyInfoWidget();
	
	//void ConfigureResistance(WidgetContainer* i_parent, const PlantFamilyResistance& i_config, const SexyString i_description);
	void ConfigureDifficulty(WidgetContainer* i_parent, RtWeakPtr<LevelModuleDifficultyUIProps> i_config, const SexyString i_description);
	
protected:
	void onLoadUIView() override;
	void onLinkToUIViewCreated() override;
	void setText(SexyString i_name, SexyString i_description);
	
private:
	WidgetContainer* m_parent;
	//PlantFamilyResistance m_resistanceConfig;
	RtWeakPtr<LevelModuleDifficultyUIProps> m_difficultyModConfig;
	SexyString m_description;
	std::vector<HotUIAdaptor*> m_contentWidgets;
};

#endif /* AdaptorRiftDifficultyInfoWidget_h */
