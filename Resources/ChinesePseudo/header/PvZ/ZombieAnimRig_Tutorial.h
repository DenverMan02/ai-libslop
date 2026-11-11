//
//  ZombieAnimRig_Tutorial.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 4/27/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ZombieAnimRig_Tutorial_h
#define PlantsVersusZombies2_ZombieAnimRig_Tutorial_h

#include "Precompile.h"
#include "ZombieAnimRig_Basic.h"

class ZombieAnimRig_Tutorial : public ZombieAnimRig_Basic
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_Tutorial, ZombieAnimRig_Basic, RtClass);

protected:
	virtual const std::vector<std::string>& getHeadLayerNames() override;
	virtual const std::vector<std::string>& getArmLayerNames() override;
	virtual const std::vector<std::string>& getArmReplacementPairNames() override;
	virtual const std::vector<std::string>& getFlagHandLayerNames() override;
	virtual const std::vector<std::string>& getNoFlagHandLayerNames() override;
	virtual const std::vector<std::string>& getConeLayerNames() override;
	virtual const std::vector<std::string>& getBucketLayerNames() override;
};

class ZombieAnimRig_TutorialBirthday : public ZombieAnimRig_Tutorial
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_TutorialBirthday, ZombieAnimRig_Tutorial, RtClass);
    
protected:
    const std::string getDieAnimationName() override;
    
    const std::vector<std::string>& getHeadLayerNames() override;
};

class ZombieAnimRig_TutorialSpring : public ZombieAnimRig_Tutorial
{
public:
    ZombieAnimRig_TutorialSpring()
    {
        m_everHadHelm = false;
    }
    
    RT_CLASS_DEFINE(ZombieAnimRig_TutorialSpring, ZombieAnimRig_Tutorial, RtClass);
    
    void SetHasHelm(HelmType i_helmType) override;
    class ZombieParticle* DropHead(class Zombie* i_zombie) override;
protected:
    const std::vector<std::string>& getHeadLayerNames() override;
    void updateHelmLayerVisibility(HelmType i_helmType) override;
    
    bool m_everHadHelm;
};

// summer
class ZombieAnimRig_TutorialSummer : public ZombieAnimRig_Tutorial
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_TutorialSummer, ZombieAnimRig_Tutorial, RtClass);

protected:
    const std::vector<std::string>& getFlagHandLayerNames() override;
    const std::vector<std::string>& getNoFlagHandLayerNames() override;
};

class ZombieAnimRig_TutorialSummerFlag : public ZombieAnimRig_Tutorial
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_TutorialSummerFlag, ZombieAnimRig_Tutorial, RtClass);

protected:
    const std::vector<std::string>& getFlagHandLayerNames() override;
    const std::vector<std::string>& getNoFlagHandLayerNames() override;
};

// childrensday
class ZombieAnimRig_ChildrensdayBasic : public ZombieAnimRig_Tutorial
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_ChildrensdayBasic, ZombieAnimRig_Tutorial, RtClass);

protected:
    void updateHelmLayerVisibility(HelmType i_helmType) override;
    const std::vector<std::string>& getFlagHandLayerNames() override;
    const std::vector<std::string>& getNoFlagHandLayerNames() override;
};

class ZombieAnimRig_ChildrensdayFlag : public ZombieAnimRig_Tutorial
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_ChildrensdayFlag, ZombieAnimRig_Tutorial, RtClass);

protected:
};

class ZombieAnimRig_ChildrensdayBucket : public ZombieAnimRig_ChildrensdayBasic
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_ChildrensdayBucket, ZombieAnimRig_ChildrensdayBasic, RtClass);

protected:
	const std::vector<std::string>& getBucketLayerNames() override;
};

class ZombieAnimRig_ChildrensdayCone : public ZombieAnimRig_ChildrensdayBasic
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_ChildrensdayCone, ZombieAnimRig_ChildrensdayBasic, RtClass);

protected:
	const std::vector<std::string>& getConeLayerNames() override;
};


// normal parkour zombies
class ZombieAnimRig_ParkourBasic : public ZombieAnimRig_Tutorial
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_ParkourBasic, ZombieAnimRig_Tutorial, RtClass);    
protected:
    void updateHelmLayerVisibility(HelmType i_helmType) override;    
    virtual void hidePaint();
};

class ZombieAnimRig_ParkourBucket : public ZombieAnimRig_ParkourBasic
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_ParkourBucket, ZombieAnimRig_ParkourBasic, RtClass);

protected:
	const std::vector<std::string>& getBucketLayerNames() override;    
};

class ZombieAnimRig_ParkourCone : public ZombieAnimRig_ParkourBasic
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_ParkourCone, ZombieAnimRig_ParkourBasic, RtClass);

protected:
	const std::vector<std::string>& getConeLayerNames() override;
    void hidePaint() override { };
};

#endif
