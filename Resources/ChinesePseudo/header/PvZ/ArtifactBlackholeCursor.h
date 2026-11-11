/*
 * ArtifactBlackholeCursor.h
 *
 *  Created on: 2022-8-22
 *      Author: zohusen
 */

#ifndef ARTIFACTBLACKHOLECURSOR_H_
#define ARTIFACTBLACKHOLECURSOR_H_

#include "PVZTypes.h"
#include "PacketCursor.h"
#include "Point.h"
#include "RtObject.h"
#include "SeedPacket.h"

class ArtifactBlackholeCursor : public PacketCursor
{
public:
	RT_CLASS_DEFINE(ArtifactBlackholeCursor, PacketCursor, RtClass) {}

	ArtifactBlackholeCursor() {}
	~ArtifactBlackholeCursor();

	explicit ArtifactBlackholeCursor(const Sexy::Touch& i_boardSpaceTouch, SeedPacketPtr i_seedPacket);

	bool CanUseAtCurrentPosition() override;
	Point GetCurrentGridPosition() override;
	bool IsInsideOriginRect() const override;

	PlantTypePtr GetPlantType() const { return m_plantType; }

protected:
	bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;
	void tryToUse() override;

	void cacheOrDestroyCursor();
	bool canAffordPlant(PlantTypePtr i_plantType) const;
	Sexy::SexyVector2 getCursorAnimOffset() const override;

	PlantTypePtr m_plantType;
};


///ArtifactEvolutionCursor
class ArtifactEvolutionCursor : public PacketCursor
{
public:
	RT_CLASS_DEFINE(ArtifactEvolutionCursor, PacketCursor, RtClass) {}

	ArtifactEvolutionCursor(){

	}
	virtual ~ArtifactEvolutionCursor();

	explicit ArtifactEvolutionCursor(const Sexy::Touch& i_boardSpaceTouch, SeedPacketPtr i_seedPacket);

	bool CanUseAtCurrentPosition() override;
	Point GetCurrentGridPosition() override;
	bool IsInsideOriginRect() const override;

	PlantTypePtr GetPlantType() const { return m_plantType; }

protected:
	bool onTouchEvent(const Sexy::Touch& i_boardSpaceTouch) override;
	void tryToUse() override;

	void cacheOrDestroyCursor();
	bool canAffordPlant(PlantTypePtr i_plantType) const;
	Sexy::SexyVector2 getCursorAnimOffset() const override;

	PlantTypePtr m_plantType;

};

#endif /* ARTIFACTBLACKHOLECURSOR_H_ */
