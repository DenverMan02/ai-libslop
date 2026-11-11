// Definition.h

#ifndef __DEFINITION_H__
#define __DEFINITION_H__

#include "TodCommon.h"
#include "Curve.h"

enum DefFieldType
{
	DT_INVALID,
	DT_INT,
	DT_FLOAT,
	DT_STRING,
	DT_ENUM,
	DT_VECTOR2,
	DT_VECTOR3,
	DT_RECT,
	DT_BOOL,
	DT_ARRAY,
	DT_ARRAY_FROM_FILE,
	DT_ARRAY_SSL,
	DT_ARRAY_SSL_KEY,
	DT_TRACK_FLOAT,
	DT_FLAGS,
	DT_IMAGE,
	DT_FONT,
	DT_BOOL_SSL_KEY,
	DT_INT_SSL,
};


class FloatParameterTrackNode
{
public:
	float       m_time;
	float       m_lowValue;
	float       m_highValue;
	CurveType   m_curveType;
	CurveType   m_distribution;
};

class FloatParameterTrack
{
public:
	FloatParameterTrackNode *m_nodes;
	int m_countNodes;
};

class IntArrayData
{
public:
	int *m_data;
	int m_dataCount;
};

class CharArrayData
{
public:
	char *m_data;
	int m_dataCount;
};

class SSListKey
{
public:
	// Two dimensional array... kinda
	CharArrayData *m_key;
	int m_keyCount;
//	std::vector<std::vector<bool>>	m_data;
};

extern FloatParameterTrack FloatTrackAlwaysOne;
extern FloatParameterTrack FloatTrackAlwaysZero;

class DefSymbol
{
public:
	int m_symbolValue;
	const SexyChar *m_symbolName;
};

class DefField
{
public:
	const SexyChar *m_fieldName;
	int m_fieldOffset;
	DefFieldType m_fieldType;
	void *m_extraData;
};

typedef void* (*ContructorFunc)(void *pointer);

class DefMap
{
public:
	DefField *m_mapFields;
	int m_defSize;
	ContructorFunc m_constructorFunc;
};

bool DefinitionLoadXML(const std::string& i_filename, DefMap *defMap, void *definition, bool i_skipCompile = false, bool i_runDefinitionConstructor = true);
bool DefSymbolValueFromString(DefSymbol *symbolMap, const SexyChar *name, int *resultValue);
const SexyChar* DefSymbolStringFromValue(DefSymbol *symbolMap, int i_value);
void* DefinitionAlloc(int size);
void* DefinitionRealloc(void *ptr, int size);
void DefinitionFree(void *ptr);
float FloatTrackEvaluate(FloatParameterTrack &i_track, float i_timeValue, float i_interp);
void FloatTrackGetMinMaxAtTime(FloatParameterTrack &i_track, float i_timeValue, float &i_min, float &i_max);
void FloatTrackSetDefault(FloatParameterTrack &track, float value);
bool FloatTrackIsSet(FloatParameterTrack &i_track);
bool FloatTrackIsConstantZero(FloatParameterTrack &track);
void DefinitionFreeMap(DefMap *defMap, void *definition);
bool DefinitionIsCompiled(const std::string& i_xMLFilePath);

#endif //__DEFINITION_H__
