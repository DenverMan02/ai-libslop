//
//  ZombieCamel.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/10/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __ZOMBIECAMEL_H__
#define __ZOMBIECAMEL_H__

#include "Zombie.h"

enum ZombieCamelSegmentType
{
	CAMELTYPE_INVALID,
	CAMELTYPE_HEAD,
	CAMELTYPE_BODY,
	CAMELTYPE_TAIL,
};

STATE_ENUM_CHILD_BEGIN(ZombieCamelState, ZombieState)
	ZS_C_CamelIdle,
	ZS_C_Surprised,
STATE_ENUM_END(ZombieCamelState)

class ZombieCamel : public Zombie 
{
public:
	RT_CLASS_DEFINE(ZombieCamel, Zombie, RtClass);
	
	bool GetIsACamel() const
	{
		return m_isACamel;
	}
	inline void SetSpawnsDeathAnim(bool i_spawnsAnim)
	{
		m_spawnDeathAnim = i_spawnsAnim;
	}
	virtual void BecomeHeadZombie(ZombieTypePtr i_camelType);

	virtual int CalcHelmDamageIndex() const override;

	virtual RtWeakPtr<PopAnim> GetHeadParticlePopAnim() override;
	
	inline ZombieCamelSegmentType GetCamelType()  const
	{
		return m_camelType;
	}
    
    virtual void onChangeTeams(TeamFlags i_oldTeams, TeamFlags i_newTeams) override;

	void onArmorDropped(std::string i_armorType) override;
	
protected:
	virtual void onZombieInitialize() override;
	virtual void onPlaceOnBoard() override;
	virtual void onPlaceOnStreet() override;
	virtual void addCamelArmor(ZombieCamelSegmentType i_camelType);
	
	virtual std::string getSegmentTypeName(ZombieCamelSegmentType i_type);
	class ZombieCamelSubSystem* getCamelManager();
	virtual ZombieTypePtr getSegmentType(ZombieCamelSegmentType i_type);

	virtual std::string getNormalZombiePAM();
    virtual std::string getHeadParticlePAMBase();

	OVERRIDE_STATE_ONENTER(ZombieState, Walk);
	OVERRIDE_STATE_UPDATE(ZombieState, Walk);
	
	DECLARE_STATE_FUNCTIONS(ZombieState, CamelIdle);
	DECLARE_STATE_FUNCTIONS(ZombieState, Surprised);
	
	//virtual void onTakeHelmDamage(const DamageInfo& i_damageReceived) override;
    //ZombieParticle* onHelmDropped(HelmType i_helmType, int i_helmHitpoints) override;

	virtual void onApplyCondition(ZombieConditions i_condition) override;
	
	BoardEntity* findTarget() override;

	void initializeCamel(ZombieCamelSegmentType i_camelType, RtWeakPtr<Zombie> i_headZombie);
	void spawnInitialSegments(int i_numPieces, bool i_onTheStreet);

	float getArmDropFraction() const override;
	bool isTooFarFromNext() { return m_tooFarFromNext; }
	virtual bool shouldPlayArmorDrop(std::string i_armorType) { return true; }
    virtual bool canBecomeUncamel() { return true; }
	virtual void onCamelStateChange();
	
private:
	
	bool isHeadZombie();
	void setCamelSegmentType(ZombieCamelSegmentType i_camelType);
	float takePropagatedSignDamage(float i_damageAmount, DamageTypeFlags i_damageFlags);
	void switchToNormalZombiePAM();
	void updateWalkingBasedOnNeighborDistance();
	
	ZombieCamelSegmentType m_camelType;

	bool m_isACamel;
	bool m_tooCloseToPrev;
	bool m_tooFarFromNext;
	
	int m_signDamageIndex;
	bool m_spawnDeathAnim;
};

#endif
