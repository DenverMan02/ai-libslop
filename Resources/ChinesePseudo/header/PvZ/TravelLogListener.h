#ifndef TRAVELLOGLISTENER_H
#define TRAVELLOGLISTENER_H

#include<string>

struct LevelDefinitionForTask
{
    LevelDefinitionForTask()
    :levelName(""),
    levelNumber(0),
    isHard(false),
    isBoss(false),
    isBattleZ(false),
    isPvP(false),
    isEpicTask(false),
    isChallenge(false),
    challengeDifficulty(-1),
    isPennyLevel(false),
    isPennyBoss(false),
    pennyDifficulty(-1),
    isEndless(false),
    isWin(false),
    isNormalLevel(false),
    sunCurrency(0)
    {}

    std::string levelName;
    int levelNumber;
    bool isHard;
    bool isBoss;
    bool isBattleZ;
    bool isPvP;
    bool isEpicTask;
    bool isChallenge;
    int challengeDifficulty;
    bool isPennyLevel;
    bool isPennyBoss;
    int pennyDifficulty;
    bool isEndless;
    bool isWin;
    bool isNormalLevel;//not a special level,like battlez, pvp etc
    int sunCurrency;
};

enum GenericTaskType
{
    GENERIC_TASK_TYPE_INVILD = 0,
    GENERIC_TASK_TYPE_CALL_OF_WISH = 1,
};

struct NewPVPAddZombieMessageData
{
	NewPVPAddZombieMessageData() {}
	NewPVPAddZombieMessageData(int i_type, int i_level, bool i_isInSpeedUp, bool i_isInHP, bool i_isInImmune)
	: Type(i_type), Level(i_level), IsInSpeedUp(i_isInSpeedUp), IsInHP(i_isInHP), IsInImmune(i_isInImmune)
	{}

	int Type = 0;
	int Level = 1;
	bool IsInSpeedUp = false;
	bool IsInHP = false;
	bool IsInImmune = false;
};

class Plant;
class Zombie;
class BoardEntity;
namespace Message
{
    void LevelEndForTask(LevelDefinitionForTask* i_def);
    void ObtainPlantChips(int i_chip);
    void ObtainIntegral(int i_num);
    void ObtainDaveTreasureIntegral(int i_num);
    void FinishPlantAdventure(int worldId);
    void FinishPennyGacha(int type, int num);
    void FinishSecretGacha(int num);
    void FinishLimitGacha(int num);
    void ExtinguishFire();
    void PlantTransgenic();
    void AvatarTransgenic();
    void SaveTaskState();
    void DeleteTask(int TaskID);
    void ReBuildTasks();
    void RefreshSomeTasksData();
    void GemsRecharge(int num);
    void SetDailyGemsRecharge(int num);
    void SetGemsRecharge(int num);
    void ObtainPennySignal(int num);
    void ConsumeFuel(int num);
    void SettlePennyLevel();
    void ObtainStar(int num);
    void PlantLevelUp();
    void FinishTravelogDailyTask();
    void FinishTravelogSpecialTask();
    void FinishTravelogWorildTask();
    void PlantFamilyRefresh();
    void SetPvPLabLevel(int label, int level);
    void SetDangerRoomMaxLevel(int level);
    void PVPBuyShopObject();
    void SteadyAccessory();
    void ObtainAccessoryPieces(int i_pieceId, int i_number);
    void BuySecretStore();//水晶商店
    void GenericObtainIntegral(int taskType, int i_num);
    void PvZ1FinishLevel(int levelNodeID, bool isHard);
    void MagnetShroomPullHelm(Plant* i_plant, BoardEntity* i_entity);
    void PlantHypnoZombie(Plant* i_plant, Zombie* i_zombie);
    void ShieldArtifactKillZombie(Zombie* i_zombie);
    void VaseArtifactProducePlantCard(const std::string& plantName);
    void EvaluateCustomLevel(bool i_like);
    void PublishCustomLevel();
    void HappyVaseBreaker_BreakVase();
    void FestivalGoldenEgg_BreakEgg();
    void FightZodiac_UseFirework(int i_fireworkNum, bool i_killedZodiac);
    void BeforeChangeMaterialNumber(int i_matId, int i_diff);
    void RichMan_RollDice();
    void WinBossChallenge();
    void BuyRealSecretStore();//神秘商店
    void NewPVPAddPlant(int i_type, int i_level);
    void NewPVPAddZombie(NewPVPAddZombieMessageData* i_data);
    void NewPVPUpgradeSun();
    void NewPVPDamageOpponentBases(float i_DamagePoints);
    void NewPVPPassLevel(bool i_isWin, bool i_isFullHitpoints, int i_curRound);
    void NewPVPFirstBlood();
    void NewPVPCompleteTask(int i_taskID);
    void ObtainGeneSequence(int i_num);
    void ObtainGeneEssence(int i_num);
    void RecruitNum();
    void RecruitStarNum();
    void FinishEndlessLevel(bool i_win);
}

#endif
