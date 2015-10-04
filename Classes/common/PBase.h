#ifndef __PBASE_SCENE_H__
#define __PBASE_SCENE_H__

#include "cocos2d.h"
#include "LBToolbarLayer.h"
#include "LBModalDialogLayer.h"
#include "LBPopupMenu.h"
#include "LBSnapshotLayer.h"
#include "Common.h"
#include "Loading.h"
#include "Store.h"

USING_NS_CC;

#define ZORDER_SCENE_JSON			0
#define ZORDER_TOP_LAYER			1000
#define ZORDER_POPUPMENU			1000
#define ZORDER_ADS_LAYER			8000
#define ZORDER_SNAPSHOT				9000

// --------new macro----------
#define RESTORE_POS_TIME					0.3f				// 拖动的物品在松手之后回到原来的位置的时间
#define SCROLL_MOVE_TIME					0.5f			// 侧边框移动出现和消失的时间

#define SCREEN_CENTER				CENTER_SIZE(m_winSize)

#define VISIBLE_RECT_CENTER			CENTER_RECT(m_visibleRect)

#define VISIBLE_RECT_TOP			Vec2(m_visibleRect.getMidX(), m_visibleRect.getMaxY())
#define VISIBLE_RECT_BOTTOM			Vec2(m_visibleRect.getMidX(), m_visibleRect.getMinY())
#define VISIBLE_RECT_LEFT			Vec2(m_visibleRect.getMinX(), m_visibleRect.getMidY())
#define VISIBLE_RECT_RIGHT			Vec2(m_visibleRect.getMaxX(), m_visibleRect.getMidY())

#define VISIBLE_RECT_LEFT_TOP		Vec2(m_visibleRect.getMinX(), m_visibleRect.getMaxY())
#define VISIBLE_RECT_LEFT_BOTTOM	Vec2(m_visibleRect.getMinX(), m_visibleRect.getMinY())
#define VISIBLE_RECT_RIGHT_TOP		Vec2(m_visibleRect.getMaxX(), m_visibleRect.getMaxY())
#define VISIBLE_RECT_RIGHT_BOTTOM	Vec2(m_visibleRect.getMaxX(), m_visibleRect.getMinY())

class PBase : public WJLayer
{
protected:
	void* m_userData;

	Size m_winSize;
	Size m_visibleSize;
    Rect m_visibleRect;
	Vec2 m_origin;

	WJLayer* m_topLayer;

	WJLayerJson* m_sceneJson;
	LBPopupMenu *m_popupMenu;
	LBSnapshotLayer *m_snapShot;

	LayerColor* m_adsLayer;
	bool m_adsLayerVisible;

	EventListenerCustom* m_storeEventListener;
	EventListenerCustom* m_getfreeEventListener;

	virtual GameNumber getGameNumber() = 0;	// override me.
	std::string getGameName();

	virtual void initSceneJson(const char* jsonFileName);
	virtual void initPopupMenu();
	virtual void initSnapshot();
	virtual void initAdsBanner();
	virtual void showGameAds();
	void refreshAdBanner(float duration);

	virtual void onPopupMenuClick(Node* node, WJTouchEvent* event);

    virtual void showSnapshot(const char* fileName = nullptr);
	virtual void onSnapshotClick(Node* node, WJTouchEvent* event);
	virtual void onSnapshotBefore();	// override me.
	virtual void onSnapshotAfter();
	virtual void onSnapshotClosed();	// override me.

	virtual void onStoreClosedAndPurchased();	// override me.
	virtual void onGetFreeVideoClosed(const char* getFreeLockKey, bool isUnlocked);	// override me.
    virtual void onGetFreeVideoUnlocked(const char* getFreeLockKey);                // override me.

	virtual void playGameBgMusic();

	virtual void showInfoDialog();

public:
    void showStarAni(WJSprite *starSprite);
public:
	PBase();
	virtual ~PBase();
	virtual bool init() override;

	virtual void onEnter() override;
	virtual void onEnterTransitionDidFinish() override;
	virtual void onExit() override;
};

#endif // __PBASE_SCENE_H__
