
#pragma once
#include <vector>
#include "Common.h"

#define SUPPORT_POPCAP_SHARING 1

namespace Sexy
{

	/**
	 * PopCapSharing provides access to a shared iOS Keychain Access Group.
	 * To enable this sharing, the project settings in
	 * "Target->Summary->Entitlements" must be modified.
	 * Check "Enable Entitlements", verify the entitlements file name,
	 * remove iCloud settings if you are not using iCloud,
	 * and add a Keychain Access Group named "PopCapSharing".
	 * You can remove the access group that matches your Bundle Id since that
	 * group is always implicitly available. 
	 */
	class PopCapSharing
	{
	public:

		/**
		 * Get the shared instance of PopCapSharing.  May return NULL
		 * if the instance has not been created.
		 * Call PopCapSharingRequired() if you need to make sure
		 * the instance is created.
		 */
		static PopCapSharing* PopCapSharingOptional();
		
		/**
		 * Get the shared instance of PopCapSharing.  The instance
		 * will be created if it does not already exist.
		 */
		static PopCapSharing* PopCapSharingRequired();
		
		/**
		 * Delete the shared instance of PopCapSharing.
		 */
		static void DeletePopCapSharing();

		typedef std::vector<byte> Data;
		
		virtual bool SavePassword( const std::string& service, const std::string& account, const Data& generic, const Data& value ) = 0;
		virtual bool SavePassword( const std::string& service, const std::string& account, const std::string& generic, const Data& value ) = 0;
		
		virtual bool RetrievePassword( const std::string& service, const std::string& account, Data& generic, Data& value ) = 0;
		virtual bool RetrievePassword( const std::string& service, const std::string& account, std::string& generic, Data& value ) = 0;
		
	protected:

		virtual ~PopCapSharing() {}
		
	};

}
