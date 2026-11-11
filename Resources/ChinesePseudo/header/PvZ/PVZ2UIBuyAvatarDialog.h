/*
 * PVZ2UIBuyAvatarDialog.h
 *
 *  Created on: Jan 15, 2014
 *      Author: lijie
 */

#ifndef PVZ2UIBUYAVATARDIALOG_H_
#define PVZ2UIBUYAVATARDIALOG_H_

#include "PVZ2UIBuyPlantDialog.h"
#include "TodStringFile.h"
#include "UIHelper.h"
#include "ProfileUtils.h"

class PVZ2UIBuyAvatarDialog: public PVZ2UIBuyPlantDialog
{
public:
	PVZ2UIBuyAvatarDialog(MagentoProductPropsPtr i_props, bool i_quick = true);
	virtual ~PVZ2UIBuyAvatarDialog();

	virtual void ButtonDepress(int i_id);
    
    void onUseGemFinish(const bool& isSuccess);
};

#endif /* PVZ2UIBUYAVATARDIALOG_H_ */
