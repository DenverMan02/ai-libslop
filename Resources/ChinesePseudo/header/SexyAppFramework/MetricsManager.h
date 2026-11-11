
#pragma once
#include "NetworkServiceManager.h"
#include "IHttpDriver.h"
#ifdef HOST_IPHONEOS
#include "drivers/misc/iphoneos/NotificationManager.h"
#endif
#include "MTRand.h"
#include "SexyURL.h"

namespace Sexy
{

	/**
     * Version 1.8
     * () Modified ReportAppLaunch to only send data when source type is set
     * () Added support for throttle values to be refreshed
     * () Removed SetDefaultThrottle
     *
	 * Version 1.7
	 * () Immediately sends cached reports upon availability of network.
	 * () Add support for conditional throttles.
	 * () Switched to the application/json format for sending reports to server.
	 *
	 * Version 1.6
	 * () Framework compatibility updates.
	 *
	 * Version 1.5
	 * () Added SKUCode property.
	 *
	 * Version 1.4.1
	 * () Simulator builds default to the test server.
	 * () Added more details to the v1.4 documentation below.
	 *
	 * Version 1.4
	 * -----
	 * () Saved state version 2.  See implementation notes in Restore().
	 * () MetricsManager is now a single shared instance.
	 * () ApplicationActivated() and ApplicationDeactivated() are now protected
	 *    and handled internally without game code intervention. #ios
	 * () Automatically reports to the common AppLaunch table.
	 *    Includes reporting details of URL activations and Push Notification
	 *    activations.  For URL activations, the query string is examined for
	 *    the source tracking fields "st", "sst1", "sst2", and "sst3".  For
	 *    PushNotifications, the SourceType is "RemoteNotification" and the
	 *    notification payload is examined for an Array named "sst", from
	 *    which up to three strings are sent as the SourceSubType# report
	 *    fields.
	 *    
	 *
	 * Version 1.3
	 * -----
	 * () Added support for sharing SamplingKey and CopernicusServer settings
	 *    between apps on the same iOS device.  To enable this sharing,
	 *    the project settings in "Target->Summary->Entitlements" must be
	 *    modified.  Check "Enable Entitlements", verify the entitlements
	 *    file name, remove iCloud settings if you are not using iCloud,
	 *    and add a Keychain Access Group named "PopCapSharing".  You can
	 *    remove the access group that matches your Bundle Id since that
	 *    group is always implicitly available.  #ios
	 * () Renamed SetMetricsURL() to SetCopernicusServer().  Hi!  If anybody
	 *    was actually using this call, you shouldn't need to anymore.
	 *    Instead, use the new MetricsTester app to change the shared setting
	 *    with no need to modify your builds!
	 * () Renamed SetThrottlsURL() to SetGatsServer(), because it was mis-
	 *    spelled!  Haha, actually because the GATS data is so much more
	 *    than just throttles now.  And I don't think anybody was using
	 *    this method.  I don't think there is a test server for GATS data.
	 *
	 * Version 1.2.1
	 * -----
	 * () Added a save operation during initialization just to make double
	 *    extra sure that the initial SamplingKey gets cached.
	 *
	 * Version 1.2
	 * -----
	 * () You must call the new ApplicationDeactivated method in order to
	 *    save configuration data and cached reports. #bugfix #critical
	 * () GATS protocol v2.  Added support for arbitrary configuration data
	 *    to be bundled into the GATS data and access by the client.
	 * () Added console logging of configuration data to help with testing.
	 * () Changed SetSamplingRoll to SetSamplingKey.  I am breaking the API
	 *    intentionally because this should not be called by clients under
	 *    normal circumstances #breaking
	 * () Added ReportHashedString() method.
	 * 
	 */
	class MetricsManager
		: public NetworkServiceListener
		, INetworkStatusListener
#ifdef HOST_IPHONEOS
		, NotificationListener
#endif
	{
	public:

		/**
		 * Get the shared instance of MetricsManager.  May return NULL
		 * if the instance has not been created.
		 * Call SharedMetricsManagerRequired() if you need to make sure
		 * the instance is created.
		 */
		static MetricsManager* SharedMetricsManagerOptional();
		
		/**
		 * Get the shared instance of MetricsManager.  The instance
		 * will be created if it does not already exist.
		 */
		static MetricsManager* SharedMetricsManagerRequired();
		
		/**
		 * Delete the shared instance of MetricsManager.
		 */
		static void DeleteSharedMetricsManager();
		
		/**
		 * Supply your own NetworkServiceManager for the MetricsManager to use.
		 * By default, the MetricsManager will use the DefaultNetworkServiceManager.
		 * @param nsm The NetworkServiceManager to use.
		 * @param channel The channel to enqueue MetricsManager requests on.
		 */
		void UseNetworkServiceManager( NetworkServiceManager* nsm, const std::string& channel );

		/**
		 * Optional call to override the default maximum number of reports
		 * that will be cached in memory and on the filesystem.
		 * Default value is 1000.
		 */
		void SetCacheReportLimit( size_t reportCount );
		
		/**
		 * Optional call to override the default PlatformName.
		 * Default values are "iOS", "OSX", "Windows" depending on platform.
		 */
		void SetPlatformName( const std::string& platformName );
		
		/**
		 * Optional call to override the ProductName.
		 * The default value is read from SexyAppBase::mProdName.
		 */
		void SetProductName( const std::string& productName );
		
		/**
		 * Optional call to override the SKUCode.
		 * The default value is an empty string, which is reported to
		 * Copernicus as a Null.
		 */
		void SetSkuCode( const std::string& skuCode );
		
		/**
		 * Optional call to override thedefault ClientVersion.
		 * The default value is read from SexyAppBase::mProductVersion.
		 */
		void SetClientVersion( const std::string& clientVersion );
		
		/**
		 * Optional call to override the default AppLaunch throttle value.
		 * This value is used if there is any problem fetching the GATS 
		 * data for the AppLaunch table. Default value is 1.0 (always sent).
		*/
		void SetAppLaunchDefaultThrottle( double throttle );

		/**
		 * Optional call to override the automatically generated random
		 * number that controls metrics sampling.  This is the value that
		 * is tested against the throttles.
		 * This should only be done for testing purposes.
		 */
		void SetSamplingKey( double samplingKey );
		
		/**
		 * Clears any sampling conditions that have been set by AddSamplingCondition.
		 */
		void ClearSamplingConditions();
		
		/**
		 * Add a sampling condition.  The GATS throttles can have conditional values
		 * set in addition to the base value.  If any of the throttle conditions
		 * are matched by a sampling condition, then the largest (most permissive)
		 * throttle (i.e. samplingProbability) will be used to control sampling.
		 */
		void AddSamplingCondition( const std::string& condition );
		
		/**
		 * Enable or disable all metrics reporting.  Default is true.
		 */
		void Enable( bool enable );
		
		/**
		 * Optional call to override the default GATS server URL.
		 */
		void SetGatsServer( const std::string& url );
		
		/**
		 * Optional call to override the default CopernicusServer URL.
		 */
		void SetCopernicusServer( const std::string& url );
		
		/**
		 * Call this method at some point in your application flow where you
		 * wouldn't mind it doing some processing and hitting the network.
		 * It is called automatically be EndReport(), but you should call it
		 * regularly in case the network has been unavailable and some reports
		 * have been cached.
		 */
		void SendReports();
		
		/**
		 * Begins a new metrics report.  This will create a new report and 
		 * initialize it with the following required fields:
		 *    "MetricsType" - based on the metricsType parameter.
		 *    "MetricsVersion" - based on a metricsVersion parameter.
		 *    "ClientVersion" - based on a previous call to SetClientVersion.
		 *    "PlatformName" - based on a previous call to SetPlatformName.
		 *    "ProductName" - based on a previous call to SetProductName.
		 *    "SamplingProb" - based on the current throttle value.
		 * You *may* use the returned StructuredData to add fields to the
		 * report, or you may simply use ReportString, ReportNumber and
		 * ReportDeviceId calls to build your report.
		 *
		 * @param metricsType The metric type you are building a report for.
		 * @return The StructuredData representing the report, or NULL if
		 *         the metric is throttled off.
		 */
		StructuredData* BeginReport( const std::string& metricsType, const std::string& metricsVersion );
		StructuredData* BeginReportUnthrottled(const std::string& metricsType, const std::string& metricsVersion);
		
		/**
		 * Add a named string value to the current report.
		 */
		void ReportString( const std::string& name, const std::string& value );
		
		/**
         * Add a named string value to the current report.
         * This string is hashed using the SHA1 hashing algorithm used for the DeviceID.
         */
        void ReportHashedString( const std::string& name, const std::string& value );
		
		/**
		 * Add a named number value to the current report.
		 */
		void ReportNumber( const std::string& name, double value );
		
		/**
		 * Add a named integer value to the current report.
		 */
		void ReportInteger( const std::string& name, int64 value );

		/**
		 * Add a named boolean value to the current report.
		 */
		void ReportBoolean( const std::string &name, bool value );
		
		/**
		 * Add a named device id to the current report.  This id is created
		 * internally by hashing the MAC address of the primary network
		 * interface.
		 */
		void ReportDeviceId( const std::string& name );
		
		/**
		 * End the report and send it to the server.  The "UnixTime" field
		 * will be added and the report will be queued to send.
		 */
		void EndReport();
		
		/**
		 *
		 */
		void ReportAppLaunch();
		
        /**
         * Retrieve arbitrary value from the GATS data.
         */
        const StructuredData::Value* GatsValueForPath( const std::string& path );
        
		const std::string VersionString() const;
        
		const std::string& PlatformName() const;
		const std::string& ProductName() const;
		const std::string& ClientVersion() const;
		const std::string& DeviceId() const;
		double SamplingKey() const;
		std::string GatsPath() const;
		time_t GatsTimestamp() const;
		const StructuredData* GatsErrorResponse() const;
		time_t GatsErrorTimestamp() const;
		const std::string& GatsServer() const;
		const std::string& CopernicusServer() const;
		
        void ResetOpenURL();
        
	protected:

		MetricsManager();
		virtual ~MetricsManager();
		
		void RequestThrottles();
		void RecieveThrottles( const StructuredData* response );
		void LogThrottles();
		double GetThrottleValue( const std::string& metricsType, double defaultThrottle );
		
		void EnsureNetworkServiceManager();
		void RegisterThrottlesSchema();

		StructuredData* BeginReportHelper( const std::string& metricsType, const std::string& metricsVersion, const int samplingProb);

		void EnforceReportsLimit();
		void ClearReports();
		void ClearSentReports();
		
		void NetworkStatusChanged( IHttpDriver::NetworkStatus status );
		
		void ServiceRequestValidated( const StructuredData* response, const void* context );
		void ServiceRequestCompleted( const StructuredData* response, const void* context );
		void ServiceRequestCompleted( ImageLib::Image*& image, const void* context );
		void ServiceRequestCompleted( const Buffer* buffer, const void* context );
        void ServiceResumableRequestCompleted( const std::string& filePath, const void* context );
        void ServiceProgressUpdate( uint64 inNumBytesDownloaded, uint64 inTotalBytes, const void* context );
		void ServiceRequestFailed( const StructuredData* response, const void* context );
        
        void EnsureGatsThrottleFreshness();
		
		void Save();
		int32 Restore();
		
#if SEXY_IS_PLATFORM_IOS
		void DidReceiveRemoteNotification( const StructuredData* userInfo );
		void DidReceiveLocalNotification( const StructuredData* userInfo );
		bool HandleOpenURL( const SexyURL& url );
#endif // SEXY_IS_PLATFORM_IOS
#if SEXY_IS_PLATFORM_IOS || SEXY_IS_PLATFORM_ANDROID
		void ApplicationActivated();
		void ApplicationDeactivated();
#endif // SEXY_IS_PLATFORM_IOS || SEXY_IS_PLATFORM_ANDROID
		
		enum RequestContexts
		{
			GET_THROTTLES,
			POST_METRICS,
		};
		
		struct Report
		{
			time_t creationTime;
			StructuredData data;
		};
		typedef std::vector< Report* > Reports;
		typedef std::set< std::string > Conditions;
		
		static std::string sThrottlesSchemaJSON;
		NetworkServiceManager* mNetwork;
		std::string mNetworkChannel;
		MTRand mRand;
		std::string mDeviceId;
		StructuredData mGatsData;
		StructuredData mErrorResponse;
		time_t mGatsTimestamp;
		time_t mErrorTimestamp;
		double mDefaultThrottle;
		double mAppLaunchDefaultThrottle;
		double mSamplingKey;
		Conditions mSamplingConditions;
		bool mMetricsEnabled;
		std::string mGatsServer;
		std::string mCopernicusServer;
		std::string mClientVersion;
		std::string mPlatformName;
		std::string mProductName;
		std::string mSkuCode;
		
		bool mLaunchStandard;
		std::string mLastLaunchVersion;
		std::string mLaunchSourceType;
		std::string mLaunchSourceSubtype1;
		std::string mLaunchSourceSubtype2;
		std::string mLaunchSourceSubtype3;
		
		size_t mReportsLimit;
		Reports mReports;
		Reports mSentReports;
		Report* mActiveReport;
        
        bool mRequestThrottleIssued;
		
	};

}
