/*
 * UIRankAvatarSelect.h
 *
 *  Created on: 2022-3-31
 *      Author: admin
 */

#ifndef UIRANKAVATARSELECT_H_
#define UIRANKAVATARSELECT_H_

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "EditListener.h"
#include "UIListener.h"
#include "NetworkData.h"

enum
{
	RankAvatar_Btn_Close = 5000,
	RankAvatar_Btn_Change = 5001,

	RankAvatar_Btn_Select_Index_Start = 5100
};

class NetworkRankAvatarData : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkRankAvatarData, INetworkData, Sexy::RtClass);

public:
    int CurrentId;
};

class RankAvatarWidget : public PVZ2UIButton, public ButtonListener
{
public:
	RankAvatarWidget(int i_buttonID, int i_id);
	virtual ~RankAvatarWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    virtual void InitView();

    void Select();

    void SetBgImage(Image* i_img) { m_img = i_img; }
    void SetID(int i_id) { m_id = i_id; }
    int GetID() const { return m_id; }
    bool IsSelected() const { return m_selected; }
    void SetSelected(bool i_selected) { m_selected = i_selected; }
    void SetClickFunc(Delegate1<int> i_function) { m_function = i_function; }

protected:
    int m_id;
    Image* m_img;
    Image* m_selectImg;
    bool m_selected;// if is selected.
    Delegate1<int> m_function;
};

class UIRankAvatarSelect : public UISingletonDialog<UIRankAvatarSelect>, public Sexy::ScrollWidgetListener
{
public:
	UIRankAvatarSelect();
	virtual ~UIRankAvatarSelect();

	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UIRankAvatarSelect"; }
	virtual void ButtonDepress(int i_id) override;
	virtual void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
	virtual void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}

protected:
	void InitView();
	void ChangeRankAvatar();
	std::vector<class RankAvatarWidget*> CreateRankWidgets(Widget* parent, std::vector<int> i_idList,int startBtnID);
	void OnClickRankWidget(int i_id);
	void UpdateContent(int i_id);

private:
	std::vector<class RankAvatarWidget*> m_rankWidgets;
	int m_currentSelectedId;
};


#endif /* UIRANKAVATARSELECT_H_ */
