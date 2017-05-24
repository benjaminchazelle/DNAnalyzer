
// DNAnalyzerClientDlg.cpp : fichier d'implémentation
//

#include "stdafx.h"
#include "DNAnalyzerClient.h"
#include "DNAnalyzerClientDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include "string.h"
#include "Configuration.h"
#include "Service.h"
#include "Serveur.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// boîte de dialogue CAboutDlg utilisée pour la boîte de dialogue 'À propos de' pour votre application

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Données de boîte de dialogue
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // Prise en charge de DDX/DDV

// Implémentation
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


// boîte de dialogue CDNAnalyzerClientDlg



CDNAnalyzerClientDlg::CDNAnalyzerClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DNANALYZERCLIENT_DIALOG, pParent)
	, pathname(_T(""))
	, obtenirMaladiesThreadInstance(nullptr)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDNAnalyzerClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MFCEDITBROWSE1, pathname);
}

BEGIN_MESSAGE_MAP(CDNAnalyzerClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDNAnalyzerClientDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_MFCMENUBUTTON1, &CDNAnalyzerClientDlg::OnBnClickedMfcmenubutton1)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CDNAnalyzerClientDlg::OnEnChangeMfceditbrowse1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CDNAnalyzerClientDlg::OnCbnSelchangeCombo2)
END_MESSAGE_MAP()


// gestionnaires de messages pour CDNAnalyzerClientDlg

BOOL CDNAnalyzerClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Ajouter l'élément de menu "À propos de..." au menu Système.

	// IDM_ABOUTBOX doit se trouver dans la plage des commandes système.
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

	// Définir l'icône de cette boîte de dialogue.  L'infrastructure effectue cela automatiquement
	//  lorsque la fenêtre principale de l'application n'est pas une boîte de dialogue
	SetIcon(m_hIcon, TRUE);			// Définir une grande icône
	SetIcon(m_hIcon, FALSE);		// Définir une petite icône

	// TODO: ajoutez ici une initialisation supplémentaire

	CComboBox * pCombo = (CComboBox *)GetDlgItem(IDC_COMBO2);

	Configuration & cf1 = Configuration::ObtenirInstance() ;
	string fichierConfig = "C:\\Users\\thomas\\Desktop\\testGL.txt";
	bool test = cf1.ChargerFichier(fichierConfig);

	if (!test)
	{
		cout << "Erreur de chargement des serveur, arrêt de l'application.";
		exit(0);
	}


	vector<struct Serveur> liste = cf1.ObtenirListeServeur();


	for(vector<struct Serveur>::iterator i = liste.begin(); i!=liste.end();i++)
	{
		Serveur serv = *i;
		string str = serv.host + ":" + to_string(serv.port);
		CString aAfficher = (CString) str.c_str();
		int position = pCombo->AddString((LPCTSTR) aAfficher);
		serveurs[position] = *i;

	}

	pCombo->SetWindowText(L"Choisir un Serveur");
	GetDlgItem(IDC_COMBO2)->EnableWindow(false);
	GetDlgItem(IDC_COMBO1)->EnableWindow(false);
	GetDlgItem(IDC_MFCMENUBUTTON1)->EnableWindow(false);
	SetWindowText(L"DNAnalyser");
	return TRUE;  
}

void CDNAnalyzerClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// Si vous ajoutez un bouton Réduire à votre boîte de dialogue, vous devez utiliser le code ci-dessous
//  pour dessiner l'icône.  Pour les applications MFC utilisant le modèle Document/Vue,
//  cela est fait automatiquement par l'infrastructure.

void CDNAnalyzerClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // contexte de périphérique pour la peinture

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Centrer l'icône dans le rectangle client
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Dessiner l'icône
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Le système appelle cette fonction pour obtenir le curseur à afficher lorsque l'utilisateur fait glisser
//  la fenêtre réduite.
HCURSOR CDNAnalyzerClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CDNAnalyzerClientDlg::OnCbnSelchangeCombo1()
{
	GetDlgItem(IDC_MFCMENUBUTTON1)->EnableWindow(true);
}


void CDNAnalyzerClientDlg::OnBnClickedMfcmenubutton1()
{
	CComboBox * pCombo1 = (CComboBox *)GetDlgItem(IDC_COMBO2);
	CComboBox * pCombo = (CComboBox *)GetDlgItem(IDC_COMBO1);
	int index = pCombo1->GetCurSel();
	Serveur serveur = serveurs[index];
	CString choix;

	pCombo->GetLBText(pCombo->GetCurSel(), choix);
	CT2CA pszConvertedAnsiString(choix);
	std::string maladie(pszConvertedAnsiString);

	CT2CA pathnameAConvertir(pathname);
	std::string filename(pathnameAConvertir);

	if (maladie == "_Analyse Globale (Toutes les maladies)_")
	{
		CTabCtrl * pTC = (CTabCtrl *)GetDlgItem(IDC_TAB1);
		TCITEM tcItem = { 0 };
		CString pszString;
		TCHAR buffer[256] = { 0 };
		tcItem.mask = TCIF_TEXT;
		int iTabs = pTC -> GetItemCount();
		

		for (int j = 0; j < iTabs; j++)
		{
			// Get tab item and display its name (just for testing)
			pTC ->GetItem(j, &tcItem);
			MessageBox(tcItem.pszText, _T("TabName"));
		} // for (int j = 0; j &lt; iTabs; j++)

		  // Insert the new tab
		//sprintf(szTabName, _T("Tab #%d"), i);
		tcItem.pszText = buffer;
		pTC->GetItem(0, &tcItem);
		TRACE(_T("Changing item text from %s to %s..."), tcItem.pszText, pszString);
		tcItem.pszText = pszString.LockBuffer();
		//tcItem.lParam = 0;
		pTC->SetItem(0, &tcItem);
		tcItem.pszText = L"Troll";
		pTC ->InsertItem(iTabs, &tcItem);
		pszString.UnlockBuffer();
		//pTC ->SetCurSel(0);
		/*
		CString pszString;

		//  Get text for the tab item.
		GetDlgItemText(IDC_ITEM_TEXT, pszString);

		//  Get the current tab item text.
		TCHAR buffer[256] = {0};
		tcItem.pszText = buffer;
		tcItem.cchTextMax = 256;
		tcItem.mask = TCIF_TEXT;
		m_TabCtrl.GetItem(0, &tcItem);
		TRACE(_T("Changing item text from %s to %s..."), tcItem.pszText, pszString);

		//  Set the new text for the item.
		tcItem.pszText = pszString.LockBuffer();

		//  Set the item in the tab control.
		m_TabCtrl.SetItem(0, &tcItem);

		pszString.UnlockBuffer();
		*/
		//unordered_set<string> resultats = Service::AnalyseGlobale(serveur, filename);
	}
	else
	{
		bool resultat = Service::AnalysePrecise(serveur, filename, maladie);
	}
	

}



void CDNAnalyzerClientDlg::OnCbnSelchangeCombo1()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle

}


void CDNAnalyzerClientDlg::OnBnClickedMfcmenubutton1()
{
	// TODO: ajoutez ici le code de votre gestionnaire de notification de contrôle
}


void CDNAnalyzerClientDlg::OnEnChangeMfceditbrowse1()
{
	UpdateData(true);

	GetDlgItem(IDC_COMBO2)->EnableWindow(true);
}

unordered_map<int, Serveur> CDNAnalyzerClientDlg::getServeurs()
{
	return serveurs;
}

void CDNAnalyzerClientDlg::setWindowTitle(string title)
{
	CString cs = (CString)title.c_str();
	SetWindowTextW((LPCTSTR)cs);
}


void CDNAnalyzerClientDlg::OnCbnSelchangeCombo2()
{
	GetDlgItem(IDC_MFCMENUBUTTON1)->EnableWindow(false);
	CComboBox * pCombo1 = (CComboBox *)GetDlgItem(IDC_COMBO2);
	CComboBox * pCombo = (CComboBox *)GetDlgItem(IDC_COMBO1);
	int index = pCombo1->GetCurSel();
	Serveur serveur = serveurs[index];
	pCombo->ResetContent();
	pCombo->AddString(L"_Analyse Globale (Toutes les maladies)_");
	pCombo->SetCurSel(0);
	GetDlgItem(IDC_COMBO1)->EnableWindow(true);
	if (obtenirMaladiesThreadInstance != nullptr)
	{
		TerminateThread(*obtenirMaladiesThreadInstance, 1);
	}

	CWinThread * plop = AfxBeginThread(ObtenirMaladiesThread, this);
	CWnd * label = (CWnd*) GetDlgItem(IDS_ABOUTBOX);
	label->SetWindowText(L"Statut chargement maladies :\nChargement des maladies en cours...");
	obtenirMaladiesThreadInstance = &(plop->m_hThread);
	


}
	
UINT CDNAnalyzerClientDlg::ObtenirMaladiesThread(void *pParam)
{

	CDNAnalyzerClientDlg* pThis = (CDNAnalyzerClientDlg*)pParam;

	CComboBox * pCombo1 = (CComboBox *)pThis->GetDlgItem(IDC_COMBO2);
	CComboBox * pCombo = (CComboBox *)pThis->GetDlgItem(IDC_COMBO1);
	int index = pCombo1->GetCurSel();
	Serveur serveur = pThis->getServeurs()[index];


	try
	{
		unordered_set<string> maladies = Service::ObtenirMaladies(serveur);
		for (unordered_set<string>::iterator i = maladies.begin(); i != maladies.end(); i++)
		{
			CString cs = (CString)(*i).c_str();
			pCombo->AddString((LPCTSTR)cs);
		}
		CWnd * label = (CWnd*)pThis->GetDlgItem(IDS_ABOUTBOX);
		label->SetWindowText(L"Statut chargement maladies :\nChargement des maladies effectué avec succès.");

	}
	catch (exception const & e)
	{
		CWnd * label = (CWnd*)pThis->GetDlgItem(IDS_ABOUTBOX);
		label->SetWindowText(L"Statut chargement maladies :\nEchange avec le serveur impossible, échec du chargement des maladies.");
	}


	pThis->unSetObtenirMaladiesThreadInstance();

	return 0;
}

void CDNAnalyzerClientDlg::unSetObtenirMaladiesThreadInstance()
{
	obtenirMaladiesThreadInstance = nullptr;
}
