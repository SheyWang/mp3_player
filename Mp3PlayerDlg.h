
// Mp3PlayerDlg.h : 头文件
//

#pragma once

#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")
#include "Digitalv.h"//这里是设置音量时需要添加的头文件
#include "afxwin.h"
// CMp3PlayerDlg 对话框
class CMp3PlayerDlg : public CDialogEx
{
// 构造
public:
	CMp3PlayerDlg(CWnd* pParent = NULL);	// 标准构造函数

	MCI_OPEN_PARMS open1;
	MCI_PLAY_PARMS play1;
	MCI_SET_PARMS m_set;
	UINT s;
	MCIDEVICEID m_id;
	MCI_SET_PARMS m_settime;
	CString str;
	CString str1;

// 对话框数据
	enum { IDD = IDD_MP3PLAYER_DIALOG };

	protected:
	virtual  DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedOpen();
	afx_msg void OnClickedPlay();
	afx_msg void OnClickedStop();
private:
	int h;
	DWORD cur;
	DWORD len;
	CProgressCtrl m_pro;
	UINT volume;
	CString current;
	CString length;
	BOOL m_isPlay;
	BOOL m_isOpen;
	CString m_songPath;
	int m_songIndex;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
//	int m_volume;
public:

//	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CSliderCtrl m_volume;
//	afx_msg void OnStnClickedTime();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnBnClickedAddDlg();
	afx_msg void OnSelchangeList();
	CListBox m_playList;
	CString m_playListStr;
	CString str4;
private:
	int m_index;
	int zflag;
public:
	afx_msg void OnClickedFolder();
	afx_msg void OnDblclkList();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedBefore();
//	afx_msg void OnBnClickedButton5();
//	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedClear();
};
