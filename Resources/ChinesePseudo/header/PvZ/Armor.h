//
//  Armor.hpp
//  PlantsVersusZombies2
//
//  Created by Kobylarek, Alexander on 12/19/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef Armor_hpp
#define Armor_hpp

#include "RtDb.h"
#include "RtObject.h"

#include "ArmorPropertySheet.hpp"
#include "DamageInfo.h"

typedef RtWeakPtr<class Armor> ArmorPtr;

class Zombie;

class Armor : public GameObject
{
public:
	RT_CLASS_DEFINE(Armor, GameObject, RtClass);
	Armor();
	
public:
	virtual ~Armor();
	
	void InitializeArmor(ArmorPropertySheetPtr i_propertySheet, RtWeakPtr<Zombie> i_owner);
	void onPostLoad() override;
	void ReinitializeFromPropertySheet();
	void SetPropertySheet(ArmorPropertySheetPtr i_propertySheetPtr);
	
	virtual DamageInfo TakeDamage(const DamageInfo& i_damageInfo);
	virtual class ZombieParticle* DropArmor(DamageTypeFlags i_damageFlags);
	
	void DestroyArmor();
	
	float			GetHealth() const { return m_health; }
	float			GetMaxHealth() const { return m_maxHealth; }
	std::string		GetArmorType() const { return getProps()->ArmorType; };
	
	ArmorTypeFlags GetArmorFlags() const { return m_armorFlagsOverride == ARMOR_None ? getProps()->ArmorFlags : m_armorFlagsOverride; }

	bool IsDecorativePassthrough() { return TestFlag(getProps()->ArmorFlags, ARMOR_PASSDAMAGE); }

	bool IsDestroyed() { return m_destroyed; }
	
protected:
	virtual void updateDamageState();
	virtual void onTakeDamage(const DamageInfo& i_damageInfo) { };
	virtual void onArmorDropped(std::string i_armorType) { };
	
	inline const ArmorPropertySheet* getProps() const
	{
		// Return cached bare ptr, set it from RtPtr if NULL
		if (!m_cachedPropertySheet)
		{
			m_cachedPropertySheet = m_propertySheetPtr.Get();
		}
		return m_cachedPropertySheet;
	}
	
private:
	mutable ArmorPropertySheet*		m_cachedPropertySheet; 	// Transient
	RtWeakPtr<ArmorPropertySheet> 	m_propertySheetPtr;		// Serialized
	
protected:
	RtWeakPtr<Zombie>				m_ownerZombiePtr;

private:
	float m_health;
	float m_maxHealth;
	int m_damageState;
	bool m_destroyed;
	
	// Armor type override
	ArmorTypeFlags m_armorFlagsOverride;
	
};

namespace Message
{
	void NewspaperBurned();
}

class NewspaperArmor : public Armor
{
public:
	RT_CLASS_DEFINE(NewspaperArmor, Armor, RtClass);
	NewspaperArmor();
	
protected:
	void onTakeDamage(const DamageInfo& i_damageInfo) override;
	void updateDamageState() override;
	
	bool m_onFire;
};

class CoalCartDefault : public Armor
{
public:
	RT_CLASS_DEFINE(CoalCartDefault, Armor, RtClass);
	CoalCartDefault();

	bool IsBurnt();

protected:
	void onTakeDamage(const DamageInfo& i_damageInfo) override;

	float m_FireDamage;
};
#endif /* Armor_hpp */
