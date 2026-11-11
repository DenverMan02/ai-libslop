#ifndef __USERDIALOG_H__
#define __USERDIALOG_H__

#include "LawnDialog.h"

#include "SexyAppFramework/EditListener.h"
#include "SexyAppFramework/ListListener.h"

class LawnApp;

namespace Sexy
{
	class DialogButton;
	class EditWidget;
	class ListWidget;
	class ScrollbarWidget;
}

class UserDialog : public LawnDialog, public Sexy::ListListener, public Sexy::EditListener
{
public:
	Sexy::ListWidget *m_userList;
	StretchableNewLawnButton*	m_renameButton;
	StretchableNewLawnButton*	m_deleteButton;
	int m_numUsers;

	UserDialog();
	virtual ~UserDialog();

	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
	virtual int	GetPreferredHeight(int i_width);

	virtual void AddedToManager(Sexy::WidgetManager *i_widgetManager);
	virtual void RemovedFromManager(Sexy::WidgetManager *i_widgetManager);

	virtual void ListClicked(int i_id, int i_idx, int i_clickCount);
	virtual void ButtonDepress(int i_id);
	virtual void EditWidgetText(int i_id, const SexyString& i_string);
	virtual bool AllowChar(int i_id, SexyChar i_char);
	virtual void Draw(Sexy::Graphics *g);

	void FinishDeleteUser();
	void FinishRenameUser(const SexyString &i_newName);

	SexyString GetSelName();
	//int GetTransferAmount();
};

#endif
