///////////////////////////////////////////////////////////////////////////////
// TestThread.h
//
// Copyright(c) 2011, Electronic Arts Inc. All rights reserved.
//
// Created by Paul Pedriana
///////////////////////////////////////////////////////////////////////////////


#ifndef TESTTHREAD_H
#define TESTTHREAD_H


extern unsigned int gTestLengthSeconds;


int TestThreadSync();
int TestThreadAtomic();
int TestThreadCallstack();
int TestThreadStorage();
int TestThreadSpinLock();
int TestThreadRWSpinLock();
int TestThreadFutex();
int TestThreadMutex();
int TestThreadRWMutex();
int TestThreadSemaphore();
int TestThreadCondition();
int TestThreadBarrier();
int TestThreadThread();
int TestThreadThreadPool();
int TestThreadSmartPtr();
int TestThreadFiber();
int TestThreadLockFree();
int TestThreadMisc();
int TestEnumerateThreads();

#endif // Header include guard


