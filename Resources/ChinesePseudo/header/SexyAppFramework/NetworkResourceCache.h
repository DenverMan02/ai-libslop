#ifndef __BufferCache_H__
#define __BufferCache_H__

#include "RtStandaloneObject.h"
#include "SexyApp.h"
#include "StructuredData.h"
#include "NetworkServiceManager.h"

namespace Sexy
{
	class NetworkResourceCache
		: public RtStandaloneObject
		, NetworkServiceListener
	{
		typedef RtStandaloneObject super;
		
	public:
		
		RT_CLASS_DEFINE( NetworkResourceCache, RtStandaloneObject, RtClass );
		
		static NetworkResourceCache* SharedCache();
		static void DeleteSharedCache();

		enum ResourceType
		{
			RESOURCE_NOT_LOADED,
			RESOURCE_BUFFER,
			RESOURCE_IMAGE,
			RESOURCE_DATA,
		};
		
		struct Descriptor
		{
			std::string url;
			std::string group;
			time_t maxAge;
			std::string trace;
			
			ResourceType type;
			std::string file;
			time_t time;
			
			Descriptor();
			std::string GetSummary();
		};
	
		class Listener
		{
		public:
			virtual bool NetworkDataLoaded( const StructuredData* data, const Descriptor& desc, const void* context ) = 0;
			virtual bool NetworkImageLoaded( ImageLib::Image*& image, const Descriptor& desc, const void* context ) = 0;
			virtual bool NetworkBufferLoaded( const Buffer* buffer, const Descriptor& desc, const void* context ) = 0;
			virtual void NetworkResourceDidNotLoad( const Descriptor& desc, const void* context ) = 0;
		};
		
		bool LoadResource( const Descriptor& desc, Listener* listener, const void* context );
		
		/**
		 * @param group The group to flush.  Pass NULL to flush all resources.
		 */
		void FlushResourceGroup( const char* group );
		
		void FlushAll();
		
	protected:

		struct RequestContext
		{
			Listener* listener;
			const void* listenerContext;
			Descriptor descriptor;
		};
		
		NetworkResourceCache();
		virtual ~NetworkResourceCache();

		bool GetFlush();
		void DoFlush( bool flush );
		bool GetClean();
		void DoClean( bool clean );
		
		void ReadCatalog();
		void WriteCatalog();
		Descriptor* GetCatalogEntry( const std::string& url );
		void SetCatalogEntry( const Descriptor& entry );

		RequestContext* CreateRequestContext();
		void ReleaseRequestContext( const RequestContext* context );
		
		const std::string FileNameForUrl( const std::string& url );

		bool LoadBuffer( const Buffer& buffer, const Descriptor& desc, Listener* listener, const void* context );
		bool LoadImage( const Buffer& buffer, const Descriptor& desc, Listener* listener, const void* context );
		bool LoadData( const Buffer& buffer, const Descriptor& desc, Listener* listener, const void* context );
		
		bool RequestResource( const Descriptor& desc, Listener* listener, const void* context );
		
		void ServiceRequestValidated( const StructuredData* response, const void* context ) override;
		void ServiceRequestCompleted( const StructuredData* response, const void* context ) override;
		void ServiceRequestCompleted( ImageLib::Image*& image, const void* context ) override;
		void ServiceRequestCompleted( const Buffer* buffer, const void* context ) override;
		void ServiceRequestFailed( const StructuredData* response, const void* context ) override;
		
		std::string CatalogNetworkResource( ResourceType type, RequestContext* rc );
		void CleanseCacheFolder();
		bool IsCacheFile( const std::string& filename );
		
#if 0
		bool Check( const std::string& key, StructuredData& outMetaData );
		bool Retrieve( const std::string& key, Buffer* outBuffer );
		void Remove( const std::string& key );
		
		void TranslateToCacheFileName( std::string& theFileName );
		bool CacheFileExists( std::string theFileName );
		void DeleteCacheFile( std::string theFileName );
		void ClearCacheFiles();
		bool WriteBufferToCacheFile(std::string theFileName, Sexy::Buffer& theBuffer);
		bool ReadBufferFromCacheFile(std::string theFileName, Sexy::Buffer& theBuffer);
#endif
		
		typedef std::vector< Descriptor > Entries;
		
		std::string mCachePath;
		std::string mCatalogPath;
		Entries mCatalog;
		bool mVerboseLogging;
		
	};

}

#endif //__BufferCache_H__
