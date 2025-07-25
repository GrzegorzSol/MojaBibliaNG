﻿/////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2008,2009,2010,2011,2012,2013, 2014, 2015, 2016, 2017, 2018, 2019, 2020, 2021 //
//							 2022,2023, 2024																															 //
//																		 Grzegorz Sołtysik																			 //
//																		 All rights reserved.																		 //
//																		grzegorzsol@gmail.com																		 //
//																 www.facebook.com/MojaBiblia																 //
/////////////////////////////////////////////////////////////////////////////////////////////////
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
#include <vcl.h>
#pragma hdrstop

#include "uMainWindow.h"
#include "uSearchTextWindow.h"
#include "uLibrary.h"
#include "uSetupsWindow.h"
#include "uSelectVersWindow.h"
#include "uDictGrecPolWindow.h"
#include "uNewSchemeVersWindow.h"
#include "uAllMultimediaView.h"
#include "uInformationsAppWindow.h"
#include "uChapterEditWindow.h"
#include "uSendingMailWindow.h"
#include "uReadingPlanWindow.h"
#include "uHistoryChaptersOpen.h"
#include "uBooksSpecjalistWindow.h"
#include "uStrongWindow.h"
#include "MyBibleLibrary\GsReadBibleTextdata.h"
#include <System.Win.Registry.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Vcl.HtmlHelpViewer" //!!!
#pragma resource "*.dfm"
TMainBibleWindow *MainBibleWindow;
int Global_WidthTabTools = 0;
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
// Makro zmieniajace niektóre parametry w środowisku C++Builder v12.1 Athens //[30-08-2024]
#if(__CODEGEARC__ == 0x0770)
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
catch(Exception &e)
{
	MessageBox(NULL, e.Message.c_str() , TEXT("Błąd"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
}
*/
enum {enImageMainIndex_CloseSheet,		 //0.Zamknięcie aktywnej zakładki
			enImageMainIndex_Search,				 //1.Wyszukiwanie
			enImageMainIndex_Setups,				 //2.Ustawienia
			enImageMainIndex_SaveChapter,		 //3.Zapis aktualnego rozdziału
			enImageMainIndex_ChoiceVers,		 //4.Wybór i przegląd pojedyńczego wersetu
			enImageMainIndex_InformHelp,		 //5.Pomoc i informacje
			enImageMainIndex_CorcondanceGrek,//6.Konkordancja grecka
			enImageSchemeVers,							 //7.Projektowanie zależności logicznej między wersetami
			enImageViewAllResources,				 //8.Przegląd wszystkich dostępnych zasobów
			enImageResizeWork,							 //9.Poszerzanie obszaru tekstu
			enImageFacePage,								 //10.Odnośnik do strony FaceBook
			enImageUpdate,									 //11.Sprawdzanie aktualizacji i ewentualny aktualizacje
			enImageLogoApplication,					 //12.Ikona z główną grafiką aplikacji
			enImageEditChapter,							 //13.Edycja rozdziału
			enImage_MailChapt,							 //14.Wyśli emailem rozdział
			enImage_Help,										 //15.Pomocnik
			enImage_Tips,										 //16.Nawigator podpowiedzi
			enImage_ReadingPlan,						 //17.Plan czytania bibli
			enImage_HistoryTextOpen,				 //18.Historia otwieranych rozdziałów
			enImage_OpenInWord,							 //19.Otwarcie wybranego rozdziału w Ms Wordzie
			enImage_BooksSpec,							 //20.Okno z tłumaczeniami specjalistycznymi
			enImage_StrongDictionary,				 //21.Okno ze słownikiem Stronga
			enImage_HelpVideo,							 //22.Pomocnicy video na kanale.
			enImageMainIndex_Count,					 //Ilość ikon
			//Małe ikony
			enImage16_Books=0,							 //0.Księgi biblijne
			enImage16_Media,								 //1.Multimedia
			enImage16_Coments,							 //2.komentarze
			enImage16_InfoTaskBarButton,		 //3.Obraz dla przycisku informacji na taskbarze, o aktualnie wczytanym rozdziele
			enImage16_InfoApplicationTaskBarButton,//4.Obraz dla przycisku informacji o aplikacji
			enImage16_FavSearchResults,				//5.Obraz dla zakładki z ulubionymi wynikami wyszukiwań //[11-10-2023]
			enImage16_Count,								 //Ilość małych ikon
			//Numer paneli na objekcie klasy TStatusBar
			enPanelMain_InfoText=0, enPanelMain_InfoEx, //Numery paneli
			//menu Tray
			enPMenuTray=0, //Początkowa pozycja w menu Tray
			//Panele objektu MBW_PControlTools, klasy TPageControl
			enPageTools_Books=0, //0.Zakładka z drzewem ksiąg biblijnych
			enPageTools_CommentsVers, //1.Zakładka ze wszystkimi komentarzami
			enPageTools_FavSearchResults, //2.Zakładka z ulubionymi wynikami wyszukiwań //[11-10-2023]
			//Tagi dla kontrolek
			enTagCloseSheet=100,	//100.Zamknięcie aktywnej zakładki
			enTagSaveChaptToHTML, //101.Zapis rozdziału z bierzącej zakładki, jako pliku html
			enTagSearchBibleText, //102.Zaawansowane wyszukiwanie tekstu
			enTagSetupsApplic,		//103.Wszystkie ustawienia aplikacji.
			enTagSelectVers,			//104.Wybór pojedyńczego wersetu
			enTagCorcondance,			//105.Korkondancja grecka
			enTagSchemeVers,			//106.Projektowanie zależności logicznej między wersetami
			enTagInformations,		//107.Wyświetlanie informacji
			enTagViewAllResources,//108.Przegląd wszystkich dostępnych zasobów
			enTagResizeWork,			//109.Poszerzanie obszaru tekstu
			enTagFacePage,				//110.Odnośnik do strony facebook
			enTagUpdate,					//111.Sprawdzanie aktualizacji i ewentualny aktualizacje
			enTagEditChapter,			//112.Edycja rozdziału
			enTagMailChapt,				//113.Wyśli emailem rozdział
			//enTagImageAndText,		//114.Tworzenie grafiki z tekstem
			enTagImageHelp,				//115.Pomocnik
			enTagImage_Tips,			//116.Nawigator podpowiedzi
			enTagImage_ReadingPlan,//117.Plan czytania bibli
			enTagImage_HistoryTextOpen,//118.Historia otwieranych rozdziałów
			enTagImage_OpenInWord,		//119.Otwarcie wybranego rozdziału w Ms Wordzie
			enTagImage_BooksSpec,			//120.Okno z tłumaczeniami specjalistycznymi
			enTagImage_StrongDictionary,//121.Okno ze słownikiem Stronga
			enTagImage_HelpVideo,				//122.Pomocnicy video na kanale.
			//Tagi dla komponentów TImage
			enTagPic_Backgound,				//120.Komponent typu TImage podkładu
			//
			enTagPageControlBibleText = 200, //Zakładki z tekstem
			enTagPageControlTools,						//Zakładka z narzędziami
			//Numery dla przycisków na taskbarze
			enNumTaskBar_InfoReadChapt = 0,	 //Informacja o aktualnie wczytanym rozdziale
			enNumTaskBar_InfoAplic,					 //Informacja o aplikacji
			enNumTaskBar_NumberButtons,			 //Ilość przycisków na taskbarze
			//Nagi dla zakładki plików ulubionych, wyszukiwania
			enTagSearchFav_DeleteFile = 200 //200.Przycisk kasowania zaznaczonego pliku w zakładce ulubionych plików wyszukiwania
		 };

const UnicodeString Gl_custrNameAppReload = "MBRestart.exe"; //Nazwa aplikacji odpowiedzialnej za restart głównego programu po zmianie nie których ustawień konfiguracyjnych
										// Zmiana makr ze względu na nazwe projektu //08-07-2024
//										Gl_custrModuleTestings = "Moja Biblia NG Testing.exe",
//										Gl_custrModuleRelease = "Moja Biblia NG.exe";
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
	Application->OnException = this->_AppException; //Ustawienie obsługi błędów dla całej aplikacji

	#if defined(_DEBUGINFO_) //Ewentualne tworzenie konsoli TMemo dla prywatnego debugera
		GsDebugClass::InitDebug(10, 10);
	#endif
	//----- Sprawdzenie czy aktualnym systemem jest Windows 10
	GlobalVar::IsWindows10 = TOSVersion::Check(10); //???
	//----- Sprawdzanie istnienia odpowiednich katalogów
	if(!TDirectory::Exists(GlobalVar::Global_custrPathMultimediaFilesData)) TDirectory::CreateDirectory(GlobalVar::Global_custrPathMultimediaFilesData);
		//----- Katalog z nieuzywanymi tłumaczeniami [31-05-2024]
	//if(!TDirectory::Exists(GlobalVar::Global_custrPathTranslatesNotUse)) TDirectory::CreateDirectory(GlobalVar::Global_custrPathTranslatesNotUse);
	//----- Tworzenie globalnego wskaźnika, do pliku konfiguracyjnego
	GlobalVar::Global_ConfigFile = new TMemIniFile(GlobalVar::Global_custrGetConfigFile, TEncoding::UTF8);
	if(!GlobalVar::Global_ConfigFile) throw(Exception("Błąd inicjalizacji objektu TMemIniFile"));
	//----- Ścieżki dostępu do wybranych, przez użytkownika katalogów z multimediami
	GlobalVar::Global_SListPathMultiM = new TStringList();
	if(!GlobalVar::Global_SListPathMultiM) throw(Exception("Błąd inicjalizacji objektu TStringList"));
	//----- String lista histori otwieranych rozdziałow księg biblijnych
	GlobalVar::Global_HListHistoryChapterOpen = new THashedStringList();
	if(!GlobalVar::Global_HListHistoryChapterOpen) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
	//Odczyt pliku historii
	this->Act_HistoryChapters->Enabled = TFile::Exists(GlobalVar::Global_custrPathHistory);
	if(TFile::Exists(GlobalVar::Global_custrPathHistory))
	{
		GlobalVar::Global_HListHistoryChapterOpen->LoadFromFile(GlobalVar::Global_custrPathHistory, TEncoding::UTF8);
	}
	//---
	Application->OnHint = this->_AppOnHint;
	//Application->OnMessage = this->_AppMessage;
	Application->OnHelp = this->_AppHelp;
	//Kontrola wymiarów okna, minimalne, dopuszczalne wymiary
	this->Constraints->MinHeight = 600;
	this->Constraints->MinWidth = 1024;
	//Uzależnienie wymiarów okna, od wymiarów ekranu
	if(Screen->DesktopWidth > 1280) this->Width = 1280;
	if(Screen->DesktopHeight > 800) this->Height = 795; else this->Height = 600;
	//---Wczytanie stylu
	UnicodeString ustrSelectStyle = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_SelectStyleName, GlobalVar::Global_DefaultStyleName);
	if(!TStyleManager::TrySetStyle(ustrSelectStyle, false)) //[02-05-2023]
	//Jeśli nie ma takiego stylu, ustawiany jest styl domyślny
	{
		//TStyleManager::TrySetStyle(GlobalVar::Global_DefaultStyleName, false);
		TStyleManager::SetStyle(GlobalVar::Global_DefaultStyleName);
	}
	//Wyłączenie styli dla okien dialogowych, w tym przypadku chodzi o wyłączenie styli dla okna pomocy
	TStyleManager::SystemHooks = TStyleManager::SystemHooks >> TStyleManager::shDialogs;
	//Sprawdzenie czy aplikacja MS Word jest zainstalowana w systemie
	this->_bIsWordInstalled = this->_IsWordInstalled();
	this->Act_OpenInWord->Enabled = false;
		//---BallonHint
	this->_InitAllTagAndHint(); //Musi być ostatni [28-08-2023]
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
	if(GlobalVar::Global_SListPathMultiM) {delete GlobalVar::Global_SListPathMultiM; GlobalVar::Global_SListPathMultiM = nullptr;}
	if(GlobalVar::Global_ConfigFile) {delete GlobalVar::Global_ConfigFile; GlobalVar::Global_ConfigFile = nullptr;}
	#if defined(_DEBUGINFO_) //Konsola debuggera
		//GsDebugClass::WriteDebug("TMainBibleWindow::~TMainBibleWindow()");
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
	//OleInitialize(NULL);
	//Odczyt z konfiguracji grafiki podkładu pod główne okno //Nieskończone [11-12-2023]
	UnicodeString ustrGraphicsBackground = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_OthersSection,
		GlobalVar::GlobalIni_GrahicsBackground, GlobalVar::Global_custrPathBackgroundWindow); //[11-12-2023]
	TWICImage *pWICImage=nullptr;

	if(TFile::Exists(ustrGraphicsBackground)) //29-04-2021 //[11-12-2023]
	{
		try
		{
			try //[12-12-2023]
			{
				//--- Wczytanie grafiki podkładu głównego okna(dopuszczalne jest jej brak)
				pWICImage = new TWICImage();
				if(!pWICImage) throw(Exception("Błąd inicjalizacji objektu TWICImage"));
				pWICImage->LoadFromFile(ustrGraphicsBackground);
				this->ImageBackgroundWindow->Picture->Assign(pWICImage);
			}
			catch(Exception &e)
			{
				MessageBox(NULL, e.Message.c_str(), TEXT("Informacje aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
			}
		}
		__finally
		{
			delete pWICImage; pWICImage = nullptr;
		}
	}
	//---
	TThumbBarButton *pNewThumbBarButton;
	//--- Tworzenie głównego objektu z tłmaczeniami, klasy GsReadBibleTextClass.
	//		KLASA MUSI BYĆ ZAINICOWANA METODĄ InitMyBible(), PRZED JAKIM KOLWIEK UŻYWANIEM BIBLIOTEKI GsReadBibleTextClass
	GsReadBibleTextData::InitMyBible(this);
	if(!GsReadBibleTextData::IsInitLibrary) throw(Exception("Błąd inicjalizacji głównej bilioteki do pracy i analizy pisma Świętego!"));
	GsReadBibleTextData::CreateTreeBooks(this->TabSheetBooks, this->PageControlBibleText);
	//----- Odzcyt wersji biblioteki
	UnicodeString ustrVersion = Library::GetInfo();
	const UnicodeString custrNameMod = TPath::GetFileNameWithoutExtension(Application->ExeName); //10-11-2024
	GlobalVar::Global_ustrVerAplicMain = ustrVersion;

	#if defined(_WIN64) //10-11-2024
		this->Caption = Format("%s wersja x64 v%s © Grzegorz Sołtysik [Oświęcim Date: %s Time: %s.]",
			ARRAYOFCONST((custrNameMod, ustrVersion, __DATE__, __TIME__)));
	#else //10-11-2024
		this->Caption = Format("%s wersja x32 v%s © Grzegorz Sołtysik [Oświęcim Date: %s Time: %s.]",
			ARRAYOFCONST((custrNameMod, ustrVersion, __DATE__, __TIME__)));
	#endif
	//Zapis pliku tekstowego z wersją
	TFile::WriteAllText(GlobalVar::Global_custrGetVersionUpdate, GlobalVar::Global_ustrVerAplicMain, TEncoding::UTF8);
	//----- Nagłówek listy wersetów z komentarzami
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
	//--- Tworzenie listy ulubionych wyników wyszukiwania //[12-10-2023]
	this->pGsSearchFavFilesClass = new GsSearchFavFilesClass(this->TabSheetFavResultSearch);
	if(!this->pGsSearchFavFilesClass) throw(Exception("Błąd inicjalizacji objektu, klasy GsViewAllResourcesClass"));
	this->pGsSearchFavFilesClass->Parent = this->TabSheetFavResultSearch;
	this->pGsSearchFavFilesClass->Align = alClient;
	this->pGsSearchFavFilesClass->OnSelectItem = this->_OnSelectItemSearchFile; //[15-10-2023]
	//---
	if(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsDisplayStartInfoTray, true))
		//Czy wyświetlac informacje o aplikacji w polu traja, w momencie jej uruchamiania
		{this->TrayIconMain->ShowBalloonHint();}
	this->TrayIconMain->Hint = Format("Moja Biblia NG wersja beta v%s © Grzegorz Sołtysik.", ARRAYOFCONST((ustrVersion)));
	this->TrayIconMain->BalloonTitle = this->TrayIconMain->Hint;
	this->TrayIconMain->BalloonHint = "Oprogramowanie do studiowania Pisma Świętego";
	//this->MBW_TrayIconMain->Icon = Application->Icon;
	this->_CreatePopupTrayIcon(); //Tworzenie menu podręcznego dla traya
	this->PageControlTools->ActivePage = this->TabSheetBooks;	 //Domyślnie aktywna zakładka
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
		for(int iButton=0; iButton<enNumTaskBar_NumberButtons; ++iButton)
		{
			pNewThumbBarButton = this->TaskbarMain->TaskBarButtons->Add();
			if(pNewThumbBarButton)
			{
				//Dodanie akcji do przycisku na taskbarze
				pNewThumbBarButton->Action = this->ActionManagerOther->Actions[iButton];
				pNewThumbBarButton->Hint = ustrHintTBarButtons[iButton];
			}
		}
	}

	this->TaskbarMain->ApplyChanges();
	//ustawienie wartości domyślnej dla szerokości, do której zostanie zwinięty objekt, klasy TSplitView.
	//Dokładna szerokość określana jest w metodzie TMainBibleWindow::MBW_PageControlsAllDrawTab() tylko jednokrotnie!
	//Szerokość lewego kontenera przycisków
	this->ActionToolBarMain->Width = this->Width / 2;

	this->ImageBackgroundWindow->OnDragDrop = GsReadBibleTextData::pGsReadBibleTextClass->GlobalTextDragDrop;
	//--- Ustawienia zakładki ulubionych plików wyszukiwań //[14-10-2023]
	this->ToolBarSearcheFiles->Images = this->pGsSearchFavFilesClass->GetImageList();
		//Stałe indeksu TImageList pochodzi z GsComponents\GsSearchFavFilesClass.h //[14-10-2023]
	this->ToolButtDeleteFile->ImageIndex = enIndexImage16_Delete;
	this->ToolButtDeleteFile->Tag = enTagSearchFav_DeleteFile;
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
	static bool sbIsNextOpen; //24-04-2020. Zmienna statyczna która zapobiega powtórnemu uruchomieniu metody
	//---
	if(sbIsNextOpen) return;
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
		for(int i=0; i<pHSListOpenBooksInExit->Count; ++i)
		{
			iBook = pHSListOpenBooksInExit->Strings[i].SubString(1, 3).ToIntDef(1);
			iChapt = pHSListOpenBooksInExit->Strings[i].SubString(4, 3).ToIntDef(1);
			GsReadBibleTextData::OpenSelectBookAndChapter(iBook, iChapt);
			GlobalVar::Global_HListHistoryChapterOpen->Delete(GlobalVar::Global_HListHistoryChapterOpen->Count - 1);
		}

		delete pHSListOpenBooksInExit; pHSListOpenBooksInExit = nullptr;

		sbIsNextOpen = true;
		//Uaktywnienie przycisku wysyłania rozdziału mailem, gdy istnieje bierzący rozdział
		this->Act_MailChapt->Enabled = ((this->PageControlBibleText->PageCount > 0) &&
			(dynamic_cast<GsTabSheetClass *>(this->PageControlBibleText->ActivePage)));
	}
	//Stan przycisku zmiany obszaru tekstu 12-04-2021
	this->Act_ResizeWork->Enabled = (this->PageControlBibleText->PageCount > 0);
	//Stan przycisku zapisu aktywnego rozdziału 07-04-2021
	this->Act_SaveChaptToHTML->Enabled = (this->PageControlBibleText->PageCount > 0);
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
	if(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsRequestEnd, true) &&
		 GlobalVar::iReturnUpdate != 1)
	{
		TTaskDialog *pTaskDialog = new TTaskDialog(this);
		if(!pTaskDialog) throw(Exception("Błąd inicjalizacji objektu TTaskDialog"));
		pTaskDialog->Caption = "Pytanie aplikacji";
		pTaskDialog->Title = "Czy rzeczywiście chcesz opuścić apilkacje?";

		pTaskDialog->ExpandedText = "Naciśnięcie przycisku OK, spowoduje opuszczenie aplikacji. To pytania można wyłączyć w jej ustawieniach, wtedy aplikacja zostanie zaknięta bez pytania!";
		pTaskDialog->MainIcon = tdiWarning;
		pTaskDialog->DefaultButton = tcbNo;
		pTaskDialog->CommonButtons = TTaskDialogCommonButtons() << tcbYes << tcbNo;
		pTaskDialog->ModalResult = mrNo;
		pTaskDialog->Flags = TTaskDialogFlags() << tfUseHiconMain << tfExpandedByDefault << tfPositionRelativeToWindow;
		if(this->ImageListMainActive) this->ImageListMainActive->GetIcon(enImageLogoApplication, pTaskDialog->CustomMainIcon);
		if(pTaskDialog->Execute())
		{
			if(pTaskDialog->ModalResult == mrYes) CanClose = true; else CanClose = false;
		}
		if(pTaskDialog) {delete pTaskDialog; pTaskDialog = nullptr;}
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
	//---
	if(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsLoadBooksOnInit, true))
	//Zapis listy otwartych ksiąg i rozdziałów w momencie zamknięcia aplikacji
	{
		THashedStringList *pHSListOpenBooksInExit = new THashedStringList();
		if(!pHSListOpenBooksInExit) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
		UnicodeString ustrAdress;
		for(int i=0; i<this->PageControlBibleText->PageCount; ++i)
		{
			GsTabSheetClass *pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(this->PageControlBibleText->Pages[i]);
			if (pGsTabSheetClass)
			{
				GsReadBibleTextData::GetAdressFromId(ustrAdress, pGsTabSheetClass->_ShucIndexBook+1, pGsTabSheetClass->_ShucIndexChapt+1);
				pHSListOpenBooksInExit->Add(ustrAdress);
			}
		}
		GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_LoadBooksOnExit, pHSListOpenBooksInExit->CommaText);
		delete pHSListOpenBooksInExit; pHSListOpenBooksInExit = nullptr;
	}
	//--- Zamknięcie klasy głównej do analizy Pisma
	GsReadBibleTextData::CloseMyBible();
	//Zwolnienie pamięci na konfiguracje aplikacji
	if(GlobalVar::Global_ConfigFile)
	{
		GlobalVar::Global_ConfigFile->UpdateFile();	//Zrzut pliku ini z pamięci, do pliku ini
	}
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("FormClose -> GlobalIni_IsDisplayBackgroundImage: \"%s\"", ARRAYOFCONST((GlobalVar::GlobalIni_IsDisplayBackgroundImage))));
//	#endif
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
	//OleUninitialize();
//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("FormDestroy -> GlobalIni_IsDisplayBackgroundImage: \"%s\"", ARRAYOFCONST((GlobalVar::GlobalIni_IsDisplayBackgroundImage))));
//	#endif
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
	this->StatusBarMain->Panels->Items[enPanelMain_InfoText]->Width = (int)(0.75 * this->Width);
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::FormKeyUp(TObject *Sender, WORD &Key, TShiftState Shift)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	switch(Key)
	{
		case vkF1:
			Application->HelpContext(HELP_Wprowadzenie);
		break;
	}
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
	this->OnCloseQuery = nullptr;
	Application->Terminate(); //Zamknięcie aplikacji
}
//---------------------------------------------------------------------------
bool __fastcall TMainBibleWindow::_AppHelp(System::Word Command, NativeInt Data, bool &CallHelp)
/**
	OPIS METOD(FUNKCJI): Globalna pomoc
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	Application->HelpFile = GlobalVar::Global_custrPathGlobalHelp;
	CallHelp = true;
	return true;
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
void __fastcall TMainBibleWindow::_AppMessage(tagMSG &Msg, bool &Handled)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//
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
	this->ImageBackgroundWindow->Tag = enTagPic_Backgound; //[12-12-2023]
	//Podpowiedzi i tagi akcji
	this->Act_CloseSheetActive->Tag = enTagCloseSheet;	//Zamknięcie aktywnej zakładki
	this->Act_CloseSheetActive->Hint = Format("Zamknięcie zakładki|Zamknięcie aktualnie aktywnej zakładki z tekstem|%u", ARRAYOFCONST((this->Act_CloseSheetActive->ImageIndex)));
	this->Act_SaveChaptToHTML->Tag = enTagSaveChaptToHTML; //Zapis rozdziału z bierzącej zakładki, jako pliku html
	this->Act_SaveChaptToHTML->Hint = Format("Zapis do pliku|Zapis zawartości aktualnej zakładki, do pliku w formacie html.|%u", ARRAYOFCONST((this->Act_SaveChaptToHTML->ImageIndex)));
	this->Act_SearchBibleText->Tag	= enTagSearchBibleText; //Zaawansowane wyszukiwanie tekstu
	this->Act_SearchBibleText->Hint = Format("Wyszukiwanie|Otwiera okno do wyszukiwanie wyrażeń i fraz w tekście biblijnym.|%u", ARRAYOFCONST((this->Act_SearchBibleText->ImageIndex)));
	this->Act_SetupsApplic->Tag	 = enTagSetupsApplic;		 //Wszystkie ustawienia aplikacji.
	this->Act_SetupsApplic->Hint = Format("Ustawienia|Wszystkie ustawienia aplikacji.|%u", ARRAYOFCONST((this->Act_SetupsApplic->ImageIndex)));
	this->Act_SelectVers->Tag = enTagSelectVers;			 //Wybór pojedyńczego wersetu
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
	this->Act_MailChapt->Tag = enTagMailChapt;
	this->Act_MailChapt->Hint = Format("Wysłanie rozdziału emailem|Wysłanie aktualnie wczytanego rozdziału emailem, na wybrany adres.|%u", ARRAYOFCONST((this->Act_MailChapt->ImageIndex)));
	//this->Act_ImageAndText->Tag = enTagImageAndText;
	//this->Act_ImageAndText->Hint = Format("Tworzenie grafiki z tekstem biblijnym, lub innym|Moduł do tworzenia grafiki w formie podkładu i dowolnego tekstu.|%u", ARRAYOFCONST((this->Act_ImageAndText->ImageIndex)));
	this->Act_ReadingPlan->Tag = enTagImage_ReadingPlan;
	this->Act_ReadingPlan->Hint = Format("Okno planu czytania Biblii|Otwiera okno czytania Pisma Świętego, według ustawionego planu.|%u", ARRAYOFCONST((this->Act_ReadingPlan->ImageIndex)));
	this->Act_HistoryChapters->Tag = enTagImage_HistoryTextOpen;
	this->Act_HistoryChapters->Hint = Format("Okno histori otwieranych rozdziałów|Otwiera okno z historia rozdziałów otwartych w aplikacji.|%u", ARRAYOFCONST((this->Act_HistoryChapters->ImageIndex)));
	this->Act_OpenInWord->Tag = enTagImage_OpenInWord;
	if(this->_bIsWordInstalled) //[28-08-2023]
		this->Act_OpenInWord->Hint = Format("Otwarcie rozdziału w Ms Wordzie|Otwarcie aktywnego rozdziału w aplikacji Ms Word.|%u", ARRAYOFCONST((this->Act_OpenInWord->ImageIndex)));
	else
		this->Act_OpenInWord->Hint = Format("Otwarcie rozdziału w Ms Wordzie|Otwarcie aktywnego rozdziału w aplikacji MS Word jest niemożliwe.\nBrak zainstalowanego oprogramowania.|%u", ARRAYOFCONST((this->Act_OpenInWord->ImageIndex)));
	this->Act_SpecBooks->Tag = enTagImage_BooksSpec;
	this->Act_SpecBooks->Hint = Format("Okno tłumaczeń specjalistycznych|Otwiera okno z dostępnymi tłumaczeniami specjalistycznymi, Pisma Świetego.|%u", ARRAYOFCONST((this->Act_SpecBooks->ImageIndex)));
	this->Act_StrongDictionary->Tag = enTagImage_StrongDictionary;
	this->Act_StrongDictionary->Hint = Format("Okno słownika Stronga|Otwarcie okna przeznaczonego do pracy ze słownikiem stronga.|%u", ARRAYOFCONST((this->Act_StrongDictionary->ImageIndex)));
	this->Act_HelpVideo->Tag = enTagImage_HelpVideo;
	this->Act_HelpVideo->Hint = Format("Pomocnicy video dla aplikacji.|Otwarcie kanału filmów instruktażowych dla aplikacji.|%u", ARRAYOFCONST((this->Act_HelpVideo->ImageIndex)));

	this->ToolButtDeleteFile->Hint = "Usunięcie zaznaczonego pliku z ulubionym wyszukiwaniem"; //[14-10-2023]
	//---
	this->PageControlBibleText->Tag = enTagPageControlBibleText; //Zakładki z tekstem
	this->PageControlTools->Tag = enTagPageControlTools;						//Zakładka z narzędziami
}
//---------------------------------------------------------------------------
bool __fastcall TMainBibleWindow::_IsWordInstalled()
/**
	OPIS METOD(FUNKCJI): Metoda sprawdza czy MS Word jest zainstalowany
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	bool bIsInstalled=false;
	const UnicodeString custrReg = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\Winword.exe";

	TRegistry *pRegistry = new TRegistry(KEY_READ);
	if(!pRegistry) throw(Exception("Błąd załadowania objektu klasy TRegistry"));

	pRegistry->RootKey = HKEY_LOCAL_MACHINE;
	if(pRegistry->KeyExists(custrReg))
	{
		pRegistry->CloseKey();
		bIsInstalled = true;
	}
	if(pRegistry) {delete pRegistry; pRegistry = nullptr;}
	return bIsInstalled;
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
	for(unsigned int i=0; i<GlobalVar::Global_NumberBooks; ++i)
	{
		TMenuItem *NewItem = new TMenuItem(this->PMenuTray);
		if(!NewItem) throw(Exception("Błąd inicjalizacji objektu TMenuItem"));
		this->PMenuTray->Items->Add(NewItem);
		NewItem->Caption = AppCTable_InfoAllBooks[i].FullNameBook;
		NewItem->OnClick = this->_OnClick_PMenuTray;
		NewItem->Tag = enPMenuTray + i;
		NewItem->ImageIndex = enImageIndex_Book;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::ImageBackgroundWindowDragOver(TObject *Sender,
					TObject *Source, int X, int Y, TDragState State, bool &Accept)
/**
	OPIS METOD(FUNKCJI): Główna metoda wywoływana podczas przeciągania elementu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Akceptacja jeśli jest to objekt odpowiedniej klasy
	Accept = Source->ClassNameIs("GsTreeBibleClass");
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::_DisplayHelp(TAction *_pAction)
/**
	OPIS METOD(FUNKCJI): Wyświetlenie pomocy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
//	HelpWindowData pHelpWindowData;
//	SecureZeroMemory(&pHelpWindowData, sizeof(HelpWindowData));
//	pHelpWindowData.pAction = _pAction;
//	//---
//	THelpMyBibleWindow *pTHelpMyBibleWindow = new THelpMyBibleWindow(this, pHelpWindowData);
//	if(!pTHelpMyBibleWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna THelpMyBibleWindow"));
//	pTHelpMyBibleWindow->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::PageControlBibleTextEnter(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Zdarzenie związane z aktywacją zakładki, wykorzystywane do wykrywania pojawienia się pierwszej zakładki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPageControl *pPageControl = dynamic_cast<TPageControl *>(Sender);
	if(!pPageControl) return;
	//---
	this->Act_HistoryChapters->Enabled = true;
	//Stan przycisku zmiany obszaru tekstu 12-04-2021
	this->Act_ResizeWork->Enabled = (this->PageControlBibleText->PageCount > 0);
	this->Act_ResizeWork->Checked = (pPageControl->PageCount > 0);
	this->Act_ResizeWorkExecute(this->Act_ResizeWork);
	//Stan przycisku zapisu aktywnego rozdziału 07-04-2021
	this->Act_SaveChaptToHTML->Enabled = (pPageControl->PageCount > 0);
	//---
	this->Act_ResizeWorkExecute(this->Act_ResizeWork);
	this->Act_CloseSheetActive->Enabled = (pPageControl->PageCount > 0);
	this->Act_EditChapter->Enabled = (pPageControl->PageCount > 0);
	this->Act_OpenInWord->Enabled = this->Act_EditChapter->Enabled && this->_bIsWordInstalled;
	//Uaktywnienie przycisku wysyłania rozdziału mailem, gdy istnieje bierzący rozdział
	this->Act_MailChapt->Enabled = this->Act_EditChapter->Enabled;
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
		case enTagPageControlTools:						 //Zakładka z narzędziami (wybór ksiąg, zasoby, wersety)
		{
		}
		break;
	}
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
	//StatusBar->Font = this->Font;
	pCanvas->Font = this->Font;
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
	if((this->PageControlBibleText->PageCount == 0)	 || (this->PageControlBibleText->ActivePageIndex == -1)) return;
	//---
	TTabSheet* pActiveSheet = this->PageControlBibleText->ActivePage;
	if(pActiveSheet)
	{
		if(pActiveSheet->ClassNameIs("GsTabSheetSelectVersClass")) GsReadBibleTextData::GsSheetListVers = 0; //Jeśli to zakładka z listą wybranych wersetów,
																																																				 //globalny wskaźnik na zakładkę zostanie wyzerowany
		delete pActiveSheet; pActiveSheet = nullptr;
		pAction->Enabled = (this->PageControlBibleText->PageCount > 0);
		this->Act_EditChapter->Enabled = ((this->PageControlBibleText->PageCount > 0) && (dynamic_cast<GsTabSheetClass *>(pActiveSheet)));
		this->Act_OpenInWord->Enabled = this->Act_EditChapter->Enabled && this->_bIsWordInstalled;
		//Uaktywnienie przycisku wysyłania rozdziału mailem, gdy istnieje bierzący rozdział
		this->Act_MailChapt->Enabled = this->Act_EditChapter->Enabled;
		//---
		if((this->PageControlBibleText->PageCount == 0) && (this->PageControlTools->ActivePageIndex == enPageTools_Books)) //[02-11-2019]
		//Otwieranie zakładki z wyborem ksiąg, w wypadku, gdy żadna księga nie jest wczytana, i aktywną zakładką jest zakładka wyboru ksiąg
		{
			this->Act_ResizeWork->Checked = false;
			this->Act_ResizeWorkExecute(this->Act_ResizeWork);
		}
		if(this->PageControlBibleText->PageCount == 0) // Brak zakładek z tekstem
		{
			this->PageControlBibleText->Visible = false; //01-02-2020
			// W wypadku zamkniecia ostatniej zakładki, wskaźnik na pasku zadań zostaje wyzerowany
			this->TaskbarMain->ProgressValue = 0; //11-06-2023
		}
	}
	//Stan przycisku zmiany obszaru tekstu 12-04-2021
	this->Act_ResizeWork->Enabled = (this->PageControlBibleText->PageCount > 0);
	//Stan przycisku zapisu aktywnego rozdziału 07-04-2021
	this->Act_SaveChaptToHTML->Enabled = (this->PageControlBibleText->PageCount > 0);
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
	TFileSaveDialog	 *pFileSaveDialog	 = new TFileSaveDialog (this);
	if(!pFileSaveDialog) throw(Exception("Błąd inicjalizacji objektu TFileSaveDialog "));
	//---
	UnicodeString ustrTypesFile[] = {"Wszystkie pliki", "*.*", "Pliki typu html", "*.html"},
								ustrSelect;
	TFileTypeItem *pFileTypeItem = nullptr;
	pFileSaveDialog->Title = "Wybierz nazwę pliku do zapisu...";
	pFileSaveDialog->Options << fdoOverWritePrompt << fdoNoDereferenceLinks;
	pFileSaveDialog->DefaultExtension = ".html";
	pFileSaveDialog->OkButtonLabel = "Zapisz otwarty rozdział do pliku";

	for(int i=0; i<ARRAYSIZE(ustrTypesFile); i+=2)
	{
		pFileTypeItem = pFileSaveDialog->FileTypes->Add();
		pFileTypeItem->DisplayName = ustrTypesFile[i];
		pFileTypeItem->FileMask = ustrTypesFile[i+1];
	}

	if(pFileSaveDialog->Execute())
	{
		ustrSelect = pFileSaveDialog->FileName;
		GsReadBibleTextData::WriteCurrentSheetText(ustrSelect);
	}
	else
	{
		MessageBox(NULL, TEXT("Nie wybrałeś lokalizacji, ani nazwy do zapisu otwartego rozdziału, więc plik będzie zapisany pod domyślną nazwą i w domyślnej lokalizacji"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
		GsReadBibleTextData::WriteCurrentSheetText();
	}

	if(pFileSaveDialog) {delete pFileSaveDialog; pFileSaveDialog = nullptr;}
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
	pTSearchTextWindow->ShowModal();
	this->pGsSearchFavFilesClass->ReadDirectoryFavSearch();
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
	//Przeładowanie aplikacji po zminie ustawień o aktywnych tłumaczeniach

	if(GlobalVar::IsRunReload)
	{
		int iResult = MessageBox(NULL, TEXT("Została zmieniona konfiguracja dostępnych tłumaczeń. Potrzebny jest restart aplikacji, Czy chcesz zamknąć i ponownie otworzyć aplikacje, by zmiany zostały wprowadzone?"),
													 TEXT("Pytanie aplikacji"), MB_YESNO | MB_ICONWARNING | MB_TASKMODAL | MB_DEFBUTTON2);
		if(iResult == IDNO)
		{
			GlobalVar::IsRunReload = false;
			return;
		}
		//Sprawdzanie czy aplikacja do przeładowania istnieje i uruchomienie jej
		if(TFile::Exists(Gl_custrNameAppReload))
		{
			ShellExecute(NULL, L"open", Gl_custrNameAppReload.c_str(), NULL, GlobalVar::Global_custrGetExeDir.c_str(), SW_SHOW);
		}
	}
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
	TSelectVersWindow *pSelectVersWindow=nullptr;
	GsTabSheetClass *pGsTabSheetClass = dynamic_cast<GsTabSheetClass *>(this->PageControlBibleText->ActivePage);
	if(!pGsTabSheetClass) {pSelectVersWindow = new TSelectVersWindow(this);} //Brak zakładki z załadowaną księgą i rozdziałem
	//Jest zakładka z załadowaną księgą i rozdziałem, więc domyślnie startowym tekstem będzie pierwszy werset z załadowanej księgi i rozdziały,
	//w aktualnej zakładce, w oknie głównym. [23-10-2023]
	else {pSelectVersWindow = new TSelectVersWindow(this, pGsTabSheetClass->_ShucIndexBook, pGsTabSheetClass->_ShucIndexChapt, 1, true);}
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
//	TSchemeVersWindow *pTSchemeVersWindow = new TSchemeVersWindow(this);
//	if(!pTSchemeVersWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TSchemeVersWindow"));
//	pTSchemeVersWindow->ShowModal();
	TNewSchemeVersWindow *pNewSchemeVersWindow = new TNewSchemeVersWindow(this);
	if(!pNewSchemeVersWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TNewSchemeVersWindow"));
	pNewSchemeVersWindow->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_InfomationsExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Akcja wyświetlająca okno z informacjami o aplikacji (winietę) na pasku zadań
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
	TAllMultimediaView *pAllMultimediaView = new TAllMultimediaView(this);
	if(!pAllMultimediaView) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TAllMultimediaView"));
	pAllMultimediaView->ShowModal();
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
	//this->SplitViewMain->Opened = !pAction->Checked;
	if(pAction->Checked)
		this->PanelTools->Width = Global_WidthTabTools;
	else this->PanelTools->Width = 300;
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_OtherInfoTaskbarButtonExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Akcja umieszczona w TaskBarze, informująca o aktualnie wczytanym rozdziale na pasku zadań
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
	MessageBox(NULL, (UnicodeString("Niestety moduł pobierania aktualizacji został wyłączony ze względu na problemy z serwerem. ") +
			"Proszę o pobieranie pełnej paczki z pod adresu \"https://sourceforge.net/projects/moja-biblia-ng/\" \n" +
			"Po zamknięciu okienka, zostanie uruchomiona domyślna przeglądarka, z załadowaną stroną, do pobierania całej paczki z aplikacją."
			"Przepraszam za utrudnienia, ale nie wynikają one z mojej winy :(").c_str(),
			TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);

	ShellExecute(this->Handle, NULL , TEXT("https://sourceforge.net/projects/moja-biblia-ng/"), NULL, NULL, SW_SHOWNORMAL);
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
void __fastcall TMainBibleWindow::Act_MailChaptExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Wysłąnie emailem aktualnego rozdziału
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	UnicodeString ustrTextHTML;
	GsReadBibleTextData::GetTextHTMLCurrentSheet(ustrTextHTML);

	TSendingMailWindow *pTSendingMailWindow = new TSendingMailWindow(this, ustrTextHTML);
	if(!pTSendingMailWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TChapterEditWindow"));
	pTSendingMailWindow->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_ReadingPlanExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Plan czytania bibli
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	if(!GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_IsStartPlan, false))
	{
		MessageBox(NULL, TEXT("Brak aktywnego Planu czytania Pisma Świętego. Wybierz w ustawieniach programy Plan czytania, następnie wybierz datę jego rozpoczęcia i aktywuj go."),
			TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
		return;
	}
	TReadingPlanWindow *pTReadingPlanWindow = new TReadingPlanWindow(this);
	if(!pTReadingPlanWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TFastTipsWindow"));
	pTReadingPlanWindow->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_HistoryChaptersExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Okno histori otwieranych rozdziałów
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	THistoryOpenChaptersWindow *pHistoryOpenChaptersWindow = new THistoryOpenChaptersWindow(this, pAction);
	if(!pHistoryOpenChaptersWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna THistoryOpenChaptersWindow"));
	//pHistoryOpenChaptersWindow->ShowModal();
	pHistoryOpenChaptersWindow->Show();
	//pAction->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_OpenInWordExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Otwarcie wybranego rozdziału w Ms Wordzie
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	Variant vWDocuments, vWActiveDoc, vMApplication, vWWords, vWAdd, vWLast,
					vWRange, vMFont;
	int iStart=0, iStop=0;
	UnicodeString ustrAddressVers, ustrTextVers;
	const int wdRed=6;

	MyObjectVers *pMyOjectVers=nullptr;
	TForm *pMainForm = Application->MainForm;
	if(!pMainForm) throw(Exception("Nie można wyłuskać wskaźnika na główne okno"));

	THashedStringList *pHSListGetText = new THashedStringList();
	if(!pHSListGetText) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));

	GsReadBibleTextData::GetCurentListText(pHSListGetText);
	int iASize = pHSListGetText->Count; //Ilość wersetów (lini w liście)
	//Wskaźnik zaawansowania
	TProgressBar *pPBar = new TProgressBar(pMainForm);
	pPBar->Parent = pMainForm;
	pPBar->Width = 400; pPBar->Height = 30;
	pPBar->Left = pMainForm->ClientWidth / 2 - (pPBar->Width / 2);
	pPBar->Top = pMainForm->ClientHeight / 2 - (pPBar->Height / 2);
	pPBar->Max = iASize;

	vMApplication = Variant::CreateObject("Word.Application");
	vMApplication.OlePropertySet("Visible", (Variant)true);

	vWDocuments = vMApplication.OlePropertyGet("Documents");
	vWAdd = vWDocuments.OleFunction("Add");
	vWActiveDoc = vMApplication.OlePropertyGet("ActiveDocument");
	vWWords = vWActiveDoc.OlePropertyGet("Words");

	for(int i=0; i<iASize; ++i)
	{
		pPBar->Position = i;
		Application->ProcessMessages();
		pMyOjectVers = static_cast<MyObjectVers *>(pHSListGetText->Objects[i]);
		if(pMyOjectVers)
		{
			ustrAddressVers = pMyOjectVers->BookChaptVers;
			iStart = iStop;
			iStop += ustrAddressVers.Length();

			vWLast = vWWords.OlePropertyGet("Last");
			vWLast.OlePropertySet("Text", (Variant)ustrAddressVers);
			vWRange = vWActiveDoc.OleFunction("Range", iStart, iStop);

			vMFont = vWRange.OlePropertyGet("Font");
			vMFont.OleFunction("Reset");
			vMFont.OlePropertySet("Bold", (Variant)true);
			vMFont.OlePropertySet("ColorIndex", (Variant)wdRed);
			//---
			iStart = iStop;
			if(i<(iASize-1)) ustrTextVers = pHSListGetText->Strings[i] + "\n";
			else ustrTextVers = pHSListGetText->Strings[i];
			iStop += ustrTextVers.Length();

			vWLast = vWWords.OlePropertyGet("Last");
			vWLast.OlePropertySet("Text", (Variant)ustrTextVers);
			vWRange = vWActiveDoc.OleFunction("Range", iStart, iStop);
			vMFont = vWRange.OlePropertyGet("Font");
			vMFont.OleFunction("Reset");
		}
	}

	if(pHSListGetText) {delete pHSListGetText; pHSListGetText = nullptr;}
	if(pPBar) {delete pPBar; pPBar = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_SpecBooksExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Otwarcie wybranego okna z tłumaczeniami specjalistycznymi
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	TBooksSpecjalistWindow *pBooksSpecjalistWindow = new TBooksSpecjalistWindow(this);
	if(!pBooksSpecjalistWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TBooksSpecjalistWindow"));
	pBooksSpecjalistWindow->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_StrongDictionaryExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Otwarcie wybranego okna ze słownikiem grecko-hebrajsko-polskim
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	TStrongWindow *pStrongWindow = new TStrongWindow(this);
	if(!pStrongWindow) throw(Exception("Błąd inicjalizacji objektu, klasy, okna TStrongWindow"));
	pStrongWindow->Show();
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::Act_HelpVideoExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Pomoc video
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	ShellExecute(this->Handle, NULL , TEXT("https://www.youtube.com/channel/UCqx3U8EUzjAcwHOM4GNDWNw"), NULL, NULL, SW_SHOWNORMAL);
}
//-----------------------ZDARZENIA ZWIAZANE Z KONTROLKAMI--------------------
void __fastcall TMainBibleWindow::ToolButtSearchFavClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Zdarzenie zwiazane z przyciskiem na karcie ulubionych wyszukiwań
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TToolButton *pTButton = dynamic_cast<TToolButton *>(Sender);
	if(!pTButton) return;
	//---
	switch(pTButton->Tag)
	{
		case enTagSearchFav_DeleteFile: //200.Przycisk kasowania zaznaczonego pliku w zakładce ulubionych plików wyszukiwania
			this->pGsSearchFavFilesClass->DeleteSelectFile();
		break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMainBibleWindow::_OnSelectItemSearchFile(System::TObject* Sender, TListItem* Item, bool Selected)
/**
	OPIS METOD(FUNKCJI): //[15-10-2023]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsSearchFavFilesClass *pSelect = dynamic_cast<GsSearchFavFilesClass *>(Sender);
	if(!pSelect) return;
	//---
	if(Selected)
	{
		UnicodeString ustrTemp = TPath::ChangeExtension(pSelect->SelectFile, GlobalVar::Global_custrFileSearchInfoExtand);

		TMemIniFile *pIni = new TMemIniFile(ustrTemp, TEncoding::UTF8);
		if(!pIni) throw(Exception("Błąd inicjalizacji objektu TMemIniFile"));

		this->MemoInfosSearchFile->Lines->BeginUpdate();
		this->MemoInfosSearchFile->Clear(); //[17-10-2023]
		this->MemoInfosSearchFile->Lines->Add(Format("Szukane słowo: %s", ARRAYOFCONST(( pIni->ReadString(GlobalVar::GlobalInfoSearch_Header, GlobalVar::GlobalInfoSearch_Name, "Brak") ))));
		this->MemoInfosSearchFile->Lines->Add(Format("Tłumaczenie: %s", ARRAYOFCONST(( pIni->ReadString(GlobalVar::GlobalInfoSearch_Header, GlobalVar::GlobalInfoSearch_Translate, "Brak") ))));
		this->MemoInfosSearchFile->Lines->Add(Format("Nazwa zakresu wyszukiwania: %s", ARRAYOFCONST(( pIni->ReadString(GlobalVar::GlobalInfoSearch_Header, GlobalVar::GlobalInfoSearch_RangeName, "Brak") ))));
		this->MemoInfosSearchFile->Lines->Add(Format("Dokładny zakres wyszukiwania: %s", ARRAYOFCONST(( pIni->ReadString(GlobalVar::GlobalInfoSearch_Header, GlobalVar::GlobalInfoSearch_Range, "Brak") ))));
		this->MemoInfosSearchFile->Lines->Add(Format("Ilość wystąpień szukanego wyrażenia: %d", ARRAYOFCONST(( pIni->ReadInteger(GlobalVar::GlobalInfoSearch_Header, GlobalVar::GlobalInfoSearch_Count, 0) ))));
		this->MemoInfosSearchFile->Lines->EndUpdate();

		if(pIni) {delete pIni; pIni = nullptr;}
	}
}
//---------------------------------------------------------------------------

