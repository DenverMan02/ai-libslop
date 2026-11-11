/*
 * UIPlayerSurvey.h
 *
 *  Created on: 2021-6-18
 *      Author: admin
 */

#ifndef UIPLAYERSURVEY_H_
#define UIPLAYERSURVEY_H_

#include "UISingletonDialog.h"
#include "NetworkData.h"
#include "Image.h"

namespace Message
{
	void NotifySelectBoxSelected(int i_id);
	void NotifySelectBoxIsCorrect(bool correct);
}

class PlayerSurveySelectBox : public Widget, public Sexy::ButtonListener
{
public:
	PlayerSurveySelectBox();
    virtual ~PlayerSurveySelectBox();
public:
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            Update() override;

    virtual void	ButtonPress(int i_id) override;
    virtual void	ButtonDepress(int i_id) override;

    void SetSelected(bool i_selected) { m_selected = i_selected; }
    bool GetSelected() { return m_selected; }

    void SetId(int i_id) { m_id = i_id; }
    int GetId() { return m_id; }

    void InitView(SexyString i_text);

protected:
    void onNotifySelectBoxSelected(int i_id);

    int m_id;
    bool m_selected;
    PVZ2UIButton* m_selectButton;
    SexyString m_text;
};

struct PlayerSurveyStringData
{
	std::string QuestionStr;
	std::string AnswerStr;
};

class NetworkPlayerSurvey : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkPlayerSurvey, INetworkData, RtClass);

public:
	int QuestionNum;
	std::vector<PlayerSurveyStringData> QuestionStrList;
	std::vector<S2C_BonusInfo> RewardPreview;
};

class UIPlayerSurvey : public UISingletonDialog<UIPlayerSurvey>
{
public:
	UIPlayerSurvey();
	virtual ~UIPlayerSurvey();
public:
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIPlayerSurveyNew"; }
    virtual void                Draw(Sexy::Graphics* i_g) override;
	virtual void 				Update() override;

	void 						InitView();
	void 						CreateQuestion(int i_id);
	virtual void ButtonDepress(int theId) override;
	void 						SetQuestionNum(int i_num) { m_questionNum = i_num; }
	void						SetQuestionStrList(std::vector<PlayerSurveyStringData> strList);

private:
    void FillAnswer(int index, int answer);
    bool CheckValid(int index);
    void onNotifySelectBoxSelected(int i_id);
    int Inc_Index();
    int Dec_Index();
    bool IsAnswersValid();
    void InitBtns();
    void UpdateBtns();
    void CommitResult();
    void LogTGAResult();

private:
	std::vector<PlayerSurveySelectBox*> m_selects;
	SexyString          m_questionStr;
	int m_currentIndex;
    static std::vector<int> m_surveyAnswers;// fill final answers
    PVZ2UIButton* m_prevBtn;
    PVZ2UIButton* m_nextBtn;
    PVZ2UIButton* m_commitBtn;
    int m_questionNum;
    std::vector<PlayerSurveyStringData> m_questionStrList;
};


#endif /* UIPLAYERSURVEY_H_ */
