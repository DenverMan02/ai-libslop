//
//  ZombieParticle.h
//  PlantsVersusZombies2
//
//  Created by Austin McGee on 5/23/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ZombieParticle__
#define __PlantsVersusZombies2__ZombieParticle__

#include <string>
#include <vector>

#include "BoardEntity.h"
#include "PopAnimRig.h"
#include "Rect.h"
#include "RtObject.h"
#include "SexyVector.h"
#include "TimeMgr.h"

class Zombie;
class ZombieAnimRig;

namespace Sexy {
	class Graphics;
	class PASpriteInst;
}  // namespace Sexy

enum ZombieParticleMotionType
{
	PVZ_BEGIN_ENUM(ZOMBIEPARTICLEMOTION_),
		ZOMBIEPARTICLEMOTION_EXTERNALLYCONTROLLED,
		ZOMBIEPARTICLEMOTION_BOUNCE,
	PVZ_END_ENUM(ZOMBIEPARTICLEMOTION_)
};

enum ZombieParticleAttribute
{
	PVZ_BEGIN_FLAG_ENUM(ZOMBIEPARTICLEATTRIBUTE_),
		PVZ_FLAG(ZOMBIEPARTICLEATTRIBUTE_BodyPart),
		PVZ_FLAG(ZOMBIEPARTICLEATTRIBUTE_Helm),
		PVZ_FLAG(ZOMBIEPARTICLEATTRIBUTE_Metal),
	PVZ_END_FLAG_ENUM(ZOMBIEPARTICLEATTRIBUTE_)
};
PVZ_MAKE_ENUM_BIT_OPERATORS(ZombieParticleAttribute);


class ZombieParticle : public BoardEntity
{
public:
	RT_CLASS_DEFINE(ZombieParticle, BoardEntity, RtClass);

	virtual ~ZombieParticle();

	void InitializeAnimation(ZombieAnimRig* i_originalZombieAnimRig, ZombieAnimRig* i_newAnimRig, const std::vector<std::string>& i_sprites, const std::string& i_particleReplacement, const float i_shadowScale=0.75f);
	void InitializeAnimation(Zombie* i_zombie, const std::vector<std::string>& i_sprites, const std::string& i_particleReplacement, const float i_shadowScale=0.75f);
	
	void SetMotionType(ZombieParticleMotionType i_motionType);
	void SetBounceMotionRandomlyFromZombie(Zombie* i_zombie);
	void SetBounceMotionWithVelocity(SexyVector3 i_velocity);

	void SetScale(float i_newScale);
	void SetRotation(float i_newRotation);
	
    int CalcRenderOrder() const override;
	
	void SetAttribute(ZombieParticleAttribute i_attribute, bool i_set);
	bool HasAttribute(ZombieParticleAttribute i_attribute) const;
	
	void CancelFadeOutAndDestroy();
	bool SetLayerVisibility(const std::string& i_layerName, bool i_visible);
	
protected:
	void onInitialized() override;
	void onPostLoad() override;
	void onUpdate() override;
	void onDraw(class Graphics* i_g) override;
	void onDrawShadow(class Sexy::Graphics* i_g) override;
	
	float getFadeOutAlpha() const;
	
	void startFadeOutAndDestroy();

private:
	void onBeganBounceMotion();
	void updateBounceMotion();
	void onHitGround();
	float calcBounceGroundLine() const;
    
    void InSkyUpdate();
    
    bool IsInSky() const;
    
    bool IsDropingInSky() const;
	
	// Serialized
	
	PopAnimRigPtr m_zombieRig;

	float m_rotation;
	float m_currentRotation;
	float m_scale;
	float m_shadowScale;
	pvztime_t m_motionBeginTime;
	
	pvztime_t m_fadeOutBeginTime;

	bool m_settled;

	Sexy::Rect m_newParticleRect;
	Sexy::SexyVector3 m_velocity;
	Sexy::SexyVector3 m_acceleration;
	Sexy::Rect m_spriteRectInZombie;
	
	std::string m_particleName;
	
	ZombieParticleMotionType m_motionType;
	ZombieParticleAttribute m_attributes;
	
	// Transient

	PASpriteInst* m_particleSprite;
};

#endif /* defined(__PlantsVersusZombies2__ZombieParticle__) */
