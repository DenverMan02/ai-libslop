#ifndef __GeneralPlantChipsExchange_H__
#define __GeneralPlantChipsExchange_H__

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "UIListener.h"
#include "EffectAnim_UIAnim.h"
#include "Slider.h"
#include "SliderListener.h"

class GeneralPlantChipsExchangeConfig : public PropertySheetBase
{
    RT_CLASS_DEFINE(GeneralPlantChipsExchangeConfig, PropertySheetBase, RtClass);
public:
    std::string TypeName;
    std::vector<std::string> ExchangeList;
};

class GeneralPlantChipsExchangeCard : public Widget
{
public:
    GeneralPlantChipsExchangeCard();
    virtual ~GeneralPlantChipsExchangeCard();

    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    void InitView(int i_index, const std::string& i_typeName, class UIGeneralPlantChipsExchange* i_parent);
    void SelectCard(const std::string& i_typename);

protected:
    int m_index;
    int m_touchId;
    bool m_selected;
    std::string m_typeName;
    Sexy::DeviceImage* m_seedPacketImage;
    class UIGeneralPlantChipsExchange* m_parentDialog;

};

class ValueInuptEditor : public Sexy::Widget, public ButtonListener, public Sexy::EditListener
{
public:
    ValueInuptEditor();
    ~ValueInuptEditor();
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;
    virtual void EditWidgetText(int theId, const SexyString& theString) override;

    void Init();
    void SetOnConfirmText(std::function<void(const std::string&)> i_func) { m_confirm = i_func; }
    bool CheckNameFilter();

private:
    class EditWidget* m_editWidget;
    std::function<void(const std::string&)> m_confirm;
};


class UIGeneralPlantChipsExchange : public UISingletonDialog<UIGeneralPlantChipsExchange>, public Sexy::ScrollWidgetListener, public SliderListener
{
public:
    UIGeneralPlantChipsExchange();
    virtual ~UIGeneralPlantChipsExchange();
    
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIGeneralPlantChipsExchange"; }
    void ButtonDepress(int i_id) override;
    void ScrollTargetReached(ScrollWidget* scrollWidget) override {}
    void ScrollTargetInterrupted(ScrollWidget* scrollWidget) override {}
    void SliderVal(int theId, double theVal) override;

    void InitView(const std::string& i_material);
    void Refresh();
    void SelectPlant(const std::string& i_str);

private:
    void ExchangeConfirm(class UIMessageBox* box, int buttonID);
    void ExchangePlantChips();
    int m_exchangeValue;
    int m_maxValue;
    int m_materialId;
    std::string m_selectTypeName;
    Sexy::Slider* m_sliderWidget;
    std::vector<GeneralPlantChipsExchangeCard* > m_cardList;
};

namespace Message
{
    void ExchangeGeneralPlantChips(int i_materialId, int i_number);
}

#endif