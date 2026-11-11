/**
 * Copyright 2002 by Zylom BV,
 * De Zaale 11, 5600 AB Eindhoven, The Netherlands.
 * All rights reserved.
 *
 * This software is the confidential and proprietary information of Zylom BV. Use is subject to license terms.
 */

#ifndef ZYLOMSO_H
#define ZYLOMSO_H

#pragma warning(disable: 4251)
#include <string>

#ifndef ZYLOMGS_API
#define ZYLOMGS_API __declspec(dllexport)
#define ZYLOMGS_TEMPLATE
#endif

namespace zylom
{
	namespace zylomso
	{
		/**
		 * A class that holds the update information for a game.<br>
		 * This class is used when checking for updates for a game. In addition this class
		 * can be used by a game to retreive the update details after checking for an update.<br>
		 *
		 * @author      <a href="mailto:m.kremers@zylom.com">Mark Kremers</a>
		 * @version     1.0, Aug 2002
		 */
		class ZYLOMGS_API UpdateInformation
		{
			//////////////////////////////////////////////////////////////////////////////
			// Properties
			//////////////////////////////////////////////////////////////////////////////

			/** The game identification number of the game this update information is for. */
			private: int			gameID;

			/** Indicates the result of the last update (0 = no update available, 1 = update available, 3 = error). */
			private: int			updateResult;

			/** The latest available version. */
			private: std::string	latestVersion;

			/** The text message that explains the update reason. */
			private: std::string	updateText;

			//////////////////////////////////////////////////////////////////////////////
			// Constructors and destructor
			//////////////////////////////////////////////////////////////////////////////

			/**
			 * The class constructor.
			 * 
			 * @param gameID the game identification number.
			 */
			public: UpdateInformation(int gameID);

			/**
			 * The copy constructor.
			 */
			public: UpdateInformation(const UpdateInformation& updateInformation);

			/**
			 * The class destructor.
			 */
			public: virtual ~UpdateInformation();

			//////////////////////////////////////////////////////////////////////////////
			// Getter/Setters
			//////////////////////////////////////////////////////////////////////////////

			/**
			 * Gets the current value of the updateResult property.
			 *
			 * @return the current value of the updateResult property.
			 */
			public: virtual int getUpdateResult();

			/**
			 * Gets the current value of the latestVersion property.
			 *
			 * @return the current value of the latestVersion property.
			 */
			public: virtual std::string getLatestVersion();

			/**
			 * Gets the current value of the updateText property.
			 *
			 * @return the current value of the updateText property.
			 */
			public: virtual std::string getUpdateText();

			//////////////////////////////////////////////////////////////////////////////
			// Methods
			//////////////////////////////////////////////////////////////////////////////

			/**
			 * Initialises this object.
			 *
			 * @param updateResult the value for the updateResult property.
			 * @param latestVersion the value for the latestVersion property.
			 * @param updateText the value for the updateText property.
			 */
			public: virtual void init(int updateResult, std::string latestVersion, std::string updateText);

			/**
			 * Compares to version strings.
			 *
			 * @param version1 the first version to check.
			 * @param version2 the second version to check the first version against.
			 * @return 0 if version1 == version2 or -1 if version1 < version2 or 1 if version1 > version2.
			 */
			public: static int compareVersions(std::string version1, std::string version2);
		};
	}
}

/**
 * This function should be called by the game when it initialises.
 * All registry information and needed dll instances are created by this function.
 *
 * @param gameID the unique identification number of the game.
 * @param exceptionText the text that is displayed in a dialog box when the ZylomGS_StandAlone_SendBugReport function is called.
 * @param exceptionTitle the titel of the dialog box that is shown when the ZylomGS_StandAlone_SendBugReport function is called.
 */
ZYLOMGS_API  void ZylomGS_StandAlone_Init(unsigned int gameID);
ZYLOMGS_API  void ZylomGS_StandAlone_Init(unsigned int gameID, const char* exceptionText = "", const char* exceptionTitle = "");

/**
 * This function checks if (based on some rules) it is time to do an update check.
 *
 * @return true if it is time to do an update check.
 */
ZYLOMGS_API bool ZylomGS_StandAlone_UpdateCheckNeeded();

/**
 * This function performs an update check. While checking for an update ads are (possibly) downloaded and installed.
 * This function is blocking until the update is done or the maximum time has expired (registry setting).
 *
 * @return an instance of the UpdateInformation that contains all information for the update.
 */
ZYLOMGS_API zylom::zylomso::UpdateInformation ZylomGS_StandAlone_CheckUpdate();

/**
 * This function should be called by the game when it exits.
 * Based on some rules (including runtime duration) an ad is shown in a browser window.
 *
 * @param registered should indicate if the game is registered or not (used to determine the ad).
 * @param readFromRegistry should indicate if the registered state should be read from the registry setting (debugging).
 */
ZYLOMGS_API void ZylomGS_StandAlone_ShowAd(bool registered, bool readFromRegistry = false);

/**
 * This function shows the buy web page for this game.
 */
ZYLOMGS_API void ZylomGS_StandAlone_ShowBuyPage();

/**
 * This function shows the update web page for this game.
 */
ZYLOMGS_API void ZylomGS_StandAlone_ShowUpdatePage();

/**
 * This function should be called by the game when an exception has been caught. 
 * This function will generate a debug report and send it to the Zylom server.
 *
 * @param extraText some optional extra text that will be included in the bug report.
 */
ZYLOMGS_API void ZylomGS_StandAlone_SendBugReport(char* extraText = "");

#endif
