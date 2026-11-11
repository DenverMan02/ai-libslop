/*
 * RiftSeedBank.h
 *
 *  Created on: 2022-3-4
 *      Author: admin
 */

#ifndef RIFTSEEDBANK_H_
#define RIFTSEEDBANK_H_

#include "core.h"
#include "RtObject.h"
#include "UIWidget.h"
#include "PVZTypes.h"
#include "SeedBank.h"
#include "SeedPacket.h"

class RiftSeedBank : public SeedBankNew
{

public:
	RT_CLASS_DEFINE(RiftSeedBank, SeedBankNew, RtClass);

	RiftSeedBank();
	virtual ~RiftSeedBank();

	void SetNumPackets(uint8 i_numPackets, bool i_updatePositions = true) override;

private:
	void OnSeedChooserFinalized();
	void OnNotifyToolPlantLevelUp();
};

#endif /* RIFTSEEDBANK_H_ */
