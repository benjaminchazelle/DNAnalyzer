
// DNAnalyzerClientDlg.h : fichier d'en-tête
//

#pragma once
#include <unordered_map>
#include "Serveur.h"


// boîte de dialogue CDNAnalyzerClientDlg
class CDNAnalyzerClientDlg : public CDialogEx
{
// Construction
public:
	CDNAnalyzerClientDlg(CWnd* pParent = NULL);	// constructeur standard

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DNANALYZERCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// Prise en charge de DDX/DDV


// Implémentation
protected:
	HICON m_hIcon;
	
	// Fonctions générées de la table des messages
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
	unordered_map<unsigned int, string> getMessagesOnglets();
	unordered_map<unsigned int, HANDLE*> getThreadsOnglets();
	//unordered_multiset<Serveur, string> getCacheMaladies();
	 
	static UINT ObtenirMaladiesThread(void*);
	static UINT AnalyseGlobaleThread(void*);
	static UINT AnalysePreciseThread(void*);
	void createTab(string title, string content);
	void unSetObtenirMaladiesThreadInstance();
	void setWindowTitle(string title);

	//TCITEM * getCurrentTab();
protected:
	CString pathname;
	unordered_map<int,Serveur> serveurs;
	unordered_map<unsigned int, string> messagesOnglets;
	unordered_map<unsigned int, HANDLE*> threadsOnglets;
	//unordered_multiset<Serveur, string> cacheMaladies;
	unsigned int nextTabId;
	HANDLE* obtenirMaladiesThreadInstance;

public:
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton1();
};
