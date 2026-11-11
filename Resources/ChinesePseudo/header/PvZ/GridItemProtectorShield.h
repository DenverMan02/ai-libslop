//

//  GridItemProtectorShield.h

//  PlantsVersusZombies2

//

//  Created by Michael Fromwiller on 7/24/13.

//  Copyright (c) 2013 PopCap Games. All rights reserved.

//



#ifndef __PlantsVersusZombies2__GridItemProtectorShield__

#define __PlantsVersusZombies2__GridItemProtectorShield__



#include <string>

#include <vector>



#include "Core.h"

#include "DamageInfo.h"

#include "GridItem.h"

#include "GridItemPropertySheet.h"

#include "Rect.h"

#include "RtDb.h"

#include "RtObject.h"

#include "TimeMgr.h"



namespace Sexy {

class Graphics;

class Point;

class SexyVector3;

}  // namespace Sexy



enum ShieldState

{

    PVZ_BEGIN_ENUM(STATE_SHIELD_),

	STATE_SHIELD_INACTIVE,

	STATE_SHIELD_ACTIVATING,

	STATE_SHIELD_ACTIVE,

	STATE_SHIELD_DEACTIVATING,

    PVZ_END_ENUM(STATE_SHIELD_)

};


enum ProtectorShieldType

{

	protectorshieldsegment,

	protectorshieldsegment_alpha,

	protectorshieldsegment_wavegenerator,

};


class GridItemProtectorShield;

class GridItemProtectorShieldSegment;

class ZombieFutureProtector;



struct ProtectorShieldSlice

{

	ProtectorShieldSlice(GridItemProtectorShield* i_owningShield);

	ProtectorShieldSlice()

	{}

	

	bool IsBottomPiece;

	bool IsTopPiece;

	float TopY;

	float BottomY;

	

	int RenderOrder;

	RtWeakPtr<GridItemProtectorShield> OwningShield;

	bool m_mirror;
	

	void Draw(Graphics* i_g);

};



class GridItemProtectorShield : public GridItem

{

public:

	

	RT_CLASS_DEFINE(GridItemProtectorShield, GridItem, RtClass);



    GridItemProtectorShield();

	virtual ~GridItemProtectorShield();

	

	void						AddToRenderQueue(class RenderQueue* i_queue) override;

	virtual void				SetPosition(const SexyVector3& i_newPosition) override;



	void						SetShieldSize(const float i_sizeX, const float i_sizeY);

	void						SetShieldHP(const float i_hitpoint);

	void						SetShieldParent(RtWeakPtr<ZombieFutureProtector> i_parent);

	

	float						GetShieldLeft() const;

	float						CalculateShieldExpansionScale();



	void						Activate();

	void						Deactivate();

	void						ShieldGotHit(class GridItemProtectorShieldSegment* i_shieldSegment, const DamageInfo& i_damage);

	pvztime_t					GetTimeSinceHit() const;
    
    bool						NeutralizeSplashDamage() override { return true; }
    void						SetReverseShield(bool i_reverse, const SexyVector3& i_veloctiy);
    void						SetVelocity(const SexyVector3& i_veloctiy) { m_velocity = i_veloctiy; }
	const SexyVector3&			GetVelocity() const { return m_velocity; }
	void						SetRadius(float i_radius) { m_radius = i_radius; }

	std::string					getShieldTypeStr() { return m_shieldTypeStr; }

	void						setShieldTypeStr(std::string i_shieldTypeStr) { m_shieldTypeStr = i_shieldTypeStr; }

	void						setCardGameReverseShield(bool i_flag){ m_cardGameReverseShield = i_flag; }

protected:

	virtual void 				moveThroughTime(pvztime_t i_dt);

	virtual void				onGridItemInitialize() override;

	virtual void				onUpdate() override;

	

private:

	void						buildSlicesForRow(int i_row, bool i_hasTopPiece, bool i_hasBottomPiece, std::vector<ProtectorShieldSlice>& o_slices, bool i_mirror);

	

	void						calculateShieldArea();



	void						createChildren();

	void						deleteChildren();

	void						setChildPositions();

	void						recordChildPrePositions();

	RtWeakPtr<ZombieFutureProtector> m_shieldParentZombie;

	float						m_shieldHP = 1000.0f;

	ShieldState					m_shieldState = STATE_SHIELD_INACTIVE;

	pvztime_t					m_shieldStateStartTime = 0;

	float						m_shieldSizeX = 3.0f;

	float						m_shieldSizeY = 3.0f;

	std::vector<RtWeakPtr<GridItemProtectorShieldSegment> >	m_children;

	Rect						m_shieldArea;

	pvztime_t					m_shieldLastHitTime = PVZ_EOT();

	

	std::vector<ProtectorShieldSlice>	m_shieldSlices;

	bool						m_reverseShield = false;
	std::string					m_shieldTypeStr = "";
	SexyVector3					m_velocity;
	float						m_radius = 0.f;

	bool						m_cardGameReverseShield;
};



class GridItemProtectorShieldProps : public GridItemPropertySheet

{

public:

	RT_CLASS_DEFINE(GridItemProtectorShieldProps, GridItemPropertySheet, RtClass);

	

	std::string			SoundOnActivate;

	std::string			SoundOnDeactivate;

	std::string			SoundOnHit;

};



#endif /* defined(__PlantsVersusZombies2__GridItemProtectorShield__) */

