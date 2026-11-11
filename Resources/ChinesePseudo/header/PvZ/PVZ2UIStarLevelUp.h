/*
 * PVZ2UIStarLevelUp.h
 *
 *  Created on: May 29, 2014
 *      Author: lijie
 */

#ifndef PVZ2UISTARLEVELUP_H_
#define PVZ2UISTARLEVELUP_H_

#include "Precompile.h"

#include "Widget.h"
#include "RtObject.h"
#include "Core.h"
#include "Effect_PopAnim.h"
#include "PlantType.h"
#include "SexyAppFramework/PerfTimer.h"
//#include "PlantLevelUpIconWidget.h"

namespace Message
{
    void NoticeStorePlantGiftView();
}

class PlantLevelUpIconWidget;
struct IconData
{
	std::string name;
	int level;
	bool isProperty;
	bool isLevelIcon;
	IconData()
	{
		name = "";
		level = 1;
		isProperty = false;
		isLevelIcon = false;
	}
};

enum AnimState
{
	State_Init,
	State_Plant,
	State_Title,
	State_Text,
	State_Icon_First,
	State_Icon_Second,
	State_Icon_Third,
	State_Icon_Level_Up,
	State_Icon_Updating,
	State_Finish,
	State_Finish_Final,
};

class PVZ2UIStarLevelUp: public Sexy::Widget
{
public:
	enum AnimaType
	{
		E_LEVELUP,
		E_UNLOCK,
	};

public:
	PVZ2UIStarLevelUp(int iWidth, int iHeight);
    virtual ~PVZ2UIStarLevelUp();
    
    void InitUIView(AnimaType eType, std::string i_name, int i_level);
    virtual void DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g) override;
    virtual void Update() override;
    //PVZ2_CHINESE_END
    
    virtual void Draw(Graphics* i_g) override;
    
    bool IsFinished();
    
    void NotifyUpdateComplete(bool isFastFinish = false);
    
    void IncrementUpdateCount();
    
    int	 GetUpdateCount();
    
    void NotifyFadeInComplete(bool isFirst);
    
protected:
    void onAnimStopped(const std::string &i_animName);
    virtual	void TouchEnded(const Sexy::Touch& touch) override;

private:
	class Effect_PopAnim* m_levelupAnimEffect;
	bool m_bAnimFinished;
	PopAnimRig   *  m_pAnimRig;
	std::string		m_plantName;
	Sexy::Rect		m_pAnimRect;
	int				m_pLevel;
	AnimState		m_AnimState;

	PerfTimer		m_Timer;

	//std::vector<PlantLevelUpIconWidget*>	m_vecLevelUp;
	bool			m_addedIcon;
	PlantLevelUpIconWidget* 		m_iconFirst;
	PlantLevelUpIconWidget* 		m_iconSecond;
	PlantLevelUpIconWidget* 		m_iconThird;

	int				m_updateCount;

	bool			m_fadeComplete;

	AnimaType		m_Type;

	class Effect_PopAnim*   m_levelEffectBg;
	class Effect_PopAnim*   m_levelEffectFg;

	class Effect_PopAnim*   m_iconEffectBgFirst;
	class Effect_PopAnim*   m_iconEffectBgSecond;

	void CreateTitleEffect();
	void StartTimer();
	bool CheckCooldownAndReset(bool isRestart = true);
	void CreateAllIcons();
	void CreateLevelEffect();
	void CreateIconEffect(bool isFirst);

};

#endif /* PVZ2UISTARLEVELUP_H_ */
