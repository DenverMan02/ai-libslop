
#ifndef ZombieDinoEggShell_h
#define ZombieDinoEggShell_h

#include "ZombieBasic.h"
#include "ZombieAnimRig_Basic.h"
#include "ZombieAnimRig.h"

class ZombieDinoEggShell : public ZombieBasic
{
public:
    RT_CLASS_DEFINE(ZombieDinoEggShell, ZombieBasic, RtClass);
    
    ZombieDinoEggShell();
    ~ZombieDinoEggShell();

    bool willDieToShrinking() override { return true; }
};

class ZombieAnimRig_EggShell : public ZombieAnimRig_Basic
{
public:
    RT_CLASS_DEFINE(ZombieAnimRig_EggShell, ZombieAnimRig_Basic, RtClass);
    ZombieAnimRig_EggShell() { }
    
    void SetLayerVisibilityForCurrentState() override;
protected:
    const std::vector<std::string>& getHeadLayerNames() override;
    const std::vector<std::string>& getArmLayerNames() override;
    const std::vector<std::string>& getArmReplacementPairNames() override;
    const std::vector<std::string>& getHelmetLayerNames() override;
};

#endif
