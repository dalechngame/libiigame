#include "PBase.h"
#include "Common.h"
#include "TestGameMenu.h"

PBase::PBase() : WJLayer(), 
	m_userData(nullptr),
	m_sceneJson(nullptr),
	m_popupMenu(nullptr),
	m_snapShot(nullptr),
	m_adsLayer(nullptr),
	m_storeEventListener(nullptr),
	m_getfreeEventListener(nullptr)
{

}

PBase::~PBase()
{

}

bool PBase::init()
{
	if ( !WJLayer::init() )
	{
		return false;
	}

#if (COCOS2D_DEBUG)
	CCLOG("Init Scene: %s...", getGameName().c_str());
#endif

	m_winSize = Director::getInstance()->getWinSize();
	m_visibleSize = Director::getInstance()->getVisibleSize();
	m_origin = Director::getInstance()->getVisibleOrigin();
    m_visibleRect = Rect(m_origin.x, m_origin.y, m_visibleSize.width, m_visibleSize.height);

	// top layer
	m_topLayer = WJLayer::create();
	m_topLayer->saveCurrentPosition();
	this->addChild(m_topLayer, ZORDER_TOP_LAYER);

	// p001 welcome
	if (getGameNumber() == GameNumber::P000 || getGameNumber() == GameNumber::P010)
	{
		// android back key
		this->addChild(LBToolbar::createBackKey([&]()
		{
			// quit app
			WJUtils::callaction_void(ACTION_VOID_CONFIRM_QUIT);
		}));
	}
	else
	{
		initPopupMenu();
		initSnapshot();
		initAdsBanner();
	}
	
	return true;
}

std::string PBase::getGameName()
{
	return Common::getGameName(getGameNumber());
}

void PBase::initSceneJson( const char* jsonFileName )
{
	if (m_sceneJson)
		return;

	m_sceneJson = WJLayerJson::create(jsonFileName);
	m_sceneJson->ignoreAnchorPointForPosition(false);
	m_sceneJson->setAnchorPoint(Vec2(0.5f, 0.5f));
	m_sceneJson->setPosition(SCREEN_CENTER);
    
    // 隐藏安全线
    if (m_sceneJson->getSubNodeByKey("layer"))
    {
        m_sceneJson->getSubNodeByKey("layer")->setVisible(false);
    }

	this->addChild(m_sceneJson, ZORDER_SCENE_JSON);
}

void PBase::initPopupMenu()
{
	if (m_popupMenu)
		return;

	m_popupMenu = LBPopupMenu::create(CC_CALLBACK_2(PBase::onPopupMenuClick, this));
	m_popupMenu->setAutoCloseMenu(true);	// auto close

	// menu main button
	m_popupMenu->setMainButton("button/menu.png", m_origin.x + 60, m_visibleRect.getMaxY() - 60, MENU_TAG_POPUP)
               ->setClickAniType(WJButton::ClickAniType::QBreathing)->noClickMoveEffect();

	if (!Store::isUnlockedAll())
	{
		// store button
		m_popupMenu->addHorizontalButton("button/store_popup.png", MENU_TAG_STORE)->setClickAniType(WJButton::ClickAniType::QBreathing)->noClickMoveEffect();
	}

	// home button
	m_popupMenu->addHorizontalButton("button/home.png", MENU_TAG_GOHOME)->setClickAniType(WJButton::ClickAniType::QBreathing)->noClickMoveEffect();

	if (getGameNumber() != GameNumber::P002)
	{
		// back button
		m_popupMenu->addHorizontalButton("button/back.png", MENU_TAG_BACK)->setClickAniType(WJButton::ClickAniType::QBreathing)->noClickMoveEffect();
	}

	// music button
	m_popupMenu->addVerticalButton("button/music_on.png", MENU_TAG_MUSIC)->setClickAniType(WJButton::ClickAniType::QBreathing)->noClickMoveEffect();
	// camera button
	m_popupMenu->addVerticalButton("button/camera.png", MENU_TAG_CAMERA)->setClickAniType(WJButton::ClickAniType::QBreathing)->noClickMoveEffect();
	// rate button
	m_popupMenu->addVerticalButton("button/rate.png", MENU_TAG_RATE)->setClickAniType(WJButton::ClickAniType::QBreathing)->noClickMoveEffect();
	// moregame button(fixed)
	m_popupMenu->addFixedVerticalButton("button/moregame.png", MENU_TAG_MOREGAME)->setClickAniType(WJButton::ClickAniType::QBreathing)->noClickMoveEffect();

	// set music button textures
	m_popupMenu->setMusicButtonFile("button/music_on.png", "button/music_off.png");
	

	m_popupMenu->saveCurrentPosition();
	m_topLayer->addChild(m_popupMenu, ZORDER_POPUPMENU);
}

void PBase::initSnapshot()
{
	if (m_snapShot)
		return;

	m_snapShot = LBSnapshotLayer::create(CC_CALLBACK_2(PBase::onSnapshotClick, this));

	m_snapShot->addButton("button/snapshot/close.png", MENU_TAG_CLOSE);
	m_snapShot->addButton("button/snapshot/facebook.png", MENU_TAG_FACEBOOK, 0.8f * TO_SCALE_HEIGHT, 0, 0, "_", "selected");
	m_snapShot->addButton("button/snapshot/email.png", MENU_TAG_EMAIL, 0.7f * TO_SCALE_HEIGHT, 0, 0, "_", "selected");
	m_snapShot->addButton("button/snapshot/photos.png", MENU_TAG_PHOTOS, 0.7f * TO_SCALE_HEIGHT, 0, 0, "_", "selected");
    
	this->addChild(m_snapShot, ZORDER_SNAPSHOT);
}

void PBase::initAdsBanner()
{
	if (m_adsLayer || Common::isAdsRemoved())
		return;

	Size adsSize = Common::getAdsSize();
	Vec2 adsLayerPosHide = Vec2(0, m_visibleRect.getMaxY() + adsSize.height + 5);

	m_adsLayer = LayerColor::create(Color4B(110, 110, 110, 125));
	m_adsLayer->setContentSize(Size(m_winSize.width, adsSize.height));
	m_adsLayer->ignoreAnchorPointForPosition(false);
	m_adsLayer->setAnchorPoint(Vec2(0, 1.0f));
	m_adsLayer->setPosition(adsLayerPosHide);
	m_adsLayerVisible = false;

	this->addChild(m_adsLayer, ZORDER_ADS_LAYER);

	refreshAdBanner(0);
	this->runAction(RepeatForever::create(
										Sequence::createWithTwoActions(
												DelayTime::create(0.2f),
												CallFunc::create(CC_CALLBACK_0(PBase::refreshAdBanner, this, 0.2f)))));
}

void PBase::refreshAdBanner(float duration)
{
	if (!m_adsLayer)
		return;

	if (WJUtils::isAdsReallyVisible())
	{
		if (!m_adsLayerVisible)
		{
			m_adsLayerVisible = true;
            
            Vec2 adsLayerPos = Vec2(0, m_visibleRect.getMaxY());
            
			m_adsLayer->stopAllActions();
			m_adsLayer->runAction(MoveTo::create(duration, adsLayerPos));

			// move down top layer
			Vec2 pos = m_topLayer->getSavedPosition();
			Vec2 mp = Vec2(0, m_adsLayer->getContentSize().height + 10);
			m_topLayer->stopAllActions();
			m_topLayer->runAction(MoveTo::create(duration, pos - mp));
		}
	}
	else if (m_adsLayerVisible)
	{
		m_adsLayerVisible = false;
        
        Size adsSize = Common::getAdsSize();
        Vec2 adsLayerPosHide = Vec2(0, m_visibleRect.getMaxY() + adsSize.height + 5);
        
		m_adsLayer->stopAllActions();
		m_adsLayer->runAction(MoveTo::create(duration, adsLayerPosHide));

		// move up top layer
		m_topLayer->stopAllActions();
		m_topLayer->restoreSavedPosition(duration);
	}
}

void PBase::onPopupMenuClick( Node* node, WJTouchEvent* event )
{
	int tag = node->getTag();

	switch (tag)
	{
		case MENU_TAG_POPUP:
			Common::sound.play("Common:button");
			break;

        case MENU_TAG_GOHOME:
            Loading::gotoScene(GameNumber::P000);
            Common::sound.play("Common:button");
            break;
            
        case MENU_TAG_BACK:
            Loading::gotoScene(GameNumber::P010);
            Common::sound.play("Common:button");
            break;

		case MENU_TAG_MOREGAME:
			Common::sound.play("Common:popup");
#if (DEBUG_SHOW_TEST_MENU)
            TestGameMenu::show();
#else
            WJUtils::showMoreGameDialog(THIS_APP_ID, URL_MOREGAME_DEF);
#endif

			break;

		case MENU_TAG_RATE:
			showInfoDialog();
			break;

		case MENU_TAG_STORE:
			Store::showStore();
			break;

		case MENU_TAG_CAMERA:
			if (WJUtils::canClick("camera", 2000))
			{
                showSnapshot();
			}
			break;
	}
}

void PBase::showInfoDialog()
{
    Common::sound.play("Common:popup");
    
    WJLayerJson *info = WJLayerJson::create("infoDialog/infoDialog.json");
    info->ignoreAnchorPointForPosition(false);
    info->setPosition(SCREEN_CENTER);
    info->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    auto onClick = [=](Node* node, WJTouchEvent* event)
    {
        const char* key = info->getSubKeyByNode(node);
        if (WJUtils::equals(key, "close"))
        {
            Common::sound.play("Common:close");
            static_cast<LBModalDialog*>(info->getParent())->close();
        }
        else if (WJUtils::equals(key, "likeUs"))
        {
            Common::sound.play("Common:button");
            if (APP_LANG_IS_CN)
                WJUtils::openURL(URL_WECHAT);
            else
                WJUtils::openURL(URL_FACEBOOK);
        }
        else if (WJUtils::equals(key, "contactUs"))
        {
            Common::sound.play("Common:button");
            
            std::string strTitle = EMAIL_FEEDBACK;
            std::string verName = WJUtils::callaction_retstr(ACTION_RETSTR_GET_THISAPP_VERSION_NAME);
            WJUtils::callaction_void(ACTION_VOID_SENDMAIL, strTitle.append(verName).c_str());
        }
        else if (WJUtils::equals(key, "rateUs"))
        {
            Common::sound.play("Common:button");
            WJUtils::promptForRating(NULL, RATE_MESSAGE, RATE_URL, RATE_NEW_VERSION_RATE_AGAIN);
        }
    };
    info->setSubNodeOnClick("close", onClick)->nodeInstance()->setTag(MENU_TAG_BACK);  // for android back button
    info->setSubNodeOnClick("likeUs", onClick);
    info->setSubNodeOnClick("contactUs", onClick);
    info->setSubNodeOnClick("rateUs", onClick);
    
    LBModalDialog *dialog = LBModalDialog::create(info, true);
    Director::getInstance()->getRunningScene()->addChild(dialog);
    
    dialog->show(LBModalDialogAnimationType::Scale);
}

void PBase::showSnapshot(const char* fileName /*= NULL*/)
{
    Sprite* spriteFromFile = nullptr;
    Sprite*	spriteLogo = nullptr;
    
    onSnapshotBefore();
    Common::sound.play("Common:camera");
    
    Rect rect(0, 0, 0, 0);
    
    if (fileName)
    {
        spriteFromFile = Sprite::create(fileName);
        
        float scale = m_visibleSize.width / spriteFromFile->getContentSize().width;
        spriteFromFile->setScale(scale);
        spriteFromFile->setAnchorPoint(Vec2::ZERO);
        spriteFromFile->setPosition(m_origin);
        
        this->addChild(spriteFromFile, ZORDER_SNAPSHOT);
        rect = spriteFromFile->getBoundingBox();
    }
    
    // app logo
    spriteLogo = Sprite::create("appIcon.png");
    spriteLogo->setScale(TO_SCALE_HEIGHT);
    spriteLogo->setAnchorPoint(Vec2(1, 0));
    spriteLogo->setPosition(Vec2(m_visibleRect.getMaxX() - 20, m_origin.y + 20));
    this->addChild(spriteLogo, ZORDER_SNAPSHOT);
    
    m_snapShot->snapShow(this, rect, fileName == nullptr);
    
    spriteLogo->removeFromParent();
    
    if (spriteFromFile)
    {
        Texture2D *texture = spriteFromFile->getTexture();
        spriteFromFile->removeFromParent();
        Director::getInstance()->getTextureCache()->removeTexture(texture);
    }
    
    onSnapshotAfter();
}

void PBase::onSnapshotClick( Node* node, WJTouchEvent* event )
{
	int tag = node->getTag();
	switch (tag)
	{
		case MENU_TAG_FACEBOOK:
			Common::sound.play("Common:button");
			WJUtils::sharePhoto(WJUtils::saveLastScreenShot(true).c_str(), FACEBOOK_SHARE, FACEBOOK_APPID);
			break;

		case MENU_TAG_EMAIL:
			{
				Common::sound.play("Common:button");
				std::string str(EMAIL_SHARE);
				str.append(WJUtils::saveLastScreenShot(true));
				WJUtils::callaction_void(ACTION_VOID_SENDMAIL, str.c_str());
			}
			break;

		case MENU_TAG_PHOTOS:
			if (WJUtils::canClick("photos", 2000))
			{
				Common::sound.play("Common:button");
				WJUtils::saveLastScreenShotToSystemAlbum(SAVETO_ALBUM_FOLDER, true);
			}
			break;

		case MENU_TAG_CLOSE:
			Common::sound.play("Common:close");
			onSnapshotClosed();
			break;
	}
}

void PBase::onSnapshotBefore()
{
	if (m_popupMenu)
		m_popupMenu->setVisible(false);

	if (m_adsLayer)
		m_adsLayer->setVisible(false);

	// hide ads banner
	WJUtils::hideAds();

	// move up top layer
	refreshAdBanner(0);
}

void PBase::onSnapshotAfter()
{

}

void PBase::onSnapshotClosed()
{
	if (m_popupMenu)
		m_popupMenu->setVisible(true);

	if (m_adsLayer)
		m_adsLayer->setVisible(true);

	// 恢复Banner广告显示
	showGameAds();

	// 弹Chartboost，拍照关闭为每次都弹，且弹Default。其它游戏地方请弹默认的 LevelComplete
	Common::showChartBoost(WJChartboostLocation::Default, true);
}

void PBase::onEnter()
{
	WJLayer::onEnter();

	// store notification
	m_storeEventListener = _eventDispatcher->addCustomEventListener(NOTIFI_STORE_IAP_PURCHASED, 
							[&](EventCustom* ec)
							{
								onStoreClosedAndPurchased();
							});

	// getfree notification
	m_getfreeEventListener = _eventDispatcher->addCustomEventListener(NOTIFI_GETFREE_REWARD_VIDEO_CLOSED, 
							[&](EventCustom* ec)
							{
								onGetFreeVideoClosed(WJUtils::getLastRewardVideoLockKey(), 
													 WJUtils::isGetFreeUnlocked(WJUtils::getLastRewardVideoLockKey()));
                                
                                if (WJUtils::isGetFreeUnlocked(WJUtils::getLastRewardVideoLockKey()))
                                {
                                    WJUtils::delayExecute(0.2f, [this](float delay)
                                    {
                                        onGetFreeVideoUnlocked(WJUtils::getLastRewardVideoLockKey());
                                    });
                                }
							});
}

void PBase::onEnterTransitionDidFinish()
{
	WJLayer::onEnterTransitionDidFinish();

	showGameAds();

	playGameBgMusic();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	// nothing
#else
	this->runAction(Sequence::createWithTwoActions(
		DelayTime::create(0.1f),
		CallFunc::create([]()
	{
		LOGD("------------- PBase: release unused resource.------------- ");
		WJSkeletonDataCache::getInstance()->removeUnusedSkeletonData();
		Director::getInstance()->purgeCachedData(); // getTextureCache()->removeUnusedTextures();
	})));
#endif
}

void PBase::onExit()
{
	_eventDispatcher->removeEventListener(m_storeEventListener);
	_eventDispatcher->removeEventListener(m_getfreeEventListener);

	WJLayer::onExit();

	WJUtils::hideAds();
}

void PBase::showGameAds()
{
	if (getGameNumber() != GameNumber::P000)
	{
		Common::showAds();
	}
}

void PBase::onStoreClosedAndPurchased()
{
	if (m_popupMenu && Store::isUnlockedAll())
	{
		m_popupMenu->removeItem(MENU_TAG_STORE);
	}
}

void PBase::onGetFreeVideoClosed(const char* getFreeLockKey, bool isUnlocked)
{
	// override me.
}

void PBase::onGetFreeVideoUnlocked(const char* getFreeLockKey)
{
    // override me.
}

void PBase::playGameBgMusic()
{
    switch (getGameNumber())
    {
        case GameNumber::P000:
            Common::sound.playBackgroundMusic("BG:bg001");
            break;
        case GameNumber::P001:
            Common::sound.playBackgroundMusic("BG:bg002");
            break;
        case GameNumber::P002:
            Common::sound.playBackgroundMusic("BG:bg003");
            break;
        case GameNumber::P003:
            Common::sound.playBackgroundMusic("BG:bg002");
            break;
        case GameNumber::P004:
            Common::sound.playBackgroundMusic("BG:bg003");
            break;
        case GameNumber::P005:
            Common::sound.playBackgroundMusic("BG:bg003");
            break;
        case GameNumber::P006:
            Common::sound.playBackgroundMusic("BG:bg002");
            break;
        case GameNumber::P007:
            Common::sound.playBackgroundMusic("BG:bg002");
            break;
        case GameNumber::P008:
            Common::sound.playBackgroundMusic("BG:bg002");
            break;
        case GameNumber::P009:
            Common::sound.playBackgroundMusic("BG:bg004");
            break;
        case GameNumber::P010:
            Common::sound.playBackgroundMusic("BG:bg001");
            break;
        default:
            break;
    }
}

void PBase::showStarAni(WJSprite *starSprite)
{
    if (WJUtils::equals(starSprite->getUserString(), "get"))
    {
        starSprite->setVisible(true);
    }
    else
    {
        Common::sound.play("Common:star");
        
        // 添加星星出现的粒子效果
        ParticleSystemQuad *starParticle = ParticleSystemQuad::create("particles/star.plist");
        starParticle->setPosition(Vec2(starSprite->getContentSize().width / 2, starSprite->getContentSize().height / 2));
        starSprite->addChild(starParticle);
        starParticle->setAutoRemoveOnFinish(true);
        
        starSprite->setUserString("get");
        starSprite->runAction(
                              Sequence::create(
                                               ScaleTo::create(0.0f, 0.0f, 0.0f),
                                               Show::create(),
                                               Spawn::create(
                                                             ScaleTo::create(0.3f, 1.0f, 1.0f), 
                                                             RotateBy::create(0.3f, 360.0f, 360.0f),
                                                             NULL),
                                               NULL));
    }
}
