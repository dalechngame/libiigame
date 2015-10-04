//
//  P006Sub.h
//  WeddingSalon
//
//  Created by DalechnMac on 15-9-30.
//
//

#ifndef __WeddingSalon__P006Sub__
#define __WeddingSalon__P006Sub__

#include "Sub.hpp"
#include "P001Macro.h"
class P006;

class P006Baby :public Sub<P006, WJSkeletonAnimation>
{
public:
    CREATE_FUNC(P006Baby);

	virtual void bind(P006 *fa, WJSkeletonAnimation* sub, WJLayerJson* json);
    
protected:
    
    WJSprite *m_messyHair;                       //杂乱的头发
    
protected:
    virtual bool init() override;
    
    virtual bool subInit();
    void babyAnimationCompleted(int index, int loopCount);
};

#endif /* defined(__WeddingSalon__P006Sub__) */




