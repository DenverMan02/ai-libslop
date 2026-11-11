//
//  ZombieAnimRig_Basic.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/30/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_Basic_h
#define PlantsVersusZombies2_ZombieAnimRig_Basic_h

#include "Precompile.h"
#include "ZombieAnimRig.h"
#include "ZombieEnums.h"
#include "ArmorPropertySheet.hpp"

class ZombieAnimRig_Basic : public ZombieAnimRig
{
public:
	RT_CLASS_DEFINE_ABSTRACT(ZombieAnimRig_Basic, ZombieAnimRig, RtClass);

	ZombieAnimRig_Basic();
    
    void SetHasTanHao(bool i_hasTanHao);
	void SetHasFlag(bool i_hasFlag);
	bool HasFlag();
    
    virtual void SetHasHelm(HelmType i_helmType);
    virtual void SetHelmDamageIndex(int i_newIndex);
    virtual int GetHelmDamageIndex() const;
	virtual const std::string GetHelmSymbolName(HelmType i_helmType);
    
    void FlashHelm();
	virtual void SetLayerVisibilityForCurrentState();
    virtual class ZombieParticle* DropHelm(HelmType i_helmType, class Zombie* i_zombie);
    HelmType GetHelm();
	virtual void SetAlmanacArmor(std::vector<RtWeakPtr<class ArmorPropertySheet>> armorProps);;
protected:
	virtual void onPopAnimInitialized() override;
    void onPostDraw(Graphics* i_g) override;
    
    static const std::vector<std::string>& getEmptyLayerNames()
	{
		STATIC_VECTOR_INIT(std::string, k_layerArray);
		return k_layerArray;
	}
	
	virtual const std::vector<std::string>& getFlagHandLayerNames()
	{
		return getEmptyLayerNames();
	}
	virtual const std::vector<std::string>& getNoFlagHandLayerNames()
	{
		return getEmptyLayerNames();
	}
	virtual const std::vector<std::string>& getConeLayerNames()
	{
		return getEmptyLayerNames();
	}
	virtual const std::vector<std::string>& getBucketLayerNames()
	{
		return getEmptyLayerNames();
	}
    virtual const std::vector<std::string>& getCrownLayerNames()
    {
        return getHelmetLayerNames();
    }
    virtual const std::vector<std::string>& getHelmetLayerNames()
    {
        return getEmptyLayerNames();
    }
    virtual const std::vector<std::string>& getIceBlockLayerNames()
    {
        return getEmptyLayerNames();
    }
    virtual const std::vector<std::string>& getShovelLayerNames()
    {
        return getEmptyLayerNames();
    }
    virtual const std::vector<std::string>& getMiningToolLayerNames()
	{
		return getEmptyLayerNames();
	}
    virtual const std::vector<std::string>& getGlidingLayerNames()
    {
        return getEmptyLayerNames();
    }
    virtual const std::vector<std::string>& getBrickLayerNames()
	{
    	return getEmptyLayerNames();
	}
    virtual const std::vector<std::string>& getBoxLayerNames()
	{
		return getEmptyLayerNames();
	}
    virtual const std::vector<std::string>& getHelmLayerNames(HelmType i_helmType);
    virtual void updateHelmLayerVisibility(HelmType i_helmType);
    virtual bool hasHelm(HelmType i_helmType);
    
	bool m_hasFlag;
    HelmType m_helmType;
    int32 m_helmDamageIndex;
    pvztime_t m_helmFlashStart;
};

#endif
