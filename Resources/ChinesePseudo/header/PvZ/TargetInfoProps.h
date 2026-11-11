#ifndef __TARGET_INFO_PROPS_H__
#define __TARGET_INFO_PROPS_H__

#include <string>
#include <vector>

#include "Core.h"
#include "ZombieEnums.h"
#include "Utils.h"
#include "PropertySheetBase.h"
#include "GridItemPropertySheet.h"

class TargetInfoProps : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(TargetInfoProps, PropertySheetBase, RtClass);

	TargetInfoProps()
	:IgnoreZombiesFlagged(ZT_Invalid)
	,IgnoreGridItemsFlagged(GT_Invalid)
	{}

	void FilterUntargetable(std::vector<BoardEntity*>& o_entities, const BoardEntityPtr targeter);
    void FilterUntargetableAtLoc(std::vector<BoardEntity*>& o_entities, const BoardEntityPtr targeter, Sexy::Point i_gridOrigin);
	void FilterUntargetableZombies(std::vector<BoardEntity*>& o_entities, const BoardEntityPtr targeter);
    void FilterUntargetableZombiesAtLoc(std::vector<BoardEntity*>& o_entities, const BoardEntityPtr targeter, Sexy::Point i_gridOrigin);
	void FilterUntargetableGridItems(std::vector<BoardEntity*>& o_entities, const BoardEntityPtr targeter);
    void FilterUntargetableGridItemsAtLoc(std::vector<BoardEntity*>& o_entities, const BoardEntityPtr targeter, Sexy::Point i_gridOrigin);
	
private:
	void makeSureInitialized();
	void compileZombieFlags();
	void compileGridItemFlags();
	
	ZombieTestFlag IgnoreZombiesFlagged;
	GridItemTestFlag IgnoreGridItemsFlagged;
	std::vector<ZombieTestFlag> JsonIgnoreZombiesFlagged;
	std::vector<GridItemTestFlag> JsonIgnoreGridItemsFlagged;
};
#endif // __TARGET_INFO_PROPS_H__
