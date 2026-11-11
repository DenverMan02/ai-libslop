/*
 * LightningBoltToGroundToGround.h
 *
 *  Created on: 2022-12-7
 *      Author: admin
 */

#ifndef LIGHTNINGBOLTTOGROUND_H_
#define LIGHTNINGBOLTTOGROUND_H_

#include "BoardEntity.h"
#include "PopAnimRig.h"

class LightningBoltToGround : public BoardEntity
{
public:
	RT_CLASS_DEFINE(LightningBoltToGround, BoardEntity, RtClass);

	LightningBoltToGround();

    void SetPopAnimNames(const std::string& i_popAnimName, const std::string& i_bouncePopAnimName, const std::string& i_hitPopAnimName)
	{
		m_popAnimName = i_popAnimName; //
		m_bouncePopAnimName = i_bouncePopAnimName; //
		m_hitPopAnimName = i_hitPopAnimName; //
	}

	void SetOwner(const BoardEntityPtr i_owner) { m_owner = i_owner; }
	void SetInitialTarget(Sexy::SexyVector3 i_target);
	void SetBounceCount(const int i_count) { m_bounceCount = i_count; }
	void SetHitTargets(const std::vector<SexyVector3> i_hitTargets) { m_hitTargets = i_hitTargets; }
    void SetStarAttack(bool i_starAttack) { m_starAttack = i_starAttack; }
    void SetCitronAttack(bool i_citronAttack) { m_citronAttack = i_citronAttack; }
    void SetMaxBounces(const int i_maxBounces) { m_maxBounces = i_maxBounces; }
	void SetBounceDelay(const pvztime_t i_bounceDelay, const pvztime_t i_decayDelay) { m_bounceDelay = i_bounceDelay; m_decayDelay = i_decayDelay; }

	virtual int CalcRenderOrder() const override;

    bool ShouldDrawShadow() const override { return false; }

    void SetPopAnim(const std::string &i_BoltDefaultPopAnim,
                    const std::string &i_BoltPopAnim,
                    const std::string &i_HitPopAnim);

    void SetManual(bool i_manual) { m_manual = i_manual; }
    void ClearChild();


protected:
	virtual void onInitialized() override;
	virtual void onDestroy() override;
	virtual void onUpdate() override;
	virtual void onDraw(Graphics* i_g) override;

//	virtual void createBounce();

protected:
	void setRenderTransformForRig(PopAnimRig* i_rig, const float i_xOffset);

	int m_bounceCount;
    bool m_starAttack;
    bool m_citronAttack;

	BoardEntityPtr m_owner;
	SexyVector3 m_endPos;
	std::vector<SexyVector3> m_hitTargets;

	pvztime_t m_bounceTime;
	pvztime_t m_destroyTime;

	std::vector<PopAnimRigPtr> m_tiledRigs;

    std::string m_popAnimName;
	std::string m_bouncePopAnimName;
	std::string m_hitPopAnimName;
    int m_maxBounces;
    pvztime_t m_bounceDelay;
    pvztime_t m_decayDelay;
    bool m_manual;
};


#endif /* LIGHTNINGBOLTTOGROUND_H_ */
