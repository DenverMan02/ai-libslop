#ifndef __NEWOPTIONSDIALOG_H__
#define __NEWOPTIONSDIALOG_H__

#include "SexyAppFramework/SliderListener.h"
#include "SexyAppFramework/CheckboxListener.h"
#include "SexyAppFramework/ButtonListener.h"
#include "SexyAppFramework/Checkbox.h"

#include "LawnDialog.h"
#include "UIHelper.h"
#include "PrimeTextWidget.h"
#include "WidgetButtonList.h"
#include "PVZ2UIDialog.h"

class LawnApp;
class StretchableNewLawnButton;

namespace Sexy
{
	class Slider;
	class Checkbox;
	class DialogButton;
	class ImageFont;
}

class NewOptionsDialog : public Widget, public ButtonListener, public SliderListener, public CheckboxListener
{

public:	
	NewOptionsDialog(const bool i_showBackToMap, const bool i_isDangerRoom);
	virtual ~NewOptionsDialog();
	
	virtual int		GetPreferredHeight(int i_width);
	virtual void	AddedToManager(WidgetManager* i_widgetManager);
	virtual void	RemovedFromManager(WidgetManager* i_widgetManager);
	virtual void	Resize(int i_x, int i_y, int i_width, int i_height);
	virtual void	Draw(Graphics* i_g);	
	virtual void	SliderVal(int i_id, double i_val);
	virtual void	CheckboxChecked(int i_id, bool i_isChecked);
	virtual void	ButtonPress(int i_id);
	virtual void	ButtonDepress(int i_id);	
    virtual void    MouseDrag(int x, int y);
	virtual void	SliderReleased(int i_id, double i_val);

	virtual void	MouseMove(int x, int y);
	virtual void	MouseDown(int x, int y, int theClickCount);
	virtual void	MouseUp(int x, int y);
    
private:
	
    void drawShadedBox(Graphics* i_g, Rect extents);
    void draw_Flowerbox(Graphics* i_g, float boxTopCenterX, float boxTopCenterY);
    void drawInnerBoxes(Graphics* i_g);
    int getFlowerboxTopSpace();
    void getObjectiveData(bool& hasObjective, std::vector<SexyString>& o_objectiveText, std::vector<bool>& o_objectiveFailed);
    void getObjectiveDataProgress(std::vector<SexyString>& o_objectiveText);
    double sunflowerAngle();
    void drawHeaderText(Graphics* i_g);
    void recalculateObjectiveBox(const std::vector<SexyString>& i_objectiveText, std::vector<Rect> *o_textBlocks, bool hasStar = false);
    void calculateOuterBoxes();

    void showConfirmBackToMap();
    void onCancelBackToMap();
    void onConfirmBackToMap();
    
    void showConfirmBackToMenu();
    void onCancelBackToMenu();
    void onConfirmBackToMenu();
    
    void showConfirmRestart();
    void onCancelRestart();
    void onConfirmRestart();
    
	void showConfirmQuitDangerRoom();
	void onCancelQuickDangerRoom();
    void onConfirmQuickDangerRoom();
	
    UIWidget*    IsMouseOverFriendWidget(int x, int y);
    
    PVZ2UIDialog* showExitMenu_Internal(SexyString i_headerLabel, SexyString i_messageBody);

    Widget_ButtonList           m_buttonList;
    std::vector<PrimeTextWidget*> m_textWidgets;
    std::vector<PrimeTextWidget*> m_textChallengeProgressWidgets;
    
	Slider*						m_musicVolumeSlider;
	Slider*						m_sfxVolumeSlider;
    PrimeTextWidget*            m_musicVolumeTextWidget;
    PrimeTextWidget*            m_sfxVolumeTextWidget;
    
    Rect                        m_OuterBoxExtents;
    Rect                        m_InnerBoxExtents;
    Rect                        m_ObjectiveBoxExtents;
    Point                       m_ObjectiveStarPos;
    bool                        m_HasObjective;
	PopAnimRig*					m_starAnimRig;
};

#endif //__NEWOPTIONSDIALOG_H__
