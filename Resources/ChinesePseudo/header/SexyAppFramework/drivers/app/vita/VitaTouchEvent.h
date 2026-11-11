/*                 -*- mode: c; tab-width: 4; indent-tabs-mode: t; -*- */
/* SCE CONFIDENTIAL
 PSP2 Programmer Tool Runtime Library Release 00.931.000
 *
 *      Copyright (C) 2010 Sony Computer Entertainment Inc.
 *                        All Rights Reserved.
 *
 */

#ifndef _SCE_TOUCH_SAMPLE_EVENT_H
#define _SCE_TOUCH_SAMPLE_EVENT_H


#include <scetypes.h>
#include <touch.h>

#if defined(__cplusplus)
extern "C" {
#endif

/*E Maximum number of basic event */
#define MAX_EVENT   (SCE_TOUCH_MAX_REPORT * 2)

/*E Default value of move threshold */
#define MOVE_THRESHOLD  10

/*E Type of basic event */
typedef enum TouchEvent{
	TOUCH_EVENT_RELEASE = 0,
	TOUCH_EVENT_PRESS,
	TOUCH_EVENT_HOLD,
	TOUCH_EVENT_MOVE,
}TouchEvent;

/*E Touch Event Element  */
typedef struct TouchEventElem{
	TouchEvent  event;		/*E Event Type         */
	SceUInt8    id;			/*E Touch ID           */
	SceInt16    curX;		/*E Current x position */
	SceInt16    curY;		/*E Current y position */
	SceInt16    curF;		/*E Current force      */
	SceInt16    deltaX;		/*E Delta x position   */
	SceInt16    deltaY;		/*E Delta y position   */
	SceInt16    deltaF;		/*E Delta force        */
	SceUInt32   deltaT;		/*E Delta time         */
	SceUInt32   elapsedT;	/*E Elapsed time       */

	struct TouchEventElem* pNext;
}TouchEventElem;

/*E Basic Touch Event Information */
typedef struct TouchEventInfo{
	SceUInt32       updateTime;		/*E Last update time              */
	SceUInt32       moveThreshold;	/*E The threshold of "MOVE" state */
	TouchEventElem* pFree;			/*E Free Resources                */
	TouchEventElem* pPress;			/*E "PRESS"   state Touch.        */
	TouchEventElem* pHold;			/*E "HOLD"    state Touch.        */
	TouchEventElem* pMove;			/*E "MOVE"    state Touch.        */
	TouchEventElem* pRelease;		/*E "RELEASE" state Touch         */
	TouchEventElem  eventElem[MAX_EVENT];
}TouchEventInfo;

/*E Initialize the TouchEventInfo Structure. */
int touchEventInit(TouchEventInfo* pEventInfo);

/*E Set threshold to judge "MOVE" or "HOLD" event. (Default:10) */
int touchEventSetMoveThreshold(TouchEventInfo* pEventInfo, SceUInt32 threshold);

/*E Updates the event information. */
int touchEventUpdate(const SceTouchData* pData, TouchEventInfo* pEventInfo);

/*E Dump Event Element */
void touchEventDumpElemQueue(TouchEventElem* pEventElem);

#if defined(__cplusplus)
}
#endif


#endif  /* _SCE_TOUCH_SAMPLE_EVENT_H */

