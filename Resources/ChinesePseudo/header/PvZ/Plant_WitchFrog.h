/*
 * Plant_WitchFrog.h
 *
 *  Created on: 2022-3-11
 *      Author: admin
 */

#ifndef PLANT_WITCHFROG_H_
#define PLANT_WITCHFROG_H_

#include "PlantFramework.h"
#include "StandaloneEffect.h"

class WitchFrogProps : public PlantPropertySheet
{
public:
	RT_CLASS_DEFINE(WitchFrogProps, PlantPropertySheet, RtClass);

	WitchFrogProps()
	: JumpInterval(2.0f)
	{

	}

	float JumpInterval;
};

class PlantWitchFrog : public PlantFramework
{
public:
	RT_CLASS_DEFINE(PlantWitchFrog, PlantFramework, RtClass);

	// Public Interface (Inheritable)

    virtual void				Initialize() override;
	virtual void				UpdateActions() override;

	virtual bool				CanApplyPlantfood() override;

	virtual int					CalcRenderOrder() override;
	bool                        CanBeTargeted() override;
	virtual SexyVector2			GetShadowOffset() override;
	virtual bool				IsInvincible() const override;
	virtual bool				CanBeShoveled() override;

    void registerForEvents() override;
	void unregisterForEvents() override;
    void Idle() override;

    void Appear(PlantPtr i_carriedPlant);

    void SetOriginalPlant(PlantPtr i_plant) { m_originalPlant = i_plant; }
    PlantPtr GetOriginalPlant() { return m_originalPlant; }

    void LostControll();

protected:
    virtual bool CanTargetZombie(ZombiePtr i_zombie, PlantWeapon i_plantWeapon) override;
	virtual void onDestroy() override;

private:

	// Private Interface (Core)
    void onAnimStoppedCallback(const std::string&) override;

	void						onAnimTurnFinished(const std::string& i_animLabel);
	void						onAnimLandingFinished(const std::string& i_animLabel);

	void						pickNextDestination();
	void						travelToJumpUpDestination();
	void						travelToLandingDestination();
	void						playPlantAnimation(const std::string& i_animLabel, PopAnimRig::AnimStoppedReflectionDelegate i_delegate = PopAnimRig::AnimStoppedReflectionDelegate());

    void						setState(uint i_plantState);
    void                    	onPlantPlacedOnBoard(Plant* i_plant);	// Private Members (serialized)
    void 						hideShowOriginal(bool i_hide);
    void						doAppear();
    void 						doJump();
    void						doFinalJump(const Point& i_point);
    bool						checkJumpEdge();
    void 						tryJump();
    bool						checkQueuedState();
    bool						queuedState(uint i_waitedState);
    void						tryRecover();
    void						tryDisappear();
    void						doDisappear(bool i_killCarried);
    Point						findRecoverGrid();
    void						tryTransformBack();
    bool 						HasGirdItem(const Sexy::Point& i_targetSquare);

	SexyVector3					m_startPos;
	SexyVector3					m_endPos;
	PlantPtr					m_originalPlant;
	uint						m_queuedState;
	pvztime_t					m_nextJumpTime;
};


#endif /* PLANT_WITCHFROG_H_ */
