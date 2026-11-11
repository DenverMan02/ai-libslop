//
//  LineBatcher.h
//  PlantsVersusZombies2
//
//  Created by jsola on 8/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_LineBatcher_h
#define PlantsVersusZombies2_LineBatcher_h

#include "Precompile.h"
#include "DataArray.h"
#include "ResourceHelpers.h"
#include "TimeMgr.h"

template<typename T>
class Batcher
{
public:
	void Initialize(int i_maxBatcherSize)
	{
		m_entries.DataArrayInitialize(i_maxBatcherSize, "linebatcher");
	}

	void CleanUp(pvztime_t i_currTime)
	{
		for (T* entry = NULL; m_entries.IterateNext(entry); )
		{
			if (i_currTime >= entry->GetEndTime())
				m_entries.DataArrayFree(entry);
		}
	}
	
	void Draw(Graphics* i_g)
	{
		GraphicsAutoState ag(i_g);
		for (T* entry = NULL; m_entries.IterateNext(entry); )
		{
			DrawItem(i_g, entry);
		}
	}
	
	virtual void DrawItem(Graphics* i_g, T* i_item) = 0;
	
protected:
	T* add()
	{
		T* ret = m_entries.DataArrayAlloc();
		if (!ret)
		{
			OutputDebugStrF("*** Batcher::Add Failed, ran out of slots in the batcher!\n");
			return NULL;
		}
		return ret;
	}
	
	bool iterate(T *&i_item)
	{
		return m_entries.IterateNext(i_item);
	}
	
	
private:
	DataArray<T> m_entries;
};


struct LineEntry
{
	float x0, y0, x1, y1;
	Color color;
	
	pvztime_t endTime;

	pvztime_t GetEndTime() { return endTime; }
};

class LineBatcher : public Batcher<LineEntry>
{
public:
	void Add(float i_x0, float i_y0, float i_x1, float i_y1, Color i_color, pvztime_t i_endTime);
	virtual void DrawItem(Graphics* i_g, LineEntry* i_item);
};


struct TextEntry
{
	float x, y;
	SexyString text;
	PrimeTypeface* font;
	PrimeTypeface* outlineFont;
	Color color;
	DrawStringJustification justification;
	
	pvztime_t endTime;
	
	pvztime_t GetEndTime() { return endTime; }
};

class TextBatcher : public Batcher<TextEntry>
{
public:
	void Add(float i_x, float i_y, const SexyString& i_text, PrimeTypeface* i_font, PrimeTypeface* i_outlineFont, DrawStringJustification i_just, Color i_color, pvztime_t i_endTime);
	void Add(float i_x, float i_y, const std::string& i_text, PrimeTypeface* i_font, PrimeTypeface* i_outlineFont, DrawStringJustification i_just, Color i_color, pvztime_t i_endTime);
	virtual void DrawItem(Graphics* i_g, TextEntry* i_item);
};


#endif
