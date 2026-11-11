#ifndef HeroPlant_H_
#define HeroPlant_H_

#include "PlantFramework.h"
#include "GameSubSystem.h"
#include "HeroPlantConfig.h"

class HeroPlantFramework;
class HeroPlantTalentButton;
class HeroPlantTalentSubsystem;

struct HeroPlantSaveInfo
{
    int m_currentExp = 0;
    int m_currentGrade = 0;
    int m_maxGrade = 0;
    int m_talentPoints = 0;
    std::vector<int> m_talentLevels;
};

class HeroPlantFramework : public PlantFramework
{
    friend class HeroPlantTalentSubsystem;

public:
    RT_CLASS_DEFINE(HeroPlantFramework, PlantFramework, RtClass);

    virtual void PostInitialize() override;
    virtual float GetRefundSunAmount() override;
    virtual void onKilled(bool i_instantKill) override;
    virtual void onDestroy() override;

    void SaveHeroPlantInfo();

//about display
public:
    virtual void AddToRenderQueue(class RenderQueue* i_queue) override;
	void DrawHeroPlantHud(Graphics *i_g);


//about touch
public:
    bool DoPressHeroPlant();

    virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;

	bool onTouchEvent(const Sexy::Touch& i_touch);
	void onCancelEvent();
    void ClearTouch();

//about grade and talent
public:
    void InitGradeUpInfo();
    void InitByHeroPlantSaveInfo();

    void AddExperience(int i_exp);
    bool CanGradeUp();
    void GradeUp();

    int GetTalentPointsFromGradeUp(int i_grade);//升级获得的技能点
    int GetExpForGradeUp(int i_grade);//升级需要的经验
    HeroPlantGradeUp GetGradgeUpInfo(int i_grade);
    Sexy::Image* GetExpSliceImage();

    int GetTalentLevel(int i_talentIndex);//天赋等级
    int GetTalentLevelUpCost(int i_talentIndex);//天赋升级消耗天赋点数量
    bool CanTalentLevelUp(int i_talentIndex);//是否可以升级
    bool IsTalentLevelMax(int i_talentIndex);//是否满级
    void TalentLevelUp(int i_talentIndex);

    HeroPlantTalent GetTalentConfig(int i_talentIndex);
    SexyString GetTalentName(int i_talentIndex, int i_talentLevel);
    SexyString GetTalentDescription(int i_talentIndex, int i_talentLevel, bool i_canLevelUp);

protected:
    int m_currentExp;
    int m_currentGrade;
    int m_maxGrade;

    int m_talentPoints;
    std::vector<int> m_talentLevels;

protected:
    Sexy::TouchID m_touchIdent;

};

namespace Message 
{
    void HeroPlantTalenLevelUp(Plant* i_plant, int i_talentIndex);
}


//////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////HeroPlantTalentSubsystem////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

enum HeroPlantTalentSubsystemState : int
{
    HeroPlantTSS_Inactive = 0,
    HeroPlantTSS_Active,
    HeroPlantTSS_Close,
};

class HeroPlantTalentSubsystem : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(HeroPlantTalentSubsystem, GameSubSystem, RtClass);

    HeroPlantTalentSubsystem();
    ~HeroPlantTalentSubsystem();

    void ShowHeroPlantTalentPannel(PlantPtr i_heroPlant);
    void CloseHeroPlantTalentPannel();

	virtual void Update() override;
    virtual void onDestroy() override;
    void setState(HeroPlantTalentSubsystemState i_state);

    void SelectTalentButton(int i_talentIndex);
    void RefreshButtons();

protected:
	virtual void registerForEvents() override;
	virtual void unregisterForEvents() override;
public:
    virtual void AddToRenderQueue(class RenderQueue* i_queue) override;
    void drawHeroPlantTalentButtons(Sexy::Graphics *i_g);

private:
    Sexy::TouchID m_touchIdent;

    bool handleTouch(const Sexy::Touch& i_touch);
    void cancelTouch();
    void clearTouch();


    void onHeroPlantTalenLevelUp(Plant* i_plant, int i_talentIndex);
private:
    bool IsSystemActive();

    PlantPtr m_heroPlantPtr;
    Sexy::Point m_archorPoint;

    HeroPlantTalentSubsystemState m_state;
    std::vector<HeroPlantTalentButton> m_buttonList;

    bool m_firstPlant;
    HeroPlantSaveInfo m_saveInfo;
}; 


//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////HeroPlantTalentButton/////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

class HeroPlantTalentButton
{
    friend class HeroPlantTalentSubsystem;
public:
    HeroPlantTalentButton();
    ~HeroPlantTalentButton();

    void InitButton(int i_talentIndex, PlantTypePtr i_heroPlant);
    void RefreshInfo();

public:
    void Resize(int i_x, int i_y, int i_width,  int i_height);
    void Update();
    void Draw(Sexy::Graphics *i_g);

	bool onTouchEvent(const Sexy::Touch& i_touch);
    void clearTouch();
    void OnClick();

    void OnSelect(bool i_flag);

private:
    void DrawCenter(Sexy::Graphics *i_g, float i_centerX, float i_centerY, Sexy::Image* i_image);

    Rect m_rect;
    std::pair<float, float> m_archor;
    std::vector<std::pair<float, float>> m_slotArchor;
    float m_scale;

    bool m_selected;
    Sexy::Image* m_talentImage = nullptr;

    Sexy::TouchID m_touchIdent;

private:
    int m_talentIndex;
    PlantPtr m_heroPlantPtr;

    bool m_canLevelUp;
    int m_currentLevel;
    int m_maxLevel;
};


#endif
