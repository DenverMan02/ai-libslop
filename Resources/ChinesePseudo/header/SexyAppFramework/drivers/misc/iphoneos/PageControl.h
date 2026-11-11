/*
 *  PageControl.h
 *  SexyAppFramework
 *
 *  Created by Joseph Mobley on 2/5/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "Widget.h"

namespace Sexy
{

	class PageControl : public Widget
	{
		typedef Widget super;

	public:
		
		PageControl( Image* partsImage );
		~PageControl();
		
		void SetNumberOfPages( int count );
		void SetCurrentPage( int page );
		int GetCurrentPage();

		void Draw( Graphics* g );
		
	protected:
		
		Image* mPartsImage;
		int mNumberOfPages;
		int mCurrentPage;
	};

}
