//
// P000.cpp
// WeddingSalon
//
// Created by DalechnMac on 15-9-22.
//
//

#include "P000.h"
#include "TestGameMenu.h"

INIT_SCENE_LOADER_ASYNC(P000);

void P000::asyncLoadSceneResource()
{
   	WJLayerJsonPreload::getInstance()->asyncPreload("game/json/p000.json");
    WJLayerJsonPreload::getInstance()->asyncPreload("infoDialog/infoDialog.json");
    
    Common::sound.preload("Homepage");
}

GameNumber P000::getGameNumber()
{
    return GameNumber::P000;
}


bool P000::init()
{
    if ( !PBase::init() )
    {
        return false;
    }
    
    initData();
    
	initSceneJson("game/json/p000.json");
    
    initSceneAni();
    
    initToolbar();
    
    return true;
}

void P000::initData()
{
    m_toolbar = NULL;
}

void P000::initSceneJson( const char* jsonFileName )
{
    PBase::initSceneJson(jsonFileName);
    
    // 给公主和baby绑定默认衣服
    WJSkeletonAnimation *princessSpine = m_sceneJson->getSubSkeleton("womanSpine");
    princessSpine->setSlotTexture("dress01", "game/P008/princess/dress01/clothes05.png");
    princessSpine->setSlotTexture("dress02", "game/P008/princess/dress02/clothes02.png");
    princessSpine->setSlotTexture("dress03", "game/P008/princess/dress03/clothes02.png");
    princessSpine->setSlotTexture("dress05", "game/P008/princess/dress05/clothes06.png");
    princessSpine->setSlotTexture("dress06", "game/P008/princess/dress06/clothes02.png");
    
    WJSkeletonAnimation *babySpine = m_sceneJson->getSubSkeleton("babySpine");
    babySpine->setSlotTexture("dress02", "game/P008/baby/dress02/clothes08.png");
    babySpine->setSlotTexture("dress03", "game/P008/baby/dress03/clothes01.png");
    
    WJUtils::addEffect("sound/button.mp3");
    WJUtils::addEffect("sound/close.mp3");
    
}


void P000::initSceneAni()
{
    WJSprite *play = m_sceneJson->getSubSprite("play");
    play->runAction(
            RepeatForever::create(
            Sequence::create(
            ScaleTo::create(1.3f, 0.9f, 0.9f),
            ScaleTo::create(1.3f, 1.1f, 1.1f),
            NULL)));
    
    play->setOnClick([](Node *node, void *WJTouchEvent){
            WJUtils::showChartboostOnPlayButton();
            Loading::gotoScene(GameNumber::P010);
            Common::sound.play("Common:button02");
    });
}

void P000::initToolbar()
{
    m_toolbar = LBToolbar::create(CC_CALLBACK_2(P000::onToolbarClick, this));
    
    // forparents button
    m_toolbar->addButton("button/forParents.png", m_origin.x + 20, m_visibleRect.getMaxY() - 20, MENU_TAG_FORPARENTS)->setAnchorPoint(Vec2(0, 1));
    
    // info button
    m_toolbar->addButton("button/uiButton014.png", m_origin.x + 20, m_origin.y + 20, MENU_TAG_INFO)->setAnchorPoint(Vec2(0, 0));
    
    // store button
    if (!Store::isUnlockedAll() )
    {
        m_toolbar->addButton("button/uiButton013.png",m_origin.x + 95, 20 + m_origin.y, MENU_TAG_STORE)->setAnchorPoint(Vec2(0, 0));
    }
    
    //   music button
    if (WJUtils::isSmallScreen())
        m_toolbar->addButton("base/none.png", m_visibleRect.getMaxX() - 160, 20 + m_origin.y, MENU_TAG_MUSIC)->setAnchorPoint(Vec2(1, 0));
    else
        m_toolbar->addButton("base/none.png", m_visibleRect.getMaxX() - 115, 25 + m_origin.y, MENU_TAG_MUSIC)->setAnchorPoint(Vec2(1, 0));
    m_toolbar->setMusicButtonFile("button/uiButton015.png", "button/uiButton016.png");
    
    this->addChild(m_toolbar, 10);
}

void P000::onToolbarClick(Node* node, WJTouchEvent* evnet)
{
    int tag = node->getTag();
    switch (tag)
    {
        case MENU_TAG_FORPARENTS:
            Common::sound.play("Common:button01");
            
#if (DEBUG_SHOW_TEST_MENU)
            TestGameMenu::show();
#else
            WJUtils::showForParentDialog(THIS_APP_ID, URL_FOR_PARENTS);
#endif
            break;
            
        case MENU_TAG_INFO:
            showInfoDialog();
            break;
            
        case MENU_TAG_STORE:
            Store::showStore();
            break;
    }
}

void P000::showInfoDialog()
{
    Common::sound.play("Common:windowIn");
    
    WJLayerJson *info = WJLayerJson::create("infoDialog/infoDialog.json");
    info->ignoreAnchorPointForPosition(false);
    info->setPosition(SCREEN_CENTER);
    info->setAnchorPoint(Vec2(0.5f, 0.5f));
    
    auto onClick = [=](Node* node, WJTouchEvent* event)
    {
        const char* key = info->getSubKeyByNode(node);
        if (WJUtils::equals(key, "close"))
        {
            Common::sound.play("Common:windowOut");
            static_cast<LBModalDialog*>(info->getParent())->close();
        }
        else if (WJUtils::equals(key, "likeUs"))
        {
            Common::sound.play("Common:button");
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
    this->addChild(dialog, 1000);
    
    dialog->show(LBModalDialogAnimationType::Scale);
}

void P000::onExit()
{
    PBase::onExit();
    
    WJUtils::hideMoreGameButton();
}

void P000::onEnterTransitionDidFinish()
{
    PBase::onEnterTransitionDidFinish();
    
    WJUtils::showMoreGameButton(-1, -1, 74, 74, THIS_APP_ID, URL_MOREGAME_DEF, wjalNone, MOREGAME_TEXT_COLOR_WHITE);
}

void P000::onStoreClosedAndPurchased()
{
    PBase::onStoreClosedAndPurchased();
    
    Node* node = m_toolbar->getButtonByTag(MENU_TAG_STORE);
    if (node)
    {
        node->setVisible(!Store::isUnlockedAll());
    }
}