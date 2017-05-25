
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
	CComboBox * comboServeurs = (CComboBox *)GetDlgItem(IDC_COMBO2);

	Configuration & configuration = Configuration::ObtenirInstance() ;
	string fichierConfig = "./serveurs.config";
	bool chargement = configuration.ChargerFichier(fichierConfig);

	if (!chargement)
	{
		MessageBox(_T("DNAnalyser ne trouve pas le fichier contenant les serveurs.\nArrêt de l'application."), _T("Error"),
			MB_ICONERROR | MB_OK);
		exit(0);
	}


	vector<struct Serveur> listeServeurs = configuration.ObtenirListeServeur();

	mtxServeurs.lock();
	for(vector<struct Serveur>::iterator i = listeServeurs.begin(); i!= listeServeurs.end();i++)
	{
		Serveur serv = *i;
		string str = serv.host + ":" + to_string(serv.port);
		CString aAfficher = (CString) str.c_str();
		int position = comboServeurs->AddString((LPCTSTR) aAfficher);
		serveurs[position] = *i;

	}
	mtxServeurs.unlock();
	comboServeurs->SetWindowText(L"Choisir un Serveur");
	GetDlgItem(IDC_COMBO2)->EnableWindow(false);
	GetDlgItem(IDC_COMBO1)->EnableWindow(false);
	GetDlgItem(IDC_MFCMENUBUTTON1)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	SetWindowText(L"DNAnalyser");

	//Création de l'onglet Bienvenue

	CTabCtrl * ongletControlleur = (CTabCtrl *)GetDlgItem(IDC_TAB1);

	//insertion d'un onglet

	TCITEM onglet = { 0 };
	onglet.mask = TCIF_TEXT | TCIF_PARAM;
	onglet.lParam = CDNAnalyzerClientDlg::nextTabId++;
	int nbOnglets = ongletControlleur->GetItemCount();

	onglet.pszText = L"Bienvenue";
	ongletControlleur->SetItem(nbOnglets, &onglet);
	ongletControlleur->InsertItem(nbOnglets, &onglet);

	mtxMessages.lock();

	//mise à jour et affichage du contenu de l'onglet
	messagesOnglets[onglet.lParam] = "Bienvenue sur DNAnalyser.\nVeuillez Sélectionner un génôme tester, un serveur d'analyse et une maladie à analyser.\nPour obtenir de l'aide, veuillez consulter le manuel utilisateur.";
	setMessageDisplay(this, onglet.lParam);

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
	CComboBox * comboServeurs = (CComboBox *)GetDlgItem(IDC_COMBO2);
	CComboBox * comboMaladies = (CComboBox *)GetDlgItem(IDC_COMBO1);
	int indexServeurCourant = comboServeurs->GetCurSel();
	Serveur serveur = serveurs[indexServeurCourant];
	CString choixMaladie;

	comboMaladies->GetLBText(comboMaladies->GetCurSel(), choixMaladie);
	CT2CA pszConvertedAnsiString(choixMaladie);
	std::string maladie(pszConvertedAnsiString);

	string serv = serveur.host + ":" + to_string(serveur.port);
	string titreOnglet = " - " + serv;

	//Choix du type d'analyse à réaliser et lancement d'un nouveau thread dédié à cette unique analyse
	if (maladie == "=Analyse Globale (Toutes les maladies)=")
	{
		string contenuOnglet = "Envoi d'une requête d'Analyse Globale au serveur " + serv;
		createTab(titreOnglet, contenuOnglet);
		CWinThread * analyseGlobThread = AfxBeginThread(AnalyseGlobaleThread, this);
		mtxThreads.lock();
		threadsOnglets[CDNAnalyzerClientDlg::nextTabId-1] = &(analyseGlobThread->m_hThread);
		mtxThreads.unlock();
	}
	else
	{
		string contenuOnglet = "Envoi d'une requête d'Analyse Précise au serveur " + serv+" pour la maladie : "+maladie;
		createTab(titreOnglet, contenuOnglet);
		CWinThread * analysePrecThread = AfxBeginThread(AnalysePreciseThread, this);
		mtxThreads.lock();
		threadsOnglets[CDNAnalyzerClientDlg::nextTabId-1] = &(analysePrecThread->m_hThread);
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
void CDNAnalyzerClientDlg::setMessageDisplay(CDNAnalyzerClientDlg * fen, int idOnglet)
{
	CRichEditCtrl* rich = (CRichEditCtrl*)fen->GetDlgItem(IDC_RICHEDIT23);

	CString cstringed = (CString)fen->messagesOnglets[idOnglet].c_str();

	rich->SetWindowTextW((LPCTSTR)cstringed);
}

//Evènement de sélection d'un serveur à qui adresser une analyse
void CDNAnalyzerClientDlg::OnCbnSelchangeCombo2()
{
	//Récupération du serveur sélectionné
	GetDlgItem(IDC_MFCMENUBUTTON1)->EnableWindow(false);
	CComboBox * comboServeurs = (CComboBox *)GetDlgItem(IDC_COMBO2);
	CComboBox * comboMaladies = (CComboBox *)GetDlgItem(IDC_COMBO1);
	int indexServeurCourant = comboServeurs->GetCurSel();
	Serveur serveur = serveurs[indexServeurCourant];
	comboMaladies->ResetContent();
	comboMaladies->AddString(L"=Analyse Globale (Toutes les maladies)=");
	comboMaladies->SetCurSel(0);
	GetDlgItem(IDC_COMBO1)->EnableWindow(true);

	// Lancement d'une requête de récupération des maladies que le serveur sélectionné peut analyser
	if (obtenirMaladiesThreadInstance != nullptr)
	{
		TerminateThread(*obtenirMaladiesThreadInstance, 1);
	}

	CWinThread * maladiesServeurThread = AfxBeginThread(ObtenirMaladiesThread, this);
	CWnd * labelStatutChargementMaladies = (CWnd*) GetDlgItem(IDS_ABOUTBOX);
	labelStatutChargementMaladies->SetWindowText(L"Statut chargement maladies :\nChargement des maladies en cours...");
	obtenirMaladiesThreadInstance = &(maladiesServeurThread->m_hThread);
}

//Thread chargé de récupérer les maladies présentes sur un serveur et de mettre à jour le panel de choix de maladies à analyser
UINT CDNAnalyzerClientDlg::ObtenirMaladiesThread(void * window)
{

	CDNAnalyzerClientDlg* fenetre = (CDNAnalyzerClientDlg*)window;

	//Récupération du serveur actuellement sélectionné
	CComboBox * comboServeurs = (CComboBox *)fenetre->GetDlgItem(IDC_COMBO2);
	CComboBox * comboMaladies = (CComboBox *)fenetre->GetDlgItem(IDC_COMBO1);
	int indexServeurCourant = comboServeurs->GetCurSel();
	Serveur serveur = fenetre->getServeurs()[indexServeurCourant];


	try
	{
		//Lancement de la requête de récupération des maladies
		unordered_set<string> maladies = Service::ObtenirMaladies(serveur);

		//Mise à jour des maladies sujettes à une analyse par le serveur sélectionné
		for (unordered_set<string>::iterator i = maladies.begin(); i != maladies.end(); i++)
		{
			CString cs = (CString)(*i).c_str();
			comboMaladies->AddString((LPCTSTR)cs);
		}
		CWnd * labelStatutChargementMaladies = (CWnd*)fenetre->GetDlgItem(IDS_ABOUTBOX);
		labelStatutChargementMaladies->SetWindowText(L"Statut chargement maladies :\nChargement des maladies effectué avec succès.");

	}
	catch (runtime_error const & e)
	{
		CWnd * labelStatutChargementMaladies = (CWnd*)fenetre->GetDlgItem(IDS_ABOUTBOX);
		labelStatutChargementMaladies->SetWindowText(L"Statut chargement maladies :\nEchange avec le serveur impossible, échec du chargement des maladies.");
	}
	catch (logic_error const & e)
	{
		CWnd * labelStatutChargementMaladies = (CWnd*)fenetre->GetDlgItem(IDS_ABOUTBOX);
		labelStatutChargementMaladies->SetWindowText(L"Statut chargement maladies :\nRéponse du serveur incorrecte, échec du chargement des maladies.");
	}
	catch (domain_error const & e)
	{
		CWnd * labelStatutChargementMaladies = (CWnd*)fenetre->GetDlgItem(IDS_ABOUTBOX);
		labelStatutChargementMaladies->SetWindowText(L"Statut chargement maladies :\nRequête envoyée au serveur incorrecte, échec du chargement des maladies.");
	}

	fenetre->unSetObtenirMaladiesThreadInstance();

	return 0;
}

//Thread charger de réaliser une analyse globale
UINT CDNAnalyzerClientDlg::AnalyseGlobaleThread(void * window)
{
	//Récupération des paramètres d'analyse
	CDNAnalyzerClientDlg* fenetre = (CDNAnalyzerClientDlg*)window;
	CComboBox * comboServeurs = (CComboBox *)fenetre->GetDlgItem(IDC_COMBO2);
	int indexServeurCourant = comboServeurs->GetCurSel();
	Serveur serveur = fenetre->serveurs[indexServeurCourant];

	CT2CA pathnameAConvertir(fenetre->pathname);
	std::string fichierGenome(pathnameAConvertir);

	//Création d'un nouvel onglet
	CTabCtrl * ongletControlleur = (CTabCtrl *)fenetre->GetDlgItem(IDC_TAB1);
	int indexOnglet = ongletControlleur->GetCurSel();
	TCHAR buf[256] = { 0 };
	TCITEM onglet;
	onglet.pszText = buf;
	onglet.cchTextMax = 256;
	onglet.lParam = 0;
	onglet.mask = TCIF_TEXT | TCIF_PARAM;

	BOOL test = ongletControlleur->GetItem(indexOnglet, &onglet);

	fenetre->setMessageDisplay(fenetre, onglet.lParam);

	try
	{
		//Lancement d'une requête d'analyse globale
		unordered_set<string> resultats = Service::AnalyseGlobale(serveur, fichierGenome);

		//Récupération et affichage des résultats de l'anayse
		string nouveauMessage = fenetre->messagesOnglets[onglet.lParam]+"\nRésultats de l'analyse globale - Maladies détectées positivement :\n";
		if (resultats.size() != 0)
		{
			for (unordered_set<string>::iterator i = resultats.begin(); i != resultats.end(); i++)
			{
				nouveauMessage += "- " + *i + "\n";
			}
		}
		else
		{
			nouveauMessage += "Aucune maladie";
		}
		mtxMessages.lock();
		fenetre->messagesOnglets[onglet.lParam] = nouveauMessage;
		
		ongletControlleur->SetCurSel(indexOnglet);

		fenetre->setMessageDisplay(fenetre, onglet.lParam);

		mtxMessages.unlock();

	}
	catch (invalid_argument const & e)
	{
		string nouveauMessage = fenetre->messagesOnglets[onglet.lParam] + "\nProblème d'ouverture du fichier contenant le génome.";
		mtxMessages.lock();
		fenetre->messagesOnglets[onglet.lParam] = nouveauMessage;

		ongletControlleur->SetCurSel(indexOnglet);

		fenetre->setMessageDisplay(fenetre, onglet.lParam);

		mtxMessages.unlock();

	}
	catch (logic_error const & e)
	{
		string nouveauMessage = fenetre->messagesOnglets[onglet.lParam] + "\nRéponse incorrecte provenant du serveur.";
		mtxMessages.lock();
		fenetre->messagesOnglets[onglet.lParam] = nouveauMessage;

		ongletControlleur->SetCurSel(indexOnglet);

		fenetre->setMessageDisplay(fenetre, onglet.lParam);

		mtxMessages.unlock();

	}
	catch (domain_error const & e)
	{
		string nouveauMessage = fenetre->messagesOnglets[onglet.lParam] + "\nRequête incorrecte envoyée au serveur.";
		mtxMessages.lock();
		fenetre->messagesOnglets[onglet.lParam] = nouveauMessage;

		ongletControlleur->SetCurSel(indexOnglet);

		fenetre->setMessageDisplay(fenetre, onglet.lParam);

		mtxMessages.unlock();

	}
	catch (runtime_error const & e)
	{
		string nouveauMessage = fenetre->messagesOnglets[onglet.lParam] + "\nEchec de la communication avec le serveur.";
		mtxMessages.lock();
		fenetre->messagesOnglets[onglet.lParam] = nouveauMessage;
		
		ongletControlleur->SetCurSel(indexOnglet);

		fenetre->setMessageDisplay(fenetre, onglet.lParam);

		mtxMessages.unlock();

	}

	return 0;
}

//Thread charger de réaliser une analyse précise
UINT CDNAnalyzerClientDlg::AnalysePreciseThread(void * window)
{
	//Récupération des paramètres d'analyse
	CDNAnalyzerClientDlg* fenetre = (CDNAnalyzerClientDlg*)window;
	CComboBox * comboServeurs = (CComboBox *)fenetre->GetDlgItem(IDC_COMBO2);
	CComboBox * comboMaladies = (CComboBox *)fenetre->GetDlgItem(IDC_COMBO1);
	int indexServeurCourant = comboServeurs->GetCurSel();
	Serveur serveur = fenetre->serveurs[indexServeurCourant];
	CString choix;

	comboMaladies->GetLBText(comboMaladies->GetCurSel(), choix);
	CT2CA pszConvertedAnsiString(choix);
	std::string maladie(pszConvertedAnsiString);

	CT2CA pathnameAConvertir(fenetre->pathname);
	std::string fichierGenome(pathnameAConvertir);

	//Création d'un nouvel onglet
	CTabCtrl * ongletControlleur = (CTabCtrl *)fenetre->GetDlgItem(IDC_TAB1);
	int indexOnglet = ongletControlleur->GetCurSel();
	TCHAR buf[256] = { 0 };
	TCITEM onglet;
	onglet.pszText = buf;
	onglet.cchTextMax = 256;
	onglet.lParam = 0;
	onglet.mask = TCIF_TEXT | TCIF_PARAM;

	BOOL test = ongletControlleur->GetItem(indexOnglet, &onglet);

	fenetre->setMessageDisplay(fenetre, onglet.lParam);

	try
	{
		//Lancement d'une requête d'analyse précise
		bool resultat = Service::AnalysePrecise(serveur, fichierGenome, maladie);

		//Récupération des résultats
		string nouveauMessage = fenetre->messagesOnglets[onglet.lParam] + "\nRésultat de l'analyse précise - "+maladie+" : ";
		if (resultat)
		{
			nouveauMessage += "test positif\n";
		}
		else
		{
			nouveauMessage += "test négatif\n";
		}
		mtxMessages.lock();
		fenetre->messagesOnglets[onglet.lParam] = nouveauMessage;
		
		ongletControlleur->SetCurSel(indexOnglet);

		fenetre->setMessageDisplay(fenetre, onglet.lParam);

		mtxMessages.unlock();

	}
	catch (invalid_argument const & e)
	{
		string nouveauMessage = fenetre->messagesOnglets[onglet.lParam] + "\nProblème d'ouverture du fichier contenant le génome.";
		mtxMessages.lock();
		fenetre->messagesOnglets[onglet.lParam] = nouveauMessage;

		ongletControlleur->SetCurSel(indexOnglet);

		fenetre->setMessageDisplay(fenetre, onglet.lParam);

		mtxMessages.unlock();

	}
	catch (logic_error const & e)
	{
		string nouveauMessage = fenetre->messagesOnglets[onglet.lParam] + "\nRéponse incorrecte provenant du serveur.";
		mtxMessages.lock();
		fenetre->messagesOnglets[onglet.lParam] = nouveauMessage;

		ongletControlleur->SetCurSel(indexOnglet);

		fenetre->setMessageDisplay(fenetre, onglet.lParam);

		mtxMessages.unlock();

	}
	catch (domain_error const & e)
	{
		string nouveauMessage = fenetre->messagesOnglets[onglet.lParam] + "\nRequête incorrecte envoyée au serveur.";
		mtxMessages.lock();
		fenetre->messagesOnglets[onglet.lParam] = nouveauMessage;

		ongletControlleur->SetCurSel(indexOnglet);

		fenetre->setMessageDisplay(fenetre, onglet.lParam);

		mtxMessages.unlock();

	}
	catch (runtime_error const & e)
	{
		string nouveauMessage = fenetre->messagesOnglets[onglet.lParam] + "\nEchec de la communication avec le serveur.";
		mtxMessages.lock();
		fenetre->messagesOnglets[onglet.lParam] = nouveauMessage;
		
		ongletControlleur->SetCurSel(indexOnglet);

		fenetre->setMessageDisplay(fenetre, onglet.lParam);

		mtxMessages.unlock();

	}

	return 0;
}

//Méthode de création d'un nouvel onglet
void CDNAnalyzerClientDlg::createTab(string title,string content)
{
	CTabCtrl * ongletControlleur = (CTabCtrl *)GetDlgItem(IDC_TAB1);
	TCITEM onglet = { 0 };
	onglet.mask = TCIF_TEXT | TCIF_PARAM;
	int indiceNouvelOnglet = ongletControlleur->GetItemCount();
	string str = to_string(CDNAnalyzerClientDlg::nextTabId)+ title;
	CString titreOnglet = (CString)str.c_str();
	onglet.pszText = (LPTSTR)(LPCTSTR)titreOnglet;
	onglet.lParam = CDNAnalyzerClientDlg::nextTabId++;
	ongletControlleur->InsertItem(indiceNouvelOnglet, &onglet);
	ongletControlleur->SetCurSel(indiceNouvelOnglet);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	mtxMessages.lock();
	messagesOnglets[onglet.lParam] = content;
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
	CTabCtrl * ongletControlleur = (CTabCtrl *)GetDlgItem(IDC_TAB1);
	int indexOnglet = ongletControlleur->GetCurSel();
	if (indexOnglet == 0)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	}
	else
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
	}
	TCHAR buf[256] = { 0 };
	TCITEM onglet;
	onglet.pszText = buf;
	onglet.cchTextMax = 256;
	onglet.lParam = 0;
	onglet.mask = TCIF_TEXT | TCIF_PARAM;

	BOOL test = ongletControlleur->GetItem(indexOnglet,&onglet);

	setMessageDisplay(this, onglet.lParam);
}

//Evènement de suppression de l'onglet sélectionné
void CDNAnalyzerClientDlg::OnBnClickedButton1()
{
	CTabCtrl * ongletControlleur = (CTabCtrl *)GetDlgItem(IDC_TAB1);
	int indexOnglet = ongletControlleur->GetCurSel();
	TCHAR buf[256] = { 0 };
	TCITEM onglet;
	onglet.pszText = buf;
	onglet.cchTextMax = 256;
	onglet.lParam = 0;
	onglet.mask = TCIF_TEXT | TCIF_PARAM;

	BOOL test = ongletControlleur->GetItem(indexOnglet, &onglet);
	mtxThreads.lock();
	HANDLE * ongletASupprimer = threadsOnglets[onglet.lParam];
	TerminateThread(*ongletASupprimer, 1);
	mtxThreads.unlock();
	mtxMessages.lock();
	messagesOnglets[onglet.lParam]="";
	mtxMessages.unlock();
	BOOL suppr = ongletControlleur->DeleteItem(indexOnglet);
	int newIndex = (indexOnglet - 1) < 0 ? indexOnglet + 1 : indexOnglet - 1;
	ongletControlleur->SetCurSel(newIndex);
	if (newIndex == 0)
	{
		GetDlgItem(IDC_BUTTON1)->EnableWindow(false);
	}
	test = ongletControlleur->GetItem(newIndex, &onglet);
	
	setMessageDisplay(this, onglet.lParam);
}
