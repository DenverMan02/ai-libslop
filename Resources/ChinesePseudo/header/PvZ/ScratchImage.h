//
//  ScratchImage.h
//  PlantsVersusZombies2
//
//  Created by Andrew Khosravian on 4/29/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __SCRATCH_IMAGE_H__
#define __SCRATCH_IMAGE_H__

#include <memory>

// This class is for providing some shared scratch memory for full screen effects.
// This class is *not* thread safe. It should not be changed to manage a list of
// full screen images because that is memory usage madness.

namespace Sexy
{
	class Graphics;
}

// This class has a very big wart: the static value set via SetTransitionAlpha is used in the constructor
// right now that is set by the TransitionOverlayWidget.
// SetMinAlpha interacts with that value in a weird way.
// You can right the madness by calling SetAlpha to the value you really want to use.
class ScratchImage
{
public:
	ScratchImage();
	~ScratchImage();

	// We could support move semantics, but I don't think its needed right now
	ScratchImage(ScratchImage&&) = delete;
	ScratchImage& operator=(ScratchImage&&) = delete;

	// Copying doesn't make sense since there is only one scratch buffer.
	ScratchImage(const ScratchImage&) = delete;
	ScratchImage& operator=(const ScratchImage&) = delete;

	operator Image*() const;

	Graphics* StartDraw();
	void FinishDraw(Graphics* i_g);
	static void DeleteRenderTarget();

	void SetAlpha(const int i_val);
	// SetMinAlpha is weird and for *bad dudes* only
	void SetMinAlpha(const int i_val);
	static void SetTransitionAlpha(const int i_val);

private:

	class DeviceImage* m_image;
	std::unique_ptr<Graphics> m_graphics;
	int m_alpha;
	static bool m_targetOwned;
	static int m_transitionAlpha;
};

#endif
