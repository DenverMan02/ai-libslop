//
//  JamApplier.h
//  PlantsVersusZombies2
//
//  Created by Mina, Elliott on 7/15/15.
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__JamApplier__
#define __PlantsVersusZombies2__JamApplier__

#include <stdio.h>
#include "GridItemJammable.h"
#include "PropertySheetBase.h"
#include "ZombieEnums.h"

class Zombie;

namespace  {
	static const std::string kInvalidJam = "invalid_jam";
	static const std::vector<std::string> kEightiesJams = {
		"jam_ballad",
		"jam_pop",
		"jam_metal",
		"jam_punk",
		"jam_rap",
		"jam_8bit"
	};
}

class MusicalJamProperties : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(MusicalJamProperties, PropertySheetBase, RtClass);
	
	std::map<std::string, std::string> JamsToMusicSwitches;
	std::map<std::string, std::string> JamsToMusicEnterEvents;
	std::map<std::string, ZombieConditions> JamsToZombieConditionApplied;
};

class JamListener : public IInteractiveAudioCallbackListener
{
public:
	// mostly no-effect overrides; beat and bar are the only two we're interested in right now
	// NOTE: Code written in these methods will execute on the audio thread not the gameplay thread.
	void OnEndOfEvent( AudioGameObjectId id, AudioPlayingId playingId, AudioEventId eventId ) override { }
	void OnEndOfDynamicSequenceItem( AudioGameObjectId id ) override { }
	void OnMarker( AudioGameObjectId id ) override { }
	void OnDuration( AudioGameObjectId id ) override { }
	void OnSpeakerVolumeMatrix( AudioGameObjectId id ) override { }
	void OnMusicPlayStarted( AudioGameObjectId id ) override { }
	void OnMusicSyncEntry( AudioGameObjectId id, AudioPlayingId playingId ) override { }
	void OnMusicSyncExit( AudioGameObjectId id, AudioPlayingId playingId ) override { }
	void OnMusicSyncGrid( AudioGameObjectId id ) override { }
	void OnMusicSyncUserCue( AudioGameObjectId id ) override { }
	void OnMusicSyncPoint( AudioGameObjectId id ) override { }
	
	void OnMusicSyncBeat( AudioGameObjectId id ) override;
	void OnMusicSyncBar( AudioGameObjectId id ) override;
};

class JamApplier
{
public:
	virtual ~JamApplier(){};
		
	void ApplyMusicConditionsToAllZombies(const std::string& i_oldJam, const std::string& i_newJam) const;
	void ApplyMusicConditionsTo(const std::string& i_theJam, Zombie * i_zombie) const;
	void RemoveMusicConditionsFrom(const std::string& i_theJam,Zombie * i_zombie) const;
	void ChangeMusicGenre(const std::string& i_jam) const;
	void PlayMusicGenreEnterEvent(const std::string& i_jam) const;
	void ApplyJamToJammableGridItem(GridItemJammable *item, const std::string& i_oldJam, const std::string& i_newJam) const;
	void ApplyJamToAllJammableGridItems(const std::string& i_oldJam, const std::string& i_newJam) const;

private:
	MusicalJamProperties* getMusicalJamProps() const;
};

#endif /* defined(__PlantsVersusZombies2__JamApplier__) */
