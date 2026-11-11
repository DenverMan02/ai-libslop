/*
 * UniverseUnlockGate.h
 *
 *  Created on: 2015-3-25
 *      Author: jianglc
 */

#ifndef UNIVERSEUNLOCKGATE_H_
#define UNIVERSEUNLOCKGATE_H_

#include "Core.h"
#include "Effect_PopAnim.h"

enum GateLevel
{
	LEVEL_ONE,
	LEVEL_TWO,
	LEVEL_THREE,
	LEVEL_FOUR,
    LEVEL_FIVE,
	LEVEL_COUNT
};

enum GateStatus
{
	NOT_ACTIVATED,
	ACTIVATING,
	ACTIVATED
};

class UniverseUnlockGate : public Sexy::Widget
{
public:
	UniverseUnlockGate(GateLevel i_level, int i_postionX, int i_postionY);
    virtual ~UniverseUnlockGate();

    virtual void Draw(Sexy::Graphics* i_g);
    virtual void DrawOverlay(Sexy::Graphics* i_g);

    virtual void Update();

    virtual void MouseUp(int x, int y, int theClickCount);

    void SetIsSelected(bool i_selected);

    bool IsSelected();

    bool CanBeSelected();

    std::string GetAnimLabel();

    void AddRequiredWorld(const std::string& i_world);

    void AddUnlockedWorld(const std::string& i_world);

    bool HasTargetWorld(bool i_required, const std::string& i_world);

    int GetWorldNum(bool i_required);

    void SetGateStatus(GateStatus i_status);

    void OnCloseDialog();

public:
    std::vector<std::string> m_requiredWorlds;
    std::vector<std::string> m_unlockedWorlds;
    Effect_PopAnim* m_UnlockGateAnim;

private:
    bool            m_isSelected;
    GateLevel m_level;
    GateStatus m_status;
};


#endif /* UNIVERSEUNLOCKGATE_H_ */
