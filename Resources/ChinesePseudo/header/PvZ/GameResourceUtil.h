/*
 * GameResourceUtil.h
 *
 *  Created on: 2019-4-8
 *      Author: zhousen
 */

#ifndef GAMERESOURCEUTIL_H_
#define GAMERESOURCEUTIL_H_

class GameResourceUtil
{
public:
    static Image* GetFrameImageByRare(int rare);
    static Image* GetFrameImageById(int id);
    static Image* GetImageById(int id);
};


#endif /* GAMERESOURCEUTIL_H_ */
