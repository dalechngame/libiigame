//
//  SpriteAnimation.cpp
//  WeddingSalon
//
//  Created by DalechnMac on 15-9-23.
//
//

#include "SpriteAnimation.h"


void SpriteAnimation::playAnimation(WJSprite* sprite,LBAniTypeTip type,bool repeat,float waitSecond/*=0.0f*/)
{
    FiniteTimeAction* action;
    stopAnimation(sprite);
    switch (type)
    {
        case LBAniTypeTip::Tip1:
            
            action = Repeat::create(
                                    Sequence::create(
                                                     ScaleTo::create(0.15f,sprite->getSavedScale()*1.1f),
                                                     ScaleTo::create(0.15f,sprite->getSavedScale()*1.0f),
                                                     NULL
                                                     ),3);
            if(repeat)
            {
                action = RepeatForever::create(
                                               Sequence::createWithTwoActions(action,DelayTime::create(3.0f))
                                               );
            }
            
            action->setTag(LB_ANI_TYPE_TIP1_TAG);
            break;
        case LBAniTypeTip::Tip2:
           
            sprite->setOpacity(255*0.3f);
            action = Sequence::createWithTwoActions(
                                                    Repeat::create(
                                                                   Sequence::create(
                                                                                    FadeTo::create(0.5f,255*0.8f),
                                                                                    FadeTo::create(0.5f,255*0.3f),
                                                                                    NULL
                                                                                    ),3),
                                                    FadeTo::create(0.3f,0)
                                                    );
            if(repeat)
            {
                action = RepeatForever::create(
                                               Sequence::create(
                                                                action,
                                                                DelayTime::create(3.0f),
                                                                FadeTo::create(0.0f,255*0.3f),
                                                                NULL
                                                                ));
            }
            
            action->setTag(LB_ANI_TYPE_TIP2_TAG);
            break;
        case LBAniTypeTip::Tip3:
            
            action = Sequence::create(
                                      DelayTime::create(0.5f),
                                      CallFunc::create([=](){sprite->loadSpriteTextureAddSuffix("_","blink");}),
                                      DelayTime::create(0.5f),
                                      CallFunc::create([=](){sprite->loadSpriteTextureRemoveSuffix("_");}),
                                      NULL
                                      );
            action = Repeat::create(action,3);
            
            if(repeat)
            {
                action = RepeatForever::create(
                                               Sequence::create(
                                                                action,
                                                                DelayTime::create(3.0f),
                                                                NULL
                                                                ));
            }
            
            action->setTag(LB_ANI_TYPE_TIP3_TAG);
            break;
        case LBAniTypeTip::Tip4:
            action = RepeatForever::create(Sequence::create(
                                                            FadeTo::create(0, 255 * 0.0f),
                                                            FadeTo::create(1.5f, 255 * 0.8f),
                                                            FadeTo::create(1.5f, 255 * 0.0f),
                                                            NULL));
            
            action->setTag(LB_ANI_TYPE_TIP4_TAG);
            break;
        case LBAniTypeTip::Tip5:
            action = Sequence::create(
                                      EaseOut::create(ScaleTo::create(0.1f,1.3f*sprite->getSavedScale()),1),
                                      EaseOut::create(ScaleTo::create(0.1f,sprite->getSavedScale()),1),
                                      NULL
                                      );
            
            action->setTag(LB_ANI_TYPE_TIP5_TAG);
            break;
        case LBAniTypeTip::Tip6:
            sprite->restoreSavedScale(0);
            action = Spawn::create(
                                   EaseOut::create(ScaleTo::create(0.15f,1.5f*sprite->getSavedScale()),1),
                                   EaseOut::create(FadeOut::create(0.15f),1),
                                   NULL
                                   );
            
            action->setTag(LB_ANI_TYPE_TIP6_TAG);
            break;
        default:
            break;
    }
    
    
    if(waitSecond!=0)
    {
        action->retain();
        auto delayAction = Sequence::create(
                    DelayTime::create(waitSecond),
                    CallFunc::create([sprite,action](){
                    sprite->runAction(action);
                    action->release();
                    }),
                    nullptr
                    );
        delayAction->setTag(LB_ANI_TYPE_TIP_DELAY_TAG);
        sprite->runAction(delayAction);
    }
    else
    {
        sprite->runAction(action);
    }
    
    
}

void SpriteAnimation::stopAnimation(WJSprite* sprite,LBAniTypeTip type /* = ALL */)
{
    if(sprite->getActionByTag(LB_ANI_TYPE_TIP_DELAY_TAG))
    {
        sprite->stopActionByTag(LB_ANI_TYPE_TIP_DELAY_TAG);
    }
    switch (type)
    {
        case LBAniTypeTip::ALL:
            
            if(sprite->getActionByTag(LB_ANI_TYPE_TIP1_TAG))
            {
                sprite->stopActionByTag(LB_ANI_TYPE_TIP1_TAG);
                sprite->setScale(sprite->getSavedScale());
            }
            
            if(sprite->getActionByTag(LB_ANI_TYPE_TIP2_TAG))
            {
                sprite->stopActionByTag(LB_ANI_TYPE_TIP2_TAG);
                sprite->setOpacity(0.0f);
            }
            if(sprite->getActionByTag(LB_ANI_TYPE_TIP3_TAG))
            {
                sprite->stopActionByTag(LB_ANI_TYPE_TIP3_TAG);
                sprite->loadSpriteTextureRemoveSuffix("_");
            }
            if(sprite->getActionByTag(LB_ANI_TYPE_TIP4_TAG))
            {
                sprite->stopActionByTag(LB_ANI_TYPE_TIP4_TAG);
                sprite->setOpacity(255.0f);
            }
            if(sprite->getActionByTag(LB_ANI_TYPE_TIP5_TAG))
            {
                sprite->stopActionByTag(LB_ANI_TYPE_TIP5_TAG);
                sprite->setScale(sprite->getSavedScale());
            }
            if(sprite->getActionByTag(LB_ANI_TYPE_TIP6_TAG))
            {
                sprite->stopActionByTag(LB_ANI_TYPE_TIP6_TAG);
                sprite->setScale(sprite->getSavedScale());
                sprite->setOpacity(0.0f);
            }
            break;
        case LBAniTypeTip::Tip1:
            sprite->stopActionByTag(LB_ANI_TYPE_TIP1_TAG);
            sprite->setScale(sprite->getSavedScale());
            break;
        case LBAniTypeTip::Tip2:
            sprite->stopActionByTag(LB_ANI_TYPE_TIP2_TAG);
            sprite->setOpacity(0.0f);
            break;
        case LBAniTypeTip::Tip3:
            sprite->stopActionByTag(LB_ANI_TYPE_TIP3_TAG);
            sprite->loadSpriteTextureRemoveSuffix("_");
            break;
        case LBAniTypeTip::Tip4:
            sprite->stopActionByTag(LB_ANI_TYPE_TIP4_TAG);
            sprite->setOpacity(255.0f);
            break;
        case LBAniTypeTip::Tip5:
            sprite->stopActionByTag(LB_ANI_TYPE_TIP5_TAG);
            sprite->setScale(sprite->getSavedScale());
            break;
        case LBAniTypeTip::Tip6:
            sprite->stopActionByTag(LB_ANI_TYPE_TIP6_TAG);
            sprite->setScale(sprite->getSavedScale());
            sprite->setOpacity(0.0f);
            break;
        default:
            break;
    }
}

float SpriteAnimation::show(WJSprite* sprite,LBAniTypeShow type,float waitSecond)
{
    FiniteTimeAction* action;
    if(sprite->getActionByTag(LB_ANI_TYPE_SHOW_TAG))
    {
        sprite->stopActionByTag(LB_ANI_TYPE_SHOW_TAG);
    }
    switch (type)
    {
        case LBAniTypeShow::Show1:
            action = Sequence::create(
                                      ScaleTo::create(0,0),
                                      DelayTime::create(waitSecond),
                                      Show::create(),
                                      EaseOut::create(ScaleTo::create(0.15f,1.1f*sprite->getSavedScale()),1),
                                      EaseOut::create(ScaleTo::create(0.15f,sprite->getSavedScale()),1),
                                      NULL
                                      );
            break;
        case LBAniTypeShow::Show2:
            action = Sequence::create(
                                      FadeOut::create(0),
                                      DelayTime::create(waitSecond),
                                      Show::create(),
                                      FadeIn::create(0.3f),
                                      NULL
                                      );
            break;
        case LBAniTypeShow::Show3:
            action = Sequence::create(
                                      ScaleTo::create(0, 1.5f*sprite->getSavedScale()),
                                      FadeOut::create(0),
                                      DelayTime::create(waitSecond),
                                      Show::create(),
                                      Spawn::createWithTwoActions(
                                                                  EaseIn::create(ScaleTo::create(0.5f, sprite->getSavedScale()*1.0f),1),
                                                                  FadeIn::create(0.5f)
                                                                  ),
                                      NULL
                                      );
            break;
        case LBAniTypeShow::Show4:
            action = Sequence::create(
                                      FadeOut::create(0),
                                      DelayTime::create(waitSecond),
                                      Show::create(),
                                      FadeTo::create(0.5f,0.8f*255),
                                      FadeTo::create(0.5f,0.3f*255),
                                      FadeTo::create(0.5f,0.8f*255),
                                      FadeTo::create(0.5f,0.3f*255),
                                      FadeTo::create(0.5f,255),
                                      nullptr
                                      );
            break;
        default:
            break;
    }
    action->setTag(LB_ANI_TYPE_SHOW_TAG);
    sprite->runAction(action);
    return action->getDuration();
}

float SpriteAnimation::hide(WJSprite* sprite,LBAniTypeHide type,Vec2 toPoint /*= Vec2(-9999,-9999)*/,bool cleanUp /*=true*/)
{
    if(sprite->getActionByTag(LB_ANI_TYPE_HIDE_TAG))
    {
        sprite->stopActionByTag(LB_ANI_TYPE_HIDE_TAG);
    }
    FiniteTimeAction* action;
    switch (type)
    {
        case LBAniTypeHide::Hide1:
           
            if (toPoint.equals(Vec2(-9999,-9999)))
            {
                action = ScaleTo::create(0.5f,0);
            } else
            {
                action = Spawn::create(
                                       ScaleTo::create(0.5f,0),
                                       MoveTo::create(0.5f,toPoint),
                                       NULL
                                       );
            }
            break;
        case LBAniTypeHide::Hide2:
           
            action = FadeOut::create(0.5f);
            break;
        case LBAniTypeHide::Hide3:
           
        {
            auto scale = EaseOut::create(ScaleTo::create(0.15f,sprite->getSavedScale()*1.5f),1);
            auto fadeOut = FadeOut::create(0.5f);
            action = Spawn::createWithTwoActions(scale,fadeOut);
        }
            break;
        default:
            break;
    }
    
    if (cleanUp)
    {
        action = Sequence::create(
                                  action,
                                  Hide::create(),
                                  RemoveSelf::create(true),
                                  NULL
                                  );
    } else 
    {
        action = Sequence::create(
                                  action,
                                  Hide::create(),
                                  NULL
                                  );
    }
    action->setTag(LB_ANI_TYPE_HIDE_TAG);
    sprite->runAction(action);
    return action->getDuration();
}

float SpriteAnimation::moveTo(Node* node,LBAniTypeMove type,Vec2 toPoint,float waitSecond,float moveTime/* = 0.0f*/)
{
    if(node->getActionByTag(LB_ANI_TYPE_MOVE_TAG))
    {
        node->stopActionByTag(LB_ANI_TYPE_MOVE_TAG);
    }
    FiniteTimeAction* action;
    float saveScaleX = 1.0f;
    float saveScaleY = 1.0f;
    switch (type)
    {
        case LBAniTypeMove::Move1:

            action = Sequence::createWithTwoActions(
                                                    DelayTime::create(waitSecond),
                                                    EaseInOut::create(MoveTo::create(0.2f,toPoint),1)
                                                    );
            Common::sound.play("Common:sfx_01");
            break;
        case LBAniTypeMove::Move2:

            action = Sequence::createWithTwoActions(
                                                    DelayTime::create(waitSecond),
                                                    EaseInOut::create(MoveTo::create(0.5f,toPoint),1)
                                                    );
            break;
        case LBAniTypeMove::Move3:
          
            action = MoveTo::create(0.1f,toPoint);
            Common::sound.play("Common:sfx_02");
            break;
        case LBAniTypeMove::Move4:
      
            if(moveTime==0.0f)
            {
                action = EaseInOut::create(MoveTo::create(0.5f,toPoint),1);
            } else 
            {
                action = EaseInOut::create(MoveTo::create(moveTime,toPoint),1);
            }
            break;
        case LBAniTypeMove::Move5:
           
            action = Sequence::create(
                                      EaseInOut::create(MoveTo::create(0.3f,toPoint+Vec2(0,-50)),1),
                                      EaseInOut::create(MoveBy::create(0.2f,Vec2(0,+75)),1),
                                      EaseInOut::create(MoveBy::create(0.2f,Vec2(0,-50)),1),
                                      EaseInOut::create(MoveBy::create(0.2f,Vec2(0,+50)),1),
                                      EaseInOut::create(MoveBy::create(0.2f,Vec2(0,-25)),1),
                                      nullptr
                                      );
            
            
        default:
            break;
    }
    action->setTag(LB_ANI_TYPE_MOVE_TAG);
    node->runAction(action);
    return action->getDuration();
}