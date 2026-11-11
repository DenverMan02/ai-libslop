/*
 * CustomLevelDataPacket.h
 *
 *  Created on: 2021-12-9
 *      Author: admin
 */

#ifndef CUSTOMLEVELDATAPACKET_H_
#define CUSTOMLEVELDATAPACKET_H_

enum class CustomLevelAPIContext
{
	None,
	UploadLevel,
	DeleteLevel,
	LevelDetails,
	ViewLevels,
	FilterLevels,
	SearchLevels,
	LikeDislike,
	StartLevel,
	Favourite,
	ModifyLevelName,
	PlayCount,
	ModifyDownloadable,
	Download,
	CheckUploadedLevels,
	AuthorLevel,
};

enum class CustomLevelAPIResponseStatus
{
	None,
	WaitingOnResponse,
	ResponseSuccess,
	ResponseFailNetwork,
	ResponseFailInvalidData
};

namespace Message
{
	// Subscribe to handle the result of the PVZ1NetworkIssue dialog.
	void CustomLevelNetworkIssueDecision(int i_context, int i_decision);
	void CustomLevelNetworkResponseReceived(int i_context, int i_status);
	void CustomLevelTutorialSeedBankCreated();
	void CustomLevelTutorialSeedPacketCreated();
	void CustomLevelTutorialSurfaceCreated();
	void CustomLevelTutorialZombieModuleCreated();
	void CustomLevelTutorialZombieSelectedListCreated();
	void CustomLevelTutorialRedoDrag();
	void CustomLevelTutorialFinishDrag();
	void CustomLevelTutorialCloseContainer();
	void CustomLevelTutorialRedoDragWaveEvent();
	void CustomLevelTutorialFinishDragWaveEvent();
	void CustomLevelTutorialFinishCloseEvent();
	void CustomLevelTutorialCloseEditor();
}

#endif /* CUSTOMLEVELDATAPACKET_H_ */
