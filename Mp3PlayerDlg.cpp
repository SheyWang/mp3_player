
// Mp3PlayerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Mp3Player.h"
#include "Mp3PlayerDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMp3PlayerDlg 对话框




CMp3PlayerDlg::CMp3PlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMp3PlayerDlg::IDD, pParent)
	, m_playListStr(_T(""))
	, str4(_T(""))
	, m_index(-1)
	, zflag(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	s=-1;
	m_id=NULL;
	m_isOpen=false;
	m_isPlay=false;
	length=L"00:00";
	current=L"00:00";
	h=0;
	len=0;
	cur=0;
	volume=700;
	m_playListStr=_T(" ");
	m_songIndex=-1;
	zflag=0;
}

void CMp3PlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Slider(pDX, IDC_VOLUME, m_volume);
	DDX_Control(pDX, IDC_VOLUME, m_volume);
	DDX_Control(pDX, IDC_LIST, m_playList);
	DDX_LBString(pDX, IDC_LIST, m_playListStr);
}

BEGIN_MESSAGE_MAP(CMp3PlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &CMp3PlayerDlg::OnClickedOpen)
	ON_BN_CLICKED(IDC_PLAY, &CMp3PlayerDlg::OnClickedPlay)
	ON_BN_CLICKED(IDC_STOP, &CMp3PlayerDlg::OnClickedStop)
	ON_WM_TIMER()

//	ON_STN_CLICKED(IDC_TIME, &CMp3PlayerDlg::OnStnClickedTime)
ON_WM_HSCROLL()
ON_BN_CLICKED(IDC_ADD_DLG, &CMp3PlayerDlg::OnBnClickedAddDlg)
ON_LBN_SELCHANGE(IDC_LIST, &CMp3PlayerDlg::OnSelchangeList)
ON_BN_CLICKED(IDC_FOLDER, &CMp3PlayerDlg::OnClickedFolder)
ON_LBN_DBLCLK(IDC_LIST, &CMp3PlayerDlg::OnDblclkList)
ON_BN_CLICKED(IDC_NEXT, &CMp3PlayerDlg::OnBnClickedNext)
ON_BN_CLICKED(IDC_BEFORE, &CMp3PlayerDlg::OnBnClickedBefore)
ON_BN_CLICKED(IDC_DELETE, &CMp3PlayerDlg::OnBnClickedDelete)
ON_BN_CLICKED(IDC_CLEAR, &CMp3PlayerDlg::OnBnClickedClear)
END_MESSAGE_MAP()


// CMp3PlayerDlg 消息处理程序

BOOL CMp3PlayerDlg::OnInitDialog()
{
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_pro.Create(WS_CHILD | WS_VISIBLE | PBS_SMOOTH,CRect(15,60,180,65),this,123);
//	m_pro.SetPos(50);
	m_volume.SetRange(0,1000);
	m_volume.SetPos(1000-volume);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMp3PlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMp3PlayerDlg::OnPaint()
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
HCURSOR CMp3PlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMp3PlayerDlg::OnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog open(true);

	open.m_ofn.lpstrFilter=L"mp3(*.mp3)\0*.mp3\0All Files(*.*)\0*.*\0";
	if(IDOK==open.DoModal())
	{
		mciSendCommand(m_id,MCI_CLOSE,NULL,NULL);
		m_index=-1;
		h=1;
		str1=open.GetPathName();
		open1.dwCallback = NULL;
		open1.lpstrAlias = NULL;
    	open1.lpstrDeviceType = _T("MPEGAudio");
		open1.lpstrElementName = str1;
		open1.wDeviceID = NULL;
		str4=open.GetFileName();
	//	SetDlgItemText(IDC_STATIC_INFO,str);

		int index = m_playList.AddString(open.GetFileName());
		m_playList.SetItemDataPtr(index, new CString(open.GetPathName()));

	//	s=mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT | MCI_WAIT | MCI_OPEN_SHAREABLE,(DWORD)(LPVOID)&open1);
	//	if (s==0)
	//		m_id=open1.wDeviceID;
	//	else
	//		m_id=NULL;
		
	}
}


void CMp3PlayerDlg::OnClickedPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	play1.dwCallback=NULL;
	play1.dwFrom=0; 

	if((h || (m_playListStr!=" ")))
	{
	//	s=-1;
	//	m_open=true;
		SetDlgItemText(IDC_STATIC_INFO,str4);
		mciSendCommand(NULL,MCI_OPEN,MCI_OPEN_ELEMENT | MCI_WAIT | MCI_OPEN_SHAREABLE,(DWORD)(LPVOID)&open1);
		m_id=open1.wDeviceID;
		//设置时间
		MCI_STATUS_PARMS mcisp;
		mcisp.dwItem=MCI_STATUS_LENGTH;
		mciSendCommand(m_id,MCI_STATUS,MCI_WAIT | MCI_STATUS_ITEM,(DWORD)(LPVOID)&mcisp);
		len=mcisp.dwReturn;
		length.Format(L"%2d:%2d",mcisp.dwReturn/1000/60,mcisp.dwReturn/1000%60);
		CString str;
		str.Format(L"%s/%s",current,length);
		SetDlgItemText(IDC_TIME,str);

		//设置声音
		MCI_DGV_SETAUDIO_PARMS level;
		level.dwItem=MCI_DGV_SETAUDIO_VOLUME ;
		level.dwValue=volume;
		mciSendCommand(m_id,MCI_SETAUDIO,MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE,(DWORD)&level);

		if(!m_isPlay)
		{
			play1.dwCallback=NULL;
			play1.dwFrom=0; 
		//	mciSendCommand(m_id,MCI_PLAY,MCI_WAIT,(DWORD)&play1);//注意这里，用这一语句时，移动播放器时，会出现未响应情况，用下面的语句正确
			mciSendCommand(m_id,MCI_PLAY,MCI_NOTIFY,(DWORD)&play1);
			m_isPlay=true;
			SetDlgItemText(IDC_PLAY,L"暂停");
			GetDlgItem(IDC_OPEN)->EnableWindow(false);
			SetTimer(1,1000,NULL);
		
		}
		else
		{
			m_isPlay=false;
			mciSendCommand(m_id,MCI_PAUSE,NULL,NULL);
			SetDlgItemText(IDC_PLAY,L"播放");
			GetDlgItem(IDC_OPEN)->EnableWindow(true);
			s=0;
			KillTimer(1);
		}
	}
	else
	{
		MessageBox(L"请选择歌曲!");
	}
}


void CMp3PlayerDlg::OnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码

	if(m_isPlay)
	{
		m_isPlay=false;
	//	m_open=false; 
		h=0;
		mciSendCommand(m_id,MCI_CLOSE,NULL,NULL);
		SetDlgItemText(IDC_PLAY,L"播放");
		GetDlgItem(IDC_OPEN)->EnableWindow(true);
		m_pro.SetPos(0);
		KillTimer(1);
	}
}


void CMp3PlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	MCI_STATUS_PARMS m_time;
	m_time.dwItem=MCI_STATUS_POSITION;
	mciSendCommand(m_id,MCI_STATUS,MCI_STATUS_ITEM | MCI_WAIT,(DWORD)(LPVOID)&m_time);
	cur=m_time.dwReturn;
	current.Format(L"%2d:%2d",m_time.dwReturn/1000/60,m_time.dwReturn/1000%60);
	CString str;
	str.Format(L"%s/%s",current,length);
	SetDlgItemText(IDC_TIME,str);

	m_pro.SetPos(cur*100/len);//注意这里cur乘以100的意思，假如不乘100，整首歌播完以后，cur/len=1,那么进度栏只前进1格

	if(cur==len)
	{
		m_isPlay=false;
	//	m_open=false; 
		h=0;
		mciSendCommand(m_id,MCI_CLOSE,NULL,NULL);
		SetDlgItemText(IDC_PLAY,L"播放");
		GetDlgItem(IDC_OPEN)->EnableWindow(true);
		KillTimer(1);

		OnBnClickedNext();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CMp3PlayerDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	volume=m_volume.GetPos();
	MCI_DGV_SETAUDIO_PARMS level;
	level.dwItem=MCI_DGV_SETAUDIO_VOLUME ;
	level.dwValue=volume;
	mciSendCommand(m_id,MCI_SETAUDIO,MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE,(DWORD)&level);


	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMp3PlayerDlg::OnBnClickedAddDlg()
{
	// TODO: 在此添加控件通知处理程序代码
	CString str3;
	if (GetDlgItemText(IDC_ADD_DLG, str3), str3 == "+")
	{
		SetDlgItemText(IDC_ADD_DLG, L"—");
	}
	else
	{
		SetDlgItemText(IDC_ADD_DLG, L"+");
	}

	static CRect rectLarge;
	static CRect rectSmall;

	if (rectLarge.IsRectNull())
	{
		CRect rectSeparator;
		GetWindowRect(&rectLarge);
		GetDlgItem(IDC_SEPARATOR)->GetWindowRect(&rectSeparator);

		rectSmall.left=rectLarge.left;
		rectSmall.top=rectLarge.top;
		rectSmall.right=rectLarge.right;
		rectSmall.bottom=rectSeparator.bottom;
	}

	if (str3 == "—")
	{
		SetWindowPos(NULL,0,0,rectSmall.Width(),rectSmall.Height(),SWP_NOMOVE | SWP_NOZORDER);
	}
	else
	{
		SetWindowPos(NULL,0,0,rectLarge.Width(),rectLarge.Height(),SWP_NOMOVE | SWP_NOZORDER);
	}
}

void CMp3PlayerDlg::OnSelchangeList()
{
	// TODO: 在此添加控件通知处理程序代码
//	h=1;
	if (m_isPlay == false)
	{
		int index=m_playList.GetCurSel();
		m_songIndex=index;
	
		if (index==m_index)
		{
			return;
		}
		else
		{
			mciSendCommand(m_id,MCI_CLOSE,NULL,NULL);
			m_songPath=*(CString *)m_playList.GetItemDataPtr(index);
		//	m_songIndex=index;
			open1.dwCallback = NULL;
			open1.lpstrAlias = NULL;
			open1.lpstrDeviceType = _T("MPEGAudio");
			open1.lpstrElementName = m_songPath;
			open1.wDeviceID = NULL;

		//	CString str4;
			m_playList.GetText(index,str4);//得到歌曲列表的内容
			m_playListStr=str4;
		}
		m_index=index;
	}
}

void CMp3PlayerDlg::OnClickedFolder()
{
	// TODO: 在此添加控件通知处理程序代码
	CString FolderPath;
	char buffer[MAX_PATH];
	BROWSEINFO bf;
	bf.hwndOwner = NULL;
	bf.pidlRoot = NULL;
	bf.pszDisplayName = (LPWSTR)buffer;
	bf.lpszTitle = L"本地音乐";
	bf.ulFlags = BIF_EDITBOX;
	bf.lpfn=NULL;
	bf.lParam=NULL;
	bf.iImage = IDR_MAINFRAME;

	LPITEMIDLIST pList=(LPITEMIDLIST)CoTaskMemAlloc(sizeof(LPITEMIDLIST));  
    pList = SHBrowseForFolder(&bf);  
	if(pList)
	{
		SHGetPathFromIDList(pList,(LPWSTR)buffer);
		FolderPath=(LPWSTR)buffer;
	}
	CoTaskMemFree(pList);

	CFileFind finder;   //构造finder
	bool m_bFind;
	m_bFind=finder.FindFile(FolderPath+"\\*.mp3");
	while(m_bFind)
	{
		int index;
		m_bFind=finder.FindNextFile();
		//MessageBox(finder.GetFileName());   //
		index=m_playList.AddString(finder.GetFileName());
		m_playList.SetItemDataPtr(index,new CString(finder.GetFilePath()));

		//CString str=*(CString *)m_playList.GetItemDataPtr(m_playList.GetCount()-1);
		//MessageBox(str);
	}

		if(str4 == "")
		{
			m_playList.GetText(0,str4);
			m_playListStr = str4;
			m_playList.SetCurSel(0);
			m_songIndex = 0;

			mciSendCommand(m_id,MCI_CLOSE,NULL,NULL);
			m_songPath=*(CString *)m_playList.GetItemDataPtr(0);
		//	m_songIndex=index;
			open1.dwCallback = NULL;
			open1.lpstrAlias = NULL;
			open1.lpstrDeviceType = _T("MPEGAudio");
			open1.lpstrElementName = m_songPath;
			open1.wDeviceID = NULL;
		}
}

void CMp3PlayerDlg::OnDblclkList()
{
	// TODO: 在此添加控件通知处理程序代码
	OnClickedStop();

	int index=m_playList.GetCurSel();
	m_songPath=*(CString *)m_playList.GetItemDataPtr(index);
	m_songIndex=index;
	open1.dwCallback = NULL;
	open1.lpstrAlias = NULL;
	open1.lpstrDeviceType = _T("MPEGAudio");
	open1.lpstrElementName = m_songPath;
	open1.wDeviceID = NULL;

//	CString str4;
	m_playList.GetText(index,str4);//得到歌曲列表的内容
	m_playListStr=str4;

	m_index = -1;

	OnClickedPlay();
}

void CMp3PlayerDlg::OnBnClickedNext()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_songIndex>=0 && m_songIndex<m_playList.GetCount()-1)
	{
		OnClickedStop();

		int index = m_songIndex+1;
		m_playList.SetCurSel(index);

		OnSelchangeList();
		OnClickedPlay();
	}
	else if( m_songIndex >= m_playList.GetCount()-1 )
	{
		m_songIndex = 0;
		OnClickedStop();
		m_playList.SetCurSel(m_songIndex);

		OnSelchangeList();
		OnClickedPlay();
	}
}

void CMp3PlayerDlg::OnBnClickedBefore()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_songIndex>0 && m_songIndex<=m_playList.GetCount())
	{
		OnClickedStop();
		
		int index = m_songIndex-1;
		m_playList.SetCurSel(index);

		OnSelchangeList();
		OnClickedPlay();
	}
	else if( m_songIndex <= m_songIndex )
	{
		m_songIndex = m_playList.GetCount()-1;
		OnClickedStop();
		m_playList.SetCurSel(m_songIndex);

		OnSelchangeList();
		OnClickedPlay();
	}
}


void CMp3PlayerDlg::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	int index=m_playList.GetCurSel();
	if(LB_ERR==index)
	{
		MessageBox(L"请先选择要删除的歌曲！");
	}
	else
	{
		delete (CString *)m_playList.GetItemDataPtr(index);
		m_playList.DeleteString(index);
		m_songPath="";

		if( m_songIndex==index )
		{
			OnClickedStop();
		//	m_songIndex = index + 1;
			if(m_playList.GetCount()!=0)
			{
				m_playList.SetCurSel(m_songIndex);
				m_songPath=*(CString *)m_playList.GetItemDataPtr(index);
			//	m_songIndex=index;
				open1.dwCallback = NULL;
				open1.lpstrAlias = NULL;
				open1.lpstrDeviceType = _T("MPEGAudio");
				open1.lpstrElementName = m_songPath;
				open1.wDeviceID = NULL;
				m_playList.GetText(index,str4);//得到歌曲列表的内容
				m_playListStr=str4;
			}
			else
			{
					m_playListStr = " ";
					str4 = "";
			}
		}
	}
}


void CMp3PlayerDlg::OnBnClickedClear()
{
	// TODO: 在此添加控件通知处理程序代码
	while(m_playList.GetCount())
	{
		delete (CString *)m_playList.GetItemDataPtr(0);
		m_playList.DeleteString(0);
	}
	m_songPath="";

	OnClickedStop();
	m_playListStr = " ";
	str4 = "";
	SetDlgItemText(IDC_STATIC_INFO,L"欢迎使用Mp3Player");
}
