//
//  AttachedEffectManager.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 5/6/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__AttachedEffectManager__
#define __PlantsVersusZombies2__AttachedEffectManager__

#include "Effect_PopAnim.h"
#include "Utils.h"

class AttachedGameObjectNode
{
public:
	virtual ~AttachedGameObjectNode() {}
	AttachedGameObjectNode()
	{}
	
	AttachedGameObjectNode(const std::string& i_name)
	: m_name(i_name)
	{}
	
	const std::string& GetName() const;
	
	bool IsValid() const;
	
	virtual void Update(float i_dt) {}
	void Destroy();
	virtual void Attach(BoardEntity* i_target, const SexyVector3& i_boardSpaceOffset, int i_renderOffset) {}
	virtual void Attach(RealObject* i_target, const SexyVector3& i_boardSpaceOffset, int i_renderOffset) {}
	void Set(RtWeakPtr<GameObject> i_object) { m_object = i_object; }

public:
	std::string m_name;
	RtWeakPtr<GameObject> m_object;
};

class AttachedBoardEntityNode : public AttachedGameObjectNode
{
public:
	AttachedBoardEntityNode()
	{}
	
	AttachedBoardEntityNode(const std::string& i_name)
	: AttachedGameObjectNode(i_name)
	{}
	
	void Update(float i_dt) override;
	void Attach(BoardEntity* i_target, const SexyVector3& i_boardSpaceOffset, int i_renderOffset) override;
	void Attach(RealObject* i_target, const SexyVector3& i_boardSpaceOffset, int i_renderOffset) override;
};

class AttachedEffect : public AttachedGameObjectNode
{
public:
	AttachedEffect()
		: m_updateMethod(Invalid)
        , m_staticScale(1.0f)
        , m_dynamicScale(1.0f)
        , m_disableDynamicScaling(false)
	{}
	
	AttachedEffect(const std::string& i_name)
		: AttachedGameObjectNode(i_name), m_updateMethod(Invalid)
        , m_staticScale(1.0f)
        , m_dynamicScale(1.0f)
        , m_disableDynamicScaling(false)
	{}
	
	void InitializeWithAnimation(PopAnim* i_anim);
	void InitializeWithAnimationAndClass(PopAnim* i_anim, RtClass* i_popAnimRigClass);
	void InitializeWithEffectPopAnim(Effect_PopAnim* i_effect);
	void PlayAnimLoopedWithDelay(const std::string& i_animName, float i_minDelay, float i_maxDelay);
	void PlayAnimLooped(const std::string& i_animName, const AnimSelectionMethod i_method = SELECT_RANDOM_INDEX);
	void PlayAnimLooped(const std::string &i_animName, const std::string &i_loopAnimName);
	void PlayAnimAndDestroy(const std::string& i_animName, AnimSelectionMethod i_select = SELECT_RANDOM_INDEX);
	void PlayAnimSequence(const AnimationSequence &i_animSeq);
	void PlayAnimSequenceAndDestroy(const AnimationSequence& i_animSeq);
	bool IsAnimActive(const std::string& i_animName);
	
	void Attach(BoardEntity* i_target, const SexyVector3& i_boardSpaceOffset, int i_renderOffset) override;
	void Attach(RealObject* i_target, const SexyVector3& i_boardSpaceOffset, int i_renderOffset) override;
	
	void Update(float i_dt) override;
	
	void Detach();

	Effect_PopAnim* GetEffect() const;
	
	void SetAttachedSyncClipRect(bool i_flag) { GetEffect()->SetAttachedSyncClipRect(i_flag); }
    
    void UpdateStaticScale(float i_scale);
    void UpdateDynamicScale(float i_scale);
	
public:
	enum UpdateMethod
	{
		Invalid,
		Looped,
		LoopedDelay,
		DestroyOnCompletion
	};

	UpdateMethod m_updateMethod;
	
	std::string m_loopAnimName;
	ValueRange m_loopDelayRange;
	float m_loopDelay = 0.0f;
	
    float m_staticScale;
    float m_dynamicScale;
    bool m_disableDynamicScaling;
};

//
// Rt-Serializable GameObject dictionary base pattern
//
// Commentary:
// The FindOrCreate is a little odd here in that it requires type knowledge in the container class.
// Consider refactoring this out in the future to make it more of a pure container.
//
class GameObjectDictionary : public RtObject
{
public:
	RT_CLASS_DEFINE_ABSTRACT(GameObjectDictionary, RtObject, RtClass);
	
	AttachedGameObjectNode& FindOrCreate(const std::string& i_name);
	//void Set(const std::string& i_name, AttachedGameObjectNode& i_node);
	bool Contains(const std::string& i_name) const;
	void Remove(const std::string& i_name);
	void Update(float i_dt);
	virtual void Clear() = 0;
	virtual int Count() = 0;
	
protected:
	virtual AttachedGameObjectNode& add(const std::string& i_name) = 0;
	virtual AttachedGameObjectNode& at(int i_index) = 0;
	virtual void remove(int i_index) = 0;
	virtual int indexOf(const std::string &i_name) const = 0;
	virtual void update(float i_dt) = 0;
	
public:

};

class AttachedEffectManager : public GameObjectDictionary
{
public:
	RT_CLASS_DEFINE(AttachedEffectManager, GameObjectDictionary, RtClass);
	
	int Count() override;
	void Clear() override;
    void UpdateDynamicScaleForAllEffects(float i_scale, const std::vector<std::string>& i_filters = {});

protected:
	AttachedGameObjectNode& add(const std::string& i_name) override;
	AttachedGameObjectNode& at(int i_index) override;
	void remove(int i_index) override;
	int indexOf(const std::string &i_name) const override;
	void update(float i_dt) override;

	std::vector<AttachedEffect> m_nodes;
};

class AttachedBoardEntityManager : public GameObjectDictionary
{
public:
	RT_CLASS_DEFINE(AttachedBoardEntityManager, GameObjectDictionary, RtClass);
	int Count() override;
	void Clear() override;
	
protected:
	AttachedGameObjectNode& add(const std::string& i_name) override;
	AttachedGameObjectNode& at(int i_index) override;
	void remove(int i_index) override;
	int indexOf(const std::string &i_name) const override;
	void update(float i_dt) override;

	std::vector<AttachedBoardEntityNode> m_nodes;
};

#endif /* defined(__PlantsVersusZombies2__AttachedEffectManager__) */
