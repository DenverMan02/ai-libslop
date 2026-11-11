//
//  EffectObject.h
//  PlantsVersusZombies2
//
//  Created by Jason Emery on 10/16/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EffectObject__
#define __PlantsVersusZombies2__EffectObject__

#include "Effect_PopAnim.h"
#include "EffectObjectType.h"
#include "PropertySheetBase.h"
#include "PVZTypes.h"

typedef RtWeakPtr<class EffectObject> EffectObjectPtr;

class EffectObjectPropertySheet : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(EffectObjectPropertySheet, PropertySheetBase, RtClass);
	
	EffectObjectPropertySheet()
	{
	}

	std::string							PopAnim;
	SexyVector2							PopAnimRenderOffset;
	std::string							SpawnSoundID;
	std::string							SpawnAnimation;
};


class EffectObject : public Effect_PopAnim
{
public:
	RT_CLASS_DEFINE(EffectObject, Effect_PopAnim, RtClass);
	
	/// Initialization
	void					EffectObjectInitialize(EffectObjectTypePtr i_Type, int i_gridX, int i_gridY);
	
	/// Accessors
	inline EffectObjectTypePtr		GetType() const;
	inline EffectObjectPropsPtr		GetProps() const;
	template <class T>
	inline const T*				GetProps() const;
	
	Point CalcGridPosition() const;
	
protected:
	
	// Interface
	virtual void			onEffectObjectInitialize(EffectObjectTypePtr i_Type, int i_gridX, int i_gridY)
	{}
	
	void onUpdate() override;
	void onDraw(class Graphics* i_g) override;

private:
	EffectObjectTypePtr		m_type;
	
	void					initializeAnimRig();

};


inline EffectObjectTypePtr EffectObject::GetType() const
{
	return m_type;
}
inline EffectObjectPropsPtr EffectObject::GetProps() const
{
	DBG_ASSERT(m_type.IsValid());
	return m_type->Properties;
}
template<class T> inline const T* EffectObject::GetProps() const
{
	EffectObjectPropsPtr props = GetProps();
	const T* typedProps = props->Cast<const T>();
	return typedProps;
}

#endif /* defined(__PlantsVersusZombies2__EffectObject__) */
