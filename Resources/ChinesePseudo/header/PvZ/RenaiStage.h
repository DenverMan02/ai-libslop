/*
 * RenaiStage.h
 *
 *  Created on: 2019-7-22
 *      Author: Administrator
 */

#ifndef RENAISTAGE_H_
#define RENAISTAGE_H_

#include <stdio.h>

#include "AudioMgr.h"
#include "PVZTypes.h"
#include "RtObject.h"
#include "StageModule.h"
#include "WaveActionSpawnZombies.h"

typedef RtWeakPtr<class Effect_PopAnim> Effect_PopAnimPtr;

enum EnvironmentType
{
	EType_Day,
	EType_Evening,
	EType_Night
};

class RenaiStage : public StageModule
{
public:
	RT_CLASS_DEFINE(RenaiStage, StageModule, RtClass);

	RenaiStage();
	virtual ~RenaiStage();

	void SetEnvironmentType(EnvironmentType i_type);
	EnvironmentType GetEnvironmentType() { return m_environmentType; }
	void ActivateAnims();

protected:
	void initializeModule() override;
	void registerForEvents() override;

private:
	void addBackgroundToRenderQueue(class RenderQueue* i_queue);
	void onLoadComplete();
	void onRenderDay(Graphics* i_g);
	void onRenderEvening(Graphics* i_g);
	void onRenderNight(Graphics* i_g);
	void setUpAnims();

	EnvironmentType m_environmentType;
	ImagePtr m_dayBackImage;
	ImagePtr m_dayBackImageRight;
	ImagePtr m_dayBackImageLeft;

	ImagePtr m_eveningBackImage;
	ImagePtr m_eveningBackImageRight;
	ImagePtr m_eveningBackImageLeft;

	ImagePtr m_nightBackImage;
	ImagePtr m_nightBackImageRight;
	ImagePtr m_nightBackImageLeft;
	std::vector<Effect_PopAnimPtr> m_environmentAnims;
};

struct EnvironmentAnim
{
	std::string AnimName;
	SexyVector2 AnimPos;
};

class RenaiStageProperties : public StageModuleProperties
{
public:
	RT_CLASS_DEFINE(RenaiStageProperties, StageModuleProperties, RtClass);

	RtClass* GetModuleClass() const override
	{
		return RenaiStage::StaticGetClass();
	}

	RenaiStageProperties()
	{

	}

	std::vector<EnvironmentAnim> Anims;
};


#endif /* RENAISTAGE_H_ */
