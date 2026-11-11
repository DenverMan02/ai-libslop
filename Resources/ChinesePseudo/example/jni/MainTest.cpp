
#include <android/log.h>
#include <dlfcn.h>

#include "LawnApp.h"
#include "Board.h"
#include "StarConvert.h"
#include "PlantUtils.h"
#include "TodLib/TodStringFile.h"

#include "And64InlineHook.hpp"
#include "WidgetTest.h"

#include "SingletonExtern.h"

#define LOG_TAG "SrcExt"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

WidgetTest *gWidgetTest;

void OutputDebugStr(const char* fmt ...)
{
    va_list args;
    va_start(args, fmt);
    if (strncmp(fmt, "LevelUtils::readLevelMetaData", 29) &&
        strncmp(fmt, "creating render list", 20) &&
        strncmp(fmt, "start sort", 10) &&
        strncmp(fmt, "resetting render list", 21) &&
        strncmp(fmt, "end sort, start draw", 20) &&
        strncmp(fmt, "end draw", 8)
    ) {
        __android_log_vprint(ANDROID_LOG_VERBOSE, "SexyDebug", fmt, args);
    }
    va_end(args);
}

long GetDigitalSignature()
{
    return -865154223;
}

bool IsForbiddenPlatform()
{
    return false;
}

void TryCheckAccount()
{
    gMessageRouter->Broadcast(Message::SyncPlayerInfoFinish, true);

    //gGameStateMgr->StartLevel(g_strCheatwldName, "egypt6");
}

void (*_OnStarConverted)(StarConvertObject *self, bool i_success);
void StarConvertObject::OnStarConverted(bool i_success)
{
    return _OnStarConverted(this, true);
}

bool (*_PlayerHasCompletedTutorial)(const PlayerInfo *self, MapTutorialState i_state);
bool PlayerInfo::PlayerHasCompletedTutorial(MapTutorialState i_state) const
{
    if (i_state == TUTORIAL_NEW_DAILY_SIGN || i_state == TUTORIAL_GACHA_INTRO_1 ||
        i_state == TUTORIAL_GACHA_INTRO_2 || i_state == TUTORIAL_ACCESSORY ||
        i_state == TUTORIAL_PLANTADVENTURE_INTRO || i_state == TUTORIAL_TRANSGENOSIS ||
        i_state == TUTORIAL_GENEENHANCEMENT_NEW
    ) {
        //this->CompleteTutorial(i_state);
        return true;
    }
    return _PlayerHasCompletedTutorial(this, i_state);
}

bool (*_IsUnlockRechargeNode)(PlayerInfo *self, RechargeNode i_node);
bool PlayerInfo::IsUnlockRechargeNode(RechargeNode i_node)
{
    if (i_node == RECHARGE_DOUBLE_SPEED) {
        //this->UnlockRechargeNode(i_node);
        return true;
    }
    return _IsUnlockRechargeNode(this, i_node);
}

void PeashooterPlantfood::Update(Plant *i_owner, const SexyVector3 &i_plantPosition, float i_plantScale, const PlantAction &i_action)
{
    pvztime_t currentTime = PVZ_T() - this->m_startTime;
    int shotsLeft = this->m_shotTotal - this->m_shotsFired;
    int shotsDue = (currentTime * this->m_shotsPerSecond) - this->m_shotsFired;
    int shotsToFireNow = std::min<int>(shotsDue, shotsLeft);
    if (shotsToFireNow > 0) {
        bool isRotated = false;
        SexyTransform2D rotationTransform;
        if (!Sexy::IsNearZero(this->m_rotation)) {
            isRotated = true;
            rotationTransform.CreateRotation(this->m_rotation);
        }
        for (int i = 0; i != shotsToFireNow; ++i) {
            //z (also known as height) will visually move projectile at y axis, but shadow will stay at y pos.
            Projectile *proj = gLawnApp->m_board->AddProjectile(
                i_plantPosition.x + (i_action.SpawnOffset.x * i_plantScale),
                i_plantPosition.y,
                i_plantPosition.z - (i_action.SpawnOffset.y * i_plantScale),
                i_action.Projectile, i_owner);

            //NOTE: Repeater level and costumes are not implemented

            proj->SetDamageFlags(proj->GetDamageFlags() | DAMAGE_FROM_PLANTFOOD_EFFECT);
            if (i_owner->GetType()->TypeName == "bitpeashooter") {
                proj->ShouldDestroyOnOutOfStage(1);
                proj->SetBaseDamageAmount(this->m_extraDamage);
            } else {
                proj->SetAppendExtraDamage(this->m_extraDamage);
            }

            SexyVector3 projPos = proj->GetPosition();
            SexyVector2 wobbleOffset = SexyVector2(0.0f, sinf(this->m_shotsFired * 10.0f) * 5.0f);
            if (isRotated)
                wobbleOffset = rotationTransform * wobbleOffset;
            projPos.x += wobbleOffset.x;
            projPos.y += wobbleOffset.y;
            projPos.z -= sinf(this->m_shotsFired * 10.0f) * 10.0f;
            proj->SetPosition(projPos);
            if (isRotated)
                proj->ApplyRotationToVelocity(rotationTransform);

            SexyVector3 projVelScale = proj->GetVelocityScale();
            projVelScale.x *= Rand(0.7f) + 1.0f;
            proj->SetVelocityScale(projVelScale);

            if (this->m_backwardsProjectiles) {
                proj->SetVelocityScale(-projVelScale.x, projVelScale.y, projVelScale.z);
                proj->SetMirrored(projVelScale.x > 0);
            }

            ++this->m_shotsFired;
        }
    }
}

void (*_Sexy_SexyAppRun)(Sexy::SexyAppBase *app);
void Sexy::SexyAppRun(Sexy::SexyAppBase *app)
{
    _Sexy_SexyAppRun(app);
    gWidgetTest = new WidgetTest();
}

void (*_PVZDB_LoadPackageForTable)(PVZDB *self, PVZDB::TableIndex i_table, RtWeakPtr<GenericResFile> i_packageResource);
void PVZDB::LoadPackageForTable(TableIndex i_table, RtWeakPtr<GenericResFile> i_packageResource)
{
    std::string fullPath = "/sdcard/Android/data/" + gLawnApp->GetPackageName() + "/" +
        i_packageResource->GetFilePath();
    fullPath.replace(fullPath.length() - 4, 4, "json");
    //LOGI("File: %s", fullPath.c_str());
    if (gSexyApp->FileExists(fullPath)) {
        Sexy::Buffer jsonFile;
        gSexyApp->ReadBufferFromFile(fullPath, &jsonFile);
        std::string jsonText((char *)jsonFile.GetDataPtr(), jsonFile.GetDataLen());
        bool didLoad = this->LoadPackageForTableFromJson(i_table, jsonText);
        if (didLoad)
            return;
    }
    _PVZDB_LoadPackageForTable(this, i_table, i_packageResource);
}

int64_t RetZero()
{
    return 0;
}

__attribute__((constructor))
void mainFunc()
{
    LOGI("Extension lib entry");
    //Needed for gdb
    setpgid(0, 0);

    A64HookFunction(dlsym(RTLD_NEXT, "_ZN4Sexy15OutputDebugStrFEPKcz"),
        (void *)OutputDebugStr, nullptr);

    A64HookFunction(dlsym(RTLD_NEXT, "_ZN4Sexy21AndroidAntiHackDriver19GetDigitalSignatureEv"),
        (void *)GetDigitalSignature, nullptr);
    A64HookFunction(dlsym(RTLD_NEXT, "_ZN7LawnApp19IsForbiddenPlatformEv"),
        (void *)IsForbiddenPlatform, nullptr);

    A64HookFunction(dlsym(RTLD_NEXT, "_ZN16AccountRemoveMgr15TryCheckAccountEb"),
        (void *)TryCheckAccount, nullptr);

    //Sexy::AndroidHttpDriver::GetNetworkStatus
    A64HookFunction(dlsym(RTLD_NEXT, "_ZN4Sexy17AndroidHttpDriver16GetNetworkStatusEv"),
        (void *)RetZero, nullptr);
    //androidNetworkMsgProcess::SendHttpRequest block
    A64HookFunction(dlsym(RTLD_NEXT, "_ZN24androidNetworkMsgProcess15SendHttpRequestERSt3mapISsSsSt4lessISsESaISt4pairIKSsSsEEEbRS4_bb"),
        (void *)RetZero, nullptr);
    //Star convert Plants Level no network fix
    A64HookFunction(dlsym(RTLD_NEXT, "_ZN17StarConvertObject15OnStarConvertedEb"),
        (void *)&StarConvertObject::OnStarConverted, (void **)&_OnStarConverted);
    //Disable broken tutorials
    A64HookFunction(dlsym(RTLD_NEXT, "_ZNK10PlayerInfo26PlayerHasCompletedTutorialE16MapTutorialState"),
        (void *)&PlayerInfo::PlayerHasCompletedTutorial, (void **)&_PlayerHasCompletedTutorial);

    //Enable Turbo
    A64HookFunction(dlsym(RTLD_NEXT, "_ZN10PlayerInfo20IsUnlockRechargeNodeE12RechargeNode"),
        (void *)&PlayerInfo::IsUnlockRechargeNode, (void **)&_IsUnlockRechargeNode);

#pragma region LUA_DISABLE
#if 1
    //Sexy::LazySingleton<Lua::CLuaEngine>::GetInstancePtr
    A64HookFunction(dlsym(RTLD_NEXT, "_ZN4Sexy13LazySingletonIN3Lua10CLuaEngineEE14GetInstancePtrEv"),
        (void *)RetZero, nullptr);
    //LuaUpdateMgr::Init
    A64HookFunction(dlsym(RTLD_NEXT, "_ZN12LuaUpdateMgr4InitEv"),
        (void *)RetZero, nullptr);
    //Lua::CLuaEngine::ExecuteTableFunction called by UIWidget::ResetUI
    A64HookFunction(dlsym(RTLD_NEXT, "_ZN3Lua10CLuaEngine20ExecuteTableFunctionEPKcS2_"),
        (void *)RetZero, nullptr);
    //Lua::CLuaEngine::OnNetworkMsg called by INetworkMsgProcess::ProcessMsg
    A64HookFunction(dlsym(RTLD_NEXT, "_ZN3Lua10CLuaEngine12OnNetworkMsgESsR11_NetWorkMsg"),
        (void *)RetZero, nullptr);
    //LawnApp::ShowPlantFamilyUI LUA based, so just remove.
    A64HookFunction(dlsym(RTLD_NEXT, "_ZN7LawnApp17ShowPlantFamilyUIEi"),
        (void *)RetZero, nullptr);
#endif
#pragma endregion


    A64HookFunction(dlsym(RTLD_NEXT, "_ZN4Sexy10SexyAppRunEPNS_11SexyAppBaseE"),
        (void *)&Sexy::SexyAppRun, (void **)&_Sexy_SexyAppRun);
    A64HookFunction(dlsym(RTLD_NEXT, "_ZN19PeashooterPlantfood6UpdateEP5PlantRKN4Sexy11SexyVector3EfRK11PlantAction"),
        (void *)&PeashooterPlantfood::Update, nullptr);
    //Load json's from /sdcard/Android/data/.../packages for testing
    A64HookFunction(dlsym(RTLD_NEXT, "_ZN5PVZDB19LoadPackageForTableENS_10TableIndexEN4Sexy9RtWeakPtrINS1_14GenericResFileEEE"),
        (void *)&PVZDB::LoadPackageForTable, (void **)&_PVZDB_LoadPackageForTable);

    LOGI("Extension lib loaded!");
}
