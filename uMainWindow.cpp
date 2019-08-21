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

3. Nazwa klasy (główne okno dla modułu), tworzy się z nazwy modułu, bez początkowego u.
Przykład: nazwa klasy dla modułu uMojaBibliaWindow.h, będzie nazywać się MojaBibliaWindow

4. Nazwa komponentów wizualnych rozpoczyna się przedrostkiem tworzonym skrótu klasy okna na której ten komponent będzie się znajdował.
Przykład: komponent na oknie klasy MainBibleWindow, zaczyna się od przedrostka MBW_ (duże litery występująca w nazwie klasy okna),
potem następuje nazwa klasy bez przedrostka T (ImageList), ewentualnie jej zrozumiały dla programisty skrót (ImgList, ImgL),  potem dowolna nazwa.
Najlepiej skomentować nazwę klasy, dla lepszego zrozumienia.

5. Nazwa klas i komponentów niewidocznych tworzy się podobnie, co komponentów wizualnych, lecz na początku dodajemy dużą literę X.
Przykład: klasa okna to MojaBibliaWindow, nazwa klasy nie wizualnej to XMBW_HSList (to obiekt klasy THashedStringList, w wersji skróconej).

6. Nazwa wskaźników na własne klasy tworzy się z przedrostka "p" + nazwy klasy, lub skrót nazwy klasy,
np. wskaźnik na obiekt klasy ReadBibleTextClass, tworzy się następująco: _(jeśli prywatny)pReadBibleTextClass.

7.Nazwy akcji, czyli składników objektu, klasy TActionManager, tworzy się przez dodanie przedrostka Act_

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
/*************************************************************************************************************************************************
 *  03.07.2019 TYMCZASOWE ZANIECHANIE DODAWANIA NOWYCH ELEMENTÓW DO KODU. ROZPOCZĘTO GRUNTOWNE SPRAWDZANIE, ORAZ OPTYMALIZACJĘ KODU ŹRÓDŁOWEGO.  *
 *  PODMIENIANIE PRZESTARZAŁYCH, LUB STARYCH FUNKCJI, METOD, NOWYMI BARDZIEJ ZOPTYMALIZOWANYMI I ZAAWANSOWANYMI.                                 *
 *  SPRAWDZANIE MOŻLIWOSCI PODMIANY FUNKCJI ZAPISU I ODCZYTU PLIKÓW, PRZEZ METODY Z KLASY TFILE.                                                 *
 *************************************************************************************************************************************************/
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
#include <System.IOUtils.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainBibleWindow *MainBibleWindow;
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
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
	//Kontrola wymiarów okna
	this->Constraints->MinHeight = 600;
	this->Constraints->MinWidth = 1024;
	if(Screen->DesktopWidth > 1280) this->Width = 1280;
	if(Screen->DesktopHeight > 800) this->Height = 795; else this->Height = 600;
	//---BallonHint
	this->_InitAllTagAndHint();
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::MBW_TrayIconMainBalloonClick(TObject *Sender)
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
		MessageBox(NULL, TEXT("Wstrzymanie zamykania aplikacji, w celu przeglądu komunikatów konsoli!"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
		GsDebugClass::CloseDebug();
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
	TThumbBarButton *pNewThumbBarButton;
  //--- Tworzenie głównego objektu z tłmaczeniami, klasy GsReadBibleTextClass.
	//    KLASA MUSI BYĆ ZAINICOWANA METODĄ InitMyBible(), PRZED JAKIM KOLWIEK UŻYWANIEM BIBLIOTEKI GsReadBibleTextClass
	GsReadBibleTextData::InitMyBible(this);
	if(!GsReadBibleTextData::IsInitLibrary) throw(Exception("Błąd inicjalizacji głównej bilioteki do pracy i analizy pisma Świętego!"));
	GsReadBibleTextData::CreateTreeBooks(this->MBW_TabSheetBooks, this->MBW_PageControlBibleText);
	//---
	UnicodeString ustrVersion = Library::GetInfo();
	#if defined(__BORLANDC__) && defined(__clang__) && defined(_WIN32)
		this->Caption = Format("Moja Biblia NG wersja beta CLANG v%s © Grzegorz Sołtysik. [Oświęcim %s]", ARRAYOFCONST((ustrVersion, __DATE__)));
	#else
		this->Caption = Format("Moja Biblia NG wersja beta v%s © Grzegorz Sołtysik. [Oświęcim %s]", ARRAYOFCONST((ustrVersion, __DATE__)));
	#endif
	this->STextHeaderListCommentVers->Caption = "Lista wersetów do, których istnieją\n komentarze";
	//--- Tworzenie objektu, klasy listy komentarzy (klasa GsLViewCommentsAllClass) i nagłówka
	this->pGsLViewCommentsAllClass = new GsLViewCommentsAllClass(this->MBW_TabSheetAllCommentsVers);
	this->pGsLViewCommentsAllClass->Parent = this->MBW_TabSheetAllCommentsVers;
	this->pGsLViewCommentsAllClass->Align = alTop;
	this->pGsLViewCommentsAllClass->Height = 360;
	this->pGsLViewCommentsAllClass->OnDblClick = this->_OnDblClick_ListComment;
	//--- Tworzenie listy ulubionych wersetów (klasa GsListBoxFavoritiesClass) i nagłówka
	this->STextHeaderFavorteListVers->Caption = "Lista ulubionych wersetów";
	this->pGsListBoxFavoritiesClass = new GsListBoxFavoritiesClass(this->MBW_TabSheetAllCommentsVers);
	if(!this->pGsListBoxFavoritiesClass) throw(Exception("Błąd inicjalizacji objektu GsListBoxFavoritiesClass"));
	this->pGsListBoxFavoritiesClass->Parent = this->MBW_TabSheetAllCommentsVers;
	this->pGsListBoxFavoritiesClass->Align = alClient;
	this->pGsListBoxFavoritiesClass->OnDblClick = this->_OnDblClick_ListFavorities;
	//---
	this->MBW_TrayIconMain->ShowBalloonHint();
	this->MBW_TrayIconMain->Hint = Format("Moja Biblia NG wersja beta v%s © Grzegorz Sołtysik.", ARRAYOFCONST((ustrVersion)));
	this->MBW_TrayIconMain->BalloonTitle = this->MBW_TrayIconMain->Hint;
	this->MBW_TrayIconMain->BalloonHint = "Oprogramowanie do studiowania Pisma Świętego";
  //this->MBW_TrayIconMain->Icon = Application->Icon;
	this->_CreatePopupTrayIcon(); //Tworzenie menu podręcznego dla traya
	//Stworzenie zawartości zakładki z multimediami
	GsPanelMultiM *pGsPanelMultiM = new GsPanelMultiM(this->MBW_TabSheetMultimedials, this->MBW_PageControlBibleText);
	if(!pGsPanelMultiM) throw(Exception("Błąd inicjalizacji objektu GsPanelMultiM"));
	pGsPanelMultiM->Parent = this->MBW_TabSheetMultimedials;
	pGsPanelMultiM->Align = alClient;
	this->MBW_PageControlTools->ActivePage = this->MBW_TabSheetBooks;  //Domyślnie aktywna zakładka
	static UnicodeString ustrHintTBarButtons[] = {"Informacje o aktualnie wczytanym rozdziele", "Informacje o aplikacji"};
	//---
	this->Width = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_AppWidth, this->Constraints->MinWidth);
	this->Height = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_AppHeight, this->Constraints->MinHeight);

	this->MBW_TaskbarMain->PreviewClipRegion->Left = 0;
	this->MBW_TaskbarMain->PreviewClipRegion->Top = 0;
	this->MBW_TaskbarMain->PreviewClipRegion->Width = this->Width;
	this->MBW_TaskbarMain->PreviewClipRegion->Height = this->Height;
	//---
	if((enNumTaskBar_NumberButtons == this->XMBW_ActionManagerOther->ActionCount) && (enNumTaskBar_NumberButtons == ARRAYSIZE(ustrHintTBarButtons)))
	{
    #if defined(_DEBUGINFO_)
			//GsDebugClass::WriteDebug(Format("this->XMBW_ActionManagerOther->Count: %d", ARRAYOFCONST((this->XMBW_ActionManagerOther->ActionCount))));
		#endif
		for(int iButton=0; iButton<enNumTaskBar_NumberButtons; iButton++)
		{
			pNewThumbBarButton = this->MBW_TaskbarMain->TaskBarButtons->Add();
			if(pNewThumbBarButton)
			{
				//Dodanie akcji do przycisku na taskbarze
				pNewThumbBarButton->Action = this->XMBW_ActionManagerOther->Actions[iButton];
				pNewThumbBarButton->Hint = ustrHintTBarButtons[iButton];
			}
		}
		#if defined(_DEBUGINFO_)
			//GsDebugClass::WriteDebug(Format("this->MBW_TaskbarMain->TaskBarButtons->Count: %d", ARRAYOFCONST((this->MBW_TaskbarMain->TaskBarButtons->Count))));
		#endif
	}

  this->MBW_TaskbarMain->ApplyChanges();
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
	if(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsRequestEnd, true))
	{
		int iResult;
		iResult = MessageBox(NULL, TEXT("Czy rzeczywiście chcesz opuścić apilkacje?"), TEXT("Pytanie aplikacji"), MB_YESNO | MB_ICONWARNING | MB_TASKMODAL | MB_DEFBUTTON2);
		if(iResult == IDYES) CanClose = true; else CanClose = false;
	}
  else CanClose = true;
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
  GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_AppWidth, this->Width);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_AppHeight, this->Height);
	//--- Zamknięcie klasy głównej do analizy Pisma
	GsReadBibleTextData::CloseMyBible();
	//Zwolnienie pamięci na konfiguracje aplikacji
	if(GlobalVar::Global_ConfigFile)
	{
		GlobalVar::Global_ConfigFile->UpdateFile();	//Zrzut pliku ini z pamięci, do pliku ini
		delete GlobalVar::Global_ConfigFile;
		GlobalVar::Global_ConfigFile = 0;
	}
	Action = caFree;
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
	///
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
	//Główna część panelu zajmuje 75% szerokości oka
	this->MBW_StatusBarMain->Panels->Items[enPanelMain_InfoText]->Width = (int)(0.75 * this->Width);
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
	//---
	this->MBW_PageControlBibleText->Tag = enTagPageControlBibleText; //Zakładki z tekstem
	this->MBW_PageControlTools->Tag = enTagPageControlTools;            //Zakładka z narzędziami

	//this->MBW_HdrControlBooks->Hint = "Nagłówek drzewa ksiąg biblijnych|Nagłówek drzewa ksiąg biblijnych, pokazujący nazwy poszczególnych informacji o księgach biblijnych";
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
	this->MBW_StatusBarMain->Panels->Items[enPanelMain_InfoText]->Text = GetShortHint(Application->Hint);//this->XMBW_BalloonHintMain->Description;//
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
	this->MBW_PMenuTray->Images = pImageList;
	//---
	for(unsigned int i=0; i<GsReadBibleTextData::GsNumberBooks; i++)
	{
		TMenuItem *NewItem = new TMenuItem(this->MBW_PMenuTray);
		if(!NewItem) throw(Exception("Błąd inicjalizacji objektu TMenuItem"));
		this->MBW_PMenuTray->Items->Add(NewItem);
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
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	TTabSheet* pActiveSheet = this->MBW_PageControlBibleText->ActivePage;
	if(pActiveSheet)
	{
		if(pActiveSheet->ClassNameIs("GsTabSheetSelectVersClass")) GsReadBibleTextData::GsSheetListVers = 0; //Jeśli to zakładka z listą wybranych wersetów,
                                                                                      //globalny wskaźnik na zakładkę zostanie wyzerowany
		delete pActiveSheet; //pActiveSheet = 0;
	}
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
void __fastcall TMainBibleWindow::MBW_StatusBarMainDrawPanel(TStatusBar *StatusBar,
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
	GsTabSheetClass *pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(this->MBW_PageControlBibleText->ActivePage);
	if(!pGsTabSheetClass) {pSelectVersWindow = new TSelectVersWindow(this);} //Brak zakładki z załadowaną księgą i rozdziałem
	//Jest zakładka z załadowaną księgą i rozdziałem, więc domyślnie startowym tekstem będzie pierwszy werset z załadowanej księgi i rozdziały,
	//w aktualnej zakładce, w oknie głównym.
	else {pSelectVersWindow = new TSelectVersWindow(this, pGsTabSheetClass->_ShucIndexBook, pGsTabSheetClass->_ShucIndexChapt);}
	//---
	if(!pSelectVersWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TSelectVersWindow"));
	pSelectVersWindow->ShowModal();
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
	//this->MBW_PageControlTools->Visible = !pAction->Checked;
	this->MBW_SplitViewMain->Opened = !pAction->Checked;
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
	if(this->MBW_PageControlBibleText->PageCount > 0)
  //Sprawdzenie czy istnieją zakładki
	{
		UnicodeString ustrMsg;
    ustrMsg = this->MBW_PageControlBibleText->ActivePage->Caption;
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
				this->MBW_TaskbarMain->ProgressValue = 0;
				return;
			}
			//Wyłuskanie wskaźnika do TProgressBaru, aktualnej zakładki
			TProgressBar *pProgressBar = GsReadBibleTextData::GetCurrentNamberChaptOnSheet();
			if(!pProgressBar) return;
			//---
			this->MBW_TaskbarMain->ProgressMaxValue = pProgressBar->Max;
			this->MBW_TaskbarMain->ProgressValue = pProgressBar->Position;
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
	TReadUpdateWindow *pReadUpdateWindow = new TReadUpdateWindow(this);
	if(!pReadUpdateWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TReadUpdateWindow"));
	pReadUpdateWindow->ShowModal();
}
//---------------------------------------------------------------------------

