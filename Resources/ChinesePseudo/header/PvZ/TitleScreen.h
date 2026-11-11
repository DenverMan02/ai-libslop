#ifndef __TitleSCREEN_H__
#define __TitleSCREEN_H__

#include "SexyAppFramework/ButtonListener.h"
#include "SexyAppFramework/Widget.h"
#include "core.h"

class LawnApp;

namespace Sexy
{
	class DialogButton;
	class HyperlinkWidget;
}

enum TitleState
{
    PVZ_BEGIN_ENUM(TITLESTATE_),
    TITLESTATE_READY,          // init screen assets loaded.
	TITLESTATE_DISPLAYING_LOGO_EA,
    TITLESTATE_DISPLAYING_LOGO_TW,
    TITLESTATE_SCREEN_PRESENT, // first presenting
	TITLESTATE_SCREEN_LOADING, // waiting for load.
	TITLESTATE_SCREEN_LOADING_DECOMPRESS,
	TITLESTATE_SCREEN_FINISHED, // waiting for load.
    PVZ_END_ENUM(TITLESTATE_)
};

struct CheckRsbInfo
{
	CheckRsbInfo()
	: RsbName("")
	, RsbConfigName("")
	{

	}

	CheckRsbInfo(const std::string& i_rsbName, const std::string& i_rsbConfigName)
	: RsbName(i_rsbName)
	, RsbConfigName(i_rsbConfigName)
	{

	}

	std::string RsbName;
	std::string RsbConfigName;
};

// -
// The title screen request for and waits until the main data is loaded. 
// -
class TitleScreen : public Sexy::Widget
{
public:
	
	TitleScreen();
    virtual ~TitleScreen();

	virtual void Update();
	virtual void Draw(Sexy::Graphics *g);
	virtual void Resize(int i_x, int i_y, int i_width, int i_height);
    
	void SetSkipIntro(bool i_skip);
	
	bool IsTitleScreenFinished() const;

	void LoadRsbsProc();
	void LoadRsbsExtraProc();
    
private:
    void SetState(TitleState i_titleState);
    TitleState GetState() {return m_titleState;}

    bool NeedDecompressRsbs();
    bool NeedDecompressRsbsExtra();
    float GetFirstDecompressTotalAmount();
    float GetSecondDecompressTotalAmount();
    void LoadRsbs();
    void LoadRsbsExtra();
    unsigned int GetTargetRSBDecompressSize(const std::string& i_rsbName);
    void InitForDecompressRsbs();
    void InitDecompressImage();
    void DrawDecompressTips(Sexy::Graphics *g);
    int GetLeftDecompressTime();
    int GetPreviousDecompressTime();
    int GetTotalDecompressTime();

    TitleState m_titleState;
    
	float m_loadBarProgress;
	float m_decompressBarProgress;
	float m_totalBarWidth;
	bool m_skipIntro;
	bool m_finishedLoadingBar;

	pvztime_t m_stateEnterTime;
    
	int m_logoIndex;

	bool m_needDecompressRsbs;
	std::vector<float> m_decompressPercents;
	int m_currentDecompressIndex;
	Rect m_meterRect;
	Rect m_fillRect;
	SexyString m_progressPercentTxt;
	Rect m_tips1Rect;
	Rect m_tipsPercentRect;
	Rect m_tips2Rect;

	Sexy::Image* m_backgrounImg;
	Sexy::Image* m_backgrounImgT;
	Sexy::Image* m_meterImg;
	Sexy::Image* m_fillImg;
	Sexy::Image* m_loaderImg;
	Sexy::Image* m_loadfillImg;
	int m_totalRsbCount;
	int m_currentLeftDuration;
};

namespace Message
{
    //For AntiHack
    void Matikck();
}

#endif

