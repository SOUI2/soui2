
#pragma once
#include "interface/Sskinobj-i.h"

namespace SOUI
{

// State Define
enum
{
    WndState_Normal       = 0x00000000UL,
    WndState_Hover        = 0x00000001UL,
    WndState_PushDown     = 0x00000002UL,
    WndState_Check        = 0x00000004UL,
    WndState_Invisible    = 0x00000008UL,
    WndState_Disable      = 0x00000010UL,
};

#define IIF_STATE2(the_state, normal_value, hover_value) \
    (((the_state) & WndState_Hover) ? (hover_value) : (normal_value))

#define IIF_STATE3(the_state, normal_value, hover_value, pushdown_value) \
    (((the_state) & WndState_PushDown) ? (pushdown_value) : IIF_STATE2(the_state, normal_value, hover_value))

#define IIF_STATE4(the_state, normal_value, hover_value, pushdown_value, disable_value) \
    (((the_state) & WndState_Disable) ? (disable_value) : IIF_STATE3(the_state, normal_value, hover_value, pushdown_value))


//////////////////////////////////////////////////////////////////////////
class SOUI_EXP SSkinImgList: public ISkinObj
{
    SOUI_CLASS_NAME(SSkinImgList, L"imglist")

public:
    SSkinImgList();
    virtual ~SSkinImgList();

    virtual void Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState,BYTE byAlpha=0xFF);

    virtual SIZE GetSkinSize();

    virtual BOOL IgnoreState();
    
    virtual int GetStates();
    void    SetStates(int nStates){m_nStates=nStates;}


    void SetImage(IBitmap *pImg)
    {
        if(m_pImg) m_pImg->Release();
        m_pImg=pImg;
        if(m_pImg) m_pImg->AddRef();
    }

    IBitmap * GetImage()
    {
        return m_pImg;
    }

    void SetTile(BOOL bTile){m_bTile=bTile;}
    BOOL IsTile(){return m_bTile;}

    void SetVertical(BOOL bVertical){m_bVertical=bVertical;}
    BOOL IsVertical(){return m_bVertical;}
    
protected:
    HRESULT OnAttrImage(const SStringW & strValue,BOOL bLoading);

    IBitmap *m_pImg;
    int  m_nStates;
    BOOL m_bTile;
    BOOL m_bVertical;
    
    SOUI_ATTRS_BEGIN()
        ATTR_CUSTOM(L"src", OnAttrImage)    //skinObj���õ�ͼƬ�ļ�������uires.idx�е�name���ԡ�
        ATTR_INT(L"tile", m_bTile, TRUE)    //�����Ƿ�ƽ��,0--λ�죨Ĭ�ϣ�������--ƽ��
        ATTR_INT(L"vertical", m_bVertical, TRUE)//��ͼ�Ƿ�ֱ���У�0--ˮƽ����(Ĭ��), ����--��ֱ����
        ATTR_INT(L"states",m_nStates,TRUE)  //��ͼ����,Ĭ��Ϊ1
    SOUI_ATTRS_END()
};

//////////////////////////////////////////////////////////////////////////
class SOUI_EXP SSkinImgFrame : public SSkinImgList
{
    SOUI_CLASS_NAME(SSkinImgFrame, L"imgframe")

public:
    SSkinImgFrame();


    void SetMargin(const CRect rcMargin){m_rcMargin=rcMargin;}

    CRect GetMargin(){return m_rcMargin;}

    virtual void Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState,BYTE byAlpha=0xFF);
protected:
    CRect m_rcMargin;

    SOUI_ATTRS_BEGIN()
        ATTR_INT(L"left", m_rcMargin.left, TRUE)        //�Ź�����߾�
        ATTR_INT(L"top", m_rcMargin.top, TRUE)          //�Ź����ϱ߾�
        ATTR_INT(L"right", m_rcMargin.right, TRUE)      //�Ź����ұ߾�
        ATTR_INT(L"bottom", m_rcMargin.bottom, TRUE)    //�Ź����±߾�
        ATTR_INT(L"margin-x", m_rcMargin.left=m_rcMargin.right, TRUE)//�Ź������ұ߾�
        ATTR_INT(L"margin-y", m_rcMargin.top=m_rcMargin.bottom, TRUE)//�Ź������±߾�
    SOUI_ATTRS_END()
};

//////////////////////////////////////////////////////////////////////////
class SOUI_EXP SSkinButton : public ISkinObj
{
    SOUI_CLASS_NAME(SSkinButton, L"button")

    enum{
        ST_NORMAL=0,
        ST_HOVER,
        ST_PUSHDOWN,
        ST_DISABLE,
    };

public:
    SSkinButton();

    virtual void Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState,BYTE byAlpha=0xFF);

    virtual BOOL IgnoreState();

    virtual int GetStates();

    void SetColors(COLORREF crUp[4],COLORREF crDown[4],COLORREF crBorder);

protected:
    COLORREF m_crBorder;

    COLORREF    m_crUp[4];
    COLORREF    m_crDown[4];
public:
    SOUI_ATTRS_BEGIN()
        ATTR_COLOR(L"colorBorder", m_crBorder, TRUE)                //�߿���ɫ
        ATTR_COLOR(L"colorUp", m_crUp[ST_NORMAL], TRUE)             //����״̬������ʼ��ɫ
        ATTR_COLOR(L"colorDown", m_crDown[ST_NORMAL], TRUE)         //����״̬������ֹ��ɫ
        ATTR_COLOR(L"colorUpHover", m_crUp[ST_HOVER], TRUE)         //����״̬������ʼ��ɫ
        ATTR_COLOR(L"colorDownHover", m_crDown[ST_HOVER], TRUE)     //����״̬������ֹ��ɫ
        ATTR_COLOR(L"colorUpPush", m_crUp[ST_PUSHDOWN], TRUE)       //��ѹ״̬������ʼ��ɫ
        ATTR_COLOR(L"colorDownPush", m_crDown[ST_PUSHDOWN], TRUE)   //��ѹ״̬������ֹ��ɫ
        ATTR_COLOR(L"colorUpDisable", m_crUp[ST_DISABLE], TRUE)     //����״̬������ʼ��ɫ
        ATTR_COLOR(L"colorDownDisable", m_crDown[ST_DISABLE], TRUE) //����״̬������ֹ��ɫ
    SOUI_ATTRS_END()
};

//////////////////////////////////////////////////////////////////////////

class SOUI_EXP SSkinGradation  : public ISkinObj
{
    SOUI_CLASS_NAME(SSkinGradation, L"gradation")
public:
    SSkinGradation();

    virtual void Draw(IRenderTarget *pRT, LPCRECT prcDraw, DWORD dwState,BYTE byAlpha=0xFF);
    
    void SetColorFrom(COLORREF crFrom)
    {
        m_crFrom=crFrom;
    }

    void SetColorTo(COLORREF crTo)
    {
        m_crTo=crTo;
    }

    void SetVertical(BOOL bVertical)
    {
        m_bVert=bVertical;
    }

protected:
    COLORREF m_crFrom;
    COLORREF m_crTo;
    BOOL m_bVert;

    SOUI_ATTRS_BEGIN()
        ATTR_COLOR(L"colorFrom", m_crFrom, TRUE)    //������ʼ��ɫ
        ATTR_COLOR(L"colorTo", m_crTo, TRUE)        //������ֹ��ɫ
        ATTR_INT(L"vertical", m_bVert, TRUE)        //���䷽��,0--ˮƽ(Ĭ��), 1--��ֱ
    SOUI_ATTRS_END()
};


//////////////////////////////////////////////////////////////////////////
//
enum SBSTATE{
    SBST_NORMAL=0,    //����״̬
    SBST_HOVER,        //hover״̬
    SBST_PUSHDOWN,    //����״̬
    SBST_DISABLE,    //����״̬
    SBST_INACTIVE,    //ʧ��״̬,��Ҫ������˵ļ�ͷ
};

#define MAKESBSTATE(sbCode,nState1,bVertical) MAKELONG((sbCode),MAKEWORD((nState1),(bVertical)))
#define SB_CORNOR        10
#define SB_THUMBGRIPPER    11    //�������ϵĿ��϶�����

#define THUMB_MINSIZE    18

class SOUI_EXP SSkinScrollbar : public SSkinImgList
{
    SOUI_CLASS_NAME(SSkinScrollbar, L"scrollbar")

public:

    SSkinScrollbar();

    virtual void Draw(IRenderTarget *pRT, LPCRECT prcDraw, DWORD dwState,BYTE byAlpha=0xFF);

    //ָʾ������Ƥ���Ƿ�֧����ʾ���¼�ͷ
    virtual BOOL HasArrow(){return TRUE;}
    
    virtual int GetIdealSize(){
        if(!m_pImg) return 0;
        return m_pImg->Width()/9;
    }

protected:
    //����Դָ��������ԭλͼ�ϵ�λ�á�
    CRect GetPartRect(int nSbCode, int nState,BOOL bVertical);
    int         m_nMargin;
    BOOL        m_bHasGripper;
    BOOL        m_bHasInactive;//��ʧ��״̬�ļ�ͷʱ��������Ƥ���б�����5�У����������3�л���4��

    SOUI_ATTRS_BEGIN()
        ATTR_INT(L"margin",m_nMargin,FALSE)             //��Ե�������С
        ATTR_INT(L"hasGripper",m_bHasGripper,FALSE)     //�������Ƿ��а���(gripper)
        ATTR_INT(L"hasInactive",m_bHasInactive,FALSE)   //�Ƿ��н���̬
    SOUI_ATTRS_END()
};

class SOUI_EXP SSkinMenuBorder : public SSkinImgFrame
{
    SOUI_CLASS_NAME(SSkinMenuBorder, L"border")

public:

    SSkinMenuBorder():m_rcBorder(1,1,1,1)
    {

    }

    CRect GetMarginRect()
    {
        return m_rcBorder;
    }
protected:
    CRect        m_rcBorder;

    SOUI_ATTRS_BEGIN()
        ATTR_RECT(L"border",m_rcBorder,FALSE)
    SOUI_ATTRS_END()
};

}//namespace SOUI