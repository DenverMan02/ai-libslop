// LawnMower.h

#ifndef __LAWNMOWER_H__
#define __LAWNMOWER_H__

#include "BoardEntity.h"
#include "EntityComponent.h"

class GridItemArmrack;


enum LawnMowerState
{
	MOWER_INVALID,
	MOWER_INITTED,
	MOWER_READY,
	MOWER_TRIGGERED,
};

class LawnMower : public BoardEntity
{
public:
	RT_CLASS_DEFINE(LawnMower, BoardEntity, RtClass);
	
	LawnMower();
	~LawnMower();
    
    static SexyVector3 GetStartingLocation(int i_rowIndex);

	void				LawnMowerInitialize(PopAnim* i_mowerPopAnim, int i_row, const std::string& i_activatedAudioEvent, std::vector<int> i_idleAnimWeights);
	void				ResetStartingLocation();
	
	void				SpawnMower();
	void				StartMower();
	void				MowZombie(class Zombie* i_zombie);
    void				MowGridItem(class GridItem* i_gridItem);
    
	void				CreateSpawnEffect();
	
	Rect			GetAttackRect();
    void				SetRow(int i_row);
    int				GetRow() { return m_row; }
    void            SetMowerState(LawnMowerState state) { m_mowerState = state; }
	LawnMowerState		GetMowerState() const { return m_mowerState; }
	static Rect	GetAttackRect(const SexyVector2& pos);
	static Rect	GetAttackRect(int i_row);
	static SexyVector2	GetArtOffset();
    void                SetExplodeAtGridX(int i_gridX) { m_explodeAtGridX = i_gridX; }

	/// BoardEntity interface
	virtual int 		CalcRenderOrder() const override;

    int					GetNumZombiesMowed() { return m_numZombiesMowed; }
    
    bool				ShouldClipWithWater() const override;
    bool				ShouldDrawShadow() const override;
    
protected:
	/// GameObject interface
	virtual void		onInitialized() override;
	virtual void		onUpdate() override;
	virtual void		onDestroy() override;
	virtual void		onDraw(Graphics* i_g) override;
	virtual void		onDrawShadow(Graphics* i_g) override;
    virtual void		registerForEvents() override;
	virtual void		unregisterForEvents() override;
	
private:
    
    bool onTouchEvent(const Sexy::Touch& i_touch);
	void clearTouch();
    
    void				updateGroundEffect();
    
	void				initializePAM(PopAnim* i_mowerPopAnim, std::vector<int> i_animIdleWeights);
    void				onAnimStopped(const std::string& i_animName);
    static float		getRowToPixelY(int i_row);
    void				tryDestroy();
    
    EntityComponent_GroundEffect	m_groundEffect;

	int					m_row;
	LawnMowerState		m_mowerState;
	
	RtWeakPtr<class PopAnimRig>	m_popAnimRig;
    
    pvztime_t			m_chompTime;
    std::string			m_activatedAudioEvent;
    bool				m_fallingIntoWater;
    int					m_numZombiesMowed;
    pvztime_t			m_fallingStartTime;
    pvztime_t 			m_touchStartTime;
	Sexy::TouchID       m_touch;
    int                 m_explodeAtGridX;
};

namespace Message
{
	void MowerDie(LawnMower* i_mower);
	void MowerTriggered(LawnMower* i_mower);
    void MowerCreated(LawnMower* i_mower);
	void MowerInitialized(LawnMower* i_mower);
	void MowerReset(LawnMower* i_mower);
	void ZombieMowed(LawnMower* i_mower);
	void MowerLaunched(LawnMower* i_mower);
}

#endif //__LAWNMOWER_H__



