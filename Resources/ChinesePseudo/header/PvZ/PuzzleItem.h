/*
 * PuzzleItem.h
 *
 *  Created on: 2019-3-26
 *      Author: zhousen
 */

#ifndef PUZZLEITEM_H_
#define PUZZLEITEM_H_

#include "SeedPacketUtils.h"
#include "UISingletonDialog.h"

enum GachaStatus
{
	GachaStatus_NotLogin,
	GachaStatus_Enabled,
	GachaStatus_Disabled
};

//  platform gift serialize object
class PlatformGiftSerializeData : public RtObject
{
public:
    RT_CLASS_DEFINE(PlatformGiftSerializeData, RtObject, RtClass);

    int _canGetGift;
    std::vector<GiftItem> _giftList;
};

// many param adjust the rotary speed , used in rotate panel
struct PuzzleRotateConfig {
    // the speed accl, calc per frame distance we move, 
    // steps = sum distance / step distance means how many steps we move,
    // the steps add 1, we play StepNext() in PuzzleRotatePanel, 

    int _round_number;// how many rounds will stop in exact item

    int _speedup_step_number;// how many steps are in speed up status
    int _speeddown_step_number;// how many steps are in speed down status

    float _step_distance;// the distance between items
    float _speed_acc;// the speed accel
    float _speed_max;// the max speed

    PuzzleRotateConfig() {
        _round_number = 2;
        _speedup_step_number = 3;
        _speeddown_step_number = 3;
        _step_distance = 100.0f;
        _speed_acc = 1.0f;
        _speed_max = 30.f;
    }

    PuzzleRotateConfig(const PuzzleRotateConfig& config){
        _round_number = config._round_number;
        _speedup_step_number = config._speedup_step_number;
        _speeddown_step_number = config._speeddown_step_number;
        _step_distance = config._step_distance;
        _speed_acc = config._speed_acc;
        _speed_max = config._speed_max;
    }
};

// we use this base type data in puzzle class
// change serialzie network data to this class , and initilaize our puzzle class
class CoreItemDataBase {
public:
    CoreItemDataBase();
    CoreItemDataBase(int id, int count);
    virtual ~CoreItemDataBase();

    virtual bool IsSame(CoreItemDataBase* data) {
        if (data == nullptr) return false;

        return _id == data->GetID() && _count == data->GetCount();
    }

    int GetID() const {
        return _id;
    }

    int GetCount() const {
        return _count;
    }

protected:
    int _id;// item id
    int _count;// how many items
};

// a puzzle item base class
class PuzzleItemBase {
public:
    PuzzleItemBase();
    virtual ~PuzzleItemBase();

    virtual void SetItemData(CoreItemDataBase* data);
    CoreItemDataBase* GetItemData() const;

protected:
    CoreItemDataBase* _data;
};

// this data struct is used in a lottery panel
class PuzzleRotateItemBase : public PuzzleItemBase, public PVZ2UIButton, public ButtonListener{
public:
    PuzzleRotateItemBase(int id);
    virtual ~PuzzleRotateItemBase();
};

// this class will not be render now, only be a data struct class
// because we now use uirewardframe class
class PuzzleRotateButton : public PuzzleRotateItemBase
{
public:
    PuzzleRotateButton(int id);
    virtual ~PuzzleRotateButton();

    virtual void Draw(Graphics* g) override;
    virtual void Resize(const Rect& rect) override;
    virtual void ButtonPress(int buttonId) override;
    virtual void ButtonDepress(int buttonId) override;
    virtual void ButtonMouseLeave(int buttonId) override;

    virtual void SetItemData(CoreItemDataBase* data) override;

protected:
    virtual void AnalyzeItemInfo(CoreItemDataBase* data);
    virtual Rect CreateFrameRect();
    virtual Rect CreateIconRect();
    virtual Rect CreateCountRect();

    void InitPieceRenderData(SexyString name);
    void DeleteTip();

protected:
    Rect _frameRect;
    Rect _iconRect;

    Image* _frameImg;
    Image* _iconImg;

    SexyString _itemName;
    SexyString _description;

    int _count;// count of this item

    Rect _tipRect;// tips rect
    PuzzleTip* _tip;// tempolary tip ptr

    // for pieces rendering,
    PacketRenderData _renderData;
    Rect _renderBGRect;
    Rect _renderPieceRect;
    bool _isPiece;

    // for count draw
    Rect _countRect;
};

// rotate panel
class PuzzleRotatePanel : public Widget 
{
public:
    // rotate state machine
    enum {
        Rotate_Idle = 0,
        Rotate_Begin,
        Rotate_SpeedUp,
        Rotate_SpeedMax,
        Rotate_SpeedDown,
        Rotate_End,
        Rotate_None,
    };

    PuzzleRotatePanel(PuzzleRotateConfig config);
    virtual ~PuzzleRotatePanel();

    virtual void Draw(Graphics* g) override;
    virtual void DrawAll(ModalFlags* i_flags, Graphics* i_g) override;

    virtual void Update() override;
    virtual void Resize(const Rect& rect) override;

    virtual void UpdateStepNext();
    virtual void BeginRotate();
    virtual void UpdateRotate();
    virtual void EndRotate();

    bool IsRotating() const;
    bool IsFinishRotating() const;

    virtual void InitButtonList(std::vector<CoreItemDataBase*> dataList); 
    virtual Rect CreateItemRect(int row, int column, int gapx, int gapy, int index);
    class UIRewardFrame* CreateUIRewardFrame(int objectId, int num, bool hasFrame);

    // this should be used after InitButtonlist()
    void SetTargetIndex(int target);
    // not use
    void SetEffectWidget(Widget* effect);

    int GetCurrentIndex() const;
    PuzzleRotateButton* GetCurrentButton() const;
    class UIRewardFrame* GetCurrentUIRewardFrame() const;
    CoreItemDataBase* GetCurrentButtonData() const;

    // calc final target steps
    int GetFinalTargetSteps(CoreItemDataBase* data);

    // callback func when we click pop dialog's close button
    void OnCloseGiftDialog();
protected:
    // for rotating panel
    int GetDistanceIndexStep(float distance, float stepDistance, int listCount);
    int CalcTargetIndex(std::vector<PuzzleRotateButton*> list, CoreItemDataBase* data);
    float AddSpeed(PuzzleRotateConfig config);
    float DeclineSpeed(PuzzleRotateConfig config);
    void ShowItemDialog(CoreItemDataBase* data);

protected:
    std::vector<PuzzleRotateButton*> _buttonList;// the bonus list , it is now used only be a data list, not draw in screen
    std::vector<class UIRewardFrame*> _rewardList;// the real UI list

    int _currentIndex;// current bonus index, -1 mean not begin
    int _targetIndex;// which is the target bonus index
    int _listCount;// the buttonList count

    Widget* _effectWidget;// not used, the hint effect which is the current bonus

    int _rotate_state;// rotate state machine
    PuzzleRotateConfig _config;// rotate config
    float _distance;// the distance we move
    float _speed;// the speed we got
    int _stepCount;// the steps count
};

// get gift button
class PuzzleGetGiftButton : public PVZ2UIButton {
public:
    PuzzleGetGiftButton(int id, ButtonListener* listener, GachaStatus i_stauts, int i_count);
    virtual ~PuzzleGetGiftButton();

    virtual void Update() override;
    virtual void Resize(const Rect& rect) override;
    virtual void Draw(Graphics* g) override;

protected:
    void InitButton();
    void SetGachaCount(int count);
    void UpdateButtonStatus();
    void InitRect();

private:
    Rect _freeRect;
    Image* _freeImg;

    Rect _gachaRect;
    int _gachaCount;// gacha times you got
    SexyString _freeText;// the free text
    SexyString _gachaCountText;
    GachaStatus _status;
};

//  puzzle platform gift panel
class PuzzlePlatformGiftPanel : public UISingletonDialog<PuzzlePlatformGiftPanel> 
{
public:
    enum {
        BTN_CLOSE = 0, // close btn
        BTN_GET_BONUS = 100, // get btn
    };

    PuzzlePlatformGiftPanel();
    virtual ~PuzzlePlatformGiftPanel();

    virtual bool OnCreate() override;
    virtual void Resize(const Rect& rect) override;
    virtual std::string GetLayoutName() override { return "PlanformGift"; }
    virtual void Draw(Graphics* g) override;
    virtual void DrawAll(ModalFlags* flags, Graphics* g) override;
    virtual void Update() override;
    virtual void ButtonDepress(int id) override;

    void InitRotateList(std::vector<GiftItem> list);
    void InitView(GachaStatus i_status, int i_count, const std::string& i_url);

    void SetLeftDays(int days);

    // callback func that we click get bonus btn, server will give us a certain bonus
    void NotifyGetBonus(bool success, const S2C_PlatformGiftData* pData);
private:
    PuzzleRotatePanel* _rotatePanel;// this is a rotating panel
    PuzzleGetGiftButton* _getButton;// get the bonus button
    
    UIWidgetText* _countdownText; // count down text
    PVZ2UIButton* _exitButton;// which is to quit, not use

    UIWidgetBackground* _confirm;// this will not use, only to hide a panel we make in PlatformGift.json

    std::vector<CoreItemDataBase*> _itemDataList;// this gift list data
    int _leftDays;// how many days will this activity left
    GachaStatus _status;
    int _count;
    std::string _linkUrl;
};


#endif /* PUZZLEITEM_H_ */
