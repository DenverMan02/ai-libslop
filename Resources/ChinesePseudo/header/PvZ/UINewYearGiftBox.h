
/*
 * UITenYearRecord.h
 *
 *  Created on: 2023-7-20
 *      Author: admin
 */

#ifndef UINEWYEARGIFTBOX_H_
#define UINEWYEARGIFTBOX_H_

#include "UISingletonDialog.h"
#include "NetworkData.h"
#include "Image.h"

enum NewYearGiftBoxButtonId
{
    NEW_YEAR_GIFTBOX_CLOSE = 100,
    NEW_YEAR_GIFTBOX_SHARE,
    NEW_YEAR_GIFTBOX_NEXT,
    NEW_YEAR_GIFTBOX_RECEIVE,
    NEW_YEAR_GIFTBOX_START
};


class NetworkNewYearGiftBoxData : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkNewYearGiftBoxData, INetworkData, RtClass);
    int receive;
    int loginDays;
    int averageTime;
    int gemNum;
    int plantNum;
    int dreesNum;
    int plantAdventureNum;
    int travelWoodNum;
    int selfControlLevel;
    int pvpSuperMax;
    int pennyPursuitNum;
    // int extractedWish;
};

struct NewYear_BonusInfo
{
    int32 objectId;
    int32 Quantity;
    int32 probability;
};

class NewYear_BillingReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(NewYear_BillingReward, INetworkData, RtClass);
    // int32 objectId;
    // int32 Quantity;
    // int32 probability;
    NewYear_BonusInfo billing;
};


class NewYearGiftBoxInfoPage : public Sexy::Widget
{
public:
    
	NewYearGiftBoxInfoPage(UIWidgetImage* i_backimageWidget);
	virtual ~NewYearGiftBoxInfoPage();
    
    int             GetPageIndex();
    void            SetPageIndex(int i_indexPage);
	
	//virtual void    Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g);
    
    // void SetBackImageWidget(UIWidgetImage* i_backimageWidget) {back_imageWidget = i_backimageWidget;}
    // void    Setrecord(UITenYearRecord* i_record) { m_record = i_record}
private:
    
    void            setupScreen();
    
private:
    
    int             m_indexPage;
    
    SexyString      m_Name;
    SexyString      m_strType;

    int             m_loginDays;
    int             m_averageTime;
    
    int             m_gemNum;
    int             m_plantCount;
    int             m_avatarNum;

    int             m_plantAdventureNum;
    int             m_travelWoodNum;
    int             m_selfControlLevel;
    int             m_pvpSuperMax;
    int             m_pennyPursuitNum;
    // 家族

public:
    bool m_receiveflag; 
    UIWidgetImage* back_imageWidget;
    // UITenYearRecord* m_record;
};



class UINewYearGiftBox : public UISingletonDialog<UINewYearGiftBox>
{
public:
	UINewYearGiftBox();
	virtual ~UINewYearGiftBox();
public:
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UINewYearGiftBox"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;
	virtual void 				Update() override;

	void 						InitView();
	void 						CreateQuestion(int i_id);
	virtual void ButtonDepress(int theId) override;
	void 						SetQuestionNum(int i_num) { m_RecordNum = i_num; }
private:
    void Receive();
    void share();
    // void closepersonalty();

private:
	SexyString          m_questionStr;
	int m_currentIndex;

    bool m_receiveflag = false;

    PVZ2UIButton* m_nextBtn;
    PVZ2UIButton* m_stateBtn;
    PVZ2UIButton* m_receiveBtn;
    PVZ2UIButton* m_shareBtn;
    UIWidgetImage* m_ReceiveImage;

    NewYearGiftBoxInfoPage * m_page;
    int m_RecordNum;
    // const std::vector<ArtifactInfo>   m_UnlockedArtifactList;
    // std::vector<PlayerSurveyStringData> m_questionStrList;
public:
    // UIWidgetImage* m_personality0Image;
    // UIWidgetImage* m_personality1Image;
    // UIWidgetImage* m_personality2Image;
    // UIWidgetImage* m_personality3Image;
    // UIWidgetImage* m_personality4Image;
    UIWidgetImage* imageWidget;
    UIWidgetAnim* tmpAnim;
    UIWidgetImage* bg;
};

#endif /* UITENYEARRECORD_H_ */
