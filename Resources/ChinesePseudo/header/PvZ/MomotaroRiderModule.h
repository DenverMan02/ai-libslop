/*
 * MomotaroRiderModule.h
 *
 *  Created on: 2021-3-23
 *      Author: admin
 */

#ifndef MOMOTARORIDERMODULE_H_
#define MOMOTARORIDERMODULE_H_

#include "RiverCrossingModule.h"

class MomotaroRiderModule : public RiverCrossingModule
{
public:

    RT_CLASS_DEFINE(MomotaroRiderModule, RiverCrossingModule, RtClass);

    MomotaroRiderModule();
    virtual ~MomotaroRiderModule();

    void AddResourceRequirements(std::set<std::string>& io_resGroupNames) override;

protected:
    RiverCrossingDodoRider* CreateRider() override;
    std::string GetRiderPam() override;
    bool isInRiver(Point point) override;

    void        RequireNextChomerGroup() override;
    void		InitChomerGroup() override;
    bool		IsRiderKilled() override;
    void 		registerForEvents() override;
    void        onDodoRiderDying() override;
    void		InitDodoRider(bool i_extern, RtWeakPtr<PopAnim> i_animPtr) override;
    std::string GetReviveTip() override;
    ImagePtr 	GetRiderUIImage() override;
    ImagePtr	GetRemainUIImage() override;

private:
    void 		onTryKillRider();

    bool m_riderHitByNinja = false;
};

struct NinjaProperties
{
	NinjaProperties()
    {
        GridX = -1;
        GridY = -1;
        Wave = -1;
    }

    int				GridX;
    int				GridY;
    int             Wave;
};

class MomotaroRiderModuleProperties : public RiverCrossingProperties
{
public:
    RT_CLASS_DEFINE(MomotaroRiderModuleProperties, RiverCrossingProperties, RtClass);

    virtual RtClass* GetModuleClass() const override
    {
        return MomotaroRiderModule::StaticGetClass();
    }

    MomotaroRiderModuleProperties()
    {

    }

    std::vector<NinjaProperties>  NinjaPlacements;
};


#endif /* MOMOTARORIDERMODULE_H_ */
