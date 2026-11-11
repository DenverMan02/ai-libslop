/*
 * CardGameBoardConfig.h
 *
 *  Created on: 2022-6-6
 *      Author: admin
 */

#ifndef CARDGAMEBOARDCONFIG_H_
#define CARDGAMEBOARDCONFIG_H_

#include "PropertySheetBase.h"
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "BoardConstants.h"

struct TagColorValue
{
	TagColorValue()
	: Red(0)
	, Green(0)
	, Blue(0)
	, Alpha(0)
	{

	}

	int Red;
	int Green;
	int Blue;
	int Alpha;
};

struct TagData
{
	TagData()
	: Name("")
	, ColorValue("")
	{

	}

	std::string Name;
	TagColorValue Color;
	std::string ColorValue;
};

class CardGameBoardConfig : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(CardGameBoardConfig, PropertySheetBase, RtClass);

public:
	float GetCommonConfigValue(const std::string& i_key, float i_default) const;
	std::string GetCardUIConfigValue(const std::string& i_key, std::string i_default) const;
	const TagColorValue& GetTagColor(int i_tag) const;
	const TagData& GetTagData(int i_tag) const;

public:
	std::map<std::string, float> CommonConfigsNormal;
	std::map<std::string, float> CommonConfigsLarge;
	std::map<std::string, float> CommonConfigsFull;
	std::map<std::string, std::string> StringMaps;
	std::vector<TagData> Tags;
};


#endif /* CARDGAMEBOARDCONFIG_H_ */
