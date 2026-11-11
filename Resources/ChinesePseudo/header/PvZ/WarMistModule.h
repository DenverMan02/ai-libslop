//
//  WarMistModule.h
//  PlantsVersusZombies2
//
//  Created by Nan, Lang on 14-9-4.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_WarMistModule_h
#define PlantsVersusZombies2_WarMistModule_h

#include "LevelModule.h"
#include "UIWidget.h"
#include "Plant.h"
#include "ShovelCursor.h"

struct MistImageInfo
{
    float       iPosx;
    float       iPosy;
    float       iOffsetW;
    bool        bLeftMask;
    bool        bRightMask;
    bool        bAllMask;
    bool        bFadeOut;
    bool        bNeedFade;
    pvztime_t   tStartTime;
    Rect        rRect;
    Point       IPoint;
    RtWeakPtr<Image>      pMistImage;
    
    MistImageInfo() {}
    MistImageInfo(RtWeakPtr<Image> pImage, Point p, float iX, float iY, float iW)
    : iPosx(iX)
    , iPosy(iY)
    , pMistImage(pImage)
    , iOffsetW(iW)
    , bLeftMask(false)
    , bRightMask(false)
    , bAllMask(false)
    , IPoint(p)
    , tStartTime(PVZ_T())
    , bFadeOut(false)
    , bNeedFade(false)
    {
        if (pMistImage)
            rRect = Rect(0, 0, pImage->GetWidth(), pImage->GetHeight());
    }
    
    void Reset()
    {
        rRect       = Rect(0, 0, pMistImage->GetWidth(), pMistImage->GetHeight());
        iOffsetW    = 0;
        bLeftMask   = false;
        bRightMask  = false;
        bAllMask    = false;
    }
};

struct SupplymentInfo
{
    FPoint      fPosition;
    Point       IPoint;
    bool        bLeft;
    
    SupplymentInfo() {}
    
    SupplymentInfo(FPoint p, Point i, bool isLeft)
    : fPosition(p)
    , IPoint(i)
    , bLeft(isLeft)
    {
        
    }
};

class WarMistModule : public LevelModule
{
public:
    RT_CLASS_DEFINE(WarMistModule, LevelModule, RtClass);
    
    WarMistModule();
    
    virtual void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;
    
protected:
	virtual void initializeModule() override;
	virtual void registerForEvents() override;
    virtual void unregisterForEvents() override;
    
private:
    
    void            GameplayStarted();
    void            AddToRenderQueue(class RenderQueue* i_queue);
    void            RenderInfos(Graphics* i_g);
    void            OnUpdate();
    
    void            InitMistImage();
    void            SetMistImagePos(float iX, float iY);
    MistImageInfo*  GetWarMistModule(int i, int j);
    void            DrawMistImage(Graphics* pGraphics);
    void            AddEmptyRect(Point& p);
    void            UpdateEmptyRect();
    void            RealRefreshRect();
    
    void            OnPlantRefresh(Plant* pPlant);
    
    void            CheckStreetEffect(BoardEntity* pEntity);
    void            CheckTorchWoodEffect(BoardEntity* pEntity);
    void            CheckBloverEffect();
    
    void            StreetLampUseSkill();
    void            StreetLampUseSkillEnd();
    
    void            MistyIntervalUpdata();
    
private:
    
    bool                        m_bGameStart;
    bool                        m_bStatic;
    bool                        m_bRefresh;
    bool                        m_bStreetLampFoodEffectRunning;
    float                       m_iTargetPosX;
    pvztime_t                   m_iIntervalEndTime;
    
    std::vector<MistImageInfo>  m_vMistImageVec;
    std::vector<Point>          m_EmptyPointVec;
    std::vector<SupplymentInfo> m_SupplymentVec;
    std::vector<MistImageInfo>  m_vFragmentMistImageVec;
    
};


class WarMistProperties : public LevelModuleProperties
{
public:
	RT_CLASS_DEFINE(WarMistProperties, LevelModuleProperties, RtClass);
	
	virtual RtClass* GetModuleClass() const override
	{
		return WarMistModule::StaticGetClass();
	}
    
    WarMistProperties()
    : m_iNormValX(10.0f)
    , m_iBloverEffectInterval(10.0f)
    , m_iInitMistPosX(0)
    {
    }
    
    float       m_iNormValX;
    pvztime_t   m_iBloverEffectInterval;
    int         m_iInitMistPosX;
    
};


#endif
