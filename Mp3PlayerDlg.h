
// Mp3PlayerDlg.h : ͷ�ļ�
//

#pragma once

#include "mmsystem.h"
#pragma comment(lib,"winmm.lib")
#include "Digitalv.h"//��������������ʱ��Ҫ��ӵ�ͷ�ļ�
#include "afxwin.h"
// CMp3PlayerDlg �Ի���
class CMp3PlayerDlg : public CDialogEx
{
// ����
public:
	CMp3PlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

	MCI_OPEN_PARMS open1;
	MCI_PLAY_PARMS play1;
	MCI_SET_PARMS m_set;
	UINT s;
	MCIDEVICEID m_id;
	MCI_SET_PARMS m_settime;
	CString str;
	CString str1;

// �Ի�������
	enum { IDD = IDD_MP3PLAYER_DIALOG };

	protected:
	virtual  DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
