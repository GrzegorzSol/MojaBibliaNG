/*
	Klasa do obsługi okna wszystkich ustawień aplikacji
*/
//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "uSetupsWindow.h"
#include <System.IOUtils.hpp>
#include "GsReadBibleTextClass\GsReadBibleTextClass.h"
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
			enSelectDirMulti_1, enSelectDirMulti_2, enSelectDirMulti_3,
			enSetup_Save=10, enSetup_Return, enSetup_Cancel,
			enTag_IsDisplaySplashScreen=20, enTag_IsRequestEnd, enTag_IsOnlyOne, enTag_IsAutoFindUpdate, enTag_IsLoadBooksOnInit,
			//Tagi dla przycisków i innych kontrolek
			enTagControl_ButtFontMain=100,
			enTagControl_ButtFontAdress,
			enTagControl_ButtFontNameTranslates,
        //TSpinEdit
			enTagControl_SpinEdSizeMainFont,
			enTagControl_SpinEdSizeAdressFont,
			enTagControl_SpinEdSizeTranslatesFont,
			//Indeksy grafik ikon this->SW_ImgListSmallMain
			enImage_SelectDir=0, enImage_SaveConfig, enImage_Cancel, enImage_UndoSetup,
			//Indeksy grafik ikon this->SW_ImgListMainSmall
			enImage_ViewAplic=0, enImage_SetupFlags, enImage_Paths, enImage_OtherSetups, enImage_Translates, enImage_TypeTranslate, enImage_DescryptionTranslate,
			//Numery kolumn dodatkowych w ustawieniach tłumaczeń
			enColumn_TypeTranslate=0, enColumn_DescryptionTranslate,
			//Grupy tłumaczeń
			enGroup_PolCompleteTrans=0, enGroup_OrygTrans, enGroup_Count
		 };
const UnicodeString ustrColumnLViewTranslates[] = {"Plik tłumaczenia", "Typ tłumaczenia", "Opis tłumaczenia"},
										ustrGroups[] = {"Polskie kompletne tłumaczenia", "Tłumaczenia oryginalne"};

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
	//Hinty
	this->SW_ButGroupSections->Hint = "Grupy ustawień";
	this->SW_LEditPath1->Hint = Format("Ścieżka dostępu do katalogu z multimediami||%u", ARRAYOFCONST((enImage_SelectDir)));
	this->SW_LEditPath2->Hint = Format("Ścieżka dostępu do katalogu z multimediami||%u", ARRAYOFCONST((enImage_SelectDir)));
	this->SW_LEditPath3->Hint = Format("Ścieżka dostępu do katalogu z multimediami||%u", ARRAYOFCONST((enImage_SelectDir)));
	this->SW_ButtSelectDirMulti_1->Hint = Format("Wybór katalogu z multimediami||%u", ARRAYOFCONST((this->SW_ButtSelectDirMulti_1->ImageIndex)));
	this->SW_ButtSelectDirMulti_2->Hint = Format("Wybór katalogu z multimediami||%u", ARRAYOFCONST((this->SW_ButtSelectDirMulti_2->ImageIndex)));
	this->SW_ButtSelectDirMulti_3->Hint = Format("Wybór katalogu z multimediami||%u", ARRAYOFCONST((this->SW_ButtSelectDirMulti_3->ImageIndex)));
	this->SW_ButtSetupSave->Hint = Format("Zapis zmienionej konfiguracji||%u", ARRAYOFCONST((this->SW_ButtSetupSave->ImageIndex)));
	this->SW_ButtSetupCancel->Hint = Format("Anulowanie zmienionej konfiguracji||%u", ARRAYOFCONST((this->SW_ButtSetupCancel->ImageIndex)));

	this->SW_CBoxIsDisplaySplashScreen->Tag = enTag_IsDisplaySplashScreen;
	this->SW_CBoxIsRequestEnd->Tag = enTag_IsRequestEnd;
	this->SW_CBoxOnlyOne->Tag = enTag_IsOnlyOne;
	this->SW_CBoxAutoFindUpdate->Tag = enTag_IsAutoFindUpdate;
	this->SW_CBoxReLoadBooks->Tag = enTag_IsLoadBooksOnInit;
	//Dodawanie grup do objektu, typu TListView
	for(int i=0; i<enGroup_Count; i++)
	{
		TListGroup *pLGroup = this->SW_ListViewAllTranslates->Groups->Add();
		pLGroup->Header = ustrGroups[i];
	}
	//Dodawanie kolumn do objektu, typu TListView
	TListColumn  *NewColumn;//=0;
	for(unsigned int iColumns=0; iColumns<ARRAYSIZE(ustrColumnLViewTranslates); iColumns++)
	{
		NewColumn = this->SW_ListViewAllTranslates->Columns->Add();
		NewColumn->Caption = ustrColumnLViewTranslates[iColumns];
		NewColumn->AutoSize = true;
		NewColumn->ImageIndex = enImage_Translates + iColumns;
	}
	//Tekst informacyjny na dole okna
	this->SW_STextInfo->Caption = UnicodeString("\tUwagi dotyczące zadziałanie ustawień\n") +
		" 1. - Ustawienie będzie obowiązywało po ponownym uruchomieniu aplikacji." +
		"\n 2. - Po zmianie tych parametrów, dopiero w nowo otwartej księdze, zaczną, one obowiązywać.";
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
	//Pole tekstowe z wybranymi katalogami z multimediami
	this->SW_LEditPath1->Tag = enSelectDirMulti_1; this->SW_ButtSelectDirMulti_1->Tag = enSelectDirMulti_1;
	this->SW_LEditPath2->Tag = enSelectDirMulti_2; this->SW_ButtSelectDirMulti_2->Tag = enSelectDirMulti_2;
	this->SW_LEditPath3->Tag = enSelectDirMulti_3; this->SW_ButtSelectDirMulti_3->Tag = enSelectDirMulti_3;
	//Dolne przyciski
	this->SW_ButtSetupSave->Tag = enSetup_Save;
	this->SW_ButtSetupReturn->Tag = enSetup_Return;
	this->SW_ButtSetupCancel->Tag = enSetup_Cancel;
	//Przyciski wyboru czcionki
	this->ButtFontNameMainText->Tag = enTagControl_ButtFontMain;
	this->ButtFontNameAdress->Tag = enTagControl_ButtFontAdress;
	this->ButtFontNameTranslates->Tag = enTagControl_ButtFontNameTranslates;
	//Kontrolka do ustawiania wielkości czcionek
	this->SpEditSizeMainFont->Tag = enTagControl_SpinEdSizeMainFont;
	this->SpEditSizeAdressFont->Tag = enTagControl_SpinEdSizeAdressFont;
	this->SpEditSizeTranslatesFont->Tag = enTagControl_SpinEdSizeTranslatesFont;
	//Odczyt konfiguracji
	this->_ReadAllConfig();
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
	if(this->_SListOldConfig) {delete this->_SListOldConfig; this->_SListOldConfig = 0;} //Przechowywanie ustawień, podczas uruchomienia okna konfiguracji
	if(this->_HSListViewAllTr) {delete this->_HSListViewAllTr; this->_HSListViewAllTr = 0;} //Tekst wszystkich dostępnych tłumaczeń, modelowego wersetu
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::_ReadAllConfig()
/**
	OPIS METOD(FUNKCJI): Odczyt wszystkich ustawień aplikacji i ustawienie komponentów
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Ścierzki dostępu do katalogów z multimediami
	this->SW_LEditPath1->Text = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM1, "");
	this->SW_LEditPath2->Text = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM2, "");
	this->SW_LEditPath3->Text = GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM3, "");
	//Flagi
	this->SW_CBoxIsDisplaySplashScreen->Checked = GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsDisplaySplashStart, true);
	this->SW_CBoxIsRequestEnd->Checked = GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsRequestEnd, true);
	this->SW_CBoxOnlyOne->Checked = GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsOnlyOne, true);
	this->SW_CBoxAutoFindUpdate->Checked = GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsAutoFindUpdate, true);
	this->SW_CBoxReLoadBooks->Checked = GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsLoadBooksOnInit, true);
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
		//Kolor czcionki, dla oryginalnych tłumaczeń
	this->SW_ColorBoxColorOrygTr->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorOryginalTranslates, clMaroon);
		//Kolor nazwy oryginalnego tłumaczenia
	this->SW_ColorBoxColorNameOrygTran->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorNameOryginalTranslate, clRed);
		//Kolor adresu oryginalnego tłumaczenia
	this->SW_ColorBoxAdressOryg->Selected = (TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorAdressOryginalTranslate, clBlue);
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
		else
			NewItem->SubItems->Add("");
		NewItem->SubItemImages[enColumn_TypeTranslate] = enImage_TypeTranslate;
		//--- Opis tłumaczenia	//Poprawić
		GsReadBibleTextData::GetInfoNameTranslate(i, ustrNameTranslate);
		NewItem->SubItems->Add(ustrNameTranslate);
		NewItem->SubItemImages[enColumn_DescryptionTranslate] = enImage_DescryptionTranslate;

	}
	if(pSListExcludeTrans) {delete pSListExcludeTrans;}
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
	//Zapis flag
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsDisplaySplashStart, this->SW_CBoxIsDisplaySplashScreen->Checked);
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsRequestEnd, this->SW_CBoxIsRequestEnd->Checked);
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsOnlyOne, this->SW_CBoxOnlyOne->Checked);
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsAutoFindUpdate, this->SW_CBoxAutoFindUpdate->Checked);
  GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_FlagsSection_Main, GlobalVar::GlobalIni_IsLoadBooksOnInit, this->SW_CBoxReLoadBooks->Checked);
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
		//Kolor czcionki, dla oryginalnych tłumaczeń
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorOryginalTranslates, this->SW_ColorBoxColorOrygTr->Selected);
		//Kolor nazwy oryginalnego tłumaczenia
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorNameOryginalTranslate, this->SW_ColorBoxColorNameOrygTran->Selected);
		//Kolor adresu oryginalnego tłumaczenia
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_ColorsSection_Main, GlobalVar::GlobalIni_ColorAdressOryginalTranslate, this->SW_ColorBoxAdressOryg->Selected);
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
	GlobalVar::Global_ConfigFile->WriteString(GlobalVar::GlobalIni_TranslatesSection_Main, GlobalVar::GlobalIni_ExcludeTranslates, pSListExcludeTrans->CommaText);
	if(pSListExcludeTrans) {delete pSListExcludeTrans; /*pSListExcludeTrans = 0;*/}
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
      this->Close();
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

	if(pFileOpenDialog) {delete pFileOpenDialog; /*pFileOpenDialog = 0;*/}
	return ustrSelect;
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::SW_CBox_Click(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCheckBox *pCBox = dynamic_cast<TCheckBox *>(Sender);
	if(!pCBox) return;
	//---
	switch(pCBox->Tag)
	{
		case enTag_IsDisplaySplashScreen:
		break;
		//---
		case enTag_IsRequestEnd:
    break;
  }
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
	Items->AddObject("clWebWheat", reinterpret_cast<TObject*>(clWebWheat));
	Items->AddObject("clWebBurlywood", reinterpret_cast<TObject*>(clWebBurlywood));
	Items->AddObject("clWebLinen", reinterpret_cast<TObject*>(clWebLinen));
	Items->AddObject("clWebLemonChiffon", reinterpret_cast<TObject*>(clWebLemonChiffon));
	Items->AddObject("clWebDarkOrange", reinterpret_cast<TObject*>(clWebDarkOrange));
	Items->AddObject("clWebDarkRed", reinterpret_cast<TObject*>(clWebDarkRed));
	Items->AddObject("clWebCoral", reinterpret_cast<TObject*>(clWebCoral));
	Items->AddObject("clWebGold", reinterpret_cast<TObject*>(clWebGold));
	Items->AddObject("clWebRosyBrown", reinterpret_cast<TObject*>(clWebRosyBrown));
	Items->AddObject("clWebForestGreen", reinterpret_cast<TObject*>(clWebForestGreen));
	Items->AddObject("clWebChartreuse", reinterpret_cast<TObject*>(clWebChartreuse));
	Items->AddObject("clWebSeaGreen", reinterpret_cast<TObject*>(clWebSeaGreen));
	Items->AddObject("clWebMediumAquamarine", reinterpret_cast<TObject*>(clWebMediumAquamarine));
	Items->AddObject("clWebLightCyan", reinterpret_cast<TObject*>(clWebLightCyan));
	Items->AddObject("clWebCornFlowerBlue", reinterpret_cast<TObject*>(clWebCornFlowerBlue));
	Items->AddObject("clWebIndigo", reinterpret_cast<TObject*>(clWebIndigo));
	Items->AddObject("clWebAqua", reinterpret_cast<TObject*>(clWebAqua));
	Items->AddObject("clWebRoyalBlue", reinterpret_cast<TObject*>(clWebRoyalBlue));
	Items->AddObject("clWebMidnightBlue", reinterpret_cast<TObject*>(clWebMidnightBlue));
	Items->AddObject("clWebDarkViolet", reinterpret_cast<TObject*>(clWebDarkViolet));
	Items->AddObject("clWebDarkMagenta", reinterpret_cast<TObject*>(clWebDarkMagenta));
	Items->AddObject("clWebDeepPink", reinterpret_cast<TObject*>(clWebDeepPink));
	Items->AddObject("clWebMediumSlateBlue", reinterpret_cast<TObject*>(clWebMediumSlateBlue));
	Items->AddObject("clWebSteelBlue", reinterpret_cast<TObject*>(clWebSteelBlue));
	Items->AddObject("clWebSlateBlue", reinterpret_cast<TObject*>(clWebSlateBlue));
	Items->AddObject("clWebDarkSlategray", reinterpret_cast<TObject*>(clWebDarkSlategray));
}
//---------------------------------------------------------------------------
void __fastcall TSetupsWindow::SW_PBoxViewSetupColorsPaint(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPaintBox *pPBox = dynamic_cast<TPaintBox *>(Sender);
	if(!pPBox) return;
	//---
	int iLeft, iTop=8;// iWidth=pPBox->Width;
	UnicodeString ustrAdres=Format("%s 5:1", ARRAYOFCONST((GsReadBibleTextData::GsInfoAllBooks[44].ShortNameBook))),
								ustrTextLine,
								ustrNametr;
	//---
	pPBox->Canvas->Font = this->ButtFontNameMainText->Font;
	GsReadBibleTextData::GetSelectVerAllTranslates(44, 5, 1, this->_HSListViewAllTr);
	pPBox->Canvas->Brush->Color = this->SW_ColorBoxBackground->Selected;
	pPBox->Canvas->FillRect( this->SW_PBoxViewSetupColors->ClientRect);
	for(int i=0; i<this->_HSListViewAllTr->Count; i++)
	{
		//Znacznik istnienia komentarza
		iLeft = 4;
		pPBox->Canvas->Font = this->ButtFontNameMainText->Font;
		if(i==0)
		{
			pPBox->Canvas->Font->Color = this->SW_ColorBoxComment->Selected;
			pPBox->Canvas->Font->Style = TFontStyles() << fsBold << fsUnderline;
			pPBox->Canvas->Brush->Color = this->SW_ColorBackgroundMarkerComment->Selected; //Kolor podkładu głównego
			pPBox->Canvas->Font->Size = this->SpEditSizeMainFont->Value;
			pPBox->Canvas->TextOut(iLeft, iTop, "C");
			iLeft += pPBox->Canvas->TextWidth("C") + 3;
    }
		//Atrybuty adresu wersetu
		pPBox->Canvas->Font = this->ButtFontNameAdress->Font;
		pPBox->Canvas->Font->Style = TFontStyles();
		iTop += 3;
		if(i == this->_HSListViewAllTr->Count - 1) pPBox->Canvas->Font->Color = this->SW_ColorBoxAdressOryg->Selected;
		else pPBox->Canvas->Font->Color = this->SW_ColorBoxColorAdressFulltranslates->Selected;
		pPBox->Canvas->Brush->Color = this->SW_ColorBoxBackground->Selected;
		pPBox->Canvas->Font->Size = this->SpEditSizeAdressFont->Value;
		pPBox->Canvas->TextOut(iLeft, iTop, ustrAdres);
		iLeft += pPBox->Canvas->TextWidth(ustrAdres) + 8;
		//Tekst wersetu
		pPBox->Canvas->Font = this->ButtFontNameMainText->Font;
		if(i == this->_HSListViewAllTr->Count - 1) pPBox->Canvas->Font->Color = this->SW_ColorBoxColorOrygTr->Selected; //Tekst wersetu oryginalnego tłumaczenia
		else pPBox->Canvas->Font->Color = clBlack;
		pPBox->Canvas->Font->Size = this->SpEditSizeMainFont->Value;
		ustrTextLine = this->_HSListViewAllTr->Strings[i];
		iTop -= 3;
		if(i==0) pPBox->Canvas->Brush->Color = this->SW_ColorBoxFavorities->Selected; //Kolor podkłady ulubionego wersetu
		else pPBox->Canvas->Brush->Color = this->SW_ColorBoxBackground->Selected; //Kolor podkłady ulubionego wersetu
		pPBox->Canvas->TextOut(iLeft, iTop, ustrTextLine);
		GsReadBibleTextData::GetInfoNameTranslate(i, ustrNametr);
		iLeft += pPBox->Canvas->TextWidth(ustrTextLine) + 8;
		//Znaczniki tekstu, nazwy tłumaczenia
    pPBox->Canvas->Font = this->ButtFontNameTranslates->Font;
		pPBox->Canvas->Font->Size = this->SpEditSizeTranslatesFont->Value; iTop += 3;
		if(i == this->_HSListViewAllTr->Count - 1) pPBox->Canvas->Font->Color = this->SW_ColorBoxColorNameOrygTran->Selected;
		else pPBox->Canvas->Font->Color = this->SW_ColorBoxNameTranslate->Selected;
		pPBox->Canvas->Brush->Color = this->SW_ColorBoxBackground->Selected;
		pPBox->Canvas->TextOut(iLeft, iTop, "[" + ustrNametr + "]");
		iTop += -pPBox->Canvas->Font->Height + 4;
	}
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
	this->SW_PBoxViewSetupColors->Repaint();
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
	pFontDialog->MaxFontSize = 14;

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

	if(pFontDialog) {delete pFontDialog; /*pFontDialog = 0;*/}
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

