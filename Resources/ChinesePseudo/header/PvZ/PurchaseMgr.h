/*
 * PurchaseMgr.h
 *
 *  Created on: 2016-8-9
 *      Author: jianglc
 */

#ifndef PURCHASEMGR_H_
#define PURCHASEMGR_H_

#include "Singleton.h"
#include "NetworkData.h"

namespace Message
{
	void NotifyPurchaseResult(bool i_success, const std::string& i_skuId, int i_errorCode);
	void NotifyRetreiveLostOrderEnd();
}

enum PurchaseValidationState
{
	NOT_IN_VALIDATION,
	FIRST_TRY,
	SECOND_TRY
};

class PurchaseMgr : public LazySingleton<PurchaseMgr>
{

public:
	enum ValidationResult
	{
		RESULT_PENDING = 2,
		RESULT_SUCCESS = 3,
		RESULT_INVALID = 4,
		RESULT_COMPLETED_ORDER = 8
	};

    PurchaseMgr();
    ~PurchaseMgr();

    // Init purchase order when user start to request payment
    void InitPurchaseOrder(const std::string& i_sku);
    void onNotifyPurchaseInit(int i_errorCode, const std::string& i_orderId, const std::string& i_skuId);
    void onNotifyPurchaseValidation(int i_errorCode, const std::string& i_skuId, int i_status);
    void onNotifyLostPurchaseOrder(int i_errorCode, const S2C_Purchase_LostPurchaseOrder& i_order);

    // Validate purchase order after initialization
    void ValidatePurchaseOrder(const std::string& i_sku, bool isRestore);

    void SetOrderId(const std::string& i_orderId);
    void SetChannelId(const std::string& i_channelId);
    void SetIsOnlinePay(bool isOnlinePay) { m_isOnlinePay = isOnlinePay; }

    const std::string& GetOrderId() { return m_orderId; }
    const std::string& GetChannelId() { return m_channelId; }
    const std::string& GetProductId() { return m_productId; }

    void ResetPurchaseInfo();

    void SetValidateState(PurchaseValidationState i_state) { m_validateState = i_state; }

    // Try acquire lost purchase order after user login
    void RequestLostPurchaseOrder();
    void TryRetreiveLostOrders();
    void FinishRetreiveLostOrders();
    bool IsRetreivingLostOrders() { return m_requestLostOrders; }

private:
    void onNetworkError(int erroId);
    void TryValidateAgain();
    void DoValidateAgain();

    std::string m_orderId;
    std::string m_channelId;
    std::string m_productId;
    PurchaseValidationState m_validateState;
    std::vector<PurchaseOrderInfo> m_lostOrders;
    bool m_requestLostOrders;
    bool m_isOnlinePay;
};


#endif /* PURCHASEMGR_H_ */
