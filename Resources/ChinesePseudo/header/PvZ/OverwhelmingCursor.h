// PVZ1BowlingModule.h
// create by lfy
// 2023.11.04

#ifndef __OVERWHELMINGMINIGAME_H__
#define __OVERWHELMINGMINIGAME_H__

#include "BoardEnums.h"
#include "PlantType.h"
#include "PlantCursor.h"
#include "LevelModule.h"
#include "PlantAnimRig.h"

namespace OverwhelmUtils
{
    bool IsPlayingOverwhelm();
};

class OverwhelmCursor : public PlantCursor
{
public:
    RT_CLASS_DEFINE(OverwhelmCursor, PlantCursor, RtClass) {}

	OverwhelmCursor() {}
    ~OverwhelmCursor();

    explicit OverwhelmCursor(const Sexy::Touch& i_boardSpaceTouch, SeedPacketPtr i_seedPacket, int i_level = -1);
	explicit OverwhelmCursor(const Sexy::Touch& i_boardSpaceTouch, PlantTypePtr i_plantType, Sexy::Rect i_originBoardSpaceRect = Sexy::Rect(0,0,0,0), bool i_useBoost = false, int i_level = -1);

    std::vector<PlantAnimRig*> GetPlantAnimRig() { return m_animArray; }
protected:
    void onDraw(Sexy::Graphics* i_g) override;
    void onUpdate() override;
    void tryToUse() override;
    void tryToPlantAt(const int i_gridX, const int i_gridY);
private:
    void createCacheAnim();    
    std::vector<PlantAnimRig*> m_animArray;
    int m_plantCnt = 0;
};


class PVZ1OverwhelmModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(PVZ1OverwhelmModule, LevelModule, RtClass);    
};

class PVZ1OverwhelmModuleProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(PVZ1OverwhelmModuleProperties, LevelModuleProperties, RtClass);

	virtual RtClass* GetModuleClass() const override
	{
		return PVZ1OverwhelmModule::StaticGetClass();
	}    
};



#endif  // END OF __OVERWHELMINGMINIGAME_H__