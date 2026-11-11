/*
 * PopAnimEffectFactory.h
 *
 *  Created on: 2019-3-11
 *      Author: zhousen
 */

#ifndef POPANIMEFFECTFACOTRY_H_
#define POPANIMEFFECTFACOTRY_H_

#include <string>

class PopAnimEffectFactory
{
public:
	static class RtWeakPtr<GameObject> CreateEffect(std::string name, int layer, class SexyVector3 position, bool isScreenSpaceEffect = false, bool isVisible = false);
};

#endif /* POPANIMEFFECTFACOTRY_H_ */
