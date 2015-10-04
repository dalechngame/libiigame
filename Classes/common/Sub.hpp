//
//  Sub.h
//  WeddingSalon
//
//  Created by DalechnMac on 15-9-28.
//
//

#ifndef __WeddingSalon__Sub_
#define __WeddingSalon__Sub_

#include "LBLibraryBase.h"
#include "PBase.h"

template<typename T, typename S>
class Sub :public Node
{
protected:
    virtual bool init() override;
    
    virtual  bool thingOnTouchAble(Node *node, WJTouchEvent *event);
    virtual bool thingOnWillMoveTo(Node *node, WJTouchEvent *event);
    virtual void thingOnTouchEnd(Node *node, WJTouchEvent *event);
    virtual void thingOnClick(Node *node, WJTouchEvent *event);
    
    T * m_fa;
	S * m_sub;
	WJLayerJson* m_sceneJson;
  
public:
	virtual void bind(T *fa, S* sub, WJLayerJson* json);
    
    CREATE_FUNC(Sub);
};

template<typename T, typename S>
bool Sub<T, S>::init()
{
	if (!(Node::init()))
	{
		return  false;
	}

	m_sceneJson = nullptr;
	m_fa  = nullptr;
	m_sub = nullptr;

	return true;
}

template<typename T, typename S>
void Sub<T, S>::bind(T *fa, S* sub,  WJLayerJson* json)
{
	m_fa = fa;
	m_sub = sub;
	m_sceneJson = json;
}

template<typename T, typename S>
bool Sub<T, S>::thingOnTouchAble(Node *node, WJTouchEvent *event)
{
	// to do
	return true;
}

template<typename T, typename S>
bool Sub<T, S>::thingOnWillMoveTo(Node *node, WJTouchEvent *event)
{
	//to do
	return true;
}

template<typename T, typename S>
void Sub<T, S>::thingOnTouchEnd(Node *node, WJTouchEvent *event)
{
	// to do
}

template<typename T, typename S>
void Sub<T, S>::thingOnClick(Node *node, WJTouchEvent *event)
{
	// to do
}

#define CREATE_SUB(__SUB_TYPE__, __FA_TYPE__, __SUB_NAME__, __WJ_NAME__) \
	Sub<__FA_TYPE__, __SUB_TYPE__> *sub = __SUB_NAME__::create(); \
	sub->bind(this, __WJ_NAME__, m_sceneJson); \
	sub->retain(); 

#endif /* defined(__WeddingSalon__Sub__) */
