/*
 * UIBagItemBox.h
 *
 *  Created on: 2021-2-6
 *      Author: zhousen
 */

#ifndef UIBAGITEMBOX_H_
#define UIBAGITEMBOX_H_

#include "UISingletonDialog.h"
#include "StringHelper.h"
#include "LuaEngine.h"
#include "PVZ2UIButton.h"

class UIBagItemBox : public UISingletonDialog<UIBagItemBox> {
public:
    typedef Sexy::Delegate2<UIBagItemBox*, int> MessageCallbackEvent;

    enum 
    {
        Item_Invalid = -1,
        Item_Plant_Piece,
        Item_Avatar_Piece,
        Item_Accessory_Piece,
        Item_Material,
        Item_TrialCard,
        Item_Max,
    };

    enum
    {
        Btn_Close = 0,
        Btn_Left = 1,
        Btn_Right = 2,
        Btn_Middle = 3,
    };

    enum ShowType {
        Type_Invalid = 0,
        Type_ShowLeft = 1 << 0,
        Type_ShowMiddle = 1 << 1,
        Type_ShowRight = 1 << 2,
        Type_Max = 0xffff,
    };

public:
    UIBagItemBox();
    virtual ~UIBagItemBox();

    virtual bool OnCreate() override;
    virtual std::string GetLayoutName() override { return "uibagitembox"; }
    virtual void OnClose() override;
    virtual void Draw(Sexy::Graphics* i_g) override;
    virtual void DrawAll(ModalFlags* theFlags, Graphics* i_g) override;
    virtual void ButtonDepress(int i_id) override;

    void InitView();
    void InitView(int type, int itemID, int count);
    void SetCallBack(MessageCallbackEvent callback);
    void SetCallBack(ShowType tyoe, MessageCallbackEvent callback);
    void SetShowType(int i_type); 
    void SetButtonDialogStates(ShowType type, const PVZ2UIImage& i_normalImage, const PVZ2UIImage& i_downImage);
    void SetButtonTitle(ShowType type, const std::string title);
    void SetButtonDialog(ShowType type, const PVZ2UIImage& i_normalImage, const PVZ2UIImage& i_downImage,const std::string title);
    void OnCollectionStateSwitch(int i_collectionId, int i_state);

    bool Is_Open = true;
    PVZ2UIButton* m_Button = nullptr;
    int _itemID;// item id
protected:
    SexyString GetItemBoxTitle(int itemID);
    void InitButtons(int type);
    void InitTitleAndDesc(int type, int itemID);
    void InitRects(int type);
    SexyString GetPlantGotWay(std::string plantName);
    SexyString GetAvatarSpecification(int avatarPieceId);
    SexyString GetAvatarGotWay(int avatarPieceId);
    SexyString GetAccessoryGotWay(std::string accessoryName);

protected:
    MessageCallbackEvent _btnCallbackLeft;
    MessageCallbackEvent _btnCallbackMiddle;
    MessageCallbackEvent _btnCallbackRight;
    
    MessageCallbackEvent _callbackEvent;

    int _uiType;// plant / avatar / accessory / material
    int _itemCount;// item count

    SexyString _titleStr;// title str
    SexyString _itemCountStr;// item count str

    SexyString _itemDescTitle1;// upper desc title
    SexyString _itemDescTitle2;// lower desc title

    SexyString _itemSpecification;// item specification
    SexyString _itemUseDesc;// item use
    SexyString _itemRareL;// item Rare
    SexyString _itemRareR;// item Rare
    SexyString _itemGotWay;// item got way

    Rect _itemCountRect;
    Rect _itemTitle1Rect;
    Rect _itemTitle2Rect;
    Rect _itemSpecificationRect;
    Rect _itemUseRect;
    Rect _itemRareRectL;
    Rect _itemRareRectR;
    Rect _itemGotWayRect;
};


#endif /* UIBAGITEMBOX_H_ */
