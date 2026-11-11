//
//  GridItemVase.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 6/25/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__GridItemVase__
#define __PlantsVersusZombies2__GridItemVase__

#include "GridItem.h"
#include "PopAnimRig.h"
#include "EntityComponent.h"

class Collectable;
class GridItemVase;

namespace Message
{
	void CollectableSpawnedFromVase(Collectable* i_collectable);
	void VaseBroken(GridItemVase* i_vase);
}

class GridItemVaseProps : public GridItemPropertySheet
{
public:
	RT_CLASS_DEFINE(GridItemVaseProps, GridItemPropertySheet, RtClass);
};

enum VaseFlags
{
	PVZ_BEGIN_FLAG_ENUM(VASE_),
	PVZ_FLAG(VASE_ColorByContents),
	PVZ_FLAG(VASE_ContentsRevealed),
	PVZ_FLAG(VASE_Broken),
	PVZ_END_FLAG_ENUM(VASE_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(VaseFlags);

class GridItemVase : public GridItem
{
public:
	RT_CLASS_DEFINE(GridItemVase, GridItem, RtClass);

	GridItemVase();
	virtual ~GridItemVase();

	int CalcRenderOrder() const override;

	void GatherPlantingRestrictions(const PlantType* i_plantType, std::vector<PlantingReason>* io_reasons) const override;

	void SetContentsType(RtWeakPtr<ObjectTypeDescriptor> i_contentsType);
	void SetColorByContents(bool i_colorize);
	void SetContentsRevealed(bool i_revealed);

	bool DoColorByContents() const;
	bool AreContentsRevealed() const;

	bool ContainsGargantuar() const;
	bool ContainsZombie() const;
	bool ContainsPlant() const;
	bool ContainsCollectable() const;

	bool IsBreaking() const;
	void BreakVase();

	void SetSelectedForMove(bool i_selected);
	void SetMovePreviewPosition(const Point& i_gridPos);
	
	void SetAllowPreGameplayInteraction(bool i_allowInteraction);

	void CreateAnimRig();
	class GridItemVaseAnimRig* GetAnimRig();
	void Drop();
    
    bool ShouldClipWithWater() const override;

	bool ShouldDrawShadow() const override;
	
protected:
	void registerForEvents() override;
	void unregisterForEvents() override;
	void onUpdate() override;
	void onDraw(Sexy::Graphics* i_g) override;
	void onDrawShadow(Sexy::Graphics* i_g) override;

    virtual void onDestroy() override;
    
private:
#if defined( HOST_ANDROID )
	void Android_OnAppResumeFocus();
#endif // defined( HOST_ANDROID )

	void drawAnimRig(Sexy::Graphics *i_g, const float i_scale);
	bool onTouchEvent(const Sexy::Touch& i_touch);
	void onTouchCancelEvent();
    
    void updateGroundEffect();

	void spawnContents();
	void playBreakSound();
	void onBreakAnimStopped(const std::string& i_animName);
	Point getRenderGridSquare() const;
	DeviceImage* tryCreatePreviewImage(int i_maxImageWidth, int i_maxImageHeight) const;

	SexyVector2 getPreviewImageOffsetBoardSpace() const;
	Point getPreviewImageSizePixels() const;

	PopAnim* getPAMAsset() const;

	RtWeakPtr<class GridItemVaseAnimRig> m_animRig;
	RtWeakPtr<ObjectTypeDescriptor> m_contentsType;
	VaseFlags m_flags;
	pvztime_t m_dropStartTime;
	pvztime_t m_dropEndTime;
	bool m_allowPreGameplayInteraction;

	// not serialized
	Sexy::TouchID	m_owningTouchIdent;
	bool			m_touchHovering;
	bool			m_selectedForMove;
	pvztime_t		m_selectedForMoveTime;
	Point			m_selectedForMovePreviewPosition;

	DeviceImage*	m_contentsPreviewImage;
    
    EntityComponent_GroundEffect	m_groundEffect;
};

class GridItemVaseAnimRig : public PopAnimRig
{
public:
	RT_CLASS_DEFINE(GridItemVaseAnimRig, PopAnimRig, RtClass);

	GridItemVaseAnimRig();

	void PlayIdle();
	void PlayDrop();

	void SetRevealedAndTransition(bool i_revealed, PopAnimRig::AnimStoppedReflectionDelegate i_onTransitionAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());
	void SetRevealedImmediately(bool i_revealed);

	void Break(PopAnimRig::AnimStoppedReflectionDelegate i_onBreakAnimStopped = PopAnimRig::AnimStoppedReflectionDelegate());

	pvztime_t CalcDropAnimLength();

private:
	void onDropCompleted(const std::string& i_animName);
	bool m_revealed;
};

#endif /* defined(__PlantsVersusZombies2__GridItemVase__) */
