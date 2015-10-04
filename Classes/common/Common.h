// Created by wangwenjie on 2013/04

#ifndef __COMMON_H__
#define __COMMON_H__

#include "cocos2d.h"
#include "string"
#include "vector"
#include "LBLibraryBase.h"
#include "ConfigFoolHead.h"
#include "LBAudioControllerT.hpp"
#include "CommonTemplate.h"
#include "ConfigLanguageSetting.h"

USING_NS_CC;

#define DEBUG_NO_ADS				1       //  0 or 1
#define DEBUG_NO_IAP                1       //  0 or 1
#define DEBUG_SHOW_TEST_MENU		1		//	0 or 1

extern  float  TO_SCALE_WIDTH;
extern  float  TO_SCALE_HEIGHT;

// size
#define winSize Director::getInstance()->getWinSize()
//#define visibleSize Director::getInstance()->getVisibleSize();
//#define  visibleOrigin Director::getInstance()->getVisibleOrigin()
//#define frameSize Director::getInstance()->getOpenGLView()->getFrameSize()

// platform
#define PC_PLATFORM CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 \
|| CC_TARGET_PLATFORM == CC_PLATFORM_MAC

// ----- MENU_BUTTON_TAG -----
#define MENU_TAG_PLAY       101 //play
#define MENU_TAG_EMAIL		102 //email
#define MENU_TAG_TWITTER	103 //twitter
#define MENU_TAG_FACEBOOK	104 // facebook
#define MENU_TAG_FORWARD	105 // forward
#define MENU_TAG_RESET		106 // reset
#define MENU_TAG_CHG_BG		108 //changebg
#define MENU_TAG_CAMERA		109 // camera
#define MENU_TAG_PHOTOS		110 // photos
#define MENU_TAG_RATE		111 // rate
#define MENU_TAG_TAKEPIC    112 // takepicture
#define MENU_TAG_STORE		113 // store
#define MENU_TAG_AWARD      114 // award
#define MENU_TAG_CONTEST	115 // contest
#define MENU_TAG_BUY        116 // buy
#define MENU_TAG_HAND		117 // hand
#define MENU_TAG_TOALL		118 // toall
#define MENU_TAG_RESET2		119 // reset2
#define MENU_TAG_UNDO		120 // undo
#define MENU_TAG_DELETE		121 // delete
#define MENU_TAG_NEXT		122 // next
#define MENU_TAG_DONE		123 // done
#define MENU_TAG_SKIP		124 // skip
#define MENU_TAG_MOREGAME   125 // moregame
#define MENU_TAG_INFO       126 // info
#define MENU_TAG_EDIT       127 // edit
#define MENU_TAG_CANCEL     128 // cancel
#define MENU_TAG_ALBUM      129 // album
#define MENU_TAG_LIKEUS_FORFREE    130 // like_us_forfree
#define MENU_TAG_FORPARENTS 131 // forparents

#define LOCKED_TAG          5680
#define LOCKED_NAME			"lock"
#define GETFREE_NAME		"getfree"

#define IAP_PLIST_FOLDER        "store"
#define IAP_PLIST_FILENAME      "productInfo.plist"
#define IAP_UNLOCKALL_KEY		"_unlockAll_"
#define IAP_UNLOCKNOADS_KEY		"_unlockAds_"

#define CENTER_SIZE(_SIZE_)     Vec2(_SIZE_.width / 2, _SIZE_.height / 2)
#define CENTER_RECT(_RECT_)     Vec2(_RECT_.getMidX(), _RECT_.getMidY())


// ----- common begin--------------------------------------------------------------------------

#define APP_TARGET_KINDLE_FIRE		1 // kind_fire
#define APP_TARGET_GOOGLE			2 // google
#define APP_TARGET_IOS              3 // ios
#define APP_TARGET_WP8              4 // wp8

#define URL_TWITTER					"http://twitter.com/libiitech"
#define URL_FACEBOOK				"http://www.facebook.com/LibiiGame"
#define URL_WECHAT                  "http://libii.com/t+wxhp"

#define URL_MOREGAME_UPDATE			""  // blank
#define URL_FOR_PARENTS				"http://libii.com/for_parents.html"
#define URL_AWARD					"http://www.libii.com/award/award_show.action"


#define MESSAGE_RESET				"Reset?|Are you sure you want to reset?"

#define MESSAGE_GOHOME			"Are you sure you want to start over? All changes will be lost."

//#define MESSAGE_CONTEST			"Cake of the Week!|Challenge for the weekly cake award.\nSend us the most awesome photos about you and cake.|Later|Go"

//#define MESSAGE_LIKEUS_FORFREE	"|You don't own this item. Would you like to Unlock %s? This feature will unlock all items in this package.|Cancel|Like Us & Unlock(Free)|Purchase"

//#define EMAIL_CONTEST				"cakeaward@libiitech.com|Submit for Wedding Salon Contest|Tell us your story about cake.|"

#define FACEBOOK_APPID			"1418438228371570"      // girls game2
//#define FACEBOOK_APPID			"274636492672269"       // cooking game
//#define FACEBOOK_APPID				"518642684872109"       // kids game
#define FACEBOOK_SHARE				""

#define SAVETO_ALBUM_FOLDER			"PrincessNewBaby"          // folder name
#define PACKAGE_NAME				"com.libii.princessnewbaby"

#define CTV(key1, key2)				CommonTemplateTem(std::string(key1).append(":").append(key2)).Value.c_str()

#define APP_LANG_IS_CN				ConfigLanguageSetting::instance().getCurLanguage() == LanguageType::CHINESE
#define APP_LANG_IS_EN				ConfigLanguageSetting::instance().getCurLanguage() == LanguageType::ENGLISH

// ----- common end--------------------------------------------------------------------------

// ----- platform begin--------------------------------------------------------------------------
// ----- for ios ------------------------------------------------------------------------------
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define APP_TARGET						APP_TARGET_IOS
#define CTV_KEY							"iOS"

#define URL_MOREGAME_DEF				""
#endif

// ----- for android --------------------------------------------------------------------------
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM \
== CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#define SESSION_TIME		30000						// 30s for Android

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)

#define APP_TARGET		APP_TARGET_GOOGLE			// for desktop test
#endif

#if APP_TARGET == APP_TARGET_KINDLE_FIRE    // for kindle_fire

#define CTV_KEY						"Amazon"
#define URL_MOREGAME_DEF			"http://amzn.to/JbvTei"
#endif

#if APP_TARGET == APP_TARGET_GOOGLE     // for google

#define CTV_KEY						"Google"
#define URL_MOREGAME_DEF			"market://search?q=libiitech&c=apps"
#endif
#endif

// --- common settings
#define THIS_APP_ID							CTV(CTV_KEY, "THIS_APP_ID")

#define THIS_APP_STORE_URL					CTV(CTV_KEY, "THIS_APP_STORE_URL")
#define THIS_APP_STORE_URL_LONG				CTV(CTV_KEY, "THIS_APP_STORE_URL_LONG")

#define GOOGLE_ADS_ID						CTV(CTV_KEY, "GOOGLE_ADS_ID")
#define GOOGLE_ADS_ID_INTERSTITIAL			CTV(CTV_KEY, "GOOGLE_ADS_ID_INTERSTITIAL")

#define EMAIL_FEEDBACK						CTV(CTV_KEY, "EMAIL_FEEDBACK")

// --- for ios
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define EMAIL_SHARE						StringUtils::format(CTV(CTV_KEY, "EMAIL_SHARE"), THIS_APP_STORE_URL, THIS_APP_STORE_URL, THIS_APP_STORE_URL, nullptr).c_str()

#define RATE_MESSAGE					""  // blank
#define RATE_URL						std::string(THIS_APP_ID).append("|").append(THIS_APP_STORE_URL_LONG).c_str()
#define RATE_NEW_VERSION_RATE_AGAIN		false
#endif

// --- for android
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
#define EMAIL_SHARE						StringUtils::format(CTV(CTV_KEY, "EMAIL_SHARE"), THIS_APP_STORE_URL_LONG, nullptr).c_str()

#define RATE_MESSAGE		            "If you like this game please rate it to keep free updates coming. Thanks!"
#define RATE_URL			            THIS_APP_STORE_URL
#define RATE_NEW_VERSION_RATE_AGAIN		false
#endif
// ----- platform begin--------------------------------------------------------------------------

// --------create func---------------------------------------------------------------------------------
#define CREATE_SCENE_FUNC(__TYPE__)					\
static Node* createSceneNode(void* userData = nullptr)	\
{													\
    __TYPE__ *layer = new __TYPE__();				\
    layer->m_userData = userData;					\
    layer->autorelease();							\
    layer->init();									\
    return layer;									\
};                                                 \
static Scene* createScene(void* userData = nullptr) \
{                                                   \
    Scene *scene = Scene::create();					\
    scene->addChild(createSceneNode(userData));     \
    return scene;                                   \
}

#define INIT_SCENE_LOADER_ASYNC(__GAMENUMBER__)	\
static PLoader loader(GameNumber::__GAMENUMBER__, &__GAMENUMBER__::createSceneNode, &__GAMENUMBER__::asyncLoadSceneResource);

#define INIT_SCENE_LOADER_SYNC(__GAMENUMBER__)	\
static PLoader loader(GameNumber::__GAMENUMBER__, &__GAMENUMBER__::createSceneNode, nullptr);

enum class GameNumber
{
    P000 = 0,
    P001,
    P002,
    P003,
    P004,
    P005,
    P006,
    P007,
    P008,
    P009,
    P010,
    P011,
    P012,
    P013,
    P014,
    P015,
    P016,
    P017,
    P018,
    P019,
    P020
};

typedef Node* (*SEL_CreateSceneNode)(void*);
typedef void   (*SEL_AsyncLoadSceneResource)();

// 文件加载器
class PLoader
{
private:
    static std::map<GameNumber, PLoader*>* s_loaderMap;
    
    GameNumber m_gameNumber;
    SEL_CreateSceneNode m_createSceneSelector;
    SEL_AsyncLoadSceneResource m_asyncLoadSceneSelector;
    
public:
    GameNumber getGameNumber();
    SEL_CreateSceneNode getCreateSceneSelector();
    SEL_AsyncLoadSceneResource getAsyncLoadSceneSelector();
    
    static PLoader* getLoader(GameNumber gameNumber);
    
public:
    PLoader(GameNumber gameNumber,
            SEL_CreateSceneNode createSceneSelector,
            SEL_AsyncLoadSceneResource asyncLoadSceneSelector);
};

// 商店广告相关
class Common
{
private:
    static int s_bgMusicIndex;
    
    static ValueMap* s_lockDict;
    
    static std::map<GameNumber, std::string> s_gameNamesMap;
    
public:
    // ----- Sound
    static LBAudioControllerT<SoundTemplate> sound;
    static void loadCommonEffect();
    // -----
    
    // ----- GameNumber
    
    static std::string getGameName(GameNumber gameNumber);
    static GameNumber getGameNumber(const std::string& gameName);
    
    // ----- IAP & ADS
    static ValueVector getProductInfoArray();
    
    static bool isInAppPurchasedByKey( const char* lockKey, bool checkAll = true );
    static bool isInAppPurchased( const char* iapId, bool checkAll = true );
    
    static bool isGetFreeUnlocked( const char* getFreeLockKey );
    
    static void showAds();
    static cocos2d::Size getAdsSize();
    static bool isAdsRemoved();
    // -----
    
    // ----- ChartBoost
    static void showChartBoost(WJChartboostLocation location = WJChartboostLocation::LevelComplete,
                               bool forceCount = false, bool forceShow = false);
    static void showChartBoostOnPlayButton();
    // -----
    
    // ----- Lock
    static ValueMap* getLockDict();
    static int getLockStartNo(const char* key);
    
    static std::string getLockIapId(const char* key);
    static std::string getUnlockAllIapId();
    static std::string getUnlockNoAdsIapId();
    
    static std::string getLockOtherString(const char* key, const char* otherKey);
    // -----
    
};

#endif // __COMMON_H__
