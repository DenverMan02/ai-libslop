#ifndef UICHESTAWARD_h
#define UICHESTAWARD_h

#include "DNode/DNodeWidget.h"

struct ChestAwardContent
{
    int Id;
    int Quantity;
};

class UIChestAward: public DNodeWidget
{
public:
    static UIChestAward* create(const std::vector<ChestAwardContent>& rewards, std::string effectName = "effects/ChestHardLevel_Chest");
    UIChestAward(const std::vector<ChestAwardContent>& rewards, std::string effectName = "effects/ChestHardLevel_Chest");
    virtual ~UIChestAward();
    
    virtual void Initialize() override;
    void setChestEffect(const std::string& i_effect) { m_chestEffect = i_effect; }
    void setEndCallBack(const std::function<void(DTransformNode*)>& i_callBack) { m_endCallFunc = i_callBack; };
private:
    DAnimNode*                  				m_pChest;
	std::vector<ChestAwardContent>          	m_rewards;
	bool										m_bBoxIsOpen;
    std::string                                 m_chestEffect;
    std::function<void(DTransformNode*)>        m_endCallFunc;
	static UIChestAward* 						s_pWidgetHandler;
};

#endif
