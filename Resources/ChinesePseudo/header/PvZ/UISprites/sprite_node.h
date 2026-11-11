/*
 * sprite_node.h
 *
 *  Created on: 2013-9-9
 *      Author: chenyc
 */

#ifndef SPRITE_NODE_H_
#define SPRITE_NODE_H_

#include "Precompile.h"

class spriteNode : public Sexy::Widget
{
public:
	spriteNode( Sexy::Image* img );
	virtual~spriteNode();

	virtual void Update();
	virtual void Draw(Sexy::Graphics* g);

private:
	Sexy::Image* currentImg_;
};


#endif /* SPRITE_NODE_H_ */
