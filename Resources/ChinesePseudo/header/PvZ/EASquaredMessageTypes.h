//
//  EASquaredMessageTypes.h
//  PlantsVersusZombies2
//
//  Created by Bradley Buchanan on 2/12/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__EASquaredMessageTypes__
#define __PlantsVersusZombies2__EASquaredMessageTypes__

namespace Message {
	void EASquaredEnabledChanged();
	void EASquaredAdsAvailableChanged();
	void EASquaredAdvertisementsClosed();
	void EASquaredAdvertisementsWillOpen();
	void EASquaredFlowEnded(const std::string& i_placementOrigin, int i_coinsEarned, int i_videosWatched);
    void EASquaredOpened(const std::string& i_source);
    void EASquaredButtonTracking(const std::string& i_source, int i_inventoryCount, const std::string& i_reason);
	void EASquaredBeginShowAd();
}

#endif /* defined(__PlantsVersusZombies2__EASquaredMessageTypes__) */
