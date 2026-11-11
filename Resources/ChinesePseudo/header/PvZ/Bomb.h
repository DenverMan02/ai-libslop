//
//  Bomb.h
//  PlantsVersusZombies2
//
//  Created by hanj on 12/04/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

//PVZ2_CHINESE_BEGIN

#ifndef PlantsVersusZombies2_Bomb_h
#define PlantsVersusZombies2_Bomb_h

#include "BoardEntity.h"
#include "StateMachine.h"

STATE_ENUM_BASE_BEGIN(BombState)
	BombState_INIT,
	BombState_SPAWN,
	BombState_READY,
	BombState_CLOSETOEXPLOSION,
	BombState_EXPLODE,
STATE_ENUM_END(BombState);

//forward declaration
class Fuse;
class BombProperties;

class Bomb : public BoardEntity
{
public:
	RT_CLASS_DEFINE(Bomb, BoardEntity, RtClass);

	void					BombInitialize(const BombProperties& i_bombProps, int i_row);

    int						GetRow() const { return m_row; }

	/// BoardEntity interface
	virtual int 			CalcRenderOrder() const override;
	/// BoardEntity interface end

	bool       			 	isInState(BombState i_state) const;
	void        			setState(BombState i_newState);

protected:
	/// GameObject interface
	virtual void			onUpdate() override;
	virtual void			onDestroy() override;
	virtual void			onDraw(Graphics* i_g) override;
	virtual void			onDrawShadow(Graphics* i_g) override;
	/// GameObject interface end

	void 					onBombExplosionEnd(const std::string& i_animLabelName);
	void 					onBombCloseToExplosionEnd(const std::string& i_animLabelName);
	void 					onFuseLitEnd();

	virtual void 			registerForEvents() override;

	/// Bomb State Machine
	DECLARE_STATE_FUNCTIONS(BombState, INIT);
	DECLARE_STATE_FUNCTIONS(BombState, SPAWN);
	DECLARE_STATE_FUNCTIONS(BombState, READY);
	DECLARE_STATE_FUNCTIONS(BombState, CLOSETOEXPLOSION);
	DECLARE_STATE_FUNCTIONS(BombState, EXPLODE);

private:

	void 					CreateSpawnEffect();
	void 					killPlantsAround() const;

	int32					getBombStateSerialization();
	void					setBombStateSerialization(int32 i_state);

	int								m_row = 0;
	float 							m_whiteFadeToBoardTimeRemaining = 0.0f;
	RtWeakPtr<class PopAnimRig> 	m_bombPopAnimRig;

    RtWeakPtr<Fuse>					m_fuse;

    StateMachine<BombState> 		m_bombState;
};

namespace Message
{
	void BombTriggered(Bomb* i_bomb);
}


#endif //PlantsVersusZombies2_Bomb_h


//PVZ2_CHINESE_END


