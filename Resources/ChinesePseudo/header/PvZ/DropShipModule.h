//
//  DropShipModule.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 15-7-23.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_DropShipModule_h
#define PlantsVersusZombies2_DropShipModule_h

#include "LevelModule.h"
#include "UIWidget.h"
#include "Plant.h"
#include "WaveGenerator.h"

struct IntRange
{
    int Min;
    int Max;
    
    int GetRandomValue() const
    {
        return Min + Sexy::Rand(Max - Min + 1);
    }
};

struct DropImpInfo
{
    DropImpInfo() : ImpLv(3) {}
    
    int Wave;
    int Imp;
    int ImpLv;
    IntRange RowRange;
    IntRange ColRange;
};

class DropShipEffectAnim : public Effect_PopAnim
{
public:
    
    RT_CLASS_DEFINE(DropShipEffectAnim, Effect_PopAnim, RtClass);
    
    DropShipEffectAnim() : m_iDropNum(0) {}
    
    void onAnimStopped(const std::string& i_animLabel) override;
    
    void OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    
    void SetDropInfo(const DropImpInfo& info) { m_DropInfo = info; }
    
private:
    
    void DropImp();
    
private:
    
    pvztime_t m_iNextDropTime;
    
    DropImpInfo  m_DropInfo;
    
    int       m_iDropNum;
    
};

class DropingImpEffectAnim : public Effect_PopAnim
{
public:
    
    RT_CLASS_DEFINE(DropingImpEffectAnim, Effect_PopAnim, RtClass);
    
    DropingImpEffectAnim() : m_bFlyingEnd(false), m_iImpLv(3) {}
    
    void onAnimStopped(const std::string& i_animLabel) override;
    
    void onUpdate() override;
    
    void registerForEvents() override;
    
    void SetDate(Sexy::Point pt, int iLv) { m_desGrid = pt; m_iImpLv = iLv; }
    
    void SetImpPosition(Sexy::SexyVector2 v2);
    
private:
    
    void DoPowerupCuke();
    
private:
    
    Sexy::Point m_desGrid;
    
    bool m_bFlyingEnd;
    
    int  m_iImpLv;
    
};


class DropShipModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(DropShipModule, LevelModule, RtClass);
    
    DropShipModule();
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
    
private:

    void            OnUpdate();
    
    void            OnWaveStarted(int iWaves);
    bool            WaveContain(int iWaves);
    void            DropShipBegin(int iWaves);
    const DropImpInfo&       GetDropInfo(int iWaves);
    
};


class DropShipProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(DropShipProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return DropShipModule::StaticGetClass();
	}
    
    DropShipProperties()
    {
    }
    
    std::vector<DropImpInfo> AppearWaves;
};


#endif
