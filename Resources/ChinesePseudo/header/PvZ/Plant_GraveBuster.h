#pragma once


#include "PlantFramework.h"

enum GraveBusterState
{
	PVZ_BEGIN_ENUM(BUSTERSTATE_),
	BUSTERSTATE_LANDING,
	BUSTERSTATE_EATING,
	BUSTERSTATE_FADINGOUT,
	PVZ_END_ENUM(BUSTERSTATE_),
};

class PlantGraveBuster : public PlantFramework 
{
public:
	RT_CLASS_DEFINE(PlantGraveBuster, PlantFramework, RtClass);

	PlantGraveBuster();

	virtual void Initialize() override;
	virtual void UpdateActions() override;
	virtual void Draw(Graphics* i_g) override;
	virtual bool CanBeShoveled() override;
	virtual float GetAdditionalDrawHeightOffset() override;
	virtual void onKilled(bool i_instantKill) override;
	virtual bool IsInvincible() const override;
	virtual bool HasShadow() override
	{ 
		return false; 
	}

	bool IsEating() const
	{
		return m_busterState == BUSTERSTATE_EATING;
	}
	float GetEatingProgress() const;
	int	  CalcRenderOrder();
private:
	void SetState(GraveBusterState newState);
	void OnStateChanged(GraveBusterState oldState);
	void UpdateState();
	
	GraveBusterState m_busterState;
	pvztime_t m_busterEatEndTime;
	pvztime_t m_busterFadeEndTime;
	RtWeakPtr<GridItemGravestone> m_targetGraveStone;
};

class PlantTypeGraveBuster : public PlantType
{
public:
	RT_CLASS_DEFINE(PlantTypeGraveBuster, PlantType, RtClass) {}
	
	// Gravebuster can ONLY be planted on gravestones
	void GatherPlantingRestrictions(Board* i_board, const Sexy::Point& i_gridPosition, std::vector<PlantingReason>* io_plantingReasons) const override;
	virtual int GetCost(PlantAvatarType i_avatarType) const override;
};
