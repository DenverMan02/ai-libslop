//
//  ToolPackets.h
//  PlantsVersusZombies2
//
//  Created by Joseph Sola on 1/30/14.
//  Copyright (c) 2014 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__ToolPackets__
#define __PlantsVersusZombies2__ToolPackets__

#include <string>
#include <set>
#include "ObjectTypeDescriptor.h"
#include "Point.h"
#include "PowerTileSubsystem.h"
#include "RtDb.h"
#include "SexyVector.h"


class ToolPacketProps;

#define gToolPacketTypeMgr (ObjectTypeDirectory<ToolPacketProps>::GetInstancePtr())
typedef ObjectTypeDirectory<ToolPacketProps>::Iterator			ToolPacketTableIter;
typedef ObjectTypeDirectory<ToolPacketProps>::ObjectTypePtr		ToolPacketTablePtr;

typedef RtWeakPtr<class ToolPacketProps> ToolPacketPropsPtr;

class ToolPacketProps : public ObjectTypeDescriptor
{
	RT_CLASS_DEFINE(ToolPacketProps, ObjectTypeDescriptor, RtClass);
    
	std::string ToolPacketClass;
	std::string ResourceGroup;
	std::string TypeToSpawn;
	SexyVector2 SpawnOffset;
	std::string SpawnSound;
	std::string CursorPopAnim;
	std::string CursorAnim;
	SexyVector2	CursorOffset;
	
	// Currently here to avoid the code-based table conversion - could be handled better
	PowerTileClass	PowerTileType;
	int			Cost;
	std::vector<int> CostList;
	int			CostInterval;
};

class ToolPacketData : public Sexy::RtObject
{
public:
	RT_CLASS_DEFINE_ABSTRACT(ToolPacketData, Sexy::RtObject, Sexy::RtClass) {}
	
	ToolPacketData() {}
	virtual ~ToolPacketData() {}
    
	virtual void SetData(ToolPacketPropsPtr i_props) { m_properties = i_props; }
	
	virtual bool CanUseAt(const Sexy::Point& i_position) = 0;
	virtual bool UseAt(const Sexy::Point& i_position) = 0;
	virtual void GatherResourceRequirements(std::set<std::string> &io_resourceGroupNames);
	virtual class PopAnimRig* CreateCursorAnimRig();
	virtual Sexy::SexyVector2 GetCursorAnimRigOffset() const;
	virtual int GetCost(int i_useCount);
	ToolPacketPropsPtr GetProps() const;
	
protected:
	ToolPacketPropsPtr m_properties;
};

class ToolPacketData_Dummy : public ToolPacketData
{
public:
	RT_CLASS_DEFINE(ToolPacketData_Dummy, ToolPacketData, RtClass) {}
    
	bool CanUseAt(const Sexy::Point& i_position) override;
	bool UseAt(const Point& i_position) override;
	class PopAnimRig* CreateCursorAnimRig() override;
	Sexy::SexyVector2 GetCursorAnimRigOffset() const override;
};

/// ToolPacketData_PowerTile
///	- Handles power tile seed packet functionality
class ToolPacketData_PowerTile : public ToolPacketData
{
public:
	RT_CLASS_DEFINE(ToolPacketData_PowerTile, ToolPacketData, RtClass) {}
	
	bool CanUseAt(const Point& i_position) override;
	bool UseAt(const Point& i_position) override;
	class PopAnimRig* CreateCursorAnimRig() override;
	Sexy::SexyVector2 GetCursorAnimRigOffset() const override;
};

/// ToolPacketData_Projectile
///	- One-use projectiles
class ToolPacketData_Projectile : public ToolPacketData
{
public:
	RT_CLASS_DEFINE(ToolPacketData_Projectile, ToolPacketData, RtClass) {}
	
	bool CanUseAt(const Point& i_position) override;
	bool UseAt(const Point& i_position) override;
};

class ToolPacketData_RiftPlantLevelUp : public ToolPacketData
{
public:
	RT_CLASS_DEFINE(ToolPacketData_RiftPlantLevelUp, ToolPacketData, RtClass) {}

	bool CanUseAt(const Point& i_position) override;
	bool UseAt(const Point& i_position) override;

	int GetCost(int i_useCount) override;

private:
	void CheckAllSeedPackets();
};

class ToolPacketData_RiftPlantfood : public ToolPacketData
{
public:
	RT_CLASS_DEFINE(ToolPacketData_RiftPlantfood, ToolPacketData, RtClass) {}

	bool CanUseAt(const Point& i_position) override;
	bool UseAt(const Point& i_position) override;

	int GetCost(int i_useCount) override;
};

class ToolPacketData_RiftArtifact : public ToolPacketData
{
public:
	RT_CLASS_DEFINE(ToolPacketData_RiftArtifact, ToolPacketData, RtClass) {}

	bool CanUseAt(const Point& i_position) override;
	bool UseAt(const Point& i_position) override;

	int GetCost(int i_useCount) override;
};

namespace ToolPacketDataFactory
{
	ToolPacketData* CreateData(const std::string& i_toolType);
};

namespace Message
{
	void NotifyToolPlantLevelUp();
	void NotifyToolPlantLevelUpMax(class ToolPacketData* i_data);
	void NotifyToolPlantfoodMax(ToolPacketData* i_data);
}

#endif /* defined(__PlantsVersusZombies2__ToolPackets__) */
