//
//  GetGemsRestoreUI.h
//  PlantsVersusZombies2
//
//  Created by Peteo Chen on 13-8-31.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GetGemsRestoreUI__
#define __PlantsVersusZombies2__GetGemsRestoreUI__

#include "Core.h"
#include "PVZ2UIDialog.h"
#include "PrimeTextWidget.h"
#include "EditListener.h"
#include "EditWidget.h"
#include "NetworkServiceManager.h"

enum RestorePlantLevel
{
	FIRST_LEVEL = 1,
	SECOND_LEVEL,
	THIRD_LEVEL,
};

enum RestorePlantType
{
	PLANT_WINTERMELON,
	PLANT_CIRTON,
	PLANT_PEAPOD,
	PLANT_SNOWPEA,
	PLANT_HOLONUT,
	PLANT_TURNIP,
	PLANT_STARFRUIT,
	PLANT_TORCHWOOD,
	PLANT_LIGHTNINGREED,
	PLANT_BONKCHOY,
	PLANT_LASER_BEAN,
	PLANT_SNAPDRAGON,
};

struct CompensatedAward
{
	int typeId;
	std::string plant;
	int plantLevel;
	int plantPieceCount;
	int avatarPieceCount;
    int coinCount;
    int gemCount;
    std::string awardTitle;
	std::string awardDescription;
    CompensatedAward();
};

class CompensatedAwardList : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE(CompensatedAwardList, Sexy::RtObject, Sexy::RtClass);

	bool AddCompensatedAward(int typeID, std::string& description);
    const CompensatedAward* GetItem(int typeID);
private:
	std::vector<CompensatedAward> awardList;
};
enum RestoreType
{
    RESTORE_GEM = -1,
    RESTORE_DOUBLE_SPEED,
    RESTORE_CHERRY_BOMB,
    RESTORE_DOUBLE_COIN,
    RESTORE_DOUBLE_GACHA,
    RESTORE_AUTO_COLLECT_SUN,
    RESTORE_THREEPEATER_AVATAR,
    RESTORE_CHERRY_BOMB_AVATAR,
    RESTORE_ICEBURG_AVATAR,
    RESTORE_CARROTLAUNCHER_PIECE,
    RESTORE_WINTERMELON_SECOND = 11,
    RESTORE_WINTERMELON_THIRD,
    RESTORE_CITRON_SECOND,
    RESTORE_CITRON_THIRD,
    RESTORE_PEAPOD_SECOND,
    RESTORE_PEAPOD_THIRD,
    RESTORE_SNOWPEA_SECOND,
    RESTORE_SNOWPEA_THIRD,
    RESTORE_HOLONUT_SECOND,
    RESTORE_HOLONUT_THIRD,
    RESTORE_TURNIP_SECOND,
    RESTORE_TURNIP_THIRD,
    RESTORE_STARFRUIT_SECOND,
    RESTORE_STARFRUIT_THIRD,
    RESTORE_TORCHWOOD_SECOND,
    RESTORE_TORCHWOOD_THIRD,
    RESTORE_LIGHTNINGREED_SECOND,
    RESTORE_LIGHTNINGREED_THIRD,
    RESTORE_BONKCHOY_SECOND,
    RESTORE_BONKCHOY_THIRD,
    RESTORE_LASERBEAN_SECOND,
    RESTORE_LASERBEAN_THIRD,
    RESTORE_SNAPDRAGON_SECOND,
    RESTORE_SNAPDRAGON_THIRD,
};

class GetGemsRestoreUI : public Sexy::Widget, public Sexy::ButtonListener, public Sexy::EditListener, public Sexy::NetworkServiceListener
{
public:
    
	GetGemsRestoreUI();
	virtual ~GetGemsRestoreUI();
	
	virtual void	Update();
	virtual void	Draw(Sexy::Graphics* i_g);
    virtual void    DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);

	void            RequestRechargeCheck(int i_retries = 0);
	void            TryRequest();
	void            OnRequestFinished(std::string i_json);

	void            ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context);
	void            ServiceRequestFailed(const Sexy::StructuredData* i_response, const void* i_context);
	void            ServiceRequestCompleted(ImageLib::Image*&, const void* i_context);
	void            ServiceRequestCompleted(const Sexy::Buffer*, const void* i_context);
    
	virtual void    EditWidgetText(int i_id, const SexyString& i_string);
	virtual bool    AllowChar(int i_id, SexyChar i_char);

    void            onServiceRequestCompleted(int result, int gems, RestoreType typeId);
    
private:
    
    void setupScreen();
    
    void systemBusy();

    void drawShadedBox(Graphics* i_g, Rect extents);
    
    void GetBag(int gems);
    void GetDoubleSpeedUp();
    void GetCherryBomb();
    void GetDoubleCoin();
    void GetDoubleLottery();
    void GetAutoCollectSun();

    //avatar
    void GetThreepeaterAvatar();
    void GetCherryBombAvatar();
    void GetIceburgAvatar();

    //plant piece
    void GetCarrotLauncherPiece();

    //avatar and plant level
    void GetPlantAvatarAndLevel(RestorePlantType i_type, RestorePlantLevel i_level);

    void onCloseDialog();
    void onCloseDialogAndCloseSelf();

private:
    
    class PVZ2UIEditWidget*         m_editWidget;
    
    PVZ2UIButton * 					m_button_cancel;
    PVZ2UIButton * 					m_button_ok;
    PVZ2UIButton * 					m_button_get;
    Sexy::Rect                      m_rectDialog;
    
    bool							m_IsBusy;
    bool                            m_inputting = false;
    pvztime_t 						m_busyWaitingTime;

    bool           					m_haveGet;
    int32                 			m_retriesLeft;
    int32              				m_randomSeed;
    Image*							m_giftImage;
    SexyString						m_giftTitle;
    SexyString						m_giftDesc;

};

#endif /* defined(__PlantsVersusZombies2__GetNewerBagUI__) */
