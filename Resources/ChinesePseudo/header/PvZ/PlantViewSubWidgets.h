#ifndef PlantViewSubWidgets
#define PlantViewSubWidgets

#include "Widget.h"
#include "drivers/misc/iphoneos/ScrollWidget.h"
#include "PlantDisplayBoard.h"
#include "UISingletonDialog.h"
#include "UIListener.h"
#include "MagentoService.h"
#include "PlantAccessoryMgr.h"
#include "PlantAccessoryUI.h"
#include "PlantAccessoryPropertySheet.h"

class UINewPlantView_SkillDisplay : public UISingletonDialog<UINewPlantView_SkillDisplay>
{
public:
    UINewPlantView_SkillDisplay();
	virtual ~UINewPlantView_SkillDisplay();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UINewPlantView_SkillDisplay"; }
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							Update() override;
	virtual void							ButtonDepress(int i_id) override;

    void InitView(const std::string& i_plantName);

protected:
    void OnDisplaySelectButton(int i_selectLevel);
private:
    PlantTypePtr m_plantType;
    class PlantDisplayBoard* m_plantDisplay;
    int m_selectLevel;
};

class UINewPlantView_SkillTab : public Widget, public Sexy::ButtonListener
{
public:
    virtual void Draw(Sexy::Graphics* i_g) override;
	virtual void ButtonDepress(int i_id) override;

    void InitView(const std::string& i_plantName);

private:
    void initLv5SkillSwitch(PlayerInfo* i_playerInfo, const std::string& i_plantName, int i_currentLevel);

    PlantTypePtr m_plantType;
    std::vector<std::tuple<Sexy::Image*, Sexy::Image*, Sexy::Image*, SexyString, bool>> m_levelData;    
    PVZ2UIButton* m_switchBtn{nullptr};
};


class AvatarPackageItem : public Widget
{
    friend class UINewPlantView_AvatarPackage;
public:
    virtual void Draw(Sexy::Graphics* i_g) override;

    virtual void TouchBegan( const Sexy::Touch& touch ) override;
    virtual void TouchEnded( const Sexy::Touch& touch ) override;

    void InitView(int i_avatarId);
    void Refresh();
    void SelectPackageItem(bool i_flag);

private:
    Sexy::TouchID m_touch;
    bool m_selected = false;

    int m_avatarId;
    bool m_isNewAvatar;
    bool m_avatarUnlocked;
    bool m_equiped;
    SexyString m_avatarName;
    Sexy::Image* m_avatarImage;
    int m_currentNumber;
    int m_exchangeNum;
};

class UINewPlantView_AvatarPackage : public UISingletonDialog<UINewPlantView_AvatarPackage>
{
public:
    UINewPlantView_AvatarPackage();
	virtual ~UINewPlantView_AvatarPackage();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UINewPlantView_AvatarPackage"; }
	virtual void							Draw(Sexy::Graphics* i_g) override;
    virtual void                            DrawAll(Sexy::ModalFlags* i_flags, Graphics* i_g);
	virtual void							Update() override;
	virtual void							ButtonDepress(int i_id) override;

    void InitView(const std::string& i_plantName);

    void FocusAvatar(int i_avatarId);

private:
    void UnlockAvatar();
    void OnUnlockAvatar(bool i_success, int i_avatarId);
    void EquipAvatar();
    void UnEquipAvatar();

    int m_currentAvatar;
    PlantTypePtr m_plantType;
    class PlantDisplayBoard* m_plantDisplay;
    std::vector<AvatarPackageItem*> m_itemList;
};

class UINewPlantView_LevelUp : public UISingletonDialog<UINewPlantView_LevelUp>
{
public:
    UINewPlantView_LevelUp();
	virtual ~UINewPlantView_LevelUp();
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UINewPlantView_LevelUp"; }
	virtual void							Draw(Sexy::Graphics* i_g) override;
	virtual void							Update() override;
	virtual void							ButtonDepress(int i_id) override;

    void InitView(const std::string& i_plantName);
    void Refresh();

private:
    void ConfirmLevelUp(class UIMessageBox* box, int buttonID);
    void ConfirmLevelUpBook(class UIMessageBox* box, int buttonID);
    void onPlantLevelUpSuccess();
    void onBookLevelUpSuccess(bool i_flag);
    void onCoinStoreClose();

    MagentoProductPropsPtr m_props;
    PlantTypePtr m_plantType;
    int m_currentLevel;
};


class UINewPlantView_Classify : public UISingletonDialog<UINewPlantView_Classify>
{
public:
	virtual bool	                        OnCreate() override;
    virtual std::string                     GetLayoutName() override { return "UINewPlantView_Classify"; }
	virtual void							ButtonDepress(int i_id) override;
};

class UINewPlantView_PlantDetails : public UISingletonDialog<UINewPlantView_PlantDetails>, public Sexy::ScrollWidgetListener
{
public:
	virtual bool	                        OnCreate() override;
    virtual void                            ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void                            ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    virtual std::string                     GetLayoutName() override { return "UINewPlantView_PlantDetails"; }
	virtual void							ButtonDepress(int i_id) override;

    void InitView(const std::string& i_plantName);
};

class AccessoryPackageItem : public Sexy::Widget
{
    friend class UINewPlantView_AccessoryPackage;
    enum AccessoryBindState : int
    {
        ABS_NotBind = 0,
        ABS_Self,
        ABS_Other,
    };
public:
    virtual void Draw(Sexy::Graphics* i_g);
    virtual void TouchBegan( const Sexy::Touch& touch );
    virtual void TouchEnded( const Sexy::Touch& touch );

    void InitView(int i_id, const PlantAccessoryInfo& i_accessory);
    void Refresh();

private:
    int m_Id;
    PlantAccessoryPropertySheetPtr m_props;
    PlantAccessoryInfo m_accessoryInfo;
    AccessoryUIInfo m_accessoryUIInfo;

    Sexy::Image* m_frame = nullptr;
    Sexy::Image* m_image = nullptr;
    Sexy::Image* m_level = nullptr;

private:
    Sexy::TouchID m_touch;

    bool m_selected = false;
    bool m_disableBind = false;
    AccessoryBindState m_bindState = AccessoryBindState::ABS_NotBind;
};


class AccessoryPiecesPackageItem : public Sexy::Widget
{
    friend class UINewPlantView_AccessoryPackage;
public:
    virtual void Draw(Sexy::Graphics* i_g);
    virtual void TouchBegan( const Sexy::Touch& touch );
    virtual void TouchEnded( const Sexy::Touch& touch );

    void InitView(MagentoProductPropsPtr i_pieceProps);
    void Refresh();

private:
    Sexy::TouchID m_touch;
    MagentoProductPropsPtr m_pieceProps;
    AccessoryUIInfo m_accessoryUIInfo;

    Sexy::Image* m_frame = nullptr;
    Sexy::Image* m_image = nullptr;

    int m_ownNumber = 0;
    bool m_isFull = false;
    bool m_selected = false;
};

class AccessorySalePackageItem : public Sexy::Widget
{
    friend class UINewPlantView_AccessoryPackage;
public:
    virtual void Draw(Sexy::Graphics* i_g);
    virtual void TouchBegan( const Sexy::Touch& touch );
    virtual void TouchEnded( const Sexy::Touch& touch );

    void InitView(int i_id, const PlantAccessoryInfo& i_saleInfo);
    void Refresh();

private:
    int m_Id;
    PlantAccessoryPropertySheetPtr m_props;
    PlantAccessoryInfo m_saleInfo;
    AccessoryUIInfo m_accessoryUIInfo;

    Sexy::Image* m_frame = nullptr;
    Sexy::Image* m_image = nullptr;
    Sexy::Image* m_level = nullptr;

private:
    Sexy::TouchID m_touch;

    bool m_selected = false;
    bool m_canSale = false;
};

class AccessorySteadyPackageItem : public Sexy::Widget
{
    friend class UINewPlantView_AccessoryPackage;
public:
    virtual void Draw(Sexy::Graphics* i_g);
    virtual void TouchBegan( const Sexy::Touch& touch );
    virtual void TouchEnded( const Sexy::Touch& touch );

    void InitView(int i_id, PlantAccessoryPropertySheetPtr i_props, PlantAccessoryInfo i_steadyInfo);
    void Refresh();

private:
    int m_Id;
    PlantAccessoryPropertySheetPtr m_props;
    PlantAccessoryInfo m_steadyInfo;
    AccessoryUIInfo m_accessoryUIInfo;

    Sexy::Image* m_frame = nullptr;
    Sexy::Image* m_image = nullptr;
    Sexy::Image* m_level = nullptr;

private:
    Sexy::TouchID m_touch;

    bool m_selected = false;
    bool m_canSale = false;
};


class UINewPlantView_AccessoryPackage : public UISingletonDialog<UINewPlantView_AccessoryPackage>, public Sexy::ScrollWidgetListener, public UI::TabControlListener
{
public:
    UINewPlantView_AccessoryPackage();
    virtual ~UINewPlantView_AccessoryPackage();

	virtual bool	                        OnCreate() override;
    virtual void                            ScrollTargetReached( ScrollWidget* scrollWidget ) override {}
    virtual void                            ScrollTargetInterrupted( ScrollWidget* scrollWidget ) override {}
    virtual std::string                     GetLayoutName() override { return "UINewPlantView_AccessoryPackage"; }
    virtual void                            TabSelectionChanged(int tabID) override;
	virtual void							ButtonDepress(int i_id) override;

    void InitView(const std::string& i_plantName);
    void RefreshOwnNumber();

    void showSuperAccessoryDescription();
    void closeSuperAccessoryDescription();
private:
    void InitAccessory();
    void OnActionComplete();
    void RefreshAccessory();
    void ConfirmSwitchAccessory(UIMessageBox* box, int buttonID);

    void InitExchange();
    void OnExchangeComplete(bool i_flag);
    void RefreshPieces();
    void ConfirmExchangePieces(UIMessageBox* box, int buttonID);

    void InitSale();
    void OnSoldTargetAccessory(int32 i_type);
    void OnResetSuccess(int32 i_type);
    void ConfirmSaleAccessory(UIMessageBox* box, int buttonID);
    void ConfirmResetAccessory(UIMessageBox* box, int buttonID);

    void InitSteady();
    void OnSteadySuccess(int32 i_type);
    void RefreshSteady();
    void ConfirmSteady();

public:
    void SelectAccessoryItem(AccessoryPackageItem* i_packageItem);
    void SelectPieceItem(AccessoryPiecesPackageItem* i_packageItem);
    void SelectSaleItem(AccessorySalePackageItem* i_packageItem);
    void SelectSteadyItem(AccessorySteadyPackageItem* i_packageItem);

private:
    void OnCloseDialog();
private:
    AccessoryPackageItem* m_accessorySelect = nullptr;
    std::vector<AccessoryPackageItem*> m_accessoryList;
    AccessoryPiecesPackageItem* m_pieceSelect = nullptr;
    std::vector<AccessoryPiecesPackageItem*> m_pieceList;
    AccessorySalePackageItem* m_saleSelect = nullptr;
    std::vector<AccessorySalePackageItem*> m_saleList;
    AccessorySteadyPackageItem* m_steadySelect = nullptr;
    std::vector<AccessorySteadyPackageItem*> m_steadyList;
    
    class ActivityDescriptionUI* m_descriptionUI;
public:
    std::string m_plantName;
};

namespace Message
{
    void NewPlantView_PlantLevelUp(int i_plantID);
    void NewPlantView_SwitchAvatar(int i_plantID);
    void NewPlantView_SwitchAccessory(int i_plantID);
    void NewPlantView_UnlockAvatar(int i_plantID);
};

#endif
