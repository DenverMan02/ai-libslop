#ifndef __SEXYAPPFRAMEWORK_REPORTINGMANAGER_H__
#define __SEXYAPPFRAMEWORK_REPORTINGMANAGER_H__

#include "Reporting.h"

#include "CritSect.h"
#include "Debug.h"
#include "Singleton.h"
#include "TArray.h"
//PVZ2_CHINESE_BEGIN
#include "Font.h"
//PVZ2_CHINESE_END
namespace Sexy
{
#if PRIME_IS_REPORTING_ENABLED || PRIME_IS_ASSERT_ENABLED

// forward declarations
struct SRptInstanceCallSpec;
class Graphics;
    
#ifdef WIDGETS_USE_PRIMETEXT
    class PrimeTypeface;
#else
    class Font;
#endif

    
#define MAX_REPORT_STRING_SIZE 1024

    inline int PrimeVsnprintf(char *i_buffer, int i_size, const char *i_format, va_list i_argList)
    {
        int count = 0;
        
        // _vsnprintf crashes in nasty ugly ways with bad format strings.
        // This try-catch block makes it so we have a good stack trace.
#ifdef SUPPORT_EXCEPTIONS
#ifdef HOST_WINDOWS
        __try
#else
        try
#endif
#endif
        {
            count = vsnprintf(i_buffer, i_size, i_format, i_argList);
        }
#ifdef SUPPORT_EXCEPTIONS
#ifdef HOST_WINDOWS
        __except(EXCEPTION_EXECUTE_HANDLER)
#else
        catch(...)
#endif
        {
#ifdef PLATFORM_IS_WINDOWS
            PRIME_ERROR("bad format string");
#elif defined(PLATFORM_IS_MACOSX)
#ifdef SEXY_DEBUG_BUILD
            std::ostringstream oss;
            oss << "bad format string" << std::endl;
            DebugStr((const unsigned char*)oss.str().c_str());
#endif
#endif
        }
#endif
        
        if (count == -1)
        {
            i_buffer[i_size - 1] = NULL;
            return i_size - 1;
        }
        else
        {
            return count;
        }
    }

inline void PrimeVsnprintfEnsureNewLine(char *buffer, int size, const char *i_format, va_list i_argList)
{
	int len = PrimeVsnprintf(buffer, size, i_format, i_argList);
	if (buffer[len - 1] != '\n')
	{
		if (len + 1< size)
		{
			// append a new line
			buffer[len] = '\n';
			buffer[len + 1] = NULL;
		}
		else
		{
			// overwrite last character with new line
			buffer[len - 1] = '\n';
		}
	}
}


/*--------------------------------------------------------------------------*/
// Struct SReportChunk definition.

struct SReportChunk
{
    ERptInstanceType			InstanceType;
	const char*					Category;
	SRptInstanceLocationSpec	LocationSpec;
	const char*					Text;
	bool						BeginLine;
	bool						EndLine;
    
	SReportChunk()
    { Sexy::ClearStruct(this); }
    
	SReportChunk(
                 const SRptInstanceCallSpec i_callSpec,
                 const SRptInstanceLocationSpec i_locationSpec,
                 const char* i_category,
                 const char* i_text)
	{
		InstanceType = i_callSpec.InstanceType;
		Category	 = i_category;
		LocationSpec = i_locationSpec;
		Text		 = i_text;
		BeginLine	 = false;
		EndLine		 = i_callSpec.MessageEol;
	}
};

/*--------------------------------------------------------------------------*/
// Interface IReportSink definition.

class IReportSink
{
public:
	virtual ~IReportSink() {}
    
	virtual void Write(const SReportChunk& i_chunk) = 0;
	virtual void Flush() {}
};

/*--------------------------------------------------------------------------*/
// Class ReportingMgr definition.
    
// $$ not currently thread-safe, needs to be
class ReportingMgr : public LazySingleton <ReportingMgr>
{
    friend struct SRptInstanceCallSpec;
//PVZ2_CHINESE_BEGIN
//#ifdef WIDGETS_USE_PRIMETEXT
//    typedef     PrimeTypeface      ReportFont;
//#else
//    typedef     Font               ReportFont;
//#endif
//PVZ2_CHINESE_END
    
public:
	ReportingMgr();
    ~ReportingMgr();
    
	static bool IsReportActive()
    { return HasInstance() && (GetInstance().m_recursionCount > 0); }
    
    // Reporting instance API.
    
	ERptUserChoice GeneralReport(
                                 CRptInstanceStaticSpec& io_staticSpec,
                                 const SRptInstanceCallSpec& i_callSpec,
                                 const SRptInstanceLocationSpec& i_locationSpec);
    
	ERptUserChoice FullReport(
                              CRptInstanceStaticSpec& io_staticSpec,
                              SRptInstanceCallSpec i_callSpec,
                              const SRptInstanceLocationSpec& i_locationSpec);
    
	ERptUserChoice ModalReport(
                               CRptInstanceStaticSpec& io_staticSpec,
                               const SRptInstanceCallSpec& i_callSpec,
                               const SRptInstanceLocationSpec& i_locationSpec);
    
	void Write(const SReportChunk& i_chunk);
    
    void Draw(Graphics* g);
    
	void Flush();
    
    
    // Warnings and errors.
    
	void AddWarning();
	void AddError();
    void AddContentError();
    
	int32  GetWarningCount() const {
        return m_warningCount; }
	int32  GetErrorCount() const {
        return m_errorCount; }
	int32  GetContentErrorCount() const {
        return m_contentErrorCount; }
	int32  GetTotalWarningCount() const {
        return m_totalWarningCount; }
	int32  GetTotalErrorCount() const {
        return m_totalErrorCount; }
    
	void ResetWarningCount() {
        m_warningCount = 0; }
	void ResetErrorCount() {
        m_errorCount = 0; m_contentErrorCount = 0; }
    
    // Custom sinks.
    
	void AddSink(IReportSink* i_sink, bool i_shouldOwnSink);
    
    // Call ReportingMgr_Update() instead of this, ReportingMgr_Update() will always exist (at least as a nop) even if reporting is disabled)
    void Update();
    
private:
    void writeToSinks(const SReportChunk& i_chunk);
    
    ERptUserChoice queueReportForMainThreadAndWait(CRptInstanceStaticSpec* ioStaticSpec, SRptInstanceCallSpec* inRptInstCallSpec, const SRptInstanceLocationSpec* inRptInstLocSpec); // safe to call from any thread
    void doPendingReports(); // Should only be called from main thead.
    
    //PVZ2_CHINESE_BEGIN
    Font* mFont;
#ifdef WIDGETS_USE_PRIMETEXT
    PrimeTypeface* mPrimeFont;
#endif
    //PVZ2_CHINESE_END
    
	static bool isContentCategory(RptCategoryType i_categoryName);
	static bool isContentError(ERptInstanceType i_instanceType, RptCategoryType i_categoryType);
    
	struct SSinkEntry : Sexy::TOptAutoPtr <IReportSink>
	{
		SSinkEntry() {}
		~SSinkEntry() { if (IsValid()) (*this)->Flush(); }
	};
    
    struct SPendingReportInfo
    {
        SPendingReportInfo(CRptInstanceStaticSpec* ioStaticSpec, SRptInstanceCallSpec* inRptInstCallSpec, const SRptInstanceLocationSpec* inRptInstLocSpec, ERptUserChoice* outUserChoice, Condition* inReportIssuedOnMainThread)
        {
            StaticSpec = ioStaticSpec;
            RptInstCallSpec = inRptInstCallSpec;
            RptInstLocSpec = inRptInstLocSpec;
            *outUserChoice = RPT_UC_Continue;
            UserChoice = outUserChoice;
        }
        
        CRptInstanceStaticSpec* StaticSpec;
        SRptInstanceCallSpec* RptInstCallSpec;
        const SRptInstanceLocationSpec* RptInstLocSpec;
        ERptUserChoice* UserChoice; // Once the main thread sends the report, the user's choice will be set here.
        Condition* ReportIssuedOnMainThread; // The queueing thread will wait for the main thread to set this condition before it reads the value from UserChoice
    };
    
	// state
    Sexy::TArray<SSinkEntry, 10> m_sinkColl;	// route all logging through these sinks
	bool m_isLinePending;				// true while we're in the middle of rendering a line (before EOL hits)
    
	// stats
	int32	 m_recursionCount;				// depth inside reporting function (to avoid problems from asserting inside the assert system etc.)
	int32  m_warningCount;				// current warning count (from anything causing an error - asserts, errors, etc.)
	int32  m_errorCount;					// current error count (from the warning system)
	int32  m_contentErrorCount;			// num of content errors (a subset of error count)
	int32  m_totalWarningCount;			// cumulative total warnings, does not get reset
	int32  m_totalErrorCount;				// cumulative total errors, does not get reset
    
    CritSect mCritSect; // Protects access to mPendingNonMainThreadReports
    std::vector<SPendingReportInfo> mPendingNonMainThreadReports;
};
    
inline ReportingMgr& ReportingMgr_GetSingleton() { return ReportingMgr::GetInstance(); }
#define g_reportingmgr (ReportingMgr_GetSingleton())
    
#endif // PRIME_IS_REPORTING_ENABLED OR PRIME_IS_ASSERT_ENABLED
    
} //namespace Sexy

#endif //__SEXYAPPFRAMEWORK_REPORTINGMANAGER_H__
