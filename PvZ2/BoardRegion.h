#pragma once

#include "GameObject.h"
#include "BoardEntity.h"
#include <Sexy/Rect.h>

enum BoardRegionFlags {
	region_deepwater = 1,
	region_tidewater = 2,
	region_sky = 4
};

class BoardRegion : public GameObject
{
public:
	int m_flags;
	Sexy::FRect m_region;
	int unk;

	virtual void SetRegionFromGridSquare(const Rect& rect) {
		CallFunc<void, BoardRegion*, const Rect*>(0x729C48, this, &rect);
	}

	virtual void Function13() {}
	virtual void OnParticleImpact() {}
	virtual void CanPlantGoHere(int* gridCoords, int plantType, std::vector<int>* reasonsVec) {}
	virtual float GetSinkDistance(float*) { return 0.0f; }
	virtual void RunsEveryFrame() {}
};

class BoardRegionTideWater : public BoardRegion
{
public:
	static Sexy::RtClass* StaticGetClass() {
		return CallFunc<Sexy::RtClass*>(0x6854F0);
	}

	void SetRegionFromGridSquare(const Rect& rect) override {
		CallFunc<void, BoardRegionTideWater*, const Rect*>(0x729C48, this, &rect);
	}
};
