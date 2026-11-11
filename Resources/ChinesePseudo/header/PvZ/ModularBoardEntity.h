//
//  BoardEntity.h
//  PlantsVersusZombies2
//
//  BoardEntity type that can own/attach other things to it.
//
//  Created by Joseph Sola on 5/2/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __MODULAR_BOARDENTITY_H__
#define __MODULAR_BOARDENTITY_H__

#include <string>

#include "AttachedEffectManager.h"
#include "BoardEntity.h"

class ModularBoardEntity : public BoardEntity
{
public:
	RT_CLASS_DEFINE_ABSTRACT(ModularBoardEntity, BoardEntity, RtClass);

protected:
	ModularBoardEntity() {}
	
public:
	virtual ~ModularBoardEntity();

	// Effects
	AttachedEffect& AddAttachedEffect(const char* iEffectName, const char* iPanAnimName, const char* iAnimName, const SexyVector3& iOffset, int iRenderLayerOffset = 1, bool iPlayOnce = false, bool iDisableDynamicScaling = false);
	void RemoveAttachedEffect(const char* i_entityName);
	void DetachAttachedEffect(const char* i_entityName);
	AttachedEffect* GetAttachedEffect(const std::string& i_entityName);
    AttachedEffectManager& GetAttachedEffectManager() { return m_attachedEffects; }

protected:
	void onUpdate() override;
	void onDestroy() override;
	
	void clearAttachedEffects();
	virtual void onEffectAttached(AttachedEffect& i_effect, bool i_disableDynamicScaling);
	virtual void updateOverlayEffects();

	AttachedEffectManager m_attachedEffects;
};

#endif
