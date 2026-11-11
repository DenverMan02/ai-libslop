//
//  ActivityManager.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2016.7.20
//  Copyright (c) 2016 PopCap Games. All rights reserved.
//

#ifndef _ActivityManager_h_
#define _ActivityManager_h_

#include "Singleton.h"

enum ActivityTypeID {
	Activity_All = 0,
	Activity_Spring_Sale = 10601,
	Activity_Old_OneYuan = 10602,
	Activity_New_OneYuan = 10603,
	Activity_Summer_Boss = 10604,
	Activity_Summer_Fire = 10605,
	Activity_Summer_Ice = 10606,
	Activity_Summer_PlantComposit = 10607,
	Activity_Levels = 10608,
	Activity_Anniversary = 10609,
	Activity_LimitedGacha = 10610, // 限时宝物
	Activity_WorldUnlockPack = 10611,
	Activity_Anniversary_2nd = 10612,
	Activity_BossChallenge = 10613, // 挑战僵博
	Activity_NewGacha = 10614,
	Activity_Ads = 10615,
	Activity_First_Recharge = 10616, // 首充礼包
	Activity_Recharge_Reward = 10617,
	Activity_Consumption_Reward = 10618,
	Activity_BossChallengeMedalLottery = 10619,
	Activity_DailySign_TW4399 = 10620,
	Activity_Anniversary_General = 10621,// 充值有礼
	Activity_DangerRoom = 10622,
	Activity_Special_Gem_Offer = 10623,
	Activity_TransGenosis = 10624,
	Activity_DinosaurDanger = 10626,
	Activity_RechargeBundle = 10627, // 限时礼包
	Activity_SpringShop = 10628,
	Activity_RedPacket = 10629,
	Activity_PlantTree = 10782, // 快乐植树（植树节）已移除，新的植树节 Activity_ArborDay
	Activity_ChildrenDay = 10640,
	Activity_SummerEvent = 10641,
	Activity_TimeTravel = 10642,
	Activity_PlantDefence = 10643,
	Activity_ChildrenDay2018 = 10644,
	Activity_WechatShare = 10650,
	Activity_StoneLottery = 10651,
	Activity_DaveClub = 10652,
	Activity_PlantBundle = 10653,
	Activity_NationalHolidayLottery = 10654,
	Activity_7DaysLoginReward = 10660,
	Activity_NationalHoliday = 10661,
	Activity_NationalShop = 10655,
	Activity_NationalBundle = 10662,
	Activity_MiniGameBundle = 10670,
	Activity_MiniGameRank = 10672,
	Activity_ChristmasReward = 10673,
	Activity_ChristmasChargeReward = 10675,
	Activity_BossChallengeMedalLotteryNew = 10674,
	Activity_Chrismas = 10677,
	Activity_FestivalEvent = 10680,
	Activity_SpringDailyReward = 10693,
	Activity_LanternRiddle = 10682,
	Activity_FestivalRechargeReward = 10683,
	Activity_YuanBaoEvent = 10684,
	Activity_FestivalRedPacket = 10685,
	Activity_FestivalShop = 10686,
	Activity_FestivalLottery = 10687,
	Activity_FirstRecharge = 10689,// 地图右上角的首充礼包
	Activity_Plant_Special_Offer = 10688, // 感恩礼包
	Activity_Turn_charge = 10691,
	Activity_FestivalDragonBoat = 10690,
	Activity_worldCup = 10692,
	Activity_RechargeReward = 10694,// 充值返利
	Activity_NationdayEntrance2018 = 10700, // 国庆活动总入口
	Activity_NationdayWheelLuck2018 = 10701, // 幸运欢乐转 (钻石转盘)
	Activity_NationdayDailyWelfare2018 = 10702, // 每日领福利
	Activity_NationdayChargeBonus2018 = 10703, // 充值免费送
	Activity_Joust = 10704,
	Activity_BossChallengeMedalLottery5th = 10707,
	Activity_5th = 10705,
	Activity_5th_Shop = 10706,
	Activity_Web_Game = 10708,
	Activity_LimitLottery = 10801, // 限定幸运大转盘
	Activity_Recall_Offer = 10709,
	Activity_Daily_Sign_Activity = 10710, // 累计签到
	Activity_NewYear_2018 = 10711,
	Activity_NewYear_2018_GameShop = 10712,
	Activity_NewYear_2018_Game = 10713,
	Activity_NewYear_2018_Recharge = 10715,
	Activity_NewYear_2018_Lottery = 10716,

	Activity_FestivalEvent_2019 = 10835, // this is for festival entrance, last is 10819
	Activity_FestivalCracker_2019 = 10774, // 点爆竹
	Activity_FestivalDailyRecharge_2019 = 10719,
	Activity_FestivalOneYuan_2019 = 10759, // 一元礼包
	Activity_FestivalRedPacket_2019 = 10775, // 新春红包
	Activity_Festival_Monthly_Card_Try_2019 = 10722, // 月卡体验
	Activity_FestivalRechargeReward_2019 = 10723, // 累冲送好礼（累计充值）
	Activity_Festival_Piggy_Bank_2019 = 10820, // 小猪存钱罐
	Activity_Festival_Game_2019 = 10725, // 活动入口
	Activity_SpringDailyReward_2019 = 10726,
	Activity_LimitGroupBuy = 10728, // 团购
	Activity_LimitGroupBuy_ReturnGems = 10729,
	Activity_VaseBreaker = 10872, // 破罐大师, last is 10867
	Activity_BossChallengeMedalLotterySpring = 10799,// 挑战僵博转盘
	Activity_PlatformGift = 10737, // 渠道礼包
	Activity_ChildrenDay2019 = 10762, //last is 10742,
	Activity_Newer_Present = 10739, // 新手礼包
	Activity_TravelLog = 10744, // 旅行原木
	Activity_WorldCup_2019 = 10745, // 足球赛
	Activity_WorldCup_2019_Shop = 10767, // 足球赛商店
	Activity_Recall_Offer_2019_June = 10748, // 回归礼包
	Activity_DaveTreasure = 10749, // 戴夫的神秘宝藏
	Activity_PennyGuide = 10803, // 潘妮的追击指南
	Activity_Festival_MiniGame_2019 = 10754, // 迷你小游戏(趣味竞赛)
	Activity_Spring_ConsumeAndReceive = 10752, // 消耗兑换（植物）
	Activity_Spring_Lottery = 10804, // 幸运转盘 （限时转盘）
	Activity_Spring_RechargeReward = 10741, // 每日充值
	Activity_National_LevelOfDay_Entrance = 10761, // 7日挑战活动（复兴挑战）
	Activity_ConsumeAndReceiveExtra = 10769, // 消耗兑换（装扮）
	Activity_RichMan = 10771, // 大富翁
	Activity_TheaterShop = 10772, // 大富翁商店
	Activity_LuckBag = 10779, // 新春福袋
	Activity_Anniversary_Treasure = 10810, //周年寻宝
	Activity_DangerRoomSpecialOffer = 10780,
	Activity_TransGenosis_BlackList = 10781,
	Activity_SecretGacha = 10788,
	Activity_RechargeDailySignActivity = 10796, // 7日充值签到
	Activity_DiscountShopActivity = 10797, // 折扣奖池活动
	// now max activity id is up to 10791
	Activity_HappyVaseBreaker = 10790, // 欢乐砸罐子
	Activity_NoviceSevenDays = 10828, // 新手7日指南
	Activity_NewRecall_Entrance = 10791, //老玩家回归入口
	Activity_NewRecall_Sign = 10792,
	Activity_NewRecall_Bank = 10793,
	Activity_NewRecall_Bundle = 10794,
	// now max activity id is up to 10757
	Activity_Rift = 10800,
	Activity_CardGame = 10853,
	Activity_NewPVP = 10859,
	Activity_NewPVP_BattlePass = 10861,
	Activity_SecretStore = 10802,//神秘商店
	Activity_PlantAdventure = 10808,// now plant adventure move to activity icons
	Activity_MysteryStore = 10809,//水晶商店
	Activity_VivoGacha = 10813,
	Activity_MonthlyCardSpecial = 10815,// 月卡特惠
	Activity_FightZodiac = 10821, //打年兽
	Activity_CallofWish = 10831, //心愿召唤
	Activity_CustomVoting = 10814,//定制团购
	Activity_RechargeWelfare = Activity_FestivalEvent_2019,// 消耗送礼
	Activity_ScrollBanner = 10829,// 地图滚动banner按钮
	Activity_Artifact_Present = 10832, // 神器礼包
	Activity_PlayerSurvey = 10833, // 问卷调查
	Activity_PVZ1_Mode = 10836,// 回忆之旅
	Activity_PVZ1_Achievement = 10839,// 回忆之旅成就
	Activity_CustomLevel = 10840,// 创意庭院
	Activity_SpringFestivalGoldenEgg = 10841,//春节新年开金蛋
	Activity_PennyClassroom = 10843, // 潘妮课堂
	Activity_ArborDay = 10844,//植树节活动
	Activity_PVP = 10846,// pvp
	Activity_PVP_Shop = 10847,// pvp shop
	Activity_GrowthPackage = 10848,//成长礼包
	Activity_UnchartedMode = 10849,// uncharted mode
	Activity_BattleOrder = 10851,// 战令
	Activity_LimitedSummon = 10854,// 限时召唤
	Activity_LimitedSummon_Settle = 10855,// 限时召唤结算
	Activity_Carnival = 10858,// 狂欢嘉年华
	Activity_NewYearGoods = 10860,// 年货商店
	Activity_WorldLevelPackage = 10862, // 潘妮纪行
	Activity_Cornucopia = 10863, // 聚宝盆
	Activity_WishingPool = 10866, // 幸运许愿池
	Activity_InvitationRewards = 10868, // 邀请有礼
	Activity_PlantCultivate = 10871, // 植物培育
	Activity_GiftFoReturn = 10870, // 老玩家回归
	Activity_TenYearRecord = 10869, //十周年回顾
	Activity_PartyAssist = 10873, // 派对助力
	Activity_NewPlayerCollection = 10874, //新手活动合集
	Activity_NewPlayerSign = 10875, //新手签到
	Activity_NewPlayerDiscountShop = 10876, //新手折扣商店
	Activity_NewPlayerSpecialGift = 10877, //新手特惠礼包
	Activity_DaveKitchen = 10878, //戴夫厨房
	Activity_DragonTreasure = 10879, //龙族宝库
	Activity_NewYearGiftBox = 10880, //新年礼盒
};

//-----------------------------------------------------------------
// ActiveItem
//-----------------------------------------------------------------
class ActiveItem: public Sexy::RtObject {
public:
	RT_CLASS_DEFINE(ActiveItem, Sexy::RtObject, Sexy::RtClass);

	void RefreshDate();
	bool IsValid() const {
		return m_id > 0;
	}

	bool GetDataSerialized(Sexy::RtObject& i_data); // support any class inherit from Sexy::RtObject

	int GetLeftDays() const;
	int GetLeftTimes() const; // to second

	void Notify();
public:
	int m_id = 0;
	std::string m_version;
	bool m_bOpen = false;
	std::string m_strStartDate;
	std::string m_strEndDate;
	std::string m_strNewStartDate;
	std::string m_strNewEndDate;
	std::string m_jsonData;

	// not json
	time_t m_startDate = 0;
	time_t m_endDate = 0;
	int m_actionPopupNum = 1;

	//update notice
	std::function<void(ActiveItem*)> m_notice;
};

//-----------------------------------------------------------------
// ActivityManager
//-----------------------------------------------------------------
class ActivityManager: public LazySingleton<ActivityManager> {
public:
	ActivityManager();
	virtual ~ActivityManager();

	void Reset();
	void Initialse();
	void Update();
	bool IsInit() const {
		return m_bInit;
	}
	void Request(int i_id, bool i_wait = false, int i_client_status = 0);
	bool IsRequesting() const {
		return m_timerRequest > 0;
	}
	bool SerializeMessage(const std::string& i_json,
			std::set<int>& o_activeList);

	ActiveItem GetActiveItem(int i_id);
	void SetActivityPopuped(int i_id);

	//update notice
	void SetActiveUpdateNotice(int i_id,
			std::function<void(ActiveItem*)> i_notice);

	// common functions for all
	void RequestUseGem(int i_actID, int i_count = 1, bool i_bWait = true); // v209
	void OnBuyItemFinish(class MsgResultInfo* io_result,
			const class S2C_ICloud_GetConsumeGemInfo* pInfo,
			const class S2C_PlayerInfo* pGemChanged);

protected:
	void onNetworkError(int erroId);
	void onNotifyRefreshActivityList(bool i_success,
			const std::set<int>& changeList);

private:
	void InitLevelOfTheDayActivity(ActivityTypeID id,
			const std::set<int>& changeList);

private:
	bool m_bInit = false;
	float m_timerRequest = -1;
	std::map<int, ActiveItem> m_ItemList;
};

#define gActivityManager (ActivityManager::GetInstancePtr())

#endif
