#ifndef __LOADING_SCENE_H__
#define __LOADING_SCENE_H__

#include "Common.h"

class Loading:public WJLayer
{
private:
    enum class Phase
    {
        kBeforeLoad, kLoad, kAfterLoad
    };
    enum class LoadingType
    {
        kNone, kFade, k3Step
        // 没有Loading，直接场景切换
        // 有Loading，使用Fade场景切换效果
        // 有Loading，分3步自定义实现场景切换效果
    };
    
    static Loading* gotoPhase(GameNumber gameNumber, void* userData, Phase phase);
    static Scene* createNextScene(GameNumber gameNumber, void* userData);
    static Node* createNextSceneNode(GameNumber gameNumber, void* userData);
    void doLoading();
    
    // step2 release and preload res
    void releaseResources();
    void loadNextSceneResources();
    void loadNextSceneSound();
    
    // 创建下一个场景
    void createAndShowNextScene();
    void showNextScene(Node *nextSceneNode);
    
    void onLoadScene3StepCompleted();
    
public:
    static Loading* gotoScene(GameNumber gameNumber, void* userData = nullptr);
    bool init(GameNumber gameNumber, void* userData, Phase phase);
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    
protected:
    
    WJLayerJson *m_loadingJson;
    GameNumber m_gameNumber;
    void* m_userData;
    Phase m_phase;                  // 处于哪个阶段
    
    long long m_startShowTime;      // 最低展示时间
    int m_asyncLoadTaskCount;       // 加载的资源
    
    // 为了释放listener
    EventListenerCustom* m_listenerStart;
    EventListenerCustom* m_listenerComplete;
    
    static bool s_isLoading;            // 是否正在加载
    static LoadingType s_loadingType; // 加载的类型
    
};

#endif // __LOADING_SCENE_H__