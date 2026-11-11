//
//  DebugDraw.h
//  PlantsVersusZombies2
//
//	Debug draw render queue!
//
//  Created by jsola on 8/8/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_DebugDraw_h
#define PlantsVersusZombies2_DebugDraw_h

#include "core.h"
#include "TimeMgr.h"
#include "LineBatcher.h"
#include "ResourceHelpers.h"


#if !DEBUG_DRAW_ENABLED

#define DebugDraw_Line(x0, y0, x1, y1, color, duration) ((void)(x0), (void)(y0), (void)(x1), (void)(y1), (void)(color), (void)(duration))
#define DebugDraw_Box(x0, y0, x1, y1, color, duration) ((void)(x0), (void)(y0), (void)(x1), (void)(y1), (void)(color), (void)(duration))
#define DebugDraw_Rect(rect, color, duration) ((void)(rect), (void)(color), (void)(duration))
#define DebugDraw_Text(string, x, y, justification, color, duration) ((void)(string), (void)(x),(void)(y), (void)(justification), (void)(color), (void)(duration))
#define DebugDraw_TextSmall(string, x, y, justification, color, duration) ((void)(string), (void)(x),(void)(y), (void)(justification), (void)(color), (void)(duration))
#define DebugDraw_Circle(x0, y0, radius, color, duration) ((void)(x0), (void)(y0), (void)(radius), (void)(color), (void)(duration))
#define DebugDraw_ScreenSpaceRuler(x0, y0, x1, y1, interval, color, duration) ((void)(x0), (void)(y0), (void)(x1), (void)(y1), (void)(interval), (void)(color), (void)(duration))
#define DebugDraw_BoardSpaceRuler(x0, y0, x1, y1, interval, color, duration) ((void)(x0), (void)(y0), (void)(x1), (void)(y1), (void)(interval), (void)(color), (void)(duration))

#else

#define DebugDraw_Line(x0, y0, x1, y1, color, duration) \
	(gDebugDraw->DrawLine(x0, y0, x1, y1, color, duration))
#define DebugDraw_Box(x0, y0, x1, y1, color, duration) \
	(gDebugDraw->DrawRect(x0, y0, x1, y1, color, duration))
#define DebugDraw_Rect(rect, color, duration) \
	(gDebugDraw->DrawRect(rect, color, duration))
#define DebugDraw_Text(string, x, y, justification, color, duration) \
	(gDebugDraw->DrawText(string, x, y, justification, DEBUG_TEXT_FONT, NULL /*DEBUG_TEXT_FONT_OUTLINE*/, color, duration))
#define DebugDraw_TextSmall(string, x, y, justification, color, duration) \
	(gDebugDraw->DrawText(string, x, y, justification, DEBUG_TEXT_FONT_SMALL, DEBUG_TEXT_FONT_SMALL_OUTLINE, color, duration))
#define DebugDraw_Circle(x0, y0, radius, color, duration) \
	(gDebugDraw->DrawCircle(x0, y0, radius, color, duration))
#define DebugDraw_ScreenSpaceRuler(x0, y0, x1, y1, interval, color, duration) \
	(gDebugDraw->DrawRuler(x0, y0, x1, y1, 1.f, interval, color, duration))
#define DebugDraw_BoardSpaceRuler(x0, y0, x1, y1, interval, color, duration) \
	(gDebugDraw->DrawRuler(x0, y0, x1, y1, S(1.f), interval, color, duration))

class DebugDraw
{
public:
	void DrawLine(float i_x0, float i_y0, float i_x1, float i_y1, const Color& i_drawColor, pvztime_t i_duration = 0.f);
	void DrawLine(const SexyVector2& i_startPoint, const SexyVector2& i_endPoint, const Color& i_drawColor, pvztime_t i_duration = 0.f);
	void DrawRect(float i_x0, float i_y0, float i_x1, float i_y1, const Color& i_drawColor, pvztime_t i_duration = 0.f);
	void DrawRect(const SexyVector2& i_firstCorner, const SexyVector2& i_secondCorner, const Color& i_drawColor, pvztime_t i_duration = 0.f);
	void DrawRect(const Sexy::Rect& i_rect, const Color& i_drawColor, pvztime_t i_duration = 0.f);
	void DrawCircle(float i_x0, float i_y0, float i_radius, const Color& i_drawColor, pvztime_t i_duration = 0.f);
	void DrawCircle(const SexyVector2& i_center, float i_radius, const Color& i_drawColor, pvztime_t i_duration = 0.f);
	void DrawRuler(float i_x0, float i_y0, float i_x1, float i_y1, float i_scale, float i_interval, const Color& i_drawColor, pvztime_t i_duration = 0.f);
	
	void DrawText(const std::string& i_text, float i_x, float i_y, DrawStringJustification i_justification, PrimeTypeface* i_font, class PrimeTypeface* i_outlineFont, const Color& i_drawColor, pvztime_t i_duration = 0.f);
	
	void Initialize();
	void Draw(Graphics* i_g);
	void CleanUp();
	
private:
	inline pvztime_t calcEndTime(pvztime_t i_duration);
	
	LineBatcher m_lines;
	TextBatcher m_text;
};

extern DebugDraw *gDebugDraw;
#endif

#endif