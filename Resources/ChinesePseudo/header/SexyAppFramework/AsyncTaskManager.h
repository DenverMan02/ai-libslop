#ifndef __SEXYAPPFRAMEWORK_ASYNCTASKMANAGER_H__
#define __SEXYAPPFRAMEWORK_ASYNCTASKMANAGER_H__

#include "CritSect.h"
#include "StructuredData.h"

#include <string>
#include <queue>
#include <list>

namespace Sexy
{

    class NetworkServiceManager;
    class NetworkServiceListener;
    class ResumableRequestInfo;

    // -----------------------------------------------------------------------
    // class IAsyncTask declaration
    // -----------------------------------------------------------------------
    
    class AsyncTaskQueue;
    
    class IAsyncNetworkTask
    {
    public:
        enum State
        {
            State_NotStarted,
            State_PendingRun, // has been chosen to run, but may not yet be executing it's Run() method (i.e. the task has been placed in a worker thread task list to be executed.
            State_Running,
            State_SuccessComplete,
            State_ErrorComplete,
        };
        
        IAsyncNetworkTask();
        virtual ~IAsyncNetworkTask();
        // NOT A GUARANTEED UNIQUE NAME!!!
        virtual std::string GetName();
        
        virtual void RunImpl() = 0;
        void Run();
                
        // This is used to put the task into a State_PendingRun state.
        // This indicates that while the task may not yet be running, it
        // how been commited to being run (e.g. placed on a worker thread queue)
        // and it should not be deleted until it completes.
        void SetPendingRunState();
        
        virtual bool IsMainThreadTask() = 0;
        
        // This will be called on the MAIN THREAD if a task prior to this one errored.
        // This method gives tasks a chance to perform any cleanup they may need to do if they
        // will not be run because other tasks before them errored.
        virtual void OnPriorTaskError() {}
        
        // Safe to call from any thread        
        State GetState() const; // $$$ (avy) consider making this private and providing wrapper queries such as IsReservedForRunning() since there are many places where outside callers are testing for combinations of states.

        // Safe to call from any thread
        virtual void SetParentQueue( AsyncTaskQueue* theParentQueue );
        
        // Devived classes that implement these must do so in a thread safe way
        virtual bool IsErrorReportingTask() const;
        virtual bool IsQueueSuccessTask() const;

    protected:
        // Safe to call from any thread
        virtual void    notifyTaskError(IAsyncNetworkTask* inErrorTask);
        
        // Safe to call from any thread
        virtual void    setState(State inNewState);
        
        // Safe to call from any thread
        std::string     getParentQueueName() const;
        
        std::string         mTaskName;
        
        
    private:
        mutable CritSect    mLock;
        AsyncTaskQueue*     mParentQueue;
        State               mState; // $$$$ (avy) protect for multiple threads?
    };
    
    // -----------------------------------------------------------------------
    // class AsyncMainThreadTask declaration
    // -----------------------------------------------------------------------
    
    class AsyncMainThreadTask : public IAsyncNetworkTask
    {
    public:
        //
        // IAsyncTask
        //
        virtual bool IsMainThreadTask() { return true; }
    };
    
    // -----------------------------------------------------------------------
    // class AsyncThreadedTask declaration
    // -----------------------------------------------------------------------
    
    class AsyncThreadedTask : public IAsyncNetworkTask
    {
    public:
        //
        // IAsyncTask
        //
        virtual bool IsMainThreadTask() { return false; }
    };
    
    // -----------------------------------------------------------------------
    // class AsyncTaskQueue declaration
    // -----------------------------------------------------------------------
    
    class AsyncTaskQueue : public IAsyncNetworkTask
    {
    public:
        AsyncTaskQueue( const std::string& theQueueName );
        virtual ~AsyncTaskQueue();
        
        void                        RemoveTask();
        void                        RemoveCompletedTasks();
        
        void                        QueueFinished();
        
        // Returns true if either the queue is currently empty or if the queue has entered a terminal state (error or success)
        bool                        IsQueueEmpty() const;

        void                        Clear();
        
        const std::queue< IAsyncNetworkTask* >& GetTasks() const;
        std::queue< IAsyncNetworkTask* >& GetTasks();
        
        IAsyncNetworkTask*          GetNextTask();
        
        //
        // IAsyncTask
        //
        virtual void                RunImpl();
        virtual bool                IsMainThreadTask();
        
        //
        // AsyncTaskQueue
        //
        
        virtual bool                HasPendingErrorTask() const;
        
        // Called by AsyncTaskManager to ensure unrun tasks get a chance to cleanup if a prior task errored.
        void                        NotifyPendingTasksOfError();
        
        // Call only if HasPendingErrorTask() == true
        // Must call NotifyPendingTasksOfError() prior to calling this method.
        virtual IAsyncNetworkTask*  GetPendingErrorTask();

        //
        // Call only from main thread
        //
        
        virtual void                Update();
        
        //
        // The following methods are safe to call from any thread.
        //
        
        // by calling AddTask, the AsyncTaskQueue now owns the task
        void                        AddTask( IAsyncNetworkTask* inTask );
        void                        AddErrorTask( IAsyncNetworkTask* inErrorTask );

    private:
        // Must only be called from main thread.
        void addPendingTasks();
        
        std::queue< IAsyncNetworkTask* >    mTasks;
        
        mutable CritSect                    mLock;
        std::queue<IAsyncNetworkTask*>      mPendingTaskAdds;
        bool                                mHasPendingErrorTask;
    };
    
    // -----------------------------------------------------------------------
    // class AsyncTaskManager declaration
    // -----------------------------------------------------------------------
    
    class AsyncTaskManager
    {
    public:
		static AsyncTaskManager* DefaultAsyncTaskManager();
        AsyncTaskManager();
        virtual ~AsyncTaskManager();
        
        // $$$ (avy) I'm not sure it's good to use the queue names as our handle to finding the queue later.
        AsyncTaskQueue* GetQueueByName( const std::string& theTaskQueueName ) const;
        AsyncTaskQueue* CreateQueue( const std::string& theTaskQueueName );
        void AddTaskToQueue( IAsyncNetworkTask* const theTask, const std::string& theTaskQueueName );
        void AddTaskToQueue( IAsyncNetworkTask* const theTask, AsyncTaskQueue* const theQueue );
        void RequestQueueDelete( AsyncTaskQueue* inTaskQueueToDelete );
        
        bool IsQueueEmpty(const std::string& theTaskQueueName) const;
        
        void Update();
        
    private:
        bool moveToNextQueue();
        bool moveToPrevQueue();
        
        void addWorkerThreadTask(IAsyncNetworkTask* inWorkerThreadTask);
        
        void startWorkerThread();
        void stopWorkerThread();
        
        // $ called only on the worker thread
        static void workerThreadProc(void *inUntypedAsyncTaskManagerPtr);
        
        // $ called only on the worker thread
        void workerThreadMainLoop();
        

        std::list< AsyncTaskQueue* >            mQueues;
        std::list< AsyncTaskQueue* >::iterator  mLastQueueServiced;
        
        std::list< IAsyncNetworkTask* >         mWorkerThreadTasks;

        Sexy::CritSect  mWorkerThreadQueueLock;
        Sexy::Condition mWorkerThreadTasksAvailableEvent;
    };
    
    // -----------------------------------------------------------------------
    // class AsyncCreateFileOfSizeTask declaration
    // -----------------------------------------------------------------------
    
    class AsyncCreateFileOfSizeTask : public AsyncThreadedTask
    {
    public:
        AsyncCreateFileOfSizeTask( ResumableRequestInfo* const theRequestInfo, NetworkServiceListener* const theNSL, const void* theContext, const std::string& theFilePath, const unsigned long theDataLen );
        virtual ~AsyncCreateFileOfSizeTask();
        //
        // IAsyncTask
        //
        virtual void RunImpl();
        
    private:
        ResumableRequestInfo*   mResumableRequestInfo;
        NetworkServiceListener* mNSL;
        const void*             mContext;
        std::string             mFilePath;
        unsigned long           mDataLen;
    };
    
    // -----------------------------------------------------------------------
    // class AsyncWriteBytesToFileAtTask declaration
    // -----------------------------------------------------------------------
    
    class AsyncWriteBytesToFileAtTask : public AsyncThreadedTask
    {
    public:
        AsyncWriteBytesToFileAtTask( ResumableRequestInfo* const theRequestInfo, NetworkServiceListener* const theNSL, const void* theContext, const std::string& theFilePath, Buffer* theBuffer );
        virtual ~AsyncWriteBytesToFileAtTask();

        //
        // IAsyncTask
        //
        virtual void RunImpl();
        
    private:
        ResumableRequestInfo*   mResumableRequestInfo;
        NetworkServiceListener* mNSL;
        const void*             mContext;
        std::string             mFilePath;
        unsigned long           mStartAtOffset;
        Buffer*                 mBuffer;
    };
    
    // -----------------------------------------------------------------------
    // class AsyncFinalizeResumeRequestTask declaration
    // -----------------------------------------------------------------------
    
    class AsyncFinalizeResumeRequestTask : public AsyncThreadedTask
    {
    public:
        AsyncFinalizeResumeRequestTask( NetworkServiceManager* const theNSM, ResumableRequestInfo* const theRequestInfo, NetworkServiceListener* const theNSL, const void* theContext );
        virtual ~AsyncFinalizeResumeRequestTask();

        //
        // IAsyncTask
        //
        virtual void RunImpl();
        
    private:
        NetworkServiceManager*  mNSM;
        ResumableRequestInfo*   mResumableRequestInfo;
        NetworkServiceListener* mNSL;
        const void*             mContext;
    };
    
    // -----------------------------------------------------------------------
    // class AsyncResumeRequestErrorTask declaration
    // -----------------------------------------------------------------------
    
    class AsyncResumeRequestErrorTask : public AsyncMainThreadTask
    {
    public:
        AsyncResumeRequestErrorTask( ResumableRequestInfo* inResumableRequestInfo, NetworkServiceListener* const theNSL, const void* theContext, const int inErrorNumEnum );
        virtual ~AsyncResumeRequestErrorTask();

        virtual bool IsErrorReportingTask() const;

        //
        // IAsyncTask
        //
        virtual void RunImpl();
        
    private:
        ResumableRequestInfo*   mResumableRequestInfo;
        NetworkServiceListener* mNSL;
        const void*             mContext;
        int                     mErrorID;
        std::string             mErrorMessage;
    };
    
    // -----------------------------------------------------------------------
    // class AsyncRemakeRequestTask declaration
    // -----------------------------------------------------------------------
    
    class AsyncRemakeRequestTask : public AsyncMainThreadTask
    {
    public:
        AsyncRemakeRequestTask( ResumableRequestInfo* const theRequestInfoToDelete, NetworkServiceListener* const theNSL, const void* theContext );
        virtual ~AsyncRemakeRequestTask();

        //
        // IAsyncTask
        //
        bool            IsQueueSuccessTask() const;
        virtual void    RunImpl();
        virtual void    OnPriorTaskError();
        
    private:
        ResumableRequestInfo*   mResumableRequestInfoToDelete;
        NetworkServiceListener* mNSL;
        const void*             mContext;
    };
    
    // -----------------------------------------------------------------------
    // class AsyncDeletePartialFilesTask declaration
    // -----------------------------------------------------------------------
    
    class AsyncDeletePartialFilesTask : public AsyncThreadedTask
    {
    public:
        AsyncDeletePartialFilesTask( ResumableRequestInfo* const theRequestInfo );
        virtual ~AsyncDeletePartialFilesTask();

        //
        // IAsyncTask
        //
        virtual void RunImpl();
        
    private:
        ResumableRequestInfo*   mResumableRequestInfo;
    };
    
    // -----------------------------------------------------------------------
    // class AsyncQueueCompletedSuccessfullyTask declaration
    // -----------------------------------------------------------------------
    
    class AsyncQueueCompletedSuccessfullyTask : public AsyncMainThreadTask
    {
    public:
        AsyncQueueCompletedSuccessfullyTask( ResumableRequestInfo* theRequestInfoToDelete, NetworkServiceListener* const theNSL, const void* theContext );
        virtual ~AsyncQueueCompletedSuccessfullyTask();
        
        virtual bool IsQueueSuccessTask() const;
        
        //
        // IAsyncTask
        //
        virtual void RunImpl();
        virtual void OnPriorTaskError();
        
    private:
        NetworkServiceListener* mNSL;
        ResumableRequestInfo*   mResumableRequestInfoToDelete;
        const void*             mContext;
    };
    
    // -----------------------------------------------------------------------
    // class AsyncDeleteResumeRequestInfoTask declaration
    // -----------------------------------------------------------------------
    /*
    class AsyncDeleteResumeRequestInfoTask : public AsyncMainThreadTask
    {
    public:
        AsyncDeleteResumeRequestInfoTask( ResumableRequestInfo*  theRequestInfoToDelete );
        virtual ~AsyncDeleteResumeRequestInfoTask();
        
        virtual bool IsQueueSuccessTask() const;
        
        //
        // IAsyncTask
        //
        virtual void RunImpl();
        virtual void OnPriorTaskError();
        
    private:
        ResumableRequestInfo*   mResumableRequestInfoToDelete;
    };
    */
    
    
    // This "safe" error task will run on the main thread, won't mark the queue as having an error, and is primarily used by the NSM's
    // HttpTransactionError function to report an http error to the requester
    // TIM TODO: implement this when you have time
//    // -----------------------------------------------------------------------
//    // class AsyncSafeErrorTask declaration
//    // -----------------------------------------------------------------------
//    
//    class AsyncSafeErrorTask : public AsyncMainThreadTask
//    {
//    public:
//        AsyncSafeErrorTask( NetworkServiceListener* const theNSL, const void* theContext, const std::string& error );
//        virtual ~AsyncSafeErrorTask();
//                
//        //
//        // IAsyncTask
//        //
//        virtual void RunImpl();
//        
//    private:
//        NetworkServiceListener* mNSL;
//        const void*             mContext;
//        std::string             mErrorMessage;
//    };
    
    // -----------------------------------------------------------------------
    //                       END ASYNC TASK DECLARATIONS
    // -----------------------------------------------------------------------

#if defined(WANTS_ASYNCTASKMANAGER_TEST)
    class AsyncTaskManagerTest
    {
    public:
        void StartTest();
        void Update();
    private:
    };
#endif
}

#endif // __SEXYAPPFRAMEWORK_ASYNCTASKMANAGER_H__
