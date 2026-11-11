/*
 * IViewContainer.h
 *
 *  Created on: 2018-9-26
 *      Author: Administrator
 */

#ifndef IVIEWCONTAINER_H_
#define IVIEWCONTAINER_H_

class IViewContainer
{
public:
    static IViewContainer* CreateViewContainerManager();

    virtual ~IViewContainer() {}

    virtual void Initialize() = 0;

    virtual void ShowWebView(const std::string& i_url) = 0;

    virtual void PassCallSettlement(const std::string& i_key, int i_count) = 0;

    virtual void PassCallLottery(const std::string& i_key, int i_id, int i_quantity, int i_index) = 0;

    virtual void PassCallScoreStoreInfo(const std::string& i_key, const std::string& i_info) = 0;

    virtual void PassCallScoreStoreBuy(const std::string& i_key, int i_id) = 0;

    virtual void PassCallConsumeCash(const std::string& i_key, int i_num) = 0;

    virtual void PassCallAddPlayTimes(const std::string& i_key, int i_result) = 0;
};

#endif /* IVIEWCONTAINER_H_ */
