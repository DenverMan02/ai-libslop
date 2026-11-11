#ifndef __SEXYAPPFRAMEWORK_REPORTING_H__
#define __SEXYAPPFRAMEWORK_REPORTING_H__

// Cross-platform logging/assert macros

#include <assert.h>
#include "xprintf.h"
#include "Common.h"
#include "Debug.h"
#include <stdarg.h>
#include <signal.h>

#if PRIME_IS_REPORTING_ENABLED || PRIME_IS_ASSERT_ENABLED
//From LCS core.h
#if defined HOST_WINDOWS
#   define PRIME_BREAKPOINT()                       \
PRIME_SAFE_MACRO_BEGIN()                    \
__asm INT 3                                 \
PRIME_SAFE_MACRO_END()
#   define PRIME_BREAK_IF_DEBUGGING()				\
PRIME_SAFE_MACRO_BEGIN()                    \
if (::IsDebuggerPresent())                  \
{                                           \
PRIME_BREAKPOINT();                     \
}                                           \
PRIME_SAFE_MACRO_END()
#elif defined HOST_XBOX360
#   define PRIME_BREAKPOINT()                       \
PRIME_SAFE_MACRO_BEGIN()                \
__debugbreak()                          \
PRIME_SAFE_MACRO_END()
#	define PRIME_BREAK_IF_DEBUGGING()				\
PRIME_SAFE_MACRO_BEGIN()                    \
if (::DmIsDebuggerPresent())                \
{                                           \
PRIME_BREAKPOINT();                     \
}                                           \
PRIME_SAFE_MACRO_END()
#elif defined HOST_MACOSX
#   define PRIME_BREAKPOINT()                       \
PRIME_SAFE_MACRO_BEGIN()                        \
__asm__("int $3");                              \
PRIME_SAFE_MACRO_END()
#	define PRIME_BREAK_IF_DEBUGGING()               \
/* $$ figure out how to detect debugger*/       \
PRIME_SAFE_MACRO_BEGIN()                        \
PRIME_BREAKPOINT();                             \
PRIME_SAFE_MACRO_END()
#elif defined HOST_IPHONEOS
#if defined(__arm__) || defined(__arm64__)
#   define PRIME_BREAKPOINT()                       \
PRIME_SAFE_MACRO_BEGIN()                    \
__builtin_trap();                           \
PRIME_SAFE_MACRO_END()
#else
#   define PRIME_BREAKPOINT()                       \
PRIME_SAFE_MACRO_BEGIN()                    \
__asm__("int $3");                          \
PRIME_SAFE_MACRO_END()
#endif
#	define PRIME_BREAK_IF_DEBUGGING()               \
PRIME_SAFE_MACRO_BEGIN()                        \
/* $$ figure out how to detect debugger*/       \
PRIME_BREAKPOINT();                             \
PRIME_SAFE_MACRO_END()
#elif defined HOST_WII
#	define PRIME_BREAKPOINT()                       \
PRIME_SAFE_MACRO_BEGIN()					\
/* found this in rvl.cpu */             \
register unsigned int oldInts;          \
register unsigned int newInts;          \
asm volatile                            \
{                                       \
mfmsr oldInts;                      \
ori newInts, oldInts, 0x400;        \
mtmsr newInts;                      \
mtmsr oldInts;                      \
}                                       \
PRIME_SAFE_MACRO_END()
#	define PRIME_BREAK_IF_DEBUGGING()               \
PRIME_SAFE_MACRO_BEGIN()                        \
/* $$ figure out how to detect debugger*/       \
PRIME_BREAKPOINT();                             \
PRIME_SAFE_MACRO_END()
#elif defined HOST_PS3
#   define PRIME_BREAKPOINT()                       \
PRIME_SAFE_MACRO_BEGIN()                        \
__asm__ volatile ("tw 31,1,1");                 \
PRIME_SAFE_MACRO_END()
#	define PRIME_BREAK_IF_DEBUGGING()               \
PRIME_SAFE_MACRO_BEGIN()                        \
/* $$ figure out how to detect debugger*/       \
PRIME_BREAKPOINT();                             \
PRIME_SAFE_MACRO_END()
#elif defined HOST_VITA
//Not sure if this is valid for Vita. How to test?
#   define PRIME_BREAKPOINT()                       \
PRIME_SAFE_MACRO_BEGIN()                    \
__asm__ volatile ("tw 31,1,1");             \
PRIME_SAFE_MACRO_END()
#	define PRIME_BREAK_IF_DEBUGGING()               \
PRIME_SAFE_MACRO_BEGIN()                        \
/* $$ figure out how to detect debugger*/       \
PRIME_BREAKPOINT();                             \
PRIME_SAFE_MACRO_END()
#else
#   define PRIME_BREAKPOINT()                       \
PRIME_SAFE_MACRO_BEGIN()                    \
__asm INT 3;                                \
PRIME_SAFE_MACRO_END()
#	define PRIME_BREAK_IF_DEBUGGING()               \
PRIME_SAFE_MACRO_BEGIN()                    \
PRIME_BREAKPOINT();                         \
PRIME_SAFE_MACRO_END()
#endif //OS if-block
#endif //PRIME_IS_REPORTING_ENABLED || PRIME_IS_ASSERT_ENABLED

#if defined HOST_WINDOWS || HOST_XBOX360
#   define PRIME_VA_COPY(dst, src)                  \
PRIME_SAFE_MACRO_BEGIN()                    \
((dst) = (src))                             \
PRIME_SAFE_MACRO_END()
#else //HOST_WINDOWS || HOST_XBOX360
#   define PRIME_VA_COPY(dst, src)                  \
PRIME_SAFE_MACRO_BEGIN()                    \
if (src != NULL)                            \
{                                           \
va_copy(dst, src);                      \
}                                           \
else                                        \
{                                           \
Sexy::ClearStruct(&dst);                \
}                                           \
PRIME_SAFE_MACRO_END()
#endif //!HOST_WINDOWS && !HOST_XBOX360


// This macro allows you to use a typesafe bitflag parameter as a strict enum
// rather than simple an int or dword. The operators need to be defined so you
// can combine and test the component flags.
//
#define PRIME_MAKE_ENUM_BIT_OPERATORS(inEnumType)                   \
inline inEnumType operator | (inEnumType a, inEnumType b)     	\
{  return (inEnumType)((int32)a | (int32)b); }                	\
inline inEnumType operator & (inEnumType a, inEnumType b)     	\
{  return (inEnumType)((int32)a & (int32)b); }					\
inline inEnumType operator ^ (inEnumType a, inEnumType b)		\
{  return (inEnumType)((int32)a ^ (int32)b); }                  \
inline inEnumType operator ~ (inEnumType a)						\
{  return (inEnumType)~(int32)a; }							\
inline inEnumType operator |= (inEnumType& a, inEnumType b)		\
{  return a = a | b; }                                      \
inline inEnumType operator &= (inEnumType& a, inEnumType b)		\
{  return a = a & b; }

#define PRIME_BEGIN_ENUM(inPrefix)                      \
inPrefix##Invalid = -1,								\
inPrefix##BeforeBegin = -1

#define PRIME_END_ENUM(inPrefix)						\
inPrefix##End,										\
inPrefix##Last  = inPrefix##End - 1,				\
inPrefix##Begin = inPrefix##BeforeBegin + 1,		\
inPrefix##Count = inPrefix##End - inPrefix##Begin


// Note: the indices passed to PRIME_ATTRIBUTE_PRINTF are 1 based and if associated with
// a non-static method then they are 2 based (to account for the additional 'this' parameter).
//
// Use a value of 0 for FIRSTINDEX if the arguments are not available at compile time. For instance
// if your method takes a va_list argument. In this case the compiler will check the format string
// for consistency.
//
#ifdef __GNUC__

#define PRIME_ATTRIBUTE_PRINTF(STRINDEX, FIRSTINDEX) \
__attribute__ ((format (printf, STRINDEX, FIRSTINDEX)))

#else // __GNUC__

#define PRIME_ATTRIBUTE_PRINTF(STRINDEX, FIRSTINDEX)

#endif // !__GNUC__


#if SEXY_IS_REPORTING_ENABLED

#	define SEXY_ASSERT(inExpr) PRIME_ASSERT(inExpr)
#	define SEXY_ASSERTM(inExpr, ...) PRIME_ASSERTM(inExpr, __VA_ARGS__)

#	define SEXY_FATAL(...) PRIME_FATAL(__VA_ARGS__)
#	define SEXY_ERROR(...) PRIME_ERROR(__VA_ARGS__)
#	define SEXY_WARN(...)  PRIME_WARN(__VA_ARGS__)
#	define SEXY_INFO(...)  PRIME_INFO(__VA_ARGS__)
#	define SEXY_ERROR_NO_ENTRY() PRIME_ERROR_NO_ENTRY()
#	define SEXY_VERIFY(inExpr) for (;;) { bool v = (inExpr); PRIME_ASSERT(v); break; }
#	define SEXY_VERIFYM(inExpr, ...) for (;;) { bool v = (inExpr); PRIME_ASSERTM(v, __VA_ARGS__); break; }
#else //!SEXY_IS_REPORTING_ENABLED
#	define SEXY_ASSERT(inExpr)
#	define SEXY_ASSERTM(inExpr, ...)
#	define SEXY_FATAL(...)
#	define SEXY_ERROR(...)
#	define SEXY_WARN(...)
#	define SEXY_INFO(...)
#	define SEXY_ERROR_NO_ENTRY()
#	define SEXY_VERIFY(inExpr) for (;;) { bool x = (inExpr); (void)x; break; }
#	define SEXY_VERIFYM(inExpr, ...) SEXY_VERIFY(inExpr)
#endif //!SEXY_IS_REPORTING_ENABLED

#if PRIME_IS_REPORTING_ENABLED || PRIME_IS_ASSERT_ENABLED
namespace Sexy
{
    enum ERptUserChoice
    {
        RPT_UC_Continue,
        RPT_UC_BreakIntoDebugger,
    };
    
    enum ERptFormatFlag
    {
        RPT_FORMAT_No,
        RPT_FORMAT_Yes,
    };
    
    enum ERptInstanceType
    {
        PRIME_BEGIN_ENUM(RPT_T_),
        RPT_T_Log,
        RPT_T_Assert,
        RPT_T_Warning,
        RPT_T_Error,
        RPT_T_Fatal,
        PRIME_END_ENUM(RPT_T_)
    };
    
    enum RptCategoryType
    {
        PRIME_BEGIN_ENUM(RPT_Category_),
        RPT_Category_Normal,
        RPT_Category_Content,
        RPT_Category_Critical,
        PRIME_END_ENUM(RPT_Category_)
    };
    
    //	Type of fatal call if using PRIME_FATAL(...)
    enum EFatal
    {
        PRIME_BEGIN_ENUM(EFatal_),
        EFatal_FileIO,
        EFatal_Memory,
        EFatal_GraphicsMemory,
        EFatal_Audio,
        EFatal_Other,
        PRIME_END_ENUM(EFatal_),
    };
    
    //Defined in ReportingManager.cpp
    const char* ToString(ERptInstanceType i_value, bool i_errorOnFail = true);
    
    
    // This structure holds whatever we know about the location of the failure,
    // both structurally in code and physically in memory.
    //
    struct SRptInstanceLocationSpec
    {
        const char* Function;
        const char* File;
        int32			Line;
        
        SRptInstanceLocationSpec(
                                 const char* i_function = NULL,
                                 const char* i_file = NULL,
                                 int32			i_line = 0)
        {
            Function		= i_function;
            File			= i_file;
            Line			= i_line;
        }
    };
    
    // This holds whatever static content is stored per instance.
    //
    
    class CRptInstanceStaticSpec
    {
    public:
        CRptInstanceStaticSpec();
        
        // hit count
        int32				GetTotalHitCount() const {
            return m_totalHitCount; }
        void			IncrementHitCount() {
            ++m_hitCount; ++m_totalHitCount; }
        
        // ignoring
        void			SetIgnoringAlways() {
            m_ignoringAlways = true;}
        bool			IsIgnoringAlways() const {
            return m_ignoringAlways; }
        
    private:
        int32								m_hitCount;					// times this instance has been hit (regardless of when ignored) since last reset
        int32								m_totalHitCount;			// total times this instance has been hit ever
        bool								m_ignoringAlways;			// If the instance is being ignored
        CRptInstanceStaticSpec*             m_nextInList;				// singly linked list to track all currently active report instances (constructed on demand)
        
        static CRptInstanceStaticSpec*	s_listRoot;
    };
    
    // This structure is meant to contain all the params that can be passed into
    // any of the reporting macros (including implicit stuff such as PRIME_ASSERT
    // uses the instance type RPT_T_Assert).
    //
    struct SRptInstanceCallSpec
    {
        ERptInstanceType		InstanceType;
        RptCategoryType         CategoryType;	// Category of message (normal or content)
        const char* 			Expression;		// the expression that generated the report (if available, such as from an assert)
        ERptFormatFlag			FormatFlag;		// if should run sprintf on the message (RPT_FORMAT_No if caller wants pass-through)
        const char* 			Message;		// optionally formatted message (optional)
        va_list					MessageArgs;	// args to pass into sprintf (optional)
        bool					MessageEol;		// terminate message with end of line
        const char* 			Stack;		// optionally formatted message (optional)
        
        // core initializer - need to have this function call the report otherwise
        // we lose the printf args off the stack. meaning, if we construct the
        // spec then call the reporting mgr with it and the other params, the
        // __VA_ARGS__ are gone. so have to nest calls.
        //
        ERptUserChoice Report(
                              CRptInstanceStaticSpec&			io_staticSpec,
                              const SRptInstanceLocationSpec& i_locationSpec,
                              ERptInstanceType				i_instanceType,
                              bool							i_messageEol,
                              RptCategoryType                   i_categoryType,
                              const char* 					i_expression,
                              ERptFormatFlag					i_formatFlag,
                              const char* 					i_message,
                              va_list							i_messageArgs);  // too complicated to put an PRIME_ATTRIBUTE_PRINTF() here..
        
        // CAUTION: DO NOT STARE DIRECTLY AT THIS CODE WHILE SOBER!
        //
        // the overloads here are so we can fake overloaded macros through
        // __VA_ARGS__ using these methods as selectors. i'm doing this goofy
        // #define stuff to get all the combinations without going cross eyed
        // matching up params and defaults and stuff.
        //
        // this breaks coding conventions in a few ways. sorry!
        //
#	define PREFIXC	io_staticSpec, i_locationSpec, i_instanceType, i_messageEol
#	define PREFIXP	CRptInstanceStaticSpec& io_staticSpec, const SRptInstanceLocationSpec& i_locationSpec, ERptInstanceType i_instanceType, bool i_messageEol
#	define FFLAG0C  RPT_FORMAT_Yes
#	define FFLAG1P  , ERptFormatFlag i_formatFlag
#	define FFLAG1C  i_formatFlag
#	define CATEGRP  , RptCategoryType i_categoryType
#	define CATEGRC  i_categoryType
#	define MSG0C	NULL, NULL
#	define MSG1P	, const char* i_message, ...
        ERptUserChoice ReportGeneral(PREFIXP /*4*/                           )                            { return Report(PREFIXC, RPT_Category_Normal, NULL, FFLAG0C, MSG0C); }
        ERptUserChoice ReportGeneral(PREFIXP /*4*/               MSG1P /*1+*/) PRIME_ATTRIBUTE_PRINTF(6, 7)
        {
            //LCS_VA_ARGS workaround
            va_list arg_list;
            va_start(arg_list, i_message);
            return Report(PREFIXC, RPT_Category_Normal, NULL, FFLAG0C, i_message, arg_list);
        }
        ERptUserChoice ReportGeneral(PREFIXP /*4*/ FFLAG1P /*1*/             )                            { return Report(PREFIXC, RPT_Category_Normal, NULL, FFLAG1C, MSG0C); }
        ERptUserChoice ReportGeneral(PREFIXP /*4*/ FFLAG1P /*1*/ MSG1P /*1+*/) PRIME_ATTRIBUTE_PRINTF(7, 8)
        {
            //LCS_VA_ARGS workaround
            va_list arg_list;
            va_start(arg_list, i_message);
            return Report(PREFIXC, RPT_Category_Normal, NULL, FFLAG1C, i_message, arg_list);
        }
        ERptUserChoice ReportGeneral(PREFIXP /*4*/ CATEGRP                   )                            { return Report(PREFIXC, CATEGRC, NULL, FFLAG0C, MSG0C); }
        ERptUserChoice ReportGeneral(PREFIXP /*4*/ CATEGRP       MSG1P /*1+*/) PRIME_ATTRIBUTE_PRINTF(7, 8)
        {
            //LCS_VA_ARGS workaround
            va_list arg_list;
            va_start(arg_list, i_message);
            return Report(PREFIXC, CATEGRC, NULL, FFLAG0C, i_message, arg_list);
        }
        ERptUserChoice ReportGeneral(PREFIXP /*4*/ CATEGRP FFLAG1P /*1*/             )                            { return Report(PREFIXC, CATEGRC, NULL, FFLAG1C, MSG0C); }
        ERptUserChoice ReportGeneral(PREFIXP /*4*/ CATEGRP FFLAG1P /*1*/ MSG1P /*1+*/) PRIME_ATTRIBUTE_PRINTF(8, 9)
        {
            //LCS_VA_ARGS workaround
            va_list arg_list;
            va_start(arg_list, i_message);
            return Report(PREFIXC, CATEGRC, NULL, FFLAG1C, i_message, arg_list);
        }
#	undef PREFIXC
#	undef PREFIXP
#	undef FFLAG0C
#	undef FFLAG1P
#	undef FFLAG1C
#	undef MSG0C
#	undef MSG1P
        
        // assert requires a special set as it uses expr, plus we can assume some other args
        ERptUserChoice ReportAssert(CRptInstanceStaticSpec& io_staticSpec, const SRptInstanceLocationSpec& i_locationSpec, const char* i_expression, RptCategoryType i_categoryType, ERptFormatFlag i_formatFlag, const char* i_message, ...) PRIME_ATTRIBUTE_PRINTF(7, 8)
        {
            //LCS_VA_ARGS workaround
            va_list arg_list;
            va_start(arg_list, i_message);
            return Report(io_staticSpec, i_locationSpec, RPT_T_Assert, 1, i_categoryType, i_expression, i_formatFlag, i_message, arg_list);
        }
        ERptUserChoice ReportAssert(CRptInstanceStaticSpec& io_staticSpec, const SRptInstanceLocationSpec& i_locationSpec, const char* i_expression, ERptFormatFlag i_formatFlag, const char* i_message, ...) PRIME_ATTRIBUTE_PRINTF(6, 7)
        {
            //LCS_VA_ARGS workaround
            va_list arg_list;
            va_start(arg_list, i_message);
            return Report(io_staticSpec, i_locationSpec, RPT_T_Assert, 1, RPT_Category_Normal, i_expression, i_formatFlag, i_message, arg_list);
        }
        ERptUserChoice ReportAssert(CRptInstanceStaticSpec& io_staticSpec, const SRptInstanceLocationSpec& i_locationSpec, const char* i_expression, const char* i_message, ...)
        {
            //LCS_VA_ARGS workaround
            va_list arg_list;
            va_start(arg_list, i_message);
            return Report(io_staticSpec, i_locationSpec, RPT_T_Assert, 1, RPT_Category_Normal, i_expression, RPT_FORMAT_Yes, i_message, arg_list);
        }
        ERptUserChoice ReportAssert(CRptInstanceStaticSpec& io_staticSpec, const SRptInstanceLocationSpec& i_locationSpec, const char* i_expression, RptCategoryType i_categoryType, const char* i_message, ...) PRIME_ATTRIBUTE_PRINTF(6, 7)
        {
            //LCS_VA_ARGS workaround
            va_list arg_list;
            va_start(arg_list, i_message);
            return Report(io_staticSpec, i_locationSpec, RPT_T_Assert, 1, i_categoryType, i_expression, RPT_FORMAT_Yes, i_message, arg_list);
        }
        ERptUserChoice ReportAssert(CRptInstanceStaticSpec& io_staticSpec, const SRptInstanceLocationSpec& i_locationSpec, const char* i_expression)
        {
            return Report(io_staticSpec, i_locationSpec, RPT_T_Assert, 1, RPT_Category_Normal, i_expression, RPT_FORMAT_No, NULL, NULL);
        }
        ERptUserChoice ReportAssert(CRptInstanceStaticSpec& io_staticSpec, const SRptInstanceLocationSpec& i_locationSpec, const char* i_expression, RptCategoryType i_category)
        {
            return Report(io_staticSpec, i_locationSpec, RPT_T_Assert, 1, i_category, i_expression, RPT_FORMAT_No, NULL, NULL);
        }
    };
    
    const char* GetCategoryName(const SRptInstanceCallSpec& i_callSpec);
} //namespace Sexy

#if PRIME_IS_WII || PRIME_IS_PS3
#define PRIME_RPT_FUNCTION_NAME __PRETTY_FUNCTION__
#else
#define PRIME_RPT_FUNCTION_NAME __FUNCTION__
#endif

// Reporter function which handles error/ignore counting.
// Everything is wrapped in the safe macro (do-while loop) so that it can be used as a function and avoid the macro quirk of disrupting flow if
// used in an if-else block.
#   define PRIME_REPORT_CORE(i_file, i_line, i_method_name, ...)                        \
PRIME_SAFE_MACRO_BEGIN()                                                            \
Sexy::SRptInstanceLocationSpec locSpec(PRIME_RPT_FUNCTION_NAME,                       \
i_file, i_line);                                                            \
/*Do report*/                                                                   \
static Sexy::CRptInstanceStaticSpec s_StaticSpec;                                     \
if (Sexy::SRptInstanceCallSpec().i_method_name(s_StaticSpec, locSpec, __VA_ARGS__)    \
== Sexy::RPT_UC_BreakIntoDebugger)                                                \
{                                                                               \
/*Trigger break point to stop at point of failure*/                         \
PRIME_BREAKPOINT();                                                         \
}                                                                               \
PRIME_SAFE_MACRO_END()

#define PRIME_REPORT_BASE(i_methodName, ...)                                            \
PRIME_REPORT_CORE(__FILE__, __LINE__, i_methodName, __VA_ARGS__)

#endif //PRIME_IS_REPORTING_ENABLED || defined PRIME_IS_ASSERT_ENABLED

#if PRIME_IS_ASSERT_ENABLED

//Assertion macros
#   define PRIME_ASSERT(i_expression)                                                   \
PRIME_SAFE_MACRO_BEGIN()                                                        \
if (!(i_expression))                                                            \
PRIME_REPORT_BASE(ReportAssert, #i_expression)                              \
PRIME_SAFE_MACRO_END()

#   define PRIME_ASSERTM(i_expression, ...)                                             \
PRIME_SAFE_MACRO_BEGIN()                                                        \
if (!(i_expression))                                                            \
PRIME_REPORT_BASE(ReportAssert, #i_expression, __VA_ARGS__)                 \
PRIME_SAFE_MACRO_END()
#else //!PRIME_WANTS_ASSERTS_ENABLED
#   define PRIME_ASSERT(...) PRIME_SAFE_MACRO_UNIMPLEMENTED()
#   define PRIME_ASSERTM(...) PRIME_SAFE_MACRO_UNIMPLEMENTED()
#endif //PRIME_WANTS_ASSERTS_ENABLED

#if PRIME_IS_REPORTING_ENABLED
#define PRIME_WARN(...)					PRIME_SAFE_MACRO_BEGIN()    PRIME_REPORT_BASE(ReportGeneral, Sexy::RPT_T_Warning, true, __VA_ARGS__) PRIME_SAFE_MACRO_END()
#define PRIME_ERROR(...)				PRIME_SAFE_MACRO_BEGIN()	PRIME_REPORT_BASE(ReportGeneral, Sexy::RPT_T_Error, true, __VA_ARGS__)   PRIME_SAFE_MACRO_END()
#define PRIME_CONTENT_ERROR(...)		PRIME_SAFE_MACRO_BEGIN()	PRIME_REPORT_BASE(ReportGeneral, Sexy::RPT_T_Error, true, Sexy::RPT_Category_Content, __VA_ARGS__)   PRIME_SAFE_MACRO_END()
#define PRIME_CRITICAL_ERROR(...)		PRIME_SAFE_MACRO_BEGIN()	PRIME_REPORT_BASE(ReportGeneral, Sexy::RPT_T_Error, true, Sexy::RPT_Category_Critical, __VA_ARGS__)   PRIME_SAFE_MACRO_END()
#define PRIME_INFO(...)                 PRIME_SAFE_MACRO_BEGIN()    PRIME_REPORT_BASE(ReportGeneral, Sexy::RPT_T_Log, true, __VA_ARGS__)     PRIME_SAFE_MACRO_END()
#define PRIME_FATAL(fatalKind, ...)		PRIME_SAFE_MACRO_BEGIN()	PRIME_REPORT_BASE(ReportGeneral, Sexy::RPT_T_Fatal, true, __VA_ARGS__)   PRIME_SAFE_MACRO_END()

// Specialized errors.
//
// Use this for code paths that aren't supposed to be run. For example, if you
// are switching on an enum, the 'default' case may be a good place to put an
// PRIME_ERROR_NO_ENTRY to catch when people pass in bad values for the enum.
//
#define PRIME_ERROR_NO_ENTRY()         PRIME_SAFE_MACRO_BEGIN()  PRIME_ERROR("Code execution shouldn't get here! Tell an engineer.") PRIME_SAFE_MACRO_END()
//
// Use this for functions that haven't been implemented yet to make sure people
// don't call them, but to still provide an empty implementation so the thing
// compiles. The parameters to this macro can be the same as the parameters to
// the non-implemented function, in order to prevent unreferenced parameter
// warnings.
//
#define PRIME_ERROR_NOT_IMPLEMENTED(...) for (;;) { PRIME_ERROR("This function isn't implemented! Tell an engineer."); break; }

namespace Sexy
{
    void ReportingMgr_Update();
}

#else // !PRIME_IS_REPORTING_ENABLED
#define PRIME_WARN(...) PRIME_SAFE_MACRO_UNIMPLEMENTED()
#define PRIME_ERROR(...) PRIME_SAFE_MACRO_UNIMPLEMENTED()
#define PRIME_CONTENT_ERROR(...) PRIME_SAFE_MACRO_UNIMPLEMENTED()
#define PRIME_CRITICAL_ERROR(...) PRIME_SAFE_MACRO_UNIMPLEMENTED()
#define PRIME_INFO(...) PRIME_SAFE_MACRO_UNIMPLEMENTED()
#define PRIME_FATAL(fatalKind, ...) PRIME_SAFE_MACRO_UNIMPLEMENTED()
#define PRIME_ERROR_NO_ENTRY() PRIME_SAFE_MACRO_UNIMPLEMENTED()
#define PRIME_ERROR_NOT_IMPLEMENTED() PRIME_SAFE_MACRO_UNIMPLEMENTED()

namespace Sexy
{
    
    inline void ReportingMgr_Update()
    {
    }
    
} // namespace Sexy

#endif //PRIME_IS_REPORTING_ENABLED

#endif // __SEXYAPPFRAMEWORK_REPORTING_H__
