#ifndef __MoreInfoManager_H__
#define __MoreInfoManager_H__

#include "SexyApp.h"
#include "IHttpDriver.h"
#include "NetworkResourceCache.h"
#include "AtlasedImageStore.h"
#include "RtStandaloneObject.h"
#include "RtDelegate.h"
#ifdef WANTS_PRIMETEXT
#include "PrimeText.h"
#endif

namespace Sexy
{
	class MoreInfoManager;    
	struct ResourceContext;
	class MetricsManager;
	class MemoryImage;

//PVZ2_CHINESE_BEGIN
//#ifdef WIDGETS_USE_PRIMETEXT
//    typedef     PrimeTypeface      InfoFont;
//#else
//    typedef     Font               InfoFont;
//#endif
//PVZ2_CHINESE_END
    
	enum InfoPanelAlign
	{
		IP_AlignMin,
		IP_AlignCenter,
		IP_AlignMax,
		IP_AlignNone, // kojak - really?  wtf does that mean?
	};
		
	enum InfoPanelBackground
	{
		IPBG_None,
		IPBG_Local,
		IPBG_Global,
	};
	
	/**
	 *
	 */
	struct InfoPanel
	{
	public:
		InfoPanel();
		bool IsLoaded() const;
		
		SexyString name;
		SexyString text;
		RtWeakPtr<Image> image;     // main image for tile
		RtWeakPtr<Image> bgImage;   // image to draw behind mImage
		InfoPanelBackground bgType;

        //PVZ2_CHINESE_BEGIN
#ifdef WIDGETS_USE_PRIMETEXT
        PrimeTypeface*  titlePrimeFont;
        PrimeTypeface*  textPrimeFont;
#endif
		Font* titleFont;
		Font* textFont;
        //PVZ2_CHINESE_END
		std::string url;       // URL to open upon user clicking of this game tile
		std::string nid;      //  server-side value unique to each SKU in each game title
		std::string vid;      //  server-side value unique to each SKU in each game title
		InfoPanelAlign hAlign;
		InfoPanelAlign vAlign;
	};

	enum ResourceType
	{
		RC_Manifest,
		RC_DefaultBackground,
		RC_PanelBackground,
		RC_PanelImage,
	};

	struct ResourceContext
	{
	public:
		ResourceContext() : panelIndex( 0 ) {}
		ResourceType resourceType;
		uint32 panelIndex;
	};

	class MoreInfoManager
		: public RtStandaloneObject
		, public IHttpListener
		, public NetworkResourceCache::Listener
	{
		typedef RtStandaloneObject super;
		friend class MoreGamesTable;
		
	public:
		
		RT_CLASS_DEFINE( MoreInfoManager, RtStandaloneObject, RtClass );
		
		static MoreInfoManager* SharedMoreInfoManagerOptional();
		static MoreInfoManager* SharedMoreInfoManagerRequired();
		static void DeleteSharedMoreInfoManager();
		
		MoreInfoManager();
		~MoreInfoManager();

		std::string VersionString() const;
		
		void SetProductName( const char* productName );
		std::string ProductName() const;
		
		void SetLanguageName( const char* languageName );
		std::string LanguageName() const;
		
		void SetBaseURL( const char* baseURL );
		std::string BaseURL() const;

        //PVZ2_CHINESE_BEGIN
		void SetTitleFont( Font* titleFont );
		void SetTextFont( Font* titleFont );
		Font* TextFont() const;
#ifdef WIDGETS_USE_PRIMETEXT
        void SetTitlePrimeFont( PrimeTypeface* titlePrimeFont );
		void SetTextPrimeFont( PrimeTypeface* titleFont );
		PrimeTypeface* TextPrimeFont() const;
#endif
        //PVZ2_CHINESE_END
		
		RtWeakPtr<Image> DefaultItemBG();
		int DefaultItemGap();
		
		/**
		 * Allows calling app to check to see if More Games content has been
		 * updated since the last time user checked.
		 */
		bool HasUnreadContent();
		
		/**
		 * Tells manager that the last loaded content no longer has to be
		 * considered "new".  Call after user visits More Games when
		 * HasUnreadContent() was true.
		 */
		void MarkContentRead();

		/**
		 * Starts download of JSON manifest.  The override_url param is used
		 * only if you want to bypass default behavior.
		 */
		void Refresh( const char* overrideurl="" );

		bool RefreshInProgress();
		float GetRefreshProgress();
		Event0 RefreshCompleteEvent;
		Event0 RefreshCanceledEvent;
		
		// ----------
		// Interface below targets the MoreInfoWidget.
		// ----------
		
		int GetPanelCount() const { return static_cast<int>(mPanels.size()); }
		const InfoPanel* GetPanel( uint32 index ) const;
		void ActivatePanel( uint32 index );

		int GetViewedManifestVersion() { return mViewedManifestVersion; }
		int GetManifestVersion() { return mCachedManifestVersion; }
		
		bool NetworkDataLoaded( const StructuredData* data, const NetworkResourceCache::Descriptor& desc, const void* context ) override;
		bool NetworkImageLoaded( ImageLib::Image*& image, const NetworkResourceCache::Descriptor& desc, const void* context ) override;
		bool NetworkBufferLoaded( const Buffer* buffer, const NetworkResourceCache::Descriptor& desc, const void* context ) override;
		void NetworkResourceDidNotLoad( const NetworkResourceCache::Descriptor& desc, const void* context ) override;

	protected:
		
		void Cancel();
		void Clear();
		
		void RequestManifest( bool cacheOnly, const char* overrideurl="");
		void ReceiveManifest( const StructuredData* manifest );
		void SyncPanel( const StructuredData::Value* sku );
		
		std::string GetManifestURL();
		std::string GetPlatformName();

		ResourceContext* CreateResourceContext();
		void DeleteResourceContext( ResourceContext* context );
		
		typedef std::set< ResourceContext* > Requests;
		typedef std::vector< InfoPanel > Panels;
		
		std::string mProductName;
		std::string mLanguageName;
		std::string mBaseURL;
        //PVZ2_CHINESE_BEGIN
		Font* mTitleFont;
		Font* mTextFont;
#ifdef WIDGETS_USE_PRIMETEXT
        PrimeTypeface* mTitlePrimeFont;
		PrimeTypeface* mTextPrimeFont;
#endif
        //PVZ2_CHINESE_END
		
		Requests mPendingRequests;
		uint32 mNetRequests;
		bool mErrorDuringRefresh;
		
		int32 mCachedManifestVersion;
		int32 mViewedManifestVersion;
		RtWeakPtr<Image> mDefaultItemBG;
		bool mUseDefaultBG;
		int32 mDefaultItemWidth;
		int32 mDefaultItemGap;

		Panels mPanels;
		AtlasedImageStore mImageStore;
	};

}

#endif //__MoreInfoManager_H__
