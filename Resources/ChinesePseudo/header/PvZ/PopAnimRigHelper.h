//
//  PopAnimRigHelper.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 10/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_PopAnimRigHelper_h
#define PlantsVersusZombies2_PopAnimRigHelper_h

#include "Rect.h"
#include "Graphics.h"
#include "PopAnim.h"
#include "PopAnimRig.h"
#include "PVZTypes.h"

class PlantAnimRig;
class ZombieAnimRig;

// this function takes a rect and draws either the full anim rig into it or just the given sprite of the anim rig
// if the scale is different, it fits, but does not stretch
// it will also center the drawing into the rect
void DrawPopAnimRigInRect(Graphics* i_g, const Sexy::Rect &i_drawRect, PopAnimRig* i_animRig, const SexyTransform2D &i_transform, const std::string &i_spriteName="");
void DrawPopAnimRigInRect(Graphics* i_g, const Sexy::Rect &i_drawRect, PopAnimRig* i_animRig, const SexyTransform2D &i_transform, const std::vector<std::string> &i_spriteNames);
void DrawSpriteInRect(Graphics* i_g, const Sexy::Rect &i_drawRect, PopAnimRig* i_animRig, const SexyTransform2D& i_transform, PASpriteInst* i_spriteInst, const Sexy::Rect &i_spriteRect);

PlantAnimRig* CreateStandalonePlantAnimRig(PlantTypePtr i_plantType, const bool i_loadResources=false);
ZombieAnimRig* CreateStandaloneZombieAnimRig(ZombieTypePtr i_zombieType, const bool i_loadResources=false);

// Calculates the amount of motion in the ground track for the given popanim instance.
// If this calculation has already been done on a PAM with the same filename, it will use a cached value.
// Note that this is an old and crufty function, it is not const because it simulates an animation
// step on the passed-in PopAnim(!), and then attempts to put it back to the state it was in before.
// Please be careful before using it!
float CalcWalkPixelsPerSecondForAnimLabel(PopAnimRig* i_containingRig, const std::string& i_groundTrack, const std::string& i_animLabel);

class PopAnimRigRectDrawer
{
public:
	PopAnimRigRectDrawer(PopAnimRig* i_animRig);
	virtual ~PopAnimRigRectDrawer();

	void Draw(Graphics* i_g, const Sexy::Rect &i_drawRect, const SexyTransform2D &i_transform);
	void Update(pvztime_t i_t, pvztime_t i_dt);
	virtual void PlayAndStop(const std::string& i_animLabel, PopAnimRig::AnimStoppedDelegate i_onAnimStopped);

	Rect m_frameRect;
	PopAnimRig* m_animRig;
};

class ZombieParticle* SpawnZombieParticle(class Zombie* i_zombie, const std::vector<std::string>& i_sprites, const std::string& i_particleReplacement, const float i_shadowScale=0.75f);
class ZombieParticle* SpawnZombieParticle(class Zombie* i_zombie, const std::string& i_sprite, const std::string& i_particleReplacement, const float i_shadowScale=0.75f);
class ZombieParticle* SpawnZombieHead(ZombieAnimRig* i_originalZombieAnimRig, const std::vector<std::string>& i_sprites, const std::string& i_particleReplacement, const float i_shadowScale=0.75f);
class ZombieParticle* SpawnZombieProjectileParticle(class ZombieAnimRig* i_zombieAnimRig, const std::vector<std::string>& i_sprites, const std::string& i_particleReplacement, const float i_shadowScale=0.75f);

#endif
