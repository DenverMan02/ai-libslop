//
//  ProbabilityBucket.h
//  PlantsVersusZombies2
//
//  Created by Terry Franguiadakis on 1/23/12.
//  Copyright (c) 2012 PopCap Games. All rights reserved.
//

#ifndef PlantsVersusZombies2_ProbabilitySet_h
#define PlantsVersusZombies2_ProbabilitySet_h

#include "Common.h"
#include "MTRand.h"

// Probability Set.
//
// A weighted collection of items, from which we pick one of the items based on its weight. 
// The larger the weight the more likely the item will be picked. It's possible to have 
// a percentage table by assigning weights to items so the weights add up to 100. 
// for example:
//   {10,20,70} would create three items at those percentages. 
//
// Usage:
// This is a template class so this can be a set of any type. 
// 
// 
// ProbabilitySet<MyType> ps;
//
// ps.AddItem(someItem, 10);
// ps.AddItem(otherItem, 20);
// ps.AddItem(lastItem, 70);
//
// MyType item = ps.PickItem();
// 
// we can ignore the last picked item by calling... 
// MyType newitem = ps.PickItemIgnoring(item);
//

// this class's functionality could be replaced by std::discrete_distribution
template <typename T>
class ProbabilitySet 
{
private:
    struct ProbabilityBucket 
    {
        ProbabilityBucket (T i_item, int i_weight): m_item(i_item), m_weight(i_weight) {}

        T		m_item;
        int		m_weight;
    };
    
public:
    ProbabilitySet():m_totalWeight(0), m_rand(NULL), m_ownsRand(false) {}
	ProbabilitySet(unsigned long i_randSeed):m_totalWeight(0)
	{
		m_rand = new Sexy::MTRand(i_randSeed);
		m_ownsRand = true;
	}
	ProbabilitySet(Sexy::MTRand *i_rand)
	: m_totalWeight(0)
	, m_rand(i_rand)
	{
		m_ownsRand = false;
	}

	~ProbabilitySet()
	{
		if (m_ownsRand)
		{
			delete m_rand;	
		}
		
		m_rand = NULL;
	}
    
    size_t GetSize() 
    { 
        return m_weightSet.size();
    }
    
    void AddItem(T i_item, int i_weight) 
    {
		// If the item already exists, modify its weight.
		// Otherwise, we add it.
		
		bool addingItem = true;
		
		for (size_t i = 0; i < m_weightSet.size(); i++)
		{
			if (m_weightSet[i].m_item == i_item)
			{
				addingItem = false;
				m_totalWeight += (i_weight - m_weightSet[i].m_weight);
				m_weightSet[i].m_weight = i_weight;
				break;
			}
		}

		if (addingItem)
		{
			m_weightSet.push_back(ProbabilityBucket(i_item, i_weight));
			m_totalWeight += i_weight;
		}
    }
	
	bool HasItem(const T& i_item) const
	{
		for (size_t i = 0; i < m_weightSet.size(); ++i)
		{
			if (m_weightSet[i].m_item == i_item)
			{
				return true;
			}
		}
		return false;
	}

	void RemoveItem(T i_item) 
	{
        for (auto itr = m_weightSet.begin(); itr != m_weightSet.end(); )
        {
            if ((*itr).m_item == i_item)
            {
                m_totalWeight -= (*itr).m_weight;
                itr = m_weightSet.erase(itr);
            }
            else
            {
                ++itr;
            }
        }
	}

	void Clear()
	{
		m_totalWeight = 0;
		m_weightSet.clear();
	}

    T PickItem()
    {
        DBG_ASSERT(m_totalWeight > 0);

        int pick = rand(m_totalWeight);
        int acculumatedWeight = 0;

        for (size_t i = 0; i < m_weightSet.size(); i++)
        {
            acculumatedWeight += m_weightSet[i].m_weight;

			if (pick < acculumatedWeight)
            {
                return m_weightSet[i].m_item;
            }
        }
        
        DBG_ASSERT(false);
        return T();
    }
	
	T PickItemIgnoring(const T& i_ignoredValue)
	{
		size_t ignoredEntryIndex = -1;
		for (size_t i = 0; i < m_weightSet.size(); ++i)
		{
			if (m_weightSet[i].m_item == i_ignoredValue)
			{
				ignoredEntryIndex = i;
				break;
			}
		}
		
		if (ignoredEntryIndex == -1)
		{
			// That value isn't even in our buckets!
			return PickItem();
		}
		
		DBG_ASSERT(m_weightSet.size() > 0);
		
		size_t pickedIndex = -1;
		if (m_weightSet.size() == 1)
		{
			// Only one item? Sorry, gotta pick that.
			pickedIndex = 0;
		}
		else if (m_weightSet.size() == 2)
		{
			// Only two items? Pick the one we didn't specify.
			pickedIndex = (ignoredEntryIndex == 0) ? 1 : 0;
		}
		else 
		{
			// Three or more items...
			// Decrement total weight by ignored item's weight
			int totalWeight = m_totalWeight;
			totalWeight -= m_weightSet[ignoredEntryIndex].m_weight;
			DBG_ASSERT(totalWeight > 0);
			
			// Pick an item from the remaining ones in the list
			int pick = rand(totalWeight);
			int accumWeight = 0;
			for (size_t i = 0; i < m_weightSet.size(); ++i)
			{
				if (i == ignoredEntryIndex)
				{
					continue;
				}
				accumWeight += m_weightSet[i].m_weight;
				if (pick < accumWeight)
				{
					pickedIndex = i;
					break;
				}
			}
		}
		
		DBG_ASSERT(pickedIndex >= 0);
		return m_weightSet[pickedIndex].m_item;
	}
    
private:
	int rand(int i_range)
	{
		if (m_rand != NULL)
		{
			return static_cast<int>(m_rand->Next(i_range));
		}
		
		return Sexy::Rand(i_range);
	}
	
    std::vector<ProbabilityBucket>	m_weightSet;
    int								m_totalWeight;
	Sexy::MTRand*					m_rand;
	bool m_ownsRand;
};



#endif
