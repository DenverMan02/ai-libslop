/*
 * GemOfferMgr.h
 *
 *  Created on: 2017-8-15
 *      Author: Administrator
 */

#ifndef NETWORKPROFILEMGR_H_
#define NETWORKPROFILEMGR_H_

#include "NetworkData.h"

namespace Message
{
	void NetworkProfileSyncFinish(bool i_success);
}

class NetworkProfileSyncInfo : public INetworkData
{
public:
	RT_CLASS_DEFINE(NetworkProfileSyncInfo, INetworkData, RtClass);

public:
    bool success;
};

class NetworkProfileMgr : public LazySingleton <NetworkProfileMgr>
{
public:
	enum IdType
	{
		Id_Plant,
		Id_PlantChip,
		Id_Avatar,
		Id_AvatarChip
	};

	NetworkProfileMgr();
    ~NetworkProfileMgr();

    void TrySync();
    bool NeedSync();
    void DoSync();
private:
    bool HasProfileSyncComplete();
    void SetProfileSync(bool i_finish);
    void onSyncFinished(bool i_success);
    void onMsgError(int erroId, const std::string& requestID);

    std::string getPlantList();
	std::string getPlantChipList();
	std::string getAvatarList();
	std::string getAvatarChipList();
	std::string getPendantList();
	std::string getPendantChipList();
	std::string getMaterialList();
	std::string getNewAvatarList();
	std::string getNewAvatarChipList();
	std::string getRechargeStatusList();

	int GetIdByIdType(int i_plantId, IdType i_type);
};


#endif /* GEMOFFERMGR_H_ */
