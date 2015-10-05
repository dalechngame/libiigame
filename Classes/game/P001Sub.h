//
//  P001Sub.h
//  WeddingSalon
//
//  Created by DalechnMac on 15-9-28.
//
//

#ifndef __WeddingSalon__P001Sub__
#define __WeddingSalon__P001Sub__

#include "Sub.hpp"
#include "P001Macro.h"

class P001;

class P001Comb :public Sub<P001, WJSprite>
{
public:
    CREATE_FUNC(P001Comb);
    static bool s_isShowCrownScroll;
	virtual void bind(P001 *fa, WJSprite* sub, WJLayerJson* json);
    
protected:
    virtual bool init() override;
    virtual void onExit() override;
    
    virtual bool thingOnTouchAble(Node *node, WJTouchEvent *event) ;
    virtual  bool thingOnWillMoveTo(Node *node, WJTouchEvent *event) ;
    virtual void thingOnTouchEnd(Node *node, WJTouchEvent *event) ;

protected:
    Sub<P001, WJSprite> *m_crown;

    CombTaskState m_isFinishCombTask;
    WJSprite *m_touchCrownSprite;


    void setHairState(HairState hairStyle = HairState::freeHair );
    void playPrincessAni(PrincessAni aniName, bool loop = false, int stateIndex = 0);
    void initWithSkeleton();
    
    void showCrownScrollLayer();
    

};

class P001Crown :public Sub<P001, WJSprite>
{
public:
    CREATE_FUNC(P001Crown);
    static int s_selectCrownInt;
    
	virtual void bind(P001 *fa, WJSprite* sub, WJLayerJson* json);
protected:
    
    virtual bool init() override;

    virtual void crownOnClick(Node *node, WJTouchEvent *event);

protected:
    
    WJVScrollLayer *m_crownScrollLayer;
    
    void hideCrownScrollLayer();
};

#endif /* defined(__WeddingSalon__P001Sub__) */
