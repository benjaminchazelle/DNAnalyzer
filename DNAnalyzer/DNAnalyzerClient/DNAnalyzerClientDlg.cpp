
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
#include <mutex>

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
	, nextTabId(0)

{
	LoadLibrary(L"Riched32.dll");
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
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDNAnalyzerClientDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON1, &CDNAnalyzerClientDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// gestionnaires de messages pour CDNAnalyzerClientDlg

mutex mtxServeurs;
mutex mtxMessages;
mutex mtxThreads;

BOOL CDNAnalyzerClientDlg::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();

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


	//Chargement des serveurs connu par l'application Client
	CComboBox * pCombo = (CComboBox *)GetDlgItem(IDC_COMBO2);

	Configuration & cf1 = Configuration::ObtenirInstance() ;
	string fichierConfig = "C:\\Users\\thomas\\Desktop\\testGL.txt";
	bool test = cf1.ChargerFichier(fichierConfig);

	if (!test)
	{
		MessageBox(_T("DNAnalyser ne trouve pas le fichier contenant les serveurs.\nArrêt de l'application."), _T("Error"),
			MB_ICONERROR | MB_OK);
		exit(0);
	}


	vector<struct Serveur> liste = cf1.ObtenirListeServeur();

	mtxServeurs.lock();
	for(vector<struct Serveur>::iterator i = liste.begin(); i!=liste.end();i++)
	{
		Serveur serv = *i;
		string str = serv.host + ":" + to_string(serv.port);
		CString aAfficher = (CString) str.c_str();
		int position = pCombo->AddString((LPCTSTR) aAfficher);
		serveurs[position] = *i;

	}
	mtxServeurs.unlock();
	pCombo->SetWindowText(L"Choisir un Serveur");
	GetDlgItem(IDC_COMBO2)->EnableWindow(false);
	GetDlgItem(IDC_COMBO1)->EnableWindow(false);
	GetDlgItem(IDC_MFCMENUBUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	SetWindowText(L"DNAnalyser");

	//Création de l'onglet Bienvenue

	CTabCtrl * pTC = (CTabCtrl *)GetDlgItem(IDC_TAB1);

	//insertion d'un onglet

	TCITEM tcItem = { 0 };
	tcItem.mask = TCIF_TEXT | TCIF_PARAM;
	tcItem.lParam = CDNAnalyzerClientDlg::nextTabId++;
	int iTabs = pTC->GetItemCount();

	tcItem.pszText = L"Bienvenue";
	pTC->SetItem(iTabs, &tcItem);
	pTC->InsertItem(iTabs, &tcItem);

	mtxMessages.lock();

	//mise à jour et affichage du contenu de l'onglet
	messagesOnglets[tcItem.lParam] = "Bienvenue sur DNAnalyser.\nVeuillez Sélectionner un génôme tester, un serveur d'analyse et une maladie à analyser.\nPour obtenir de l'aide, veuillez consulter le manuel utilisateur.";
	setMessageDisplay(this, tcItem.lParam);

	mtxMessages.unlock();

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


//Evènement de permission de lancer une analyse
void CDNAnalyzerClientDlg::OnCbnSelchangeCombo1()
{
	GetDlgItem(IDC_MFCMENUBUTTON1)->EnableWindow(true);
}

//Evènement de lancement d'Analyse
void CDNAnalyzerClientDlg::OnBnClickedMfcmenubutton1()
{

	//Récupération des paramètres nécessaires à l'analyse
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

	string serv = serveur.host + ":" + to_string(serveur.port);
	string title = " - " + serv;

	//Choix du type d'analyse à réaliser et lancement d'un nouveau thread dédié à cette unique analyse
	if (maladie == "=Analyse Globale (Toutes les maladies)=")
	{
		string content = "Envoi d'une requête d'Analyse Globale au serveur " + serv;
		createTab(title, content);
		CWinThread * analyseGlob = AfxBeginThread(AnalyseGlobaleThread, this);
		mtxThreads.lock();
		threadsOnglets[CDNAnalyzerClientDlg::nextTabId-1] = &(analyseGlob->m_hThread);
		mtxThreads.unlock();
	}
	else
	{
		string content = "Envoi d'une requête d'Analyse Précise au serveur " + serv+" pour la maladie : "+maladie;
		createTab(title, content);
		CWinThread * analysePrec = AfxBeginThread(AnalysePreciseThread, this);
		mtxThreads.lock();
		threadsOnglets[CDNAnalyzerClientDlg::nextTabId-1] = &(analysePrec->m_hThread);
		mtxThreads.unlock();
	}

}

//Evènement résultant d'un choix d'un fichier de génome à analyser
void CDNAnalyzerClientDlg::OnEnChangeMfceditbrowse1()
{
	UpdateData(true);

	GetDlgItem(IDC_COMBO2)->EnableWindow(true);
}

//Méthode de récupération des serveurs stockés
unordered_map<int, Serveur> CDNAnalyzerClientDlg::getServeurs()
{
	return serveurs;
}

//Méthode de récupération des messages d'onglets stockés
unordered_map<unsigned int, string> CDNAnalyzerClientDlg::getMessagesOnglets()
{
	return messagesOnglets;
}

//Méthode de récupération des threads lancés
unordered_map<unsigned int, HANDLE*> CDNAnalyzerClientDlg::getThreadsOnglets()
{
	return threadsOnglets;
}

/*
unordered_multiset<Serveur, string> CDNAnalyzerClientDlg::getCacheMaladies()
{
	return unordered_multiset<Serveur, string>();
}
*/

//Méthode de mise à jour du titre de la fenêtre
void CDNAnalyzerClientDlg::setWindowTitle(string title)
{
	CString cs = (CString)title.c_str();
	SetWindowTextW((LPCTSTR)cs);
}

//Méthode d'affichage du contenu de l'onglet actif
void CDNAnalyzerClientDlg::setMessageDisplay(CDNAnalyzerClientDlg * fen, int param)
{
	CRichEditCtrl* rich = (CRichEditCtrl*)fen->GetDlgItem(IDC_RICHEDIT23);

	CString cstringed = (CString)fen->messagesOnglets[param].c_str();

	rich->SetWindowTextW((LPCTSTR)cstringed);
}

//Evènement de sélection d'un serveur à qui adresser une analyse
void CDNAnalyzerClientDlg::OnCbnSelchangeCombo2()
{
	//Récupération du serveur sélectionné
	GetDlgItem(IDC_MFCMENUBUTTON1)->EnableWindow(false);
	CComboBox * pCombo1 = (CComboBox *)GetDlgItem(IDC_COMBO2);
	CComboBox * pCombo = (CComboBox *)GetDlgItem(IDC_COMBO1);
	int index = pCombo1->GetCurSel();
	Serveur serveur = serveurs[index];
	pCombo->ResetContent();
	pCombo->AddString(L"=Analyse Globale (Toutes les maladies)=");
	pCombo->SetCurSel(0);
	GetDlgItem(IDC_COMBO1)->EnableWindow(true);

	// Lancement d'une requête de récupération des maladies que le serveur sélectionné peut analyser
	if (obtenirMaladiesThreadInstance != nullptr)
	{
		TerminateThread(*obtenirMaladiesThreadInstance, 1);
	}

	CWinThread * maladiesServeur = AfxBeginThread(ObtenirMaladiesThread, this);
	CWnd * label = (CWnd*) GetDlgItem(IDS_ABOUTBOX);
	label->SetWindowText(L"Statut chargement maladies :\nChargement des maladies en cours...");
	obtenirMaladiesThreadInstance = &(maladiesServeur->m_hThread);
}

//Thread chargé de récupérer les maladies présentes sur un serveur et de mettre à jour le panel de choix de maladies à analyser
UINT CDNAnalyzerClientDlg::ObtenirMaladiesThread(void *pParam)
{

	CDNAnalyzerClientDlg* pThis = (CDNAnalyzerClientDlg*)pParam;

	//Récupération du serveur actuellement sélectionné
	CComboBox * pCombo1 = (CComboBox *)pThis->GetDlgItem(IDC_COMBO2);
	CComboBox * pCombo = (CComboBox *)pThis->GetDlgItem(IDC_COMBO1);
	int index = pCombo1->GetCurSel();
	Serveur serveur = pThis->getServeurs()[index];


	try
	{
		//Lancement de la requête de récupération des maladies
		unordered_set<string> maladies = Service::ObtenirMaladies(serveur);

		//Mise à jour des maladies sujettes à une analyse par le serveur sélectionné
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

//Thread charger de réaliser une analyse globale
UINT CDNAnalyzerClientDlg::AnalyseGlobaleThread(void * pParam)
{
	//Récupération des paramètres d'analyse
	CDNAnalyzerClientDlg* pThis = (CDNAnalyzerClientDlg*)pParam;
	CComboBox * pCombo1 = (CComboBox *)pThis->GetDlgItem(IDC_COMBO2);
	CComboBox * pCombo = (CComboBox *)pThis->GetDlgItem(IDC_COMBO1);
	int ind = pCombo1->GetCurSel();
	Serveur serveur = pThis->serveurs[ind];
	CString choix;

	CT2CA pathnameAConvertir(pThis->pathname);
	std::string filename(pathnameAConvertir);

	//Création d'un nouvel onglet
	CTabCtrl * pTC = (CTabCtrl *)pThis->GetDlgItem(IDC_TAB1);
	int index = pTC->GetCurSel();
	TCHAR buf[256] = { 0 };
	TCITEM item;
	item.pszText = buf;
	item.cchTextMax = 256;
	item.lParam = 0;
	item.mask = TCIF_TEXT | TCIF_PARAM;

	BOOL test = pTC->GetItem(index, &item);

	pThis->setMessageDisplay(pThis, item.lParam);

	try
	{
		//Lancement d'une requête d'analyse globale
		unordered_set<string> resultats = Service::AnalyseGlobale(serveur, filename);

		//Récupération et affichage des résultats de l'anayse
		string newMessage = pThis->messagesOnglets[item.lParam]+"\nRésultats de l'analyse globale - Maladies détectées positivement :\n";
		if (resultats.size() != 0)
		{
			for (unordered_set<string>::iterator i = resultats.begin(); i != resultats.end(); i++)
			{
				newMessage += "- " + *i + "\n";
			}
		}
		else
		{
			newMessage += "Aucune maladie";
		}
		mtxMessages.lock();
		pThis->messagesOnglets[item.lParam] = newMessage;
		
		pTC->SetCurSel(index);

		pThis->setMessageDisplay(pThis, item.lParam);

		mtxMessages.unlock();

	}
	catch (exception const & e)
	{
		string newMessage = pThis->messagesOnglets[item.lParam] + "\nEchec de la communication avec le serveur.";
		mtxMessages.lock();
		pThis->messagesOnglets[item.lParam] = newMessage;
		
		pTC->SetCurSel(index);

		pThis->setMessageDisplay(pThis, item.lParam);

		mtxMessages.unlock();

	}

	return 0;
}

//Thread charger de réaliser une analyse précise
UINT CDNAnalyzerClientDlg::AnalysePreciseThread(void * pParam)
{
	//Récupération des paramètres d'analyse
	CDNAnalyzerClientDlg* pThis = (CDNAnalyzerClientDlg*)pParam;
	CComboBox * pCombo1 = (CComboBox *)pThis->GetDlgItem(IDC_COMBO2);
	CComboBox * pCombo = (CComboBox *)pThis->GetDlgItem(IDC_COMBO1);
	int ind = pCombo1->GetCurSel();
	Serveur serveur = pThis->serveurs[ind];
	CString choix;

	pCombo->GetLBText(pCombo->GetCurSel(), choix);
	CT2CA pszConvertedAnsiString(choix);
	std::string maladie(pszConvertedAnsiString);

	CT2CA pathnameAConvertir(pThis->pathname);
	std::string filename(pathnameAConvertir);

	//Création d'un nouvel onglet
	CTabCtrl * pTC = (CTabCtrl *)pThis->GetDlgItem(IDC_TAB1);
	int index = pTC->GetCurSel();
	TCHAR buf[256] = { 0 };
	TCITEM item;
	item.pszText = buf;
	item.cchTextMax = 256;
	item.lParam = 0;
	item.mask = TCIF_TEXT | TCIF_PARAM;

	BOOL test = pTC->GetItem(index, &item);

	pThis->setMessageDisplay(pThis, item.lParam);

	try
	{
		//Lancement d'une requête d'analyse précise
		bool resultat = Service::AnalysePrecise(serveur, filename, maladie);

		//Récupération des résultats
		string newMessage = pThis->messagesOnglets[item.lParam] + "\nRésultat de l'analyse précise - "+maladie+" : ";
		if (resultat)
		{
			newMessage += "test positif\n";
		}
		else
		{
			newMessage += "test négatif\n";
		}
		mtxMessages.lock();
		pThis->messagesOnglets[item.lParam] = newMessage;
		
		pTC->SetCurSel(index);

		pThis->setMessageDisplay(pThis, item.lParam);

		mtxMessages.unlock();

	}
	catch (exception const & e)
	{
		string newMessage = pThis->messagesOnglets[item.lParam] + "\nEchec de la communication avec le serveur.";
		mtxMessages.lock();
		pThis->messagesOnglets[item.lParam] = newMessage;
		
		pTC->SetCurSel(index);

		pThis->setMessageDisplay(pThis, item.lParam);

		mtxMessages.unlock();

	}

	return 0;
}

//Méthode de création d'un nouvel onglet
void CDNAnalyzerClientDlg::createTab(string title,string content)
{
	CTabCtrl * pTC = (CTabCtrl *)GetDlgItem(IDC_TAB1);
	TCITEM tcItem = { 0 };
	tcItem.mask = TCIF_TEXT | TCIF_PARAM;
	int iTabs = pTC->GetItemCount();
	string str = to_string(CDNAnalyzerClientDlg::nextTabId)+ title;
	CString titre = (CString)str.c_str();
	tcItem.pszText = (LPTSTR)(LPCTSTR) titre;
	tcItem.lParam = CDNAnalyzerClientDlg::nextTabId++;
	pTC->InsertItem(iTabs, &tcItem);
	pTC->SetCurSel(iTabs);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	mtxMessages.lock();
	messagesOnglets[tcItem.lParam] = content;
	mtxMessages.unlock();
}

//Méthode de récupération du thread actif d'obtention des maladies du serveur actuellement sélectionné
void CDNAnalyzerClientDlg::unSetObtenirMaladiesThreadInstance()
{
	obtenirMaladiesThreadInstance = nullptr;
}

//Evènement de sélection d'un onglet ouvert
void CDNAnalyzerClientDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	CTabCtrl * pTC = (CTabCtrl *)GetDlgItem(IDC_TAB1);
	int index = pTC->GetCurSel();
	if (index == 0)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	}
	else
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	}
	TCHAR buf[256] = { 0 };
	TCITEM item;
	item.pszText = buf;
	item.cchTextMax = 256;
	item.lParam = 0;
	item.mask = TCIF_TEXT | TCIF_PARAM;

	BOOL test = pTC->GetItem(index,&item);

	setMessageDisplay(this, item.lParam);
}

//Evènement de suppression de l'onglet sélectionné
void CDNAnalyzerClientDlg::OnBnClickedButton1()
{
	CTabCtrl * pTC = (CTabCtrl *)GetDlgItem(IDC_TAB1);
	int index = pTC->GetCurSel();
	TCHAR buf[256] = { 0 };
	TCITEM item;
	item.pszText = buf;
	item.cchTextMax = 256;
	item.lParam = 0;
	item.mask = TCIF_TEXT | TCIF_PARAM;

	BOOL test = pTC->GetItem(index, &item);
	mtxThreads.lock();
	HANDLE * aSuppr = threadsOnglets[item.lParam];
	TerminateThread(*aSuppr, 1);
	mtxThreads.unlock();
	mtxMessages.lock();
	messagesOnglets[item.lParam]="";
	mtxMessages.unlock();
	BOOL suppr = pTC->DeleteItem(index);
	int newIndex = (index - 1) < 0 ? index + 1 : index - 1;
	pTC->SetCurSel(newIndex);
	if (newIndex == 0)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	}
	test = pTC->GetItem(newIndex, &item);
	
	setMessageDisplay(this, item.lParam);
}
