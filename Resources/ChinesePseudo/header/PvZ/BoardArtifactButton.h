/*
 * BoardArtifactButton.h
 *
 *  Created on: 2021-6-8
 *      Author: zhousen
 */

#ifndef BOARDARTIFACTBUTTON_H_
#define BOARDARTIFACTBUTTON_H_

#include "UIEasyButtonWidget.h"
#include "Singleton.h"
#include "GameSubSystem.h"
#include "AnimationMgr.h"
#include "StandaloneEffect.h"
#include "Effect_PopAnim.h"

namespace Message
{
    void ArtifactIdle();
    void ArtifactTrigger();
    void ArtifactPrepare();
    void ArtifactCooldown();
}

//
// BoardArtifactButton
//
class BoardArtifactButton : public UIEasyButtonWidget
{
public:
    RT_CLASS_DEFINE(BoardArtifactButton, UIEasyButtonWidget, RtClass);

    BoardArtifactButton();
    virtual ~BoardArtifactButton();

    virtual void Draw(Graphics* i_g) override;
    Rect							CalcPlusButtonRect();

    virtual void OnClick();
    virtual void InitParam(int id);

	virtual bool					OnTouch(const Sexy::Touch& i_touch) override;

protected:
    void updateButtonStates(const int i_mouseX, const int i_mouseY, const bool i_isPressed) override;
    virtual void					onCursorDestroyed(class BaseCursor* i_cursor);
    virtual void					registerForEvents() override;
    virtual void					unregisterForEvents() override;

protected:
    int _artifactID;
    bool is_prepare=false;
    ImagePtr _normalArtifactImg;
    ImagePtr _pressedArtifactImg;
};

//
// AnimateArtifactMower
//
enum ArtifactAnimState
{
    Artifact_Invalid = -1,
    Artifact_Idle,// can trigger
    Artifact_Prepare,
    Artifact_Trigger,// trigger
    Artifact_Cooldown,// cooldown
    Artifact_Max,
};

class AnimateArtifactMower : public AnimationController
{
public:
    RT_CLASS_DEFINE(AnimateArtifactMower, AnimationController, RtClass);
    AnimateArtifactMower();
    ~AnimateArtifactMower();

    static AnimateArtifactMower* Create() {
        return GameObject::Create<AnimateArtifactMower>(PVZDB::TABLE_GAMEOBJECTS);
    }

	void InnerDraw(Graphics* i_g) override;
    void Update(pvztime_t i_time) override;
    void onDestroy() override;

    virtual void PlayAnimation(ArtifactAnimState state);
    virtual void Init(std::string artifactName);

    void OnArtifactIdle();
    void OnArtifactTrigger();
    void OnArtifactPrepare();
    void OnArtifactCooldown();
    void TriggerEndCallback(StandaloneEffect* i_effect);
    void onMowerCreated(class LawnMower* i_mower);
    void onMowerReset(class LawnMower* i_mower);

    RtWeakPtr<Effect_PopAnim> GetEffect() { return _effect; }
    SexyVector3 GetEffectPosition() { return _position; }

protected:
    SexyVector3 _position;// effect position
    RtWeakPtr<Effect_PopAnim> _effect;// effect object 
};

//
// BoardArtifactManager
//
class BoardArtifactManager : public GameSubSystem
{
public:
	RT_CLASS_DEFINE(BoardArtifactManager, GameSubSystem, RtClass);

	BoardArtifactManager();
	~BoardArtifactManager();

	void AddArtifact(const std::string name, bool visible = true);
	void AddArtifact(const int nameID, bool visible = true);
    void InitialArtifactIcon();
    void InitialArtifactMower(AnimationMgrWkPtr animMgr);
    void DestroyArtifact();

    BoardArtifactButton* GetBoardArtifact();
    AnimateArtifactMower* GetAnimateArtifactMower();

private:
    RtWeakPtr<BoardArtifactButton> _boardButton;
    RtWeakPtr<AnimateArtifactMower> _animArtifactMower;
};

class BoardArtifactButtonWithBeehive : public BoardArtifactButton
{
public:
	RT_CLASS_DEFINE(BoardArtifactButtonWithBeehive, BoardArtifactButton, RtClass);

	BoardArtifactButtonWithBeehive() {}
	~BoardArtifactButtonWithBeehive() {}

	void Draw(Graphics* i_g) override;
};

#endif /* BOARDARTIFACTBUTTON_H_ */
