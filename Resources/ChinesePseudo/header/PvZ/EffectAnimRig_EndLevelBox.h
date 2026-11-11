//
//  EffectAnimRig_EndLevelBox.h
//  PlantsVersusZombies2
//
//  Created by Cao Shuai, Modified By Wanqi
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EffectAnimRig_EndLevelBox__
#define __PlantsVersusZombies2__EffectAnimRig_EndLevelBox__

#include "PopAnimRig.h"
#include "WorldMap.h"
#include "TimeLine.h"
#include "NetworkCacheQueue.h"

enum HardLevelRewardType
{
    HARD_LEVEL_COINS_REWARD = 0,
    HARD_LEVEL_GEMS_REWARD,
    HARD_LEVEL_KEY_REWARD,
    HARD_LEVEL_PLANT_REWARD,
    HARD_LEVEL_AVATAR_REWARD,
    HARD_LEVEL_PLANT_PIECE_REWARD,
    HARD_LEVEL_AVATAR_PIECE_REWARD,
    HARD_LEVEL_ACCESSORY_REWARD,
    HARD_LEVEL_ACCESSORY_PIECE_REWARD,
    
    HARD_LEVEL_REWARD_COUNT,
};

struct EItem
{
    EItem()
    {
        ItemName = "";
        Type = HARD_LEVEL_COINS_REWARD;
        Count = 0;
    }
    std::string ItemName;
    HardLevelRewardType Type;
    int Count;
};

struct EBox
{
    EBox()
    {
        Weight = 0;
        Item.clear();
    }
    int Weight;
    std::vector<EItem> Item;
};

struct ESection
{
    ESection()
    {
        SectionId = 0;
        Box.clear();
    }
    int SectionId;
    std::vector<EBox> Box;
};

struct ELevelConfig
{
    ELevelConfig()
    {
        LevelName = "";
        SectionId = 0;
    }
    std::string LevelName;
    int SectionId;
};

class EndLevelAward : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(EndLevelAward, Sexy::RtObject, Sexy::RtClass);
    
    EndLevelAward();
    virtual ~EndLevelAward();
    static ELevelConfig* GetEndLevelConfig(const std::string& levelName);
    
    std::vector<ESection> Section;
    std::vector<ELevelConfig> LevelConfig;
};

struct HardAwardItem
{
public:
    HardAwardItem()
    {
        name = "";
        type = HARD_LEVEL_COINS_REWARD;
        count = 0;
        rewardImage = NULL;
        scale = 1.f;
    }
    
    std::string name;
    HardLevelRewardType type;
    int count;
    Image* rewardImage;
    float scale;
    Sexy::Point endPos;
    CurveSegment_SexyVector3 curveSeg;
} ;

class RandRecord
{
public:
    int  get()
    {
        return record[pos ++];
    }
    void set(int r)
    {
        record.push_back(r);
    }
    void reset()
    {
        record.clear();
        pos = 0;
    }
private:
    std::vector<int> record;
    int pos = 0;
};

class EffectAnimRig_EndLevelBox : public PopAnimRig
{
public:
    RT_CLASS_DEFINE(EffectAnimRig_EndLevelBox, PopAnimRig, RtClass);
    EffectAnimRig_EndLevelBox();
    ~EffectAnimRig_EndLevelBox();
    
    void setEndLevelRig(class EffectAnimRig_EndLevel* endLevelRig)
    { m_endLevelRig = endLevelRig;}
    
    void playBoxCome();
    
    void showHardAward();
    void collectHardAward();
    void adjustParentSize(int w, int h);
    
    void hardLevelAward(const struct HardAwardItem* award);
    void adjustBoxPosition(SexyVector2 pos) { m_boxPosOffset = pos; }
    
    std::vector<HardAwardItem > getHardLevelAward() const;
    
    void initHardAwardItems(const std::string& levelName,bool isRecord = false);
    std::string GetCurrentLevel();
    
private:
    virtual void onAnimStopped() override;
    virtual void onPopAnimCommand(pvztime_t i_atTime, const std::string& i_command, const std::string& i_param) override;
    virtual void onUpdate() override;
    virtual void onPostDraw(Graphics* i_g) override;
    
    void initHardAwardItems();
    EBox GetAwardBoxByRand(const std::string& levelName, bool useRecord = false);
    void SetAwardImageAndScale(const struct HardAwardItem* award, Image* &rewardImage, float &scale);
    
private:
    int m_PWidth;
    int m_PHeight;
    int m_hardState;
    pvztime_t m_endEffectTime;
    SexyVector2 m_boxPosOffset;
    std::string m_levelName;
    std::vector<struct HardAwardItem* > m_hardAwardItems;
    std::vector<ESection> Section;
    std::vector<ELevelConfig> LevelConfig;
    std::vector<NetworkCacheObjects> m_hardLevelRewards;
    class EffectAnimRig_EndLevel* m_endLevelRig;
};

#endif /* defined(__PlantsVersusZombies2__EffectAnimRig_EndLevelBox__) */
