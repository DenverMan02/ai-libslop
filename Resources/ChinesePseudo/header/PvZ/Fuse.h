//
//  Fuse.h
//  PlantsVersusZombies2
//
//  Created by hanj on 12/04/13.
//  Copyright (c) 2013 PopCap Games. All rights reserved.
//

//PVZ2_CHINESE_BEGIN

#ifndef PlantsVersusZombies2_Fuse_h
#define PlantsVersusZombies2_Fuse_h

#include "BoardEntity.h"
#include "StateMachine.h"

STATE_ENUM_BASE_BEGIN(FuseState)
	FuseState_INIT,
	FuseState_PAVE,
	FuseState_READY,
	FuseState_LIT,
STATE_ENUM_END(FuseState);

//forward declaration
class BombProperties;

class Fuse : public BoardEntity
{
public:
	static const float sPaveFuseSpeed;

public:
	RT_CLASS_DEFINE(Fuse, BoardEntity, RtClass);

	/// BoardEntity interface
	virtual int 		CalcRenderOrder() const override;
	/// BoardEntity interface end

	bool       			isInState(FuseState i_state) const;
	void        		setState(FuseState i_newState);

	float 				getSpeedByPixel() const {return m_speedByPixel;}

	float				getCurrentLength() const {return m_currentFuseLengthByPixel;}

protected:
	/// GameObject interface
	virtual void		onUpdate() override;
	virtual void		onDestroy() override;
	virtual void		onDraw(Graphics* i_g) override;
	/// GameObject interface end

	void 				onFlameExtinguished();
	virtual void registerForEvents() override;

private:
	friend class Bomb;

	void				FuseInitialize(const BombProperties& i_bombProps, int i_row);

	int32				getFuseStateSerialization();
	void				setFuseStateSerialization(int32 i_state);

	void 				EndFuseLit();

	/// Bomb State Machine
	DECLARE_STATE_FUNCTIONS(FuseState, INIT);
	DECLARE_STATE_FUNCTIONS(FuseState, PAVE);
	DECLARE_STATE_FUNCTIONS(FuseState, READY);
	DECLARE_STATE_FUNCTIONS(FuseState, LIT);

	int												m_row;
	int 											m_fuseLengthByGrid;

    StateMachine<FuseState> 						m_fuseState;

    float 											m_speedByPixel;
    float 											m_currentFuseLengthByPixel;

    RtWeakPtr<class GridItemFlame>					m_flame;
    RtWeakPtr<class PopAnimRig> 					m_fuseBallPopAnimRig;
};
typedef RtWeakPtr<Fuse> FusePtr;

#endif //PlantsVersusZombies2_Fuse_h


//PVZ2_CHINESE_END


