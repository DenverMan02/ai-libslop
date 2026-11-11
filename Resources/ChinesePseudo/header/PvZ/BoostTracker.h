#ifndef __BOOST_TRACKER__
#define __BOOST_TRACKER__

#include<vector>
#include"PlantBoostPropertySheet.h"

class PlantBoostTracker
{
public:
    PlantBoostTracker()
    :m_destory(false)
    {}

    virtual ~PlantBoostTracker(){};

    virtual void Update(class Plant* plant) = 0;

private:
    bool m_destory;
    friend class PlantBoostTrackerManager;
};
 
class PlantBoostTrackerManager
{
public:
    PlantBoostTrackerManager();
    ~PlantBoostTrackerManager();

    template<class T>
    T* ApplyBoostTracker(PlantBoostType i_boostType)
    {
        if(m_trackers[i_boostType] != nullptr)
        {
            delete m_trackers[i_boostType];
        }
        m_trackers[i_boostType] = new T;
        return (T*)m_trackers[i_boostType];
    }
    void UpdateBoostTracker(class Plant* plant);

private:
    std::map<PlantBoostType, PlantBoostTracker*> m_trackers;
};


#endif