#ifndef IdleAnimationSelector_hpp
#define IdleAnimationSelector_hpp

#include "GameObject.h"
#include "ProbabilityPicker.h"

typedef ProbabilityValueRecord<std::string> ProbabilityStringRecord;

class IdleAnimationSelector : public GameObject
{
public:
	RT_CLASS_DEFINE(IdleAnimationSelector, GameObject, RtClass);
	
	void SetWeights(const std::vector<int>& i_weights);
	std::string GetLabel();
	
private:
	std::vector<ProbabilityStringRecord> convertWeightsToEntries(const std::vector<int>& i_weights);
	
	ProbabilityPicker m_picker;
	std::vector<ProbabilityStringRecord> m_entries;
	std::string m_lastLabel;
};

#endif /* IdleAnimationSelector_h */
