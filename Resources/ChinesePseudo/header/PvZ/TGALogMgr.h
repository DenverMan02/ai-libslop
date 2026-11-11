/*
 * TGALogMgr.h
 *
 *  Created on: 2019-9-26
 *      Author: Administrator
 */

#ifndef TGALOGMGR_H_
#define TGALOGMGR_H_

#include "Singleton.h"
#include "LogCollector.h"
#include "NetworkServiceManager.h"
#include "TimeMgr.h"

typedef struct PlantAdventureInfo PlantAdventureInfo_S;

// default log id
const int TGA_LOG_LEVEL_FIGHT_ID = 10003;
const int TGA_LOG_LEVEL_ACTIVITY_FIGHT_ID = 10010;
const int TGA_LOG_DAVE_TREASURE_ID = 10031;
const int TGA_LOG_MINIGAME_ID = 10030;
const int TGA_LOG_RECHARGE_REWARD_ID = 10029;
const int TGA_LOG_DIAMOND_ID = 10026;
const int TGA_LOG_PURCHASE_ID = 10025;
const int TGA_LOG_PLANT_LEVELUP_ID = 10023;
const int TGA_LOG_NEWUSER_PRESENT_ID = 10019;
const int TGA_LOG_DAILY_SIGN_ID = 10009;
const int TGA_LOG_COIN_ID = 10013;
const int TGA_LOG_PENNY_TREASURE_ID = 10014;
const int TGA_LOG_TRAVEL_LOG_ID = 10018;
const int TGA_LOG_PLANT_TRIAL_ID = 10022;
const int TGA_LOG_TRANSGENOSIS_ID = 10015;
const int TGA_LOG_JOUST_ID = 10017;// battle z
const int TGA_LOG_ENDLESS_ID = 10016;
const int TGA_LOG_PLANT_SPECIAL_OFFER_ID = 10039;
const int TGA_LOG_LIMITED_GACHA_ID = 10037;
const int TGA_LOG_LIMITED_LOTTERY_ID = 10036;
const int TGA_LOG_RECHARGE_BUNDLE_ID = 10040;
const int TGA_LOG_GROUP_BUY_ID = 10035;
const int TGA_LOG_VASEBREAKER_ID = 10033;
const int TGA_LOG_CONSUMERECEIVE_ID = 10055;
const int TGA_LOG_MINOR_LOTTERY_ID = 10042;
const int TGA_LOG_AD_ID = 10032;
const int TGA_LOG_RICHMAN_ID = 10046;
const int TGA_LOG_LUCKBAG = 10045;
const int TGA_LOG_DANGERROOM_SPECIAL_OFFER_ID = 10043;
const int TGA_LOG_PLANTINFO_REFRESH_ID = 10044;
const int TGA_LOG_ONE_YUAN_RED_PACKET_ID = 10047;
const int TGA_LOG_PIGGYBANK_ID = 10048;
const int TGA_LOG_FESTIVAL_RED_PACKET_ID = 10049;
const int TGA_LOG_CRACK_ID = 10050;
const int TGA_LOG_DAILYSIGN_ACTIVITY_ID = 10051;
const int TGA_LOG_DAILY_RECHARGE_ID = 10053;
const int TGA_LOG_CONSUMERECEIVE_EXTRA_ID = 10054;
const int TGA_LOG_HAPPY_VASE_BREAKER_ID = 10057;
const int TGA_LOG_SECRET_GACHA_ID = 10058;
const int TGA_LOG_RENAISSANCE_CHALLENGE_ID = 10060;
const int TGA_LOG_BOSS_CHALLENGE_ID = 10059;
const int TGA_LOG_RECHARGE_DAILYSIGN_ACTIVITY = 10062;
const int TGA_LOG_DISCOUNT_SHOP_ACTIVITY = 10063;
const int TGA_LOG_NEWRECALL_SIGN = 10064;
const int TGA_LOG_NEWRECALL_BANK = 10065;
const int TGA_LOG_NEWRECALL_BUNDLE = 10066;
const int TGA_LOG_SECRET_STORE = 10067;
const int TGA_LOG_PENNY_PURSUIT = 10068;
const int TGA_LOG_IOS_REAL_NAME_LOGIN = 10070;
const int TGA_LOG_ANNIVERSARY_TREASURE = 10069;
const int TGA_LOG_FIRSTRECHARGE = 10008;
const int TGA_LOG_MYSTERY_STORE = 10071;
const int TGA_LOG_MONTHLY_CARD_SPECIAL = 10072;
const int TGA_LOG_CUSTOM_VOTING = 10073;
const int TGA_LOG_FIGHT_ZODIAC = 10074;
const int TGA_LOG_FOOL_CHALLENGE = 10075;
const int TGA_LOG_BAG = 10076;
const int TGA_LOG_ADS_LOTTERY = 10077;
const int TGA_LOG_NOVICESEVENDAYS_TASK = 10079;
const int TGA_LOG_TUTORIAL = 10080;
const int TGA_LOG_PLAYER_SURVEY = 10082;
const int TGA_LOG_SCROLLBANNER = 10090;
const int TGA_LOG_ARTIFACT_PRESENT = 10081;
const int TGA_LOG_CALL_OF_WISH_DRAW = 10083;
const int TGA_LOG_CALL_OF_WISH_TASK = 10084;
const int TGA_LOG_CALL_OF_WISH_DAILY = 10085;
const int TGA_LOG_CALL_OF_WISH_LIMIT = 10086;
const int TGA_LOG_CALL_OF_WISH_GIFT = 10087;
const int TGA_LOG_CALL_OF_WISH_TRAIN = 10088;
const int TGA_LOG_ARTIFACT_CULTIVATION = 10089;
const int TGA_LOG_PVZ1MODE = 10091;
const int TGA_LOG_PVZ1ACHIEVEMNET = 10092;
const int TGA_LOG_CUSTOMLEVEL = 10093;
const int TGA_LOG_GOLDENEGG = 10094;
const int TGA_LOG_ARBORDAY = 10117;
const int TGA_LOG_EXCHANGE_ACCESSORY = 10096;
const int TGA_LOG_PENNYCLASSROOM = 10097;
const int TGA_LOG_ONLINE = 10098;
const int TGA_LOG_PLAYER_RETURN = 10099;
const int TGA_LOG_GROWTHPACKAGE = 10100;
const int TGA_LOG_UNCHARTED_MODE = 10135;
const int TGA_LOG_CUSTOM_LEVEL_AD = 10102;
const int TGA_LOG_CLEAR_PROFILE = 10103;
const int TGA_LOG_DEBUG_INFO = 10104;
const int TGA_LOG_BATTLE_ORDER = 10105;
const int TGA_LOG_ACCOUNT_REMOVE = 10106;
const int TGA_LOG_CARD_GAME = 10107;
const int TGA_LOG_LAUNCH_APP = 10108;
const int TGA_LOG_CUSTOM_LEVEL_SHARE = 10110;
const int TGA_LOG_LIMITED_SUMMON = 10111;
const int TGA_LOG_CARNIVAL = 10112;
const int TGA_LOG_NEWYEAR_GOODS = 10113;
const int TGA_LOG_GENE_ENHANCEMENT = 10115;
const int TGA_LOG_NEW_PVP = 10116;
const int TGA_LOG_NEW_PVP_PLUS = 10119;
const int TGA_LOG_LEVEL_PACKAGE = 10118;
const int TGA_LOG_CORNUCOPIA = 10121;
const int TGA_LOG_WISHINGPOOL = 10122;
const int TGA_LOG_PLANT_DECORATE = 10024;
const int TGA_LOG_GIFT_RETURN = 10123;
const int TGA_LOG_TEN_YEARS = 10124;
const int TGA_LOG_INVITATION = 10125;
const int TGA_LOG_ANNIVERSARY_NURTURING = 10126;
const int TGA_LOG_PARTY_ASSIST = 10127;
const int TGA_LOG_NEWPLAYER_COLLECTION = 10128;
const int TGA_LOG_DAVEKITCHEN = 10130;
const int TGA_LOG_DRAGONTREASURE = 10131;
const int TGA_LOG_FIRSTRECHARGE_NEW = 10132;
const int TGA_LOG_HEROPLANT = 10134;

/////////////////////////////
/// TGA LOG ENUM
/////////////////////////////

/// custom level
enum {
	TGA_LOG_CUSTOM_LEVEL_ENTER = 1,
	TGA_LOG_CUSTOM_LEVEL_MOSTPLAY = 2,
	TGA_LOG_CUSTOM_LEVEL_MOSTLIKE = 3,
	TGA_LOG_CUSTOM_LEVEL_MY_FAVOURITE = 4,
	TGA_LOG_CUSTOM_LEVEL_SEARCH = 5,
	TGA_LOG_CUSTOM_LEVEL_SEARCH_CONFIRM = 6,
	TGA_LOG_CUSTOM_LEVEL_FILTER = 7,
	TGA_LOG_CUSTOM_LEVEL_FILTER_CONFIRM = 8,
	TGA_LOG_CUSTOM_LEVEL_REFRESH = 9,
	TGA_LOG_CUSTOM_LEVEL_COMBOBOX = 10,
	TGA_LOG_CUSTOM_LEVEL_LEVEL_FAVOURITE = 11,
	TGA_LOG_CUSTOM_LEVEL_LEVEL_UNFAVOURITE = 12,
	TGA_LOG_CUSTOM_LEVEL_LEVEL_DOWNLOAD = 13,
	TGA_LOG_CUSTOM_LEVEL_LEVEL_CHALLENGE = 14,
	TGA_LOG_CUSTOM_LEVEL_LEVEL_CHALLENGE_RESULT = 15,
	TGA_LOG_CUSTOM_LEVEL_LEVEL_CREATE = 16,
	TGA_LOG_CUSTOM_LEVEL_LEVEL_CREATE_SET = 17,
	TGA_LOG_CUSTOM_LEVEL_LEVEL_DETAIL = 18,
	TGA_LOG_CUSTOM_LEVEL_TUTORIAL_FINISH = 19,
	TGA_LOG_CUSTOM_LEVEL_SHOP = 20,
	TGA_LOG_CUSTOM_LEVEL_SHOP_BUY = 21,
	TGA_LOG_CUSTOM_LEVEL_GUESS_LIKE = 22,
	TGA_LOG_CUSTOM_LEVEL_MOTIVATE = 23,
};

enum {
	TGA_LOG_CREATE_LEVEL_CREATE = 1,
	TGA_LOG_CREATE_LEVEL_SAVE_LEVEL = 2,
	TGA_LOG_CREATE_LEVEL_DELETE = 3,
	TGA_LOG_CREATE_LEVEL_UPLOAD = 4,
	TGA_LOG_CREATE_LEVEL_COPY_ENABLE = 6,
	TGA_LOG_CREATE_LEVEL_COPY_DISABLE = 7,
};

/// penny classroom
enum {
	TGA_LOG_PENNY_CLASSROOM_ENTER = 1,
	TGA_LOG_PENNY_CLASSROOM_TRAINING_RESULT = 2,
	TGA_LOG_PENNY_CLASSROOM_EXCHANGE_ITEM = 3,
};

/// uncharted
enum {
	TGA_LOG_UNCHARTED_ENTER = 1,
	TGA_LOG_UNCHARTED_ENDLEVEL = 2,
	TGA_LOG_UNCHARTED_UNLOCK_LEVEL = 3,
	TGA_LOG_UNCHARTED_REWARD = 4,
	TGA_LOG_UNCHARTED_BUY_FESTIVAL_REWARD = 5,
	TGA_LOG_UNCHARTED_FESTIVAL_REWARD = 6,
	TGA_LOG_UNCHARTED_TASK_REWARD = 7,
	TGA_LOG_UNCHARTED_GET_SPECIAL_BONUS = 8,
	TGA_LOG_UNCHARTED_LEVEL_START = 9,
	TGA_LOG_UNCHARTED_BOOST_CHOOSE_CARD = 10,
};

// diy ad
enum
{
	TGA_LOG_DIY_AD_REQUEST = 1,
	TGA_LOG_DIY_AD_SUCCESS = 2,
	TGA_LOG_DIY_AD_CLICKED = 3,
	TGA_LOG_DIY_AD_FINISHED = 4,
	TGA_LOG_DIY_AD_CLOSED = 5,
	TGA_LOG_DIY_AD_FAILED = 6
};

// new pvp
enum
{
	TGA_LOG_NEW_PVP_ENTER = 1,
	TGA_LOG_NEW_PVP_CLICK_AREA_HOW_TO_PLAY = 2,
	TGA_LOG_NEW_PVP_CLICK_OVERVIEW = 3,
	TGA_LOG_NEW_PVP_CLICK_TASK = 4,
	TGA_LOG_NEW_PVP_CLICK_PLAY = 5,
	TGA_LOG_NEW_PVP_MATCHING = 6,
	TGA_LOG_NEW_PVP_MATCHED = 7,
	TGA_LOG_NEW_PVP_CANCEL_MATCHING = 8,
	TGA_LOG_NEW_PVP_END_PLAY = 9,
	TGA_LOG_NEW_PVP_TIMOUT = 10,
	TGA_LOG_NEW_PVP_UNLOCK_RANK_REWARD = 11,
	TGA_LOG_NEW_PVP_GET_RANK_REWARD = 12,
	TGA_LOG_NEW_PVP_SEASON_REWARD = 13,
	TGA_LOG_NEW_PVP_GET_SEASON_REWARD = 14,
	TGA_LOG_NEW_PVP_GET_TASK_EXP = 15,
	TGA_LOG_NEW_PVP_BUY_ITEM_EXP = 16,
	TGA_LOG_NEW_PVP_OPEN_CHEST = 17,
	TGA_LOG_NEW_PVP_ACTIVATE_BATTLE_PASS = 18,
};

// new pvp plus
enum
{
	TGA_LOG_NEW_PVP_GET_DAILY_CHEST = 1,
	TGA_LOG_NEW_PVP_GET_WEEKLY_CHEST = 2,
	TGA_LOG_NEW_PVP_SHOP_BUY = 3,
	TGA_LOG_NEW_PVP_SAVE_BATTLE_INFO = 4,
	TGA_LOG_NEW_PVP_LEVEL_UP_ZOMBIE = 5,
};

// arbor day
enum {
	TGA_LOG_ARBORDAY_WATER = 1,
	TGA_LOG_ARBORDAY_KETTLE_REWARD,
	TGA_LOG_ARBORDAY_BUY_KETTLE,
	TGA_LOG_ARBORDAY_SEED_REWARD,
	TGA_LOG_ARBORDAY_SEED_REFRESH,
	TGA_LOG_ARBORDAY_PLAYER_PROCESS_REWARD,
	TGA_LOG_ARBORDAY_SERVER_PROCESS_REWARD,
};

// level package
enum {
	TGA_LOG_LEVEL_PACKAGE_ENTER = 1,
	TGA_LOG_LEVEL_PACKAGE_CHOOSE_PACKAGE,
	TGA_LOG_LEVEL_PACKAGE_BUY_PACKAGE,
};

// cornucopia
enum {
	TGA_LOG_CORNUCOPIA_ENTER = 1,
	TGA_LOG_CORNUCOPIA_GACHA,
	TGA_LOG_CORNUCOPIA_PRESENT_BUY,
	TGA_LOG_CORNUCOPIA_BUBBLE_REWARD,
	TGA_LOG_CORNUCOPIA_TASK,
	TGA_LOG_CORNUCOPIA_SHOP,
	TGA_LOG_CORNUCOPIA_RANKING,
};

// plant decorate
enum {
	TGA_LOG_DECORATE_ENTER = 1,
	TGA_LOG_DECORATE_EXCHANGE_AVATAR = 2,
	TGA_LOG_DECORATE_EXCHANGE_ACCESSORY = 3,
	TGA_LOG_DECORATE_SOLD_ACCESSORY = 4,
	TGA_LOG_DECORATE_GET_ACCESSORY = 5,
	TGA_LOG_DECORATE_LEVELUP_ACCESSORY = 6,
};

// party assist
enum {
	TGA_LOG_PARTY_ASSIST_WISH_CHOOSE = 1,
	TGA_LOG_PARTY_ASSIST_ASSIST = 2,
	TGA_LOG_PARTY_ASSIST_RESET = 3,
	TGA_LOG_PARTY_ASSIST_BUY = 4,
	TGA_LOG_PARTY_ASSIST_TASK = 5,
};

// newplayer collection
enum {
	TGA_LOG_NEWPLAYER_COLLECTION_SIGN = 1,
	TGA_LOG_NEWPLAYER_COLLECTION_NOVICESEVENDAY_ENTER,
	TGA_LOG_NEWPLAYER_COLLECTION_DISCOUNTSOHP_ENTER,
	TGA_LOG_NEWPLAYER_COLLECTION_DISCOUNTSOHP_BUY,
	TGA_LOG_NEWPLAYER_COLLECTION_PENNYCLASSROOM_ENTER,
	TGA_LOG_NEWPLAYER_COLLECTION_SPECIALGIFT_ENTER,
	TGA_LOG_NEWPLAYER_COLLECTION_SPECIALGIFT_BUY,
};

// first recharge new
enum {
	TGA_LOG_FIRST_RECHARGE_NEW_ENTER = 1,
	TGA_LOG_FIRST_RECHARGE_NEW_GOT,
};

/////////////////////////////
///         struct
////////////////////////////
struct TGALogPlantDecorate {
	std::string _step = "";
	std::string _exchange_avatar = "";
	std::string _exchange_accessory = "";
	std::string _exchange_avatar_pieces_count = "";
	std::string _buy_cost = "";// exchange accessory
	std::string _sold_cost = "";
	std::string _levelup_accessory_level = "";
	std::string _levelup_accessory_consume = "";

};

struct TGALogDaveTreasureData {
    std::string _itemID = "";// buy item id
    std::string _cost = "";// buy item cost
    std::string _sumItemType = "";// item type which is normal or highlevel
    std::string _sumItemLevel = "";// item level which is 40, 80, 120, 160, 200, 250
    std::string _missionType = "";// everyday, everymonoth, everyweek
    std::string _missionID = "";// mission id
    std::string _missionItemID = "";// mission item id
    std::string _sumItemReward = "";// sum item reward
};

struct TGALogMinigameData {
    std::string _result = "";// win or lose
    std::string _coinsAward = "";// how many coins after battle
    std::string _freeGemNum = "";// how many free gems used
    std::string _payGemNum = "";// how many pay gems used
    std::string _plantPiecesNum = "";
    std::string _changePlantPieceID = "";
    std::string _changePlantPieceNum = "";
    std::string _usedCoinsNum = "";// how many coins used to change plant pieces
};

struct TGALogRechargeRewardData {
    std::string _buyItemID = "";// buy item id
    std::string _cost = "";// buy item cost
    std::string _gemsReward = "";// get how many gems
    std::string _plantPieceID = "";// get plant piece id through buying
    std::string _plantPieceNum = "";// the count of plant pieces through buying
    std::string _getPlantPieceID = "";// free get plant pieces id
    std::string _getPlantPieceNum = "";// the count of free get plant pieces 
};

struct TGALogPurchaseData {
    std::string _itemID = "";// purchase item id
    std::string _cost = "";// purchase cost
    std::string _description = "";// purchase description
    std::string _firstPayTime = "";// first pay time
    std::string _firstPayCost = "";// first pay cost
    std::string _firstPayItem = "";// first pay item
    std::string _firstPayLevel = "";// first pay level
    std::string _totalPay = "";// total pay
};

struct TGALogPlantLevelupData {
    std::string _plantID = "";// unlock or levelup plant id
    std::string _level = "";// plant level
    std::string _usePlantPiecesCount = "";// the count of level up plant pieces
    std::string _levelupCoinsCost = "";// the coins for plant level up
    std::string _levelupNutritionCost = "";// the nutrition for plant level up
    std::string _levelupFreeGemsCost = "";// the gems for plant level up
    std::string _levelupPayGemCost = "";// the pay gems for plant level up
    std::string _levelupSpecialPieceCost = "";// the pay gems for plant level up
};

struct TGALogPennyTreasureData {
    std::string _gachaType = "";// treasure type : 
    std::string _isFree = "";// if item is free
    std::string _gachaTimes = "";// one time or ten times
    std::string _freeGems = "";// free gem count
    std::string _payGems = "";// pay gem count
    std::string _gachaItemDescription = "";// information about gacha item
};

struct TGALogTravelLogData {
    std::string _missionType = "";// mission type
    std::string _missionID = "";// mission id
    std::string _levelID = "";// level id
    std::string _result = "";// win = 1 lose = 2
    std::string _jumpToWorldID = "";// jump to world id
    std::string _missionReward = "";// mission reward
};

struct TGALogTransGenosisData {
    std::string _slots[5] = {"", "", "", "", ""};// slot items
    std::string _transCost = "";// the cost of trans genosis
    std::string _freeGems = "";// how many free gems we use
    std::string _payGems = "";// how many pay gems we use
    std::string _resultPieceID = "";// result piece id
};

struct TGALogJoustData {
    std::string _matchLevel = "";// league level
    std::string _battleResult = "";// battle z result   win = 1, loss = 0
    std::string _freeGems = "";// use free gems
    std::string _payGems = "";// use pay gems
    std::string _useZCoins = "";// use z coins
    std::string _buyChallengeTimes = "";// buy challenge times
    std::string _buyChallengeCost = "";// cost
    std::string _buyPlantID = "";// plant id
    std::string _buyPlantCount = "";// buy plant count
    std::string _reward = "";// get reward
    std::string _plantOnBoard[8] = { "", "", "", "", "", "", "", "" };// the plant on board to fight
    std::string _artifactId = "";
};

struct TGALogEndlessData
{
	std::string _step = "";
	std::string _medalCost = "";
	std::string _coinCost = "";
	std::string _freeGems = "";
	std::string _payGems = "";
	std::string _purchaseID = "";
	std::string _levelID = "";
	std::string _levelResult = "";
	std::vector<std::string> _usedPlants;
	std::string _time = "";
	std::string _artifactId = "";
};

struct TGAPlantSpecialOfferData
{
	std::string _step = "";
	std::string _bundleId = "";
	std::string _cost = "";
	std::string _getCoins = "";
	std::string _getGems = "";
	std::string _plantId = "";
	std::string _avatarId = "";
};

struct TGALimitedGachaData
{
	std::string _step = "";
	std::string _price = "";
	std::string _freeGems = "";
	std::string _paidGems = "";
	std::string _rewards = "";
};

struct TGALimitedLotteryData
{
	std::string _step = "";
	std::string _drawAmt = "";
	std::string _crystalCost = "";
	std::string _bundleId = "";
	std::string _bundlePrice = "";
	std::string _crystalAmt = "";
	std::string _itemId = "";
};

struct TGABundle
{
	TGABundle()
	{
		_quantity = 0;
		_objectId = 0;
	}

	int _quantity;
	int _objectId;
};

struct TGARechargeBundleData
{
	std::string _step = "";
	std::string _rechargeAmt = "";
	std::string _purchaseId = "";
	std::string _purchasePrice = "";
	std::string _coinsAmt = "";
	std::string _gemsAmt = "";
	std::vector<TGABundle> _plantBundles;
	std::vector<TGABundle> _itemBundles;
};

struct TGAGroupBuyData
{
	std::string _step = "";
	std::string _plantId = "";
	std::string _plantQuantity = "";
	std::string _coinAmt = "";
	std::string _usedDaveAmt = "";
	std::string _freeGems = "";
	std::string _paidGems = "";
	std::string _returnGems = "";
};

struct TGAVaseBreakerData
{
	std::string _step = "";
	std::string _levelId = "";
	std::string _result = "";
	std::string _usedSkill = "";
	std::string _coinAmt = "";
	std::string _plantPieceId = "";
	std::string _plantPieceAmt = "";
};

struct TGAConsumeReceiveData
{
	std::string _step = "";
	std::string _gemsAmt = "";
	std::string _plantPieceId = "";
	std::string _plantPieceAmt = "";
	std::string _activityId = "";
	std::string _abtestId = "";
};

struct TGAMinorLotteryData
{
	std::string _step = "";
	std::string _currentLuck = "";
	std::string _afterLuck = "";
	std::string _specialId = "";
	std::string _specialQuantity = "";
	std::string _drawAmt = "";
	std::string _freeGems = "";
	std::string _paidGems = "";
	std::string _getSpecial = "";
	std::string _rewards = "";
};

struct TGARichManData
{
	std::string _step = "";
	std::string _getCoins = "";
	std::string _useCoins = "";
	std::string _useDices = "";
	std::string _rollNum = "";
	std::string _buyDices = "";
	std::string _buyDicesCost = "";
	std::string _getItemId = "";
	std::string _getItemQuantity = "";
};

struct TGALuckBagData
{
	std::string _step = "";
	std::string _plantSelect[6] = { "", "", "", "", "", "" };
	std::string _plantReward[2] = { "", "" };
	std::string _price = "";
};

struct TGADailySignActivity
{
    std::string _step = "";
    std::string _signDays = "";
    std::string _rewards = "";
};

struct TGADailyRechargeReward
{
    std::string _step = "";
    std::string _buyItemID = "";
    std::string _cost = "";
    std::string _plantChipId = "";
	std::string _plantChipamount = "";
    std::string _avatarChipId = "";
	std::string _avatarChipamount = "";
};

struct TGACustomLevelADData
{
    std::string _step = "";
    std::string _level = "";
    std::string _viewId = "";
    std::string _viewType = "";
    std::string _authorId = "";
};

struct TGADangerRoomSpecialOfferData
{
	std::string _step = "";
	std::string _bundleId = "";
	std::string _plantId = "";
	std::string _price = "";
};

struct TGAOneYuanRedPacketData
{
	std::string _step = "";
	std::string _buyAmount = "";
	std::string _price = "";
	std::string _openAmount = "";
	std::string _rewards = "";
};

struct TGAArtifactPresentData
{
	std::string _step = "";
	std::string _artifactId = "";
	std::string _price = "";
	std::string _sku = "";
	std::string _rewards = "";
};

struct TGAPlantData
{
	std::string _plantLevel = "";
	std::string _plantId = "";
};

struct CustomSegment
{
	CustomSegment(int i_index, std::string i_value)
	{
		index = i_index;
		value = i_value;
	}

	int index;
	std::string value;
};

struct TGAPigBankData
{
    std::string _step = "";
    std::string _price = "";
    std::string _gems = "";
    std::string _day = "";
};

struct TGAFestivalRedPacketData
{
    std::string _step = "";
    std::string _isFree = "";
    std::string _freeGems = "";
    std::string _paidGems = "";
    std::string _content = "";
};

struct TGASecretGacha
{
    std::string _step = "";
    std::string _plantId = "";
    std::string _cost = "";
    std::string _rewards = "";
};

struct TGACrackData
{
    std::string _step = "";
    std::string _freeGems = "";
    std::string _paidGems = "";
    std::string _content = "";
};

struct TGAAccountRemove
{
	std::string _step = "";
};

struct TGAAppLaunch
{
	std::string _step = "";
};

struct TGARenaissanceChallengeData
{
    std::string _step = "";
    std::string _itemID = "";
    std::string _itemCount = "";
    std::string _levelID = "";
    std::string _result = "";
    std::string _artifactId = "";
};

struct TGABossChallengeData
{
    std::string _step = "";// D1
    std::string _materialNum = "";// D2
    std::string _buyGemCost = "";// D3
    std::string _buyMaterialNum = "";// D4
    std::string _levelID = "";// D5
    std::string _result = "";// D6
    std::string _getMaterialCount = "";// D7
    std::string _itemID = "";// D8
    std::string _itemCount = "";// D9
    std::string _luckyMaxItemID = "";// D10
    std::string _luckyMaxItemCount = "";// D11
    std::string _lotteryTimes = "";// D12
    std::string _artifactId = "";
};

struct TGARechargeDailySignData
{
    std::string _step = "";
    std::string _day = "";
    std::string _reward = "";
    std::string _gems = "";
};

struct TGADiscountShopData
{
    std::string _step = "";
    std::string _reward = "";
    std::string _freeGems = "";
    std::string _paidGems = "";
};

//////////////////////////
///       class
//////////////////////////

struct TGAHappyVaseBreakerData
{
    std::string _step = "";
    std::string _taskInfo = "";
    std::string _taskAward = "";
    std::string _vaseAwardID = "";
    std::string _vaseAwardAmount = "";
    std::string _isBigAward = "";
    std::string _hammerUse;
};


struct TGANewRecallSignData
{
    std::string _step = "";
    std::string _day = "";
};

struct TGANewRecallBankData
{
    std::string _step = "";
    std::string _rewardId = "";
    std::string _selectId = "";
    std::string _rewardNumber = "";
    std::string _gemNumber = "";
};

struct TGANewRecallBundleData
{
    std::string _step = "";
    std::string _bundleId = "";
    std::string _rewards = "";
    std::string _gemNumber = "";
    std::string _price = "";
};

struct TGASecretStore
{
    std::string _step = "";
    std::string _isFree = "";
    std::string _bundleId = "";
    std::string _cost = "";
    std::string _rewards = "";
    std::string _getGems = "";
};

struct TGAPennyPursuitData
{
    std::string _step = "";
    std::string _levelId = "";
    std::string _difficulty = "";
    std::string _isPass = "";
    std::string _award = "";
    std::string _freeGemReward = "";
    std::string _paidGemReward = "";
    std::string _freeGemUse = "";
    std::string _paidGemUse = "";
    std::string _rank = "";
    std::string _coinUse = "";
    std::string _time = "";
    std::string _artifactId = "";
    std::string _levelIndex = "";
};

struct TGANewPVPData
{
    std::string _step = "";
    std::string _selfMatchingScore = "";
    std::string _rank = "";
    std::string _levelTime = "";
    std::string _oppoentMatchingScore = "";
    std::string _endTurn = "";
    std::string _selectedPlants = "";
    std::string _area = "";
    std::string _endResult = "";
    std::string _endRank = "";
    std::string _upgradeSun = "";
    std::string _upgradeSunTurn = "";
    std::string _addPlant = "";
    std::string _addZombie = "";
    std::string _selectedZombies = "";
    std::string _selectedZombiesDmg = "";
    std::string _zombieUpgradeSpeed = "";
    std::string _zombieUpgradeHP = "";
    std::string _zombieUpgradeBerserk = "";
    std::string _oppoentZombieMergeCount = "";
    std::string _oppoentZombieMergeHighestLevel = "";
    std::string _reward = "";
    std::string _selfProfileId = "";
    std::string _oppoentProfileId = "";
    std::string _taskLevel = "";
    std::string _taskExp = "";
    std::string _isAdv = "";
    std::string _coinAmount = "";
    std::string _coinAmountDelta = "";
    std::string _taskId = "";
    std::string _buyItem = "";
};

struct TGANewPVPPlusData
{
    std::string _step = "";
    std::string _reward = "";
    std::string _cost = "";
    std::string _coinCost = "";
    std::string _inBattleZombies = "";
    std::string _levelUpId = "";
    std::string _levelUpLevel = "";
};

struct TGAAnniversaryTreasureData
{
    std::string _step = "";
    std::string _isFree = "";
    std::string _theAwardInfo = "";
    std::string _getFreeGems = "";
    std::string _getPaidGems = "";
    std::string _useFreeGems = "";
    std::string _usePaidGems = "";
    std::string _poolNumber = "";
    std::string _rewardType = "";
    std::string _rewardInfo = "";
};

struct TGAMysteryStore
{
    std::string _step = "";
    std::string _rewards = "";
    std::string _getType = "";
    std::string _bundleId = "";
    std::string _cost = "";
};

struct TGAFirstRechargeData
{
    std::string _step = "";
    std::string _bonus = "";// all get bonus
    std::string _recharge = "";// not use, but only take a position
    std::string _gems = "";// if get gems in bonus, print here
};

struct TGAMonthlyCardSpecialData
{
    std::string _step = "";
    std::string _itemID = "";// maybe not use
    std::string _cost = "";// item cost
};

struct TGACustomVoting
{
    std::string _step = "";
    std::string _plantId = "";
    std::string _tNumber = "";
    std::string _reward = "";
};

struct TGAFightZodiac
{
    std::string _step = "";
    std::string _crackerTotal = "";
    std::string _crackerUse = "";
    std::string _crackerBehave = "";
    std::string _zodiacHitPoint = "";
    std::string _zodiacIndex = "";
    std::string _reward = "";
    std::string _product = "";
};

struct TGAFoolData
{
    std::string _step = "";
    std::string _isPass = "";
    std::string _eggNum = "";
    std::string _exchangeId = "";
    std::string _exchangeAmount = "";
    std::string _exchangeUseEgg = "";
    std::string _bundlePrice = "";
    std::string _bundleToolsId = "";
    std::string _bundleEggAmont = "";
    std::string _challengeAward = "";
};

struct TGANoviceSevenDaysData
{
    std::string _step = "";
    std::string _newOld = "";
    std::string _day = "";
    std::string _taskId = "";
    std::string _award = "";
};

struct TGABagData
{
    std::string _step = "";
};

struct TGAAdsLotteryData
{
    std::string _step = "";
    std::string _reward = "";
};

struct TGATutorialData
{
    std::string _step = "";// 1 enter 2 complete 3 got reward
    std::string _id = "";// tutorial id
    std::string _reward = "";
};

struct TGAPlayerSurveyData
{
    std::string _step = "";// 1 commit survey
    // std::string _answers = "";// as "xx,xx,xx,xx" all 10 answers
//    std::string _answer1 = "";
//    std::string _answer2 = "";
//    std::string _answer3 = "";
//    std::string _answer4 = "";
//    std::string _answer5 = "";
//    std::string _answer6 = "";
//    std::string _answer7 = "";
//    std::string _answer8 = "";
//    std::string _answer9 = "";
//    std::string _answer10 = "";
    std::vector<std::string> _answers;
    std::string _rewards = "";// bonus
};

struct TGAScrollbannerData
{
    std::string _step = "";// 1 enter event
    std::string _bannerID = "";// 0 festivalevent 1 sevendayguide
};

struct TGACallofWishDraw
{
    std::string _step = "";
    std::string _callTimes = "";
    std::string _useTicket = "";
    std::string _useFreeGem = "";
    std::string _useGem = "";
    std::string _award = "";
    std::string _wishPlantId = "";
};

struct TGACallofWishTask
{
    std::string _step = "";
    std::string _taskId = "";
    std::string _activity = "";
    std::string _gotTicket = "";
    std::string _award = "";
};

struct TGACallofWishDaily
{
    std::string _step = "";
    std::string _price = "";
    std::string _key = "";
    std::string _award = "";
};

struct TGACallofWishLimit
{
    std::string _step = "";
    std::string _price = "";
    std::string _key = "";
    std::string _award = "";
};

struct TGACallofWishGift
{
    std::string _step = "";
    std::string _index = "";
    std::string _callTimes = "";
    std::string _award = "";
};

struct TGACallofWishTrain
{
    std::string _step = "";
    std::string _index = "";
    std::string _award = "";
};

struct TGArtifactCultivation
{
    std::string _step = "";
    std::string _content = "";
    std::string _levelupMat = "";
    std::string _rankupMat = "";
    std::string _artifactId = "";
    std::string _levelorRank = "";
};

struct TGAPVZ1ModeData
{
	std::string _step = "";
	std::string _level = "";
	std::string _difficulty = "";
	std::string _win = "";
	std::string _time = "";
	std::vector<std::string> _usedPlants;
	std::string _levelReward = "";
	std::string _shopReward = "";
};

struct TGAPVZ1Achievement
{
	std::string _step = "";
	std::string _process = "";
	std::string _coin = "";
	std::string _taskId = "";
	std::string _award = "";
};

struct TGACustomLevelData
{
	std::string _step = "";
	std::string _playCoin = "";
	std::string _createCoin = "";
	std::string _playCoinChange = "";
	std::string _createCoinChange = "";
	std::string _worldsFilter = "";
	std::string _levelModeFilter = "";
	std::string _levelID = "";
	std::string _zanCount = "";
	std::string _caiCount = "";
	std::string _createLevelAction = "";
	std::string _createLevelMode = "";
	std::string _shopItemBuy = "";
	std::string _challengeResult = "";
	std::vector<std::string> _usedPlants;
};

struct TGAGoldenEgg
{
	std::string _step = "";
	std::string _eggIndex = "";
	std::string _jackpotSelect = "";
	std::string _hammerNum = "";
	std::string _hammerConsume = "";
    std::string _hammerGotWay = "";
    std::string _taskID = "";
    std::string _award = "";
    std::string _jackpotGot = "";
};

struct TGAPennyClassroomData
{
	std::string _step = "";
	std::string _coin = "";
	std::string _coinChange = "";
	std::string _levelName = "";
	std::string _bonus = "";
	std::string _passLevel = "";
};

struct TGAArborDay
{
    std::string _step = "";
    std::string _kettleNum = "";
    std::string _kettleChange = "";
    std::string _reward = "";
    std::string _taskID = "";
    std::string _useGem = "";
    std::string _freeGem = "";
    std::string _refresh = "";
};

struct TGAccessoryData
{
	std::string _award = "";
};

struct TGAGrowthPackage
{
    std::string _step = "";
    std::string _integralNum = "";
    std::string _integralChange = "";
    std::string _useMoney = "";
    std::string _objectID = "";
    std::string _reward = "";
};

struct TGAUnchartedData
{
	std::string _step = "";
	std::string _star = "";
	std::string _starChange = "";
	std::string _challengeSuccessNum = "";
	std::string _level = "";
	std::string _win = "";
	std::string _reward = "";
	std::string _is_battleorder = "";
	std::string _task_id = "";
	std::string _star_select = "";

	// for new uncharted world.
	std::string _world_type = "";
	std::string _is_first_pass = "";
	std::string _use_hero = "";
	std::string _pass_time = "";
	std::string _boost_choose_cards_pool = "";
	std::string _boost_choose_card = "";
	std::string _hero_plant_skill = "";
	std::string _plant_board_record = "";
};

struct TGACustomLevelShareData
{
	std::string _step = "";
	std::string _level = "";
	std::string _self = "";
	std::string _platform = "";
	std::string _result = "";
	std::string _reward = "";
};

struct TGAOnlineData
{
	std::string _time = "";
};

struct TGAClearProfileData
{
	std::string _oldUserID = "";
	std::string _newUserID = "";
};

struct TGAPlayerReturnData
{
	std::string _day = "";
};

struct TGADebugInfoData
{
	std::string _info = "";
};

struct TGACardGameData
{
	std::string _step = "";
    std::string _level = "";
    std::string _result = "";
    std::string _cardId = "";
	std::string _reward = "";
	std::string _star = "";
};

struct TGABattleOrderData
{
	std::string _step = "";
    std::string _level = "";
    std::string _exp = "";
    std::string _privilege = "";
    std::string _gemNumber = "";
    std::string _gemChange = "";
    std::string _award = "";
    std::string _taskId = "";
    std::string _sku = "";
    std::string _price = "";
};

struct TGALimitedSummonData
{
	std::string _step = "";
    std::string _level = "";
    std::string _price = "";
    std::string _isfree = "";
    std::string _award = "";
    std::string _skuAward = "";
};

struct TGACarnivalData
{
	std::string _step = "";
    std::string _material = "";
    std::string _materialChange = "";
    std::string _buyBundleID;
    std::string _buyBundleTimes;
    std::string _award = "";
};

struct TGANewYearGoodsData
{
	std::string _step = "";
    std::string _price = "";
    std::string _goods = "";
};

struct TGAGeneEnhancementData
{
	std::string _step = "";
    std::string _factor = "";
    std::string _exhaust = "";
    std::string _sequence = "";
    std::string _level = "";
    std::string _currency = "";
    std::string _award = "";
};

struct TGALevelPackageData
{
	std::string _step = "";
	std::string _packageID = "";
	std::string _reward = "";
	std::string _price = "";
	std::string _worldName = "";
	std::string _worldStarsCount = "";
};

struct TGACornucopiaData
{
	std::string _step = "";
	std::string _tickets = "";
	std::string _emblems = "";
	std::string _level = "";
	std::string _taskId = "";
	std::string _gachaType = "";
	std::string _reward = "";
};

struct TGAWishingPoolData
{
	std::string _step = "";
    std::string _reward = "";
	std::string _price = "";
	std::string _lotteryType = "";
};

struct TGAGiftReturnData
{
	std::string _step = "";
    std::string _signDay = "";
    std::string _taskIntegral = "";
    std::string _taskId = "";
    std::string _mysteriousCrystal = "";
    std::string _reward = "";
};

struct TGATenYearsData
{
	std::string _step = "";
    std::string _sharedPage = "";
    std::string _reward = "";	
};

struct TGAInvitationData
{
	std::string _step = "";
    std::string _invitationCode = "";
    std::string _coinNum = "";
    std::string _taskId = "";
    std::string _reward = "";	
};

struct TGAAnniversaryNurturingData
{
	std::string _step = "";
    std::string _plantId = "";
    std::string _growthValue = "";    
    std::string _taskId = "";
    std::string _goodsId = "";
    std::string _diamondsConsumedNum = "";    
    std::string _reward = "";	
};

struct TGAPartyAssistData
{
	std::string _step = "";
	std::string _tickets = "";
	std::string _currentLevel = "";
	std::string _item_id = "";
	std::string _task_id = "";    
	std::string _reward = "";
};

struct TGANewplayerCollectionData
{
	std::string _step = "";
	std::string _newplayer = "";
	std::string _signdays = "";
	std::string _specialgift_item_id = "";
	std::string _specialgift_cost = "";
	std::string _discount_cost = "";
	std::string _rewards = "";
};

struct TGADaveKitchenData
{
	std::string _step = "";
	std::string _exchangeContent = "";
    std::string _bundleId = "";
    std::string _costValue = "";
    std::string _taskId = "";
    std::string _taskReward = "";
};

struct TGADragonTreasureData
{
    std::string _step = "";
    std::string _crystal = "";
    std::string _integral = "";
    std::string _bigAward = "";
    std::string _crystalCost = "";
    std::string _integralCost = "";
    std::string _productId = "";
    std::string _price = "";
    std::string _reward = "";
};

struct TGAFirstRechargeNewData
{
	std::string _step = "";
	std::string _day = "";
	std::string _tab = "";
	std::string _reward = "";
};

struct TGAHeroPlantData
{
    std::string _step = "";
    std::string _heroPlant = "";
    std::string _level = "";
    std::string _type = "";
    std::string _time = "";
};

class TGALogMgr : public Sexy::NetworkServiceListener, public LazySingleton<TGALogMgr>
{
public:

	TGALogMgr();
    virtual ~TGALogMgr();

    void UpdateFrame();

    void Log(const std::string& i_logId,const std::vector<std::string>& i_params);
    void LogForLogin(const std::string& i_logId,const std::vector<std::string>& i_params);
    void LogSegments(int i_logId, int i_index, const std::string& i_param);

    std::string GetSegForId(int i_logId, int i_index);
    void clearSegments(int i_id);

    void ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context);
	void ServiceRequestFailed(const Sexy::StructuredData* i_response, const void* i_context);
	void ServiceRequestCompleted(ImageLib::Image*&, const void* i_context) {}
	void ServiceRequestCompleted(const Sexy::Buffer*, const void* i_context) {}

	void UseLevelItem(const std::string& i_item, int i_freeGem, int i_useGem);
	void LogPlantAdventure(int i_step, PlantAdventureInfo_S i_info, int i_cd);
	void LogFirstRecharge(int i_step, const std::map<int, int>& i_infos);
	void LogFirstRecharge(TGAFirstRechargeData i_info);
    void LogDaveTreasure(int i_step, TGALogDaveTreasureData i_info);
    void LogMinigame(int i_step, TGALogMinigameData i_info);
    void LogRechargeReward(int i_step, TGALogRechargeRewardData i_info);
    void LogDiamond(std::string description, int useFreeGem, int usePayGem, int getFreeGem, int getPayGem);
    void LogPurchase(TGALogPurchaseData i_info);
    void LogPlantLevelup(int i_step, TGALogPlantLevelupData i_info);
    void LogNewuserPresent(int i_step, std::string presentID, std::string description, int price);
    void LogDailySign(int totalSignDays, int basicSignDays, std::string bonus);
    void LogCoin(int coins, int freeGems, int payGems);
    void LogPennyTreasure(int i_step, TGALogPennyTreasureData i_info);
    void LogTravelLog(int i_step, TGALogTravelLogData i_info);
    void LogPlantTrial(int i_step, int id, int freeGems = 0, int payGems = 0, int payCost = 0);
    void LogTransGenosis(int i_step, TGALogTransGenosisData i_info);
    void LogJoust(int i_step, TGALogJoustData i_info);
    void LogEndless(TGALogEndlessData i_info);
    void LogPlantSpecialOffer(TGAPlantSpecialOfferData i_info);
    void LogLimitedGacha(TGALimitedGachaData i_info);
    void LogLimitedLottery(TGALimitedLotteryData i_info);
    void LogRechargeBundle(TGARechargeBundleData i_info);
    void LogGroupBuy(TGAGroupBuyData i_info);
    void LogVaseBreaker(TGAVaseBreakerData i_info);
    void LogConsumeReceive(TGAConsumeReceiveData i_info);
    void LogMinorLottery(TGAMinorLotteryData i_info);
    void LogAD(std::string i_step, std::string i_level, int i_pos, std::string i_rewardType, std::string i_rewardQuantity);
    void LogAD(std::string i_step, std::string i_level, std::string placementID, std::string i_rewardType, std::string i_rewardQuantity);
    void LogRichMan(TGARichManData i_info);
    void LogLuckBag(TGALuckBagData i_info);
    void LogPigBank(TGAPigBankData i_info);
    void LogFestivalRedPacket(TGAFestivalRedPacketData i_info);
    void LogCrack(TGACrackData i_info);
    void LogDangerRoomSpecialOffer(TGADangerRoomSpecialOfferData i_info);
    void LogOneYuanRedPacket(TGAOneYuanRedPacketData i_info);
    void LogPlantInfo(TGAPlantData i_info);
    void LogConsumeReceiveExtra(TGAConsumeReceiveData i_info);
    void LogDailySignActivity(TGADailySignActivity i_info);
    void LogDailyRechargeReward(TGADailyRechargeReward i_info);
    void LogRenaissanceChallenge(TGARenaissanceChallengeData i_info);
    void LogBossChallenge(TGABossChallengeData i_info);
    void LogSecretGacha(TGASecretGacha i_info);
    void LogHappyVaseBreaker(TGAHappyVaseBreakerData i_info);
    void LogRechargeDailySign(TGARechargeDailySignData i_info);
    void LogDiscountShop(TGADiscountShopData i_info);
    void LogNewRecallSign(TGANewRecallSignData i_info);
    void LogNewRecallBank(TGANewRecallBankData i_info);
    void LogNewRecallBundle(TGANewRecallBundleData i_info);
    void LogSecretStore(TGASecretStore i_info);
    void LogPennyPursuit(TGAPennyPursuitData i_info);
    void LogNewPVP(TGANewPVPData i_info);
    void LogNewPVPPlus(TGANewPVPPlusData i_info);
    void LogIOSRealNameLogin();
    void LogMysteryStore(TGAMysteryStore i_info);
    void LogAnniversaryTreasure(TGAAnniversaryTreasureData i_info);
    void LogMonthlyCardSpecial(TGAMonthlyCardSpecialData i_info);
    void LogCustomVoting(TGACustomVoting i_info); 
    void LogFightZodiac(TGAFightZodiac i_info); 
    void LogFoolChallenge(TGAFoolData i_info); 
    void LogBag(TGABagData i_info);
    void LogAccountRemove(TGAAccountRemove i_info);
    void LogAppLaunch(TGAAppLaunch i_info);
    void LogAdsLottery(TGAAdsLotteryData i_info);
    void LogTutorial(TGATutorialData i_info);
    void LogNoviceSevenDays(TGANoviceSevenDaysData i_info);
    void LogPlayerSurvey(TGAPlayerSurveyData i_info);
    void LogScrollbanner(TGAScrollbannerData i_info);
    void LogCallofWishDraw(const TGACallofWishDraw& i_info);
    void LogCallofWishTask(const TGACallofWishTask& i_info);
    void LogCallofWishDaily(const TGACallofWishDaily& i_info);
    void LogCallofWishLimit(const TGACallofWishLimit& i_info);
    void LogCallofWishGift(const TGACallofWishGift& i_info);
    void LogCallofWishTrain(const TGACallofWishTrain& i_info);
    void LogArtifactPresent(TGAArtifactPresentData i_info);
    void LogArtifactCultivation(const TGArtifactCultivation& i_info);
    void LogPVZ1Mode(const TGAPVZ1ModeData& i_info);
    void LogPVZ1Achievement(const TGAPVZ1Achievement& i_info);
    void LogCustomLevel(const TGACustomLevelData& i_info);
    void LogGoldenEgg(const TGAGoldenEgg& i_info);
    void LogPennyClassroom(const TGAPennyClassroomData& i_info);
    void LogArborDay(const TGAArborDay& i_info);
    void LogGetAccessory(const TGAccessoryData& i_info);
    void LogGrowthPackage(const TGAGrowthPackage i_info);
    void LogUncharted(const TGAUnchartedData i_info);
    void LogOnline(const TGAOnlineData i_info);
    void StartOnlineLog();
    void LogClearProfile(const TGAClearProfileData i_info);
    void LogPlayerReturn(const TGAPlayerReturnData i_info);
    void LogDebugInfo(const TGADebugInfoData i_info);
    void LogCardGame(const TGACardGameData i_info);
    void LogCustomLevelShare(const TGACustomLevelShareData& i_info);
    void LogBattleOrderInfo(const TGABattleOrderData& i_info);
    void LogCustomLevelAD(const TGACustomLevelADData& i_info);
    void LogLimitedSummon(const TGALimitedSummonData& i_info);
    void LogCarnivalData(const TGACarnivalData& i_info);
    void LogNewYearGoodsData(const TGANewYearGoodsData& i_info);
    void LogGeneEnhancementData(const TGAGeneEnhancementData& i_info);
    void LogLevelPackageData(const TGALevelPackageData& i_info);
    void LogCornucopiaData(const TGACornucopiaData& i_info);
    void LogWishingPoolData(const TGAWishingPoolData& i_info);
    void LogDecorateData(const TGALogPlantDecorate& i_info);

    void LogGiftReturnData(const TGAGiftReturnData& i_info);
    void LogTenYearsData(const TGATenYearsData& i_info);
    void LogInvitationData(const TGAInvitationData& i_info);
    void LogAnniversaryNurturingData(const TGAAnniversaryNurturingData& i_info);
    void LogPartyAssistData(const TGAPartyAssistData& i_info);
    void LogNewplayerCollectiontData(const TGANewplayerCollectionData& i_info);
    void LogDaveKitchenData(const TGADaveKitchenData& i_info);
    void LogDragonTreasure(const TGADragonTreasureData& i_info);
    void LogFirstRechargeNew(const TGAFirstRechargeNewData& i_info);
    void LogHeroPlant(const TGAHeroPlantData& i_info);

private:
    void init();
    void appendMsg(const std::string& i_msg, bool i_last);
    void sendLog(const DValue & value);
    void sendMsg();
    void requestSendMsg();
    bool needWriteLog();
    void writeLog(const std::string& i_msg);
    void UpdateOnlineLog();

    std::string m_url;
    std::string m_logId;
    std::string m_sendMsg;
    std::map<int, std::vector<CustomSegment>> m_segments;
    std::string m_logMsg;

    pvztime_t m_onlineStartTime;
    pvztime_t m_onlineEndTime;
};


#endif /* TGALOGMGR_H_ */
