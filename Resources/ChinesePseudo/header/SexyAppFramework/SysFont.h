#ifndef __SYSFONT_H__
#define __SYSFONT_H__

#include "Font.h"

#ifndef REMOVE_SEXYFONT

//JVW - I would like to support SysFont or something like it in prime, 
// but it's low priority as few games use it.
#ifdef SUPPORT_SYSFONT

#ifdef SUPPORT_BITMAP_SYSFONT

namespace Sexy
{
	
	class ImageFont;
	class SexyAppBase;
	
	void CleanupSysFont();
	
	class SysFont : public Font
	{
	public:
		RT_CLASS_DEFINE(SysFont, Font, ResourceClass) {}

	private:
		ImageFont*				mImageFont;
		uint64					mCurRev;
		
		void					InitFromImageFont();
		void					ReInit();
	public:
		SexyAppBase*			mApp;
		bool					mDrawShadow;
		bool					mSimulateBold;
		//void Init(SexyAppBase* theApp, const std::string& theFace, int thePointSize, int theScript, bool bold, bool italics, bool underline, bool useDevCaps);
		
	public:
		SysFont(const std::string& theFace = "Arial", int thePointSize = 10, bool bold = false, bool italics = false, bool underline = false);
		SysFont(SexyAppBase* theApp, const std::string& theFace, int thePointSize, int theScript = 0, bool bold = false, bool italics = false, bool underline = false);
		SysFont(const SysFont& theSysFont);
		
		virtual ~SysFont();
		
		ImageFont*				CreateImageFont();
		virtual int				StringWidth(const SexyString& theString) override;
		virtual void			DrawString(Graphics* g, int theX, int theY, const SexyString& theString, const Color& theColor, const Rect& theClipRect) override;
		
		virtual Font*			Duplicate() override;
	};
	
}

#else
namespace Sexy
{

class ImageFont;
class SexyAppBase;

class SysFont : public Font
{
public:
	RT_CLASS_DEFINE(SysFont, Font, ResourceClass) {}

public:	
	HFONT					mHFont;
	SexyAppBase*			mApp;
	bool					mDrawShadow;
	bool					mSimulateBold;
	
	void Init(SexyAppBase* theApp, const std::string& theFace, int thePointSize, int theScript, bool bold, bool italics, bool underline, bool useDevCaps);

public:
	SysFont(const std::string& theFace = "Arial", int thePointSize = 10, bool bold = false, bool italics = false, bool underline = false);
	SysFont(SexyAppBase* theApp, const std::string& theFace, int thePointSize, int theScript = ANSI_CHARSET, bool bold = false, bool italics = false, bool underline = false);
	SysFont(const SysFont& theSysFont);

	virtual ~SysFont();

	ImageFont*				CreateImageFont();
	virtual int				StringWidth(const SexyString& theString);
	virtual void			DrawString(Graphics* g, int theX, int theY, const SexyString& theString, const Color& theColor, const Rect& theClipRect);

	virtual Font*			Duplicate();

	static void MakeCompiledInFont(const std::string face, int face_size);
};

}
#endif //ELSIF SUPPORT_BITMAP_SYSFONT
#endif //SUPPORT_SYSFONT
#endif //REMOVE_SEXYFONT
#endif //__SYSFONT_H__
