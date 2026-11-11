//
//  TrainingCamp.h
//  PlantsVersusZombies2
//
//  Created by Wu, Emma on 2015.10.29
//  Copyright (c) 2015 PopCap Games. All rights reserved.
//

#ifndef __PlantsVersusZombies2__TrainingCamp__
#define __PlantsVersusZombies2__TrainingCamp__

#include "GameObject.h"
#include "TrainingType.h"


//-----------------------------------------------------------
enum enumTrainingOperator
{
    Training_None,
    Training_Add,
    Training_Cancel,
    Training_Finish,
};

//-----------------------------------------------------------
class TrainingData
{
public:
    TrainingData()
    : m_haveNum(0)
    , m_trainNum(0)
    , m_trainRemainTime(-1.0f)
    , m_trainEndTime(PVZ_EOT())
    , m_queueOrder(0)
    {}
    
    bool    IsValid() const;
    bool    IsEmpty() const;
    void    Training(enumTrainingOperator op);      // not used!
    int     GetTotalSeconds() const;
    
public:
    std::string     m_trainingType;
    int             m_haveNum;
    int             m_trainNum;
    float           m_trainRemainTime;
    
    // do not write
    float           m_trainEndTime;
    uint64           m_queueOrder;
};
typedef std::vector<TrainingData> VecTrainingDatas;

//-----------------------------------------------------------
class TrainingCamp
{
public:
	TrainingCamp();
	virtual ~TrainingCamp();
    
    void        Update();
    
    void        SetSpaceMax(int iVal) { m_SpaceMax = iVal; }
    int         GetSpaceMax() const { return m_SpaceMax; }
    
    void        SetTypeMax(int iVal) { m_TypeMax = iVal; }
    int         GetTypeMax() const { return m_TypeMax; }
    
    void        ClearTrainingDatas();
    void        AddTrainingData(const TrainingData& data);
    TrainingData GetTrainingData(const std::string& i_name);
    TrainingData GetCurrentTrainingData();
    void        SetTrainingData(const std::string& i_name, const TrainingData& data);
    const VecTrainingDatas&     GetTrainingDatas() const { return m_TrainingDatas; }
    void        GetHaveDatas(VecTrainingDatas& outDatas);     // sorted
    void        SetTraining(const std::string& i_name, enumTrainingOperator op);
    bool        IsFullSpace() const { return m_bFullSpace; }
    bool        IsFullType() const { return m_bFullType; }
    
    int         GetTrainingSpace();
    int         GetSpaceUsed();
    int         GetTypeNum();
    
protected:
    VecTrainingDatas::iterator   findTrainingData(const std::string& i_name);
	
protected:
    int             m_SpaceMax;
    int             m_TypeMax;
    VecTrainingDatas    m_TrainingDatas;
    bool            m_bFullSpace;
    bool            m_bFullType;
};


#endif /* defined(__PlantsVersusZombies2__TrainingCamp__) */
