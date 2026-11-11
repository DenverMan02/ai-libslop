/*
 * default_board.h
 *
 *  Created on: 2013-9-9
 *      Author: chenyc
 */

#ifndef DEFAULT_BOARD_H_
#define DEFAULT_BOARD_H_

#include "Precompile.h"

class defaultBoard : public Sexy::Widget//,  public Sexy::ButtonListener
{
public:
	defaultBoard( int Width, int Height );
	virtual~defaultBoard();

	virtual void Update();
	virtual void Draw(Sexy::Graphics* g);

};


#endif /* DEFAULT_BOARD_H_ */
