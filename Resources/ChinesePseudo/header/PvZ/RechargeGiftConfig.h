//
//  RechargeGiftConfig.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 15/5/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_RechargeGiftConfig_h
#define PlantsVersusZombies2_RechargeGiftConfig_h


#include "RtObject.h"
#include "TimeMgr.h"


class RechargeGiftConfig : public Sexy::RtObject
{
public:
    RT_CLASS_DEFINE(RechargeGiftConfig, Sexy::RtObject, RtClass);
    
	static RechargeGiftConfig*			GetConfig(const std::string& packageName = "");
    
	const std::string&							GetPackageName() const { return m_strPackageName; }
	const std::string&							GetPackageDesc() const { return m_strPackageDesc; }
	const std::string&							GetSku() const { return m_strPaySku; }
	const std::string&							GetTitle() const { return m_strTitle; }
	const std::vector<std::string>&	GetPlants() const { return m_vecPlants; }
	int													GetStartDate() const { return m_iStartDate; }
	int													GetEndDate() const { return m_iEndDate; }

private:
	std::string						m_strPackageName;
	std::string						m_strPackageDesc;
	std::string						m_strTitle;
	std::string						m_strPaySku;
	std::vector<std::string> m_vecPlants;
	int									m_iStartDate;
	int									m_iEndDate;
};


#endif
