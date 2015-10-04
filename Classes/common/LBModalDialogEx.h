#ifndef __MODAL_DIALOG_LAYER_EX_H__
#define __MODAL_DIALOG_LAYER_EX_H__


#include "LBModalDialogLayer.h"


enum class LBModalDialogAnimationTypeEx
{
    Scale             = 1,
    ScaleEaseBack,
    PopIn1,     //����ʽ���Ե���
    PopIn2,     //��С���󣩹���ʽ���Ե���
    PopIn3,     //��С���Գ���
    PopIn4,     //��С���󣩹���ʽ���Ե���(��)
    PopIn5      // ������������Ķ���
};

class LBModalDialogEx : public LBModalDialog
{
private:
    void playButtonShowAni();

    vector<std::string> m_buttonStringList;
    float m_buttonAddInterval;

public:
    static LBModalDialogEx *create(WJBase *contentNode, bool autoReleaseOnClose);

    void addAniButton(std::string buttonStr);           // �����Ҫ���ζ�����ʽ��ʾ�İ�ť
    void setAddButtonInterval(float time);          // ÿ����ť���ֵȴ�ʱ��

protected:
    virtual void doShowAnimation(int animationType);    // �ɸ��Ǵ˺����Զ���Ч��
    virtual void doCloseAnimation(int animationType);   // �ɸ��Ǵ˺����Զ���Ч��
};
#endif // !__MODAL_DIALOG_LAYER_EX_H__
