
// WowPropertyGuideDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WowPropertyGuide.h"
#include "WowPropertyGuideDlg.h"
#include "afxdialogex.h"
#include "TIo.h"
#include "CHTCommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWowPropertyGuideDlg 对话框



CWowPropertyGuideDlg::CWowPropertyGuideDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WOWPROPERTYGUIDE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWowPropertyGuideDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialogEx::DoDataExchange(pDX);
        DDX_Control(pDX, IDC_LIST1, m_list0);
        DDX_Control(pDX, IDC_LIST2, m_list1);
        DDX_Control(pDX, IDC_COMBO1, m_combo_place);
        DDX_Control(pDX, IDC_EDIT_MIN_MINGZHONG, m_edit_min_minghzong);
        DDX_Control(pDX, IDC_EDIT2, m_baoji_xishu);
        DDX_Control(pDX, IDC_LIST3, m_list2);
}

BEGIN_MESSAGE_MAP(CWowPropertyGuideDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
        ON_CBN_SELCHANGE(IDC_COMBO1, &CWowPropertyGuideDlg::OnCbnSelchangeCombo1)
        ON_CBN_SELENDOK(IDC_COMBO1, &CWowPropertyGuideDlg::OnCbnSelendokCombo1)
        ON_CBN_EDITCHANGE(IDC_COMBO1, &CWowPropertyGuideDlg::OnCbnEditchangeCombo1)
        ON_CBN_EDITUPDATE(IDC_COMBO1, &CWowPropertyGuideDlg::OnCbnEditupdateCombo1)
        ON_CBN_CLOSEUP(IDC_COMBO1, &CWowPropertyGuideDlg::OnCbnCloseupCombo1)
        ON_BN_CLICKED(IDC_BUTTON1, &CWowPropertyGuideDlg::OnBnClickedButton1)
        ON_BN_CLICKED(IDC_BUTTON2, &CWowPropertyGuideDlg::OnBnClickedButton2)
        ON_BN_CLICKED(IDC_BUTTON3, &CWowPropertyGuideDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CWowPropertyGuideDlg 消息处理程序

BOOL CWowPropertyGuideDlg::OnInitDialog()
{
        AllocConsole();
        AttachConsole(GetCurrentProcessId());
        FILE* pFile;
        _tfreopen_s(&pFile, _T("CONOUT$"), _T("w"), stdout);
        _tfreopen_s(&pFile, _T("CONOUT$"), _T("w"), stderr);
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

        m_combo_place.AddString(L"头");
        m_combo_place.AddString(L"项链");
        m_combo_place.AddString(L"肩膀");
        m_combo_place.AddString(L"披风");
        m_combo_place.AddString(L"胸甲");
        m_combo_place.AddString(L"护腕");
        m_combo_place.AddString(L"手");
        m_combo_place.AddString(L"腰带");
        m_combo_place.AddString(L"腿");
        m_combo_place.AddString(L"鞋");
        m_combo_place.AddString(L"戒指");
        m_combo_place.SetCurSel(0);
        
        if (TIo::IsDirExists("equips"))
        {
                m_equips.InitFromFolders(L"equips");
                InitTaoZhuangPros(L"equips", m_taos);
        }
        else if (TIo::IsDirExists("..\\equips"))
        {
                m_equips.InitFromFolders(L"..\\equips");
                InitTaoZhuangPros(L"..\\equips", m_taos);
        }

        for (int i = 0; i < m_equips.GetEquips().size();i++)
        {
                Equip & eq = m_equips.GetEquips()[i];
                m_sel_equips[eq.m_place_type].GetEquips().push_back(eq);
        }



        FreshList();

        m_edit_min_minghzong.SetWindowText(L"0");
        m_baoji_xishu.SetWindowText(L"30");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWowPropertyGuideDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWowPropertyGuideDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWowPropertyGuideDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CWowPropertyGuideDlg::FreshList()
{
        CString combo_text;
        int nsel = m_combo_place.GetCurSel();
        m_combo_place.GetLBText(nsel, combo_text);
        Equip::PlaceType pt = ChineseToPlaceType((LPTSTR)(LPCTSTR)combo_text);
        m_list0.ResetContent();
        
        std::vector<Equip> & equs = m_equips.GetEquips();
        for (int i = 0; i < equs.size(); i++)
        {
                Equip & equ = equs[i];
                if (equ.m_place_type == pt)
                {
                        m_list0.AddString(equ.m_name.c_str());
                }
        }

        FreshList1(pt);
}



void CWowPropertyGuideDlg::FreshList1(Equip::PlaceType pt)
{
        m_list1.ResetContent();
        std::map<Equip::PlaceType, Equips>::iterator find_it = m_sel_equips.find(pt);
        if (find_it != m_sel_equips.end())
        {
                Equips & eqs = find_it->second;
                for (int i = 0; i < eqs.GetEquips().size(); i++)
                {
                        m_list1.AddString(eqs.GetEquips()[i].m_name.c_str());
                }
        }
}

void CWowPropertyGuideDlg::OnCbnSelchangeCombo1()
{
        // TODO: 在此添加控件通知处理程序代码
        FreshList();
}


void CWowPropertyGuideDlg::OnCbnSelendokCombo1()
{
        // TODO: 在此添加控件通知处理程序代码
        
}


void CWowPropertyGuideDlg::OnCbnEditchangeCombo1()
{
        // TODO: 在此添加控件通知处理程序代码
        
}


void CWowPropertyGuideDlg::OnCbnEditupdateCombo1()
{
        // TODO: 在此添加控件通知处理程序代码
        
}


void CWowPropertyGuideDlg::OnCbnCloseupCombo1()
{
        // TODO: 在此添加控件通知处理程序代码
        
}


void CWowPropertyGuideDlg::OnBnClickedButton1()
{
        // TODO: 在此添加控件通知处理程序代码
        int nsel0 = m_list0.GetCurSel();
        if (nsel0<0)
        {
                return;
        }
        CString com_text=L"";
        m_list0.GetText(nsel0, com_text);

        std::wstring wname = std::wstring((LPTSTR)(LPCTSTR)com_text);

        Equip * find_equ = NULL;
        for (int i = 0; i < m_equips.GetEquips().size();i++)
        {
                if (m_equips.GetEquips()[i].m_name == wname)
                {
                        find_equ = &m_equips.GetEquips()[i];
                        break;
                }
        }
        if (find_equ == NULL)
        {
                printf("not find equ by name\n");
                return;
        }

        CString combo_text;
        int nsel = m_combo_place.GetCurSel();
        m_combo_place.GetLBText(nsel, combo_text);
        Equip::PlaceType pt = ChineseToPlaceType((LPTSTR)(LPCTSTR)combo_text);

        m_sel_equips[pt].GetEquips().push_back(*find_equ);
        FreshList1(pt);
}


void CWowPropertyGuideDlg::OnBnClickedButton2()
{
        // TODO: 在此添加控件通知处理程序代码
        int nsel0 = m_list1.GetCurSel();
        if (nsel0<0)
        {
                return;
        }
        CString com_text = L"";
        m_list1.GetText(nsel0, com_text);
        std::wstring wname = std::wstring((LPTSTR)(LPCTSTR)com_text);

        CString combo_text;
        int nsel = m_combo_place.GetCurSel();
        m_combo_place.GetLBText(nsel, combo_text);
        Equip::PlaceType pt = ChineseToPlaceType((LPTSTR)(LPCTSTR)combo_text);

        std::vector<Equip> & equs = m_sel_equips[pt].GetEquips();
        std::vector<Equip>::iterator it = equs.begin();
        std::vector<Equip>::iterator find_it = equs.end();
        for (it; it != equs.end();it++)
        {
                if (it->m_name == wname)
                {
                        find_it = it;
                        break;
                }
        }
        if (find_it == equs.end())
        {
                return;
        }
        equs.erase(find_it);
        FreshList1(pt);
}

static void CycleSetEqus(
        std::map<Equip::PlaceType, Equips> & m_sel_equips,
        std::map<Equip::PlaceType, Equips>::iterator it,
        std::vector<Equips> & results,
        Equips & now_equ)
{
        if (it == m_sel_equips.end())
        {
                results.push_back(now_equ);
                return;
        }
        if (it->first != Equip::JIEZHI)
        {
                for (int i = 0; i < it->second.GetEquips().size(); i++)
                {
                        Equips new_equs = now_equ;
                        new_equs.GetEquips().push_back(it->second.GetEquips()[i]);
                        std::map<Equip::PlaceType, Equips>::iterator next_it = it;
                        next_it++;
                        CycleSetEqus(m_sel_equips, next_it, results, new_equs);
                }
        }
        else {

                if (it->second.GetEquips().size()==1)
                {
                        Equips new_equs = now_equ;
                        new_equs.GetEquips().push_back(it->second.GetEquips()[0]);
                        std::map<Equip::PlaceType, Equips>::iterator next_it = it;
                        next_it++;
                        CycleSetEqus(m_sel_equips, next_it, results, new_equs);
                }
                else {
                        for (int i = 0; i < it->second.GetEquips().size() - 1; i++)
                        {
                                for (int j = i+1; j < it->second.GetEquips().size();j++)
                                {
                                        Equips new_equs = now_equ;
                                        new_equs.GetEquips().push_back(it->second.GetEquips()[i]);
                                        new_equs.GetEquips().push_back(it->second.GetEquips()[j]);
                                        std::map<Equip::PlaceType, Equips>::iterator next_it = it;
                                        next_it++;
                                        CycleSetEqus(m_sel_equips, next_it, results, new_equs);
                                }
                        }
                }
        }

}


void CWowPropertyGuideDlg::OnBnClickedButton3()
{
        // TODO: 在此添加控件通知处理程序代码

        m_list2.ResetContent();
        CString cstr_min_mingzhong;
        m_edit_min_minghzong.GetWindowText(cstr_min_mingzhong);

        CString cstr_baoji_xishu;
        m_baoji_xishu.GetWindowText(cstr_baoji_xishu);

        float min_mingzhong = _wtof((LPTSTR)(LPCTSTR)cstr_min_mingzhong);
        float baoji_xishu = _wtof((LPTSTR)(LPCTSTR)cstr_baoji_xishu);

        std::vector<Equips> whole_equs;
        Equips begin_equs;
        CycleSetEqus(m_sel_equips, m_sel_equips.begin(), whole_equs, begin_equs);
        printf("whole_size(%d)\n", whole_equs.size());

        float max_score = -10000;
        Equips * max_eq = NULL;
        for (int i = 0; i < whole_equs.size();i++)
        {
                Equips & eq = whole_equs[i];
                float score = ZhanShiScoreCac(
                        eq, min_mingzhong, baoji_xishu,m_taos);
                if (score > max_score)
                {
                        max_score = score;
                        max_eq = &eq;
                }
        }
        printf("max score = %0.4f\n", max_score);

        if (max_eq)
        {
                std::vector<std::wstring> wss;
                wchar_t wstr[1024] = { 0 };
                swprintf_s(wstr, L"总得分=%0.4f", max_score);
                m_list2.AddString(wstr);
                max_eq->GetPrintStrings(m_taos,wss);
                for (int i = 0; i < wss.size();i++)
                {
                        m_list2.AddString(wss[i].c_str());
                        std::string str = CHTCommon::ANSIWStringtoANSIString(wss[i]);
                        printf("%s\n", str.c_str());
                }
        }
}
