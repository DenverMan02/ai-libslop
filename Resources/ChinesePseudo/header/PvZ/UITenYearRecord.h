
/*
 * UITenYearRecord.h
 *
 *  Created on: 2023-7-20
 *      Author: admin
 */

#ifndef UITENYEARRECORD_H_
#define UITENYEARRECORD_H_

#include "UISingletonDialog.h"
#include "NetworkData.h"
#include "Image.h"

enum TenYearRecordButtonId
{
    TEN_YEAR_RECORD_CLOSE = 100,
    TEN_YEAR_RECORD_SHARE,
    TEN_YEAR_RECORD_NEXT,
    TEN_YEAR_RECORD_RECEIVE,
    TEN_YEAR_RECORD_START
};
struct Pvprank
{
        int big;
        int small;
        int star;
};
struct TenYearRecordData
{
    int m_diy_level_count;
    Pvprank m_pvprank;
};

class NetworkTenYearRecordData : public INetworkData
{
public:
    RT_CLASS_DEFINE(NetworkTenYearRecordData, INetworkData, RtClass);
    int m_currentActivityID;// current period activity round.
    int receive;
    TenYearRecordData playinfo;
};

struct Tenyear_BonusInfo
{
    int32 objectId;
    int32 Quantity;
    int32 probability;
};

class Tenyear_BillingReward : public INetworkData
{
public:
    RT_CLASS_DEFINE(Tenyear_BillingReward, INetworkData, RtClass);
    // int32 objectId;
    // int32 Quantity;
    // int32 probability;
    Tenyear_BonusInfo billing;
};


class TenYearRecordInfoPage : public Sexy::Widget
{
public:
    
	TenYearRecordInfoPage(UIWidgetImage* i_backimageWidget);
	virtual ~TenYearRecordInfoPage();
    
    int             GetPageIndex();
    void            SetPageIndex(int i_indexPage);
	
	//virtual void    Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Sexy::Graphics* i_g);
    
    int UnlockedWorldCount(PlayerInfo* i_info);
    // void SetBackImageWidget(UIWidgetImage* i_backimageWidget) {back_imageWidget = i_backimageWidget;}
    // void    Setrecord(UITenYearRecord* i_record) { m_record = i_record}
private:
    
    void            setupScreen();
    
private:
    
    int             m_indexPage;
    
    SexyString      m_Name;
    SexyString      m_TimeCreate;
    SexyString      m_artifact;
    SexyString      m_strType;

    int             m_days;
    int             m_worldNum;
    
    int             m_zombieNum;
    int             m_startNum;
    
    int             m_plantNum;

    int             m_avatarNum;

    // 家族
    int             m_artifactNum;
    int             m_artifactmaxNum;
    int             m_artifactlevel;
    int             m_activatedFamily;
    int             m_customer;
    time_t          time_start;
public:
    bool m_receiveflag; 
    TenYearRecordData m_playinfo;
    int             m_rand; 
    UIWidgetImage* back_imageWidget;
    std::vector<std::string> m_maplist;
    // UITenYearRecord* m_record;
};



class UITenYearRecord : public UISingletonDialog<UITenYearRecord>
{
public:
	UITenYearRecord();
	virtual ~UITenYearRecord();
public:
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UITenYearRecord"; }
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

    TenYearRecordInfoPage * m_page;
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
