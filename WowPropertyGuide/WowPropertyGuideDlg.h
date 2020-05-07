
// WowPropertyGuideDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "Equip.h"
#include "map"


// CWowPropertyGuideDlg �Ի���
class CWowPropertyGuideDlg : public CDialogEx
{
// ����
public:
	CWowPropertyGuideDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WOWPROPERTYGUIDE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

        void FreshList();
        void FreshList1(Equip::PlaceType pt);
public:
        CListBox m_list0;
        CListBox m_list1;

        Equips m_equips;
        std::map<Equip::PlaceType, Equips> m_sel_equips;

        std::vector<TaoZhuangPro> m_taos;
        CComboBox m_combo_place;
        afx_msg void OnCbnSelchangeCombo1();
        afx_msg void OnCbnSelendokCombo1();
        afx_msg void OnCbnEditchangeCombo1();
        afx_msg void OnCbnEditupdateCombo1();
        afx_msg void OnCbnCloseupCombo1();
        afx_msg void OnBnClickedButton1();
        afx_msg void OnBnClickedButton2();
        afx_msg void OnBnClickedButton3();
        CEdit m_edit_min_minghzong;
        CEdit m_baoji_xishu;
        CListBox m_list2;
};
