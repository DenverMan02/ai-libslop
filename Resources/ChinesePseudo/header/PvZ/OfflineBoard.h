/*
 * OfflineBoard.h
 *
 *  Created on: 2020-11-4
 *      Author: admin
 */

#ifndef OFFLINEBOARD_H_
#define OFFLINEBOARD_H_

#include "UISingletonDialog.h"
#include "UIWidgetRadio.h"
#include "UIListener.h"
#include "NetworkServiceManager.h"

struct OfflineNoticeInfo
{
    int             m_id = 0;
    SexyString		m_wstrTitle;
    std::wstring    m_wstrContent;
};

class OfflineBoard : public UISingletonDialog<OfflineBoard>, public UI::RadioListener
{
public:
	OfflineBoard();
	virtual ~OfflineBoard();
	virtual bool            OnCreate() override;
    //virtual void            OnClose() override;
	virtual std::string     GetLayoutName() override { return "board_offline"; }
    virtual void            Draw(Sexy::Graphics* i_g) override;
    virtual void            DrawAll(Sexy::ModalFlags *i_flags, Sexy::Graphics *i_g) override;

	// ButtonListener
	virtual void            ButtonDepress(int i_id) override;
    // UI::RadioListener
    virtual void            RadioSelectionChanged(class UIWidgetRadio* pRadioBtn) override;

    void                    InitInfoList(const std::vector<OfflineNoticeInfo>& i_list);
    void                    RefreshTabList();
    void                    RefreshContent();
protected:
    class OfflineBoardTabBtn*      getTabBtn(int i_id);

private:
    class UIScrollControl*      m_pScrollTabs = NULL;
    class UIScrollControl*      m_pScrollContent = NULL;
    class UIWidgetText*         m_pTitleText = NULL;
    class UIWidgetText*         m_pContentText = NULL;
    class UIWidgetImage*         m_pContentImage = NULL;
    std::vector<OfflineNoticeInfo> 	m_infoList;
    int                         m_selectedBoardID = 0;
    Rect                        m_rectBg;
    Rect                        m_rectBgMore;
    Rect                        m_rectScroll;
    Rect                        m_rectScrollMore;
    Rect                        m_rectBoardTabBtn;
};

//------------------------------------------------------
// BoardTabBtn
//------------------------------------------------------
class OfflineBoardTabBtn : public UIWidgetRadio
{
public:
	OfflineBoardTabBtn(int i_id, const SexyString& text);
    virtual void        Draw(Sexy::Graphics* i_g) override;

protected:
    Sexy::Image*        m_pImageUnselectedMask = NULL;
    Sexy::Widget*       m_pRewardBack = NULL;
};

class OfflineBoardMgr : public Sexy::NetworkServiceListener, public LazySingleton<OfflineBoardMgr>
{
public:
	OfflineBoardMgr();
	virtual ~OfflineBoardMgr();

	void CheckForNotice();
    void TryRequest();
    void OnRequestFinished(std::string i_json);

    void ServiceRequestCompleted(const Sexy::StructuredData* i_response, const void* i_context);
    void ServiceRequestFailed(const Sexy::StructuredData*, const void* i_context);
    void ServiceRequestCompleted(ImageLib::Image*&, const void* i_context);
    void ServiceRequestCompleted(const Sexy::Buffer*, const void* i_context);

    std::string GetUpdateUrl();

private:
    void OnTotalRequestFinished();

    int         m_currentIndex;
    std::string m_updateUrl;
    std::vector<OfflineNoticeInfo> 	m_infoList;
};

#endif /* OFFLINEBOARD_H_ */
