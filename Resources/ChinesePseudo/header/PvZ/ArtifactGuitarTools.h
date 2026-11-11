//
// 2023.07.04 created by lfy
//

#ifndef __ARTIFACTGUITARTOOLS_H__
#define __ARTIFACTGUITARTOOLS_H__

#include "GameSubSystem.h"
#include "Graphics.h"
#include "Effect_PopAnim.h"
#include "TimeMgr.h"
#include "Projectile.h"
#include "GridItemAnimation.h"
#include "BoardArtifactButton.h"


class Effect_MusicalNote : public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(Effect_MusicalNote, Effect_PopAnim, RtClass);    
    void registerForEvents() override;  
    void unregisterForEvents() override;
    void init(const Point i_position, pvztime_t i_successed, pvztime_t i_perfected);
    void setIsEnd() { m_isEnd = true; }
protected:
    // void onPostLoad() override;
    void onDraw(Graphics* i_g) override;
    void onAnimStopped(const std::string& i_animLabel) override;
    void onUpdate() override;
private:
    
    enum NoteState
    {
        Invalid = 0,
        Idle,
        Failure,
        Succeed,
        Perfected,
    };

    bool handleTouch(const Sexy::Touch& i_touch);
    void cancelTouch();
    void playBoomEffect();
    void perfectedBoom();

    pvztime_t m_hitTime;
    NoteState m_state;    
    Point m_position;
    pvztime_t m_successed;
    pvztime_t m_perfected;
    bool m_isEnd;
};

class Effect_MusicalBoom : public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(Effect_MusicalBoom, Effect_PopAnim, RtClass);
protected:
    void onUpdate() override;
};

class ProjectileGuitarSound : public Projectile
{
public:
    RT_CLASS_DEFINE(ProjectileGuitarSound, Projectile, RtClass);
    ProjectileGuitarSound();
    void SetSuccessCount(int i_cnt);
protected:
    void damageEntity(class BoardEntity* i_entity) override;
    void onUpdate(pvztime_t i_dt) override;
    void getCollisionEntities(std::vector<BoardEntity*> &o_entities,const Rect& i_projectileRect) const override;
private:
    int m_positionX;
    int m_cnt;
    std::vector<BoardEntity*> m_hitTargets;
};

class ProjectileGuitarMusicalNote : public Projectile
{
public:
    RT_CLASS_DEFINE(ProjectileGuitarMusicalNote, Projectile, RtClass);    
protected:
    void damageEntity(class BoardEntity* i_entity);
    // void onUpdate(pvztime_t i_dt);
    bool handleImpact(BoardEntity* i_impactedEntity = NULL);
private:
    
};

class GuitarGridAudio : public GridItemAnimation
{
public:
    RT_CLASS_DEFINE(GuitarGridAudio, GridItemAnimation, RtClass);
    void SetSuccessCount(int i_cnt);
    void SetDamage(float i_damage) { m_damage = i_damage; }
protected:
    void onUpdate() override;
    void attackZombies();
    void onAnimStoppedCallback(const std::string& i_animCommand);
    void onGridItemInitialize() override;
private:    
    pvztime_t m_currentTime;
    int m_cnt;
    int m_currentCnt;
    float m_damage = 0.0f;
};

// class ArtifactGuitarSubSystem : public GameSubSystem
// {
// public:
// 	RT_CLASS_DEFINE(ArtifactGuitarSubSystem, GameSubSystem, RtClass);

//     ArtifactGuitarSubSystem();
//     ~ArtifactGuitarSubSystem();

// 	virtual void Update() override;
// 	// virtual void AddToRenderQueue(class RenderQueue* i_queue) override;

//     void Start(pvztime_t i_successedTime, pvztime_t i_perfectedTime);
//     void End();
//     pvztime_t GetSuccessedTime() { return m_successed; }
//     pvztime_t GetPerfectedTime() { return m_perfected; }
//     void AddSuccessedCnt() { ++m_counter; }
//     int GetSuccessedCnt() { return m_counter; }
// protected:
//     // virtual void onDestroy() override;
// private:
//     void setState(ArtifactGuitarSubSystemState i_state);
//     void addMusicalNotes();    
//     // void onDrawEffectUIOnBoard(Sexy::Graphics *i_g);
//     // void onDrawSelectionOnBoard(Sexy::Graphics *i_g);

//     // void ResetScale();
//     // float GetScale();

//     int m_counter;
//     pvztime_t m_timer;
//     pvztime_t m_nextStart;
//     ArtifactGuitarSubSystemState m_state;        
//     int m_musicalNoteIdx;
//     pvztime_t m_successed;
//     pvztime_t m_perfected;
// }; 

class AnimateArtifactMowerGuitar : public AnimateArtifactMower
{
public:
    RT_CLASS_DEFINE(AnimateArtifactMowerGuitar, AnimateArtifactMower, RtClass);

    static AnimateArtifactMowerGuitar* Create() {
        return GameObject::Create<AnimateArtifactMowerGuitar>(PVZDB::TABLE_GAMEOBJECTS);
    }    
    void Init(std::string artifactName);
    void PlayAnimation(ArtifactAnimState state) override;
    void PlayIdle(StandaloneEffect* i_effect) { PlayAnimation(Artifact_Idle); }
    void Update(pvztime_t i_time) override;
};

class ArtifactMowerGuitar_Effect : public Effect_PopAnim
{
public:
    RT_CLASS_DEFINE(ArtifactMowerGuitar_Effect, Effect_PopAnim, RtClass);
protected:    
    void onUpdate() override;
    void OnAnimCommand(const std::string &i_animCommand, const std::string &i_animCommandParam) override;
    void onAnimStopped(const std::string& i_animLabel);
};

#endif
