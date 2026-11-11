/*
 * CollectableWorldStarUnlock.h
 *
 *  Created on: Feb 26, 2014
 *      Author: zhaobk
 */

#ifndef COLLECTABLEWORLDSTARUNLOCK_H_
#define COLLECTABLEWORLDSTARUNLOCK_H_

#include "Collectable.h"
#include "RtObject.h"

// This class only exists so that we can switch on the type.
class CollectableWorldStarUnlock : public Collectable
{
public:
	RT_CLASS_DEFINE(CollectableWorldStarUnlock, Collectable, RtClass) {}
};


#endif /* COLLECTABLEWORLDSTARUNLOCK_H_ */
