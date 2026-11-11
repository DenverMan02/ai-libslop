
#pragma once
#include "Common.h"

#include "AutoCrit.h"
#include "Buffer.h"
#include "StructuredData.h"
#include "IHttpDriver.h"
#include "ImageLib/ImageLib.h"
#include <queue>
#include <deque>
#include <map>


namespace Sexy
{
    
    class AsyncTaskManager;
    class ResumableRequestInfo;
    
	void AppendPathComponent( std::string& url, const char* path );
    bool IsPartialFile( const std::string& filename );
    bool IsOlderThan( const uint64 timeCutoff, const std::string& filePath );

	// -----------------------------------------------------------------------
	// class NetworkServiceListener declaration
	// -----------------------------------------------------------------------

	/**
	 * The listener will receive exactly one of these calls for each
	 * request made.  The response, image or buffer object is only valid
	 * for the duration of this call.  If the listener needs to save the
	 * response for later use, it must make a copy of it.
	 */
	class NetworkServiceListener
	{
	public:
        // Mimicking the HTTP error enums...
        // 1100s are "OK"s
        // 1200s are "Completed"s
        // 1300s are "Indeterminate"s
        // 1400s are "Error"s on the caller's end
        // 1500s are "Error"s on our end
        enum ErrorNum
        {
            SEXY_ENUM_BEGIN(ErrorNum_),
            ErrorNum_CouldNotCreateFile     = 1401,
            ErrorNum_CouldNotWriteToFile    = 1402,
            ErrorNum_FailedToCopyFile       = 1403,
            ErrorNum_BadTargetFilePath      = 1404,
            SEXY_ENUM_END(ErrorNum_)
        };
        
        virtual std::string ToString( ErrorNum inErrorNum )
        {
            switch(inErrorNum)
            {
                    // 1100s
                    
                    // 1200s
                    
                    // 1300s
                    
                    // 1400s
                case ErrorNum_CouldNotCreateFile:
                    return "could_not_create_file";
                    
                case ErrorNum_CouldNotWriteToFile:
                    return "could_not_write_to_file";
                    
                case ErrorNum_FailedToCopyFile:
                    return "failed_to_copy_file";
                    
                case ErrorNum_BadTargetFilePath:
                    return "target_file_path_is_empty_or_invalid";
                    
                    // 1500s
                    
                default:
                    SEXY_ERROR_NO_ENTRY();
                    return "unknown_error_num";
            }
        }

		/** Received a JSON request which was validated against a schema. */
		virtual void ServiceRequestValidated( const StructuredData* response, const void* context )
		{
			return ServiceRequestCompleted( response, context );
		}
		
		/** Received a text response of some kind, that may have been JSON,
		 *  or may have been wrapped in JSON, or may be an error report.
		 *  Further inspection is required.
		 */
		virtual void ServiceRequestCompleted( const StructuredData* response, const void* context ) = 0;
		
		/** Received and decoded an image response.  The image pointer is
		  * passed by reference and the receiver may delete it as long as
		  * the pointer is set to NULL.  Otherwise the caller will delete
		  * the image after the this call.
		  * 
		  */
		virtual void ServiceRequestCompleted( ImageLib::Image*& image, const void* context ) = 0;
		
		/** Received a binary data response (i.e. not an image, json, or text type). */
		virtual void ServiceRequestCompleted( const Buffer* buffer, const void* context ) = 0;
		
		/** Received a binary data response (i.e. not an image, json, or text type).
          * This request was a resumable download request and should be handled
          * differently than regular requests.
          */
		virtual void ServiceResumableRequestCompleted( const std::string& filePath, const void* context ) {};

		/** In progress handling a resumable request
         * The current progress is represented as a float value between 0 and 1.
         * Called when the request begins, each time data is written to file, and upon
         * download completion.
         */
		virtual void ServiceProgressUpdate( uint64 inNumBytesDownloaded, uint64 inTotalBytes, const void* context ) {};
        
		/** The underlying HTTP transaction failed. */
		virtual void ServiceRequestFailed( const StructuredData* response, const void* context ) = 0;
        
        virtual void ServiceRequestCanceled( const void* context ) {};
	};
	
    class DummyNetworkServiceListener : public NetworkServiceListener
    {
        void ServiceRequestCompleted( const StructuredData* response, const void* context )
        {
        }
        void ServiceRequestCompleted( ImageLib::Image*& image, const void* context )
        {
        }
        void ServiceRequestCompleted( const Buffer* buffer, const void* context )
        {
        }
        void ServiceRequestFailed( const StructuredData* response, const void* context )
        {
        }
    };
    
	// -----------------------------------------------------------------------
	// class NetworkServiceProfile declaration
	// -----------------------------------------------------------------------
	
	class NetworkServiceProfile
	{
	public:
		std::string uri;
		StructuredData params;
	};
        
    struct NetworkServiceRequest
    {
        enum CancelState
        {
            CancelState_NotCanceled,
            CancelState_CancelRequested, // Cancel has been requested, but the http transaction has not yet been stopped
            CancelState_CancelPending, // The http transaction has been stopped, but we're waiting on async tasks to complete
            CancelState_Canceled
        };
        
        mutable IHttpTransaction* httpTransaction;
        mutable Buffer* requestBody;
        const void* context;
        NetworkServiceListener* listener;
        const StructuredData* schema;
        int priority;
        std::string trace;
        std::string req;
        uint32 slot;
        int32 requestId;
        
        NetworkServiceRequest(ResumableRequestInfo* inResumableRequestInfo = NULL, int32 inRequestId = -1);
        
        // $$$ (avy) rename this method.
        // Call this to ensure the ResumableRequestInfo points to this request.
        void Refresh();
        
        void Release();

        bool operator<( const NetworkServiceRequest& rhs ) const
        {
            return this->priority > rhs.priority;
        }
        
        bool IsResumableRequest()
        {
            return mIsResumableRequest;
        }
        
        void ConvertToNonResumableRequest();

        // Resets the current CancelState to NotCanceled (called when a http transaction either
        // completes or fails before we've handled a cancel request)
        void AbortCancelRequest();
        
        // stops the underlying http transaction and enters the CancelPending state.
        void CancelHttpTransactionAndEnterPendingCancel(void* slot);

        void CancelImmediate();
        
        // Only call this if the request is a resumable request (i.e. IsResumableRequest() == true)
        // callable from any thread
        ResumableRequestInfo* GetResumableRequestInfo();

        // This will return the ResumeableRequestInfo associated with the request.
        // Once this method has been called it is the callers responsiblity to
        // delete the ResumableRequestInfo object.
        //
        // If this is not a resumable request or if ownership of ResumableRequestInfo
        // has already been taken then NULL will be returned.
        //
        // callable from any thread
        ResumableRequestInfo*   TakeResumableInfoAndMarkForCancellation(bool inShouldNotifyListener);
        
        void                    MarkForCancellation(bool inShouldNotifyListener);
        
        // callable from any thread
        CancelState             GetCancelState();
    private:
        
        void                    CancelHttpTransaction();

        // callable from any thread
        void                    SetCancelState(CancelState inState);
        void                    NotifyCancel();
        
        bool                    mIsResumableRequest; // Can't just use mResumeInfo != NULL, because if ownership of ResumableRequestInfo is taken away from this request, we still want IsResumableRequest() to return true.
        
        // $$ (avy) mResumeInfo is mutable because the copy constructor
        // takes ownership of mResumeInfo away from the original '
        // object (NULLs it out), but the copy constructor must take a const
        // reference in order to make stl happy, Bleh.
        mutable ResumableRequestInfo*   mResumeInfo;
        CancelState                     mCancelState;
        bool                            mShouldNotifyListenerOnCancel; // set when MarkForCancellation() is called.
    };
    	
	// -----------------------------------------------------------------------
	// class NetworkServiceManager declaration
	// -----------------------------------------------------------------------

	class NetworkServiceManager : protected IHttpListener
	{
	public:
        friend class AsyncCreateFileOfSizeTask;
        friend class AsyncWriteBytesToFileAtTask;
        friend class AsyncFinalizeResumeRequestTask;
        friend class AsyncRemakeRequestTask;
        friend class AsyncDeletePartialFilesTask;
        friend class ResumableRequestInfo;

        //friend class NetworkServiceRequest; //PVZ2_CHINESE CJD_RSG3
		friend struct NetworkServiceRequest;

        typedef int32 RequestId;
        
        const static RequestId InvalidRequestId = -1;
		
		static NetworkServiceManager* DefaultNetworkServiceManager();
        static NetworkServiceManager* TryDefaultNetworkServiceManager();

		
		static StructuredData::String defaultChannel;
		static StructuredData::Integer defaultPriority;
		static StructuredData::Integer defaultTimeout;
		static StructuredData::Integer defaultResumePos;
        
        static const char* DefaultChannelName;
		
		enum LogLevel
		{
			LOG_NONE,
			LOG_REQUESTS,
			LOG_REQUESTS_AND_RESPONSES,
		};
		
		NetworkServiceManager();
        ~NetworkServiceManager();
		
		bool RegisterSchema( const std::string& uri, const std::string& path, StructuredData* errors );
		bool RegisterSchemaJSON( const std::string& uri, const std::string& json, StructuredData* errors );
		bool RegisterSchemaBase64( const std::string& uri, const uchar* base64, size_t size, StructuredData* errors );
		
		/**
		 * Configure the channel before using it if you don't want defaults.
		 * Once the channel has been used or configured, calling this method
		 * will throw an assertion.
		 *    slotCount - the maximum number of simultaneous requests that this
		 *                channel will make.  default is 1.
		 */
		void ConfigureChannel( StructuredData::String channelName, uint32 slotCount );
	
		/**
		 * Request parameters:
		 *   "path"          (string)   : optional URL path suffix for use with a NetworkServiceProfile.
		 *   "url"           (string)   : arbitrary URL, required if not using a NetworkServiceProfile.
		 *   "params"        (object)   : optional name-value pairs to be sent as URL parameters.
		 *   "method"        (string)   : the HTTP method to use.  defaults to "POST" if postData is set,
		 *                                otherwise defaults to "GET".
		 *   "timeout"      (integer)   : timeout value in seconds for the HTTP request.
		 *                                set to 0 for no timeout.  default is 30.
		 *   "slackCerts"      (bool)   : optional setting to ignore most problems with SSL certificates.
		 *                                default is false.
		 *   "postData"      (object)   : data to send as the body for HTTP POST requests.
		 *                                sent as JSON (application/json).
		 *   "formData"      (object)   : data to send as the body for HTTP POST request.
		 *                                sent as form data (multipart/form-data).
		 *   "channel"       (string)   : a named channel to put the request on.
		 *                                each channel has a priority queue of requests and
		 *                                a fixed number of slots to transact the requests on.
		 *                                default is NULL, indicating the default channel.
		 *   "priority"     (integer)   : request priority in queue.  default is 0.
		 *                                larger priority values will be executed before lower values.
		 *   "schema"        (string)   : the URI of a registered schema.
		 *                                if not supplied, no response validation is performed.
         *   "resumable"       (bool)   : determines if this request is one that will be resumable in
         *                                the event of a network outage or device power failure.
         *                                default is false.
         *   "targetFilePath" (string)  : the path to the file where it should be stored on the device
         *                                once the resumable download request has completed.
         *                                use only with "resumable"=true.
         *                                default is an empty string.
         *   "resumePos"    (integer)   : the position of the start of the request if it is a 
         *                                resumable request.
         *                                default is 0. use -1 to force start from the beginning.
         *   "responseBufferSize"(integer): Optional size of http response buffer. Only specify a specific size
         *                                if you want to increase the downloading throughput of an http request.
         *                                The size of the response buffer is the maximum number of bytes that 
         *                                will be downloaded per frame.
         *   "diskBufferSize"  (integer): Optional size which is only relevant to resumable downloads. The
         *                                disk buffer size controls how much data is buffered in memory before
         *                                flushing data to disk. It may be useful to adjust this size in 
         *                                conjunction with responseBufferSize if resumable download requests
         *                                are getting backed up (i.e. the secondary disk buffer is filling up
         *                                before the primary disk buffer is finished writting to disk).
         *
		 */
		RequestId MakeRequest( const StructuredData* request, const NetworkServiceProfile* profile, NetworkServiceListener* listener, const void* context );
		RequestId MakeRequest( const StructuredData* request, NetworkServiceListener* listener, const void* context );
		RequestId MakeRequest( const StructuredData* request, const std::string& url, NetworkServiceListener* listener, const void* context );
		void CancelRequests( StructuredData::String channelName );
        void CancelRequest( RequestId inRequestToCancel );
        
        /*
         * [BUG] nread - adding this breaks priority logic since the underlying container
         *               for requests needed to change.
         */
        //void CancelRequests( StructuredData::String channelName, NetworkServiceListener* listener);
        
		void CancelAllRequests();
		
		void SetLogLevel( LogLevel level );
		
        // TIM TODO: Take a look when we add threading
        bool DeleteOldPartialFiles( void );
        
//        const std::string& GetResumeCacheFolder( void ) const { return mResumeCachedFolder; }
        AsyncTaskManager* GetResumeRequestTaskManager( void ) const { return mResumeRequestTaskManager; }

        void Update();
        
        void DumpChannelState(); // Used for debugging, will dump the current channel/request/slot state to the reporting manager.
	protected:
		
        struct Channel;
		
		struct Slot
		{
			Channel* channel;
			NetworkServiceRequest request;
			StructuredData response;
			Buffer* responseBuffer;
            
			Slot() : channel(NULL), responseBuffer(NULL) { request.httpTransaction = NULL;}
            
            bool IsFree()
            {
                NetworkServiceRequest::CancelState cancelState = request.GetCancelState();
                return request.httpTransaction == NULL &&
                       cancelState != NetworkServiceRequest::CancelState_CancelRequested &&
                       cancelState != NetworkServiceRequest::CancelState_CancelPending;
            }
		};
		
		typedef std::list< NetworkServiceRequest > Queue;
		typedef std::vector< Slot > Slots;
		
		struct Channel
		{
			Queue requests;
			Slots slots;
			
			Slot* FreeSlot();
		};
		
		typedef std::map< std::string, const StructuredData* > Schemata;
		typedef std::map< std::string, Channel > Channels;
        typedef std::map< std::string, Channel* > ChannelPtrs;

		// Used internally to recreate a request with the same RequestId as a previous request (when a request is silently canceled and then recreated.
        RequestId MakeRequest( const StructuredData* request, RequestId inUseRequestId, NetworkServiceListener* listener, const void* context );
        RequestId MakeRequest( const StructuredData* request, RequestId inUseRequestId, const std::string& url, NetworkServiceListener* listener, const void* context );
        
		bool StoreSchema( const std::string& uri, StructuredData* schema, StructuredData* errors );
		
		void EncodeFormData( const StructuredData::Value* formData, NetworkServiceRequest& request );
		void EnqueueRequest( StructuredData::String channelName, const NetworkServiceRequest& request );
		void SlotRequest( const NetworkServiceRequest& request, Slot* slot );
		void SlotNextRequest( Channel* channel );
		Channel* GetChannel( StructuredData::String channelName );
		void CancelRequests( Channel* channel );
        bool CancelRequest( Channel* channel, RequestId inRequestToCancel );
        
        RequestId GetNextRequestId();
        
		void HttpReceivedResponse( IHttpTransaction* http );
		void HttpReceivedData( IHttpTransaction* http, void* data, size_t length );
		void HttpTransactionComplete( IHttpTransaction* http );
		void HttpTransactionError( IHttpTransaction* http );
        
        // Use this when you need a to get all channels.
        // Can't just use mNamedChannels because this doesn't include the default
        // channel. Calling this to fill a map with channels simplies logic
        // elsewhere by not requiring a special case for the default channel.
        // The default channel will be added under the name "*default*"
        //
        void FillWithChannels(ChannelPtrs& outChannels);
        
        // Returns true if the current slot is in the process of canelling, been requested, pending or has been canceled.
        bool UpdateRequestsPendingCancel(Slot* slot);
        
        void AddPendingCancelSlot(Slot* slot);
        
        AsyncTaskManager* mResumeRequestTaskManager;
        // Resumable Download End
		
		Schemata mSchemata;
		StructuredData mCoreMetaSchema;
		
		NetworkServiceListener* mListener;
		Channel mDefaultChannel;
		Channels mNamedChannels;
		
		LogLevel mLogLevel;
        RequestId mNextRequestId;

        CritSect mLock;
        std::vector<Slot*> mPendingCancels;
	};

}
