//
//  Plant_Pumpkin.hpp
//  PlantsVersusZombies2
//
//

#ifndef __Plant_Pumpkin_h__
#define __Plant_Pumpkin_h__

#include "Shield.h"
#include "PlantAnimRig_Shielded.h"
#include "RtObject.h"
#include "PlantTypeVine.h"

class PumpkinProps : public PlantPropertySheet
{
public:
    RT_CLASS_DEFINE(PumpkinProps, PlantPropertySheet, RtClass);
    float CheckDuration;
    float Level2Cure;
    float Level3Cure;
    float DeathBoomDamage;
    float Level2Scale;
    float Level3Scale;
};


class PlantPumpkin : public PlantVineFramework
{
public:
    RT_CLASS_DEFINE(PlantPumpkin, PlantVineFramework, RtClass);
    
    void    Initialize() override;
    bool    CanApplyPlantfood() override;
    void    ApplyPlantfood() override;
    void    CancelPlantfood() override;
    DamageInfo    TakeDamage(const DamageInfo& i_damage) override;
    void TakeSmashAttack(ZombiePtr i_srcZombie) override;
    bool TryBlockZombossRush(Zombie* i_zombie) override;
    bool    HasPlantfoodShield() override;
    // void    GetPlantfoodShieldHealth(int& o_health, int& o_maxHealth);
    void Draw(Graphics* i_g) override;
    void UpdateActions() override;
    bool HasShadow() override { return true; }
    void    PlayChewedOnSound() override;
    void onHealed() override;    
    bool AbsorbsSmashAttack() override;
    bool CanBeTargeted() override { if (m_selfIsDeath) { return false; } else { return true; } }
    void onAnimStoppedCallback(const std::string& i_animCommand) override;
    bool OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    // bool HandleDamageStateChanged();
protected:
    RtWeakPtr<Shield> m_shield;
    RtWeakPtr<Shield> m_geneShield;

private:

    Rect deathSkillRect();
    void deathBoom();
    DamageInfo handleAnimation(DamageInfo i_damage);
    void cureMainPlant();

    float m_halfOfHeal;    
    bool m_selfIsDeath = false;    
    bool m_firstPlantFood = false;
    bool m_bigger = false;
    float m_startTime = 0.0;
    bool m_isDefenced = false;
};

///// AnimRig

class PlantAnimRig_Pumpkin : public PlantAnimRig_Shielded
{
public:
    RT_CLASS_DEFINE(PlantAnimRig_Pumpkin, PlantAnimRig_Shielded, RtClass);
	
	int CalcDamageStateCount() override;
    
    pvztime_t CalcPlantFoodDuration(int i_mainAnimPlayCount = 0) override;
	bool PlayIdleLooped() override;
    bool PlayPlantFoodEnd() override;
    
    int GetArmorStateCount() override;
    void SetArmorStateIndex(int i_index) override;

    void SetShield(bool i_show) { m_hasShield = i_show; }
    void SetGeneShield(bool i_show) { m_hasGeneShield = i_show; }

    bool PlayDeathAnim(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
    bool PlayLevel2Skill(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
    bool PlayLevel3Skill(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped = {});
    void SetFirstPlantfood() { m_firstPlantFood = true; }
    
protected:
    const std::vector<std::string>& getArmorStateLayerNames() const;
    
private:
    void onPopAnimInitialized() override;
    std::string getIdleAnimationName() override { return "idle1"; };
    std::string getPlantFoodMainAnimName() override;


	int m_currentArmorShieldIndex;
	bool m_hasShield = false;
    bool m_hasGeneShield = false;
    bool m_firstPlantFood = false;
};




#endif /* Plant_Pumpkin_h */
