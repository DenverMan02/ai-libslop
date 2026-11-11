/*
 * RichmanGuessGameUI.h
 *
 *  Created on: 2019-12-24
 *      Author: zhousen
 */

#ifndef RICHMANGUESSGAMEUI_H_
#define RICHMANGUESSGAMEUI_H_

#include "Precompile.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "NetworkMsgProcess.h"
#include "Effect_PopAnim.h"
#include "RichmanDefine.h"
#include "GuessRatio.h"

// guess game cost btn id
enum {
    GuessGameCost_NotEnough = 1000,
    GuessGameCost_2_Btn,
    GuessGameCost_20_Btn,
    GuessGameScissor_Btn = 2000,
    GuessGameRock_Btn,
    GuessGamePaper_Btn,
    GuessGameClose_Btn,
    WorldLevel_Go_Btn,
    WorldLevel_Escape_Btn,
};

class GuessGameCostButton : public PVZ2UIButton
{
public:
    GuessGameCostButton(int i_id, Sexy::ButtonListener* i_listener, const SexyString& i_buttonName = _S(""), const Sexy::Color& i_fontColor = Sexy::Color::White);

    void Draw(Sexy::Graphics* i_g) override;
    void SetCount(int count);

protected:
    Image* _coinImg;
    SexyString _coinsStr;
    int _count;
};

/// 
/// guess game entry
///
class GuessGameEntryPanel : public Widget, Sexy::ButtonListener
{
public:
    GuessGameEntryPanel();
    virtual ~GuessGameEntryPanel();

    virtual void InitView();
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    
    void UpdateUI(PlayerInfo* info);// update panel

protected:
    SexyString _titleStr;
    SexyString _descriptionStr;// enough coins or not enough coins
    GuessGameCostButton* _cost2Btn;
    GuessGameCostButton* _cost20Btn;
    PVZ2UIButton* _exitBtn;
};

///
/// world level entry
///
class WorldLevelEntryPanel : public Widget, Sexy::ButtonListener
{
public:
    WorldLevelEntryPanel();

    virtual void InitView();
    virtual void Draw(Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

protected:
    SexyString _titleStr;
    SexyString _descriptionStr;
    PVZ2UIButton* _goBtn;
    PVZ2UIButton* _escapeBtn;
};

// GuessGameCard_State
enum {
    CardState_Close = 0,// close
    CardState_Click,// click button
    CardState_Turning,// turning
    CardState_Result,// after turning
};

// show 
class GuessGameCard : public Widget
{
public:
    GuessGameCard();
    virtual ~GuessGameCard();

    void Draw(Sexy::Graphics* i_g) override;
    void Update() override;

    void SetSide(bool isLeft);
    void SetState(int state);
    void SetCardType(GuessGameType type);
    void StartTurning();

    bool IsShowResult();
    void CreateTurningEffect(GuessGameType type);

protected:
    std::string GetCardTypeImageStr(GuessGameType type);
    SexyString GetCardTypeDescriptionStr(GuessGameType type);
    void OnEffectStop(const std::string& str);

protected:
    int _state;
    Image* _card;
    SexyString _cardStr;
    GuessGameType _cardType;
    Effect_PopAnim* _turnEffectPtr;// card turn effect
    std::string _animName;// card turn anim name
    bool _drawCard;// when in turning , it's false
    bool _isOnLeft;// if is right, the img should be mirrored
};

// guess game main panel
class GuessGamePanel : public UISingletonDialog<GuessGamePanel>
{
public:
    GuessGamePanel();
    virtual ~GuessGamePanel();

    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "GuessGameUI"; }
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void Update() override;

    void ShowResult();

protected:
    GuessResult CalcResult(float win, float lose);
    GuessGameType GetResultType(GuessGameType type, GuessResult result);
    void ClickGuessBtn(GuessGameType type);

    SexyString GetCardNameStr(GuessGameType type);
    Sexy::Image* GetResultImage(GuessResult result);
    SexyString GetResultStr(GuessResult result);

protected:
    PVZ2UIButton* _paperBtn;// paper -> rock -> scissor -> paper
    PVZ2UIButton* _scissorBtn;
    PVZ2UIButton* _rockBtn;
    PVZ2UIButton* _closeBtn;

    UIWidgetText* _playerCardText;
    UIWidgetText* _cpuCardText;
    UIWidgetText* _resultText;

    Widget* _darkImg;
    Widget* _titleImg;
    Widget* _vsImg;
    UIWidgetImage* _resultImg;

    GuessGameCard* _playerCard;// ui card
    GuessGameCard* _cpuCard;
    GuessResult _result;// game result

    bool _requestProtocol;// this should reques once
};


#endif /* RICHMANGUESSGAMEUI_H_ */
