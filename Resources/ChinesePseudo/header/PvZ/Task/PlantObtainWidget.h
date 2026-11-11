#ifndef GARDEN_PLANTOBTAINWIDGET_H
#define GARDEN_PLANTOBTAINWIDGET_H

#include "Precompile.h"
#include "Widget.h"
#include "PVZ2UIButton.h"
#include "PVZTypes.h"
#include "PVZ2UIPlantCard.h"

namespace Message
{
    void FinishedTutorial();
}

enum PlantObtainButtonId {
    PLANT_OBTAIN_BUTTON_ID_UNLOCK = 0,
    PLANT_OBTAIN_BUTTON_ID_BUY,
    PLANT_OBTAIN_BUTTON_ID_VIEW
};

class PlantObtainWidget : public Widget, public Sexy::ButtonListener {
public:
    PlantObtainWidget(PlantTypePtr i_objectType, int i_needStarNum, int i_worldStarNum);
    virtual ~PlantObtainWidget();
    
    virtual void                    Update();
    virtual void                    Draw(Graphics* i_g);
    virtual void                    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    
    void                            InitView();
    virtual void                    Resize(int theX, int theY, int theWidth, int theHeight);
    void                            SetWorldStarNum(int i_worldStarNum);
    void                            Unlock();
    
    virtual void                    ButtonDepress(int i_id);
    void                            SetIsTutorial(bool i_tutorial);
    bool							CanUnlockPlant();
    
private:
    PlantTypePtr                    m_objectType;
    PVZ2UIButton*                   m_btnUnlock;
    PVZ2UIButton*                   m_btnView;
    
    bool                            m_unlocked;
    int                             m_needStarNum;
    int                             m_worldStarNum;
    //for ui
    SexyString                      m_labelName;
    Sexy::Rect                      m_rectName;
    SexyString                      m_labelDesc;
    Sexy::Rect                      m_rectDesc;
    SexyString                      m_labelStar;
    Sexy::Rect                      m_rectStar;
    SexyString                      m_labelProgess;
    Sexy::Rect                      m_rectProgress;
    
    Image*                          m_backgroundImage;
    Image*                          m_obtainImage;
    
    bool                            m_isTutorial;
    class BouncingArrow*            m_tutorialArrow;
    
    PVZ2UIGameObjectCard* m_objCard;
};
#endif
