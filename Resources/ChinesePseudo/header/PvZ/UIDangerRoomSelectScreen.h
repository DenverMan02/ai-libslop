/*
 * UIDangerRoomSelectScreen.h
 *
 *  Created on: 2020-2-10
 *      Author: Administrator
 */

#ifndef UIDANGERROOMSELECTSCREEN_H_
#define UIDANGERROOMSELECTSCREEN_H_

#include "DNode/DNodeWidget.h"

namespace Message
{
	void DangerRoomSelectResultClosed();
	void DangerRoomSelectScreenClosed();
}

enum SelectMode
{
	Update_Select_None,
	Update_Select_Current,
	Update_Select_All
};

class UIDangerRoomSelectScreenResult:public DNodeWidget
{
public:
    static UIDangerRoomSelectScreenResult* create(const std::vector<int>& list,bool focus = true);

    virtual ~UIDangerRoomSelectScreenResult();

    virtual void Initialize() override;

    virtual void UserInit() override;

public:
    static UIDangerRoomSelectScreenResult* s_pWidgetHandler;
    std::vector<int>          m_list;
};

class UIDangerRoomSelectScreen:public DNodeWidget
{
public:
    static UIDangerRoomSelectScreen* create(bool focus = true);

    UIDangerRoomSelectScreen();
    virtual ~UIDangerRoomSelectScreen();

    virtual void Initialize() override;

    virtual void UserInit() override;

    static UIDangerRoomSelectScreen* s_pWidgetHandler;

    void updatePlantsShow(int i_mode);
	void updateItems(const std::vector<int>& list);
	void updatePlantList(int i_mode);
	void checkTutorial();

private:
	void initMaxSelect();
	void initPlantList();
	void initSelectList();
	void InitTestData();
	void updateSelectList(const std::vector<int>& i_list);
	void updateSelectList(int i_id, bool i_add);
	void onSelectListUpdated(SelectMode i_mode = Update_Select_None);
	void updateSelectInfo();
	void updateSelectBox(const std::vector<int>& list);
	void fastSelect();
	bool canSelect();
	void save();
	void onDangerRoomSelectResultClosed();
	void onDangerRoomSelectListSaved();
	void updateSaveBtn();
	void onNarrationFinished();
	std::vector<int> m_plantList;
	std::vector<int> m_initPlantList;
	std::vector<int> m_selectedPlantList;
	int m_maxSelect;
};

#endif /* UIDANGERROOMSELECTSCREEN_H_ */
