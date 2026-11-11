// StackWalk.h

#ifndef __STACKWALK_H__
#define __STACKWALK_H__

#ifdef ASSERTIONS_ENABLED

enum
{
	STACKWALK_MINI_STACK_FRAMES = 12,
};

class StackWalkMiniStack
{
public:
	int m_frameCount;
	uint32 m_frame[STACKWALK_MINI_STACK_FRAMES];
};

class TodMemoryTrace
{
public:
	TodMemoryTrace *m_next;
	TodMemoryTrace *m_prev;
	StackWalkMiniStack m_miniStack;
	int i_name;
	int m_bytes;
};

void StackWalkCaptureMiniStack(StackWalkMiniStack *i_miniStack, int i_skipFrames);
void StackWalkTraceMiniStack(StackWalkMiniStack *i_miniStack);
void StackWalkLogCurrentStack(int i_skipFrames);
#ifdef HOST_WINDOWS
void StackWalkLogExceptionStack(EXCEPTION_POINTERS *i_exceptionInfo);
#endif
void StackWalkShowMiniStack(StackWalkMiniStack *i_miniStack, bool i_logInsteadOfTrace, bool i_useExcelFormat);

void MemoryTraceAdd(TodMemoryTrace **i_traceHead, TodMemoryTrace *i_trace, int i_bytes);
void MemoryTraceRemove(TodMemoryTrace **i_traceHead, TodMemoryTrace *i_trace);
void MemoryTraceDetectLeaks(TodMemoryTrace *i_traceHead, const char *i_systemName);

#ifdef HOST_WINDOWS
void MiniDump(EXCEPTION_POINTERS *pExceptionInfo, const char *i_name);
#endif

#endif // ASSERTIONS_ENABLED

#endif // __STACKWALK_H__
