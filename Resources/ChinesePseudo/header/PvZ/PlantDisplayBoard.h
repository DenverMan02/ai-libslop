//
//  PlantDisplayBoard.h
//  PlantsVersusZombies2
//
//  Created by Zhen Xie "Xie Zhen" on 14-7-29.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__PlantDisplayBoard__
#define __PlantsVersusZombies2__PlantDisplayBoard__

#include "ObjectTypeDescriptor.h"
#include "PVZTypes.h"


namespace Message {
    void DisplayLevelSelect(int i_level);
    void DisplaySelectButton(int i_level);
}

enum DisplayType
{
    Display_Null,
    Display_Levelup,
    Display_Store,
    Display_Avatar
};

struct DisplayPlantInfo
{
    std::string PlantName;
    int Hitpoint;
    int PosX;
    int PosY;
    
    DisplayPlantInfo()
    {
        Hitpoint = 0;
        PosX = 0;
        PosY = 0;
    }
};

struct DisplayZombieInfo
{
    std::string ZombieName;
    int Hitpoint;
    int PosX;
    int PosY;
    DisplayZombieInfo()
    {
        Hitpoint = 0;
        PosX = 0;
        PosY = 0;
    }
};

struct DisplayActionInfo
{
    std::string DisplayImage;
    std::vector<DisplayPlantInfo> DisplayPlants;
    std::vector<DisplayZombieInfo> DisplayZombies;
    float DisplayTime;
    int Level;
    bool IsAvatar = false;
    bool IsPlantfood = false;
    int SkillProbability;
    float AutoFireTime;
    bool DelayPlantfood;
    
    DisplayActionInfo()
    {
        DisplayImage = "";
        DisplayTime = 0;
        SkillProbability = -1;
        Level = 0;
        AutoFireTime = -1;
        DelayPlantfood = false;
    }
};

class DisplayLevelButton : public Widget, public ButtonListener
{
public:
    DisplayLevelButton(int i_level);
    virtual ~DisplayLevelButton();
    
    void SelectLevel(int i_level);
    
    virtual void Draw(Graphics* i_g);
    virtual void DrawAll(ModalFlags* theFlags, Graphics* g);
    virtual void ButtonDepress(int i_id);
public:
    bool m_bSelected;
    int m_level;
    Image* m_image;
};

class PlantDisplayBoard : public Widget
{
public:
    PlantDisplayBoard(DisplayType i_type=Display_Null, bool plantTrial = false);
    ~PlantDisplayBoard();
    
    void SetPlantName(const std::string& i_plantName);
    void SetDisplayActions(std::vector<DisplayActionInfo> &i_displayActions);
    void DisplayNexyAction();
    void SetPlantLevel(int i_level);
    void SetDisplayLevel(int i_level);
    virtual void Update();
    virtual void Draw(Graphics* g);
    virtual void DrawAll(ModalFlags* theFlags, Graphics* g);
    void SetDisplayLevelButtonPosOffset(Sexy::SexyVector2 stp);
    void SetSkillNamePosOffset(Sexy::SexyVector2 stp) { m_SkillNamePosOffset = stp; }
   
    void HideDisplayItems(bool bImmediately = false);
    void EnableAutoNext() { m_enableAutoNext = true; }
    void DisableAutoNext() { m_enableAutoNext = false; }

    void SetAvatarIndex(int i_index) { m_avatarIndex = i_index; }
    void SetHideDisplayItems(bool hide) { m_hideDisplayItems = hide; }

//interface for new plant view
public:
    void SetHideSkillName(bool i_flag) { m_hideSkillName = i_flag; }
    void SetDisplayLevelButtonGapX(float i_gapX);
    void SetDisplayImageOffset(const Sexy::SexyVector2& stp) { m_DisplayImageOffset = stp; }
    void SetPlantfoodImageOffset(const Sexy::SexyVector2& stp) { m_PlantfoodImageOffset = stp; }

public:
    bool m_hideSkillName;
    bool m_hideDisplayItems;
    bool m_enableAutoNext;

    int m_avatarIndex;
    
    int m_curActionIndex;
    int m_startActionIndex;
    int m_endActionIndex;
    float m_ActionTime;
    bool m_plantTrial;
    
    class MiniBoard* m_board;
    PlantTypePtr m_plantType;
    Image *m_displayImage;
    
    SexyString m_skillName;
    int m_selectLevel;
    
    DisplayType m_displayType;
    class Plant* m_plant;
    float m_autoFireTime;
    
    Sexy::SexyVector2 m_SkillNamePosOffset;
    Sexy::SexyVector2 m_DisplayLevelButtonPosOffset;
    Sexy::SexyVector2 m_DisplayImageOffset;
    Sexy::SexyVector2 m_PlantfoodImageOffset;

    
    std::vector<DisplayLevelButton*>    m_vecDisplayLevelButton;
    std::vector<DisplayActionInfo>      m_displayActions;
};

#endif /* defined(__PlantsVersusZombies2__PlantDisplayBoard__) */
