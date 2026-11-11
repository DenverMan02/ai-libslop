/*
 * SkillPropertySheet.h
 *
 *  Created on: 2014-5-26
 *      Author: jianglc
 */

#ifndef SKILLPROPERTYSHEET_H_
#define SKILLPROPERTYSHEET_H_

#include "RtDb.h"
#include "PropertySheetBase.h"

typedef RtWeakPtr<class SkillPropertySheet> SkillPropertySheetPtr;

class SkillPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(SkillPropertySheet, PropertySheetBase, RtClass);

	SkillPropertySheet()
	{
		SkillName = "";
		SkillDescription = "";
		SkillIconImage = "";
	}

	std::string SkillName;
	std::string SkillDescription;
	std::string SkillIconImage;
};


#endif /* SKILLPROPERTYSHEET_H_ */
