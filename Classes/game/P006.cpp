//
// P006.cpp
// WeddingSalon
//
// Created by DalechnMac on 15-9-30.
//
//

#include "P006.h"
#include "P006Sub.h"
INIT_SCENE_LOADER_ASYNC(P006);

P006::P006()
{
    
}

P006::~P006()
{
    
}

void P006::asyncLoadSceneResource()
{
    WJLayerJsonPreload::getInstance()->asyncPreload("game/json/p006.json");
    
    Common::sound.preload("xxx");
}

GameNumber P006::getGameNumber()
{
    return GameNumber::P006;
}

bool P006::init()
{
    if ( !PBase::init() )
    {
        return false;
    }

    m_sub = new std::map<std::string, Node*>;
    m_sub->clear();
    
    initSceneJson("game/json/p006.json");
    
    initWithEvent();
    
    return true;
}

void P006::initWithEvent()
{
    initBaby();
}

void P006::initBaby()
{
    WJSkeletonAnimation * babySke = m_sceneJson->getSubSkeleton("baby");
    Sub<P006, WJSkeletonAnimation> *sub = P006Baby::create();
    sub->bind(this, babySke, m_sceneJson);
    sub->retain();
    
    m_sub->insert(std::make_pair("baby", sub));
}

void P006::onExit()
{
    PBase::onExit();
    
    if(m_sub->size())
    {
        std::map<std::string,Node*>::iterator _it  = m_sub->begin();

        while (_it != m_sub->end())
        {
            CC_SAFE_RELEASE( _it->second);
            ++_it;
        }
        m_sub->clear();
    }
    CC_SAFE_DELETE(m_sub);

}

void P006::onEnterTransitionDidFinish()
{
    PBase::onEnterTransitionDidFinish();
}