/*
 * PuzzleTipUtil.h
 *
 *  Created on: 2019-4-8
 *      Author: zhousen
 */

#ifndef PUZZLETIPUTIL_H_
#define PUZZLETIPUTIL_H_

class PuzzleTipUtil {
public:
    static PuzzleTip* PopTip(SexyString tip, Rect rect);
    static void DeleteTip(PuzzleTip* tipPtr);
    static Rect CreateTipRect(Point pos, int buttonWidth);
};



#endif /* PUZZLETIPUTIL_H_ */
