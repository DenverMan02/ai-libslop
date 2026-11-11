#ifndef __SEXYAPP_H__
#define __SEXYAPP_H__

#include "SexyAppBase.h"

class TimeMgr;

namespace Sexy
{

class SexyApp : public SexyAppBase
{
public:
    
	std::string				mReferId;
	std::string				mVariation;
	ulong					mDownloadId;
	std::string				mRegSource;
	ulong					mLastVerCheckQueryTime;
	bool					mSkipAd;
	bool					mDontUpdate;	
	bool					mCheckPartnerSig;

	int						mBuildNum;
	std::string				mBuildDate;

	std::string				mUserName;	
	std::string				mRegUserName;
	std::string				mRegCode;
	bool					mIsRegistered;	
	bool					mBuildUnlocked;

	int						mTimesPlayed;
	int						mTimesExecuted;
	bool					mTimedOut;

	static TimeMgr* 		gTimer;
    
#ifdef ZYLOM
	uint					mZylomGameId;
#endif

public:
	virtual void			UpdateFrames();
	virtual void			UpdateFramesPaused();

	void					WriteRegistrationInfo(std::string theRegUser, std::string theRegCode, int theTimesPlayed, int theTimesExecuted);
	void					ReadRegistrationInfo(std::string* theUser, std::string* theKey, int* theTimesPlayed, int* theTimesExecuted);

	virtual void			WriteToRegistry();
	virtual void			ReadFromRegistry();	

	virtual bool			CheckSignature(const Buffer& theBuffer, const std::string& theFileName);
	
	virtual bool			ShouldCheckForUpdate();
	virtual void			UpdateCheckQueried();

	virtual void			URLOpenSucceeded(const std::string& theURL);//UNICODE

public:
	SexyApp();
	virtual ~SexyApp();

	bool				Validate(const std::string& theUserName, const std::string& theRegCode);

	virtual bool			OpenRegisterPage(const DefinesMap& theDefinesMap);
	virtual bool			OpenRegisterPage();

	virtual void			PreDisplayHook();
	virtual void			InitPropertiesHook();
	virtual void			Init();
	virtual void			PreTerminate();

	virtual bool			OpenHTMLTemplate(const std::string& theTemplateFile, const DefinesMap& theDefinesMap);
	virtual void			OpenUpdateURL();

	virtual void			HandleCmdLineParam(const std::string& theParamName, const std::string& theParamValue);
	virtual void			HandleNotifyGameMessageCommandLine(const std::wstring& theCommandLine); // for WM_COPYDATA with dwData=mNotifyGameMessage
	virtual std::string		GetGameSEHInfo();
	virtual void			GetSEHWebParams(DefinesMap* theDefinesMap);

#ifdef ZYLOM
	bool					ZylomUpdateCheckNeeded();	
	void					ZylomShowAd();
#endif		

	//virtual bool			OverrideWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* theResult);
};

extern SexyApp* gSexyApp;

};

#endif //__SEXYAPP_H__
