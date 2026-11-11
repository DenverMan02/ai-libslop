#include "CustomUpgrades.h"
#include "GameFeature.h"
#include "MemUtils.h"

namespace
{
typedef int (*GetSeedSlotCountFunc)(void*);
GetSeedSlotCountFunc oGetSeedSlotCount = nullptr;

int hkGetSeedSlotCount(void* self)
{
    const int originalSlotCount = oGetSeedSlotCount(self);

    // The vanilla function already counts features 11 and 12 and clamps
    // against its vanilla slot-data vector. Feature 129 is our additional
    // slot, so add it after the vanilla result rather than modifying the
    // vanilla cap logic.
    if (CallFunc<bool, void*, int>(0x947870, nullptr, upgrade_9_slots))
        return originalSlotCount + 1;

    return originalSlotCount;
}
}

namespace CustomUpgrades
{
void modInit()
{
    PVZ2HookFunction(0xA50220, (void*)hkGetSeedSlotCount,
                     (void**)&oGetSeedSlotCount);
}
}
