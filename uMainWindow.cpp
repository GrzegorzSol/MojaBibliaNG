///////////////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008,2009,2010,2011,2012,2013, 2014, 2015, 2016, 2017, 2018, 2019       //
//                                     Grzegorz Sołtysik                                 //
//                                     All rights reserved.                              //
//                                    grzegorzsol@gmail.com                              //
//                                       www.nasz-salem.pl                               //
///////////////////////////////////////////////////////////////////////////////////////////
/*
			Zasady tworzenia nazw dla projektu Moja Biblia NG
1. Nazwy prywatne klasy tworzy się przez dodanie "_" przed nazwą wskaźnika prywatnego.

2. Nazwy modułów są tworzone na zasadzie u + Przeznaczenie + Window, np. Main (z racji że to główne okno modułu) + Window, czyli "uMainWindow.h"

3. Nazwa wskaźników na własne klasy tworzy się z przedrostka "p" + nazwy klasy, lub skrót nazwy klasy,
np. wskaźnik na obiekt klasy ReadBibleTextClass, tworzy się następująco: _(jeśli prywatny)pReadBibleTextClass.

4.Nazwy akcji, czyli składników objektu, klasy TActionManager, tworzy się przez dodanie przedrostka Act_

			Podstawowe założenia dla aplikacji Moja Biblia NG(Next Generations)
1.Ikony na głównym toolbarze są wielkości 32x32 pikseli i bez podpisów.
2.Objektem odpowiadającym za wygląd i obsługę przycisków będzie objekt, klasy TActionToolBar.
3.Jedynym przeznaczeniem klasy TWebBrowser, jest tylko wyświetlanie tekstu biblijnego.
4.Argumenty do metod będą miały przedrostek In
5.Wskaźniki będą miały przedrostek p
6.Metody prywane będą miały przedrostek _
  PRZYKŁAD: pInToSearchGsReadBibleTextClass - wskaźnik, będący argumentem metody
*/
//---------------------------------------------------------------------------
/*
	#if defined(__BORLANDC__) && defined(__clang__) && defined(_WIN32)
		//Your code.
	#endif
	#if defined(__BORLANDC__) && defined(__clang__)
    //Your code.
	#endif
*/
#include <vcl.h>
#pragma hdrstop

#include "uMainWindow.h"
#include "uSearchTextWindow.h"
#include "uLibrary.h"
#include "uSetupsWindow.h"
#include "uSelectVersWindow.h"
#include "uDictGrecPolWindow.h"
#include "uSchemeVersWindow.h"
#include "uViewAllResourcesWindow.h"
#include "uInformationsAppWindow.h"
#include "uMyBibleNGLibrary.h"
#include "uReadUpdateWindow.h"
#include "uChapterEditWindow.h"
#include <System.IOUtils.hpp>
#include <System.Zip.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainBibleWindow *MainBibleWindow;
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
	GsDebugClass::WriteDebug("");
#endif
#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
enum {enImageMainIndex_CloseSheet,     //0.Zamknięcie aktywnej zakładki
			enImageMainIndex_Search,         //1.Wyszukiwanie
			enImageMainIndex_Setups,         //2.Ustawienia
			enImageMainIndex_SaveChapter,    //3.Zapis aktualnego rozdziału
			enImageMainIndex_ChoiceVers,     //4.Wybór i przegląd pojedyńczego wersetu
			enImageMainIndex_InformHelp,     //5.Pomoc i informacje
			enImageMainIndex_CorcondanceGrek,//6.Konkordancja grecka
			enImageSchemeVers,               //7.Projektowanie zależności logicznej między wersetami
			enImageViewAllResources,         //8.Przegląd wszystkich dostępnych zasobów
			enImageResizeWork,               //9.Poszerzanie obszaru tekstu
			enImageFacePage,                 //10.Odnośnik do strony FaceBook
			enImageUpdate,                   //11.Sprawdzanie aktualizacji i ewentualny aktualizacje
			enImageLogoApplication,          //12.Ikona z główną grafiką aplikacji
			enImageEditChapter,              //13.Edycja rozdziału
			enImageMainIndex_Count,
			//Małe ikony
			enImage16_Books=0,               //0.Księgi biblijne
			enImage16_Media,                 //1.Multimedia
			enImage16_Coments,               //2.komentarze
			enImage16_InfoTaskBarButton,     //3.Obraz dla przycisku informacji na taskbarze, o aktualnie wczytanym rozdziele
			enImage16_InfoApplicationTaskBarButton,//4.Obraz dla przycisku informacji o aplikacji
      enImage16_Count,                 //Ilość małych ikon
			//Numer paneli na objekcie klasy TStatusBar
			enPanelMain_InfoText=0, enPanelMain_InfoEx, //Numery paneli
			//menu Tray
			enPMenuTray=0, //Początkowa pozycja w menu Tray
			//Panele objektu MBW_PControlTools, klasy TPageControl
			enPageTools_Books=0, //Zakładka z drzewem ksiąg biblijnych
			enPageTools_Multimedials, //Zakładka z danymi multimedialnymi
      enPageTools_CommentsVers, //Zakładka ze wszystkimi komentarzami
			//Tagi dla kontrolek
			enTagCloseSheet=100,  //Zamknięcie aktywnej zakładki
			enTagSaveChaptToHTML, //Zapis rozdziału z bierzącej zakładki, jako pliku html
			enTagSearchBibleText, //Zaawansowane wyszukiwanie tekstu
			enTagSetupsApplic,    //Wszystkie ustawienia aplikacji.
			enTagSelectVers,       //Wybór pojedyńczego wersetu
			enTagCorcondance,     //Korkondancja grecka
			enTagSchemeVers,      //Projektowanie zależności logicznej między wersetami
			enTagInformations,    //Wyświetlanie informacji
			enTagViewAllResources,//Przegląd wszystkich dostępnych zasobów
			enTagResizeWork,      //Poszerzanie obszaru tekstu
			enTagFacePage,        //Odnośnik do strony facebook
			enTagUpdate,          //Sprawdzanie aktualizacji i ewentualny aktualizacje
			enTagEditChapter,     //Edycja rozdziału
			enTagPageControlBibleText = 200, //Zakładki z tekstem
			enTagPageControlTools,            //Zakładka z narzędziami
			//Numery dla przycisków na taskbarze
			enNumTaskBar_InfoReadChapt = 0,  //Informacja o aktualnie wczytanym rozdziale
			enNumTaskBar_InfoAplic,          //Informacja o aplikacji
			enNumTaskBar_NumberButtons       //Ilość przycisków na taskbarze
		 };
//---------------------------------------------------------------------------
__fastcall TMainBibleWindow::TMainBibleWindow(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI): Konstruktor klasy TMainBibliaWindow
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	#if defined(_DEBUGINFO_) //Ewentualne tworzenie konsoli TMemo dla prywatnego debugera
		GsDebugClass::InitDebug();
	#endif
	#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
		GsDebugClass::WriteDebug(Format("TMainBibleWindow::TMainBibleWindow() - Mutex: \"%s\"", ARRAYOFCONST((GlobalVar::Global_ustrMutexName))));
	#endif
	//----- Sprawdzanie istnienia odpowiednich katalogów
  if(!TDirectory::Exists(GlobalVar::Global_custrPathMultimediaFilesData)) TDirectory::CreateDirectory(GlobalVar::Global_custrPathMultimediaFilesData);
	//----- Tworzenie globalnego wskaźnika, do pliku konfiguracyjnego
	GlobalVar::Global_ConfigFile = new TMemIniFile(GlobalVar::Global_custrGetConfigFile, TEncoding::UTF8);
	if(!GlobalVar::Global_ConfigFile) throw(Exception("Błąd inicjalizacji objektu TMemIniFile"));
	//---
	GlobalVar::Global_SListPathMultiM = new TStringList();  //Ścieżki dostępu do wybranych, przez użytkownika katalogów z multimediami
	if(!GlobalVar::Global_SListPathMultiM) throw(Exception("Błąd inicjalizacji objektu TStringList"));
	//---
	Application->OnException = this->_AppException; //Ustawienie obsługi błędów dla całej aplikacji
	Application->OnHint = this->_AppOnHint;
	Application->OnMessage = this->_AppMessage;
	//Kontrola wymiarów okna
	this->Constraints->MinHeight = 600;
	this->Constraints->MinWidth = 1024;
	if(Screen->DesktopWidth > 1280) this->Width = 1280;
	if(Screen->DesktopHeight > 800) this->Height = 795; else this->Height = 600;
	//---BallonHint
	this->_InitAllTagAndHint();
}
//---------------------------------------------------------------------------
__fastcall TMainBibleWindow::~TMainBibleWindow()
/**
	OPIS METOD(FUNKCJI): Destruktor klasy TMainBibliaWindow
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(GlobalVar::Global_SListPathMultiM) {delete GlobalVar::Global_SListPathMultiM; GlobalVar::Global_SListPathMultiM = 0;}
	#if defined(_DEBUGINFO_) //Konsola debuggera
		#if defined(_FULL_DEBUG_)
			MessageBox(NULL, TEXT("Wstrzymanie zamykania aplikacji, w celu przeglądu komunikatów konsoli!"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
		#endif
		GsDebugClass::CloseDebug();
	#endif
	#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
		GsDebugClass::WriteDebug("TMainBibleWindow::~TMainBibleWindow()");
	#endif
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Metoda tworząca główne okno
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(TFile::Exists(GlobalVar::Global_custrPathBackgroundWindow))
	{
		//--- Wczytanie grafiki podkładu (dopuszczalne jest jej brak)
    //this->ImageBackgroundWindow->Transparent = true;
		this->ImageBackgroundWindow->Picture->LoadFromFile(GlobalVar::Global_custrPathBackgroundWindow);
	}
	//---
	#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
		GsDebugClass::WriteDebug("TMainBibleWindow::FormCreate()");
	#endif
	TThumbBarButton *pNewThumbBarButton;
  //--- Tworzenie głównego objektu z tłmaczeniami, klasy GsReadBibleTextClass.
	//    KLASA MUSI BYĆ ZAINICOWANA METODĄ InitMyBible(), PRZED JAKIM KOLWIEK UŻYWANIEM BIBLIOTEKI GsReadBibleTextClass
	GsReadBibleTextData::InitMyBible(this);
	if(!GsReadBibleTextData::IsInitLibrary) throw(Exception("Błąd inicjalizacji głównej bilioteki do pracy i analizy pisma Świętego!"));
	GsReadBibleTextData::CreateTreeBooks(this->TabSheetBooks, this->PageControlBibleText);
	//---
	UnicodeString ustrVersion = Library::GetInfo();
	GlobalVar::Global_ustrVerAplicMain = ustrVersion;
	#if defined(_WIN64)
		this->Caption = Format("Moja Biblia NG wersja beta x64 (CLang - eksperymentalna) v%s © Grzegorz Sołtysik. [Oświęcim %s]", ARRAYOFCONST((ustrVersion, __DATE__)));
	#else
		this->Caption = Format("Moja Biblia NG wersja beta x32 (CLang) v%s © Grzegorz Sołtysik. [Oświęcim %s]", ARRAYOFCONST((ustrVersion, __DATE__)));
	#endif
	//Zapis pliku tekstowego z wersją
	TFile::WriteAllText(GlobalVar::Global_custrGetVersionUpdate, GlobalVar::Global_ustrVerAplicMain, TEncoding::UTF8);
	//---
	this->STextHeaderListCommentVers->Caption = "Lista wersetów do, których istnieją\n komentarze";
	//--- Tworzenie objektu, klasy listy komentarzy (klasa GsLViewCommentsAllClass) i nagłówka
	this->pGsLViewCommentsAllClass = new GsLViewCommentsAllClass(this->TabSheetAllCommentsVers);
	if(!pGsLViewCommentsAllClass) throw(Exception("Błąd inicjalizacji objektu GsLViewCommentsAllClass"));
	this->pGsLViewCommentsAllClass->Parent = this->TabSheetAllCommentsVers;
	this->pGsLViewCommentsAllClass->Align = alTop;
	this->pGsLViewCommentsAllClass->Height = 360;
	this->pGsLViewCommentsAllClass->OnDblClick = this->_OnDblClick_ListComment;
	//--- Tworzenie listy ulubionych wersetów (klasa GsListBoxFavoritiesClass) i nagłówka
	this->STextHeaderFavorteListVers->Caption = "Lista ulubionych wersetów";
	this->pGsListBoxFavoritiesClass = new GsListBoxFavoritiesClass(this->TabSheetAllCommentsVers);
	if(!this->pGsListBoxFavoritiesClass) throw(Exception("Błąd inicjalizacji objektu GsListBoxFavoritiesClass"));
	this->pGsListBoxFavoritiesClass->Parent = this->TabSheetAllCommentsVers;
	this->pGsListBoxFavoritiesClass->Align = alClient;
	this->pGsListBoxFavoritiesClass->OnDblClick = this->_OnDblClick_ListFavorities;
	//---
	this->TrayIconMain->ShowBalloonHint();
	this->TrayIconMain->Hint = Format("Moja Biblia NG wersja beta v%s © Grzegorz Sołtysik.", ARRAYOFCONST((ustrVersion)));
	this->TrayIconMain->BalloonTitle = this->TrayIconMain->Hint;
	this->TrayIconMain->BalloonHint = "Oprogramowanie do studiowania Pisma Świętego";
  //this->MBW_TrayIconMain->Icon = Application->Icon;
	this->_CreatePopupTrayIcon(); //Tworzenie menu podręcznego dla traya
	//Stworzenie zawartości zakładki z multimediami
	GsPanelMultiM *pGsPanelMultiM = new GsPanelMultiM(this->TabSheetMultimedials, this->PageControlBibleText);
	if(!pGsPanelMultiM) throw(Exception("Błąd inicjalizacji objektu GsPanelMultiM"));
	pGsPanelMultiM->Parent = this->TabSheetMultimedials;
	pGsPanelMultiM->Align = alClient;
	this->PageControlTools->ActivePage = this->TabSheetBooks;  //Domyślnie aktywna zakładka
	static UnicodeString ustrHintTBarButtons[] = {"Informacje o aktualnie wczytanym rozdziele", "Informacje o aplikacji"};
	//---
	this->Width = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_AppWidth, this->Constraints->MinWidth);
	this->Height = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_AppHeight, this->Constraints->MinHeight);

	this->TaskbarMain->PreviewClipRegion->Left = 0;
	this->TaskbarMain->PreviewClipRegion->Top = 0;
	this->TaskbarMain->PreviewClipRegion->Width = this->Width;
	this->TaskbarMain->PreviewClipRegion->Height = this->Height;
	//---
	if((enNumTaskBar_NumberButtons == this->ActionManagerOther->ActionCount) && (enNumTaskBar_NumberButtons == ARRAYSIZE(ustrHintTBarButtons)))
	{
    #if defined(_DEBUGINFO_)
			//GsDebugClass::WriteDebug(Format("this->ActionManagerOther->Count: %d", ARRAYOFCONST((this->ActionManagerOther->ActionCount))));
		#endif
		for(int iButton=0; iButton<enNumTaskBar_NumberButtons; iButton++)
		{
			pNewThumbBarButton = this->TaskbarMain->TaskBarButtons->Add();
			if(pNewThumbBarButton)
			{
				//Dodanie akcji do przycisku na taskbarze
				pNewThumbBarButton->Action = this->ActionManagerOther->Actions[iButton];
				pNewThumbBarButton->Hint = ustrHintTBarButtons[iButton];
			}
		}
		#if defined(_DEBUGINFO_)
			//GsDebugClass::WriteDebug(Format("this->TaskbarMain->TaskBarButtons->Count: %d", ARRAYOFCONST((this->TaskbarMain->TaskBarButtons->Count))));
		#endif
	}

	this->TaskbarMain->ApplyChanges();
	//ustawienie wartości domyślnej dla szerokości, do której zostanie zwinięty objekt, klasy TSplitView.
	//Dokładna szerokość określana jest w metodzie TMainBibleWindow::MBW_PageControlsAllDrawTab() tylko jednokrotnie!
	this->SplitViewMain->CompactWidth = 0;
	//Szerokość lewego kontenera przycisków
	this->ActionToolBarMain->Width = this->Width / 2;
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::FormActivate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Okno staje się aktywnym
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	int iBook, iChapt;
	//---
	#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
		GsDebugClass::WriteDebug("TMainBibleWindow::FormActivate()");
	#endif
	//Sprawdzanie aktualizacji podczas startu aplikacji
	if(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsAutoFindUpdate, true))
	{
		this->Act_UpdateExecute(this->Act_Update);
	}
	//---
	if(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsLoadBooksOnInit, true))
	//Odczyt poprzednio otwartych ksiąg
	{
		//Odczyt otwartych ksiąg podczas ostatniego zamknięcia aplikacji
		THashedStringList *pHSListOpenBooksInExit = new THashedStringList();
		if(!pHSListOpenBooksInExit) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
		pHSListOpenBooksInExit->CommaText = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_LoadBooksOnExit, "");
		#if defined(_DEBUGINFO_)
			GsDebugClass::WriteDebug(Format("pHSListOpenBooksInExit->Count: %u", ARRAYOFCONST((pHSListOpenBooksInExit->Count))));
		#endif
		for(int i=0; i<pHSListOpenBooksInExit->Count; i++)
		{
			iBook = pHSListOpenBooksInExit->Strings[i].SubString(1, 3).ToIntDef(1);
			iChapt = pHSListOpenBooksInExit->Strings[i].SubString(4, 3).ToIntDef(1);
			GsReadBibleTextData::OpenSelectBookAndChapter(iBook, iChapt);
			#if defined(_DEBUGINFO_)
				GsDebugClass::WriteDebug(Format("%u - pHSListOpenBooksInExit->Strings[i] = %s; %u:%u", ARRAYOFCONST((i, pHSListOpenBooksInExit->Strings[i], iBook, iChapt))));
			#endif
		}

		delete pHSListOpenBooksInExit;// pHSListOpenBooksInExit = 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::FormCloseQuery(TObject *Sender, bool &CanClose)
/**
	OPIS METOD(FUNKCJI): Metoda tworząca główne okno
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
		GsDebugClass::WriteDebug("TMainBibleWindow::FormCloseQuery()");
	#endif
	if(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsRequestEnd, true) &&
		 GlobalVar::iReturnUpdate != 1)
	{
		TTaskDialog *pTaskDialog = new TTaskDialog(this);
		if(!pTaskDialog) throw(Exception("Błąd inicjalizacji objektu TTaskDialog"));
    #if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
			GsDebugClass::WriteDebug("TMainBibleWindow::FormCloseQuery()-if(!pTaskDialog)");
		#endif
		pTaskDialog->Caption = "Pytanie aplikacji";
		pTaskDialog->Title = "Czy rzeczywiście chcesz opuścić apilkacje?";

		pTaskDialog->ExpandedText = "Naciśnięcie przycisku OK, spowoduje opuszczenie aplikacji. To pytania można wyłączyć w jej ustawieniach, wtedy aplikacja zostanie zaknięta bez pytania!";
		pTaskDialog->MainIcon = tdiWarning;
		pTaskDialog->DefaultButton = tcbNo;
		pTaskDialog->CommonButtons = TTaskDialogCommonButtons() << tcbYes << tcbNo;
    #if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
			GsDebugClass::WriteDebug("TMainBibleWindow::FormCloseQuery()-pTaskDialog->CommonButtons");
		#endif
		pTaskDialog->ModalResult = mrNo;
		pTaskDialog->Flags = TTaskDialogFlags() << tfUseHiconMain << tfExpandedByDefault << tfPositionRelativeToWindow;
    #if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
			GsDebugClass::WriteDebug("TMainBibleWindow::FormCloseQuery()-pTaskDialog->Flags");
		#endif
		if(this->ImageListMainActive) this->ImageListMainActive->GetIcon(enImageLogoApplication, pTaskDialog->CustomMainIcon);
    #if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
			GsDebugClass::WriteDebug("TMainBibleWindow::FormCloseQuery()-if(this->ImageListMainActive)");
		#endif
		if(pTaskDialog->Execute())
		{
			if(pTaskDialog->ModalResult == mrYes) CanClose = true; else CanClose = false;
			#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
				GsDebugClass::WriteDebug("TMainBibleWindow::FormCloseQuery()-if(pTaskDialog->ModalResult == mrYes)");
			#endif
		}
		if(pTaskDialog) {delete pTaskDialog;}
    #if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
			GsDebugClass::WriteDebug("TMainBibleWindow::FormCloseQuery()-if(pTaskDialog))");
		#endif
	}
	else CanClose = true;
	#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
		GsDebugClass::WriteDebug("TMainBibleWindow::FormCloseQuery()-Koniec");
	#endif
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::FormClose(TObject *Sender, TCloseAction &Action)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
		GsDebugClass::WriteDebug("TMainBibleWindow::FormClose()");
	#endif
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_AppWidth, this->Width);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_AppHeight, this->Height);
	//---
	if(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsLoadBooksOnInit, true))
	//Zapis listy otwartych ksiąg i rozdziałów w momencie zamknięcia aplikacji
	{
		THashedStringList *pHSListOpenBooksInExit = new THashedStringList();
		if(!pHSListOpenBooksInExit) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
		UnicodeString ustrAdress;
		for(int i=0; i<this->PageControlBibleText->PageCount; i++)
		{
			GsTabSheetClass *pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(this->PageControlBibleText->Pages[i]);
			if (pGsTabSheetClass)
			{
				GsReadBibleTextData::GetAdressFromId(ustrAdress, pGsTabSheetClass->_ShucIndexBook+1, pGsTabSheetClass->_ShucIndexChapt+1);
				#if defined(_DEBUGINFO_)
					GsDebugClass::WriteDebug(Format("ustrAdress: %s", ARRAYOFCONST((ustrAdress))));
				#endif
				pHSListOpenBooksInExit->Add(ustrAdress);
			}
		}
		#if defined(_DEBUGINFO_)
			GsDebugClass::WriteDebug(Format("pHSListOpenBooksInExit->CommaText: %s", ARRAYOFCONST((pHSListOpenBooksInExit->CommaText))));
		#endif
		GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_LoadBooksOnExit, pHSListOpenBooksInExit->CommaText);
		delete pHSListOpenBooksInExit;// pHSListOpenBooksInExit = 0;
	}
	//--- Zamknięcie klasy głównej do analizy Pisma
	GsReadBibleTextData::CloseMyBible();
	//Zwolnienie pamięci na konfiguracje aplikacji
	if(GlobalVar::Global_ConfigFile)
	{
		GlobalVar::Global_ConfigFile->UpdateFile();	//Zrzut pliku ini z pamięci, do pliku ini
		delete GlobalVar::Global_ConfigFile;
		GlobalVar::Global_ConfigFile = 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::FormDestroy(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Metoda likwidująca główne okno
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
		GsDebugClass::WriteDebug("TMainBibleWindow::FormDestroy()");
	#endif
	//OleUninitialize();
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::FormResize(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Metoda wywoływana podczas zmiany rozmiaru okna
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

	#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
		GsDebugClass::WriteDebug("TMainBibleWindow::FormResize()");
	#endif
	//Główna część panelu zajmuje 75% szerokości oka
	this->StatusBarMain->Panels->Items[enPanelMain_InfoText]->Width = (int)(0.75 * this->Width);
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::_AppException(TObject *Sender, Exception *pException)
/**
	OPIS METOD(FUNKCJI): Obsługa błędów całej aplikacji
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	Application->ShowException(pException);
	Application->Terminate(); //Zamknięcie aplikacji
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::_InitAllTagAndHint()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->Act_CloseSheetActive->Tag = enTagCloseSheet;  //Zamknięcie aktywnej zakładki
	this->Act_CloseSheetActive->Hint = Format("Zamknięcie zakładki|Zamknięcie aktualnie aktywnej zakładki z tekstem|%u", ARRAYOFCONST((this->Act_CloseSheetActive->ImageIndex)));
	this->Act_SaveChaptToHTML->Tag = enTagSaveChaptToHTML; //Zapis rozdziału z bierzącej zakładki, jako pliku html
	this->Act_SaveChaptToHTML->Hint = Format("Zapis do pliku|Zapis zawartości aktualnej zakładki, do pliku w formacie html.|%u", ARRAYOFCONST((this->Act_SaveChaptToHTML->ImageIndex)));
	this->Act_SearchBibleText->Tag  = enTagSearchBibleText; //Zaawansowane wyszukiwanie tekstu
	this->Act_SearchBibleText->Hint = Format("Wyszukiwanie|Otwiera okno do wyszukiwanie wyrażeń i fraz w tekście biblijnym.|%u", ARRAYOFCONST((this->Act_SearchBibleText->ImageIndex)));
	this->Act_SetupsApplic->Tag  = enTagSetupsApplic;    //Wszystkie ustawienia aplikacji.
	this->Act_SetupsApplic->Hint = Format("Ustawienia|Wszystkie ustawienia aplikacji.|%u", ARRAYOFCONST((this->Act_SetupsApplic->ImageIndex)));
	this->Act_SelectVers->Tag = enTagSelectVers;       //Wybór pojedyńczego wersetu
	this->Act_SelectVers->Hint = Format("Wybór wersetu|Umożliwia wybór pojedyńczego wersetu.|%u", ARRAYOFCONST((this->Act_SelectVers->ImageIndex)));
	this->Act_CorcordanceDictionaryGrec->Tag = enTagCorcondance;
	this->Act_CorcordanceDictionaryGrec->Hint = Format("Korkondancja grecka|Korkondancja grecka Nowego Testament, z kodami Stronga.|%u", ARRAYOFCONST((this->Act_CorcordanceDictionaryGrec->ImageIndex)));
	this->Act_ProjectSchemeVers->Tag = enTagSchemeVers;
	this->Act_ProjectSchemeVers->Hint = Format("Powiązania między wersetami|Projektowanie logicznych powiązań między wersetami.|%u", ARRAYOFCONST((this->Act_ProjectSchemeVers->ImageIndex)));
	this->Act_Infomations->Tag = enTagInformations;
	this->Act_Infomations->Hint = Format("Informacje o aplikacji|Wyświetlanie informacji o aplikacjii.|%u", ARRAYOFCONST((this->Act_Infomations->ImageIndex)));
	this->Act_ViewAllResources->Tag = enTagViewAllResources;
	this->Act_ViewAllResources->Hint = Format("Przegląd zasobów|Wyświetlanie okna z lista wszystkich, dostępnych zasobów aplikacji.|%u", ARRAYOFCONST((this->Act_ViewAllResources->ImageIndex)));
	this->Act_ResizeWork->Tag = enTagResizeWork;
	this->Act_ResizeWork->Hint = Format("Poszerzenie obszaru tekstu.|Przełącznik powodujący poszerzenie obszaru tekstu biblijnego, przez schowanie zakładek.|%u", ARRAYOFCONST((this->Act_ResizeWork->ImageIndex)));
	this->Act_FacePage->Tag = enTagFacePage;
	this->Act_FacePage->Hint = Format("Otwarcie strony na Facebooku.|Otwarcie strony aplikacji na Facebooku, w domyślnej przeglądarce.|%u", ARRAYOFCONST((this->Act_FacePage->ImageIndex)));
	this->Act_Update->Tag = enTagUpdate;
	this->Act_Update->Hint = Format("Otwarcie okna sprawdzania i akualizacji.|Otwarcie okna, do sprawdzania wersji na serwerze i ewentualnej aktualizacji.|%u", ARRAYOFCONST((this->Act_Update->ImageIndex)));
	this->Act_EditChapter->Tag = enTagEditChapter;
	this->Act_EditChapter->Hint = Format("Otwarcie okna do edycji rozdziału|Otwarcie okna, do edycji aktalnie aktywnego razdziału.|%u", ARRAYOFCONST((this->Act_EditChapter->ImageIndex)));
	//---
	this->PageControlBibleText->Tag = enTagPageControlBibleText; //Zakładki z tekstem
	this->PageControlTools->Tag = enTagPageControlTools;            //Zakładka z narzędziami

	//this->MBW_HdrControlBooks->Hint = "Nagłówek drzewa ksiąg biblijnych|Nagłówek drzewa ksiąg biblijnych, pokazujący nazwy poszczególnych informacji o księgach biblijnych";
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::TrayIconMainBalloonClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Kliknięto na objekt, klassy BallonHint, objektu klasy TTrayIcon
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TTrayIcon *pTrayIcon = dynamic_cast<TTrayIcon *>(Sender);
	if(!pTrayIcon) return;
	//---
	//MessageBox(NULL, L"TMainBibleWindow::MBW_TrayIconMainBalloonClick", TEXT("Informacja aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::_AppOnHint(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TApplication *pApplication = dynamic_cast<TApplication *>(Sender);
	if(!pApplication) return;
	//---
	this->StatusBarMain->Panels->Items[enPanelMain_InfoText]->Text = GetShortHint(Application->Hint);//this->XMBW_BalloonHintMain->Description;//
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::_CreatePopupTrayIcon()
/**
	OPIS METOD(FUNKCJI): Tworzenie menu podręcznego dla traya
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TImageList *pImageList = GsReadBibleTextData::GetImageList(); //Wyłuskanie listy ikon
	if(!pImageList) throw(Exception("Błąd wyłuskania listy grafik"));
	this->PMenuTray->Images = pImageList;
	//---
	for(unsigned int i=0; i<GsReadBibleTextData::GsNumberBooks; i++)
	{
		TMenuItem *NewItem = new TMenuItem(this->PMenuTray);
		if(!NewItem) throw(Exception("Błąd inicjalizacji objektu TMenuItem"));
		this->PMenuTray->Items->Add(NewItem);
		NewItem->Caption = GsReadBibleTextData::GsInfoAllBooks[i].FullNameBook;
		NewItem->OnClick = this->_OnClick_PMenuTray;
		NewItem->Tag = enPMenuTray + i;
		NewItem->ImageIndex = enImageIndex_Book;
  }
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::_OnClick_PMenuTray(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Wybrana została pozycja z popupmenu, trayicon
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TMenuItem *pMItem = dynamic_cast<TMenuItem *>(Sender);
	if(!pMItem) return;
	//---
	GsReadBibleTextData::LoadFirstChapt(pMItem->Tag);
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::_OnDblClick_ListComment(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsLViewCommentsAllClass *pGsLViewCommentsAllClass = dynamic_cast<GsLViewCommentsAllClass *>(Sender);
	if(!pGsLViewCommentsAllClass) return;
	//---
	ListComments *pListComments = this->pGsLViewCommentsAllClass->GetSelectComent(pGsLViewCommentsAllClass->ItemIndex);
	//return;
	TSelectVersWindow *pSelectVersWindow = new TSelectVersWindow(this, pListComments->LC_ucBook, pListComments->LC_ucChapt - 1, pListComments->LC_ucVers, true);
	if(!pSelectVersWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TSelectVersWindow"));
	pSelectVersWindow->ShowModal();
	//Odświerzemie listy wersetów, po ewemtualnych zmianach w edytorze wersetów.
	this->pGsLViewCommentsAllClass->ReloadAllVersComments(false); //Ponowne wszytanie zawartości katalogu z plikami komentarzy
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::_OnDblClick_ListFavorities(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsListBoxFavoritiesClass *pGsListBoxFavoritiesClass = dynamic_cast<GsListBoxFavoritiesClass *>(Sender);
	if(!pGsListBoxFavoritiesClass) return;
	//---
	UnicodeString AdressString = pGsListBoxFavoritiesClass->Items->Strings[pGsListBoxFavoritiesClass->ItemIndex]; //Odczytanie zawartości pozycji
	unsigned char ucBook = AdressString.SubString(1, 3).ToInt() - 1,//Księgi są numerowane w pliku z tłumaczeniem od 1, a teblice od 0.
								ucChapt = AdressString.SubString(4, 3).ToInt(),
								ucVers = AdressString.SubString(7, 3).ToIntDef(0);
  TSelectVersWindow *pSelectVersWindow = new TSelectVersWindow(this, ucBook, ucChapt - 1, ucVers, true);
	if(!pSelectVersWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TSelectVersWindow"));
	pSelectVersWindow->ShowModal();
  //Odświerzemie listy wersetów, po ewemtualnych zmianach w edytorze wersetów.
	pGsLViewCommentsAllClass->ReloadAllVersComments(false);
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_CloseSheetActiveExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Akcja zamknięcia aktywnej zakładki z tekstem.
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
		GsDebugClass::WriteDebug("TMainBibleWindow::Act_CloseSheetActiveExecute()");
	#endif
	if((this->PageControlBibleText->PageCount == 0)  || (this->PageControlBibleText->ActivePageIndex == -1)) return;
	//---
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
		GsDebugClass::WriteDebug("TMainBibleWindow::Act_CloseSheetActiveExecute()-TAction *pAction");
	#endif
	//---
	TTabSheet* pActiveSheet = this->PageControlBibleText->ActivePage;
	#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
		GsDebugClass::WriteDebug("TMainBibleWindow::Act_CloseSheetActiveExecute()-TTabSheet* pActiveSheet");
	#endif
	if(pActiveSheet)
	{
		if(pActiveSheet->ClassNameIs("GsTabSheetSelectVersClass")) GsReadBibleTextData::GsSheetListVers = 0; //Jeśli to zakładka z listą wybranych wersetów,
																																																				 //globalny wskaźnik na zakładkę zostanie wyzerowany
		#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
			GsDebugClass::WriteDebug("TMainBibleWindow::Act_CloseSheetActiveExecute()-pActiveSheet->ClassNameIs");
		#endif
		delete pActiveSheet;
		#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
			GsDebugClass::WriteDebug("TMainBibleWindow::Act_CloseSheetActiveExecute()-delete pActiveSheet");
		#endif
		pAction->Enabled = (this->PageControlBibleText->PageCount > 0);
		this->Act_EditChapter->Enabled = pAction->Enabled;
		#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
			GsDebugClass::WriteDebug("TMainBibleWindow::Act_CloseSheetActiveExecute()-pAction->Enabled");
		#endif
		//---
		if((this->PageControlBibleText->PageCount == 0) && (this->PageControlTools->ActivePageIndex == enPageTools_Books)) //[02-11-2019]
		//Otwieranie zakładki z wyborem ksiąg, w wypadku, gdy żadna księga nie jest wczytana, i aktywną zakładką jest zakładka wyboru ksiąg
		{
			#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
				GsDebugClass::WriteDebug("TMainBibleWindow::Act_CloseSheetActiveExecute()-if((this->PageControlBibleText->PageCount == 0)");
			#endif
			this->Act_ResizeWork->Checked = false;
			this->Act_ResizeWorkExecute(this->Act_ResizeWork);
		}
		if(this->PageControlBibleText->PageCount == 0)
		{
			this->PageControlBibleText->Visible = false; //01-02-2020
      #if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
				GsDebugClass::WriteDebug("this->PageControlBibleText->Visible = false)");
			#endif
		}
	}
	#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
		GsDebugClass::WriteDebug("TMainBibleWindow::Act_CloseSheetActiveExecute()-End");
	#endif
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_SaveChaptToHTMLExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Akcja zapisu rozdziału, z aktywnej zakładki, jako pliku html.
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	GsReadBibleTextData::WriteCurrentSheetText();
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_SearchBibleTextExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Akcja , która otwiera okno do zaawansowanego wyszukiwania tekstu.
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	TSearchTextWindow *pTSearchTextWindow = new TSearchTextWindow(this);
	if(!pTSearchTextWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TSearchTextWindow"));
	pTSearchTextWindow->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::StatusBarMainDrawPanel(TStatusBar *StatusBar,
					TStatusPanel *Panel, const TRect &Rect)
/**
	OPIS METOD(FUNKCJI): Własna metoda obsługi status panel.
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCanvas *pCanvas = StatusBar->Canvas;
	switch(Panel->Index)
	{
		case enPanelMain_InfoText: //Podstawowy tekst podpowiedzi
      pCanvas->Font->Style = TFontStyles() << fsBold;
			pCanvas->Font->Color = clRed;
			break;
		case enPanelMain_InfoEx:
      pCanvas->Font->Color = this->Font->Color;
      break;
	}
	pCanvas->TextOut(Rect.left, Rect.top, Panel->Text);
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_SetupsApplicExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Akcja , która otwiera okno do wszystkich ustawień aplikacji.
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	TSetupsWindow *pSetupsWindow = new TSetupsWindow(this);
	if(!pSetupsWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TSetupsWindow"));
	pSetupsWindow->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_SelectVersExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Akcja, która otwiera okno do wybrania pojedyńczego wersetu.
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	TSelectVersWindow *pSelectVersWindow;//=0;
	GsTabSheetClass *pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(this->PageControlBibleText->ActivePage);
	if(!pGsTabSheetClass) {pSelectVersWindow = new TSelectVersWindow(this);} //Brak zakładki z załadowaną księgą i rozdziałem
	//Jest zakładka z załadowaną księgą i rozdziałem, więc domyślnie startowym tekstem będzie pierwszy werset z załadowanej księgi i rozdziały,
	//w aktualnej zakładce, w oknie głównym.
	else {pSelectVersWindow = new TSelectVersWindow(this, pGsTabSheetClass->_ShucIndexBook, pGsTabSheetClass->_ShucIndexChapt);}
	//---
	if(!pSelectVersWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TSelectVersWindow"));
	pSelectVersWindow->ShowModal(); //Musi być okno modalne!
  //Odświerzemie listy wersetów, po ewemtualnych zmianach w edytorze wersetów.
	this->pGsLViewCommentsAllClass->ReloadAllVersComments(false);
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_CorcordanceDictionaryGrecExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Akcja otwierająca okno konkordancji grecko-polskiej i słownika
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	TDictGrecPolWindow *pTDictGrecPolWindow = new TDictGrecPolWindow(this);
	if(!pTDictGrecPolWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TDictGrecPolWindow"));
  pTDictGrecPolWindow->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_ProjectSchemeVersExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Akcja projektowania powiązań między wersetami
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	TSchemeVersWindow *pTSchemeVersWindow = new TSchemeVersWindow(this);
	if(!pTSchemeVersWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TSchemeVersWindow"));
	pTSchemeVersWindow->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_InfomationsExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Akcja wyświetlająca okno z informacjami o aplikacji (winietę)
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	static bool sbIsOpenInfo; //Informacja że okno już otwarto
	if(sbIsOpenInfo) return;
  //---
	TInformationsAppWindow *pTInformationsAppWindow = new TInformationsAppWindow(this);
	if(!pTInformationsAppWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TInformationsAppWindow"));
	sbIsOpenInfo = true;
	pTInformationsAppWindow->ShowModal();
	sbIsOpenInfo = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_ViewAllResourcesExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Akcja wyświetlająca okno z listą wszystkich dostępnych zasobów aplikacji
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	TViewAllResourcesWindow *pViewAllResourcesWindow = new TViewAllResourcesWindow(this);
	if(!pViewAllResourcesWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TViewAllResourcesWindow"));
	pViewAllResourcesWindow->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_ResizeWorkExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Akcja poszerzajaca obszar tekstu. Przełącznik
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	//this->PageControlTools->Visible = !pAction->Checked;
	this->SplitViewMain->Opened = !pAction->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_OtherInfoTaskbarButtonExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Akcja umieszczona w TaskBarze, informująca o aktualnie wczytanym rozdziale
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
  static bool sbIsOpenInfo; //Informacja że okno już otwarto
	if(sbIsOpenInfo) return;
	//---
	if(this->PageControlBibleText->PageCount > 0)
  //Sprawdzenie czy istnieją zakładki
	{
		UnicodeString ustrMsg;
    ustrMsg = this->PageControlBibleText->ActivePage->Caption;
		sbIsOpenInfo = true;
		MessageBox(NULL, ustrMsg.c_str(), TEXT("Informacja o aktualnie przeglądanym rozdziale"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
		sbIsOpenInfo = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::MBW_PageControlAllChange(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Metoda wywoływana podczas zmiany zakłedki, we wszystkich objektach klasy TPageControl
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPageControl *pPageControl = dynamic_cast<TPageControl *>(Sender);
	if(!pPageControl) return;
	//---
	switch(pPageControl->Tag)
	{
		case enTagPageControlBibleText: //Zakładki z tekstem
		{
			#if defined(_DEBUGINFO_)
				GsDebugClass::WriteDebug("Zakładki z tekstem");
			#endif
			//TTabSheet *pTabSheet = pPageControl->ActivePage;
			GsTabSheetClass *pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(pPageControl->ActivePage);
			if(!pGsTabSheetClass)
			//Jeśli to nie jest zakładka z wybranym rozdziałem z wybranej ksiegi, to wyzeruje się wskaźnik na taskbarze
			//i metoda zostanie opuszczona
			{
				this->TaskbarMain->ProgressValue = 0;
				return;
			}
			//Wyłuskanie wskaźnika do TProgressBaru, aktualnej zakładki
			TProgressBar *pProgressBar = GsReadBibleTextData::GetCurrentNamberChaptOnSheet();
			if(!pProgressBar) return;
			//---
			this->TaskbarMain->ProgressMaxValue = pProgressBar->Max;
			this->TaskbarMain->ProgressValue = pProgressBar->Position;
		}
		break;
		//---
		case enTagPageControlTools:            //Zakładka z narzędziami (wybór ksiąg, zasoby, wersety)
		{
      #if defined(_DEBUGINFO_)
				GsDebugClass::WriteDebug("Zakładka z narzędziami (wybór ksiąg, zasoby, wersety)");
			#endif
		}
    break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::MBW_SplitTreeTextCanResize(TObject *Sender,
					int &NewSize, bool &Accept)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TSplitter *pSplitter = dynamic_cast<TSplitter *>(Sender);
	if(!pSplitter) return;
	//---
	const int ciMaxSize = 580,
						ciMinSize = 280;
	//--- Nie możesz więcej przesunąć splittera niż, na szerokość ciMaxSize pikseli
	if((NewSize > ciMaxSize) || (NewSize < ciMinSize)) Accept = false;//NewSize = sciMaxSize;
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::MBW_PageControlsAllDrawTab(TCustomTabControl *Control,
					int TabIndex, const TRect &Rect, bool Active)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPageControl *pPControl = dynamic_cast<TPageControl *>(Control);
	if(!pPControl) return;
	//-----
	TTabSheet *pActSheet = dynamic_cast<TTabSheet *>(pPControl->Pages[TabIndex]);	//Aktualna zakładka
	if(!pActSheet) return;
	//---
	TRect MyRect(Rect);
	switch(pPControl->Tag)
	{
		case enTagPageControlBibleText: //Zakładki z tekstem
		{
			if(Active)
			{
				pPControl->Canvas->Font->Color = clYellow;
				pPControl->Canvas->Brush->Color = clBlue;
			}
			pPControl->Canvas->FillRect(Rect);
			pPControl->Images->Draw(pPControl->Canvas, Rect.Left + 4, (Rect.Top + ((Rect.Bottom - Rect.Top) / 2)) - (pPControl->Images->Height / 2) + 2, pActSheet->ImageIndex);
			MyRect.Inflate(-pPControl->Images->Width - 4, 0);
			DrawText(pPControl->Canvas->Handle, pActSheet->Caption.c_str(), -1, &MyRect, DT_VCENTER | DT_SINGLELINE);
		}
		break;
    //---
		case enTagPageControlTools:            //Zakładka z narzędziami (wybór ksiąg, zasoby, wersety)
		{
			if(Active)
			{
				pPControl->Canvas->Font->Color = clBlack;
				pPControl->Canvas->Brush->Color = clWebDarkOrange;
				//Ustwienie szerokosci "ucha" aktywnej zakładki, do jakiej bedzie się zwijać objekt, klasy TSplitView. Szerokość ustawia się tylko raz, gdy jest ustawiona na
        //domyślną wartość równą zero, później już nie jest modyfikowana - 06-10-2019
				if(this->SplitViewMain->CompactWidth == 0) this->SplitViewMain->CompactWidth = Rect.GetWidth();
			}
			pPControl->Canvas->FillRect(Rect);
			pPControl->Canvas->Font->Orientation = 900;
			MyRect.Inflate(-4, 0, 0, -10);
			DrawText(pPControl->Canvas->Handle, pActSheet->Caption.c_str(), -1, &MyRect, DT_BOTTOM | DT_SINGLELINE);
			pPControl->Images->Draw(pPControl->Canvas, Rect.Left + ((Rect.Right - Rect.Left) / 2 - (pPControl->Images->Width / 2)),
			                                           Rect.Bottom - pPControl->Images->Height - 4, pActSheet->ImageIndex);
		}
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_FacePageExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Akcja otwiera w domyślnej przeglądarce stronę facebookową
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	ShellExecute(this->Handle, NULL , TEXT("https://www.facebook.com/MojaBiblia/"), NULL, NULL, SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_UpdateExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Akcja otwiera okno do sprawdzania na serwerze i ewentualną aktualizacje
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
  //Uzyskanie ścieżki dostepu do katalogu Temp
	TCHAR pathTemp[MAX_PATH];
	GetTempPath(MAX_PATH, pathTemp);

	GlobalVar::Global_custrLocalVersionFile = TPath::Combine(pathTemp, GlobalVar::Global_custrNameIVerFile); //Pobrany plik wersjji - pathTemp + GlobalVar::Global_custrNameIVerFile,
	GlobalVar::Global_custrLocalApplicFile = TPath::Combine(pathTemp, TPath::GetFileNameWithoutExtension(Application->ExeName)) + ".zip"; //Pobrane archiwum poprawki - ...Temp\Nazwa_aplikacji.exe - Plik
	//---
	TReadUpdateWindow *pReadUpdateWindow = new TReadUpdateWindow(this);
	if(!pReadUpdateWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TReadUpdateWindow"));
	pReadUpdateWindow->ShowModal();
	if(GlobalVar::iReturnUpdate != 1) return;

	UnicodeString ustrPathDirExtract;
	//Rozpakowanie archiwum aktualizacyjnego
	if(TFile::Exists(GlobalVar::Global_custrLocalApplicFile))
	//Jeśli istnieje pobrane archiwum
	{
		ustrPathDirExtract = TPath::GetDirectoryName(GlobalVar::Global_custrLocalApplicFile); //Katalog na pliki rozpakowane z archiwum
		#if defined(_DEBUGINFO_)
			GsDebugClass::WriteDebug(Format("GlobalVar::Global_custrLocalApplicFile: %s, ustrPathDirExtract: %s", ARRAYOFCONST((GlobalVar::Global_custrLocalApplicFile, ustrPathDirExtract))));
		#endif

		TZipFile *pZipFile = new TZipFile();
		pZipFile->ExtractZipFile(GlobalVar::Global_custrLocalApplicFile, ustrPathDirExtract);

		UnicodeString ustrPathWinMBUpdate = TPath::Combine(pathTemp, GlobalVar::Global_ustrNameDirUpdate);
		ustrPathWinMBUpdate = TPath::Combine(ustrPathWinMBUpdate, GlobalVar::Global_custrNameUpd);
		#if defined(_DEBUGINFO_)
			GsDebugClass::WriteDebug(Format("ustrPathWinMBUpdate: %s", ARRAYOFCONST((ustrPathWinMBUpdate))));
			GsDebugClass::WriteDebug(Format("GlobalVar::Global_ustrPathApplicUpdate: %s", ARRAYOFCONST((GlobalVar::Global_ustrPathApplicUpdate))));
		#endif

		TFile::Copy(ustrPathWinMBUpdate, GlobalVar::Global_ustrPathApplicUpdate, true); //Kopiowanie aplikacji aktualizacyjnej do katalogu z główną aplikacją

		//TFile::Delete(ustrPathWinMBUpdate); //Kasowanie programy aktualizacyjnego z katalogu temp
		//TFile::Delete(GlobalVar::Global_custrLocalVersionFile); //Kasowanie pliku wersji
		//TFile::Delete(GlobalVar::Global_custrLocalApplicFile);  //Kasowanie archiwum z łatkami z katalogu temp

		//Kasowanie niepotrzebnych plików
		delete pZipFile;
		if(TFile::Exists(GlobalVar::Global_ustrPathApplicUpdate))
		//Jesli istnieje aplikacja do kopiowania nowej wersji na starą
		{
			this->Close();
			ShellExecute(NULL, NULL , GlobalVar::Global_ustrPathApplicUpdate.c_str(), NULL, NULL, SW_SHOWNORMAL);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::SplitViewMainOpened(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Objekt, klasy TSplitView został otwarty
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TSplitView *pSplitView = dynamic_cast<TSplitView *>(Sender);
	if(!pSplitView) return;
	//---
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::PageControlToolsChanging(TObject *Sender,
					bool &AllowChange)
/**
	OPIS METOD(FUNKCJI): Zezwolenie na zmianę zakładki w zakładkach z narzędziami
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TPageControl *pPageControl = dynamic_cast<TPageControl *>(Sender);
	if(!pPageControl) return;
	//---
	if(!this->SplitViewMain->Opened) AllowChange = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::PageControlBibleTextEnter(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Zamknięcie objektu klasy, TSplitView, po wybraniu księgi, lub rozdziału
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPageControl *pPageControl = dynamic_cast<TPageControl *>(Sender);
	if(!pPageControl) return;
	//---
	if(pPageControl->PageCount > 0)
	{
		this->Act_ResizeWork->Checked = true;
		this->Act_ResizeWorkExecute(this->Act_ResizeWork);
		this->Act_CloseSheetActive->Enabled = true;
		this->Act_EditChapter->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::PageControlToolsMouseEnter(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Myszka nad objektem TPageControl //[03-11-2019]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPageControl *pPageControl = dynamic_cast<TPageControl *>(Sender);
	if(!pPageControl) return;
	//---
	if((this->PageControlBibleText->PageCount == 0) /*|| (pPageControl->ActivePageIndex != enPageTools_Books)*/) return;
	//Jeśli nie ma rzadnej wczytanej księgi, metoda nie zadziała
	this->Act_ResizeWork->Checked = false;
	this->Act_ResizeWorkExecute(this->Act_ResizeWork);
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::TabSheetAllToolsMouseLeave(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Myszka poza objektem TTabSheet //[03-11-2019]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TTabSheet *pTabSheet = dynamic_cast<TTabSheet *>(Sender);
	if(!pTabSheet) return;
	//---
	if((this->PageControlBibleText->PageCount == 0) /*|| (this->PageControlTools->ActivePageIndex != enPageTools_Books)*/) return;
	//Jeśli nie ma rzadnej wczytanej księgi, to nie można zamknąć zakładek
	this->Act_ResizeWork->Checked = true;
	this->Act_ResizeWorkExecute(this->Act_ResizeWork);
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::_AppMessage(tagMSG &Msg, bool &Handled)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(Msg.message == WM_RBUTTONDOWN || Msg.message == WM_RBUTTONUP/* ||
		 Msg.message == WM_LBUTTONDOWN || Msg.message == WM_LBUTTONUP*/)
	//Zabezpieczenie przed reakcją na każdy przycisk myszy w obrębie klasy TWebBrowser [09-11-2019]
	{
		const int ciMaxClassName=255;
		const UnicodeString custrClassExplorerName = "Internet Explorer_Server";
		UnicodeString ustrClassName;
		POINT cursorPoint; //Msg.pt;
		//---
		GetCursorPos(&cursorPoint);
		HWND hWndSelect = WindowFromPoint(cursorPoint);
		if(hWndSelect == NULL) return;
		TCHAR szClassName[ciMaxClassName];
		GetClassName(hWndSelect, szClassName, ciMaxClassName-1);
		ustrClassName = szClassName;
		//---
		if(ustrClassName == custrClassExplorerName)
		{
			Handled = true; //Zablokowanie działania myszy dla objektu klasy TWebBrowser [09-11-2019]
			#if defined(_DEBUGINFO_) && defined(_FULL_DEBUG_)
				GsDebugClass::WriteDebug(Format("TMainBibleWindow::_AppMessage()-szClassName: %s", ARRAYOFCONST((ustrClassName))));
			#endif
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_EditChapterExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Edycja bierzącego rozdziału
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	//MessageBox(NULL, TEXT("Funkcje jeszcze nie aktywna"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
	//return;
	//---
	GsTabSheetClass *pTabSheet = dynamic_cast<GsTabSheetClass *>(this->PageControlBibleText->ActivePage);
	if(!pTabSheet) return;
	//---
	TChapterEditWindow *pChapterEditWindow = new TChapterEditWindow(this, pTabSheet);
	if(!pChapterEditWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TChapterEditWindow"));
	pChapterEditWindow->ShowModal();

	//this->PageControlBibleText->SetFocus(); pTabSheet->SetFocus(); pTabSheet->SetFocusText();
}
//---------------------------------------------------------------------------

