#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include "PropertySheetBase.h"
#include "PlantBoostPropertySheet.h"

typedef RtWeakPtr<class CollectionType> CollectionTypePtr;

class CollectionType : public PropertySheetBase
{
public:
	RT_CLASS_DEFINE(CollectionType, PropertySheetBase, RtClass);

    std::string CollectionName;
    std::vector<std::string> Names;
    std::string Description;
    std::vector<std::vector<std::string>> DesStuff;
    int MaxRare;
	std::vector<std::vector<PlantBoost>> Boosts;
    std::vector<std::string> BlackList;
};


namespace CollectionUtils
{

    void GetCollectionBoostForPlant(std::vector<const PlantBoost*>& i_Boosts, int i_plantID, PlantBoostType i_boostType);
    SexyString GetPlayerCollectionName(int i_collectionId);
    SexyString GetCollectionName(int i_collectionId, int i_rare);
    SexyString GetPlayerCollectionDescription(int i_collectionId);
    SexyString GetCollectionDescription(int i_collectionId, int i_rare);
    CollectionTypePtr GetCollectionConfig(int i_collectionId);

    std::string GetCollectionImageName(int i_collectionId, int i_rare);
    Sexy::Image* GetCollectionImage(int i_collectionId, int i_rare, bool i_default = true);


}

#endif
