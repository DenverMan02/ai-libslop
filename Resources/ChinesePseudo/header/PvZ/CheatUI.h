#ifndef PVZ2_CHEATUI_H
#define PVZ2_CHEATUI_H

#include "RtObject.h"
#include "Cheats.h"
#include "PVZCheats.h"
#include "PVZ2UIDialog.h"
#include "SexyAppBase.h"
#include "UIWidgetText.h"

/// Individual debug options

typedef Delegate1<std::string&> CheatUILabelCallback;

class CheatUILine : public RtObject
{
public:
	RT_CLASS_DEFINE(CheatUILine, RtObject, RtClass) {}
	
	CheatUILine()
		: m_cheat(NULL)
		, m_label("#INVALID#")
		, m_contexts(CHEATCONTEXT_Everything)
	{}
	CheatUILine(Cheat* i_managedCheat, const std::string& i_label)
		: m_cheat(i_managedCheat)
		, m_label(i_label)
		, m_contexts(CHEATCONTEXT_Everything)
	{}
	virtual ~CheatUILine()
	{}
	
	void Tap(const Point& i_location);
	void Draw(class Graphics* i_g);

	Cheat* GetCheat() const;
	CheatUILine* SetValidContexts(CheatContext i_context);
	CheatContext GetValidContexts() const;
    std::string GetLabel();
	
	virtual float GetHeight();
	
protected:
	SexyVector2 getDimensions();
	
	virtual Color getLabelColor() const;
	
	virtual void onTap(const Point& i_location) 	{}
	virtual void onDraw(class Graphics* i_g);
	
private:
	Cheat* m_cheat;
	std::string m_label;
    CheatUILabelCallback m_labelCallback;
	CheatContext m_contexts;
};

class CheatUILineSeparator : public CheatUILine
{
public:
	RT_CLASS_DEFINE(CheatUILineSeparator, CheatUILine, RtClass) {}
	CheatUILineSeparator() {}
	
	virtual float GetHeight() override;
	
protected:
	virtual void onDraw(class Graphics* i_g) override;
};

class CheatUILineToggle : public CheatUILine
{
public:
	RT_CLASS_DEFINE(CheatUILineToggle, CheatUILine, RtClass) {}
	
	CheatUILineToggle() {}
	CheatUILineToggle(Cheat* i_cheat, const std::string& i_label)
		: CheatUILine(i_cheat, i_label)
	{}
	
protected:
	virtual void onTap(const Point& i_location) override;
	virtual void onDraw(class Graphics* i_g) override;
};

class CheatUILineCommand : public CheatUILine
{
public:
	RT_CLASS_DEFINE(CheatUILineCommand, CheatUILine, RtClass) {}
	
	CheatUILineCommand()
		: m_lastTapped(0.f)
	{}
	CheatUILineCommand(Cheat* i_cheat, const std::string& i_label)
		: CheatUILine(i_cheat, i_label)
		, m_lastTapped(0.f)
	{}
	
protected:
	virtual void onTap(const Point& i_location) override;
	virtual void onDraw(class Graphics* i_g) override;
	
	virtual Color getLabelColor() const override;
	
private:
	pvztime_t m_lastTapped;
};

class CheatAdjusterWidget : public Sexy::Widget
{
public:
	RT_CLASS_DEFINE(CheatAdjusterWidget, Sexy::Widget, RtClass) {}

	CheatAdjusterWidget()
		: m_pEditWidget(nullptr)
		, m_pCloseButton(nullptr)
		, m_moveStartPoint(Point(0, 0))
		, m_isMoving(false)
		, m_name("")
	{}

	~CheatAdjusterWidget();

	void onCreate(const std::string& i_name, float i_value, Sexy::EditListener* i_pEditListener, Sexy::ButtonListener* i_pButtonListener);

	float getValue();

	Rect getNameDrawRect();

	void Draw(Graphics* g) override;
	void TouchBegan(const Sexy::Touch& i_touch);
	void TouchMoved(const Sexy::Touch& i_touch);
	void TouchEnded(const Sexy::Touch& i_touch);

	EditWidget* 	m_pEditWidget;
	PVZ2UIButton*	m_pCloseButton;
	Sexy::Point		m_moveStartPoint;
	bool			m_isMoving;
	std::string  	m_name;
};

class CheatUILineAdjuster : public CheatUILine, public EditListener, public Sexy::ButtonListener
{
public:
	RT_CLASS_DEFINE(CheatUILineAdjuster, CheatUILine, RtClass) {}

	CheatUILineAdjuster() {}
	CheatUILineAdjuster(Cheat* i_cheat, const std::string& i_label)
		: CheatUILine(i_cheat, i_label)
		, m_pAdjusterWidget(nullptr)
		, m_lastTapped(0.f)
	{}

protected:
	virtual void onTap(const Point& i_location) override;
	virtual void onDraw(class Graphics* i_g) override;
	virtual Color getLabelColor() const override;


	// EditListener
	virtual void EditWidgetText(int theId, const SexyString& theString);
	virtual bool AllowKey(int theId, Sexy::KeyCode theKey) { return true; }
	virtual bool AllowChar(int theId, SexyChar theChar) { return true; }
	virtual bool AllowText(int theId, const SexyString& theText) { return true; }

	// ButtonListener
	virtual void ButtonDepress(int theId);

	CheatAdjusterWidget*		m_pAdjusterWidget;

private:
	pvztime_t m_lastTapped;
};


/// CheatUIPanel

struct CheatUILineTracker
{
	// For bonus points, use this struct to interpolate cell heights (opening/closing folders, etc)
	CheatUILine* Line;
	float Height;
	float TargetHeight;
};

class CheatUILineFolder : public CheatUILine
{
public:
	RT_CLASS_DEFINE(CheatUILineFolder, CheatUILine, RtClass) {}
	
	CheatUILineFolder()
		: m_expanded(false), m_useIndent(true)
	{}
	CheatUILineFolder(const std::string& i_label)
		: CheatUILine(NULL, i_label)
		, m_expanded(false), m_useIndent(true)
	{}
	CheatUILineFolder(const std::string& i_label, bool i_expanded)
		: CheatUILine(NULL, i_label)
		, m_expanded(i_expanded), m_useIndent(true)
	{}
	virtual ~CheatUILineFolder();
	
	virtual float GetHeight() override;
	
	void AddLine(CheatUILine* i_line);
	void SetUseIndent(bool i_useIndent);
	void SetExpanded(bool i_expanded);
    
    void SortByTitle(bool i_reverse = false);
	
protected:
	virtual void onTap(const Point& i_location) override;
	virtual void onDraw(class Graphics* i_g) override;
	
private:
	bool m_expanded;
	bool m_useIndent;
	std::vector<CheatUILineTracker> m_contained;
};

class CheatUIPanel : public LazySingleton<CheatUIPanel>
{
public:
	CheatUIPanel();
	
	virtual ~CheatUIPanel();
    
    static CheatUILine* BuildUILineForCheat(const std::string& i_cheatName, const std::string& i_cheatLabel);
	
	CheatUILine* AddLine(const std::string& i_cheatName, const std::string& i_cheatLabel);
	CheatUILine* AddSeparator();
	CheatUILineFolder* BeginFolder(const std::string& i_folderLabel, bool i_expanded = false);
	CheatUILineFolder* EndFolder();
	
	void DoPartialOpenOrClose();
	
	void SetVisible(bool i_visible);
	bool IsVisible() const;
	void SetKeyboardMode(bool i_keyboardMode);
	
	Rect GetScreenRect() const;
	
	CheatUILine* AddLine(CheatUILine* i_line);
	void Draw(class Graphics* i_g);
	
	// Custom touch handling, return 'true' if we consumed the touch
	bool TouchBegan(const Sexy::Touch& i_touch);
	bool TouchMoved(const Sexy::Touch& i_touch);
	void TouchesCanceled();
	bool TouchEnded(const Sexy::Touch& i_touch);
	
	void Tap(Point i_loc);
	
	float GetDefaultLineHeight() const;
	
	void SetScrollAmount(int i_scrollAmount);
	
private:
	Rect getCloseButtonRect() const;
	Rect getCollapseButtonRect() const;
	Rect getSliderButtonRect();
	
	float getTotalHeight();

	void collapseTopLevelFolder();

	Sexy::Touch m_initialTouch;
	int m_scroll;
	
	pvztime_t m_partialOpenTime;
	bool m_visible;
	bool m_keyboardUp;
	
	bool m_scrolling;
	int m_scrollingStartedAt;
	
	bool m_sliderMoving;

	std::vector<CheatUILineTracker> m_lines;
	std::vector<CheatUILineFolder*> m_folderStack;
};

#define gCheatUI (CheatUIPanel::GetInstancePtr())




#endif
