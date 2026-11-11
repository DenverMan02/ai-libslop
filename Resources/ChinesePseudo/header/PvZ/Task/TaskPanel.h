#ifndef GARDEN_TASKPANEL_H
#define GARDEN_TASKPANEL_H

#include "Precompile.h"

#include "PlantObtainWidget.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include <list>

class TaskPanel : public Widget, public Sexy::ScrollWidgetListener, Sexy::ButtonListener {
public:
    TaskPanel(std::string i_worldName);
    ~TaskPanel();

    
    
    void InitView();
    
    virtual void ScrollTargetReached( ScrollWidget* scrollWidget ) {}
    virtual void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) {}

    virtual void ButtonDepress(int i_id);
    virtual void Draw(Graphics *i_g);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
    void         SetIsTutorial(bool i_tutorial);

private:
    PVZ2UIScrollingWidget*  m_scrollingWidget;
    
    std::string             m_worldName;
    PVZ2UIButton*           m_closeButton;
};

class TaskScroolPanel : public Widget {
public:
    TaskScroolPanel(std::string i_worldName, Rect &i_rect, int i_starNum);
    ~TaskScroolPanel();
    
    void                            RegisterForMsg();
    void                            UnregisterForMsg();
    void                            OnWorldStarChanged(int i_newStarNum);
    
private:
    void                            LoadPlantInfo();
    void                            InitView();
    
    int                             m_starNum;
    std::string                     m_worldName;
    std::list<PlantObtainWidget *>  m_listPlantWidget;
    
};

class TaskBackgroundPanel : public Widget {
public:
    TaskBackgroundPanel();
    virtual void Draw(Graphics *i_g);
};

#endif
