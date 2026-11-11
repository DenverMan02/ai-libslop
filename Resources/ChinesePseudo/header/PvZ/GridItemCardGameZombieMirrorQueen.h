/*
 * GridItemCardGameZombieMirrorQueen.h
 *
 *  Created on: 2022-7-14
 *      Author: zhousen
 */

#ifndef GRIDITEMCARDGAMEZOMBIEMIRRORQUEEN_H_
#define GRIDITEMCARDGAMEZOMBIEMIRRORQUEEN_H_

#include "GridItemCardGameZombie.h"
#include "ProjectilePropertySheet.h"
#include "SexyAppFramework/SexyVector.h"
#include "Projectile.h"


// GridItemCardGameZombieMirrorQueenProps
class GridItemCardGameZombieMirrorQueenProps : public GridItemCardGameZombieProps
{
public:
    RT_CLASS_DEFINE(GridItemCardGameZombieMirrorQueenProps, GridItemCardGameZombieProps, RtClass);

    GridItemCardGameZombieMirrorQueenProps();

    int ThrowAppleAddCount;// apple add count after each mirror broken
    std::vector<Point> MirrorPos;// start generate mirro.
    int SummonFairytaleGargantuarCount;// summon count
    ProjectilePropertySheetPtr Projectile;// apple projectile
};

// GridItemCardGameZombieMirrorQueen
class GridItemCardGameZombieMirrorQueen : public GridItemCardGameZombie
{
public:
	RT_CLASS_DEFINE(GridItemCardGameZombieMirrorQueen, GridItemCardGameZombie, RtClass);

	GridItemCardGameZombieMirrorQueen();
	virtual ~GridItemCardGameZombieMirrorQueen();

	virtual void GenerateZombieActions() override;
	virtual void onPopAnimCommand(const std::string &i_animLabel, pvztime_t i_timeStamp, const std::string &i_command, const std::string &i_param) override;
	virtual void PlayAttackAnim() override;

protected:
	void onGridItemInitialize() override;

	void GenerateMirror();
	void SummonFairytaleGargantuar();
	void ThrowApple();
	void ThrowAppleTarget(BoardEntity* target);
	void AddThrowCount(const std::string& i_gridItemType);
	std::vector<BoardEntity*> FindTargets();

protected:
	int m_throwAppleCount;// throw apple number one action.
};

#endif /* GRIDITEMCARDGAMEZOMBIEMIRRORQUEEN_H_ */
