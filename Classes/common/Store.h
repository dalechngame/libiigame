// Created by wangwenjie on 2015/01

#ifndef __STORE_H__
#define __STORE_H__

#include "cocos2d.h"
#include "LBLibraryBase.h"
#include "LBModalDialogLayer.h"
#include "Common.h"

USING_NS_CC;

// 购买成功通知Key
#define NOTIFI_STORE_IAP_PURCHASED	"lbStoreIapPurchasedNotif"

#define RESTORE_TAG     9001
#define PURCHASED_TAG	9002
class Store;
typedef std::function<void (Store* store)> StoreClosedCallback;

/**
 * 商店
 * 购买成功不使用函数回调，而是使用通知，
 * 这样更灵活，可避免一些BUG的出现
 *
 * 一些规则：
 *   如果购买UnlockEverything(解锁全部)，则其它所有单内购也被购买（已由共通处理 参看 Common::isInAppPurchased）
 *   购买任意1个内购，则广告会被去除，则NoAds(解锁广告) 也被购买 （已由共通处理 参看 Common::isInAppPurchased）
 *   购买了解锁全部，或购买完了除掉"解锁全部"及"NoAds"的单内购以外的内购，（使用 Store::isUnlockAll 判断即可）
 *       则所有商店按钮都不再显示
 */
class Store : public LBModalDialog
{
protected:
    WJLayerJson *m_layerJson;
    std::string m_miniKey;
    
    StoreClosedCallback m_storeClosedCallback;
    
    bool m_purchased;
    
    bool m_adsIsVisible;
    
    void initStore();
    void initStoreMini();
    
    void refresh();
    void refreshStore();
    void refreshStoreMini();
    
    void initStoreItemButton(const char* buttonName, const char* lockKey, const WJTouchCallback& onClick);
    
    void onStoreItemClick(Node* node, WJTouchEvent* event);
    void onStoreMiniItemClick(Node* node, WJTouchEvent* event);
    
protected:
    void onInAppPurchaseCallback(int tag, const char* value);
    
protected:
    virtual void doCloseHide() override;
    virtual void doShowAnimation(int animationType) override;
    virtual void doCloseAnimation(int animationType) override;
    
    virtual void onDialogShown() override;
    
public:
    Store();
    virtual ~Store();
    
    virtual bool init(const char* miniKey);
    virtual void onEnter() override;
    
    void setOnClosed(const StoreClosedCallback& callback);
    
    void closeStore(bool bInvokeCloseEvent = true);
    
public:
    /// 显示商店
    static Store* showStore();
    
    /// 显示Mini商店(单个内购, key参数为 lock.plist 中对应的key)
    static Store* showStoreMini(const char* key);
    
    /// 是否已经购买了全部(可能是直接购买了解锁全部，或单独购买了所有单内购)
    static bool isUnlockedAll();
    
    /// 取得单价
    static std::string getPrice(const char* iapId, ValueVector* productInfoArray);
    static std::string getPrice(const char* iapId);
    
};

#endif // __STORE_H__
