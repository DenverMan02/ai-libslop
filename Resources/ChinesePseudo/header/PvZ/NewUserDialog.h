#ifndef __NEWUSERDIALOG_H__
#define __NEWUSERDIALOG_H__

#include "LawnDialog.h"
#include "SexyAppFramework/EditListener.h"

#include <string>

class LawnApp;

namespace Sexy
{
	class EditWidget;
}

class NewUserDialog : public LawnDialog, public Sexy::EditListener
{
public:	
	Sexy::EditWidget*				m_nameEditWidget;

public:
	// Widget
	virtual int				GetPreferredHeight(int i_width);
	virtual void			Resize(int i_x, int i_y, int i_width, int i_height);

	virtual void			AddedToManager(Sexy::WidgetManager* i_widgetManager);
	virtual void			RemovedFromManager(Sexy::WidgetManager* i_widgetManager);

	virtual void			Draw(Sexy::Graphics* g);

	// EditListener
	virtual void			EditWidgetText(int i_id, const SexyString& i_text);
	virtual bool			AllowChar(int i_id, SexyChar i_char);
	
public:	
	NewUserDialog(LawnApp* i_app, bool isRename = false);
	virtual ~NewUserDialog();

	SexyString GetName();
	void SetName(const SexyString &i_name);

};

#endif //__NEWUSERDIALOG_H__
