



#ifndef __PlantsVersusZombies2__ZombieAnimRig_Neuropathy__
#define __PlantsVersusZombies2__ZombieAnimRig_Neuropathy__

#include "Precompile.h"
#include "ZombieAnimRig.h"
#include "PopAnimRigHelper.h"

#include "ZombieAnimRig_Basic.h"
class ZombieAnimRig_Neuropathy : public ZombieAnimRig_Basic
{
public:
	RT_CLASS_DEFINE(ZombieAnimRig_Neuropathy, ZombieAnimRig_Basic, RtClass);
    
	// void SetTorchLayers(const bool i_visible);
	void onPopAnimInitialized() override;

    bool PlayBigBang(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayBigBangloop(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    bool PlayBoxDiscard(PopAnimRig::AnimStoppedReflectionDelegate i_onAnimStopped);
    
	class ZombieParticle* DropHelm(HelmType i_helmType, class Zombie* i_zombie) override;
	const std::string getIdleAnimationName() override;
	const std::string getWalkAnimationName() override;
	const std::string getEatAnimationName() override;
	const std::string getDieAnimationName() override;
	AnimHandle PlayDie() override;
	class ZombieParticle* DropHead(class Zombie* i_zombie) override;



	const std::vector<std::string>& getBoxLayerNames() override;
	virtual const std::vector<std::string>& getHeadLayerNames() override;

private:
 	bool m_Havebox;
 	bool m_boxOpen;
	// virtual const std::vector<std::string>& getHeadLayerNames() override;
	// virtual const std::vector<std::string>& getArmLayerNames() override;
	// virtual const std::vector<std::string>& getArmReplacementPairNames() override;
    // virtual const std::string GetArmParticleName() override;
    
};

#endif /* defined(__PlantsVersusZombies2__ZombieAnimRig_SelfExplorer__) */
