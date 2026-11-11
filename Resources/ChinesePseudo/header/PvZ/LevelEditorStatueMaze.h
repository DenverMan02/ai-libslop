#ifndef LevelEditorStatueMaze_H
#define LevelEditorStatueMaze_H

#include "UISingletonDialog.h"
#include "ButtonListener.h"
#include "SliderListener.h"
#include "LevelEditorDefine.h"
#include "Board.h"


struct StatueDirection
{
	float m_time;
	bool m_direction;
	StatueDirection(bool i_direction,float i_time = PVZ_T()){
		this->m_direction = i_direction;
		this->m_time = i_time;
	}
	bool operator <(const StatueDirection & a) const
	{
		return this->m_time < a.m_time;
	}

	StatueDirection& operator=(StatueDirection & value)
	{
		this->m_time = value.m_time;
		this->m_direction = value.m_direction;
		return *this;
	}
};
struct StatueMazeData
{
	float m_time;
	int m_matrixSize;
	int m_targetNum;
	float m_displayTime;
	float m_bonusLife;
	float m_rotateTime;
	float m_waitTime;
	std::vector<StatueDirection*> m_direction ;
	StatueMazeData(int i_matrixSize,int i_targetNum,float i_displayTime,float i_bonusLife,float i_rotateTime,float i_waitTime,float i_time = PVZ_T()){
		m_matrixSize = i_matrixSize;
		m_targetNum = i_targetNum;
		m_displayTime = i_displayTime;
		m_bonusLife = i_bonusLife;
		m_rotateTime = i_rotateTime;
		m_waitTime = i_waitTime;
		m_time = i_time;
	}
	bool operator <(const StatueMazeData & a) const
	{
		return m_time<a.m_time;
	}
};


/*---------------------关卡编辑器------------------------------*/

class LevelEditorStatueMaze : public UISingletonDialog<LevelEditorStatueMaze>, public SliderListener
{
public:
	LevelEditorStatueMaze();
    virtual ~LevelEditorStatueMaze();
    virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "LevelEditorStatueMaze"; }
    virtual void							Draw(Sexy::Graphics* i_g) override;
    virtual void							ButtonDepress(int i_id) override;
    virtual void                            Update() override;
    std::vector<StatueMazeData*> 				all_StatueMazeData;
    int m_focus;

private:
    LevelEditorSeedBankType m_seedType;

public:
    void Init();
    void Reload();


    void ChangeBoardStage(const std::string& i_stage);
    void ChangeBoardStageArt(const std::string& i_stage);
    void ShowStatue(int num);
    std::vector<PVZ2UIButton*> Statue_Group;

private:
    void InitCommon();
    void InitBoardModule();
    void InitZombieModule();

    void SwitchToBoardModule();
    void SwitchToZombieMoudle();
private:
    class Widget* m_seedBank;
    class PVZ2UIButton* m_boardStageSelect;
    class PVZ2UIButton* m_moduleSwitchBtn;

    Widget* m_boardMainWidget;
    Widget* m_zombieMainWidget;
};

#define gLevelEditorStatueMaze LevelEditorStatueMaze::GetSingletonPtr()

class LevelEditorStatueMazeLoadGroupWidget : public Widget
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
    void Init();
};


#endif
