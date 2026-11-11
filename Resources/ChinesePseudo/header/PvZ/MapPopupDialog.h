//
//  MapPopupDialog.h
//  PlantsVersusZombies2
//
//  Created by Michael Fromwiller on 12/10/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_MapPopupDialog_h
#define PlantsVersusZombies2_MapPopupDialog_h

#include "RtDelegate.h"
#include "PlayerInfo.h"
#include "Renderable.h"

typedef Delegate0 ButtonPressDelegate;


class MapPopupDialog : public Renderable, ButtonListener
{
public:

	enum AnchorType
	{
		PD_ANCHOR_BEST_FIT,
		PD_ANCHOR_SIDES_ONLY,
        PD_ANCHOR_FORCE_TOP,
		PD_ANCHOR_CENTER,
	};

	enum DialogType
	{
		PD_DIALOG_KEYGATE_PURCHASE,
		PD_DIALOG_KEYGATE_CLEARED,
		PD_DIALOG_STARGATE_PURCHASE,
		PD_DIALOG_STARGATE_PREVIEW,
		PD_DIALOG_REWARD_INFO,
        PD_DIALOG_OTHER,
        PD_DIALOG_DESC,
	};
	
	MapPopupDialog();
	virtual ~MapPopupDialog();
	
	// Public Interface (Inheritable)
	virtual void				Draw(Sexy::Graphics* i_g);
	virtual void				OnMouseUp(const int i_mouseX, const int i_mouseY);
	virtual void				OnMouseDown(const int i_mouseX, const int i_mouseY);
	virtual bool				IsMouseOver(const int i_mouseX, const int i_mouseY);
	
	// Public Interface (Core)
	void						PopIn();
	void						PopOut();
	void						SetAnchorLocation(const Point i_location);
	void						SetDialogType(const DialogType i_dialogType);
	void						SetFreeLabel(const SexyString& i_freeLabel);
	void						SetPurchaseData(const int i_itemCount, const int i_itemCountRequired, const ImagePtr i_itemImage, PopAnim* i_itemPopAnim, const SexyString& i_yourCountLabel, const SexyString& i_requiredCountLabel);
	void						SetBypassPurchaseData(const SexyString& i_buttonBypassLabel, const SexyString& i_bypassLabel, ButtonPressDelegate i_onConfirmButtonPressed);
	void						SetRewardInfoData(RtWeakPtr<const class ObjectTypeDescriptor> i_plantTypePtr,MapEventItem* pEvtItem);
	void						SetDescriptionListData(const std::vector<SexyString>& i_descriptionList, const std::vector<bool>& i_descriptionListCompleted);
	void						SetKeygateInfo(const SexyString& i_challenegeRewardDesc, const SexyString& i_challengeName, const SexyString& i_challenegeDesc);

	void						SetConfirmButtonPressed(const SexyString& i_buttonLabel, ButtonPressDelegate i_onConfirmButtonPressed, const std::string& i_audioPress = "", const std::string& i_audioRelease = "");
	void						SetPreviewButtonPressed(const SexyString& i_buttonLabel, ButtonPressDelegate i_onPreviewButtonPressed);
	void						SetCancelButtonPressed(const SexyString& i_buttonLabel, ButtonPressDelegate i_onCancelButtonPressed);

	inline void					SetWidth(const int i_width);
	inline const int&			GetWidth() const;
	
	inline void					SetHeight(const int i_height);
	inline const int&			GetHeight() const;

	inline void					SetPositionBounds(const Rect i_boundingRect);
	inline const Rect&			GetPositionBounds() const;
	
	inline Rect					GetConfirmButtonBounds() const;
	
	inline void					SetAnchorType(const AnchorType i_anchorType);
	inline const AnchorType		GetAnchorType() const;
	
	inline void					SetHeader(const SexyString& i_headerText);
	inline const SexyString&	GetHeader() const;
	
	inline void					SetDescription(const SexyString& i_descText);
	inline const SexyString&	GetDescription() const;
	
	inline void					SetChallengeName(const SexyString& i_headerText);
    
	inline void					SetInfoObjectType(RtWeakPtr<const class ObjectTypeDescriptor> i_objectType);
	inline RtWeakPtr<const class ObjectTypeDescriptor> GetInfoObjectType() const;
	
    inline bool					IsVisible();
	
	ButtonWidget*				m_okayButton;
    
protected:

	// Private Interface (Core)
	virtual void				calculateLocation();
	void						drawContentsKeygatePurchase(Sexy::Graphics* i_g);
	void						drawContentsKeygateCleared(Sexy::Graphics* i_g);
	void						drawContentsStargatePurchase(Sexy::Graphics* i_g);
	void						drawContentsStargatePreview(Sexy::Graphics* i_g);
	void						drawContentsRewardInfo(Sexy::Graphics* i_g);
    void                        drawContentsDesc(Sexy::Graphics* i_g);

	AnchorType					m_anchorType;
	Point						m_anchorLocation;
	Point						m_location;
	int							m_width;
	int							m_height;
	Rect						m_boundingRect;
	Point						m_caretPosition;
	float						m_caretAngle;
	bool						m_visible;
	DialogType					m_dialogType;
	int							m_itemCount;
	int							m_itemCountRequired;
	ImagePtr					m_itemImage;
	PopAnim*					m_itemPopAnim;
	SexyString					m_challenegeName;
	SexyString					m_challenegeRewardDesc;
	SexyString					m_challengeDesc;
	bool						m_hasBypass;
	SexyString					m_header;
	SexyString					m_description;
    //PVZ2_CHINESE_BEGIN
    SexyString                  m_descriptionEx;
    Color                       m_descriptionExColor;

    SexyString					m_freeLabel;
    //PVZ2_CHINESE_END
	SexyString					m_costLabel;
	SexyString					m_balanceLabel;
	SexyString					m_bypassLabel;
	ButtonWidget*				m_closeButton;
	
	std::string					m_okayAudioPress;
	std::string					m_okayAudioRelease;
	ButtonWidget*				m_previewButton;
	std::vector<SexyString>		m_descriptionList;
	std::vector<bool>			m_descriptionListCompleted;
	DangerRoomInfo				m_dangerRoomInfo;
	int							m_dangerRoomCheckpointLevel;
	
	bool						m_okayButtonPressed;
	
	ButtonPressDelegate			m_onConfirmButtonPressed;
	ButtonPressDelegate			m_onPreviewButtonPressed;
	ButtonPressDelegate			m_onCancelButtonPressed;
	
	RtWeakPtr<const class ObjectTypeDescriptor> m_infoObjectType;
};

inline void MapPopupDialog::SetWidth(const int i_width)
{
	m_width = i_width;
	calculateLocation();
}

inline const int& MapPopupDialog::GetWidth() const
{
	return m_width;
}

inline void MapPopupDialog::SetHeight(const int i_height)
{
	m_height = i_height;
	calculateLocation();
}

inline const int& MapPopupDialog::GetHeight() const
{
	return m_height;
}

inline void MapPopupDialog::SetPositionBounds(const Rect i_boundingRect)
{
	m_boundingRect = i_boundingRect;
	calculateLocation();
}

inline const Rect& MapPopupDialog::GetPositionBounds() const
{
	return m_boundingRect;
}

inline Rect MapPopupDialog::GetConfirmButtonBounds() const
{
	return m_okayButton->GetRect();
}

inline void MapPopupDialog::SetAnchorType(const MapPopupDialog::AnchorType i_anchorType)
{
	m_anchorType = i_anchorType;
}

inline const MapPopupDialog::AnchorType MapPopupDialog::GetAnchorType() const
{
	return m_anchorType;
}

inline void MapPopupDialog::SetHeader(const SexyString& i_headerText)
{
	m_header = i_headerText;
}

inline void MapPopupDialog::SetChallengeName(const SexyString& i_challengeName)
{
	m_challenegeName = i_challengeName;
}

inline const SexyString& MapPopupDialog::GetHeader() const
{
	return m_header;
}
	
inline void MapPopupDialog::SetDescription(const SexyString& i_descText)
{
	m_description = i_descText;
}

inline const SexyString& MapPopupDialog::GetDescription() const
{
	return m_description;
}

inline bool	MapPopupDialog::IsVisible()
{
    return m_visible;
}

inline void MapPopupDialog::SetInfoObjectType(RtWeakPtr<const class ObjectTypeDescriptor> i_objectType)
{
	m_infoObjectType = i_objectType;
}

inline RtWeakPtr<const class ObjectTypeDescriptor> MapPopupDialog::GetInfoObjectType() const
{
	return m_infoObjectType;
}


#endif
