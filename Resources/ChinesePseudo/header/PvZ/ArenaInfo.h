/*
 * ArenaInfo.h
 *
 *  Created on: 2015-9-25
 *      Author: jianglc
 */

#ifndef ARENAINFO_H_
#define ARENAINFO_H_

#include "PVZTypes.h"

enum PVPTutorialState
{
    PVPTUTORIAL_NONE,
    PVPTUTORIAL_STARTPVP,
    PVPTUTORIAL_DEFEND,
    PVPTUTORIAL_DEFENDWAR,
    PVPTUTORIAL_TRAINZB,
    PVPTUTORIAL_TRAINZBWAR,
    PVPTUTORIAL_ATTACK,
    PVPTUTORIAL_ATTACKWAR,
    PVPTUTORIAL_OCCUPY,
    PVPTUTORIAL_OCCUPY_MAP,
    PVPTUTORIAL_EDITPLANT,
    
    PVPTUTORIAL_FINISH,
};

struct ArenaPlantInfo
{
	ArenaPlantInfo()
	{
		Row = 0;
		Column = 0;
	}

	bool operator==(const ArenaPlantInfo& i_compareTo) const
	{
		if(Type == i_compareTo.Type && Row == i_compareTo.Row && Column == i_compareTo.Column)
		{
			return true;
		}

		return false;
	}

	PlantTypePtr Type;
	int Row;
	int Column;
};

typedef std::vector<ArenaPlantInfo> ArenaPlantInfos;

struct ArenaInfo
{
	ArenaInfo()
	{
		ArenaPlantList1.clear();
        ArenaPlantList2.clear();
        ArenaPlantList3.clear();
	}

	ArenaInfo(const ArenaInfo& i_info)
	{
		ArenaPlantList1 = i_info.ArenaPlantList1;
        ArenaPlantList2 = i_info.ArenaPlantList2;
        ArenaPlantList3 = i_info.ArenaPlantList3;
	}

	bool operator==(const ArenaInfo& i_compareTo) const
	{
		bool preSeedBankCompare =

			(i_compareTo.ArenaPlantList1.size() == ArenaPlantList1.size()) &&
            (i_compareTo.ArenaPlantList2.size() == ArenaPlantList2.size()) &&
            (i_compareTo.ArenaPlantList3.size() == ArenaPlantList3.size());

		if (!preSeedBankCompare)
		{
			return false;
		}

		for (size_t i = 0; i < ArenaPlantList1.size(); i++)
		{
			bool compareFound = false;
			for (size_t j = 0; j < i_compareTo.ArenaPlantList1.size(); j++)
			{
				if (i_compareTo.ArenaPlantList1[j] == ArenaPlantList1[i])
				{
					compareFound = true;
					break;
				}
			}

			if (!compareFound)
			{
				return false;
			}
		}
        
        for (size_t i = 0; i < ArenaPlantList2.size(); i++)
        {
            bool compareFound = false;
            for (size_t j = 0; j < i_compareTo.ArenaPlantList2.size(); j++)
            {
                if (i_compareTo.ArenaPlantList2[j] == ArenaPlantList2[i])
                {
                    compareFound = true;
                    break;
                }
            }
            
            if (!compareFound)
            {
                return false;
            }
        }
        
        for (size_t i = 0; i < ArenaPlantList3.size(); i++)
        {
            bool compareFound = false;
            for (size_t j = 0; j < i_compareTo.ArenaPlantList3.size(); j++)
            {
                if (i_compareTo.ArenaPlantList3[j] == ArenaPlantList3[i])
                {
                    compareFound = true;
                    break;
                }
            }
            
            if (!compareFound)
            {
                return false;
            }
        }
		// Made it this far, thus, we are the same
		return true;
	}

	void		RestartArenaInfo();

	ArenaPlantInfos		ArenaPlantList1;
    ArenaPlantInfos		ArenaPlantList2;
    ArenaPlantInfos		ArenaPlantList3;
};


#endif /* ARENAINFO_H_ */
