
#ifndef _UI_HEADSHOT_H_
#define _UI_HEADSHOT_H_

#include "DNode/DNodeWidget.h"
#include "UIEasyButtonWidget.h"

class HeadshotConfig:public DSingleton<HeadshotConfig>
{
public:
    HeadshotConfig();
    ~HeadshotConfig();
    
    bool loadConfig();
    
    DIniFile& getConfig() {return loader;}
    
    std::string getHeadshotName(int headshotId);
    std::string getHeadshotSrc(int headshotId);
    
private:
    DIniFile loader;
};


class UIHeadshotIcon:public DNodeWidget
{
public:
    virtual void Initialize() override;
    
    virtual void UserInit() override;
    
    void UserInit(bool showEffect);

    void changeHeadshot(int headshotId);
    
    void changeHeadshot(int headshotId, bool showEffect);

    DSpriteNode* getHeadshotIcon();
    
    void setNeedShowMonthCard(bool need){m_showMonthCard = need;}
    
    bool needShowMonthCard() {return m_showMonthCard;}
    
    bool hasMonthCard();
    
    void setPostion(float x,float y);
    
    void setScale(float x,float y);
    
    void setBackSuffix(const std::string& i_str);
    
    static UIHeadshotIcon* create(int headshotId);
    static UIHeadshotIcon* create(int headshotId, bool showEffect);
    
    static UIHeadshotIcon* createShowMonthCardEffect(int headshotId,bool monthState);
    
protected:
    bool m_bMonthState = false;
    int  m_headshotId = 0;
    bool m_showMonthCard = false;
    bool m_isPlayingMonthCard = false;
    std::string m_backSuffix;
};

class UIHeadshot:public UIHeadshotIcon
{
public:
	UIHeadshot();
	virtual ~UIHeadshot();

    virtual void Initialize() override;
    virtual void UserInit() override;
    static UIHeadshot* create(int headshotId);
    void onNotifyColorChanged();
};

class WorldMap_HeadshotButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(WorldMap_HeadshotButton, UIEasyButtonWidget, RtClass);
    
    WorldMap_HeadshotButton();
    virtual ~WorldMap_HeadshotButton();
    
    virtual void Draw(Graphics* i_g) override;
    
protected:
    void onUpdate() override;
    void UpdateHeadShot(bool need);

private:
    UIHeadshot* m_pHeadshotIcon = nullptr;
    bool m_hasEffect;
};



#endif
