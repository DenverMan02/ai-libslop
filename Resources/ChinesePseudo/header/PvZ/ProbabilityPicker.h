#ifndef ProbabilityPicker_h
#define ProbabilityPicker_h

template<class ValueType>
struct ProbabilityValueRecord
{
	ValueType	Value;
	int			Weight;
};

class ProbabilityPicker
{
public:
	template<class ValueType>
	ValueType Pick(const std::vector<ProbabilityValueRecord<ValueType> >& i_records) const
	{
		int totalWeight = calculateTotalWeight(i_records);
		
		int pick = RandRangeInt(0, totalWeight - 1);
		int acculumatedWeight = 0;
		
		for (size_t i = 0; i < i_records.size(); i++)
		{
			acculumatedWeight += i_records[i].Weight;
			
			if (pick < acculumatedWeight)
			{
				return i_records[i].Value;
			}
		}
		
		DBG_ASSERT(false);
		return ValueType();
	}
	
private:
	template<class ValueType>
	int calculateTotalWeight(const std::vector<ProbabilityValueRecord<ValueType> >& i_records) const
	{
		int totalWeight = 0;
		
		for (auto record : i_records)
		{
			totalWeight += record.Weight;
		}
		
		return totalWeight;
	}
};

namespace ProbabilityPickerUtils
{
	template<class ValueType>
	std::vector<ProbabilityValueRecord<ValueType> > ConvertWeightsToEntries(const std::vector<ValueType>& i_weightedEntries)
	{
		std::vector<ProbabilityValueRecord<ValueType> > entries;
		for(const auto& weightedEntry : i_weightedEntries)
		{
			entries.push_back({weightedEntry, weightedEntry.Weight});
		}
		return entries;
	}
}

#endif