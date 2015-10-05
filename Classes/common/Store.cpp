// Created by wangwenjie on 2015/01

#include "Store.h"

Store* Store::showStore()
{
    return showStoreMini("");
}

Store* Store::showStoreMini( const char* key )
{
    if (Store::isUnlockedAll() || (key && strlen(key) > 0 && Common::isInAppPurchasedByKey(key)))
    {
        CCAssert(false, "bug");
        return nullptr;
    }
    
    Store *store = new Store();
    if (store && !store->init(key))
    {
        CC_SAFE_DELETE(store);
        return nullptr;
    }
    
    store->autorelease();
    
    Common::sound.play("Common:popup");
    
    // show
    Scene *runningScene = Director::getInstance()->getRunningScene();
    runningScene->addChild(store);
    
    store->show(LBModalDialogAnimationType::ScaleEaseBack);
    
    return store;
}


Store::Store() : LBModalDialog(),
m_layerJson(nullptr),
m_purchased(false),
m_storeClosedCallback(nullptr),
m_adsIsVisible(false)
{
    
}

Store::~Store()
{
    
}

bool Store::init(const char* miniKey)
{
    // init
    m_miniKey = miniKey;
    
    if (m_miniKey.size() > 0)
        initStoreMini();
    else
        initStore();
    
    m_layerJson->setSubNodeOnClick("close", [&](Node* node, WJTouchEvent* event)
                                   {
                                       closeStore();
                                   })->nodeInstance()->setTag(MENU_TAG_BACK);
    
    
    //	const Size& winSize = Director::getInstance()->getWinSize();
    m_layerJson->ignoreAnchorPointForPosition(false);
    m_layerJson->setAnchorPoint(Vec2(0.5f, 0.5f));
    m_layerJson->setPosition(winSize.width / 2, winSize.height / 2);
    
    // init dialog
    if (!LBModalDialog::init(m_layerJson, true))
    {
        CC_SAFE_DELETE(m_layerJson);
        return false;
    }
    
    return true;
}

bool Store::isUnlockedAll()
{
    std::string unlockAllIapId = Common::getUnlockAllIapId();
    if (Common::isInAppPurchased(unlockAllIapId.c_str(), false))
        return true;
    
    std::string unlockNoAdsIapId = Common::getUnlockNoAdsIapId();
    
    ValueVector infoArray = Common::getProductInfoArray();
    int n = 0;
    for (auto it = infoArray.begin(); it != infoArray.end(); it++)
    {
        ValueMap& dict = it->asValueMap();
        std::string productId = dict["productID"].asString();
        if (productId.compare(unlockAllIapId) == 0 || productId.compare(unlockNoAdsIapId) == 0)
            continue;
        
        n++;
        if (!Common::isInAppPurchased(productId.c_str(), false))
            return false;
    }
    
    return n > 0;
}

std::string Store::getPrice( const char* iapId, ValueVector* productInfoArray )
{
    for (auto it = productInfoArray->begin(); it != productInfoArray->end(); it++)
    {
        ValueMap& dict = it->asValueMap();
        if (dict["productID"].asString().compare(iapId) == 0)
        {
            return dict["productPrice"].asString();
        }
    }
    
    return "";
}

std::string Store::getPrice( const char* iapId )
{
    ValueVector infoArray = Common::getProductInfoArray();
    
    return getPrice(iapId, &infoArray);
}

void Store::doCloseHide()
{
    LBModalDialog::doCloseHide();
}

void Store::doShowAnimation( int animationType )
{
    // 默认效果
    LBModalDialog::doShowAnimation(animationType);
    
    // 自定义动画效果
    /*
     Node *node = m_contentNode->nodeInstance();
     node->stopAllActions();
     
     const Size& winSize = Director::getInstance()->getWinSize();
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
     
     node->setPositionY(winSize.height - origin.y + m_contentNode->getContentScaleSize().height / 2 + 20);
     node->setVisible(true);
     node->runAction(EaseBackOut::create(MoveTo::create(0.5f, m_contentNode->getSavedPosition())));
     */
}

void Store::doCloseAnimation( int animationType )
{
    // 默认效果
    LBModalDialog::doCloseAnimation(animationType);
    
    // 自定义动画效果
    /*
     Node *node = m_contentNode->nodeInstance();
     node->stopAllActions();
     
     const Size& winSize = Director::getInstance()->getWinSize();
     Vec2 origin = Director::getInstance()->getVisibleOrigin();
     
     Vec2 pos = Vec2(node->getPositionX(), winSize.height - origin.y + m_contentNode->getContentScaleSize().height / 2 + 20);
     
     node->runAction(MoveTo::create(0.3f, pos));
     */
}

void Store::onDialogShown()
{
    LBModalDialog::onDialogShown();
    
//    m_layerJson->playAllAnimation();
    	m_layerJson->getSubSprite("buyAllBotton")->runAction(
                                                             RepeatForever::create(
                                                                                   Sequence::create(
                                                                                                    ScaleTo::create(0.5f, 1.1f, 1.1f),
                                                                                                    ScaleTo::create(0.5f, 1.0f, 1.0f), NULL))
                                                             );
}

void Store::initStore()
{
    m_layerJson = WJLayerJson::create("game/json/store.json");
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    m_layerJson->getSubNodeByKey("restore")->setVisible(false);
    
#else
    m_layerJson->setSubNodeOnClick("restore", [&](Node* node, WJTouchEvent* event)
                                   {
                                       Common::sound.play("Common:button");
                                       WJUtils::inAppRestore(RESTORE_TAG, CC_CALLBACK_2(Store::onInAppPurchaseCallback, this));
                                   });
#endif
    
    refreshStore();
}

void Store::initStoreMini()
{
    m_layerJson = WJLayerJson::create("game/json/storemini.json");
    
    m_layerJson->setSubNodeOnClick("goMianStore", [&](Node* node, WJTouchEvent* event)
                                   {
                                       StoreClosedCallback callback = m_storeClosedCallback;
                                       closeStore(false);
                                       
                                       Store *store = Store::showStore();
                                       store->setOnClosed(callback);
                                   });
    
    refreshStoreMini();
}

void Store::refresh()
{
    if (m_miniKey.size() > 0)
        refreshStoreMini();
    else
        refreshStore();
}

void Store::refreshStore()
{
    initStoreItemButton("buyDecorationBotton", "AccessoriesAndCrown", CC_CALLBACK_2(Store::onStoreItemClick, this));
    initStoreItemButton("buyAllBotton", "Everything", CC_CALLBACK_2(Store::onStoreItemClick, this));
    initStoreItemButton("buyClothBotton", "AllGameAndClothingAndNipple", CC_CALLBACK_2(Store::onStoreItemClick, this));
    initStoreItemButton("noAddsBotton", "NoAds", CC_CALLBACK_2(Store::onStoreItemClick, this));
}

void Store::refreshStoreMini()
{
    initStoreItemButton("img_everything", "Everything", CC_CALLBACK_2(Store::onStoreMiniItemClick, this));
    initStoreItemButton("img_allother", m_miniKey.c_str(), CC_CALLBACK_2(Store::onStoreMiniItemClick, this));
    
    // load image
    if (m_miniKey.compare("Accessories") == 0)
    {
        m_layerJson->getSubSprite("img_allother")->loadSpriteTexture("store/popup_001.png");
    }
    else if (m_miniKey.compare("StreetHouse") == 0)
    {
        m_layerJson->getSubSprite("img_allother")->loadSpriteTexture("store/popup_005.png");
    }
    else if (m_miniKey.compare("Pet") == 0)
    {
        m_layerJson->getSubSprite("img_allother")->loadSpriteTexture("store/popup_006.png");
    }
}

void Store::initStoreItemButton( const char* buttonName, const char* lockKey, const WJTouchCallback& onClick )
{
    WJSprite *button = m_layerJson->getSubSprite(buttonName);
    button->setUserString(lockKey);
    
    bool purchased = Common::isInAppPurchasedByKey(lockKey);
    
    button->setOnClick(onClick);
    button->setClickAble(!purchased);
    
    WJSprite *purchaseNode = dynamic_cast<WJSprite *>(WJUtils::findChildByNameStartWith(button, "purchase"));
    if (purchaseNode)
    {
        purchaseNode->setVisible(false);
        if (purchased)
        {
            button->loadSpriteTexture(purchaseNode->getSpriteFileName());
        }
    }
    
    Label *priceLabel = (Label*)WJUtils::findChildByNameStartWith(button, "price");
    if (priceLabel)
    {
        priceLabel->setVisible(!purchased);
        priceLabel->setString(getPrice(Common::getLockIapId(lockKey).c_str()).c_str());
    }
}

void Store::onStoreItemClick( Node* node, WJTouchEvent* event )
{
    Common::sound.play("Common:button");
    
    WJBase *base = dynamic_cast<WJBase*>(node);
    std::string lockKey = base->getUserString();
    
    WJUtils::inAppPurchase(PURCHASED_TAG, Common::getLockIapId(lockKey.c_str()).c_str(),
                           CC_CALLBACK_2(Store::onInAppPurchaseCallback, this));
}

void Store::onStoreMiniItemClick( Node* node, WJTouchEvent* event )
{
    onStoreItemClick(node, event);
}

void Store::onInAppPurchaseCallback( int tag, const char* value )
{
    if (tag == PURCHASED_TAG || (tag == RESTORE_TAG && *value == ACTION_RESULT_IAP_RESTORE_SUCCESS))
    {
        m_purchased = true;
        
        // 购买成功立即关闭，请根据需要控制
        bool purchaseOne = true;
        
        // 不立即关闭，刷新界面显示，继续购买
        //bool purchaseOne = false;
        
        if (purchaseOne || isUnlockedAll())
        {
            // 关闭
            closeStore();
        }
        else
        {
            // 刷新显示
            refresh();
        }
    }
}

void Store::closeStore(bool bInvokeCloseEvent)
{
    if (m_purchased)
    {
        // notification
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(NOTIFI_STORE_IAP_PURCHASED);
    }
    
    if (bInvokeCloseEvent && m_storeClosedCallback)
    {
        m_storeClosedCallback(this);
    }
    
    Common::sound.play("Common:close");
    
    if (m_adsIsVisible && !WJUtils::isAdsVisible())
        Common::showAds();
    
    LBModalDialog::close();
}

void Store::setOnClosed(const StoreClosedCallback &callback)
{
    m_storeClosedCallback = callback;
}

void Store::onEnter()
{
    LBModalDialog::onEnter();
    
    m_adsIsVisible = WJUtils::isAdsVisible();
    if (m_adsIsVisible)
        WJUtils::hideAds();
}

