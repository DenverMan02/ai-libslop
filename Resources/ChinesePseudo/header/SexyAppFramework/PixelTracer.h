#ifndef __PIXELTRACER_H__
#define __PIXELTRACER_H__

#ifdef SUPPORT_PIXELTRACER
#ifndef RELEASEFINAL

#include "RenderDevice.h"

namespace Sexy
{

class Image;
class RenderStateManager;

void PixelTracerStart(int theX, int theY);
void PixelTracerStop();
void PixelTracerAddToTrace();
void PixelTracerCheckPrimitives(int thePrimType, ulong thePrimCount, const SexyVertex2D* theVertices, int theVertexSize);

extern bool gTracingPixels;
extern Image* gPixelTracerLastImage;
extern RenderStateManager* gPixelTracerStateManager;
extern const Rect* gPixelTracerSrcRect;


}

#endif // #ifndef RELEASEFINAL
#endif // SUPPORT_PIXELTRACER
#endif //__PIXELTRACER_H__
