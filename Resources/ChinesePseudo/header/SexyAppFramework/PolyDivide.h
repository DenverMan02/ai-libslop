#ifndef __POLYTRI_H__
#define __POLYTRI_H__

#include "Common.h"
#include "Point.h"

namespace Sexy
{
	bool DividePoly(FPoint v[], int n, FPoint theTris[][3], int aMaxPolys, int* theNumTris);
}

#endif //__POLYTRI_H__
