//
//  WeightedOption.h
//  PlantsVersusZombies2
//
//  Created by Sola, Joseph on 6/15/17.
//  Copyright © 2017 PopCap Games. All rights reserved.
//

#ifndef WeightedOption_h
#define WeightedOption_h

class IWeightedOption
{
public:
	virtual ~IWeightedOption() {}
	virtual float GetWeight() const = 0;
};

template<typename T>
class ConstWeightedOption : public IWeightedOption
{
public:
	ConstWeightedOption()
	{}
	
	ConstWeightedOption(T i_value, float i_weight)
	: Value(i_value)
	, Weight(i_weight)
	{}
	
	virtual float GetWeight() const
	{
		return Weight;
	}
	
	T Value;
	float Weight;
};

typedef ConstWeightedOption<std::string> StringWeightedOption;
typedef ConstWeightedOption<int> IntWeightedOption;
typedef ConstWeightedOption<float> FloatWeightedOption;

class WeightedOptionStubForRt : public RtObject
{
public:
	RT_CLASS_DEFINE(WeightedOptionStubForRt, RtObject, RtClass);
};

namespace WeightedOption
{
	template<typename T> // where T implements IWeightedOption
	typename std::vector<T>::iterator RollWeightedOptionGetIter(std::vector<T>& i_options, MTRand& i_rand)
	{
		DBG_ASSERT_MSG(i_options.size() > 0, "Tried to roll weighted option with size zero array of options!");
		
		float sum = 0.0f;
		for (auto option : i_options)
		{
			sum += option.GetWeight();
		}
		
		float selection = i_rand.Next(1.0f) * sum;
		for (auto iter = i_options.begin(); iter != i_options.end(); ++iter)
		{
			auto option = (*iter);
			sum -= option.GetWeight();
			if (sum <= selection)
				return iter;
		}
		return i_options.end() - 1;
	}
	
	template<typename T> // where T implements IWeightedOption
	T* RollWeightedOption(std::vector<T*>& i_options, MTRand& i_rand)
	{
		return (*RollWeightedOptionGetIter(i_options, i_rand));
	}
	
	// Returns a vector with min(i_count, i_options.size()) selections from the list of weighted options
	// Items in i_options will only be selected once
	template<typename T>
	std::vector<T> RollMultipleWeightedOptions(std::vector<T>& i_options, int i_count, MTRand& i_rand)
	{
		std::vector<T> selections;
		if (i_options.size() <= i_count)
		{
			selections.insert(selections.begin(), i_options.begin(), i_options.end());
			return selections;
		}
		
		std::vector<T> selectionPool(i_options);
		while (i_count > 0)
		{
			auto iter = RollWeightedOptionGetIter(selectionPool, i_rand);
			selections.push_back(*iter);
			selectionPool.erase(iter);
			i_count--;
		}
		
		return selections;
	}
}

#endif /* WeightedOption_h */
