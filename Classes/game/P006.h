//
// P006.h
// WeddingSalon
//
// Created by DalechnMac on 15-9-30.
//
//

#ifndef __WeddingSalon__P006__
#define __WeddingSalon__P006__

#include "PBase.h"
#include "P006Macro.h"

class P006 : public PBase
{

public:
    std::map<std::string, Node *> *m_sub;
    
protected:
    // method
    void initWithEvent();
    void initBaby();
    
protected:
    // attr
    
public:
    P006();
    ~P006();
    CREATE_SCENE_FUNC(P006);
    
    static void asyncLoadSceneResource();
    
protected:
    virtual GameNumber getGameNumber() override;
    
    virtual bool init() override;
    
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
};

#endif /* defined(__WeddingSalon__P006__) */