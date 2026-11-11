#ifndef BRIDGE_H_INCLUDED
#define BRIDGE_H_INCLUDED



namespace Sexy 
{
	void Bridge_RotateUI( int to, float durationSecs );
	bool Bridge_IsUIOrientationAllowed( int theOrientation );
	int Bridge_GetAppOrientation();
}


#endif
