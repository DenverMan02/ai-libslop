#ifndef __RESUMEREQUESTINFO_H__
#define __RESUMEREQUESTINFO_H__

#include "Common.h"

#include "AutoCrit.h"
#include "Buffer.h"
#include "StructuredData.h"

namespace Sexy
{
    class NetworkServiceManager;
    class NetworkServiceListener;
    class IHttpTransaction;
    struct NetworkServiceRequest;
    
    // $$$ (avy) Add a key to structured data request for number of retries.
    // $$$ (avy) Also key for expected download file size so cache file can be created before starting http request.
    // $$$ (avy) Add cache file cleanup to NetworkServiceManager::Update()/Init().
    // $$$ (avy) formalize errors that can be reported back to NetworkServiceListener (add "error_num" key to structured data), clearly identify which errors can be fixed by the caller.
    
    // Moving these structs here to make them visible to the Async tasks in the NetworkServiceManager.cpp file
    class ResumableRequestInfo
    {
    public:
        ResumableRequestInfo(const StructuredData& inHttpRequestData, uint32 inDiskBufferSize, const std::string& inTargetFilePath, int inResumePosm, bool inUseIfRangeHeader = true);
        virtual ~ResumableRequestInfo();
        
        //
        // Methods callable only from the main thread
        //
        
        void Prepare(NetworkServiceManager* inNetworkManager, const std::string& inUrl);
        
        void HandleReceivedResponse( NetworkServiceListener* listener, const void* context, std::string& RH_contentRange, std::string& RH_lastModified, int statusCode, int responseLength );
        
        // Returns true if the data was able to be recieved.
        // If false is returned, then we are getting backed up by pending file write tasks and the caller must cancel the current http request, HandleReceivedData will already have added a RemakeRequestTask to the queue.
        void HandleReceivedData(void* data, size_t dataLength );
        
        // If this returns false, then treat this like a "http fail", not "http complete"
        bool HandleHttpComplete(NetworkServiceManager* inNetworkManager);
        
        void AllocateBuffers( unsigned long bufferSize );
        bool SwapBuffers();
        
        void RemakeRequest(NetworkServiceManager* inNetworkManager, NetworkServiceListener* inListener, const void* inContext);

        void ResumeRequestError( NetworkServiceListener* nsl, const void* context, const int inErrorNumEnum );

        void DispatchProgressNotification(NetworkServiceListener* inListener, const void* inContext);
        
        void MarkQueueForDelete();
                
        //
        // Methods that can be called from any thread
        //
        
        // Call this when the http request response is first recieved. If the status code is not valid
        // for a resumable download, then convert the request into a non-resumable download.
        bool IsValidResumableDownloadHttpStatus(int inHttpStatusCode);
        
        
        static const std::string GetResumeCachedFolder( );
        
        bool IsBufferWriting( const Buffer* inBuffer );
        void SetIsBufferWriting( const Buffer* inBuffer, bool inIsWriting );
        
        std::string GetTargetFilePath() const;
        std::string GetCachedFileName() const;

        static bool ReadResumeFile( const std::string& requestInfoFilename, int& fileResumePos, std::string& fileLastModified );
        bool SaveResumeRequestData();
        
        bool FinalizeResumeRequest( NetworkServiceListener* nsl, const void* context );
        bool DeletePartialFiles();
        
        int GetPos();
        void IncrPos(int inDelta); // $$$ (avy) should find a way to make this private (could make IncrPos and SaveResumeRequestData private, then make a public method that calls both).
        void ClearPos(); // $$$ (avy) would be nice for this to be private too

        // If this ResumableRequestInfo instand is still bound to/owned-by a parent request
        // then this will mark the parent request for cancellation and take ownership of
        // the ResumableRequestInfo from the parent request and return it to the caller.
        // The caller will own the ResumeRequestInfo and is responsible for deleting it.
        //
        // Will return NULL if the current ResumeRequestInfo is not owned by a parent request.
        // This means that someone else has already taken ownership of it and will handle deleting it.
        //
        // $$$$ (avy) Danger! A success task may have taken ownership of the resumeinfo and then an
        // error may occur. And error task will be given a pointer to the resumeinfo and when it runs
        // it will try to take ownership of it which will fail because the success task has already done so.
        // The danger is in the order that OnPriorError() is called. If it is called before running the
        // error task then the resumeinfo pointer in the error task will be invalid.
        // If OnPriorError() is called after the error task runs, then other tasks like WriteBytesToFileTask may attempt to use their resumeinfo pointer to clear the IsWritting flag on their buffer, but resumeinfo will be invalid at that point too.
        //
        // $$$$ (avy) will errors tasks that mark a request as cancelled, really cause the request to be canceled? What if an error task is generated by a task that was put in the queue by HandleHttpComplete? ... this should be ok, because the request will be removed/canceled at then end of HttpTransactionComplete().  Verify that this is also true for HttpTransactionError(). For HttpRecievedData() will need to check for a request being marked for cancellation early before calling HandleDataReceived()
        //
        // $$$$ (avy) need to check everywhere where this is being called. If NULL is returned and we were going to pass
        // the result to a task, need to consider not adding the task as this probably(?) means the another task has errored
        // and taken ownership already, we don't want to pass a null resumeinfo into a task.
        ResumableRequestInfo* TakeResumableInfoAndMarkForCancellation(bool inShouldNotifyListenerOnCancel);
        
        // This should only be called by NetworkServiceRequest's constructor,
        // or NetworkServiceRequest::TakeResumableInfoAndMarkForCancellation()
        void SetParentRequest(NetworkServiceRequest* inParentRequest);

        bool IsQueueEmpty() const;
    private:
        
        // Safe to call on any thread
        std::string getQueueName() const;
        
        // Safe to call on any thread
        void setLastModifiedTimeStamp(const std::string& inLastModifiedTimestamp);
        
        // Safe to call on any thread
        std::string getLastModifiedTimeStamp() const;
        
        // Safe to call on any thread
        NetworkServiceRequest* getParentRequest() const;
        
        StructuredData      mRequestParams;
        int32               mRequestId;
        bool                mUseIfRangeHeader;
        
        int64                 mLength;
        int32               mTotalBytesRecieved; // Number of bytes that have been written to the cache file plus number of bytes that have been recieved from the network. While there are pending WriteBytesToFile tasks, this value will run ahead of mPos.
        
        uint32              mDiskBufferSize;
        Buffer*             mBuffer1;
        Buffer*             mBuffer2;
        Buffer*             mCurrBuffer;
        
        // Do not access any of these members without protecting with mLock first.
        mutable CritSect    mLock;
        NetworkServiceRequest* mParentRequest;
        int32               mPos; // Number of bytes that have been writen to the cache file
        std::string         mTargetFilePath;
        std::string         mCachedFileName;
        std::string         mQueueName;
        std::string         mLastModifiedTimeStamp;
        bool                mIsWritingBuffer1;
        bool                mIsWritingBuffer2;
    };
    
} // end namespace Sexy

#endif //   __RESUMEREQUESTINFO_H__
