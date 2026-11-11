#ifndef UIPlantCultivate_H
#define UIPlantCultivate_H

#include "UISingletonDialog.h"
#include "PVZ2UIButton.h"
#include "NetworkData.h"
#include "UIListener.h"
#include "EffectAnim_UIAnim.h"
#include "RepeatUIComponent.h"

struct PlantCultivateSelectInfo
{
    int PlantId;
    int Status;
};

struct PlantCultivateTaskInfo
{
    int TaskId;
    int Status;
};


class PlantCultivateData : public INetworkData
{
public:
	RT_CLASS_DEFINE(PlantCultivateData, INetworkData, RtClass);

    std::vector<PlantCultivateSelectInfo> PlantSelectList;
    int CurrentIntegral;
    int MaxIntegral;
    int Obtained;
    int GemNum;
    std::vector<PlantCultivateTaskInfo> TaskList;
    std::string CultivateEndTime;
    int BundleLimit;

    std::vector<S2C_BonusInfo> RewardList;
};


class PlantCultivateSelectItem : public Widget
{
public:
    PlantCultivateSelectItem();
    ~PlantCultivateSelectItem();

    virtual void TouchBegan(const Sexy::Touch& i_touch) override;
    virtual void TouchEnded(const Sexy::Touch& i_touch) override;

    void InitView(class UIPlantCultivateSelect* i_parent, int i_plantId);

    int GetPlantId();
    bool IsSelected();
    void Select(bool i_flag);

private:
    int m_touchId;
    int m_plantId;
    bool m_selected;
    class UIPlantCultivateSelect* m_parent;
    class UIWidgetImage* m_selectImage;
};

class UIPlantCultivateSelect : public UISingletonDialog<UIPlantCultivateSelect>, public Sexy::ScrollWidgetListener
{
public:
    bool OnCreate() override;
    std::string GetLayoutName() override { return "UIPlantCultivateSelect"; }
    void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();
    void SelectItem(int i_plantId);

private:
    void RequestSelectPlant(int i_plantId);
    void ConfirmSelectPlant(class UIMessageBox* box, int buttonID);

    std::vector<PlantCultivateSelectItem*> m_itemList;
};



class PlantCultivateTaskWidget : public TemplateTaskWidget
{
public:
    RT_CLASS_DEFINE(PlantCultivateTaskWidget, Sexy::Widget, RtClass);

    virtual void InitTask(GeneralTask* i_task) override;
    virtual void DrawTaskBackground(Sexy::Graphics* i_g) override;

protected:
    virtual void RequestReward() override;
};


class UIPlantCultivate : public UISingletonDialog<UIPlantCultivate>, public Sexy::ScrollWidgetListener
{
public:
    UIPlantCultivate();
    ~UIPlantCultivate();

    bool OnCreate() override;
    void Update() override;
    std::string GetLayoutName() override { return "UIPlantCultivate"; }
    void ButtonDepress(int i_id) override;
    void ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    void ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}

    void InitView();

    void RefreshTab1();
    void RefreshTab3();

    void onBuyPlantCultivate(int i_index);

    void showDescriptionWidget();
    void closeDescriptionWidget();  

private:
    void InitTab1();
    void InitTab2();
    void InitTab3();

    void GetCultivateReward();
    void GemExchangeCultivate(class UIMessageBox* box, int buttonID);

    class ActivityDescriptionUI* m_descriptionUI = nullptr;
};


class PlantCultivateManager : public LazySingleton<PlantCultivateManager>
{
public:
    PlantCultivateManager();
    ~PlantCultivateManager();

    void ShowDialog();
    void onNotifyRefreshActivityList(bool i_success, const std::set<int>& changeList);

    bool HasSelected();
    bool HasObtained();
    bool IsOutTime();
    time_t GetOutTime();
    int GetSelectPlantID();

    void AddTaskIntegral(int i_num);

    PlantCultivateData m_cacheData;
private:
    bool m_thisRequest;
};

#define gPlantCultivateManager (PlantCultivateManager::GetInstancePtr())
 

#endif