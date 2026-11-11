#ifndef __ANIMRIGLAYERSET_H__
#define __ANIMRIGLAYERSET_H__

#include "GameObject.h"
#include "PopAnimRig.h"

class AnimRigLayerSet : public GameObject
{
	RT_CLASS_DEFINE(AnimRigLayerSet, GameObject, RtClass);
public:
	AnimRigLayerSet();
	void AddSet(std::string setName, std::vector<std::string> layerNames);
	void ShowSet(PopAnimRig* animRig, std::string setName);
private:
	std::map<std::string, std::vector<std::string>> m_layerSets;
	std::string m_currentLayerName;
};

#endif // __ANIMRIGLAYERSET_H__
