#ifndef QUICKJUMPUTIL_H
#define QUICKJUMPUTIL_H

#include "PVZDB.h"
#include "Singleton.h"

#pragma mark - QuickJumpUtil

class QuickJumpUtil : public LazySingleton<QuickJumpUtil>
{
public:
    QuickJumpUtil();
    virtual ~QuickJumpUtil();

    void ShowStarConvert();
    void ShowGachaStore();
    void ShowPlantLevelUp();
    void ShowPvP();
    void ShowAdventure();
    void ShowBattleZ();
    void ShowTravelLog();
    void ShowEndLess();
    void ShowPennyRift();
    void ShowPlantFamily();
    void ShowPlantGeneEnhancement();
    void ShowArtifactCultivation();
    void ShowTransgenosis();
    void ShowChallengeLevel();
    void ShowAvatarListView();
    void ShowSecretStore();
    void ShowNoviceSevenDays();
    void ShowCallofWish();
    void ShowArtifactPresent();
    void ShowPvz1Achievement();
    void ShowPvz1();
    void ShowArborDay();
    void ShowNewPVP();
    void ShowNewPVPBattlePass();

    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);
    void onNotifyStaticConfig(int result, const class S2C_StaticConfig* data);
    void onPVPLogin(bool i_success);

protected:
    bool requested;
};

#define gQuickJumpUtil (QuickJumpUtil::GetInstancePtr())

#endif
