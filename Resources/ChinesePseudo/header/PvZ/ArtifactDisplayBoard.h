#ifndef _ArtifactDisplayBoard_H
#define _ArtifactDisplayBoard_H

#include "ObjectTypeDescriptor.h"
#include "PVZTypes.h"
#include "ArtifactMgr.h"
#include "Board.h"

class ArtifactMiniBoard : public Board
{
public:
    ArtifactMiniBoard();
    ~ArtifactMiniBoard();
    
    void InitBoard();
    void CloseBoard();
    void ResetBoard();
    bool CanSaveGameState() override;
    
    Zombie* SpawnZombie(ZombieTypePtr i_zombieType, int i_spawnedFromWave, SpawnZombieParams* pParams = nullptr) override;
    
    void Pause(bool i_pauseGame) override;
    void Update() override;
    void Draw(Graphics* i_g) override;
    bool IsMiniBoard() override;
};

class ArtifactDisplayLevelButton : public Widget, public ButtonListener
{
public:
    ArtifactDisplayLevelButton(int i_level);
    virtual ~ArtifactDisplayLevelButton();
    
    void SelectLevel(int i_level);
    
    virtual void Draw(Graphics* i_g);
    virtual void DrawAll(ModalFlags* theFlags, Graphics* g);
    virtual void ButtonDepress(int i_id);
public:
    bool m_bSelected;
    int m_level;
    Image* m_image;
};


class ArtifactDisplayBoard : public Widget
{
public:
    ArtifactDisplayBoard();
    ~ArtifactDisplayBoard();
    
    void SetArtifactId(int i_artifactId);

    void DisplayNexyAction();
    void SetArtifactLevel(int i_level);
    void SetDisplayLevel(int i_level);
    virtual void Update();
    virtual void Draw(Graphics* g);
    virtual void DrawAll(ModalFlags* theFlags, Graphics* g);

    void SetDisplayLevelButtonPosOffset(Sexy::SexyVector2 stp);
    void SetSkillNamePosOffset(Sexy::SexyVector2 stp) { m_SkillNamePosOffset = stp; }
   
    void HideDisplayItems(bool bImmediately = false);
    void EnableAutoNext() { m_enableAutoNext = true; }
    void DisableAutoNext() { m_enableAutoNext = false; }

    void SetAvatarIndex(int i_index) { m_avatarIndex = i_index; }
    
public:
    bool m_hideDisplayItems;
    bool m_enableAutoNext;

    int m_avatarIndex;
    
    int m_curActionIndex;
    int m_startActionIndex;
    int m_endActionIndex;
    float m_ActionTime;

    
    class ArtifactMiniBoard* m_board;
    class Sexy::RtWeakPtr<Artifact> m_artifactPtr;
    pvztime_t m_nextTrigger;

    ArtifactPropertiesPtr m_artifactProp;
    Image *m_displayImage;
    
    SexyString m_skillName;
    int m_selectLevel;
    
    class Plant* m_plant;

    
    Sexy::SexyVector2 m_SkillNamePosOffset;
    Sexy::SexyVector2 m_DisplayLevelButtonPosOffset;
    
    std::vector<ArtifactDisplayLevelButton*> m_vecDisplayLevelButton;
    std::vector<ArtifactDisplayActionInfo> m_displayActions;
};

namespace Message
{
    void ArtifactDisplayLevelSelect(int i_level);
    void ArtifactDisplaySelectButton(int i_level);
    void ArtifactDisplayBoardUpdate();
    void ArtifactClearBoard();
}


#endif
