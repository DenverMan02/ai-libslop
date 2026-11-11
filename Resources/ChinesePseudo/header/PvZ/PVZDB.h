//
//  PVZDB.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 3/21/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef __PVZDB_H__
#define __PVZDB_H__

#include "Precompile.h"
#include "RtDb.h"
#include "Singleton.h"
#include "RtDelegate.h"

class PVZDB : public LazySingleton<PVZDB>
{
public:
	enum TableIndex
	{
		TABLE_INVALID = -1,
		
		TABLE_SCRATCHSPACE = 0,
		
		TABLE_GAME,
		TABLE_VERSION,
		TABLE_MANIFEST,
		TABLE_LIVECONFIG,
		
		/// Mostly static data and content
		TABLE_PROPERTYSHEETS,
		TABLE_PLANTTYPES,
        TABLE_PLANTFAMILYPROPERTIES,
        TABLE_POWERS,
		TABLE_ZOMBIETYPES,
        TABLE_ZOMBIEACTIONS,
        TABLE_CREATURETYPES,
		TABLE_PROJECTILETYPES,
		TABLE_GRIDITEMTYPES,
        TABLE_EFFECTOBJECTTYPES,
		TABLE_COLLECTABLETYPES,
		TABLE_PRESENTTABLES,
		TABLE_PRESENTTYPES,
		TABLE_UISHEETS,
		TABLE_NPCSHEETS,
		TABLE_LEVELMODULES,
		TABLE_POWERUPTYPES,
		TABLE_GAMEFEATURES,
        TABLE_TOOLPACKETS,
//PVZ2_CHINESE_BEGIN
        TABLE_BONUSTYPES,
//PVZ2_CHINESE_END
        TABLE_STREAMINGMUSIC,
		TABLE_MAGENTO,

		TABLE_WORLDMAPS,
		TABLE_WORLDMAPLIST_NEW,
		TABLE_WORLDMAPLIST_RIFT,
		TABLE_WORLDMAPLIST_PVZ1,
		TABLE_WORLDMAPLIST_UNCHARTED,
		TABLE_WORLDMAPLIST_CARDGAME,
		TABLE_WORLDMAPEDITORDATA,
		TABLE_WORLDRESOURCES,
		
		TABLE_UIWIDGETS,
		TABLE_CURRENTLEVEL,
		
		/// Run-time object instances
		TABLE_BOARDSTATE,
		TABLE_GAMEOBJECTS,
		TABLE_BOARDENTITIES,
		TABLE_ZOMBIES,
        TABLE_CREATURES,
        TABLE_PROJECTILES,
		TABLE_PLANTS,
		TABLE_PLANTGROUPS,
		TABLE_COLLECTABLES,
		TABLE_GRIDITEMS,
        TABLE_EFFECTOBJECTS,
		TABLE_EFFECTS,
		TABLE_POPANIMRIGS,
		TABLE_SUBSYSTEMS,
		TABLE_LEVELMODULEINSTANCES,

		TABLE_WAVEACTIONINSTANCES,
		TABLE_POWERUPINSTANCES,
        
        TABLE_PLAYER_PROFILES,		// Player profile entry
		TABLE_PLAYER_INFO_DELTA,	// Player profile delta entry
        
        TABLE_HOTUI_FONTS,              // Fonts
        TABLE_HOTUI_FONTS_ALIASES,      // Fonts Aliases
		
        TABLE_SERVER_CONFIG,
        TABLE_PURCHASE_CONFIG,
        TABLE_LOOTSAVEDATA,
        
		TABLE_DROP_ITEM_GROUPS,
        TABLE_DROP_ITEMS,
        TABLE_CHALLENGE_DROP_ITEMS,
        
        TABLE_PROFILELOCALSAVEDATA,
		TABLE_DRAPERSAVEDATA,
        
		TABLE_TLogCache,

        TABLE_ACTIVITY_CONFIG,
        TABLE_GACHA_CONFIG,
        TABLE_SKILLTYPES,
        TABLE_DISPLAYACTIONS,
        TABLE_DISPLAYAVATARACTIONS,
        TABLE_PLANT_PIECE_LEVEL_DATA,
        TABLE_STORE_GIFT_CONFIG,

        TABLE_DAILY_REWARD_CONFIG,
        TABLE_NETWORK_CACHE,
        TABLE_TREASURE_CONFIG,
        TABLE_DANGERROOM_REWARD_CONFIG,
        //TABLE_MINIGAMEACTIVITY,
        TABLE_PEDTREASURE_CONFIG,
        TABLE_REDPACKET_REWARD,
        TABLE_PLANT_TRIAL_CONFIG,
        TABLE_PLANTGIFTTYPES,
		TABLE_RECHARGE_GIFT_CONFIG,
        TABLE_RECHARGE_REWARD_CONFIG,
        TABLE_CONSUMPTION_REWARD,
        TABLE_PLANT_ADVENTURE_CONFIG,
		
//		TABLE_COMPENSATED_AWARD,
		TABLE_UILAYOUT,
                
        TABLE_DAILY_ACHIEVEMENT,
        TABLE_LEVELOFTHEDAY_CONFIG,
        TABLE_NATIONALDAYREWARD_CONFIG,
		TABLE_DANGERROOM_REWARD_LIST,
        TABLE_PVP_OBJECTS,
        TABLE_TRAININGTYPES,
        TABLE_REBATE_REWARD,
        TABLE_HARDLEVEL_CONFIG,
        
        // star convert
        TABLE_STAR_CONVERT_CONFIG,
        
        TABLE_ENDLEVEL_AWARD,
        
        //Pvp table
        TABLE_PVPSHOP_CONFIG,
        TABLE_PVP_UPGRADE,
        
        // Lost Net Activity
        TABLE_LOSTNET_ACTIVITY_CONFIG,
        
        TABLE_COMPENSATED_AWARD, // Keep last for ios
        
        TABLE_EASQUAREDCONFIG,
        
		TABLE_ARMORTYPES,
		//for oppo
#ifdef HOST_ANDROID
		TABLE_OFFER_BUNDLE_CONFIG,
#endif
		TABLE_WORLDCUP_CONFIG,

		TABLE_AWARDCONFIG,
		TABLE_JOUST_CONFIG,
		TABLE_JOUST_SCHEDULE,
		TABLE_JOUST_LEVELS,
		TABLE_JOUST_LEADERBOARDS,
		TABLE_JOUST_CROWN_REWARDS,
		TABLE_JOUST_PROGRESSIVE_REWARDS,
		TABLE_JOUST_TOURNAMENT_REWARDS,

		TABLE_RIFT_SCHEDULE,
		TABLE_PERK_PROPERTIES,
		TABLE_PERKS,
		TABLE_PERK_PROGRESSION,
		TABLE_RIFT_EVENT_CONFIG,
		TABLE_RIFT_SUB_EVENT_CONFIG,
		TABLE_RIFT_CONFIG,
		TABLE_RIFT_ZOMBOSS_REWARDS,
		TABLE_RIFT_LEVEL_UNLOCKS,
		TABLE_RIFT_FIRST_CLEAR_REWARDS,
		TABLE_BOARDGRIDMAPS,
		TABLE_LEVELMODULESDIFFICULTY,
		TABLE_LEVELMUTATORMODULES,
		TABLE_LEVELMUTATORTABLES,
		TABLE_MAIN_THEME_PROPERTIES,
		TABLE_THEME_PROPERTIES,
		TABLE_THEMES,

		TABLE_AREA_MAIN_PROPERTIES,
		TABLE_AREA_PROPERTIES,
		TABLE_AREAS,

		TABLE_ARTIFACT_PROPERTIES,
		TABLE_ARTIFACT,
		TABLE_ARTIFACT_DISPLAY_ACTIONS,
		TABLE_ARTIFACT_CULTIVATION,
		TABLE_ARTIFACTIMPROVEDPROPERTIES,

		TABLE_PVZ1_CONFIG, // for pvz1 mode config

		TABLE_CUSTOM_LEVEL_CONFIG,
		TABLE_CUSTOM_LEVEL_DATA,

		TABLE_CARD_GAME_BOARD_CONFIG,

		TABLE_HOTUICONFIG,
		TABLE_HOTUI_WIDGETS,			// Hot loaded UIs in memory
		TABLE_HOTUI_COMPONENTS,         // Hot loaded components in memory
		TABLE_HOTUI_PROPERTYSHEETS,		// Hot loaded property sheets in memory
		TABLE_HOTUI_COLORS,             // Colors
		TABLE_HOTUI_COLORS_ALIASES,

		TABLE_LEVELSCORINGRULES,

		TABLE_JOUST_PLANT_POWER_CONFIG,

		TABLE_PROBABILITY_CONFIG,

		TABLE_ARCADECONFIG,

		TABLE_TRAVELLOG_CONFIG,
		TABLE_TRAVELLOG_STATUS,

		TABLE_DAVETREASURE_CONFIG,

		TABLE_PLANTNEWAVATARS,

		TABLE_RICHMAN_EVENT_CONFIG,

		TABLE_GENERALTASK_CONFIG,

		TABLE_LEVELEDITOR_CONFIG,

		TABLE_COLLECTION_CONFIG,

		TABLE_CARD_CONFIG,

		TABLE_CARD_OBJECTS,

		TABLE_GENEENHANCEMENT_CONFIG,

		TABLE_CTHULHU_CONFIG,

		TABLE_LEVEL_MODIFIER_MODULE_COLLECTION_CONFIG,
		TABLE_LEVEL_MODIFIER_MODULE_CONFIG,

		TABLE_RESISTENCE_CONFIG,
		TABLE_RESILIENCE_CONFIG,

		TABLE_UNCHARTED_BOOST_PROPERTIES,
		TABLE_HEROPLANT_CONFIG,
        
		TABLE_COUNT,
		TABLE_DYNAMIC_BEGIN = TABLE_COUNT
	};

	struct TableSchema
	{
		TableSchema()
		{}
		TableSchema(TableIndex i_index, const RtName& i_rtName, const std::string& i_prettyName, bool i_fixedContent, bool i_gameObjectTable, const std::string i_packageResource = "")
		{
			Index = i_index;
			Name = i_rtName;
			PrettyName = i_prettyName;
			FixedContent = i_fixedContent;
			PackageResource = i_packageResource;
			SerializableGameObjects = i_gameObjectTable;
		}
		
		TableIndex 	Index;						// Table index
		RtName		Name;						// Actual table name string used to look up the table in RtDb
		std::string PrettyName;					// 'Pretty' name used when displaying this table remotely
		bool		FixedContent;				// True if this table holds immutable data (ask chargrove!)
		bool		SerializableGameObjects;	// True if this table should be part of the load/save process
		
		std::string PackageResource; // (Optional) Generic resource that points to this table's package file
	};
	
	struct TableRuntimeInfo
	{
		uint32		TableIndex;
		RtName		TableName;
		bool		PackageLoaded;
	};
	
	PVZDB()
	{
		m_initialized = false;
		m_highestClaimedDynamicTableIndex = static_cast<PVZDB::TableIndex>(TABLE_DYNAMIC_BEGIN - 1);
	}

	void InitializeTables();
	bool IsInitialized() const;
	
	void LoadAllPackages();
	void LoadDefaultPackageForTable(TableIndex i_table);
	bool LoadPackageForTableFromRTONFile(TableIndex i_table, const std::string& i_filename);
	void LoadPackageForTable(TableIndex i_table, RtWeakPtr<GenericResFile> i_packageResource);
    //PVZ2_CHINESE_START
    bool LoadPackageForTableFromFile(TableIndex i_table, const std::string& i_filename, bool i_strictUids = false, const bool i_FileEncryption = false);
	//PVZ2_CHINESE_END
    void LoadPackageForTableFromBuffer(TableIndex i_table, RtSerialRtonReader& rtonReader, bool i_strictUids = false);
    bool LoadPackageForTableFromJson(TableIndex i_table, const std::string& i_json, bool i_stringUids = false);
    

    void SetPackageLoaded(const PVZDB::TableIndex i_table, const bool i_value);
    
    //PVZ2_CHINESE_START
    bool SavePackageForTableToFile(PVZDB::TableIndex i_table, const std::string& i_filename, const bool i_asJSON = false, const bool i_FileEncryption = false);

    bool SavePackageFromNetJsonStringToFile(PVZDB::TableIndex i_table,
    										const std::string & sNetJson,
    										const std::string & i_filename,
    										const bool i_asJson = false,
    										const bool i_FileEncryption = false);
    //PVZ2_CHINESE_END
	void ReleasePackageForTable(TableIndex i_table);
	void ReleaseAllPackages();
	
	void Shutdown();
	
	std::string GetTableName(TableIndex i_inTable);
	TableIndex ClaimDynamicTable(bool i_resetTable);
	void ReleaseDynamicTable(TableIndex i_tableIndex);

	RtDbTable* GetTable(TableIndex i_inTable);
	
	RtDbTable::Iterator GetObjectIteratorForTable(TableIndex i_inTable);
	RtId GetIdByAlias(TableIndex i_inTable, RtName i_alias);

	template<class T>
	RtWeakPtr<T> FindObjectByAlias(TableIndex i_inTable, RtName i_alias)
	{
		RtId objId = GetIdByAlias(i_inTable, i_alias);
		return RtWeakPtr<T>(objId);
	}
	
	RtId FindFirstObjectByClass(TableIndex i_index, RtClass* i_class);

	template<class T>
	RtWeakPtr<T> FindFirstObjectByClass(TableIndex i_index)
	{
		RtId objId = FindFirstObjectByClass(i_index, T::StaticGetClass());
		return RtWeakPtr<T>(objId);
	}

	void SaveGameState(bool i_special);
	void LoadGameState(bool i_special);
	Event0 OnPostLoadGameState;
	
	void DestroyGameObjects();
	void RunDeferredDeletions();
    void VerifyGameObjectTablesAreEmpty();
	
	void DebugPrintTableInfo(PVZDB::TableIndex i_table);
	void DebugPrintTableContents(PVZDB::TableIndex i_table);
	
    //c03 add for dlc db
    void RefreshPackageForTable(TableIndex i_table, RtWeakPtr<GenericResFile> i_packageResource);
	
private:
    bool isPredefinedTable(TableIndex i_tableIndex) const;
	bool isDynamicTable(TableIndex i_tableIndex) const;
	bool isTableIndexValid(TableIndex i_tableIndex) const;
	PVZDB::TableSchema& getTableSchema(TableIndex i_tableIndex);
	const PVZDB::TableSchema& getTableSchema(TableIndex i_tableIndex) const;
	PVZDB::TableRuntimeInfo& getRuntimeInfo(TableIndex i_tableIndex);
	void createTableForSchema(const TableSchema& i_schema) const;
	void constructGameInfoObjects();
	void releaseGameInfoObjects();
    void onGameObjectSerialized(class GameObject *i_object);
	
	std::vector<PVZDB::TableSchema> m_PVZTableSchema;
	std::vector<PVZDB::TableRuntimeInfo> m_PVZTableRuntimeInfo;
	bool m_initialized;
	std::vector<PVZDB::TableIndex> m_freeDynamicTableIndices;
	std::map<PVZDB::TableIndex, PVZDB::TableSchema> m_dynamicTableSchema;
	std::map<PVZDB::TableIndex, PVZDB::TableRuntimeInfo> m_dynamicTableRuntimeInfo;
	PVZDB::TableIndex m_highestClaimedDynamicTableIndex;
};


#endif // __PVZDB_H__
