#include "Loading.h"
#include "LBToolbarLayer.h"

#define LOADING_TYPE_3STEP_ONE_SCENE    1   // 0 or 1 是否只使用1个场景来实现Loading的3个步骤(推荐)

#define MIN_WAIT_TIME			500
#define FADE_TIME						0.8f
#define FADE_COLOR					Color3B::BLACK

#define TAG_LOADING               36214 //-- question
#define ZORDER_LOADING        99999

Loading::LoadingType Loading::s_loadingType = LoadingType::kFade;
bool Loading::s_isLoading = false;

Loading* Loading::gotoScene( GameNumber gameNumber, void* userData /*= nullptr*/)
{
//    // switch loading type
//    if (gameNumber == GameNumber::P002)
//        s_loadingType = LoadingType::k3Step;
//    else
//        s_loadingType = LoadingType::kFade;
    
    // goto scene
    if (s_loadingType == LoadingType::kNone || s_loadingType == LoadingType::kFade)
    {
        return Loading::gotoPhase(gameNumber, userData, Phase::kLoad);       // kLoad
    }
    else if (s_loadingType == LoadingType::k3Step)
    {
        return Loading::gotoPhase(gameNumber, userData, Phase::kBeforeLoad); // kBeforeLoad
    }
    else
    {
        return nullptr;
    }
}

bool Loading::init( GameNumber gameNumber, void* userData, Phase phase )
{
    if (!WJLayer::init()) {
        return false;
    }
    m_gameNumber = gameNumber;
    m_userData = userData;
    m_phase = phase;
    m_startShowTime = 0;
    m_listenerStart = nullptr;
    m_listenerComplete = nullptr;
    
    setClickAble(true);
    noClickMoveEffect();
    setTouchSwallowsTouches(true);
    setCustomizeTouchRect(Rect(0, 0, winSize.width, winSize.height), false);
    
    m_loadingJson = WJLayerJson::create("game/json/loading.json");
    m_loadingJson->ignoreAnchorPointForPosition(false);
    m_loadingJson->setAnchorPoint(Vec2(0.5f, 0));
    m_loadingJson->setPosition(Vec2(winSize.width / 2, 0));
    if (m_phase == Phase::kBeforeLoad)
        m_loadingJson->setPositionY(winSize.height);
    
    m_loadingJson->playAnimation("aniLoading");
    
    addChild(m_loadingJson);
    
    return true;
}

void Loading::doLoading()
{
    if (m_phase == Phase::kBeforeLoad)
    {
        m_loadingJson->runAction(Sequence::create(
                                                  EaseBackOut::create(MoveTo::create(0.5f, Vec2(m_loadingJson->getPositionX(), 0))),
                                                  CallFunc::create([&]()
                                                                   {
                                                                       // begin load
                                                                       Loading::gotoPhase(m_gameNumber, m_userData, Phase::kLoad);
                                                                   }),
                                                  NULL));
        
    }
    else if (m_phase == Phase::kLoad)
    {
        m_startShowTime = WJUtils::millisecond();
        runAction(Sequence::create(
                                   DelayTime::create(0.1f),	// delay
                                   CallFunc::create([&]()
                                                    {
                                                        // release res
                                                        releaseResources();
                                                        
                                                        // load next scene
                                                        loadNextSceneResources();
                                                        
                                                        // load next scene sound
                                                        loadNextSceneSound();
                                                    }),
                                   NULL));
    }
    else if (m_phase == Phase::kAfterLoad)
    {
        m_loadingJson->runAction(Sequence::create(
                                                  EaseSineOut::create(MoveTo::create(0.5f, Vec2(m_loadingJson->getPositionX(), winSize.height))),
                                                  CallFunc::create(CC_CALLBACK_0(Loading::onLoadScene3StepCompleted, this)),
                                                  NULL));
    }
    
}

void Loading::releaseResources()
{
#if (PC_PLATFORM)
    CCLOG("------------- LOADING: win32/mac don't release unused resources ------------- ");
#else
    CCLOG("------------- LOADING: release unused resources. ------------- ");
    
    // release skeleton data cache
    WJSkeletonDataCache::getInstance()->removeUnusedSkeletonData();
    
    // release snapsnot(快照)
    WJUtils::releaseLastScreenShot();

    // last, release textures
    Director::getInstance()->purgeCachedData();
    
    // release sound
    Common::sound.clearAll();
    
#endif
}

void Loading::loadNextSceneResources()
{
    PLoader *loader = PLoader::getLoader(m_gameNumber);
    CCAssert(loader, "not found loader.");
    
    SEL_AsyncLoadSceneResource asyncLoadResource = loader->getAsyncLoadSceneSelector();
    if (asyncLoadResource)
    {
        m_asyncLoadTaskCount = 0;
        
        m_listenerStart = Director::getInstance()->getEventDispatcher()->addCustomEventListener(NOTIF_ASYNC_PRELOAD_START,
                                                                                                [&](EventCustom* event)
                                                                                                {
                                                                                                    m_asyncLoadTaskCount++;
                                                                                                });
        
        m_listenerComplete = Director::getInstance()->getEventDispatcher()->addCustomEventListener(NOTIF_ASYNC_PRELOAD_COMPLETE,
                                                                                                   [&](EventCustom* event)
                                                                                                   {
                                                                                                       if (--m_asyncLoadTaskCount == 0)
                                                                                                       {
                                                                                                           // all resource load completed
                                                                                                           createAndShowNextScene();
                                                                                                       }
                                                                                                   });
        
        asyncLoadResource();
        if (WJLayerJsonPreload::getInstance()->getTaskCount() <= 0)
        {
            // sync load
            createAndShowNextScene();
        }
        // else
        //	async load, do nothing, wait completed.
    }
    else
    {
        // sync load
        createAndShowNextScene();
    }
}

void Loading::loadNextSceneSound()
{
    // load common sound
    Common::loadCommonEffect();
    
}

void Loading::createAndShowNextScene()
{
    Node *nextSceneNode = createNextSceneNode(m_gameNumber, m_userData);
    nextSceneNode->retain();
    
    long long t = WJUtils::millisecond();
    if (t - m_startShowTime < MIN_WAIT_TIME)
    {
        // wait some time
        runAction(Sequence::createWithTwoActions(
                                                 DelayTime::create((MIN_WAIT_TIME - (t - m_startShowTime)) / 1000.0f),
                                                 CallFunc::create(CC_CALLBACK_0(Loading::showNextScene, this, nextSceneNode))
                                                 ));
    }
    else
    {
        showNextScene(nextSceneNode);
    }
}

Scene* Loading::createNextScene( GameNumber gameNumber, void* userData )
{
    Node* node = createNextSceneNode(gameNumber, userData);
    
    Scene* scene = Scene::create();
    scene->addChild(node);
    
    return scene;
}

Node* Loading::createNextSceneNode( GameNumber gameNumber, void* userData )
{
    PLoader *loader = PLoader::getLoader(gameNumber);
    CCAssert(loader, "not found loader.");
    
    // call create scene func.
    return loader->getCreateSceneSelector()(userData);
}

void Loading::showNextScene(Node *nextSceneNode)
{
    if (s_loadingType == LoadingType::kFade)
    {
        // set as false
        s_isLoading = false;
        LBToolbar::setBackKeyEnabled(true);
        
        Scene* nextScene = Scene::create();
        nextScene->addChild(nextSceneNode);
        Director::getInstance()->replaceScene(TransitionFade::create(FADE_TIME, nextScene, FADE_COLOR));
    }
    else if (s_loadingType == LoadingType::k3Step)
    {
#if (LOADING_TYPE_3STEP_ONE_SCENE)
        Scene *runningScene = Director::getInstance()->getRunningScene();
        runningScene->addChild(nextSceneNode, 0);
        
        Loading::gotoPhase(m_gameNumber, m_userData, Phase::kAfterLoad);
#else
        Loading *loading = Loading::gotoPhase(m_gameNumber, m_userData, Phase::kAfterLoad);
        
        Scene* nextScene = Scene::create();
        nextScene->addChild(nextSceneNode);
        nextScene->addChild(loading);
        
        Director::getInstance()->replaceScene(nextScene);   // replace
#endif
    }
    
    nextSceneNode->release();
}

Loading* Loading::gotoPhase( GameNumber gameNumber, void* userData, Phase phase )
{
    if (s_isLoading && phase == Phase::kBeforeLoad)
        return nullptr;
    
    s_isLoading = true;
    LBToolbar::setBackKeyEnabled(false);
    
    Loading* loading = nullptr;
    
    if (s_loadingType == LoadingType::kNone)
    {
        Director::getInstance()->replaceScene(TransitionFade::create(FADE_TIME,
                                                                     createNextScene(gameNumber, userData),
                                                                     FADE_COLOR));
        s_isLoading = false;
        LBToolbar::setBackKeyEnabled(true);
    }
    else if (s_loadingType == LoadingType::kFade)
    {
        loading = new Loading();
        loading->autorelease();
        loading->init(gameNumber, userData, phase);
        
        Scene *scene = Scene::create();
        scene->addChild(loading);
        Director::getInstance()->replaceScene(TransitionFade::create(FADE_TIME, scene, FADE_COLOR));
    }
    else if (s_loadingType == LoadingType::k3Step)
    {
        if (phase == Phase::kBeforeLoad)
        {
            loading = new Loading();
            loading->autorelease();
            loading->init(gameNumber, userData, phase);
            
            Scene *runningScene = Director::getInstance()->getRunningScene();
            runningScene->addChild(loading, ZORDER_LOADING, TAG_LOADING);
        }
        else if (phase == Phase::kLoad)
        {
#if (LOADING_TYPE_3STEP_ONE_SCENE)
            Scene *runningScene = Director::getInstance()->getRunningScene();
            
            Vector<Node*>& children = runningScene->getChildren();
            Vector<Node*> deleteChild;
            for (auto child : children)
            {
                if (dynamic_cast<Camera*>(child))
                    continue;
                else if (child->getTag() == TAG_LOADING)
                    loading = (Loading*)child;
                else
                    deleteChild.pushBack(child);
            }
            
            for (auto child : deleteChild)
                child->removeFromParent();
            
            loading->m_phase = phase;
            loading->doLoading();       // goto Phase 2 (kLoad)
            
#else
            loading = new Loading();
            loading->autorelease();
            loading->init(gameNumber, userData, phase);
            
            Scene *scene = Scene::create();
            scene->addChild(loading);
            
            Director::getInstance()->replaceScene(scene);   // replace scene Phase 2 (kLoad)
#endif
        }
        else if (phase == Phase::kAfterLoad)
        {
#if (LOADING_TYPE_3STEP_ONE_SCENE)
            Scene *runningScene = Director::getInstance()->getRunningScene();
            loading = static_cast<Loading*>(runningScene->getChildByTag(TAG_LOADING));
            loading->m_phase = phase;
            loading->doLoading();       // goto Phase3 (kAfterLoad)
#else
            loading = new Loading();
            loading->autorelease();
            loading->init(gameNumber, userData, phase); // replace scene Phase3 (kAfterLoad)
#endif
        }
    }
    
    return loading;
}

void Loading::onLoadScene3StepCompleted()
{
    removeFromParent();
    
    s_isLoading = false;
    LBToolbar::setBackKeyEnabled(true);
}

void Loading::onExit()
{
    WJLayer::onExit();
    
    if (m_listenerStart)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listenerStart);
        Director::getInstance()->getEventDispatcher()->removeEventListener(m_listenerComplete);
    }
}

void Loading::onEnterTransitionDidFinish()
{
    WJLayer::onEnterTransitionDidFinish();
    
    doLoading();
}

