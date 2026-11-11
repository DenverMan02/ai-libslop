#if 0
#pragma once
#include "IFacebookDriver.h"
#include "NetworkServiceManager.h"

using namespace Sexy;

namespace Sexy
{
	class BaseFacebookDriver : public IFacebookDriver, IHttpListener
	{
	public:
		
		BaseFacebookDriver();
		~BaseFacebookDriver();
	
		void InitWithAppId( const std::string& appId );
		void SetUserDataFields( const std::string& userDataFields );
		bool Resume( IFBSessionListener* listener );
		void Authorize( IFBSessionListener* listener );
		
		bool IsAuthorizing();
		bool IsAuthorized();
		
		const NetworkServiceProfile* ServiceProfile();

		const std::string& GetUserId();
		const std::string& GetAccessToken();
		time_t GetExpirationDate();
		const StructuredData* GetUserData();
		
	protected:
	
		virtual void RequestSession() = 0;
		virtual void ReceiveSession( const std::string& accessToken, int32 expiresIn );
		
		virtual void RequestUserData();
		virtual void ReceiveUserData();
		
		void HttpReceivedResponse( IHttpTransaction* http );
		void HttpReceivedData( IHttpTransaction* http, void* data, size_t length );
		void HttpTransactionComplete( IHttpTransaction* http );
		void HttpTransactionError( IHttpTransaction* http );
		
		virtual void WriteSession();
		virtual void ReadSession();
		virtual void EraseSession();
		virtual bool SessionIsValid();
		virtual void InitProfileParams();
		
		void FireDidLogin();
		void FireDidNotLogin( bool canceled );
		void FireDidLogout();
		
		std::string mAppId;
		std::string mAccessToken;
		time_t mExpirationDate;
		
		NetworkServiceProfile mServiceProfile;
		StructuredData mErrorData;
		StructuredData mUserData;
		Buffer* mUserDataBuffer;
		std::string mUserDataFields;
		std::string mUserId;

		bool mAuthorizing;
		IFBDialogListener* mDialogListener;
	};
	
}
#endif //0
