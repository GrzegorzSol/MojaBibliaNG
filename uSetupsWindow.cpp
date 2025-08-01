﻿/*
	Klasa do obsługi okna wszystkich ustawień aplikacji
*/

#include <vcl.h>
#pragma hdrstop

#include "uSetupsWindow.h"
#include <System.IOUtils.hpp>
#include <System.StrUtils.hpp>
#include <DateUtils.hpp>
#include <sapi.h>
#include "MyBibleLibrary\MyBibleLibrary.h"
#include "MyBibleLibrary\GsReadBibleTextdata.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
*/
TSetupsWindow *SetupsWindow;
enum {enPageSetups_Layout, enPageSetup_Flags, enPageSetup_Paths, enPageSetup_OtherSetups, enPageSetup_Translates,
			enPageSetups_ReadingPlan, enPageSetups_SelectThemes,
			enSelectDirMulti_1, enSelectDirMulti_2, enSelectDirMulti_3,
			enSelectBackground, //[12-12-2023]
			enSetup_Save=50, enSetup_Return, enSetup_Cancel, enSetup_Help,
			//enTag_IsDisplaySplashScreen=20, enTag_IsRequestEnd, enTag_IsOnlyOne, enTag_IsAutoFindUpdate, enTag_IsLoadBooksOnInit,
			//Tagi dla przycisków i innych kontrolek
			enTagControl_ButtFontMain=100,
			enTagControl_ButtFontAdress,
			enTagControl_ButtFontNameTranslates,
			enTagControl_ButtDisplayselectTheme,
				//TSpinEdit
			enTagControl_SpinEdSizeMainFont,
			enTagControl_SpinEdSizeAdressFont,
			enTagControl_SpinEdSizeTranslatesFont,

			//Indeksy grafik ikon this->SW_ImgListSmallMain
			//Indeksy grafik ikon this->SW_ImgListMain
			//Indeksy grafik ikon this->SW_ImgListMainSmall

			//Indeksy grafik ikon this->SW_ImgListSmallMain
			enImage_SmallSelectDir=0, enImage_SmallSaveConfig, enImage_SmallCancel, enImage_SmallUndoSetup, enImage_SmallColors, enImage_SmallSelectTranslate,
			emImage_DisplaySelectTheme, //6
			//Indeksy grafik ikon this->SW_ImgListMainSmall
			enImage_ViewAplic=0, enImage_SetupFlags, enImage_Paths, enImage_OtherSetups, enImage_Translates, enImage_TypeTranslate, enImage_DescryptionTranslate,
			enImage_ReadingPlan, enImage_NumberDayPlan, enImage_SelectThemes,	 //9
			//Numery kolumn dodatkowych w ustawieniach tłumaczeń
			enColumn_TypeTranslate=0, enColumn_DescryptionTranslate,
			//Grupy tłumaczeń
			enGroup_PolCompleteTrans=0, enGroup_OrygTrans, enGroup_Count,
			//Tagi dla przycisków rozpoczęcia i przerwania Planu czytania Pisma Świętego
			enTagButt_StartPlan=200,
			//Nazwy kolumn przeglądu wybranego planu czytania biblii
			enNameColumnDisplaySelectPlay_NumberDay=0, enNameColumnDisplaySelectPlay_Text, enNameColumnDisplaySelectPlay_CountColumn,
			//Opisy przełączników na karcie przełączników, typu TToggleSwitch //[15-08-2023]
			enToggleCaptionOn_ToggleSwitchIsDisplayInfos=0,
			enToggleCaptionOff_ToggleSwitchIsDisplayInfos,

			enToggleCaptionOn_ToggleSwitchIsRequestClose,
			enToggleCaptionOff_ToggleSwitchIsRequestClose,

			enToggleCaptionOn_ToggleSwitchIsOneInstance,
			enToggleCaptionOff_ToggleSwitchIsOneInstance,

			enToggleCaptionOn_ToggleSwitchIsUpdatesOnStartup,
			enToggleCaptionOff_ToggleSwitchIsUpdatesOnStartup,

			enToggleCaptionOn_ToggleSwitchIsReopenSchets,
			enToggleCaptionOff_ToggleSwitchIsReopenSchets,

			enToggleCaptionOn_ToggleSwitchIsHintsOnStart,
			enToggleCaptionOff_ToggleSwitchIsHintsOnStart,

			enToggleCaptionOn_ToggleSwitchisInfosOnStatusBar,
			enToggleCaptionOff_ToggleSwitchisInfosOnStatusBar,

			enToggleCaptionOn_ToggleSwitchIsImageBgn,
			enToggleCaptionOff_ToggleSwitchIsImageBgn
		 };
const UnicodeString ustrColumnLViewTranslates[] = {"Plik tłumaczenia", "Typ tłumaczenia", "Opis tłumaczenia"},
										ustrGroups[] = {"Polskie kompletne tłumaczenia", "Tłumaczenia oryginalne i specjalistyczne. Nie można ich wyłączyć!"}, //[18-05-2024]
										//Czcionki i ich wysokości dla Planu czytania biblii
										ustrFontList[] = {"Arial", "Calibri", "Courier New", "DejaVu Sans", "Segoe UI", "Times New Roman", "Verdana"},
										ustrSizeFontList[] = {"8", "9", "10", "11", "12", "14", "16", "18", "20", "22", "24", "26"},
										//Nazwy kolumn przeglądu wybranego planu czytania biblii
										ustrNamesColumns[] = {"Dzień planu", "Tekst Pisma świetego do przeczytania"},
										//Opisy przełączników na karcie przełączników, typu TToggleSwitch //[15-08-2023]
										ustrCaptionToggles[] = {"Będzie wyświetlany ekran informacyjny podczas uruchamiania aplikacji.",
																						"Nie będzie wyświetlany ekran informacyjny podczas uruchamiania aplikacji.",

																						"Przed zamknięciem aplikacji, zapyta ona o zgodę.",
																						"Zamykanie aplikacji bez powiadamiania.",

																						"Dozwolona tylko jedna kopia aplikacji.",
																						"Możliwość otwierania wielu kopi aplikacji.",

																						"Sprawdzanie aktualizacji podczas jej uruchamiania.",
																						"Brak sprawdzania aktualizacji podczas startu aplikacji.",

																						"Po uruchomieniu aplikacji zostaną wczytane wszystkie zakładki, które były otwarte podczas jej zamykania.",
																						"Aplikacja uruchamia się bez jakich kolwiek otwartych zakładek z poprzednio wczytanym tekstem.",

																						"Szybkie podpowiedzi pojawia sią po otwarciu aplikacji.",
																						"Szybkie podpowiedzi nie pojawią się po otwarciu aplikacji.",

																						"Wyświetlanie informacji na pasku zadań, podczas jej uruchamiania.",
																						"Informacje nie będą wyświetlane na pasku zadań, podczas jej uruchamiania.",

																						"Podkładem pod główny tekst biblijny bedzie grafika domyślna",
																						"Podkładem pod główny tekst biblijny będzie jednolity kolor, wybierany z listy obok"
																						};

//---------------------------------------------------------------------------
__fastcall TSetupsWindow::TSetupsWindow(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->WebBrowserPreview->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą strony.
	//Hinty
	this->SW_ButGroupSections->Hint = "Grupy ustawień";
	this->SW_LEditPath1->Hint = Format("Ścieżka dostępu do katalogu z multimediami|Ścieżka dostępu do głównego katalogu z multimediami|%u", ARRAYOFCONST((enImage_SmallSelectDir)));
	this->SW_LEditPath2->Hint = Format("Ścieżka dostępu do katalogu z multimediami|Ścieżka dostępu do pierwszego, dodatkowego katalogu z multimediami|%u", ARRAYOFCONST((enImage_SmallSelectDir)));
	this->SW_LEditPath3->Hint = Format("Ścieżka dostępu do katalogu z multimediami|Ścieżka dostępu do drugiego, dodatkowego katalogu z multimediami|%u", ARRAYOFCONST((enImage_SmallSelectDir)));
	this->SW_ButtSelectDirMulti_1->Hint = Format("Wybór katalogu z multimediami|Główny katalog z multimediami|%u", ARRAYOFCONST((this->SW_ButtSelectDirMulti_1->ImageIndex)));
	this->SW_ButtSelectDirMulti_2->Hint = Format("Wybór katalogu z multimediami|Pierwszy, dodatkowy katalog z multimediami|%u", ARRAYOFCONST((this->SW_ButtSelectDirMulti_2->ImageIndex)));
	this->SW_ButtSelectDirMulti_3->Hint = Format("Wybór katalogu z multimediami|Drugi, dodatkowy katalog z multimediami|%u", ARRAYOFCONST((this->SW_ButtSelectDirMulti_3->ImageIndex)));
	this->SW_ButtSetupSave->Hint = Format("Zapis zmienionej konfiguracji||%u", ARRAYOFCONST((this->SW_ButtSetupSave->ImageIndex)));
	this->SW_ButtSetupCancel->Hint = Format("Anulowanie zmienionej konfiguracji||%u", ARRAYOFCONST((this->SW_ButtSetupCancel->ImageIndex)));
	this->ButtFontNameMainText->Hint = Format("Wybór głównej czcionki|Główna czcionka używana do wyświetlania tekstów wersetów w głównym oknie|%u", ARRAYOFCONST((this->ButtFontNameMainText->ImageIndex)));
	this->ButtFontNameAdress->Hint = Format("Wybór czcionki dla adresu wersetu|Czcionka do wyświetlania adresów wersetów w głównym oknie|%u", ARRAYOFCONST((this->ButtFontNameAdress->ImageIndex)));
	this->ButtFontNameTranslates->Hint = Format("Wybór czcionki dla nazwy tłumaczenia|Czcionka do wyświetlania nazwy tłumaczenia w głównym oknie|%u", ARRAYOFCONST((this->ButtFontNameTranslates->ImageIndex)));
	//Tagi

	//Pole tekstowe z wybranymi katalogami z multimediami
	this->SW_LEditPath1->Tag = enSelectDirMulti_1; this->SW_ButtSelectDirMulti_1->Tag = enSelectDirMulti_1;
	this->SW_LEditPath2->Tag = enSelectDirMulti_2; this->SW_ButtSelectDirMulti_2->Tag = enSelectDirMulti_2;
	this->SW_LEditPath3->Tag = enSelectDirMulti_3; this->SW_ButtSelectDirMulti_3->Tag = enSelectDirMulti_3;
	//Inne pola tekstowe
	this->SW_ButtSelectBackground->Tag =  enSelectBackground; //[12-12-2023]
	//Dolne przyciski
	this->SW_ButtSetupSave->Tag = enSetup_Save;
	this->SW_ButtSetupReturn->Tag = enSetup_Return;
	this->SW_ButtSetupCancel->Tag = enSetup_Cancel;
	this->SW_ButtSetupHelp->Tag = enSetup_Help;
	//Przyciski wyboru czcionki
	this->ButtFontNameMainText->Tag = enTagControl_ButtFontMain;
	this->ButtFontNameAdress->Tag = enTagControl_ButtFontAdress;
	this->ButtFontNameTranslates->Tag = enTagControl_ButtFontNameTranslates;
	//Kontrolka do ustawiania wielkości czcionek
	this->SpEditSizeMainFont->Tag = enTagControl_SpinEdSizeMainFont;
	this->SpEditSizeAdressFont->Tag = enTagControl_SpinEdSizeAdressFont;
	this->SpEditSizeTranslatesFont->Tag = enTagControl_SpinEdSizeTranslatesFont;
	//Inne przyciski
	this->SW_ButtDisplaySelectTheme->Tag = enTagControl_ButtDisplayselectTheme;
	//Ustawienia na karcie tematów
	if(TStyleManager::Enabled)
	{
		this->SW_LBoxSelectTheme->Items->AddStrings(TStyleManager::StyleNames); //Wczytanie tematów załadowanych do aplikacji
	}
	//Tagi dla przycisków rozpoczęcia i przerwania Planu czytania Pisma Świętego
	this->SpButtonStartPlan->Tag = enTagButt_StartPlan;
	//Dodawanie grup do objektu, typu TListView
	for(int i=0; i<enGroup_Count; i++)
	{
		TListGroup *pLGroup = this->SW_ListViewAllTranslates->Groups->Add();
		pLGroup->Header = ustrGroups[i];
	}
	//Dodawanie kolumn do objektu, typu TListView
	TListColumn	 *NewColumn;//=0;
	for(unsigned int iColumns=0; iColumns<ARRAYSIZE(ustrColumnLViewTranslates); iColumns++)
	{
		NewColumn = this->SW_ListViewAllTranslates->Columns->Add();
		NewColumn->Caption = ustrColumnLViewTranslates[iColumns];
		NewColumn->AutoSize = true;
		NewColumn->ImageIndex = enImage_Translates + iColumns;
	}
	//Tekst informacyjny na dole okna
	this->SW_STextInfo->Caption = UnicodeString("\tUwagi dotyczące zadziałanie ustawień.\n") +
		"  1. Ustawienie będzie obowiązywało po ponownym uruchomieniu aplikacji.\n" +
		"  2. Po zmianie tych parametrów, dopiero w nowo otwartej księdze, zaczną, one obowiązywać.";

	//Logo ustawień
	if(TFile::Exists(GlobalVar::Global_custrPathSetupsLogo))
	{
		TWICImage *pWICImage = new TWICImage();
		if(!pWICImage) throw(Exception("Błąd inicjalizacji objektu TWICImage"));
		pWICImage->LoadFromFile(GlobalVar::Global_custrPathSetupsLogo);
		this->SW_SetupsImageLogo->Picture->Assign(pWICImage);
		delete pWICImage; pWICImage = nullptr;
	}
	//Wstępne ustawienie na karcie ustawień czytania tekstu
	this->TrackBarSetRate->Min = SPVLIMITS::SPMIN_RATE;
	this->TrackBarSetRate->Max = SPVLIMITS::SPMAX_RATE;
	this->TrackBarSetVolume->Min = SPVLIMITS::SPMIN_VOLUME;
	this->TrackBarSetVolume->Max = SPVLIMITS::SPMAX_VOLUME;
	//Wstępne ustawieni na karcie tematów graficznych
	this->SW_ButtDisplaySelectTheme->Enabled =	this->SW_LBoxSelectTheme->ItemIndex > -1;
	//Inicjalizacja obsługi przełączników flag //[15-08-2023]
	this->_InitToggleSwitches();
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::FormClose(TObject *Sender, TCloseAction &Action)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TWICImage *pWICImage=nullptr;
	//---
	this->_SListOldConfig = new TStringList(); //Przechowywanie ustawień, podczas uruchomienia okna konfiguracji
	if(!this->_SListOldConfig) throw(Exception("Błąd funkcji TStringList"));
	//---
	this->_HSListViewAllTr = new THashedStringList(); //Tekst wszystkich dostępnych tłumaczeń, modelowego wersetu
	if(!this->_HSListViewAllTr) throw(Exception("Błąd funkcji THashedStringList"));
	//--- Zachowanie pierwotnych ustawień z bufora pliku ini, do TStringListy
	GlobalVar::Global_ConfigFile->GetStrings(this->_SListOldConfig);
	//---
	this->SW_PControlSelected->ActivePageIndex = enPageSetups_Layout;
	//Odczyt wszystkich ustawień aplikacji i stanu kontrolek zależnych od posczególnych parametrów odczytanych z konfiguracji
	this->_InitLViewDisplaySelectPlan();
	this->_ReadAllConfig();
	this->_DisplayPreview();
	//Wczytanie podglądu dla podkładu pod główny tekst
	try
	{
		try
		{
			//--- Wczytanie grafiki podkładu głównego tekstu(dopuszczalne jest jej brak)
			pWICImage = new TWICImage();
			if(!pWICImage) throw(Exception("Błąd inicjalizacji objektu TWICImage"));
			pWICImage->LoadFromFile(GlobalVar::Global_custrPathImageBackgroundMainText);
			this->SW_ImageBackground->Picture->Assign(pWICImage);
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
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::FormDestroy(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->_SListOldConfig) {delete this->_SListOldConfig; this->_SListOldConfig = nullptr;} //Przechowywanie ustawień, podczas uruchomienia okna konfiguracji
	if(this->_HSListViewAllTr) {delete this->_HSListViewAllTr; this->_HSListViewAllTr = nullptr;} //Tekst wszystkich dostępnych tłumaczeń, modelowego wersetu
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::_InitToggleSwitches()
/**
	OPIS METOD(FUNKCJI): Inicjalizacja obsługi przełączników flag //[15-08-2023]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	// Makro zmieniajace niektóre parametry w środowisku C++Builder v12.1 Athens //[30-08-2024]
	#if(__CODEGEARC__ == 0x0770)
	#endif

	this->ToggleSwitchIsDisplayInfos->StateCaptions->CaptionOn = ustrCaptionToggles[enToggleCaptionOn_ToggleSwitchIsDisplayInfos];
	this->ToggleSwitchIsDisplayInfos->StateCaptions->CaptionOff = ustrCaptionToggles[enToggleCaptionOff_ToggleSwitchIsDisplayInfos];

	this->ToggleSwitchIsRequestClose->StateCaptions->CaptionOn = ustrCaptionToggles[enToggleCaptionOn_ToggleSwitchIsRequestClose];
	this->ToggleSwitchIsRequestClose->StateCaptions->CaptionOff = ustrCaptionToggles[enToggleCaptionOff_ToggleSwitchIsRequestClose];

	this->ToggleSwitchIsOneInstance->StateCaptions->CaptionOn = ustrCaptionToggles[enToggleCaptionOn_ToggleSwitchIsOneInstance];
	this->ToggleSwitchIsOneInstance->StateCaptions->CaptionOff = ustrCaptionToggles[enToggleCaptionOff_ToggleSwitchIsOneInstance];

	this->ToggleSwitchIsUpdatesOnStartup->StateCaptions->CaptionOn = ustrCaptionToggles[enToggleCaptionOn_ToggleSwitchIsUpdatesOnStartup];
	this->ToggleSwitchIsUpdatesOnStartup->StateCaptions->CaptionOff = ustrCaptionToggles[enToggleCaptionOff_ToggleSwitchIsUpdatesOnStartup];

	this->ToggleSwitchIsReopenSchets->StateCaptions->CaptionOn = ustrCaptionToggles[enToggleCaptionOn_ToggleSwitchIsReopenSchets];
	this->ToggleSwitchIsReopenSchets->StateCaptions->CaptionOff = ustrCaptionToggles[enToggleCaptionOff_ToggleSwitchIsReopenSchets];

	this->ToggleSwitchIsHintsOnStart->StateCaptions->CaptionOn = ustrCaptionToggles[enToggleCaptionOn_ToggleSwitchIsHintsOnStart];
	this->ToggleSwitchIsHintsOnStart->StateCaptions->CaptionOff = ustrCaptionToggles[enToggleCaptionOff_ToggleSwitchIsHintsOnStart];

	this->ToggleSwitchisInfosOnStatusBar->StateCaptions->CaptionOn = ustrCaptionToggles[enToggleCaptionOn_ToggleSwitchisInfosOnStatusBar];
	this->ToggleSwitchisInfosOnStatusBar->StateCaptions->CaptionOff = ustrCaptionToggles[enToggleCaptionOff_ToggleSwitchisInfosOnStatusBar];

	this->ToggleSwitchIsImageBgn->StateCaptions->CaptionOn = ustrCaptionToggles[enToggleCaptionOn_ToggleSwitchIsImageBgn];
	this->ToggleSwitchIsImageBgn->StateCaptions->CaptionOff = ustrCaptionToggles[enToggleCaptionOff_ToggleSwitchIsImageBgn];
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::_InitLViewDisplaySelectPlan()
/**
	OPIS METOD(FUNKCJI): Inicjalizacja parametrów dla listy przeglądu wybranego planu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListColumn *NewColumn=nullptr;
	//Dodawanie kolumn
	for(unsigned int iColumns=0; iColumns<enNameColumnDisplaySelectPlay_CountColumn; iColumns++)
	{
		NewColumn = this->LViewDisplayselectPlan->Columns->Add();
		NewColumn->Caption = ustrNamesColumns[iColumns];
		if(iColumns > 0) NewColumn->AutoSize = true;
		//NewColumn->ImageIndex = 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::_DisplayPreview()
/**
	OPIS METOD(FUNKCJI): Wyświetlenie podgladu tekstu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI): //[24-09-2023]
*/
{
	int //Kolory
			iColorFavVers = this->SW_ColorBoxFavorities->Selected,
			iColorCommentVers = this->SW_ColorBoxComment->Selected,
			iColorBackgroundText = this->SW_ColorBoxBackground->Selected,
			iColorNameFullTranslate = this->SW_ColorBoxNameTranslate->Selected,
			iColorAdressFullTranslates = this->SW_ColorBoxColorAdressFulltranslates->Selected,
			iColorBackgroundMarkComment = this->SW_ColorBackgroundMarkerComment->Selected,
			iColorBorderFavoritiesVers = this->SW_ColorBoxBorderFavoritiesVers->Selected,
			//Kolor nazwy oryginalnego tłumaczenia
			//iColorOryginalTranslates = this->SW_ColorBoxColorOrygTr->Selected,
			//iColorAdressOryg = this->SW_ColorBoxAdressOryg->Selected,
			//iColorNameOryginalTranslate = this->SW_ColorBoxColorNameOrygTran->Selected,
			//Other
			iSizeFontMain = this->SpEditSizeMainFont->Value,
			iSizeAdressFont = this->SpEditSizeAdressFont->Value,
			iSizeTranslatesFont = this->SpEditSizeTranslatesFont->Value;

	UnicodeString ustr_FontNameMain = this->ButtFontNameMainText->Caption,
								ustr_FontNameAdress = this->ButtFontNameAdress->Caption,
								ustr_FontNameTranslators = this->ButtFontNameTranslates->Caption;

	UnicodeString		//Styl dla głównego tekstu
								_GlobalText = Format(".styleText {color: #000000;font-size:%upt;font-family:%s;}\n",
									ARRAYOFCONST((iSizeFontMain, ustr_FontNameMain))),
									//Styl dla ulubionych wersetów
								_FavoriteStyle = Format(".styleFavorite {background-color: %s;border: 1px solid %s;}\n",
									ARRAYOFCONST((RGBToWebColorStr(iColorFavVers), RGBToWebColorStr(iColorBorderFavoritiesVers)))),
								//_FavoriteStyle = Format(".styleFavorite {border: 3px solid %s}", ARRAYOFCONST((RGBToWebColorStr(iColorFavVers)))),
									//Styl .css dla zaznaczania wersetów z komentarzem, podkład i kolor znacznika.
								_CommentStyle = Format( ".styleComment {font-family:%s;font-weight: 900; text-decoration: underline; background-color: %s ;color: %s;}\n",
									ARRAYOFCONST((ustr_FontNameMain, RGBToWebColorStr(iColorBackgroundMarkComment), RGBToWebColorStr(iColorCommentVers)))),
									//Kolor podkładu głównego tekstu
								_BackGroundMainText = Format("body {background-color: %s;\n\tfont-size:%upt;\n\tfont-family:%s;}\n",
									ARRAYOFCONST((RGBToWebColorStr(iColorBackgroundText), iSizeFontMain, ustr_FontNameMain))),
								//_BackGroundMainText = Format("body {background-color: %s;\n\tbackground-image: url(\"%s\");\n\tbackground-repeat: no-repeat;\n\tfont-size:%upt;\n\tfont-family:%s;}\n",
								//	ARRAYOFCONST((RGBToWebColorStr(iColorBackgroundText), ustrTemp, iSizeFontMain, ustr_FontNameMain))), //[01-09-2023]
									//Kolor nazwy przekładu, dla pełnego tłumaczenia
								_ColorNameFullTranslate = Format(".styleTranslates {color: %s;font-size:%upt;font-family:%s;}\n", ARRAYOFCONST((RGBToWebColorStr(iColorNameFullTranslate), iSizeTranslatesFont, ustr_FontNameTranslators))),
									//Kolor adresu dla pełnych tłumaczeń
								_ColorAdressFullTranslates = Format(".styleColorAdressTranslates {color: %s; font-size:%upt;font-family:%s;}\n",
									ARRAYOFCONST((RGBToWebColorStr(iColorAdressFullTranslates), iSizeAdressFont, ustr_FontNameAdress)));

	UnicodeString HTMLHeaderText = UnicodeString("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\" \"http://www.w3.org/TR/html4/loose.dtd\">\n") +
																							 "<html>\n<head>\n" +
																							 "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n" +
																							 GsReadBibleTextData::GsHTMLTitle + "\n" + //[03-08-2023]
																							 "<style type=\"text/css\">\n" +
																							 _ColorAdressFullTranslates +
																							 _ColorNameFullTranslate +
																							 _GlobalText +
																							 ".styleNoTranslate {color: #FF0000;font-size:16pt;font-family:Times New Roman;}\n" + //Informacja o braku księgi
																							 _FavoriteStyle + //Kolor zaznaczenie ulubionego wersetu
																							 _CommentStyle + //Kolor zaznaczania wersetu z komentarzem
																							 _BackGroundMainText +
																							 "</style>\n</head>\n\n<body>\n";
	MyObjectVers *pMyOjectVers=nullptr;
	UnicodeString _Style_FavoriteStyle = "", //Styl zaznaczania ulubionego wersetu
								_Style_CommentStyle = "",	 //Styl zaznaczania wersetu skomentowanego
								_StyleFav_End = "",
								_StyleComm_End = "",
								//---
								DisplaySelectNameTranslate; //Nazwa tlumaczenia wyłuskana z GsReadBibleTextItem->NameTranslate.

	THashedStringList *_pTempHSListViewAllTr = new THashedStringList(); //Tekst wszystkich dostępnych tłumaczeń, modelowego wersetu
	if(!_pTempHSListViewAllTr) throw(Exception("Błąd funkcji THashedStringList"));
	TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true); //Allokacja strumienia dla tekstu html
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));

	GsReadBibleTextData::GetSelectVerAllTranslates(44, 5, 1, _pTempHSListViewAllTr);
	pStringStream->WriteString(HTMLHeaderText); //Zapis nagłówka kodu html do strumienia

	try
	{
		for(int i=0; i<_pTempHSListViewAllTr->Count; i++)
		{
			pMyOjectVers = static_cast<MyObjectVers *>(_pTempHSListViewAllTr->Objects[i]);
			if(!pMyOjectVers) throw(Exception("Błąd odczytu objektu MyObjectVers"));

			GsReadBibleTextItem *pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(i); //Wyłuskanie wskaźnika GsReadBibleTextItem konkretnego tłumaczenia, w celu sprawdzenia typu tłumaczenia
			DisplaySelectNameTranslate = pGsReadBibleTextItem->NameTranslate;

			if(i==0) //Będzie wyswietlony text ulubiony i z komentarzem
			{
				_Style_FavoriteStyle = "<div class=\"styleFavorite\">\n"; //Styl zaznaczania ulubionego wersetu
				_StyleFav_End = "</div>\n";
				_Style_CommentStyle = "<span class=\"styleComment\">C";	 //Styl zaznaczania wersetu skomentowanego
				_StyleComm_End = "</span>\n";
			}
			else
			{
				_Style_FavoriteStyle = ""; //Styl zaznaczania ulubionego wersetu
				_StyleFav_End = "";
				_Style_CommentStyle = "";	 //Styl zaznaczania wersetu skomentowanego
				_StyleComm_End = "";
			}
			if(pGsReadBibleTextItem->enTypeTranslate == enTypeTr_Full) //[20-04-2024] //[17-08-2024]Pełne polskie tłumaczenie
			{
					pStringStream->WriteString(Format(UnicodeString("<p>\n") +
					_Style_FavoriteStyle +
					"%s" +	//_Style_CommentStyle
					"%s" + "<span class=\"styleColorAdressTranslates\">\n\t" + //_StyleComm_End,
					"%s\n</span>\n"+ //pMyOjectVers->BookChaptVers,
					"<span class=\"styleText\">\n\t" + "%s\n</span>\n",
					ARRAYOFCONST((_Style_CommentStyle,
												_StyleComm_End,
												pMyOjectVers->BookChaptVers,
												_pTempHSListViewAllTr->Strings[i]))));
				//Nazwa tłumaczenia
				pStringStream->WriteString(Format(UnicodeString("<span class=\"styleTranslates\">\n\t%s\n</span>\n"),
					ARRAYOFCONST((DisplaySelectNameTranslate))));
				pStringStream->WriteString(_StyleFav_End); //[14-04-2024] //[17-08-2024]
				pStringStream->WriteString("</p>\n");
			}
			else
			{

			}
			pStringStream->WriteString("<!---- Kolejny werset ---->\n"); //[20-04-2024]
		}
		pStringStream->WriteString("</body>\n</html>\n");
		pStringStream->Position = 0;

		IPersistStreamInit *psi;
		_di_IStream sa(*(new TStreamAdapter(pStringStream, soReference)));
		if(SUCCEEDED(this->WebBrowserPreview->Document->QueryInterface(IID_IPersistStreamInit, (void **)&psi)))
			{psi->Load(sa);}
	}
	__finally
	{
		if(pStringStream) {delete pStringStream; pStringStream = nullptr;}
		if(_pTempHSListViewAllTr) {delete _pTempHSListViewAllTr; _pTempHSListViewAllTr = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::_DisplaySelectPlan()
/**
	OPIS METOD(FUNKCJI): Wyswietlenie wybranego planu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	UnicodeString ustrPathFileReadingPlan, ustrTemp, ustrItemText;
	const UnicodeString custrSeparator = "|";
	THashedStringList *pHSList=nullptr;
	TListItem *pItem=nullptr;
	int iLengthPair;
	const int ciOneChapt=6, ciTwoChapt=12, ciFullAdres=18;

	try
	{
		try
		{
			pHSList = new THashedStringList();
			if(!pHSList) throw(Exception("Błąd funkcji THashedStringList"));
			this->LViewDisplayselectPlan->Items->BeginUpdate();
			this->LViewDisplayselectPlan->Clear();
			if(this->CBoxSelectPlan->ItemIndex > -1)
			{
				ustrPathFileReadingPlan = TPath::Combine(GlobalVar::Global_custrPathAllReadingPlan, this->CBoxSelectPlan->Text);

				if(!TFile::Exists(ustrPathFileReadingPlan)) throw(Exception("Brak pliku z wybranym planem czytania biblii"));
				pHSList->LoadFromFile(ustrPathFileReadingPlan, TEncoding::UTF8);
				for(int i=1; i<pHSList->Count; i++)
				{
					pItem = this->LViewDisplayselectPlan->Items->Add();
					pItem->Caption = UnicodeString(i);

					TStringDynArray sda = SplitString(pHSList->Strings[i], custrSeparator); //Ilość par rozdzialona znakiem custrSeparator
					for(int si=0; si<sda.Length; si++)
					{
						ustrTemp = ReplaceText(UnicodeString(sda[si]), " ", ""); //Usunięcie wszystkich spacji
						iLengthPair = ustrTemp.Length(); //Długość pary
						if(si > 0) ustrItemText += "; "; //Gdy istnieje kolejna para dodaj przed nią "; "
						//Formatowanie wyświetlania zakresów w liście wczytanego planu
						switch(iLengthPair)
						//Formatowanie wyświetlania zależnie od dłygości zcalonej pary (pozbawionej spacji zakresu)
						{
							case ciOneChapt:
								ustrItemText += Format("%s %d", ARRAYOFCONST((AppCTable_InfoAllBooks[ustrTemp.SubString(1, 3).ToInt()-1].ShortNameBook,	 ustrTemp.SubString(4, 3).ToInt() )));
								break;

							case ciTwoChapt:
								ustrItemText += Format("%s %d - %s %d",
									ARRAYOFCONST((AppCTable_InfoAllBooks[ustrTemp.SubString(1, 3).ToInt()-1].ShortNameBook, ustrTemp.SubString(4, 3).ToInt(),
										AppCTable_InfoAllBooks[ustrTemp.SubString(7, 3).ToInt()-1].ShortNameBook, ustrTemp.SubString(10, 3).ToInt())));
								break;

							case ciFullAdres:
								ustrItemText += Format("%s %d:%d - %s %d:%d",
									ARRAYOFCONST((AppCTable_InfoAllBooks[ustrTemp.SubString(1, 3).ToInt()-1].ShortNameBook, ustrTemp.SubString(4, 3).ToInt(), ustrTemp.SubString(7, 3).ToInt(),
										AppCTable_InfoAllBooks[ustrTemp.SubString(10, 3).ToInt()-1].ShortNameBook, ustrTemp.SubString(13, 3).ToInt(), ustrTemp.SubString(16, 3).ToInt() )));
								break;

							default:
								#if defined(_DEBUGINFO_)
									GsDebugClass::WriteDebug(Format("Linia: %d", ARRAYOFCONST((i+1))));
								#endif
								throw(Exception("Niewłaściwy format pliku z wybranym planem"));
						}

					}
					pItem->SubItems->Add(ustrItemText);
					ustrItemText = ""; //Po dodaniu pozycji wyczyszczenie zawartości
				}
			}
			this->LViewDisplayselectPlan->Items->EndUpdate();
		}
		catch(Exception &e)
		{
			MessageBox(NULL, e.Message.c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{
		if(pHSList) {delete pHSList; pHSList = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::_ReadAllConfig()
/**
	OPIS METOD(FUNKCJI): Odczyt wszystkich ustawień aplikacji i stanu kontrolek zależnych od posczególnych parametrów odczytanych z konfiguracji
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Ścierzki dostępu do katalogów z multimediami
	this->SW_LEditPath1->Text = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM1, "");
	this->SW_LEditPath2->Text = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM2, "");
	this->SW_LEditPath3->Text = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM3, "");
  this->SW_LEditPathBackGround->Text = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_OthersSection,
		GlobalVar::GlobalIni_GrahicsBackground, GlobalVar::Global_custrPathBackgroundWindow); //[12-12-2023]
	//Sprawdzenie poprawności ścieżki dostępu
	this->_VaidatePathMedia(this->SW_LEditPath1, GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM1);
	this->_VaidatePathMedia(this->SW_LEditPath2, GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM2);
	this->_VaidatePathMedia(this->SW_LEditPath3, GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM3);
	//Odczyt flag [15-08-2023] - [16-08-2023]
	this->ToggleSwitchIsDisplayInfos->State = static_cast<TToggleSwitchState>(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsDisplaySplashStart, true));
	this->ToggleSwitchIsRequestClose->State = static_cast<TToggleSwitchState>(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsRequestEnd, true));
	this->ToggleSwitchIsOneInstance->State = static_cast<TToggleSwitchState>(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsOnlyOne, true));
	this->ToggleSwitchIsUpdatesOnStartup->State = static_cast<TToggleSwitchState>(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsAutoFindUpdate, true));
	this->ToggleSwitchIsReopenSchets->State = static_cast<TToggleSwitchState>(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsLoadBooksOnInit, true));
	this->ToggleSwitchIsHintsOnStart->State = static_cast<TToggleSwitchState>(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsTipsWindowStart, true));
	this->ToggleSwitchisInfosOnStatusBar->State = static_cast<TToggleSwitchState>(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsDisplayStartInfoTray, true));
	this->ToggleSwitchIsImageBgn->State = static_cast<TToggleSwitchState>(GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsDisplayBackgroundImage, false));
  //Widoczność lub nie, w pomniejszeniu podkładu pod główny tekst, zależnie od odczytanej konfiguracji
	this->SW_ImageBackground->Visible = (this->ToggleSwitchIsImageBgn->State == tssOn); //[24-04-2024]
	//Kolory
		//Kolor zaznaczania ulubionych wersetów
	this->SW_ColorBoxFavorities->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorFavoritesVers, clYellow);
		//Kolor wersetu z komentarzem
	this->SW_ColorBoxComment->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorCommentVers, clLime);
		//Kolor podkładu
	this->SW_ColorBoxBackground->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorBackgroundText, clSkyBlue);
		//Kolor nazwy tłumaczenia
	this->SW_ColorBoxNameTranslate->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorNameFullTranslates, clFuchsia);
		//Kolor adresu wersetów, dla pełnych tłumaczeń
	this->SW_ColorBoxColorAdressFulltranslates->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorAdressVersFullTranslates, clRed);
		//Kolor podkładu dla znacznika, istnienia komentarza dla wersetu
	this->SW_ColorBackgroundMarkerComment->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorBackgroundMarkerComment, clYellow);
		//Kolor ramki naokoło ulubionego wersetu
	this->SW_ColorBoxBorderFavoritiesVers->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorBorderFavoritiesVers, clRed);
	//Others
		//Wielkość głównej czcionki tekstu wersetu
	this->SpEditSizeMainFont->Value = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_OtherSizeFontMain, 12);
		//Wielkość czcionki, adresu wersetu
	this->SpEditSizeAdressFont->Value = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_OtherSizeFontAdress, 9);
		//Wielkość czcionki nazwy tłumaczeń
	this->SpEditSizeTranslatesFont->Value = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_OtherSizeFontNameTranslators, 9);
			//Czcionki
	this->ButtFontNameMainText->Caption = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_FontNameMain, "Times New Roman");
	this->ButtFontNameMainText->Font->Name = this->ButtFontNameMainText->Caption;
	this->ButtFontNameMainText->Font->Size = this->SpEditSizeMainFont->Value;
	this->ButtFontNameAdress->Caption = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_FontNameAdress, "Times New Roman");
	this->ButtFontNameAdress->Font->Name = this->ButtFontNameAdress->Caption;
	this->ButtFontNameAdress->Font->Size = this->SpEditSizeAdressFont->Value;
	this->ButtFontNameTranslates->Caption = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_FontNameTranslators, "Times New Roman");
	this->ButtFontNameTranslates->Font->Name = this->ButtFontNameTranslates->Caption;
	this->ButtFontNameTranslates->Font->Size = this->SpEditSizeTranslatesFont->Value;
	//Lista tłumaczeń wyłączonych z wyświetlania
	TStringList *pSListExcludeTrans = new TStringList();
	if(!pSListExcludeTrans) throw(Exception("Błąd inicjalizacji objektu TStringList"));
	//Odczyt z pliku ini, tłumaczeń wykluczonych
	pSListExcludeTrans->CommaText = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_TranslatesSection_Main, GlobalVar::GlobalIni_ExcludeTranslates, "");
	//Dodawanie ścieżek dostępu do wszystkich tłumaczeń
	UnicodeString ustrNameTranslate;
	GsReadBibleTextItem *pGsReadBibleTextItem = nullptr;
	for(int i=0; i<GlobalVar::SDirTranslatesList.Length; i++)
	{
		TListItem *NewItem = this->SW_ListViewAllTranslates->Items->Add();
		NewItem->Caption = TPath::GetFileName(GlobalVar::SDirTranslatesList[i]);
		//Jeśli tłumaczenia nie ma na liście tłumaczeń wykluczonych, to go zaznacz
		NewItem->Checked = pSListExcludeTrans->IndexOf(TPath::GetFileName(GlobalVar::SDirTranslatesList[i])) == -1; //Tłumaczenia nie ma na liście tłumaczeń wykluczonych
		NewItem->ImageIndex = enPageSetup_Translates;
		//--- Typ tłumaczenia
		if(TPath::GetExtension(NewItem->Caption) == GsReadBibleTextData::GsExtendNoAsteriskFileTranslateFull)
		{
			NewItem->SubItems->Add("Polskie tłumaczenie kompletne");
			NewItem->GroupID = enGroup_PolCompleteTrans;
		}
		else if(TPath::GetExtension(NewItem->Caption) == GsReadBibleTextData::GsExtendNoAsteriskFileTranslateGrecOrg)
		{
			NewItem->SubItems->Add("Greckie tłumaczenie");
			NewItem->GroupID = enGroup_OrygTrans;
		}
		else if(TPath::GetExtension(NewItem->Caption) == GsReadBibleTextData::GsExtendNoAsteriskFileTranslateHbrOrg)
		{
			NewItem->SubItems->Add("Hebrajskie tłumaczenie");
			NewItem->GroupID = enGroup_OrygTrans;
		}
		else {NewItem->SubItems->Add("");}
		NewItem->SubItemImages[enColumn_TypeTranslate] = enImage_TypeTranslate;
		//--- Zwraca nazwę tłumaczenia niezależnie od jego statusu (aktywny, lub nie) //[09-12-2023] [31-05-2024]
		pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(i);
		if(pGsReadBibleTextItem)
		{
//			#if defined(_DEBUGINFO_)
//				GsDebugClass::WriteDebug(Format("%d - %s", ARRAYOFCONST(( i,  pGsReadBibleTextItem->NameTranslate))));
//			#endif
			ustrNameTranslate = pGsReadBibleTextItem->NameTranslate;
		}

		NewItem->SubItems->Add(ustrNameTranslate);
//    #if defined(_DEBUGINFO_)
//			GsDebugClass::WriteDebug(Format("ustrNameTranslate: %s", ARRAYOFCONST((ustrNameTranslate))));
//		#endif
		NewItem->SubItemImages[enColumn_DescryptionTranslate] = enImage_DescryptionTranslate;
		//--- Tworzenie listy dostępnych tłumaczeń dla planu czytania biblii. Dostępne sa tylko polskie, pełne tłumaczenia.
		if(TPath::GetExtension(NewItem->Caption) == GsReadBibleTextData::GsExtendNoAsteriskFileTranslateFull)
			{this->CBoxSelectTranslate->AddItem(Format("%s - %s", ARRAYOFCONST((NewItem->Caption, ustrNameTranslate))), 0);}
	}
	if(pSListExcludeTrans) {delete pSListExcludeTrans; pSListExcludeTrans = nullptr;}
	//--- Wybór tłumaczenia, które bedzie uzywane dla słownika i konkordancji grecko-polskiej [02-06-2024]
	UnicodeString ustrSelectTransDictCord = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_TranslatesSection_Main,
		GlobalVar::GlobalIni_SelectTranslateForDictConcord, GlobalVar::Global_DefaultNameTranslateToDictionary);
	for(int i=0; i<GlobalVar::SDirTranslatesList.Length; i++)
	{
    //--- Zwraca nazwę tłumaczenia niezależnie od jego statusu (aktywny, lub nie) //[09-12-2023] [31-05-2024] [02-06-2024]
		pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(i);
		if(pGsReadBibleTextItem)
		{
			if((pGsReadBibleTextItem->enTypeTranslate == enTypeTr_Greek) &&
				 (pGsReadBibleTextItem->NameTranslate.Pos("LXX") == 0)) // [03-06-2024]

			{
				this->SW_RGroupSelectTransDict->Items->Add(pGsReadBibleTextItem->NameTranslate);
				if(pGsReadBibleTextItem->NameTranslate == ustrSelectTransDictCord)
					{this->SW_RGroupSelectTransDict->ItemIndex = this->SW_RGroupSelectTransDict->Items->Count - 1;}
			}
    }
	}
	//--- Planu czytania biblii
		//--- Odczyt planów
	TStringDynArray SDirReadingPlanList = TDirectory::GetFiles(GlobalVar::Global_custrPathAllReadingPlan, "*" +GlobalVar::Global_ustrFileReadingPlanExtend, 0);
	this->CBoxSelectPlan->Items->BeginUpdate();
	for(int i=0; i<SDirReadingPlanList.Length; i++)
	{
		this->CBoxSelectPlan->AddItem(TPath::GetFileName(SDirReadingPlanList[i]), 0);
	}
	this->CBoxSelectPlan->Items->EndUpdate();
		//--- Wybrany plan czytania
	this->CBoxSelectPlan->Text = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_SelectPlan, "");
	this->CBoxSelectPlan->ItemIndex = this->CBoxSelectPlan->Items->IndexOf(this->CBoxSelectPlan->Text);
	if(this->CBoxSelectPlan->ItemIndex > -1) this->_InfoStartStopPlan();
		//--- Odczyt wybranego tłumaczenia dla Planu czytania biblii z konfiguracji
	this->CBoxSelectTranslate->Text = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_TranslateRPlan, "bwa.pltmb - Biblia Warszawska");
	this->CBoxSelectTranslate->ItemIndex = this->CBoxSelectTranslate->Items->IndexOf(this->CBoxSelectTranslate->Text);
	this->_DisplaySelectPlan();
		//--- Lista czcionek dla planu czytania biblii
	this->CBoxSelectFontReadingPlan->Text = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_FontPlan, "Times New Roman");
	for(int i=0; i<ARRAYSIZE(ustrFontList); i++)
	{
		this->CBoxSelectFontReadingPlan->AddItem(ustrFontList[i], 0);
	}
	this->CBoxSelectFontReadingPlan->ItemIndex = this->CBoxSelectFontReadingPlan->Items->IndexOf(this->CBoxSelectFontReadingPlan->Text);
		//--- Wielkość czcionek
	this->CBoxSelectSizeFontPlan->Text = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_SizeFontPlan, "16");
	for(int i=0; i<ARRAYSIZE(ustrSizeFontList); i++)
	{
		this->CBoxSelectSizeFontPlan->AddItem(ustrSizeFontList[i], 0);
	}
	this->CBoxSelectSizeFontPlan->ItemIndex = this->CBoxSelectSizeFontPlan->Items->IndexOf(this->CBoxSelectSizeFontPlan->Text);
		//--- Data rozpoczęcia planu
	this->SpButtonStartPlan->Down = GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_IsStartPlan, false);
	//if(this->SpButtonStartPlan->Down)
			//Wybór daty mozliwy tylko wtedy gdy plan nieaktywny, czyli this->SpButtonStartPlan->Down = false
	this->DateTimePickerSelectStartDatePlan->Enabled = !this->SpButtonStartPlan->Down;
	this->DateTimePickerSelectStartDatePlan->Date = GlobalVar::Global_ConfigFile->ReadDate(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_StartDate, TDateTime::CurrentDate());
	//--- Parametry mowy
	this->TrackBarSetRate->Position = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_SetRate, -2);
	this->TrackBarSetVolume->Position = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_SetVolume, 100);
	//--- Parametry styli aplikacji
	UnicodeString ustrSelectStyle = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_SelectStyleName, GlobalVar::Global_DefaultStyleName);
	this->SW_LBoxSelectTheme->ItemIndex = this->SW_LBoxSelectTheme->Items->IndexOf(ustrSelectStyle);
	if(this->SW_LBoxSelectTheme->ItemIndex == -1)
	//Jeśli nie ma takiego stylu na liście, znajdowany jest styl domyślny
	{
		this->SW_LBoxSelectTheme->ItemIndex = this->SW_LBoxSelectTheme->Items->IndexOf(GlobalVar::Global_DefaultStyleName);
	}
	this->SW_ButtSetups_Click(this->SW_ButtDisplaySelectTheme);
  this->_bIsStart = false; //Koniec uruchamiania listy przekładów
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::_VaidatePathMedia(TLabeledEdit *pLEditPath, UnicodeString ustrSection, UnicodeString ustrkey) //30-03-2021
/**
	OPIS METOD(FUNKCJI): Niewłaściwa ścierzka dostępu do katalogu z mediami
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(pLEditPath->Text.IsEmpty()) return;
	//---
	if(!TDirectory::Exists(pLEditPath->Text))
	{
		UnicodeString ustrPathError = Format("Ścieżka dostępu: %s jest nie właściwa. Prawdopodobnie wybrany katalog nie istnieje! Proszę wybrać istniejący katalog.", ARRAYOFCONST((pLEditPath->Text)));
		MessageBox(NULL, ustrPathError.c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		pLEditPath->Text= "";
		GlobalVar::Global_ConfigFile->WriteString(ustrSection, ustrkey, "");
	}
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::_WriteAllConfig()
/**
	OPIS METOD(FUNKCJI): Zapis wszystkich ustawień aplikacji
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Zapis ścierzek dostępu
	if(!this->SW_LEditPath1->Text.IsEmpty())
		{GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM1, this->SW_LEditPath1->Text);}
	if(!this->SW_LEditPath2->Text.IsEmpty())
		{GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM2, this->SW_LEditPath2->Text);}
	if(!this->SW_LEditPath3->Text.IsEmpty())
		{GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM3, this->SW_LEditPath3->Text);}
	if(!this->SW_LEditPathBackGround->Text.IsEmpty())
	{
    //[12-12-2023]
		GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_GrahicsBackground, this->SW_LEditPathBackGround->Text);
		TForm *pMainWindow = Application->MainForm;
		TWICImage *pWICImage=nullptr;

		try
		{
			try
			{
				pWICImage = new TWICImage();
				if(!pWICImage) throw(Exception("Błąd inicjalizacji objektu TWICImage"));
				if(pMainWindow)
				{
					TComponent *pComponent=nullptr;
					for(int i=0; i<pMainWindow->ComponentCount; ++i)
					{
						pComponent = pMainWindow->Components[i];
						if(pComponent->ClassNameIs("TImage"))
						{
							TImage *pImage = dynamic_cast<TImage *>(pComponent);
							if(pImage)
							{
								pWICImage->LoadFromFile(this->SW_LEditPathBackGround->Text);
								pImage->Picture->Assign(pWICImage);
							}
						}
					}
				}
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
	} //[12-12-2023]
	//Zapis flag //[15-08-2023] [18-04-2024]
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsDisplaySplashStart, this->ToggleSwitchIsDisplayInfos->IsOn());
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsRequestEnd, this->ToggleSwitchIsRequestClose->IsOn());
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsOnlyOne, this->ToggleSwitchIsOneInstance->IsOn());
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsAutoFindUpdate, this->ToggleSwitchIsUpdatesOnStartup->IsOn());
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsLoadBooksOnInit, this->ToggleSwitchIsReopenSchets->IsOn());
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsTipsWindowStart, this->ToggleSwitchIsHintsOnStart->IsOn());
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsDisplayStartInfoTray, this->ToggleSwitchisInfosOnStatusBar->IsOn());
	//GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsDisplayOnlyPolTranslates, this->ToggleSwitchOnlyPolTranslates->IsOn());
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsDisplayBackgroundImage, this->ToggleSwitchIsImageBgn->IsOn());
	//Zapis kolorów
		//Kolor zaznaczenie ulubionych wersetów
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorFavoritesVers, this->SW_ColorBoxFavorities->Selected);
		//Kolor zaznaczenie wersetów, do których istnieje komentarz
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorCommentVers, this->SW_ColorBoxComment->Selected);
		//Kolor podkładu pod wyswietlany tekst,
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorBackgroundText, this->SW_ColorBoxBackground->Selected);
		//Kolor nazwy pełnego tłumaczenia
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorNameFullTranslates, this->SW_ColorBoxNameTranslate->Selected);
		//Kolor adresu, wersetu dla pełnego tłumaczenia
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorAdressVersFullTranslates, this->SW_ColorBoxColorAdressFulltranslates->Selected);
		//Kolor podkładu dla znacznika, istnienia komentarza dla wersetu
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorBackgroundMarkerComment, this->SW_ColorBackgroundMarkerComment->Selected);
		//Kolor ramki naokoło ulubionego wersetu
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorBorderFavoritiesVers, this->SW_ColorBoxBorderFavoritiesVers->Selected);
	//Others
		//Wielkość głównej czcionki tekstu wersetu
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_OtherSizeFontMain, this->SpEditSizeMainFont->Value);
		//Wielkość czcionki, adresu wersetu
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_OtherSizeFontAdress, this->SpEditSizeAdressFont->Value);
		//Wielkość czcionki nazwy tłumaczeń
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_OtherSizeFontNameTranslators, this->SpEditSizeTranslatesFont->Value);
		//Nazwy Czcionek
	GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_FontNameMain, this->ButtFontNameMainText->Caption);
	GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_FontNameAdress, this->ButtFontNameAdress->Caption);
	GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_FontNameTranslators, this->ButtFontNameTranslates->Caption);

	GsReadBibleTextData::SetupVariables(); //Odświerzenie zmiennych dla plików html klasy GsReadBibleTextData
	//Lista tłumaczeń wyłączonych z wyświetlania
	TStringList *pSListExcludeTrans = new TStringList(); //Lista przekładów wykluczonych
	if(!pSListExcludeTrans) throw(Exception("Błąd inicjalizacji objektu TStringList"));
	//TStringList *pSListIncludeTrans = new TStringList(); //Lista przekładów używanych
	//if(!pSListIncludeTrans) throw(Exception("Błąd inicjalizacji objektu TStringList"));
	//---
	for(int i=0; i<this->SW_ListViewAllTranslates->Items->Count; i++)
	{
		if(!this->SW_ListViewAllTranslates->Items->Item[i]->Checked)
		//Jeśli tłumaczenie nie jest zaznaczone, dodaj tłumaczenie do listy wykluczeń
		{
			pSListExcludeTrans->Add(this->SW_ListViewAllTranslates->Items->Item[i]->Caption);
		}
		else
		//Jeśli tłumaczenie jest zaznaczone, dodaj tłumaczenie do listy używanych
		{
			//pSListIncludeTrans->Add(this->SW_ListViewAllTranslates->Items->Item[i]->Caption);
		}
	}
  // Zapis Wykluczonych, lub wybranych tłumaczeń
	GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_TranslatesSection_Main, GlobalVar::GlobalIni_ExcludeTranslates, pSListExcludeTrans->CommaText);
	if(pSListExcludeTrans) {delete pSListExcludeTrans; pSListExcludeTrans = nullptr;}
  // Zapis tłumaczenia wykorzystanego do słownika i konkordancji grecko-polskiej [02-06-2024]
	GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_TranslatesSection_Main,
		GlobalVar::GlobalIni_SelectTranslateForDictConcord,
		this->SW_RGroupSelectTransDict->Items->Strings[this->SW_RGroupSelectTransDict->ItemIndex]);
	//--- Zapis konfiguracji dla Planu czytania biblii
	UnicodeString ustrNameTransIDPlan;
	int iIDTranslatePlan=-1, intPosSpace=0;
		//--- Wyprowadzania numeru identyfikacyjnego tłumaczenia przeznaczonego do planu czytania biblii
	if(!this->CBoxSelectTranslate->Text.IsEmpty())
	//----- Jest wybrane tłumaczenie z listy dla planu
	{
		intPosSpace = this->CBoxSelectTranslate->Text.Pos(" ");
		for(int i=0; i<GlobalVar::SDirTranslatesList.Length; i++)
		{
			ustrNameTransIDPlan = TPath::GetFileName(GlobalVar::SDirTranslatesList[i]);
			if(this->CBoxSelectTranslate->Text.SubString(1, intPosSpace-1) == ustrNameTransIDPlan)
			//Jeśli nazwa kolejnego tłumaczenia równa się nazwie wybranemu z listy this->CBoxSelectTranslate
			{
				if(iIDTranslatePlan == -1) iIDTranslatePlan = i;
			}
		}
		GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_TranslateRPlan, this->CBoxSelectTranslate->Text);
		GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_IDTranslateRPlan, iIDTranslatePlan);
	}
		//Czy plan aktywowany
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_IsStartPlan, this->SpButtonStartPlan->Down);
	if(!this->SpButtonStartPlan->Down)
	{
		GlobalVar::Global_ConfigFile->DeleteKey(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_SelectPlan);
		GlobalVar::Global_ConfigFile->DeleteKey(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_StartDate);
		if(TFile::Exists(GlobalVar::GlobalPath_CurrentActivePlan)) TFile::Delete(GlobalVar::GlobalPath_CurrentActivePlan);
	}
	else
	{
		//Wybrany plan czytania
		GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_SelectPlan, this->CBoxSelectPlan->Text);
		//Data rozpoczęcia planu
		GlobalVar::Global_ConfigFile->WriteDate(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_StartDate, this->DateTimePickerSelectStartDatePlan->Date);
	}
		//Nazwa czcionki dla planu
	GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_FontPlan, this->CBoxSelectFontReadingPlan->Text);
		//--- Wielkość czcionki dla planu
	GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_SizeFontPlan, this->CBoxSelectSizeFontPlan->Text);
	//--- Parametry mowy
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_SetRate, this->TrackBarSetRate->Position);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_SetVolume, this->TrackBarSetVolume->Position);
	//--- Parametry styli aplikacji
	if(TStyleManager::Enabled)
	{
		//TCustomStyleServices *pActiveStyle = TStyleManager::ActiveStyle;
		GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_OthersSection, GlobalVar::GlobalIni_SelectStyleName,
			this->SW_LBoxSelectTheme->Items->Strings[this->SW_LBoxSelectTheme->ItemIndex]);
		TStyleManager::SetStyle(this->SW_LBoxSelectTheme->Items->Strings[this->SW_LBoxSelectTheme->ItemIndex]);
	}
	//Zrzucenie zawartości objektu, klasy TMemIni, do pliku
	GlobalVar::Global_ConfigFile->UpdateFile();
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::SW_ButGroupSectionsButtonClicked(TObject *Sender,
					int Index)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButtonGroup *pButtGr = dynamic_cast<TButtonGroup *>(Sender);
	if(!pButtGr) return;
	//---
	this->SW_PControlSelected->ActivePageIndex = Index;
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::SW_ButGroupSectionsKeyUp(TObject *Sender, WORD &Key,
					TShiftState Shift)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButtonGroup *pButtGr = dynamic_cast<TButtonGroup *>(Sender);
	if(!pButtGr) return;
	//---
	this->SW_PControlSelected->ActivePageIndex = pButtGr->ItemIndex;
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::SW_PControlSelectedChange(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPageControl *pPControl = dynamic_cast<TPageControl *>(Sender);
	if(!pPControl) return;
	//---
	this->SW_ButGroupSections->ItemIndex = pPControl->ActivePageIndex;
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::SW_ButtSetups_Click(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButton *pButton = dynamic_cast<TButton *>(Sender);
	if(!pButton) return;
	//---
	switch(pButton->Tag)
	{
		//Przyciski wyboru katalogów z multimediami
		case enSelectDirMulti_1:
			this->SW_LEditPath1->Text = this->_SelectMultimediaDir(this->SW_LEditPath1->Text);
			break;
		case enSelectDirMulti_2:
			this->SW_LEditPath2->Text = this->_SelectMultimediaDir(this->SW_LEditPath2->Text);
			break;
		case enSelectDirMulti_3:
			this->SW_LEditPath3->Text = this->_SelectMultimediaDir(this->SW_LEditPath3->Text);
			break;
		//Wybór grafiki na podkład
		case enSelectBackground:
			this->SW_LEditPathBackGround->Text = this->_SelectBackGround();
    break;
		//Dolne przyciski akcji
		case enSetup_Save:
		{
			this->_WriteAllConfig();
			this->Close();
		}
		break;
		//---
		case enSetup_Return:
		{
			//Odczytanie starych ustawień do bufora, pliku ini, z TStringListy
			GlobalVar::Global_ConfigFile->SetStrings(this->_SListOldConfig);
			//---Ustawienie wszystkick ustawień na pierwotny stan, przed jaką kolwiek zmianą.
			this->_ReadAllConfig();
		}
		break;
		//---
		case enSetup_Cancel:
		{
      GlobalVar::IsRunReload = false; //Anulowanie przeładowania aplikcji po zmianie konfiguracji
			this->Close();
		}
		break;
		//---
		case enSetup_Help:
		{
			int iIndexPage = this->SW_PControlSelected->TabIndex;
			switch(iIndexPage)
			{
				case enPageSetups_Layout:
					Application->HelpContext(HELP_Set_Wygladaplikacji);
				break;
				//---
				case enPageSetup_Flags:
					Application->HelpContext(HELP_Set_Flagiiprzelaczniki);
				break;
				//---
				case enPageSetup_Paths:
					Application->HelpContext(HELP_Set_Sciezkidostepu);
				break;
				//---
				case enPageSetup_OtherSetups:
					Application->HelpContext(HELP_Set_Inneustawienia);
				break;
				//---
				case enPageSetup_Translates:
					Application->HelpContext(HELP_Set_Wybortlumaczen);
				break;
				//---
				case enPageSetups_ReadingPlan:
					Application->HelpContext(HELP_Set_PlanczytaniaBiblii);
				break;
				//---
				case enPageSetups_SelectThemes:
					Application->HelpContext(HELP_Set_Tematygraficzne);
				break;
				//---
				default:
					Application->HelpContext(HELP_Ustawieniaaplikacji);
			}

		}
		break;
		//Wyświetlenie wybranego tematu
		case enTagControl_ButtDisplayselectTheme:
		{
			UnicodeString ustrSelectPathThemeName = TPath::ChangeExtension(TPath::Combine(GlobalVar::Global_custrPathImagesStyles,
																								this->SW_LBoxSelectTheme->Items->Strings[this->SW_LBoxSelectTheme->ItemIndex]), ".jpg");

			TWICImage *pWICImage=nullptr;

			try
			{
				try
				{
					pWICImage = new TWICImage();
					if(!pWICImage) throw(Exception("Błąd inicjalizacji objektu TWICImage"));
					pWICImage->LoadFromFile(ustrSelectPathThemeName);
					this->SW_ImagePreviewSelectStyle->Picture->Assign(pWICImage);
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
		break;
	}
}
//---------------------------------------------------------------------------
UnicodeString __fastcall TSetupsWindow::_SelectMultimediaDir(UnicodeString _ustrPath)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	UnicodeString ustrSelect;
	TFileOpenDialog *pFileOpenDialog = new TFileOpenDialog(this);
	if(!pFileOpenDialog) throw(Exception("Błąd inicjalizacji objektu TFileOpenDialog"));
	//---
	pFileOpenDialog->Title = "Wybierz katalog...";
	pFileOpenDialog->Options << fdoPickFolders << fdoPathMustExist << fdoForceFileSystem;
	pFileOpenDialog->DefaultFolder = _ustrPath;
	//Otwarcie wyboru katalogu
	if(pFileOpenDialog->Execute())
		ustrSelect = pFileOpenDialog->FileName;
	else ustrSelect = _ustrPath;

	if(pFileOpenDialog) {delete pFileOpenDialog; pFileOpenDialog = nullptr;}
	return ustrSelect;
}
//---------------------------------------------------------------------------
UnicodeString __fastcall TSetupsWindow::_SelectBackGround(UnicodeString _ustrPath)
/**
	OPIS METOD(FUNKCJI): //[12-12-2023]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	const UnicodeString ustrFileTypes[] = {"Pliki jpg", "*.jpg", "Pliki jpeg", "*.jpeg",
																				 "Pliki png", "*.png", "Pliki bmp", "*.bmp", "Każdy plik", "*.*"};

	UnicodeString ustrSelect;
  TFileOpenDialog *pFileOpenDialog = new TFileOpenDialog(this);
	if(!pFileOpenDialog) throw(Exception("Błąd inicjalizacji objektu TFileOpenDialog"));
	//---
  for(int i=0; i<ARRAYSIZE(ustrFileTypes); i+=2)
	{
		TFileTypeItem *pTFileTypeItem = pFileOpenDialog->FileTypes->Add();
		pTFileTypeItem->DisplayName = ustrFileTypes[i];
		pTFileTypeItem->FileMask = ustrFileTypes[i+1];
	}

	pFileOpenDialog->Title = "Wybierz plik z grafiką jako podkład pod główne okno...";
	pFileOpenDialog->Options << fdoPathMustExist << fdoFileMustExist << fdoForceFileSystem;
	pFileOpenDialog->DefaultFolder = _ustrPath;

  if(pFileOpenDialog->Execute())
		ustrSelect = pFileOpenDialog->FileName;
	else ustrSelect = _ustrPath;

  if(pFileOpenDialog) {delete pFileOpenDialog; pFileOpenDialog = nullptr;}
	return ustrSelect;
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::SW_ColorBoxGetColors(TCustomColorBox *Sender,
					TStrings *Items)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TColorBox *pColorBox = dynamic_cast<TColorBox *>(Sender);
	if(!pColorBox) return;
	//---
	Items->AddStrings(GlobalVar::Global_ItemsColor);
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::SW_ColorAllChange(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TColorBox *pColorBox = dynamic_cast<TColorBox *>(Sender);
	if(!pColorBox) return;
	//---
	this->_DisplayPreview(); //[24-09-2023]
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::ButtFontSelectClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButton *pButt = dynamic_cast<TButton *>(Sender);
	if(!pButt) return;
	//---
	TFontDialog *pFontDialog = new TFontDialog(this);
	if(!pFontDialog) throw(Exception("Błąd inicjalizacji objektu TFontDialog"));
	pFontDialog->Font = pButt->Font;
	pFontDialog->Options.Clear();
	pFontDialog->Options << fdLimitSize;
	pFontDialog->MinFontSize = 8;
	pFontDialog->MaxFontSize = 24;

	//---
	if(pFontDialog->Execute())
	{
		pButt->Font = pFontDialog->Font;
		pButt->Caption = pFontDialog->Font->Name;
		switch(pButt->Tag)
		{
			case enTagControl_ButtFontMain: this->SpEditSizeMainFont->Value = pFontDialog->Font->Size;
			break;
			//---
			case enTagControl_ButtFontAdress: this->SpEditSizeAdressFont->Value = pFontDialog->Font->Size;
			break;
			//---
			case enTagControl_ButtFontNameTranslates: this->SpEditSizeTranslatesFont->Value = pFontDialog->Font->Size;
			break;
			//---
		}
	}

	if(pFontDialog) {delete pFontDialog; pFontDialog = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::SpEditSizeFontChange(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Zmiana wartości w kontrolce klasy TSpinEdit
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TSpinEdit *pSpinEdit = dynamic_cast<TSpinEdit *>(Sender);
	if(!pSpinEdit) return;
	//---
	switch(pSpinEdit->Tag)
	{
		case enTagControl_SpinEdSizeMainFont:
			this->ButtFontNameMainText->Font->Size = pSpinEdit->Value;
			break;
		//---
		case enTagControl_SpinEdSizeAdressFont:
			this->ButtFontNameAdress->Font->Size = pSpinEdit->Value;
			break;
		//---
		case enTagControl_SpinEdSizeTranslatesFont:
			this->ButtFontNameTranslates->Font->Size = pSpinEdit->Value;
			break;
		//---
	}
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::SpButtonStartStopReadingPlanClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TSpeedButton *pSButton = dynamic_cast<TSpeedButton *>(Sender);
	if(!pSButton) return;
	//---
	if(pSButton->Down)
	{
		if(this->CBoxSelectPlan->Text.IsEmpty())
		//Brak wybranego planu
		{
			MessageBox(NULL, TEXT("Nie jest wybrany plan czytania, więc nie ma czego aktywować. Wybierz najpierw odpowiedni plan i aktywuj go."), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
			pSButton->Down = false;
			return;
		}
		this->DateTimePickerSelectStartDatePlan->MinDate = 0;
		this->DateTimePickerSelectStartDatePlan->Enabled = false;
		this->_InfoStartStopPlan();//Informacje o wybranym planie
		this->_WriteJournalPlan(); //Stworzenie pliku dziennika
	}
	else //Nieaktywny plan czytania
	{
		#if defined(_DEBUGINFO_)
			GsDebugClass::WriteDebug("pSButton->Down = false");
		#endif
		this->DateTimePickerSelectStartDatePlan->Enabled = true;
		this->DateTimePickerSelectStartDatePlan->MinDate = TDateTime::CurrentDate();
		this->LabelInfoSelectAndactivatePlan->Caption = "";
		this->_iNumberDayPlan = -1;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::_InfoStartStopPlan()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_iNumberDayPlan = DaysBetween(TDateTime::CurrentDate(), this->DateTimePickerSelectStartDatePlan->Date);
	this->LabelInfoSelectAndactivatePlan->Caption = Format("Aktualny plan: \"%s\", Tłumaczenie: \"%s\". Aktualna data: %s. Data rozpoczęcia aktualnego planu: %s. Dzień %d czytania.",
		ARRAYOFCONST((this->CBoxSelectPlan->Text, this->CBoxSelectTranslate->Text, TDateTime::CurrentDate().FormatString("dd-mm-yyyy"),
			this->DateTimePickerSelectStartDatePlan->Date.FormatString("dd-mm-yyyy"), this->_iNumberDayPlan+1)));
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::_WriteJournalPlan()
/**
	OPIS METOD(FUNKCJI): Zapis aktualnego dziennika czytania bibli
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	const int ciNameCurrentPlan = 0; //Indeks gdzie znajduje się nazwa aktualnie czytanego planu
	#if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug(Format("Path jcp: \"%s\"", ARRAYOFCONST((GlobalVar::GlobalPath_CurrentActivePlan))));
		GsDebugClass::WriteDebug(Format("Size: %d", ARRAYOFCONST((this->LViewDisplayselectPlan->Items->Count))));
	#endif
	TListItem *pLItem = nullptr;
	THashedStringList *pHSList = new THashedStringList();
	if(!pHSList) throw(Exception("Błąd funkcji THashedStringList"));

	try
	{
		try
		{
			if(!TFile::Exists(GlobalVar::GlobalPath_CurrentActivePlan))
			//Plik dziennika nie istnieje
			{
				pHSList->Add(this->CBoxSelectPlan->Text);
				for(int i=0; i<this->LViewDisplayselectPlan->Items->Count; i++)
				{
					pLItem = this->LViewDisplayselectPlan->Items->Item[i];
					if(pLItem)
					{
						pHSList->AddPair(pLItem->SubItems->Strings[0], "0");
					}
				}
				pHSList->SaveToFile(GlobalVar::GlobalPath_CurrentActivePlan, TEncoding::UTF8);
			} //if(!TFile::Exists(GlobalVar::GlobalPath_CurrentActivePlan))
			else
			//Plik dziennika istnieje. Trzeba sprawdzić czy nie odnosi sie do aktualnego planu
			{
				pHSList->LoadFromFile(GlobalVar::GlobalPath_CurrentActivePlan, TEncoding::UTF8);
				if(pHSList->Strings[ciNameCurrentPlan] == this->CBoxSelectPlan->Text)
				{
					#if defined(_DEBUGINFO_)
						GsDebugClass::WriteDebug("Ten sam plan");
					#endif
				}
			}
		} //try catch
		catch(Exception &e)
		{
			MessageBox(NULL, e.Message.c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	} //try __finally
	__finally
	{
		if(pHSList) {delete pHSList; pHSList = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::DateTimePickerSelectStartDatePlanChange(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Zmaia daty
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TDateTimePicker *pDTPicker = dynamic_cast<TDateTimePicker *>(Sender);
	if(!pDTPicker) return;
	//---
	if(GlobalVar::Global_ConfigFile->ValueExists(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_StartDate))
	{
		GlobalVar::Global_ConfigFile->WriteDate(GlobalVar::GlobalIni_ReadingPlan_Main, GlobalVar::GlobalIni_StartDate, pDTPicker->Date);
	}
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::LViewDisplayselectPlanDrawItem(TCustomListView *Sender,
					TListItem *Item, TRect &Rect, TOwnerDrawState State)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListView *pLView = dynamic_cast<TListView *>(Sender);
	if(!pLView) return;
	//---
	TRect RectBounds = Item->DisplayRect(drBounds);
	TRect RectLabel = Item->DisplayRect(drLabel);
	TRect RectIcon = Item->DisplayRect(drIcon);
  //--- Kolory aktywnego stylu //[16-12-2023]
	TColor cBackGround = TStyleManager::ActiveStyle->GetStyleColor(scListView);
	TColor cText = TStyleManager::ActiveStyle->GetStyleFontColor(sfListItemTextNormal);

	pLView->Canvas->Brush->Color = cBackGround; //[16-12-2023]
	//if(!(Item->Index % 2)) pLView->Canvas->Brush->Color = (TColor)0x00EEEEEE;

	pLView->Canvas->FillRect(RectBounds);
	pLView->Canvas->Font->Color = cText; //[16-12-2023]
	pLView->Canvas->Font->Style = TFontStyles() << fsBold;

	this->SW_ImgListMainSmall->Draw(pLView->Canvas, RectIcon.Left, (this->SW_ImgListMainSmall->Width / 2 - ((RectIcon.Bottom - RectIcon.Top)	/ 2)) + RectIcon.Top, enImage_NumberDayPlan);
	DrawText(pLView->Canvas->Handle, Item->Caption.c_str(), -1, &RectLabel, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);

	TRect RectSubItem	 = RectLabel;
	for(int iColumn=0; iColumn<pLView->Columns->Count - 1; iColumn++)
	{
		//Wymiary następnej kolumny
		RectSubItem.Left += pLView->Column[iColumn]->Width;
		RectSubItem.Right += pLView->Column[iColumn + 1]->Width;
		this->SW_ImgListMainSmall->Draw(pLView->Canvas, RectSubItem.Left - this->SW_ImgListMainSmall->Width, (this->SW_ImgListMainSmall->Width / 2 - ((RectIcon.Bottom - RectIcon.Top)	/ 2)) + RectIcon.Top, enImage_ReadingPlan);

		//pLView->Canvas->Font->Color = clBlue;
		pLView->Canvas->Font->Style = TFontStyles();

		TRect RectSubItem1 = RectSubItem;
		DrawText(pLView->Canvas->Handle, Item->SubItems->Strings[iColumn].c_str(), -1, &RectSubItem1, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	}
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::LViewDisplayselectPlanChanging(TObject *Sender,
					TListItem *Item, TItemChange Change, bool &AllowChange)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListView *pLView = dynamic_cast<TListView *>(Sender);
	if(!pLView) return;
	//---
	AllowChange = false;
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::CBoxSelectPlanChange(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TComboBox *pCBox = dynamic_cast<TComboBox *>(Sender);
	if(!pCBox) return;
	//--- Aktualizacje
	this->SpButtonStartStopReadingPlanClick(this->SpButtonStartPlan);
	this->_DisplaySelectPlan();
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::SW_LBoxSelectThemeClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Wybrano nazwę stylu z listy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListBox *pLBox = dynamic_cast<TListBox *>(Sender);
	if(!pLBox) return;
	//---
	this->SW_ButtDisplaySelectTheme->Enabled = pLBox->ItemIndex > -1;
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::SW_ListViewAllTranslatesItemChecked(TObject *Sender,
					TListItem *Item)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListView *pLView = dynamic_cast<TListView *>(Sender);
	if(!pLView) return;
	//---
  if(this->_bIsStart) return; //Wyjście jeśli ustawienia listy przekładów są w stanie uruchamiania

	GlobalVar::IsRunReload = true; //Potrzeba przeładować aplikcje po zmianie konfiguracji
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::ToggleSwitchIsImageBgnClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Przełączanie aktywacji podkładu graficznego pod główny tekst [24-04-2024]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TToggleSwitch *pTSwitch = dynamic_cast<TToggleSwitch *>(Sender);
	if(!pTSwitch) return;
	//---
	this->SW_ImageBackground->Visible = (pTSwitch->State == tssOn);
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::SW_ListViewAllTranslatesChanging(TObject *Sender,
					TListItem *Item, TItemChange Change, bool &AllowChange)
/**
	OPIS METOD(FUNKCJI): Metoda zapobiega zmianie stanu tłumaczeń specjalistycznych [18-05-2024]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TListView *pLView = dynamic_cast<TListView *>(Sender);
	if(!pLView) return;
	//---
	AllowChange = (Item->GroupID != enGroup_OrygTrans);
}
//---------------------------------------------------------------------------

