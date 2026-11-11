//
//  GridSquareElectricCurrantFencePiece.h
//  PlantsVersusZombies2
//
//  Created by Fleming, Eric on 2/4/16.
//  Copyright © 2016 PopCap Games. All rights reserved.
//

#ifndef GridSquareElectricCurrantFencePiece_h
#define GridSquareElectricCurrantFencePiece_h

#include <stdio.h>

#include "BoardEntity.h"

class GridSquareElectricCurrantFencePiece : public BoardEntity
{
public:
	RT_CLASS_DEFINE(GridSquareElectricCurrantFencePiece, BoardEntity, RtClass);
	
	GridSquareElectricCurrantFencePiece();
	
	void StartEffect(Point i_gridLocation);
	std::string getPamName();
    std::string getAnimName();
	Point GetGridLocation() { return m_gridLocation; }
	
	bool IsVertical() { return m_isVertical; }
	void SetIsVertical(bool i_isVertical) { m_isVertical = i_isVertical; }
	
	void StartEffect(Sexy::Point i_gridLocation, bool i_isPowered, bool i_isLevelAttack, bool i_isVertical);
	void ApplyPlantfood();
	
protected:
	void onDestroy() override;
	RtWeakPtr<class Effect_PopAnim> createEffect();
	
private:
	bool m_isVertical;
	bool m_isPowered; // TODO: do we care about this here?
    bool m_isLevelAttack;
	Point m_gridLocation;
	RtWeakPtr<class Effect_PopAnim> m_glowEffect;
};

class GridSquareElectricCurrantGlowPiece : public BoardEntity
{
public:
	RT_CLASS_DEFINE(GridSquareElectricCurrantGlowPiece, BoardEntity, RtClass);
	
	GridSquareElectricCurrantGlowPiece();
	
	void StartEffect(Point i_gridLocation);
	std::string getPamName();
    std::string getAnimName();
	Point GetGridLocation() { return m_gridLocation; }
	
	void StartEffect(Sexy::Point i_gridLocation, bool i_isPowered, bool i_isLevelAttack, RealObject *i_targetEntity);
	void ApplyPlantfood(RealObject *i_targetEntity);
	RtWeakPtr<class Effect_PopAnim> GetGlowEffect() { return m_glowEffect; }
	
protected:
	void onDestroy() override;
	RtWeakPtr<class Effect_PopAnim> createEffect(RealObject *i_targetEntity);
	
private:
	bool m_isPowered; 
	bool m_isLevelAttack;
	Point m_gridLocation;
	RtWeakPtr<class Effect_PopAnim> m_glowEffect;
};


#endif /* GridSquareElectricCurrantFencePiece_h */
