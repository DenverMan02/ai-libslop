
#pragma once
#include "IFacebookDriver.h"
#include "StructuredData.h"
#include "NetworkServiceManager.h"
#include "drivers/app/android/JavaInterface.h"
#include "drivers/app/android/JavaBound.h"
#include "drivers/app/android/AndroidAppDriver.h"
using namespace Sexy;

namespace Sexy
{

	class AndroidFacebookDriver
		: public IFacebookDriver
		, public JavaBound< AndroidFacebookDriver >
		, public IHttpListener
	{
		typedef IFacebookDriver super;

	public:

		AndroidFacebookDriver();
		void FBSessionStateDoNothingButDontCrashCallback(IFacebookDriver* inFacebook, IFacebookDriver::SessionState inSessionState);

		void InitWithAppId( const std::string& appId );
		void SetUserDataFields( const std::string& userDataFields );
		bool OpenSessionForRead( const std::string& readPermissions, bool allowLoginUI, SessionStateCallback callback );
		void ReathorizeForRead( const std::string& readPermissions, ReauthorizeCallback callback );
		void ReathorizeForPublish( const std::string& publishPermissions, DefaultAudience audience, ReauthorizeCallback callback );
		void CloseAndClearSession();
		void Update();

		bool IsOpen() const;
		bool IsOpening() const;
		SessionState GetSessionState() const;
		std::string GetUserId() const;
		const StructuredData* GetUserData() const;
		std::string GetAccessToken() const;
		time_t GetExpirationDate() const;
		const NetworkServiceProfile* ServiceProfile() const;

		void Dialog( const std::string& name, IFBDialogListener* listener );
		void Dialog( const std::string& name, const StructuredData* params, IFBDialogListener* listener );

        // [BejBlitz BEGIN CHANGE]
        int GetFriendCount() const;
        // [BejBlitz END CHANGE]

	private:

        // HTTP Listener Methods
		void HttpReceivedResponse( IHttpTransaction* http );
		void HttpReceivedData( IHttpTransaction* http, void* data, size_t length );
		void HttpTransactionComplete( IHttpTransaction* http );
		void HttpTransactionError( IHttpTransaction* http );

		void BindJavaMethods( JNIEnv* env, const JavaClass& javaClass );
		static JavaMethod<void> 		JavaInitWithAppId;
		static JavaMethod<jboolean> 	JavaOpenSessionForRead;
		static JavaMethod<jboolean>		JavaIsSessionOpen;
		static JavaMethod<jboolean>		JavaIsSessionOpening;
		static JavaMethod<jstring>		JavaGetAccessToken;
		static JavaMethod<jlong>		JavaGetExpirationDate;
		static JavaMethod<void>			JavaCloseAndClearSession;
		static JavaMethod<jlong>		JavaGetSessionState;
		static JavaMethod<void> 		JavaDialog;

		void BindNativeMethods( JNIEnv* env, const JavaClass& javaClass );
		static void OnSessionOpenedHook( JNIEnv* env, jobject javaObject, jlong aNativeObject, jstring javaAccessToken, jlong javaAccessExpires );
		static void OnSessionLoggedOutHook( JNIEnv* env, jobject javaObject, jlong aNativeObject, jboolean aLoginCanceled );

		static void DialogDidCompleteHook( JNIEnv* env, jobject javaObject, jlong nativeObject, jstring javaEncodedResults );
		static void DialogWasCanceledHook( JNIEnv* env, jobject javaObject, jlong nativeObject );
		static void DialogDidFailHook( JNIEnv* env, jobject javaObject, jlong nativeObject, jstring javaEncodedError );

		void RequestSession( const std::string& permissions );
		void WriteSession();
		void EraseSession();
		void OnSessionOpened( const std::string& accessToken, const time_t& accessExpires );
		void OnSessionLoggedOut( const bool& aLoginCanceled );

		void OnDidNotLogin( const bool& canceled );
		void OnDidLogout();

		void InitProfileParams( const std::string& theAccessToken, const time_t& theAccessExpires );
		void RequestUserData();
		void ReceiveUserData();

		void OnDialogDidComplete(const std::string& encodedResults );
		void OnDialogWasCanceled();
		void OnDialogDidFail(const std::string& encodedError );

		SessionStateCallback	mSessionStateCallback;
		std::string mUserDataFields;
		StructuredData mUserData;
		StructuredData mErrorData;
		NetworkServiceProfile mServiceProfile;
		Buffer* mUserDataBuffer;
		bool	mHasUserData;

		IFBDialogListener* mDialogListener;
		bool mDialogOpen;
		std::string mDialogName;

        // [BejBlitz BEGIN CHANGE]
        int mFBFriends;
        // [BejBlitz END CHANGE]
	};

}
