#ifndef __MODAL_DIALOG_LAYER_EX_H__
#define __MODAL_DIALOG_LAYER_EX_H__


#include "LBModalDialogLayer.h"


enum class LBModalDialogAnimationTypeEx
{
    Scale             = 1,
    ScaleEaseBack,
    PopIn1,     //果冻式渐显弹出
    PopIn2,     //（小到大）果冻式渐显弹出
    PopIn3,     //大到小渐显出现
    PopIn4,     //（小到大）果冻式渐显弹出(慢)
    PopIn5      // 从上面掉下来的动画
};

class LBModalDialogEx : public LBModalDialog
{
private:
    void playButtonShowAni();

    vector<std::string> m_buttonStringList;
    float m_buttonAddInterval;

public:
    static LBModalDialogEx *create(WJBase *contentNode, bool autoReleaseOnClose);

    void addAniButton(std::string buttonStr);           // 添加需要依次动画方式显示的按钮
    void setAddButtonInterval(float time);          // 每个按钮出现等待时间

protected:
    virtual void doShowAnimation(int animationType);    // 可覆盖此函数自定义效果
    virtual void doCloseAnimation(int animationType);   // 可覆盖此函数自定义效果
};
#endif // !__MODAL_DIALOG_LAYER_EX_H__
