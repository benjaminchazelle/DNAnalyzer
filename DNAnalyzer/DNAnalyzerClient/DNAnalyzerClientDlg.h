
// DNAnalyzerClientDlg.h : fichier d'en-t�te
//

#pragma once
#include <unordered_map>
#include "Serveur.h"


// bo�te de dialogue CDNAnalyzerClientDlg
class CDNAnalyzerClientDlg : public CDialogEx
{
// Construction
public:
	CDNAnalyzerClientDlg(CWnd* pParent = NULL);	// constructeur standard

// Donn�es de bo�te de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DNANALYZERCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV


// Impl�mentation
protected:
	HICON m_hIcon;
	
	// Fonctions g�n�r�es de la table des messages
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedMfcmenubutton1();
	afx_msg void OnEnChangeMfceditbrowse1();
	unordered_map<int, Serveur> getServeurs();
	static UINT ObtenirMaladiesThread(void*);
	void unSetObtenirMaladiesThreadInstance();
	void setWindowTitle(string title);
protected:
	CString pathname;
	unordered_map<int,Serveur> serveurs;
	HANDLE* obtenirMaladiesThreadInstance;
public:
	afx_msg void OnCbnSelchangeCombo2();
};
