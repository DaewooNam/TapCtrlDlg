
// TapCtrlDlgDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "TapCtrlDlg.h"
#include "TapCtrlDlgDlg.h"
#include "afxdialogex.h"

#include "CQuestDlg1.h"
#include "CQuestDlg2.h"
#include "CQuestDlg3.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CTapCtrlDlgDlg 대화 상자



CTapCtrlDlgDlg::CTapCtrlDlgDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAPCTRLDLG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTapCtrlDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTapCtrlDlgDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CTapCtrlDlgDlg::OnTcnSelchangeTabMain)
END_MESSAGE_MAP()


// CTapCtrlDlgDlg 메시지 처리기

BOOL CTapCtrlDlgDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	m_pTabCtrl = (CTabCtrl*)GetDlgItem(IDC_TAB_MAIN);
	m_pTabCtrl->InsertItem(0, "Quest1");
	m_pTabCtrl->InsertItem(1, "Quest2");
	m_pTabCtrl->InsertItem(2, "Quest3"); // text 값 삽입

	m_enDlgType = DT_QUEST1;


	CRect rc; // MFC rect 값
	m_pTabCtrl->GetClientRect(&rc);

	
	

	/*
	//m_pDlg[DT_QUEST1]->Create(IDD_DIALOG_QUEST1, m_pTabCtrl);

	m_pDlg[DT_QUEST1] = (CDialog*)GetDlgItem(IDD_DIALOG_QUEST1);
	m_pDlg[DT_QUEST1]->Create(IDD_DIALOG_QUEST1);
	m_pDlg[DT_QUEST1]->SetWindowPos(NULL, 0, 25, rc.Width(), rc.Height(), SWP_HIDEWINDOW);

	
	m_pDlg[DT_QUEST2] = (CDialog*)GetDlgItem(IDD_DIALOG_QUEST2);
	m_pDlg[DT_QUEST2]->SetWindowPos(NULL, 0, 25, rc.Width(), rc.Height(), SWP_HIDEWINDOW);

	m_pDlg[DT_QUEST3] = (CDialog*)GetDlgItem(IDD_DIALOG_QUEST3);
	m_pDlg[DT_QUEST3]->SetWindowPos(NULL, 0, 25, rc.Width(), rc.Height(), SWP_HIDEWINDOW);

	*/
	

	m_pDlg[DT_QUEST1] = new CQuestDlg1; // class 사용시 항상 include 가 필요함 IDD 값은 동적할당을 항상 해줘야 한다.
	m_pDlg[DT_QUEST1]->Create(IDD_DIALOG_QUEST1, m_pTabCtrl);
	m_pDlg[DT_QUEST1]->SetWindowPos(NULL,0,25,rc.Width(),rc.Height(),SWP_HIDEWINDOW);


	m_pDlg[DT_QUEST2] = new CQuestDlg2;
	m_pDlg[DT_QUEST2]->Create(IDD_DIALOG_QUEST2, m_pTabCtrl); //부모를 연결 시켜 주는것
	m_pDlg[DT_QUEST2]->SetWindowPos(NULL, 0, 25, rc.Width(), rc.Height(), SWP_HIDEWINDOW);


	m_pDlg[DT_QUEST3] = new CQuestDlg3;
	m_pDlg[DT_QUEST3]->Create(IDD_DIALOG_QUEST3, m_pTabCtrl);
	m_pDlg[DT_QUEST3]->SetWindowPos(NULL, 0, 25, rc.Width(), rc.Height(), SWP_HIDEWINDOW);


	m_pCurrDlg = m_pDlg[m_enDlgType];
	m_pCurrDlg->ShowWindow(SW_SHOW);




	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTapCtrlDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTapCtrlDlgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTapCtrlDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CTapCtrlDlgDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	int idx = m_pTabCtrl->GetCurSel();

	//예외처리
	if (idx >= DT_MAX)
		return;
	if (idx == (int)m_enDlgType) //자기자신을 클릭시
		return; 

	m_pCurrDlg->ShowWindow(SW_HIDE);
	m_enDlgType = (DLGTYPE)idx;

	m_pCurrDlg = m_pDlg[m_enDlgType];
	m_pCurrDlg->ShowWindow(SW_SHOW);
	
	
	
	*pResult = 0;
}


BOOL CTapCtrlDlgDlg::DestroyWindow()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	for (int i = 0; i < DT_MAX; i++)
	{
		
		m_pDlg[i]->DestroyWindow();

		delete m_pDlg[i];

	}
		
	return CDialogEx::DestroyWindow();
}
