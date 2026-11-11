// FilterEffect.h

#ifndef __FILTER_EFFECT_H__
#define __FILTER_EFFECT_H__

namespace Sexy
{
	class Image;
}

enum FilterEffect
{
	FILTER_EFFECT_NONE = -1,
	FILTER_EFFECT_WASHED_OUT,
	FILTER_EFFECT_LESS_WASHED_OUT,
	FILTER_EFFECT_WHITE,
	NUM_FILTER_EFFECTS,
};

void FilterEffectInitForApp();
void FilterEffectDisposeForApp();
Sexy::Image* FilterEffectGetImage(Sexy::Image *i_image, FilterEffect i_filterEffect);

#endif //__FILTER_EFFECT_H__
