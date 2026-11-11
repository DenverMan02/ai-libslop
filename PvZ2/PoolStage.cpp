#include "pch.h"
#include <cfloat>
#include "PoolStage.h"
#include "PopAnimRig.h"
#include "Board.h"
#include "BoardRegion.h"
#include "Sexy/LawnApp.h"
#include "LevelModuleManager.h"

#include <Sexy/Delegate.h>

using Sexy::make_delegate;
using Sexy::Rect;
using Sexy::Color;
using Sexy::RtWeakPtr;

void* PoolStage::vftable = nullptr;
Sexy::RtClass* PoolStage::s_rtClass = nullptr;

void* PoolStageProperties::vftable = nullptr;
Sexy::RtClass* PoolStageProperties::s_rtClass = nullptr;

// TODO: Need to put the pool anim
void PoolStage::OnLoadCompleted()
{
	auto board = Board::GetBoard();
	std::vector<int> poolRows = { 1, 2, 3 };

	for (int y : poolRows) {
		auto tideWaterRegion = board->AddRegion<BoardRegionTideWater>();
		Rect regionRect = { 0, y, 9, 1 };
		tideWaterRegion->SetRegionFromGridSquare(regionRect);
	}
    auto props = reinterpret_cast<PoolStageProperties*>(this->m_propertySheet.Get());
    auto type = Effect_PopAnim::StaticGetType();
    auto popAnim = CallFunc<Effect_PopAnim*, Board*, Sexy::RtClass*>(0xAA1EFC, board, type);
	this->m_poolAnim.FromOther((RtWeakPtr<Effect_PopAnim>*) & popAnim->m_thisPtr);
    popAnim->SetFromResource("POPANIM_EFFECTS_ZOMBIE_POOL_TOXICWATER_CHANGE");
    popAnim->SetFocusFracAndScale(1);
    popAnim->m_standaloneEffectFlags |= 32;
    Sexy::SexyVector3 pos = Sexy::SexyVector3(561.0f, 385.0f, 0.0f);
    popAnim->SetPositionAndLayer(pos, 150102);
    AnimationSequence seq;
    CallFunc<void, AnimationSequence*, const SexyString&, int, float>(0x1230B0C, &seq, "idle", 0, FLT_MAX);
    CallFunc<void, Effect_PopAnim*, AnimationSequence*>(0x1232950, popAnim, &seq);
	auto popAnimRig = reinterpret_cast<PopAnimRig*>(popAnim->m_rig.Get());
	auto lawnApp = LawnApp::GetInstance();
	popAnimRig->m_popAnim->mDrawScale = lawnApp->m_unkResValue / 1536.0f;
    popAnimRig->m_popAnim->mColor = {props->PoolAnimColor.mRed, 
                                    props->PoolAnimColor.mGreen, 
                                    props->PoolAnimColor.mBlue, 
                                    props->PoolAnimColor.mAlpha};

}

void PoolStage::OnPostLoad()
{
	CallFunc<void>(0x822284, this);
    auto props = reinterpret_cast<PoolStageProperties*>(this->m_propertySheet.Get());
	auto popAnim = reinterpret_cast<Effect_PopAnim*>(this->m_poolAnim.Get());
    popAnim->SetFromResource("POPANIM_EFFECTS_ZOMBIE_POOL_TOXICWATER_CHANGE");
    popAnim->SetFocusFracAndScale(1);
    popAnim->m_standaloneEffectFlags |= 32;
    Sexy::SexyVector3 pos = Sexy::SexyVector3(561.0f, 385.0f, 0.0f);
    popAnim->SetPositionAndLayer(pos, 150102);
    AnimationSequence seq;
    CallFunc<void, AnimationSequence*, const SexyString&, int, float>(0x1230B0C, &seq, "idle", 0, FLT_MAX);
    CallFunc<void, Effect_PopAnim*, AnimationSequence*>(0x1232950, popAnim, &seq);
    auto popAnimRig = reinterpret_cast<PopAnimRig*>(popAnim->m_rig.Get());
    auto lawnApp = LawnApp::GetInstance();
    popAnimRig->m_popAnim->mDrawScale = lawnApp->m_unkResValue / 1536.0f;
    popAnimRig->m_popAnim->mColor = { props->PoolAnimColor.mRed,
                                    props->PoolAnimColor.mGreen,
                                    props->PoolAnimColor.mBlue,
                                    props->PoolAnimColor.mAlpha };
}

void PoolStage::RegisterEvents()
{
	CallFunc<void>(0x820F30, this);
	auto delegate = make_delegate(&PoolStage::OnLoadCompleted, *this);
	Board::GetBoard()->GetLevelModuleManager()->m_onLoadComplete.AddDelegate(delegate);
}

void PoolRegisterEvents(PoolStage* poolStage)
{
	poolStage->RegisterEvents();
}


void PoolOnPostLoad(PoolStage* module) {
    module->OnPostLoad();
}

Sexy::RtClass* PoolStagePropsGetModule() {
	return PoolStage::StaticGetType();
}


void PoolStage::ModInit() {
    LOGI("PoolStageModule mod init");

    vftable = CopyVFTable(getActualOffset(0x23A25E0), 28);
    PatchVFTable(vftable, (void*)PoolStage::StaticGetType, 0);
    PatchVFTable(vftable, (void*)PoolRegisterEvents, 7);
    PatchVFTable(vftable, (void*)PoolOnPostLoad, 11);
    PoolStage::StaticGetType();
    LOGI("PoolStageModule finish init");
}

void PoolStageProperties::ModInit() {
    LOGI("PoolStageProperties init");

    vftable = CopyVFTable(getActualOffset(0x23A26D0), 18);

    PatchVFTable(vftable, (void*)PoolStageProperties::StaticGetType, 0);
    PatchVFTable(vftable, (void*)PoolStagePropsGetModule, 14);
    PoolStageProperties::StaticGetType();

    LOGI("PoolStageProperties finish init");
}
