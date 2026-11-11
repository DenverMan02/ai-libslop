
/* ------------------------------------------------------------------------------------------------------------
 
	Popcap Shanghai studio
 
	Created by weiqi.zhong @ 2012 -3- 13
 ------------------------------------------------------------------------------------------------------------*/
#ifndef PACKETID_H
#define PACKETID_H
#include <string>
#include <map>


typedef struct _PacketId
{
#ifdef HOST_ANDROID
    std::string ID_GET_FRIEDN_LIST           ;
    std::string ID_SENT_GIFT                 ;
    std::string ID_Test                      ;
    std::string ID_FRIEND_GIFT_LIST          ;
    std::string ID_PLAYERIFO                 ;
    std::string ID_FRESH_SURPOT_PLANT        ;
    std::string ID_FRESH_GEMS_COUNT          ;
    std::string ID_BORROW_FRIEND_PLANT       ;
    std::string ID_BORROWED_FRIEND_PLANT_LIST;
    std::string ID_LOGIN;
    std::string ID_HEART_BEAT                ;
    std::string ID_GET_PROFILE               ;
    std::string ID_ACCEPT_GIFT               ;
    std::string ID_UPDATE_PROFILE            ;
    std::string ID_LEVEL_SCORE               ;
    std::string ID_FRIEND_LEADERBOAD         ;
    std::string ID_TODAY_SENT_GIFT_LIST      ;
    std::string ID_INCREASE_GEMS             ;
    std::string ID_RAND_REWARD               ;
    std::string ID_TLOG                      ;
    std::string ID_ADD_FRIEND_SHIP			 ;
    std::string ID_LAUNCH_SAVE_FINISH		 ;
    std::string ID_LOAD_FRIEND_PIC           ;
    std::string ID_FRIENDS_NO_URL            ;
    std::string ID_LOCAL_MSG_ID              ;
    std::string ID_ICLOUD_SILENCE_LOGIN      ;
    std::string ID_ICLOUD_GET_PROFILE        ;
    std::string ID_ICLOUD_UPLOAD_PROFILE     ;
    std::string ID_ICLOUD_GET_PROFILE_MD5    ;
    std::string ID_ICLOUD_UPLOAD_COMPRESSED_PROFILE;
    std::string ID_TIME_LEVEL_MSG_ID_LIST    ;
    std::string ID_TIME_LEVEL_MSG_ID_NODE    ;
    std::string ID_DANGER_ROOM_UPLOAD_RANK  ;
    std::string ID_DANGER_ROOM_REQUEST_RANK  ;
    std::string ID_GET_REDPACK_RANK_BOARD ;
    std::string ID_GET_WECHAT_SHARE_GIFT;
    std::string ID_UUID_BIND;
    std::string ID_UUID_LOGIN;
    std::string ID_PURCHASE_INIT;
    std::string ID_PURCHASE_LOST;
    std::string ID_ICLOUD_GET_PLAYER_INFO = "V316";
    std::string ID_REQUEST_ACLOG;
    std::string ID_REQUEST_SYNC_PLAYER_DATA;
    std::string ID_REQUEST_DOWNLOAD_PLAYER_DATA;
    std::string ID_UPLOAD_IDENTIFICATION;
    std::string ID_ADS_CHALLENGE;
    std::string ID_RICHMAN_RESULT;
    // for new convert ios
    std::string ID_ICLOUD_SYNCHRONIZE_PLANT;
    std::string ID_ICLOUD_SYNCHRONIZE_AVATAR;
    std::string ID_ICLOUD_PLANT_LEVEL_UP;
    std::string ID_ICLOUD_CHANGE_PLANT;
    std::string ID_ICLOUD_CHANGE_AVATAR;
    std::string ID_ICLOUD_SYNCHRONIZE_PENDANT;
    std::string ID_ICLOUD_REQUEST_PENDANT_EXCHANGE;
    std::string ID_ICLOUD_REQUEST_PENDANT_SOLD;

    std::string ID_ICLOUD_REQUEST_SYNC_CACHED_OBJECTS;

    std::string ID_ICLOUD_REQUEST_PLANT_TRIAL;

    std::string ID_ICLOUD_REQUEST_GET_EXPLORE_TEAM_STATUS;
    std::string ID_ICLOUD_REQUEST_GET_EXPLORE_PLANT_STATUS;
    std::string ID_ICLOUD_REQUEST_START_EXPLORE;
    std::string ID_ICLOUD_REQUEST_STOP_EXPLORE;
    std::string ID_ICLOUD_REQUEST_GET_EXPLORE_REWARD;
    std::string ID_ICLOUD_REQUEST_OPEN_EXPLORE_SURPRISE_BOX;
    std::string ID_ICLOUD_REQUEST_RECOVER_EXPLORE_PLANT;

    std::string ID_ICLOUD_REQUEST_CHRISTMAS_LOTTERY;
    std::string ID_ICLOUD_REQUEST_COMPOSE_PLANT;

    std::string ID_ICLOUD_GET_CHARGE_REWARD;
    
    std::string ID_ICOUD_BIND_UNIQUE_ID;// bind unique id

    //for non wechat version iCloud

    _PacketId()
    {
      ID_LOGIN                     = "V1";
      ID_GET_PROFILE               = "V2";
      ID_GET_FRIEDN_LIST           = "V3";
      ID_SENT_GIFT                 = "V4";
      ID_ACCEPT_GIFT               = "V5";
      ID_Test                      = "T5";
      ID_UPDATE_PROFILE            = "V6";
      ID_FRIEND_GIFT_LIST          = "V7";
      ID_PLAYERIFO                 = "V8";
      ID_FRESH_SURPOT_PLANT        = "V9";
      ID_FRESH_GEMS_COUNT          = "V10";
      ID_LEVEL_SCORE               = "V11";
      ID_FRIEND_LEADERBOAD         = "V12";
      ID_BORROW_FRIEND_PLANT       = "V13";
      ID_BORROWED_FRIEND_PLANT_LIST= "V14";
      ID_TODAY_SENT_GIFT_LIST      = "V15";
      ID_INCREASE_GEMS             = "V16";
      ID_HEART_BEAT                = "V17";
      ID_RAND_REWARD               = "V18";
      ID_TLOG                      = "V19";
      ID_ADD_FRIEND_SHIP           = "V20";
      ID_LAUNCH_SAVE_FINISH        = "V24";
      ID_LOAD_FRIEND_PIC           = "V25";
      ID_ICLOUD_SILENCE_LOGIN      = "V202";
      ID_ICLOUD_GET_PROFILE        = "V203";
      ID_ICLOUD_UPLOAD_PROFILE     = "V204";
      ID_ICLOUD_GET_PROFILE_MD5    = "V205";
      ID_ICLOUD_UPLOAD_COMPRESSED_PROFILE = "V206";
      ID_FRIENDS_NO_URL            = "V1111";
      ID_LOCAL_MSG_ID              = "LOCAL";
      ID_TIME_LEVEL_MSG_ID_NODE    = "V208";
      ID_TIME_LEVEL_MSG_ID_LIST    = "V210";
      ID_DANGER_ROOM_UPLOAD_RANK    = "V211";
      ID_DANGER_ROOM_REQUEST_RANK  = "V212";
      ID_GET_REDPACK_RANK_BOARD = "V266";
      ID_GET_WECHAT_SHARE_GIFT = "V274";
      ID_UUID_BIND = "V219";
      ID_UUID_LOGIN = "V220";
      ID_PURCHASE_INIT = "V213";
      ID_PURCHASE_LOST = "V214";
      ID_UPLOAD_IDENTIFICATION = "V404";
      ID_ADS_CHALLENGE = "V798";
      ID_RICHMAN_RESULT = "V902";

        // for new convert ios
        ID_ICLOUD_SYNCHRONIZE_PLANT                     = "V211";
        ID_ICLOUD_SYNCHRONIZE_AVATAR                    = "V212";
        ID_ICLOUD_PLANT_LEVEL_UP                        = "V231";
        ID_ICLOUD_CHANGE_PLANT                          = "V229";
        ID_ICLOUD_CHANGE_AVATAR                         = "V230";
        ID_ICLOUD_SYNCHRONIZE_PENDANT                   = "V253";
        ID_ICLOUD_REQUEST_PENDANT_EXCHANGE              = "V254";
        ID_ICLOUD_REQUEST_PENDANT_SOLD                  = "V256";

        ID_ICLOUD_REQUEST_SYNC_CACHED_OBJECTS           = "V302";

        ID_ICLOUD_REQUEST_PLANT_TRIAL                   = "V267";

        ID_ICLOUD_REQUEST_GET_EXPLORE_TEAM_STATUS       = "V279";
        ID_ICLOUD_REQUEST_GET_EXPLORE_PLANT_STATUS      = "V280";
        ID_ICLOUD_REQUEST_START_EXPLORE                 = "V281";
        ID_ICLOUD_REQUEST_STOP_EXPLORE                  = "V282";
        ID_ICLOUD_REQUEST_GET_EXPLORE_REWARD            = "V283";
        ID_ICLOUD_REQUEST_OPEN_EXPLORE_SURPRISE_BOX     = "V284";
        ID_ICLOUD_REQUEST_RECOVER_EXPLORE_PLANT         = "V288";

        ID_ICLOUD_REQUEST_CHRISTMAS_LOTTERY             = "V289";
        ID_ICLOUD_REQUEST_COMPOSE_PLANT                 = "V301";
        ID_ICLOUD_GET_CHARGE_REWARD                     = "V226";
        
        ID_ICOUD_BIND_UNIQUE_ID							= "V770";

        InitCommon();
    }
    
#else
    
    std::string ID_LOCAL_MSG_ID              ;
    std::string ID_ICLOUD_SILENCE_LOGIN      ;
    std::string ID_ICLOUD_GET_PROFILE        ;
    std::string ID_ICLOUD_UPLOAD_PROFILE     ;
    std::string ID_GET_WECHAT_SHARE_GIFT;
    
    std::string ID_ICLOUD_GET_PROFILE_LIST   ;
    std::string ID_ICLOUD_UPLOAD_PROFILE_NOT_IN_SERVER;
    std::string ID_ICLOUD_GET_PLAYER_INFO;
    
    std::string ID_ICLOUD_VALIDATE_CHARGE;
    std::string ID_ICLOUD_GET_CONFIG_VERSION;
    std::string ID_ICLOUD_SYNCHRONIZE_PLANT;
    std::string ID_ICLOUD_SYNCHRONIZE_AVATAR;
    std::string ID_ICLOUD_ADD_FREE_GEM;
    std::string ID_ICLOUD_GET_LOGINREWARD_INFO;
    std::string ID_ICLOUD_REQUEST_LOGINREWARD;
    std::string ID_ICLOUD_COMPENSATION;
    std::string ID_ICLOUD_GET_CHARGE_REWARD;
    std::string ID_ICLOUD_GET_GACHA_INFO;
    std::string ID_ICLOUD_CHANGE_PLANT;
    std::string ID_ICLOUD_CHANGE_AVATAR;
    std::string ID_ICLOUD_PLANT_LEVEL_UP;
    std::string ID_ICLOUD_GET_SIGNREWARD_INFO;
    std::string ID_ICLOUD_REQUEST_SIGNREWARD;
    
    std::string ID_ICLOUD_RELOGIN;
    std::string ID_ICLOUD_BUY_GIFT;
    std::string ID_ICLOUD_START_LEVEL_TIME;
    std::string ID_ICLOUD_GET_LEVEL_TIME_REMAIN;
    std::string ID_ICLOUD_UNLOCK_TIME_LEVEL;
    
    std::string ID_ICLOUD_ENDLESS_CONSUME_LIFE;
    std::string ID_ICLOUD_ENDLESS_UPDATE_SCORE;
    std::string ID_ICLOUD_REQUEST_RIDDLE_INFO;
    std::string ID_ICLOUD_CONSUME_LEAFS;
    std::string ID_ICLOUD_REQUEST_RIDDLE_FOR_RED_PACK;
    std::string ID_ICLOUD_SYNCHRONIZE_PENDANT;
    std::string ID_ICLOUD_REQUEST_PENDANT_EXCHANGE;
    std::string ID_ICLOUD_REQUEST_PENDANT_SOLD;
    std::string ID_ICLOUD_REQUEST_RIDDLE_GET_PRIZE;
    std::string ID_ICLOUD_REQUEST_REDPACK_OPEN;
    std::string ID_ICLOUD_REQUEST_REDPACK_LEADERBOARD;
    std::string ID_ICLOUD_REQUEST_REDPACK_INFO;
    
    std::string ID_ICLOUD_REQUEST_2015NEWYEAR_CHARGE_STAT;
    std::string ID_ICLOUD_REQUEST_GET_REDPACK;
    std::string ID_ICLOUD_REQUEST_2015NEWYEAR_CHARGE_REWARD;
    std::string ID_ICLOUD_REQUEST_REDPACK_LEADERBOARD_REWARD;
    std::string ID_ICLOUD_REQUEST_PENDANT_GACHA;
    std::string ID_ICLOUD_REQUEST_GOLDCAN_GACHA;
    
    std::string ID_ICLOUD_REQUEST_PLANT_TRIAL;
    std::string ID_ICLOUD_REQUEST_CONSUMPTION_REWARD_STAT;
    
    std::string ID_ICLOUD_REQUEST_GET_DAILY_ACHIEVE_INFO;
    std::string ID_ICLOUD_REQUEST_GET_DAILY_ACHIEVE_BONUS;
    std::string ID_ICLOUD_REQUEST_GET_WECHAT_SHARE_GIFT;
    std::string ID_ICLOUD_REQUEST_GET_BIRTHDAY_REWARD;
    std::string ID_ICLOUD_REQUEST_GET_PINATA_REWARD;
    
    std::string ID_ICLOUD_REQUEST_GET_EXPLORE_TEAM_STATUS;
    std::string ID_ICLOUD_REQUEST_GET_EXPLORE_PLANT_STATUS;
    std::string ID_ICLOUD_REQUEST_START_EXPLORE;
    std::string ID_ICLOUD_REQUEST_STOP_EXPLORE;
    std::string ID_ICLOUD_REQUEST_GET_EXPLORE_REWARD;
    std::string ID_ICLOUD_REQUEST_OPEN_EXPLORE_SURPRISE_BOX;
	std::string ID_ICLOUD_REQUEST_GET_GEM_RETURN_STAT;
	std::string ID_ICLOUD_REQUEST_GET_GEM_RETURN_REWARD;
    std::string ID_ICLOUD_REQUEST_RECOVER_EXPLORE_PLANT;
    
    std::string ID_ICLOUD_REQUEST_CHRISTMAS_LOTTERY;
    std::string ID_ICLOUD_REQUEST_CHRISTMAS_PROTECT;
    std::string ID_ICLOUD_REQUEST_CHRISTMAS_ACCESSORY_STAT;
    std::string ID_ICLOUD_REQUEST_CHRISTMAS_ACCESSORY_BUY;
    std::string ID_ICLOUD_REQUEST_CHRISTMAS_CHECKREBATE;
    std::string ID_ICLOUD_REQUEST_CHRISTMAS_REBATE;
    
    std::string ID_ICLOUD_REQUEST_CHRISTMAS_GOLDEN_EGG_STAT;
    std::string ID_ICLOUD_REQUEST_CHRISTMAS_GOLDEN_EGG_OPEN;

    std::string ID_ICLOUD_REQUEST_COMPOSE_PLANT;
    std::string ID_ICLOUD_REQUEST_SYNC_CACHED_OBJECTS;
    
    std::string ID_UUID_BIND;
    std::string ID_UUID_LOGIN;
    std::string ID_UPLOAD_IDENTIFICATION;
    std::string ID_RICHMAN_RESULT;
    
    _PacketId()
    {
        ID_LOCAL_MSG_ID                                 = "error";
        
        ID_ICLOUD_SILENCE_LOGIN                         = "V201";
        ID_ICLOUD_GET_PROFILE_LIST                      = "V202";
        ID_ICLOUD_UPLOAD_PROFILE_NOT_IN_SERVER          = "V203";
        ID_ICLOUD_UPLOAD_PROFILE                        = "V205";
        ID_ICLOUD_GET_PROFILE                           = "V210";
        
        ID_ICLOUD_GET_PLAYER_INFO                       = "V216";
        ID_ICLOUD_VALIDATE_CHARGE                       = "V219";
        
        ID_ICLOUD_GET_CONFIG_VERSION                    = "V224";
        ID_ICLOUD_SYNCHRONIZE_PLANT                     = "V211";
        ID_ICLOUD_SYNCHRONIZE_AVATAR                    = "V212";
        ID_ICLOUD_ADD_FREE_GEM                          = "V208";
        ID_ICLOUD_GET_LOGINREWARD_INFO                  = "V217";
        ID_ICLOUD_REQUEST_LOGINREWARD                   = "V218";
        ID_ICLOUD_COMPENSATION                          = "V225";
        ID_ICLOUD_GET_CHARGE_REWARD                     = "V226";
        
        ID_ICLOUD_GET_GACHA_INFO                        = "V227";
        ID_ICLOUD_CHANGE_PLANT                          = "V229";
        ID_ICLOUD_CHANGE_AVATAR                         = "V230";
        ID_ICLOUD_PLANT_LEVEL_UP                        = "V231";
        ID_ICLOUD_GET_SIGNREWARD_INFO                   = "V232";
        ID_ICLOUD_REQUEST_SIGNREWARD                    = "V233";
        
        ID_ICLOUD_RELOGIN                               = "V240";
        ID_ICLOUD_BUY_GIFT                              = "V241";
        
        ID_ICLOUD_START_LEVEL_TIME                      = "V242";
        ID_ICLOUD_GET_LEVEL_TIME_REMAIN                 = "V243";
        ID_ICLOUD_UNLOCK_TIME_LEVEL                     = "V244";
        
        ID_ICLOUD_ENDLESS_CONSUME_LIFE                  = "V247";
        ID_ICLOUD_ENDLESS_UPDATE_SCORE                  = "V248";
        
        ID_ICLOUD_REQUEST_RIDDLE_INFO                   = "V250";
        ID_ICLOUD_CONSUME_LEAFS                         = "V251";
        ID_ICLOUD_REQUEST_RIDDLE_FOR_RED_PACK           = "V252";
        ID_ICLOUD_SYNCHRONIZE_PENDANT                   = "V253";
        ID_ICLOUD_REQUEST_PENDANT_EXCHANGE              = "V254";
        ID_ICLOUD_REQUEST_PENDANT_SOLD                  = "V256";
        ID_ICLOUD_REQUEST_RIDDLE_GET_PRIZE              = "V255";
        ID_ICLOUD_REQUEST_REDPACK_OPEN                  = "V257";
        ID_ICLOUD_REQUEST_REDPACK_LEADERBOARD           = "V258";
        ID_ICLOUD_REQUEST_REDPACK_INFO                  = "V259";
        
        ID_ICLOUD_REQUEST_2015NEWYEAR_CHARGE_STAT       = "V260";
        ID_ICLOUD_REQUEST_GET_REDPACK                   = "V261";
        ID_ICLOUD_REQUEST_2015NEWYEAR_CHARGE_REWARD     = "V262";
        ID_ICLOUD_REQUEST_REDPACK_LEADERBOARD_REWARD    = "V263";
        ID_ICLOUD_REQUEST_PENDANT_GACHA                 = "V264";
        ID_ICLOUD_REQUEST_GOLDCAN_GACHA                 = "V265";
        
        ID_ICLOUD_REQUEST_PLANT_TRIAL                   = "V267";
        ID_ICLOUD_REQUEST_CONSUMPTION_REWARD_STAT       = "V268";
        
        ID_ICLOUD_REQUEST_GET_DAILY_ACHIEVE_INFO        = "V271";
        ID_ICLOUD_REQUEST_GET_DAILY_ACHIEVE_BONUS       = "V272";
        ID_ICLOUD_REQUEST_GET_WECHAT_SHARE_GIFT			= "V274";
        ID_ICLOUD_REQUEST_GET_BIRTHDAY_REWARD           = "V275";
        ID_ICLOUD_REQUEST_GET_PINATA_REWARD             = "V276";
        
        ID_ICLOUD_REQUEST_GET_EXPLORE_TEAM_STATUS       = "V279";
        ID_ICLOUD_REQUEST_GET_EXPLORE_PLANT_STATUS      = "V280";
        ID_ICLOUD_REQUEST_START_EXPLORE                 = "V281";
        ID_ICLOUD_REQUEST_STOP_EXPLORE                  = "V282";
        ID_ICLOUD_REQUEST_GET_EXPLORE_REWARD            = "V283";
        ID_ICLOUD_REQUEST_OPEN_EXPLORE_SURPRISE_BOX     = "V284";
		ID_ICLOUD_REQUEST_GET_GEM_RETURN_STAT           = "V285";
		ID_ICLOUD_REQUEST_GET_GEM_RETURN_REWARD         = "V286";
        ID_ICLOUD_REQUEST_RECOVER_EXPLORE_PLANT         = "V288";
        
        ID_ICLOUD_REQUEST_CHRISTMAS_LOTTERY             = "V289";
        ID_ICLOUD_REQUEST_CHRISTMAS_PROTECT             = "V290";
        ID_ICLOUD_REQUEST_CHRISTMAS_GOLDEN_EGG_STAT     = "V291";
        ID_ICLOUD_REQUEST_CHRISTMAS_GOLDEN_EGG_OPEN     = "V292";
        ID_ICLOUD_REQUEST_CHRISTMAS_ACCESSORY_STAT      = "V293";
        ID_ICLOUD_REQUEST_CHRISTMAS_ACCESSORY_BUY       = "V294";
        ID_ICLOUD_REQUEST_CHRISTMAS_CHECKREBATE         = "V295";
        ID_ICLOUD_REQUEST_CHRISTMAS_REBATE              = "V296";
        
        ID_UUID_BIND                                    = "V701";
        ID_UUID_LOGIN                                   = "V702";
        
        // V297~V298 is public used by iOS/ Android.
        
        ID_ICLOUD_REQUEST_COMPOSE_PLANT                 = "V301";
        ID_ICLOUD_REQUEST_SYNC_CACHED_OBJECTS           = "V302";

        ID_UPLOAD_IDENTIFICATION                        = "V798";
        ID_RICHMAN_RESULT                               = "V902";

        InitCommon();
    }
#endif
    
    //-----------------------------------------------
    // common, both ios and android
    // !attention!: the request string start with 'P' is a PVP message, which's sent to PVP server!!
    //-----------------------------------------------
    
    std::string ID_ICLOUD_USE_GEM;
    std::string ID_ICLOUD_GETSTATE_THIRDPART_PLATFORMS;
    std::string ID_ICLOUD_LOGIN_THIRDPART_PLATFORMS;
    std::string ID_ICLOUD_BINDING_THIRDPART_PLATFORMS;
    std::string ID_ICLOUD_UNBOUND_THIRDPART_PLATFORMS;
    std::string ID_ICLOUD_TRANSFER_THIRDPART_PLATFORMS;
    std::string ID_ICLOUD_CLEARNOTIFY_THIRDPART_PLATFORMS;
    
    std::string ID_ICLOUD_GET_SERVICE_STATUS;
    std::string ID_ICLOUD_GET_RANK_LIST;
    
    std::string ID_ICLOUD_REQUEST_PVP_SHOP;
    std::string ID_ICLOUD_REQUEST_BUY_PVP_SHOP_OBJECT;
    
    std::string ID_REQUEST_BOARD_INFOLIST;
    std::string ID_REQUEST_BOARD_INFO_GET;
    
    std::string ID_REQUEST_UPDATE_CHARGE_INFO;
    
    std::string ID_UUID_INIT;
    std::string ID_UUID_CHECK;

    std::string ID_REQUEST_PVP_LOGIN;
    std::string ID_REQUEST_PVP_TRAINIGN_INFOS;
    std::string ID_REQUEST_PVP_TRAINIGN_SELL;
    std::string ID_REQUEST_PVP_TRAINIGN_ZOMBIE_REFRESH;
    std::string ID_REQUEST_PVP_TRAINIGN_ZOMBIE;
    std::string ID_REQUEST_PVP_TRAINIGN_FINISH_AT_ONCE;
    std::string ID_REQUEST_PVP_TRAINIGN_FINISH_GEMS;
    std::string ID_REQUEST_PVP_ENTRY;
    std::string ID_REQUEST_PVP_MAP_INFO;
    std::string ID_REQUEST_PVP_ACHIEVE;
    std::string ID_REQUEST_PVP_UNLOCK;
    std::string ID_REQUEST_PVP_CHANGE_ENEMY;
    std::string ID_REQUEST_PVP_PLANT_INFOS;
    std::string ID_REQUEST_GET_PVP_PLANT_INFOS;
    std::string ID_REQUEST_PVP_BATTLE_ENDING;
    std::string ID_REQUEST_PVP_EDIT_PLANT;
    std::string ID_REQUEST_PVP_CHANGE_PLAYER;
    std::string ID_REQUEST_PVP_PLAYBACK_LIST;
    std::string ID_REQUEST_PVP_PLAYBACK_DOWNLOAD;
    std::string ID_REQUEST_PVP_PLAYBACK_UPLOAD;
    std::string ID_REQUEST_PVP_PING;
    std::string ID_REQUEST_PVP_BUY_COIN;
    std::string ID_REQUEST_PVP_LAB_ENTER;
    std::string ID_REQUEST_PVP_BEGIN_UPGRADE;
    std::string ID_REQUEST_PVP_COMPLETE_UPGRADE;
    std::string ID_REQUEST_PVP_RANK;
    std::string ID_REQUEST_PVP_OTHERSZB_LIST;
    std::string ID_REQUEST_ACHIEVEMENT;
    std::string ID_REQUEST_ACHIEVEMENT_REWARD;
    std::string ID_REQUEST_PVP_SUBPVPCOIN;
    std::string ID_REQUEST_PVP_COMPENSATION_NOTICE;
    std::string ID_REQUEST_PVP_UPGRADE_COMPLETE_GEM;
    std::string ID_REQUEST_PVP_UPGRADE_CANCEL;
    
    std::string ID_REQUEST_VERIFY_SALES_REWARD;
    std::string ID_REQUEST_ACTIVE_ACTIVITY_STATES;
    std::string ID_REQUEST_ACTIVE_LEVELOFTHEDAY_REWARD;
    std::string ID_REQUEST_ACTIVE_YUANBAO_REWARD;
    
    std::string ID_ICLOUD_STATIC_CONFIG;
    std::string ID_ICLOUD_REQUSET_LUA_GENERAL;
    std::string ID_ICLOUD_DAILYSIGN_WITHTW;
    std::string ID_ICLOUD_DO_GACHA;
    std::string ID_ICLOUD_DO_NEW_GACHA;
    std::string ID_ICLOUD_REQUEST_INSTANCE_STATUS;
    std::string ID_ICLOUD_REQUEST_GET_CONSUMPTION_REWARD;
	std::string ID_ICLOUD_REQUEST_GET_STONELOTTERY;
	std::string ID_ICLOUD_REQUEST_GET_7DAYSLOGINREWARD;
	std::string ID_ICLOUD_REQUEST_GET_CHRISTMASLOGINREWARD;
    std::string ID_ICLOUD_REQUEST_GET_FIRSTCHARGESUCCEED;
    std::string ID_ICLOUD_REQUEST_GET_SPRINGLOGINREWARD;
    std::string ID_ICLOUD_REQUEST_GET_SPRINGBUYPLANT;
    std::string ID_ICLOUD_REQUEST_WORLDCUPBEGINNAME;
    std::string ID_ICLOUD_REQUEST_BUYWORLDCUPTICKET;
    std::string ID_ICLOUD_REQUEST_BUYZMATCHTICKET;
    std::string ID_ICLOUD_REQUEST_GETZMATCHSHOPDATA;
    std::string ID_ICLOUD_REQUEST_ZMATCHBUYITEM;
    std::string ID_ICLOUD_REQUEST_UNLOCKWORLDCUPTEAM;
    std::string ID_ICLOUD_REQUEST_CLEARWORLDCUPDATA;
	std::string ID_ICLOUD_REQUEST_GET_REWARDPLANTID;
	std::string ID_ICLOUD_REQUEST_GET_CHRISTMASCHARGEREWARD;
	std::string ID_ICLOUD_REQUEST_GET_RECHARGEREWARD;
    std::string ID_REQUEST_ACTIVITY_LIST;
    std::string ID_REQUEST_ACTIVITY_LEVEL_END;
    std::string ID_REQUEST_SUMMERY_LOTTERY;
    std::string ID_REQUEST_SUMMER_PLANTCOMPOSIT;
    std::string ID_REQUEST_BOSS_CHALLENGE_LEVEL_END;
    std::string ID_REQUEST_BOSS_CHALLENGE_REWARD;
    std::string ID_REQUEST_ADS_REWARD;
    std::string ID_REQUEST_USER_INFO;
    std::string ID_REQUEST_CODE_REWARD;
    std::string ID_REQUEST_WECHAT_REWARD;
	std::string ID_REQUEST_MINIGAME_REWARD;
	std::string ID_REQUEST_MINIGAME_PERIODREWARD;
	std::string ID_REQUEST_LANTERN_RIDDLES_COMPELETE;
    
    std::string ID_REQUEST_GACHA_DETAIL = "V333";
    std::string ID_REQUEST_GET_REDPACKET_REWARD = "V332";
    std::string ID_REQUEST_GET_REDPACKET_INFO = "V334";
    
    std::string ID_REQUEST_UPLOAD_USER_HEADSHOT = "V311";
    std::string ID_REQUEST_UPLOAD_USER_NAME = "V312";
    std::string ID_REQUEST_DANGERROOM_START_DATA = "V318";
    std::string ID_REQUEST_DANGERROOM_SKIP = "V319";
    std::string ID_REQUEST_DANGERROOM_BOOST_QUERY = "V320";
    std::string ID_REQUEST_DANGERROOM_BOOST_END = "V321";
    std::string ID_REQUEST_DANGERROOM_ENDLEVEL = "V322";
    std::string ID_REQUEST_TRANSGENOSIS_RESULT = "V323";
    
    std::string ID_REQUEST_FAMILY_UNLOCK_PROPERTY = "V325";
    std::string ID_REQUEST_FAMILY_REFRESH_PROPERTY = "V326";
    std::string ID_REQUEST_FAMILY_REPLACE_PROPERTY = "V327";
    std::string ID_REQUEST_FAMILY_GET_INFO = "V328";
    
    std::string ID_REQUEST_DANGERROOM_RANK_REWARD = "V329";
    std::string ID_REQUEST_DINOSAURDANGER = "V337";
    
    std::string ID_REQUEST_GET_NEW_REDPACKET_REWARD = "V348";

    std::string ID_REQUEST_BUY_NEW_REDPACKET = "V349";
    std::string ID_REQUEST_DO_NEW_LOTTERY = "V357";
    std::string ID_REQUEST_BUY_PLANT_SPECIAL_OFFER = "V355";
    std::string ID_REQUEST_SOCCER_GAME_END = "V366";
    std::string ID_REQUEST_RSBVERSION = "I5";
    std::string ID_REQUEST_DISPLAYID = "I7";
    std::string ID_REQUEST_AUTH_HEARTBEAT = "I8";
    std::string ID_REQUEST_DAILY_SIGN_REWARD_LIST = "V389";
    std::string ID_REQUEST_DO_GIFT_BOX_REWARD = "V785";
    std::string ID_REQUEST_GET_VASEBREAKER_REWARD = "V788";

    //Joust
    std::string ID_REQUEST_POST_MATCH = "V380";
    std::string ID_REQUEST_POST_COMPLETE_MATCH = "V381";

    //Web game
    std::string ID_REQUEST_WEB_CALL_SETTLEMENT = "V385";
    std::string ID_REQUEST_WEB_CALL_LOTTERY = "V386";
    std::string ID_REQUEST_WEB_CALL_STORESCOREINFO = "V387";
    std::string ID_REQUEST_WEB_CALL_STORESCOREBUY = "V388";
    std::string ID_REQUEST_WEB_CALL_WATCHAD = "V390";

    std::string ID_REQUEST_RANKLIST_MONTHLY_CARD_EFFECT = "V391";
    std::string ID_REQUEST_BUY_SHOP_ITEM = "V392";
    std::string ID_REQUEST_SUMMERY_LOTTERY_2018 = "V393"; //New "V393" Instead of "V347";

    std::string ID_REQUEST_WEEKLY_RECHARGEREWARD_2019 = "V396";
    
    std::string ID_REQUEST_REQUEST_GROWTHPACKAGE_REWARD = "V410";

    std::string ID_REQUEST_REQUEST_EQUIP_COLLECTION = "V417";

    //BattleOrder
    std::string ID_ICLOUD_REQUEST_BATTLE_ORDER_LOTTERY = "V430";
    std::string ID_ICLOUD_REQUEST_BATTLE_ORDER_REWARD = "V431";
    std::string ID_ICLOUD_REQUEST_BATTLE_ORDER_TASK = "V432";
    std::string ID_ICLOUD_REQUEST_BATTLE_ORDER_RANK_AWARD = "V434";

    //Limit Lottery
    std::string ID_ICLOUD_REQUEST_GET_LIMITLOTTERY = "V781";
    std::string ID_ICLOUD_REQUEST_BUY_LIMITLOTTERY_CRYSTAL = "V782";
    std::string ID_ICLOUD_REQUEST_BUY_LIMITLOTTERY_CUPSHOP = "V783";

    //consume and receive
    std::string ID_ICLOUD_REQUEST_CONSUME_AND_RECEIVE = "V784";

    // platform gift
    std::string ID_ICLOUD_REQUEST_PLATFORM_GIFT = "V786";

    //synchronize groupBuy record
    std::string ID_ICLOUD_SYNCHRONIZE_GROUPBUY_RECORD = "V787";

    //Ad Box
    std::string ID_REQUEST_AD_BOX_REWARD = "V394";

    //New Year 2019
    std::string ID_REQUEST_OPEN_RED_PACKET = "V395";

    std::string ID_REQUEST_PIGGY_BANK_GEMS = "V397";

    std::string ID_REQUEST_BUY_NEWER_PRESENT = "V789";

    //TravelLog
    std::string ID_REQUEST_TRAVELLOG_INTEGRAL_CHEST = "V790";

    std::string ID_REQUEST_TRAVELLOG_WORLD_CHEST = "V791";

    //Dave Treasure
    std::string ID_REQUEST_DAVE_TREASURE_REWARD = "V792";
    std::string ID_REQUEST_BILLING_POINT = "V793";
    std::string ID_REQUEST_PLANT_LEVELUP_BY_BOOK = "V794";
    std::string ID_REQUEST_DAVE_TREASURE_TASK_FINISH = "V795";

    std::string ID_REQUEST_RENAiSSANCE_CHALLENGE_SHOP = "V796";

    //new avatar exchange
    std::string ID_REQUEST_EXCHANGE_PLANT_AVATAR = "V797";

    std::string ID_ICLOUD_REQUEST_CONSUME_AND_RECEIVE_EXTRA = "V799";

    std::string ID_ICLOUD_REQUEST_REFRESH_THEATER_SHOP = "V903";

    std::string ID_REQUEST_RICHMAN_ROLL = "V904";

    std::string ID_REQUEST_LUCKBAG_SELECT = "V905";

    std::string ID_REQUEST_BUY_DANGERROOM_SPECIAL_OFFER = "V906";

    std::string ID_REQUEST_AVATAR_TRANSGENOSIS_RESULT = "V907";

    std::string ID_REQUEST_SEND_DANGERROOM_PLANTLIST = "V908";

    std::string ID_REQUEST_NETWORK_SYNC_PROFILE = "V909";

    std::string ID_REQUEST_ADD_PLANT_PIECE = "V900";
    std::string ID_REQUEST_SET_PLANT_LEVEL = "V901";

    std::string ID_REQUEST_PAYMENT_ORDER_ID = "V911";
    std::string ID_REQUEST_PAYMENT_RESULT = "V912";
    std::string ID_REQUEST_SYNC_PAYMENT_RESULT = "V913";
    std::string ID_REQUEST_GET_LOST_PAYMENT = "V914";

    std::string ID_REQUEST_REQUEST_SECRET_GACHA = "V916";
    std::string ID_REQUEST_CHANGE_SECRET_GACHA = "V917";

    //Rift
    std::string ID_REQUEST_RIFT_END_PLAY = "V927";
    std::string ID_REQUEST_RIFT_PLAY = "V930";
    std::string ID_REQUEST_RIFT_LEADERBOARD = "V933";

    std::string ID_REQUEST_STEAY_ACCESSORY = "V931";
    std::string ID_REQUEST_RESET_ACCESSORY = "V932";

	std::string ID_REQUEST_PENNY_PERK_CHOOSE_PROTOCAL = "V929";	
    std::string ID_REQUEST_RIFT_SHOP_DATA =  "V928";

    //Happy Vase Breaker
    std::string ID_REQUEST_HAPPY_VASE_BREAKE = "V918";
    std::string ID_REQUEST_HAPPY_VASE_RESET = "V919";
    std::string ID_REQUEST_HAPPY_VASE_TASK_FINISH = "V920";

    std::string ID_REQUEST_NEWRECALL_REWARD = "V923";
    std::string ID_REQUEST_NEWRECALL_SELECT = "V924";
    
    std::string ID_REQUEST_ANNIVERSARY_TREASURE = "V934";

    std::string ID_REQUEST_RECHARGE_DAILYSIGN_ACTIVITY = "V925";

    std::string ID_REQUEST_SYNC_WORLDMAP_ACTIONS = "V922";

    std::string ID_REQUEST_AUTH_VERIFY_REWARD = "V926";

    std::string ID_REQUEST_FIRST_RECHARGE_EXTRA_GOT_BONUS = "V935";

    std::string ID_REQUEST_MONTHLY_CARD_UPLOAD_COLOR = "V937";
    std::string ID_REQUEST_CUSTOM_VOTING = "V936";

    std::string ID_REQUEST_FIGHT_ZODIAC = "V938";

    std::string ID_REQUEST_DANGERROOM_TRAINING = "V939";
    std::string ID_REQUEST_ADS_LOTTERY = "V940";

    std::string ID_REQUEST_NOVICESEVENDAYS_ACTIVATION = "V950";
    std::string ID_REQUEST_NOVICESEVENDAYS_RECEIVE = "V951";
    std::string ID_REQUEST_TUTORIAL_CHECK = "V952";

    std::string ID_REQUEST_CALL_OF_WISH_SELECT = "V953";
    std::string ID_REQUEST_CALL_OF_WISH_CALL = "V954";
    std::string ID_REQUEST_CALL_OF_WISH_REWARD = "V955";

    std::string ID_REQUEST_ARTIFACT_LEVEL_UP = "V959";
    std::string ID_REQUEST_ARTIFACT_RANK_UP = "V960";
    std::string ID_REQUEST_ARTIFACT_EQUIP = "V961";

    std::string ID_REQUEST_TRIGGER_ARTIFACT = "V962";

    std::string ID_REQUEST_SURVEY_BONUS = "V956";

    // rift validation
    std::string ID_REQUEST_VALIDATE_GAME_START = "V963";
    std::string ID_REQUEST_VALIDATE_GAME_PLAY = "V964";
    std::string ID_REQUEST_LEGEND_REWARD = "V965";

    // pvz1mode
    std::string ID_REQUEST_PVZ1MODE_SHOP_DATA = "V972";
    std::string ID_REQUEST_PVZ1MODE_PLAY =  "V975";
    std::string ID_REQUEST_PVZ1MODE_ENDPLAY = "V971";
    std::string ID_REQUEST_PVZ1MODE_ACHIEVEMENT = "V976";

    // New PVP
    std::string ID_REQUEST_NEW_PVP_MATCH_PLAYER = "V821";
    std::string ID_REQUEST_NEW_PVP_CANCEL_MATCH_PLAYER = "V827";
    std::string ID_REQUEST_NEW_PVP_SYNC_PLAYER = "V823";
    std::string ID_REQUEST_NEW_PVP_QUERY_SYNC = "V822";
    std::string ID_REQUEST_NEW_PVP_GAME_POST = "V824";
    std::string ID_REQUEST_NEW_PVP_GAME_SYNC = "V825";
    std::string ID_REQUEST_NEW_PVP_GAME_END_PLAY = "V826";
    std::string ID_REQUEST_NEW_PVP_DUAN_REWARD = "V831";
    std::string ID_REQUEST_NEW_PVP_SAVE_BATTLE_INFO = "V833";
    std::string ID_REQUEST_NEW_PVP_LEVELUP = "V832";
    std::string ID_REQUEST_NEW_PVP_REPORT = "V834";
    std::string ID_REQUEST_NEW_PVP_SHOP_DATA = "V835";

    std::string ID_REQUEST_NEW_PVP_BATTLE_PASS_LOTTERY = "V855";
    std::string ID_REQUEST_NEW_PVP_BATTLE_PASS_REWARD = "V856";
    std::string ID_REQUEST_NEW_PVP_BATTLE_PASS_TASK = "V857";

    // Custom Level
    std::string ID_REQUEST_CUSTOM_LEVEL_UPLOAD = "V720";
    std::string ID_REQUEST_CUSTOM_LEVEL_END = "V721";
    std::string ID_REQUEST_CUSTOM_LEVEL_LIKE = "V722";
    std::string ID_REQUEST_CUSTOM_LEVEL_VIEW = "V723";
    std::string ID_REQUEST_CUSTOM_LEVEL_FILTER = "V724";
    std::string ID_REQUEST_CUSTOM_LEVEL_SEARCH = "V725";
    std::string ID_REQUEST_CUSTOM_LEVEL_DETAILS = "V726";
    std::string ID_REQUEST_CUSTOM_LEVEL_DELETE = "V727";
    std::string ID_REQUEST_CUSTOM_LEVEL_FAVOURITE = "V728";
    std::string ID_REQUEST_CUSTOM_LEVEL_RANK = "V729";
    std::string ID_REQUEST_CUSTOM_LEVEL_PLAY_COUNT = "V730";
    std::string ID_REQUEST_CUSTOM_LEVEL_MODIFY_LEVEL_NAME = "V731";
    std::string ID_REQUEST_CUSTOM_LEVEL_MODIFY_DOWNLOADABLE = "V732";
    std::string ID_REQUEST_CUSTOM_LEVEL_START_LEVEL = "V733";
    std::string ID_REQUEST_CUSTOM_LEVEL_AUTHOR_LEVEL = "V734";
    std::string ID_REQUEST_CUSTOM_LEVEL_OBTAIN_PLAYCOIN = "V735";
    std::string ID_REQUEST_CUSTOM_LEVEL_APPRAISE = "V736";
    std::string ID_REQUEST_CUSTOM_LEVEL_REPORT = "V737";

    std::string ID_REQUEST_CHANGE_RANK_AVATAR = "V738";

    std::string ID_REQUEST_VERIFICATION_CODE = "V739";
    std::string ID_REQUEST_PHONE_NUMBER_LINK = "V740";
    std::string ID_REQUEST_CERTIFICATION_CONDITIONS = "V741";
    std::string ID_REQUEST_CERITFICATION = "V742";

    //Spring Festival Golden Egg
    std::string ID_REQUEST_SPRING_FESTIVAL_GOLDEN_EGG_SET_JACKPOT = "V980";
    std::string ID_REQUEST_SPRING_FESTIVAL_GOLDEN_EGG_MAIN_INFO = "V981";
    std::string ID_REQUEST_SPRING_FESTIVAL_GOLDEN_EGG_TASK = "V982";
    std::string ID_REQUEST_SPRING_FESTIVAL_GOLDEN_EGG_REFRESH = "V983";

    // Penny Classroom
    std::string ID_REQUEST_PENNY_CLASSROOM_GET_BONUS = "V760";

    std::string ID_REQUEST_ARBORDAY_WATER = "V984";
    std::string ID_REQUEST_ARBORDAY_TASK = "V985";
    std::string ID_REQUEST_ARBORDAY_HARVEST = "V986";
    std::string ID_REQUEST_ARBORDAY_PROGRESS_REWARD = "V860";
    std::string ID_REQUEST_ARBORDAY_GEM_BUY = "V861";

    std::string ID_REQUEST_AD_REWARD_INFO = "V765";

    std::string ID_REQUEST_SHARE_REWARD_INFO = "V766";

    // Card Game
    std::string ID_REQUEST_CARD_GAME_ENDLEVEL = "V421";
    std::string ID_REQUEST_CARD_GAME_ACHIEVEMENT_REWARD = "V422";
    std::string ID_REQUEST_CARD_GAME_RESET = "V423";
    std::string ID_REQUEST_CARD_GAME_SELECT_CARD = "V424";

    //uncharted mode
    std::string ID_REQUEST_REQUEST_SECRET_AREA_REWARD = "V413";
    std::string ID_REQUEST_UNCHARTED_MODE_UNLOCK_HARD_LEVEL = "V412";
    std::string ID_REQUEST_UNCHARTED_MODE_ENDLEVEL = "V411";
    std::string ID_REQUEST_COLLECTION_SWITCH_STATE = "V417";
    std::string ID_REQUEST_UNCHARTED_FESTIVAL_REWARD = "V414";
    std::string ID_REQUEST_UNCHARTED_TASK_REWARD = "V415";
    std::string ID_REQUEST_UNCHARTED_LEVEL_RESET = "V442";

    // Account Remove
    std::string ID_REQUEST_DELETE_ACCOUNT = "V435";
    std::string ID_REQUEST_RECOVER_ACCOUNT = "V436";
    std::string ID_REQUEST_GET_ACCOUNT = "V437";

    //Limited Summon
    std::string ID_REQUEST_LIMITED_SUMMON = "V810";
    std::string ID_REQUEST_LIMITED_SUMMON_REWARD = "V811";
    std::string ID_REQUEST_CHIPS_CONVERT = "V812";
    std::string ID_REQUEST_LIMITED_SUMMON_RANK_LIST = "V813";

    std::string ID_REQUEST_CARNIVAL_BUNDLE = "V815";
    std::string ID_REQUEST_CARNIVAL_REWARD = "V816";
    std::string ID_REQUEST_CARNIVAL_MARQUEE = "V820";

    std::string ID_REQUEST_GENE_LEVEL_UP = "V850";
    std::string ID_REQUEST_GENE_DRAW = "V851";
    std::string ID_REQUEST_GENE_CONFIG = "V852";
    std::string ID_REQUEST_NEWYEAR_GOODS_SET = "V853";

    // Cornucopia
    std::string ID_REQUEST_CORNUCOPIA_LEADERBOARD = "V865";
    std::string ID_REQUEST_CORNUCOPIA_PLAYER_RESULT = "V866";
    std::string ID_REQUEST_CORNUCOPIA_GACHA = "V867";
    std::string ID_REQUEST_CORNUCOPIA_TASK = "V868";
    std::string ID_REQUEST_CORNUCOPIA_BUBBLE_REWARD = "V869";

    //wishing pool
    std::string ID_REQUEST_WISHINGPOOL_LOTTERY = "V870";
    std::string ID_REQUEST_WISHINGPOOL_REWARD = "V871";
    std::string ID_REQUEST_WISHINGPOOL_SET_LOTTERY = "V872";

    //plant cultivate
    std::string ID_REQUEST_PLANT_CULTIVATE_SELECT_PLANT = "V987";
    std::string ID_REQUEST_PLANT_CULTIVATE_TASK_REWARD = "V988";
    std::string ID_REQUEST_PLANT_CULTIVATE_GET_CULTIVATE = "V989";
    std::string ID_REQUEST_PLANT_CULTIVATE_EXCHANGE_INTEGRAL = "V990";

    //gift for return
    std::string ID_REQUEST_GIFT_FOR_RETURN_DAILY_SIGN = "V510";
    std::string ID_REQUEST_GIFT_FOR_RETURN_TASK_REWARD = "V511";
    std::string ID_REQUEST_GIFT_FOR_RETURN_TRIAL_CARD = "V512";

    //trial card
    std::string ID_REQUEST_SYNCHORIZE_TRIAL_CARD = "V520";
    std::string ID_REQUEST_USE_TRIAL_CARD = "V521";

    //party assist
    std::string ID_REQUEST_PARTY_ASSIST_ASSIST = "V991";
    std::string ID_REQUEST_PARTY_ASSIST_RESET = "V992";
    std::string ID_REQUEST_PARTY_ASSIST_TASK_REWARD = "V993";
    std::string ID_REQUEST_PARTY_ASSIST_TICKET_AUTO_EXCHANGE = "V994";

    std::string ID_REQUEST_ARTIFACT_BLESS = "V995";
    std::string ID_REQUEST_ARTIFACT_BLESS_SAVE = "V996";

    std::string ID_REQUEST_TRIGGER_NEWPLAYER_SIGN = "V997";
    std::string ID_REQUEST_NEWPLAYER_SIGN = "V998";
    std::string ID_REQUEST_TRIGGER_NEWPLAYER_SPECIAL_GIFT = "V1005";
    std::string ID_REQUEST_NEWPLAYER_SPECIAL_GIFT = "V1006";
    std::string ID_REQUEST_TRIGGER_NEWPLAYER_DISCOUNT_SHOP = "V1007";
    std::string ID_REQUEST_NEWPLAYER_DISCOUNT_SHOP = "V1008";

    //tutorial skip
    std::string ID_REQUEST_SKIP_TUTORIAL = "V513";

    //dave kitchn
    std::string ID_REQUEST_DAVE_KITCHEN_EXCHANGE = "V711";
    std::string ID_REQUEST_DAVE_KITCHEN_TASK = "V712";
    std::string ID_REQUEST_DAVE_KITCHEN_BUNDLE = "V713";

    //dragon treasure
    std::string ID_REQUEST_DRAGON_TREASURE_LOTTERY = "V714";
    std::string ID_REQUEST_DRAGON_TREASURE_RESET = "V715";
    std::string ID_REQUEST_DRAGON_TREASURE_SHOP = "V716";
    std::string ID_REQUEST_DRAGON_TREASURE_AUTO_EXCHANGE = "V717";

    void InitCommon()
    {
        ID_ICLOUD_STATIC_CONFIG                       = "V207";
        ID_ICLOUD_USE_GEM                               = "V209";
        ID_ICLOUD_REQUSET_LUA_GENERAL                   = "V222";
        ID_ICLOUD_DO_GACHA                              = "V228";
        ID_ICLOUD_DO_NEW_GACHA                          = "V313";
        ID_ICLOUD_GETSTATE_THIRDPART_PLATFORMS          = "V234";
        ID_ICLOUD_LOGIN_THIRDPART_PLATFORMS             = "V235";
        ID_ICLOUD_BINDING_THIRDPART_PLATFORMS           = "V236";
        ID_ICLOUD_UNBOUND_THIRDPART_PLATFORMS           = "V237";
        ID_ICLOUD_TRANSFER_THIRDPART_PLATFORMS          = "V238";
        ID_ICLOUD_CLEARNOTIFY_THIRDPART_PLATFORMS       = "V239";
        ID_REQUEST_CODE_REWARD                          = "V330";
        ID_REQUEST_WECHAT_REWARD						= "V400";
		ID_REQUEST_MINIGAME_REWARD						= "V801";
		ID_REQUEST_MINIGAME_PERIODREWARD				= "V803";
		ID_REQUEST_LANTERN_RIDDLES_COMPELETE			= "V362";
		ID_REQUEST_ACTIVE_YUANBAO_REWARD				= "V363";
        
        ID_ICLOUD_GET_SERVICE_STATUS                    = "V245";
        ID_ICLOUD_GET_RANK_LIST                         = "V246";
        ID_REQUEST_BOSS_CHALLENGE_REWARD                     = "V249";
        ID_REQUEST_BOSS_CHALLENGE_LEVEL_END                = "V273";
#ifdef HOST_ANDROID
        ID_REQUEST_VERIFY_SALES_REWARD                  = "V217";
        ID_REQUEST_ACTIVE_ACTIVITY_STATES               = "V218";
        ID_REQUEST_ACTIVE_LEVELOFTHEDAY_REWARD          = "V221";
        ID_REQUEST_UPDATE_CHARGE_INFO                   = "V223";
        ID_ICLOUD_DAILYSIGN_WITHTW                      = "V225";
        // ac log
        ID_REQUEST_ACLOG 								= "V750";
        ID_REQUEST_SYNC_PLAYER_DATA						= "V751";
        ID_REQUEST_DOWNLOAD_PLAYER_DATA					= "V752";
#else
        ID_REQUEST_VERIFY_SALES_REWARD                  = "V297";
        ID_REQUEST_ACTIVE_ACTIVITY_STATES               = "V298";
        ID_REQUEST_ACTIVE_LEVELOFTHEDAY_REWARD          = "V300";
        ID_REQUEST_UPDATE_CHARGE_INFO                   = "V999"; //Might be used sometime
#endif
        ID_ICLOUD_REQUEST_INSTANCE_STATUS               = "V299";
        
        ID_ICLOUD_REQUEST_GET_CONSUMPTION_REWARD        = "V269";
		ID_ICLOUD_REQUEST_GET_STONELOTTERY				= "V800";
        ID_REQUEST_ACTIVITY_LIST                        = "V303";
        ID_REQUEST_ACTIVITY_LEVEL_END                   = "V304";
        ID_REQUEST_SUMMERY_LOTTERY                      = "V347";//New "V347" Instead of "V305";
        ID_REQUEST_SUMMER_PLANTCOMPOSIT                 = "V306";
        
        ID_REQUEST_ADS_REWARD                           = "V309";
        ID_REQUEST_USER_INFO                            = "V310";

		ID_ICLOUD_REQUEST_GET_7DAYSLOGINREWARD			= "V401";
		ID_ICLOUD_REQUEST_GET_CHRISTMASLOGINREWARD		= "V350";
        ID_ICLOUD_REQUEST_GET_FIRSTCHARGESUCCEED        = "V356";
        ID_ICLOUD_REQUEST_GET_SPRINGLOGINREWARD         = "V361";
        ID_ICLOUD_REQUEST_GET_SPRINGBUYPLANT            = "V364";
        ID_ICLOUD_REQUEST_WORLDCUPBEGINNAME             = "V365";
        ID_ICLOUD_REQUEST_BUYWORLDCUPTICKET             = "V367";
        ID_ICLOUD_REQUEST_UNLOCKWORLDCUPTEAM            = "V370";
        ID_ICLOUD_REQUEST_CLEARWORLDCUPDATA             = "V371";
		ID_ICLOUD_REQUEST_GET_REWARDPLANTID				= "V307";
		ID_ICLOUD_REQUEST_GET_CHRISTMASCHARGEREWARD		= "V351";
		ID_ICLOUD_REQUEST_GET_RECHARGEREWARD			= "V402";
        ID_ICLOUD_REQUEST_PVP_SHOP                      = "V501";
        ID_ICLOUD_REQUEST_BUY_PVP_SHOP_OBJECT           = "V502";

        ID_ICLOUD_REQUEST_BUYZMATCHTICKET               = "V384";
        ID_ICLOUD_REQUEST_ZMATCHBUYITEM                 = "V383";
        ID_ICLOUD_REQUEST_GETZMATCHSHOPDATA                 = "V382";
        // both for android & ios
        ID_REQUEST_BOARD_INFOLIST           = "V600";
        ID_REQUEST_BOARD_INFO_GET           = "V601";
        
        
        ID_UUID_INIT						= "C10001";
        ID_UUID_CHECK						= "C10002";

        // pvp
        ID_REQUEST_PVP_LOGIN                = "P1";
        ID_REQUEST_PVP_EDIT_PLANT           = "P3";
        ID_REQUEST_GET_PVP_PLANT_INFOS      = "P4";
        ID_REQUEST_PVP_PLANT_INFOS          = "P5";
        ID_REQUEST_PVP_BATTLE_ENDING        = "P6";
        ID_REQUEST_PVP_PLAYBACK_LIST        = "P7";
        ID_REQUEST_PVP_PLAYBACK_DOWNLOAD    = "P8";
        ID_REQUEST_PVP_PLAYBACK_UPLOAD      = "P9";
        ID_REQUEST_PVP_TRAINIGN_INFOS   = "P11";
        ID_REQUEST_PVP_TRAINIGN_SELL    = "P12";
        ID_REQUEST_PVP_TRAINIGN_ZOMBIE_REFRESH = "P13";
        ID_REQUEST_PVP_TRAINIGN_ZOMBIE  = "P14";
        ID_REQUEST_PVP_TRAINIGN_FINISH_AT_ONCE = "P15";
        ID_REQUEST_PVP_TRAINIGN_FINISH_GEMS = "P16";
        ID_REQUEST_PVP_ENTRY            = "P49";
        ID_REQUEST_PVP_MAP_INFO         = "P50";
        ID_REQUEST_PVP_ACHIEVE          = "P51";
        ID_REQUEST_PVP_UNLOCK           = "P52";
        ID_REQUEST_PVP_CHANGE_ENEMY     = "P53";
        ID_REQUEST_PVP_COMPENSATION_NOTICE = "P54";
        ID_REQUEST_PVP_CHANGE_PLAYER    = "P10";
        ID_REQUEST_PVP_PING             = "P20";
        ID_REQUEST_PVP_RANK             = "P21";
        ID_REQUEST_PVP_OTHERSZB_LIST    = "P22";
        ID_REQUEST_PVP_BUY_COIN         = "P121";
        ID_REQUEST_PVP_LAB_ENTER        = "P122";
        ID_REQUEST_PVP_BEGIN_UPGRADE    = "P123";
        ID_REQUEST_PVP_COMPLETE_UPGRADE    = "P124";
        ID_REQUEST_ACHIEVEMENT          = "P100";
        ID_REQUEST_ACHIEVEMENT_REWARD   = "V343"; //"P101";
        ID_REQUEST_PVP_SUBPVPCOIN         = "P127";
        ID_REQUEST_PVP_UPGRADE_COMPLETE_GEM = "P128";
        ID_REQUEST_PVP_UPGRADE_CANCEL   = "P130";
    }
 
}PacketID;

#endif
