/*
 * LevelEditorVaseBreaker.h
 *
 *  Created on: 2022-4-28
 *      Author: zhousen
 */

#ifndef LEVELEDITORVASEBREAKER_H_
#define LEVELEDITORVASEBREAKER_H_

#include "UISingletonDialog.h"
#include "ButtonListener.h"
#include "SliderListener.h"
#include "LevelEditorDefine.h"
#include "LevelEditorUtil.h"
#include "CustomLevelConfig.h"

namespace Message
{
	void SetVaseNumber(int number);
	void UpdateCurrentTotalNumber();
    void AddCurrentTotalNumber(int num);
    void DecCurrentTotalNumber(int num);
    void SetSelectPlantOrZombie(bool isPlant);
};

//////////////////////////////////////
/// LevelEditorVaseBreakerSeedBank
//////////////////////////////////////
class LevelEditorVaseBreakerSeedBank : public Widget, public ButtonListener
{
public:
	LevelEditorVaseBreakerSeedBank();
	virtual ~LevelEditorVaseBreakerSeedBank();

    virtual void Init();
    virtual void Reload();

    int GetTotalNumber();
    void AutoSet(int totalVaseNum);

//    virtual bool CheckValidPlant(std::string name);
//    virtual bool CheckValidZombie(std::string name);
//    virtual void AddPlant(std::string name);
//    virtual void RemovePlant(std::string name);
//    virtual void AddZombie(std::string name);
//    virtual void RemoveZombie(std::string name);

protected:
//    std::vector<std::string> m_existPlantsNames;
    std::vector<class LevelEditorVaseBreakerSeedPacket*> m_seedPacketList;
};

//////////////////////////////////////
/// LevelEditorVaseBreakerSeedPacket
//////////////////////////////////////
class LevelEditorVaseBreakerSeedPacket : public LevelEditorSeedPacket
{
public:
	LevelEditorVaseBreakerSeedPacket(LevelEditorVaseBreakerSeedBank* i_bank);
	virtual ~LevelEditorVaseBreakerSeedPacket();

    void Draw(Sexy::Graphics* i_g) override;
    void TouchEnded(const Sexy::Touch& i_touch) override;
    void Reload() override;
    void onChangeCardInfo() override;

    void onClearCardInfo();
    int GetCurrentNum();

protected:
    void AddVaseBreakerDetail(int index, std::string typeName, int num);

protected:
    LevelEditorVaseBreakerSeedBank* m_seedBank;
    int m_number;
    SexyString m_numberText;
};

/////////////////////////////////////////
/// LevelEditorVaseBreakerSetting
/////////////////////////////////////////
class LevelEditorVaseBreakerSetting : public LevelEditorSliderWidget
{
public:
	LevelEditorVaseBreakerSetting();
	virtual ~LevelEditorVaseBreakerSetting();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void Init() override;
	virtual void SliderVal(int theId, double theVal) override;

    void SetFunc(std::function<void(int, std::string)> func) {m_func = func;}
    void SetVaseBreakerData(std::string plantName, bool isPlant, int number);
    void SetSelectPlant(bool isPlant);

protected:
    std::string m_plantTypeName;
    SexyString m_levelupTitle;
    std::function<void(int, std::string)> m_func;
    class LevelEditorVaseBreakerLevelUpSeedPacket* m_levelUpPlantBtn;
    class LevelEditorVaseBreakerSelect* m_plantSelect;
    class LevelEditorVaseBreakerSelect* m_zombieSelect;
    bool m_isSelectPlant;
};

//////////////////////////////////////////////
/// LevelEditorVaseBreakerSelect
//////////////////////////////////////////////
class LevelEditorVaseBreakerSelect : public Widget
{
public:
	LevelEditorVaseBreakerSelect(bool isPlant);
    virtual ~LevelEditorVaseBreakerSelect();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    virtual void SetSelect(bool select) { m_isSelect = select; }
    virtual bool IsSelected() { return m_isSelect; }

protected:
    int m_touchId;
    bool m_isSelect;
    bool m_isPlant;
    SexyString m_descText;
};


//////////////////////////////////////////////
/// LevelEditorVaseWidget
//////////////////////////////////////////////
class LevelEditorVaseWidget : public Widget
{
public:
	LevelEditorVaseWidget();

    virtual void Draw(Sexy::Graphics* i_g) override;
};


//////////////////////////////////////////////
/// LevelEditorVaseBreakerLevelUpSeedPacket
//////////////////////////////////////////////
class LevelEditorVaseBreakerLevelUpSeedPacket : public LevelEditorSeedPacket
{
public:
	LevelEditorVaseBreakerLevelUpSeedPacket();
	virtual ~LevelEditorVaseBreakerLevelUpSeedPacket();

    virtual void Draw(Sexy::Graphics* i_g) override;
    void TouchEnded(const Sexy::Touch& i_touch) override;

    std::string GetCardTypeName() const { return m_cardInfo.TypeName; }
    void SetIsPlant(bool isPlant) { m_isPlant = isPlant; }

protected:
    bool m_isPlant;
};

//////////////////////////////////////////////
/// LevelEditorVaseBreakerZombieSelectList
//////////////////////////////////////////////
class LevelEditorVaseBreakerZombieSelectList : public LevelEditorZombieSelectList
{
public:
	LevelEditorVaseBreakerZombieSelectList();

	void SetFunc(std::function<void(const LevelEditorCardInfo&)> i_cardfunc) { m_func = i_cardfunc; }

protected:
    virtual void RefreshZombiesByPage() override;

protected:
    std::function<void(const LevelEditorCardInfo&)> m_func;

};

//////////////////////////////////////////////
/// LevelEditorVaseBreakerZombieSelect
//////////////////////////////////////////////
class LevelEditorVaseBreakerZombieSelect : public LevelEditorZombieDraggable
{
public:
	LevelEditorVaseBreakerZombieSelect();

    virtual void TouchMoved(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

	void SetFunc(std::function<void(const LevelEditorCardInfo&)> i_cardfunc) { m_func = i_cardfunc; }

protected:
    std::function<void(const LevelEditorCardInfo&)> m_func;
};

/////////////////////////
/// Vase Breaker
/////////////////////////
class LevelEditorVaseBreaker : public UISingletonDialog<LevelEditorVaseBreaker>, public SliderListener
{
public:
	LevelEditorVaseBreaker();
    virtual ~LevelEditorVaseBreaker();
    virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "LevelEditorVaseBreaker"; }
    virtual void							ButtonDepress(int i_id) override;

    void Init();
    void Reload();

private:
    void InitBoardModule();
    void InitSetNumText(int current, int max);
    void InitSelectNumFirstHint(bool show);
    void ChangeBoardStageArt(const std::string& i_stage);
    bool CheckAllSelectionEmpty();
    bool CheckShowAutoTips();
    void ShowAutoSettingTips();
    void AutoSet(UIMessageBox* box, int id);
    void InitVase();
    void SetVaseNumber(int num);
    void AddCurrentTotalNumber(int num);
    void DecCurrentTotalNumber(int num);
	void UpdateCurrentTotalNumber();

private:
    LevelEditorVaseBreakerSeedBank* m_seedBank;
    Widget* m_boardMainWidget;
    UIWidgetText* m_numProgressText;
    UIWidgetText* m_selectNumFirstHintText;
    std::vector<LevelEditorVaseWidget*> m_vaseList;
    int m_vaseNumber;// max vase number.
    int m_currentSetNumber;// current plant or zombie total num
};

class LevelEditorVaseBreakerSettingNumber : public UISingletonDialog<LevelEditorVaseBreakerSettingNumber>
{
public:
	LevelEditorVaseBreakerSettingNumber();
    virtual ~LevelEditorVaseBreakerSettingNumber();
    virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UICustomLevelVaseBreakerSettingNumber"; }
    virtual void							ButtonDepress(int i_id) override;

    void InitNumber(int num);

private:

private:
    UIWidgetText* m_numberText;
    int m_vaseNumber;
};

#endif /* LEVELEDITORVASEBREAKER_H_ */
