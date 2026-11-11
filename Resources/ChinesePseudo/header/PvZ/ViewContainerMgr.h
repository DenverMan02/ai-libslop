/*
 * ViewContainerMgr.h
 *
 *  Created on: 2018-9-26
 *      Author: Administrator
 */

#ifndef VIEWCONTAINERMGR_H_
#define VIEWCONTAINERMGR_H_

#include "core.h"

class IViewContainer;

class ViewContainerMgr : public LazySingleton<ViewContainerMgr>
{
public:
	ViewContainerMgr();

    void InitializeSDK();

    void ShowWebView(const std::string& i_url);

    void PassCallSettlement(const std::string& i_key, int i_count);

    void PassCallLottery(const std::string& i_key, int i_id, int i_quantity, int i_index);

    void PassCallScoreStoreInfo(const std::string& i_key, const std::string& i_info);

    void PassCallScoreStoreBuy(const std::string& i_key, int i_id);

    void PassCallConsumeCash(const std::string& i_key, int i_num);

    void PassCallAddPlayTimes(const std::string& i_key, int i_result);

private:
    IViewContainer* m_viewContainerMgr;
};


#endif /* VIEWCONTAINERMGR_H_ */
