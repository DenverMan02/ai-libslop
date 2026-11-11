#ifndef __GAMEBUTTOM_H__
#define __GAMEBUTTOM_H__

#include "SexyAppFramework/Rect.h"
#include "SexyAppFramework/Color.h"
#include "SexyAppFramework/DialogButton.h"
#include "SexyAppFramework/SexyVector.h"
class LawnApp;

namespace Sexy
{
	class Image;
	class Graphics;
	class Font;
	class Widget;
}

using namespace Sexy;

typedef enum {
	BUTTON_ALIGN_LEFT	= -1,
	BUTTON_ALIGN_CENTER,
	BUTTON_ALIGN_RIGHT
}BUTTON_ALIGNMENT_X;

typedef struct {
	int m_buttonLeftPadding;
	int m_buttonRightPadding;
} BUTTON_PADDING;

class GameButton
{
public:
	enum {
		BUTTON_LABEL_LEFT	= -1,
		BUTTON_LABEL_CENTER,
		BUTTON_LABEL_RIGHT
	};
	enum
	{
		COLOR_LABEL,
		COLOR_LABEL_HILITE,
		COLOR_LABEL_DISABLED,
		COLOR_BKG,
		COLOR_BKG_DISABLED,
		NUM_COLORS
	};

	LawnApp *m_app;
	Widget *m_parentWidget;
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	bool m_isOver;
	bool m_isDown;
	bool m_disabled;
	Color m_colors[NUM_COLORS];

	int m_id;	
	SexyString m_label;
	int m_labelJustify;
	PrimeTypeface *m_font;
	Image *m_buttonImage;
	Image *m_overImage;
	Image *m_downImage;	
	Image *m_disabledImage;
	Image *m_overOverlayImage;
	Sexy::Rect m_normalRect;
	Sexy::Rect m_overRect;
	Sexy::Rect m_downRect;
	Sexy::Rect m_disabledRect;

	bool m_inverted;
	bool m_btnNoDraw;
	bool m_frameNoDraw;

	double m_overAlpha;
	double m_overAlphaSpeed;
	double m_overAlphaFadeInSpeed;
	bool m_drawStoneButton;
	int m_buttonVarient;
	int m_textOffsetX;
	int m_textOffsetY;
	int m_buttonOffsetX;
	int m_buttonOffsetY;

	GameButton(int i_id);
	virtual ~GameButton();
	
	bool HaveButtonImage(Image *i_image, const Sexy::Rect &i_rect);
	virtual void DrawButtonImage(Graphics *g, Image *i_image, const Sexy::Rect &i_rect, int x, int y);
	virtual void SetFont(PrimeTypeface* i_font);
	bool IsButtonDown();
	void Draw(Graphics* i_g);
	void SetDisabled(bool isDisabled);
	bool IsMouseOver() const;
	void Update();
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
    void SetPos(int i_x, int i_y);
	virtual void SetLabel(const SexyString& i_label);
    void SetImage(Image* i_image);

	virtual BUTTON_PADDING SetPadding(int i_buttonLeftPadding = 0, int i_buttonRightPadding = 0);
};

inline void GameButton::SetImage(Sexy::Image *i_image)
{
    m_buttonImage = i_image;
    Resize(m_x, m_y, i_image->GetWidth() / i_image->mNumCols, i_image->GetHeight() / i_image->mNumRows);
}

inline void GameButton::SetPos(int i_x, int i_y)
{
    m_x = i_x; m_y = i_y; 
}

class NewLawnButton : public DialogButton 
{
public:
    //PVZ2_CHINESE_BEGIN
    #ifdef WIDGETS_USE_PRIMETEXT
    PrimeTypeface *m_hilitePrimeFont;
    #endif
	Font *m_hiliteFont;
    //PVZ2_CHINESE_END
	int m_textDownOffsetX;
	int m_textDownOffsetY;
	int m_buttonOffsetX;
	int m_buttonOffsetY;

	bool m_usePolygonShape;
	SexyVector2 m_polygonShape[4];

	NewLawnButton(Image* i_componentImage, int i_id, ButtonListener* i_listener);
	virtual void Draw(Graphics* i_g);
	virtual bool IsPointVisible(int x, int y);
	void SetLabel(const SexyString& i_label);

	int m_buttonLeftPadding;
	int m_buttonRightPadding;
};

class StretchableNewLawnButton : public NewLawnButton
{
public:
	StretchableNewLawnButton(Image* i_componentImage, int i_id, ButtonListener* i_listener);
	virtual ~StretchableNewLawnButton();

	void DrawStretchableNewLawnButton(Graphics* g, Image *i_image, int x, int y, int i_width, int i_height);
	void DrawStretchableNewLawnButton(Graphics* g, Image *i_image, const Sexy::Rect& i_drawRect);

	virtual void DrawButtonImage(Graphics *g, Image *i_image, const Sexy::Rect &i_rect, int x, int y);

	LawnApp *m_app;

	int m_labelWidth;

	int m_buttonLeftPadding;
	int m_buttonRightPadding;
};

StretchableNewLawnButton* MakeStretchableNewLawnButton(int i_id, ButtonListener *i_listener, const SexyString &i_text, PrimeTypeface *i_font, Image *i_imageNormal, Image *i_imageOver, Image *i_imageDown, int i_buttonLeftPadding, int i_buttonRightPadding);

StretchableNewLawnButton* MakeStretchableNewLawnButton(int i_id, ButtonListener *i_listener, const SexyString &i_text, class PrimeText_PotentialTypeface *i_font, Image *i_imageNormal, Image *i_imageOver, Image *i_imageDown, int i_buttonLeftPadding, int i_buttonRightPadding);

//PVZ2_CHINESE_BEGIN
StretchableNewLawnButton* MakeStretchableNewLawnButton(int i_id, ButtonListener *i_listener, const SexyString &i_text, Font *i_font, Image *i_imageNormal, Image *i_imageOver, Image *i_imageDown, int i_buttonLeftPadding, int i_buttonRightPadding);
//PVZ2_CHINESE_END
#endif //__GAMEBUTTOM_H__
