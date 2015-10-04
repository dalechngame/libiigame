//
// P010.cpp
// WeddingSalon
//
// Created by DalechnMac on 15-9-25.
//
//

#include "P010.h"
INIT_SCENE_LOADER_ASYNC(P010);

void P010::asyncLoadSceneResource()
{
	WJLayerJsonPreload::getInstance()->asyncPreload("game/json/p010_main.json");
}

GameNumber P010::getGameNumber()
{
    return GameNumber::P010;
}

bool P010::init()
{
    if ( !PBase::init() )
    {
        return false;
    }
    
    initSceneJson("game/json/p010_main.json");
    
    initData();
    initWithEvent();
    
    return true;
}

void P010::initSceneJson( const char* jsonFileName )
{
    PBase::initSceneJson(jsonFileName);
    
    // �ж��Ƿ��Ѿ���������
    if (Common::isInAppPurchasedByKey("AllGameAndClothingAndNipple"))
    {
        for (int i = 1; i <= 9; i++)
        {
            std::string lockString = WJUtils::stringAddInt("lock", i, 3);
            if (m_sceneJson->getSubSprite(lockString.c_str()))
            {
                m_sceneJson->getSubSprite(lockString.c_str())->setVisible(false);
            }
        }
    }
    // ������Ϩ�𳡾�Icon
    m_lightSceneCount = UserDefault::getInstance()->getIntegerForKey("lightSceneCount", 1);
    m_getSceneNo = UserDefault::getInstance()->getIntegerForKey("getSceneNo", 1);
    m_isWinEnter = UserDefault::getInstance()->getBoolForKey("isWinEnterMain", false);
    int starNo = m_getSceneNo;
    if (m_isWinEnter)
    {
        starNo--;
    }
    for (int i = starNo + 1; i <= SCENE_COUNT; i++)
    {
        std::string sceneString = WJUtils::stringAddInt("scene", i, 3);
        WJSprite *sprite = m_sceneJson->getSubSprite(sceneString.c_str());
//        darkeningSceneIcon(sprite, i);
    }
    
    // ������Ϩ���ͷ
    for (int i = starNo; i <= ARROW_COUNT; i++)
    {
        std::string arrowString = WJUtils::stringAddInt("arrow", i, 3);
//        darkeningSceneIcon(m_sceneJson->getSubSprite(arrowString.c_str()), i);
    }

}

void P010::initData()
{
    
}

void P010::initWithEvent()
{
    for (int i = 1; i <= SCENE_COUNT; i++)
    {
        std::string sceneString = WJUtils::stringAddInt("scene", i, 3);
        WJSprite *sprite = m_sceneJson->getSubSprite(sceneString.c_str());
        sprite->setTag(i);
        sprite->setOnClick(CC_CALLBACK_2(P010::scenenButtonOnClick, this));
    }
}


void P010::darkeningSceneIcon(WJSprite *sprite, int sceneInt)
{
    std::string lightName = WJUtils::stringAddInt("level", sceneInt, 1);
    std::string darkName = WJUtils::stringAddInt("level", sceneInt, 1);
    darkName.append("_1");
    std::string newPath = WJUtils::replace(sprite->getSpriteFileName(), lightName.c_str(), darkName.c_str());
    sprite->loadSpriteTexture(newPath.c_str());
    sprite->noClickMoveEffect();
    sprite->setUserTag(SceneLightOrDark::dark);
}

void P010::lightSceneIcon(WJSprite *sprite, int sceneInt)
{
    std::string lightName = WJUtils::stringAddInt("level", sceneInt, 1);
    std::string darkName = WJUtils::stringAddInt("level", sceneInt, 1);
    darkName.append("_1");
    std::string newPath = WJUtils::replace(sprite->getSpriteFileName(), darkName.c_str(), lightName.c_str());
    sprite->loadSpriteTexture(newPath.c_str());
    sprite->defaultClickMoveEffect();
    sprite->setUserTag(SceneLightOrDark::light);
}


void P010::showWinSceneIcon()
{
    // ʤ�����룬���˵�����ͷ�ͳ���
    if (m_isWinEnter)
    {
        int arrowInt = m_lightSceneCount;
        arrowInt--;
        WJSprite *arrowSprite = m_sceneJson->getSubSprite(WJUtils::stringAddInt("arrow", arrowInt, 3).c_str());
        if (arrowSprite)
        {
            arrowSprite->runAction(
                                   Sequence::create(
                                                    ScaleTo::create(0.3f, 1.2f, 1.2f),
                                                    CallFunc::create([=](){lightSceneIcon(arrowSprite, arrowInt); Common::sound.play("Common:unlock");}),
                                                    ScaleTo::create(0.3f, 1.0f, 1.0f),
                                                    NULL));
        }
        
        int sceneInt = m_lightSceneCount;
        WJSprite *sceneSprite = m_sceneJson->getSubSprite(WJUtils::stringAddInt("scene", sceneInt, 3).c_str());
        if (sceneSprite)
        {
            sceneSprite->runAction(
                                   Sequence::create(
                                                    DelayTime::create(0.6f),
                                                    ScaleTo::create(0.3f, 1.2f, 1.2f), 
                                                    CallFunc::create([=](){lightSceneIcon(sceneSprite, sceneInt); Common::sound.play("Common:tips02");}), 
                                                    ScaleTo::create(0.3f, 1.0f, 1.0f), 
                                                    DelayTime::create(0.5f),
                                                    CallFunc::create([=](){m_sceneJson->setEnabled(true);}), 
                                                    NULL));
        }
    }
    else
    {
        m_sceneJson->setEnabled(true);
    }
}

void P010::showSceneIconAni()
{
    Common::sound.play("Common:shine");
    // ����ͼ��Ķ���
    for (int i = 1; i <= SCENE_COUNT; i++)
    {
        std::string sceneString = WJUtils::stringAddInt("scene", i, 3);
        WJSprite *sprite = m_sceneJson->getSubSprite(sceneString.c_str());
        sprite->stopAllActions();
        sprite->runAction(Sequence::create(DelayTime::create(0.3f * i), CallFunc::create(CC_CALLBACK_0(P010::sceneIconScaleAni, this, sprite)), NULL));
    }
}

void P010::sceneIconScaleAni(WJSprite *sprite)
{
    sprite->stopAllActions();
    sprite->setScale(1.0f);
    sprite->runAction(Sequence::create(ScaleTo::create(0.2f, 1.1f, 1.1f), ScaleTo::create(0.2f, 1.0f, 1.0f), NULL));
}


void P010::openCurtain()
{
    m_sceneJson->getSubSkeleton("leftSpine")->playAnimation("animation2", false);
    m_sceneJson->getSubSkeleton("rightSpine")->playAnimation("animation2", false);
}

void P010::closeCurtain()
{
    m_sceneJson->getSubSkeleton("leftSpine")->playAnimation("animation", false);
    m_sceneJson->getSubSkeleton("rightSpine")->playAnimation("animation", false);
}

void P010::onExit()
{
    PBase::onExit();
    
    // ��������ĳ�����
    UserDefault::getInstance()->setIntegerForKey("lightSceneCount", m_lightSceneCount);
    UserDefault::getInstance()->setBoolForKey("isWinEnterMain", false);
    UserDefault::getInstance()->flush();
}

void P010::onEnterTransitionDidFinish()
{
    PBase::onEnterTransitionDidFinish();
    
    // ���һ���ؿ�����ѡ��ʱ����
    if (!UserDefault::getInstance()->getBoolForKey("isWinEnterMain", false))
    {
        this->runAction(
                        Sequence::create(
                                         CallFunc::create([=](){openCurtain();}),
                                         DelayTime::create(1.5f),
                                         CallFunc::create([=](){showSceneIconAni();}),
                                         NULL));
    }
    else
    {
        this->runAction(
                        Sequence::create(
                                         CallFunc::create([=](){openCurtain(); m_sceneJson->setEnabled(false);}),
                                         DelayTime::create(1.5f),
                                         CallFunc::create([=](){showWinSceneIcon();}),
                                         NULL));
    }
    
    // ��һ��ͨ�أ���ʾ����Ч��
    if (UserDefault::getInstance()->getBoolForKey("finishAllGame") == true)
    {
        ParticleSystemQuad *finishAllGameParticle = ParticleSystemQuad::create("particles/tongguan.plist");
        finishAllGameParticle->setPosition(Vec2(m_winSize.width / 2, m_winSize.height / 2));
        m_sceneJson->addChild(finishAllGameParticle, 1000);
        finishAllGameParticle->setAutoRemoveOnFinish(true);
        UserDefault::getInstance()->setBoolForKey("finishAllGame", false);
        UserDefault::getInstance()->flush();
    }
}

void P010::onStoreClosedAndPurchased()
{
    PBase::onStoreClosedAndPurchased();
    
    // ����ɹ�֮���Ȼ�ԭȫ������������Ч��
    for (int i = 1; i <= SCENE_COUNT; i++)
    {
        std::string sceneString = WJUtils::stringAddInt("scene", i, 3);
        WJSprite *sprite = m_sceneJson->getSubSprite(sceneString.c_str());
        sprite->stopAllActions();
        sprite->setScale(1.0f);
    }
    
    // ȥ�������ϵ�����ť
    for (int i = 1; i <= 9; i++)
    {
        std::string lockString = WJUtils::stringAddInt("lock", i, 3);
        WJSprite *lockSprite = m_sceneJson->getSubSprite(lockString.c_str());
        if (lockSprite)
        {
            lockSprite->runAction(
                                  Sequence::create(
                                                   DelayTime::create(0.3f * i),
                                                   ScaleTo::create(0.2f, 1.2f, 1.2f),
                                                   ScaleTo::create(0.3f, 0.0f, 0.0f), 
                                                   Hide::create(),
                                                   NULL));
        }
    }
    
}


void P010::scenenButtonOnClick(Node *node, WJTouchEvent *event)
{
    if (!WJUtils::canClick("", 1000))
        return;
    
    WJSprite *sprite = dynamic_cast<WJSprite *>(node);
    
    bool isIap = Common::isInAppPurchasedByKey("AllGameAndClothingAndNipple");
    Common::sound.play("Common:button02");
    
    // �ж��Ƿ񸶷ѣ��������
    if (isIap)
    {
        // ����û�е����ģ���ʾ����ĵ�������
        if (sprite->getUserTag() == SceneLightOrDark::dark)
        {
            sceneIconScaleAni(m_sceneJson->getSubSprite(WJUtils::stringAddInt("scene", m_lightSceneCount, 3).c_str()));
            return;
        }
        else
        {
            // �����ģ����볡��
            m_sceneJson->setEnabled(false);
            Common::sound.stop("Common:shine");
            this->runAction(
                            Sequence::create(
                                             CallFunc::create([=](){closeCurtain();}),
                                             DelayTime::create(1.5f),
                                             CallFunc::create([=](){Loading::gotoScene((GameNumber)node->getTag());}),
                                             NULL));
            return;
        }
    }
    else
    {
        // û�и��ѣ����ǳ�������ѳ����ģ������ǵ�����
        if (sprite->getTag() < 5 && sprite->getUserTag() != SceneLightOrDark::dark)
        {
            // �����ģ����볡��
            m_sceneJson->setEnabled(false);
            Common::sound.stop("Common:shine");
            this->runAction(
                            Sequence::create(
                                             CallFunc::create([=](){closeCurtain();}),
                                             DelayTime::create(1.5f),
                                             CallFunc::create([=](){Loading::gotoScene((GameNumber)node->getTag());}), 
                                             NULL));
            return;
        }// û�и��ѣ����ǳ�������ѳ����ģ������ǰ���
        else if (sprite->getTag() < 5 && sprite->getUserTag() == SceneLightOrDark::dark)
        {
            sceneIconScaleAni(m_sceneJson->getSubSprite(WJUtils::stringAddInt("scene", m_lightSceneCount, 3).c_str()));
            return;
        }// û�и��ѣ��������շѵ�
        else if (sprite->getTag() >= 5)
        {
            Store::showStore();
            return;
        }
    }
}