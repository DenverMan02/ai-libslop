//
//  ComponentVisualStretcher.h
//  PlantsVersusZombies2
//
//  Created by Blankenship, Bradley on 5/5/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ComponentVisualStretcher__
#define __PlantsVersusZombies2__ComponentVisualStretcher__

#include "ComponentBase.h"
#include "PropertySheetBase.h"

class Effect_PopAnim;

#pragma mark - ComponentVisualStretcherProps

class ComponentVisualStretcherProps : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(ComponentVisualStretcherProps, PropertySheetBase, RtClass);
	
	ComponentVisualStretcherProps()
	{
		StretchSpeed = 1.0f;
		
		BaseAnimName = "";
		StretchAnimName = "";
		TipAnimName = "";
		
		InitialBaseAnimAnimation = "";
		InitialStretchAnimAnimation = "";
		InitialTipAnimAnimation = "";
		
		BaseAnimOffset = {0.0f, 0.0f};
		StretchAnimOffset = {0.0f, 0.0f};
		TipAnimOffset = {0.0f, 0.0f};
	}
	
	float		StretchSpeed;
	
	std::string BaseAnimName;
	std::string StretchAnimName;
	std::string TipAnimName;
	
	std::string InitialBaseAnimAnimation;
	std::string InitialStretchAnimAnimation;
	std::string InitialTipAnimAnimation;
	
	SexyVector2 BaseAnimOffset;
	SexyVector2 StretchAnimOffset;
	SexyVector2 TipAnimOffset;
};

#pragma mark - ComponentVisualStretcher

class ComponentVisualStretcher : public ComponentBase
{
public:
	RT_CLASS_DEFINE(ComponentVisualStretcher, ComponentBase, RtClass);
	
	virtual ~ComponentVisualStretcher();
	
	void	Initialize(const ComponentVisualStretcherProps& i_props, int i_renderLayer);
	
	SexyVector2 GetDelta()  const;
	SexyVector2 GetOrigin() const;
	SexyVector2 GetTarget() const;
	
	float	CurrentLength();
	bool	HasReachedTarget();
	bool	IsStretching();
	
	void	StretchFromTo(SexyVector2 i_origin, SexyVector2 i_target, float i_startingLength = 0.0f);
	void	RetractToFrom(SexyVector2 i_origin, SexyVector2 i_target, float i_startingLength);
	void	Retarget(SexyVector2 i_newTarget);
	
	void	Clear();
	
protected:
	void	onUpdate() override;
	void	onDraw(Sexy::Graphics* i_g) override;
	
private:
	RtWeakPtr<GameObject> loadPopanimEffect(const std::string& i_name,
											const std::string& i_initalAnimation,
											int i_renderLayer) const;
	
	float calculateDistanceToTarget() const;

	void drawFromToScreenSpace(Graphics*				i_graphics,
							   const Sexy::SexyVector2&	i_origin,
							   const Sexy::SexyVector2&	i_direction,
							   const Sexy::SexyVector2&	i_originArtOffset,
							   const Sexy::SexyVector2&	i_scale,
							   float					i_angle,
							   Effect_PopAnim*			i_anim);
	
	SexyTransform2D createTransformWithPivot(SexyVector2 i_translation, float i_rotation, SexyVector2 i_scale, SexyVector2 i_pivot);
	
	ComponentVisualStretcherProps	m_props;
	
	SexyVector2						m_originPosition;
	SexyVector2						m_targetPosition;
	
	RtWeakPtr<Effect_PopAnim>		m_baseAnim;			// Valid to be null
	RtWeakPtr<Effect_PopAnim>		m_stretchedAnim;	// Must not be null!
	RtWeakPtr<Effect_PopAnim>		m_tipAnim;			// Valid to be null
	
	SexyVector2						m_baseAnimOffset;
	SexyVector2						m_stretchAnimOffset;
	SexyVector2						m_tipAnimOffset;
	
	float							m_stretchLength;
	float							m_stretchDelta;
	float							m_stretchDirection;
	bool							m_isStretching;
};

#endif /* defined(__PlantsVersusZombies2__ComponentVisualStretcher__) */
