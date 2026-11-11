/*
 * UIPVZ1PlantBannedScreen.h
 *
 *  Created on: 2021-8-13
 *      Author: admin
 */

#ifndef UIPVZ1PLANTBANNEDSCREEN_H_
#define UIPVZ1PLANTBANNEDSCREEN_H_

#include "DNode/DNodeWidget.h"
#include "UIWidget.h"

class PlantBannedHeadshot : public UIWidget
{
public:
	RT_CLASS_DEFINE(PlantBannedHeadshot, UIWidget, RtClass);

	PlantBannedHeadshot();
	virtual ~PlantBannedHeadshot();

    void Draw(Sexy::Graphics* i_g) override;
    //void Resize(int theX, int theY, int theWidth, int theHeight) override;
    void InitView(std::string i_plantName);

    void onLoadComplete() override;

private:
    void doInit();
    const bool GetIsInitialized();

    Sexy::Rect m_plantRect;
    Sexy::Rect m_frameRect;
    Sexy::Rect m_bannedRect;

    Sexy::ImagePtr m_plantImg;
    Sexy::ImagePtr m_frameImg;
    Sexy::ImagePtr m_bannedImg;
    std::string m_plantName;
};

class PVZ1BannedUI : public UIWidget
{
public:
    RT_CLASS_DEFINE(PVZ1BannedUI, UIWidget, RtClass);

    PVZ1BannedUI();
    virtual ~PVZ1BannedUI();

    // Public Interface (Inheritable)
    virtual void				Draw(Graphics* i_g) override;
    void OnMouseDown(const int i_mouseX, const int i_mouseY) override;
	void OnMouseUp(const int i_mouseX, const int i_mouseY) override;
	void OnMouseMove(const int i_mouseX, const int i_mouseY) override;

protected:
    OVERRIDE_STATE_ONENTER(WidgetState, Initializing);

    virtual void	initLoadingResourcesGroupList() override;
    const Sexy::Rect GetHitRect() override;
    Sexy::Rect		CalcPlusButtonRect();
    bool			IsMouseOver(const int i_mouseX, const int i_mouseY) override;

private:
    void InitView();
    void updateButtonStates(const int i_screenX, const int i_screenY, const bool i_isPressed);

    std::vector<PlantBannedHeadshot*> m_plantWidget;
    std::vector<int> m_list;
    bool m_init;
};

class UIPVZ1PlantBannedScreen:public DNodeWidget
{
public:
    static UIPVZ1PlantBannedScreen* create(const std::vector<int>& list,bool focus = true);

    virtual ~UIPVZ1PlantBannedScreen();

    virtual void Initialize() override;

    virtual void UserInit() override;

public:
    static UIPVZ1PlantBannedScreen* s_pWidgetHandler;
    std::vector<int>          m_list;
};

#endif /* UIPVZ1PLANTBANNEDSCREEN_H_ */
