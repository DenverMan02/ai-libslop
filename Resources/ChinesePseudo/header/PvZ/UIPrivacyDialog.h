/*
 * UIPrivacyDialog.h
 *
 *  Created on: 2020-9-14
 *      Author: Administrator
 */

#ifndef UIPRIVACYDIALOG_H_
#define UIPRIVACYDIALOG_H_

#include "UISingletonDialog.h"

class UIPrivacyDialog : public UISingletonDialog<UIPrivacyDialog>
{
public:
	UIPrivacyDialog();
	virtual ~UIPrivacyDialog();
	virtual bool                OnCreate() override;
	virtual std::string         GetLayoutName() override { return "UIPrivacyDialog"; }

	// ButtonListener
	virtual void                ButtonDepress(int i_id) override;

	void SetType(int i_type = 0);

private:
	void onAgreeBtn();
	void onDisagreeBtn();
	void showDisagreeConfirm();
	void onDisagreeConfirm();
};


class UISettingLargeTextEnunciation : public UISingletonDialog<UISettingLargeTextEnunciation>
{
public:
	virtual bool OnCreate() override;
	virtual std::string GetLayoutName() override { return "UIPrivacyDialog"; }
	virtual void ButtonDepress(int i_id) override;

	void Init(const std::string& i_prefix);
};

#endif /* UIPRIVACYDIALOG_H_ */
