#include <vcl.h>
#pragma hdrstop

#include "uNewSchemeVersWindow.h"
#include "MyBibleLibrary\GsReadBibleTextdata.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNewSchemeVersWindow *NewSchemeVersWindow;
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
// Teksty pomocy
UnicodeString ustrHelpText[] = {
	"Stwórz nowe drzewo wybierając przycisk \"Nowy projekt\", lub zacznij dodawać objekty do pustego widoku.", // enTagHelp_Start
	UnicodeString("Po otwarciu lub stworzeniu nowego drzewa możesz zrobić następujące czynności:\n") +
									"- Przesuwać pojedyńcze elementy\n" +
									"- Zaznacz wiele objektów trzymając klawisz Ctr, by przesunąć naraz więcej objektów\n"+
									"- Usunąć zaznaczony objekt\n" +
									"- Skopiować wybraną gałąż, by ją wkleić w inne miejsce (do innego objektu)\n"+
									"- Zapisać układ wersetów do projektu, by je później odtworzyć\n"+
									"- Zapisać drzewo wersetów jako grafikę\n"+
									"- Rozbudowywać drzewo\n"+
									"- Zmienić w wybranej pozycji werset objektu\n", // enTagHelp_Exist
	"Rozpocząłeś prace od nowa, projekt jest pusty, więc możesz zacząć tworzyć nowe drzewo zależnośći między wersetami."}; // enTagHelp_New};
const UnicodeString custrTextWindow = "Wykres logicznego powiązania wersetów.";

enum {// Numery pomocy
			enTagHelp_Start=0,
			enTagHelp_Exist,
			enTagHelp_New,
			// Ikony 32x32
			enImage_Add=0, // Dodanie nowej pozycji
			enImage_Del, // Skasowanie wybranej pozycji
			enImage_SetupsColors, // Konfiguracja kolorów
			enImage_SelectTrans,	// Wybór tłumaczenia
			enImage_Save, // Zapisz projekt
			enImage_Open, // Otwórz projekt
			enImage_Rename,// Zmiana wersetu w objekcie
			enImage_New, // Nowy projekt
			enImage_SaveAtGfx, // Zapisz wykres jako grafikę
			enImage_AllText, // Stworzenie pliku typu txt z zawartością wszystkich pozycji
			enImage_CutCopyToPaste, // Skopiowanie lub wycięciezaznaczonej gałęzi
			enImage_PasteFromcopy, // Wklejenie skopiowanej gałęzi
			// Ikony 16x16
			enImageSmall_Root=0,
			enImageSmall_Child,
			// Tagi dla głównych przycisków
			enTag_Add = 100,	 // Dodanie nowej pozycji
			entag_Del,				 // Skasowanie wybranej pozycji
			enTag_SetupsColors, // Konfiguracja kolorów
			enTag_SelectTrans,	// Wybór tłumaczenia
			enTag_Save, // Zapisz projekt
			enTag_Open,// Otwórz projekt
			enTag_Rename,// Zmiana wersetu w objekcie
			enTag_New, // Nowy projekt
			enTag_SaveAtGfx, // zapisz wykres jako grafikę
			enTag_AllText, // Stworzenie pliku typu txt z zawartością wszystkich pozycji
			enTag_CutCopyToPaste, // Skopiowanie lub wycięciezaznaczonej gałęzi
			enTag_PasteFromcopy, // Wklejenie skopiowanej gałęzi
			// Tagi dla przycisków panelu konfiguracji
			enTag_ConfigAccept = 200,
			enTag_ConfigNoAccept
			};

//---------------------------------------------------------------------------
__fastcall TNewSchemeVersWindow::TNewSchemeVersWindow(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->Caption = Format("%s - Uktualny projekt: \"%s\"", ARRAYOFCONST((custrTextWindow, custrProjectNameDefault)));
	// Narzędzia wyboru wersetu
	this->_pGsBarSelectVers = new GsBarSelectVers(this);
	if(!this->_pGsBarSelectVers) throw(Exception("Błąd inicjalizacji objektu GsBarSelectVers"));
	this->_pGsBarSelectVers->Parent = this;
	this->_pGsBarSelectVers->Align = alTop;
	this->ActionToolBarMain->Top = 0; // Narzędzia na samej górze
	// Utworzenie głównego objektu klasy GsLogicalRelationshipTable
	this->_pGsMasterRel = new GsMaster(this, this->TrViewMain);
	if(!this->_pGsMasterRel) throw(Exception("Błąd inicjalizacji objektu GsMaster"));
	this->_pGsMasterRel->Parent = this;
	this->_pGsMasterRel->Align = alClient;
	this->_pGsMasterRel->OnMouseDown = this->_OnMouseDown;
	//this->_pGsMasterRel->Visible = false;
	// Utworzenie objektu pomocy
	this->_pGsHelp = new GsHelp(this->PanelTreeAndHelp);
	if(!this->_pGsHelp) throw(Exception("Błąd inicjalizacji objektu GsHelp"));
	this->_pGsHelp->Parent = this->PanelTreeAndHelp;
	this->_pGsHelp->Align = alBottom;
	this->_pGsHelp->HelpText = ustrHelpText[enTagHelp_Start];

	this->_InitHintsAndTags();
	this->_ReadConfig();
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//--- Zachowanie pierwotnych ustawień z bufora pliku ini, do TStringListy
	this->_SListOldConfig = new TStringList(); //Przechowywanie ustawień, podczas uruchomienia okna konfiguracji
	if(!this->_SListOldConfig) throw(Exception("Błąd funkcji TStringList"));
	GlobalVar::Global_ConfigFile->GetStrings(this->_SListOldConfig);

	this->_OpenSetupsVisualScheme(); // Otwarcie panelu do wyboru tłumaczenia
	this->_OpenSelectTranslate(); // Otwarcie panelu konfiguracyjnego wyglądu wykresu
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::FormDestroy(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->_SListOldConfig) {delete this->_SListOldConfig; this->_SListOldConfig = nullptr;} //Przechowywanie ustawień, podczas uruchomienia okna konfiguracji
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::FormClose(TObject *Sender, TCloseAction &Action)
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
void __fastcall TNewSchemeVersWindow::_InitHintsAndTags()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->Act_AddItem->Tag = enTag_Add;
	this->Act_AddItem->Hint = Format("%s|Dodaje nowe dowiązanie do aktualnego elementu|%u", ARRAYOFCONST((this->Act_AddItem->Caption, this->Act_AddItem->ImageIndex)));
	this->Act_DelItem->Tag = entag_Del;
	this->Act_DelItem->Hint = Format("%s|Usuwa aktualne dowiązanie, wcześniej zadając pytanie.|%u", ARRAYOFCONST((this->Act_DelItem->Caption, this->Act_DelItem->ImageIndex)));
	this->Act_SetupsColors->Tag = enTag_SetupsColors;
	this->Act_SetupsColors->Hint = Format("%s|Otwiera panel do wyboru kolorów.|%u", ARRAYOFCONST((this->Act_SetupsColors->Caption, this->Act_SetupsColors->ImageIndex)));
	this->Act_SelectTranslate->Tag = enTag_SelectTrans;
	this->Act_SelectTranslate->Hint = Format("%s|Otwiera panel do wyboru kolorów.|%u", ARRAYOFCONST((this->Act_SelectTranslate->Caption, this->Act_SelectTranslate->ImageIndex)));
	this->Act_Open->Tag = enTag_SetupsColors;
	this->Act_Open->Hint = Format("%s|Otwiera istniejący projekt.|%u", ARRAYOFCONST((this->Act_Open->Caption, this->Act_Open->ImageIndex)));
	this->Act_Save->Tag = enTag_SelectTrans;
	this->Act_Save->Hint = Format("%s|Zapisuje aktualny projekt.|%u", ARRAYOFCONST((this->Act_Save->Caption, this->Act_Save->ImageIndex)));
	this->Act_RenameItem->Tag = enTag_Rename;
	this->Act_RenameItem->Hint = Format("%s|Zmienia tekst w wybranej pozycji.|%u", ARRAYOFCONST((this->Act_RenameItem->Caption, this->Act_RenameItem->ImageIndex)));
	this->Act_NewProject->Tag = enTag_New;
	this->Act_NewProject->Hint = Format("%s|Zmienia tekst w wybranej pozycji.|%u", ARRAYOFCONST((this->Act_NewProject->Caption, this->Act_NewProject->ImageIndex)));
	this->Act_SaveAtGfx->Tag = enTag_SaveAtGfx;
	this->Act_SaveAtGfx->Hint = Format("%s|Zapisuje wykres jako grafikę.|%u", ARRAYOFCONST((this->Act_SaveAtGfx->Caption, this->Act_SaveAtGfx->ImageIndex)));
	this->Act_CreateAllText->Tag = enTag_AllText;
	this->Act_CreateAllText->Hint = Format("%s|Tworzy i zapisuje zawartość wszystkich wersetów w pliku tekstowego.|%u", ARRAYOFCONST((this->Act_CreateAllText->Caption, this->Act_CreateAllText->ImageIndex)));
	this->Act_CutCopyToPaste->Tag = enTag_CutCopyToPaste;
	this->Act_CutCopyToPaste->Hint = Format("%s|Kopiuje zaznaczony element, by go następnie wkleić.|%u", ARRAYOFCONST((this->Act_CutCopyToPaste->Caption, this->Act_CutCopyToPaste->ImageIndex)));
	this->Act_PasteFromCopy->Tag = enTag_PasteFromcopy;
	this->Act_PasteFromCopy->Hint = Format("%s|Wkleje wcześniej skopiowany element, w miejsce zaznaczenia.|%u", ARRAYOFCONST((this->Act_PasteFromCopy->Caption, this->Act_PasteFromCopy->ImageIndex)));
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::_OpenSetupsVisualScheme()
/**
	OPIS METOD(FUNKCJI): Otwarcie panelu ustawień
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
		int iTop, iLeft;
		// Wyszukanie akcji konfiguracji
		for(int i=0; i<this->ActionToolBarMain->ControlCount; ++i)
		{
			TControl *pControl = this->ActionToolBarMain->Controls[i];
			if(pControl->Action->Tag == enTag_SetupsColors)
			{
				iLeft = pControl->Left + this->ActionToolBarMain->Left;
				iTop	= this->ActionToolBarMain->Top + this->ActionToolBarMain->Height;
			}
		}

		this->_pPanelSetups = new TPanel(this);
		if(!this->_pPanelSetups) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		this->_pPanelSetups->Parent = this;
		this->_pPanelSetups->Top = iTop; this->_pPanelSetups->Left = iLeft;
		this->_pPanelSetups->Width = 168; this->_pPanelSetups->Height = 360;
		this->_pPanelSetups->Visible = false;

		TPanel *pPanelButtons = new TPanel(this->_pPanelSetups);
		if(!pPanelButtons) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		pPanelButtons->Parent = this->_pPanelSetups;
		pPanelButtons->Align = alBottom;
		pPanelButtons->AlignWithMargins = true;

		TButton *pButtonSave = new TButton(pPanelButtons);
		if(!pButtonSave) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		pButtonSave->Parent = pPanelButtons;
		pButtonSave->Align = alLeft;
		pButtonSave->AlignWithMargins = true;
		pButtonSave->Width = 70;
		pButtonSave->Margins->Left = 6; pButtonSave->Margins->Top = 6;
		pButtonSave->Margins->Bottom = 6;
		pButtonSave->Caption = "Zapisz";
		pButtonSave->OnClick = this->_OnAllButtonSetups;
		pButtonSave->Tag = enTag_ConfigAccept;

		TButton *pButtonExit = new TButton(pPanelButtons);
		if(!pButtonExit) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		pButtonExit->Parent = pPanelButtons;
		pButtonExit->Align = alRight;
		pButtonExit->AlignWithMargins = true;
		pButtonExit->Width = 70;
		pButtonExit->Margins->Right = 6; pButtonExit->Margins->Top = 6;
		pButtonExit->Margins->Bottom = 6;
		pButtonExit->Caption = "Anuluj";
		pButtonExit->OnClick = this->_OnAllButtonSetups;
		pButtonExit->Tag = enTag_ConfigNoAccept;
		//Kolor zaznaczonego wersetu
		TPanel *pPanelSel = new TPanel(this->_pPanelSetups);
		if(!pPanelSel) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		pPanelSel->Parent = this->_pPanelSetups;
		pPanelSel->Align = alTop;
		pPanelSel->AlignWithMargins = true;
		pPanelSel->AutoSize = true;

		TLabel *pLabelSel = new TLabel(pPanelSel);
		if(!pLabelSel) throw(Exception("Błąd inicjalizacji objektu TLabel"));
		pLabelSel->Parent = pPanelSel;
		pLabelSel->Align = alTop;
		pLabelSel->AlignWithMargins = true;
		pLabelSel->Caption = "Kolor zaznaczonego wersetu";

		this->_pCBSelect = new TColorBox(pPanelSel);
		if(!this->_pCBSelect) throw(Exception("Błąd inicjalizacji objektu TColorBox"));
		this->_pCBSelect->Parent = pPanelSel;
		this->_pCBSelect->Align = alTop;
		this->_pCBSelect->AlignWithMargins = true;
		this->_pCBSelect->OnGetColors = this->_OnGetColors;
		this->_pCBSelect->Style = TColorBoxStyle() << cbStandardColors << cbExtendedColors << cbPrettyNames << cbCustomColors;

		//Kontrolki koloru głównego wersetu
		TPanel *pPanelColMain = new TPanel(this->_pPanelSetups);
		if(!pPanelColMain) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		pPanelColMain->Parent = this->_pPanelSetups;
		pPanelColMain->Align = alTop;
		pPanelColMain->AlignWithMargins = true;
		pPanelColMain->AutoSize = true;

		TLabel *pLabelColMain = new TLabel(pPanelColMain);
		if(!pLabelColMain) throw(Exception("Błąd inicjalizacji objektu TLabel"));
		pLabelColMain->Parent = pPanelColMain;
		pLabelColMain->Align = alTop;
		pLabelColMain->AlignWithMargins = true;
		pLabelColMain->Caption = "Kolor głownego wersetu";

		this->_pCBRoot = new TColorBox(pPanelColMain);
		if(!this->_pCBRoot) throw(Exception("Błąd inicjalizacji objektu TColorBox"));
		this->_pCBRoot->Parent = pPanelColMain;
		this->_pCBRoot->Align = alTop;
		this->_pCBRoot->AlignWithMargins = true;
		this->_pCBRoot->OnGetColors = this->_OnGetColors;
		this->_pCBRoot->Style = TColorBoxStyle() << cbStandardColors << cbExtendedColors << cbPrettyNames << cbCustomColors;
		//Kontrolki koloru lini
		TPanel *pPanelColLine = new TPanel(this->_pPanelSetups);
		if(!pPanelColLine) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		pPanelColLine->Parent = this->_pPanelSetups;
		pPanelColLine->Align = alTop;
		pPanelColLine->AlignWithMargins = true;
		pPanelColLine->AutoSize = true;

		TLabel *pLabelColLine =	 new TLabel(pPanelColLine);
		if(!pLabelColLine) throw(Exception("Błąd inicjalizacji objektu TLabel"));
		pLabelColLine->Parent = pPanelColLine;
		pLabelColLine->Align = alTop;
		pLabelColLine->AlignWithMargins = true;
		pLabelColLine->Caption = "Kolor lini na wykresie";

		this->_pCBLine = new TColorBox(pPanelColLine);
		if(!this->_pCBLine) throw(Exception("Błąd inicjalizacji objektu TColorBox"));
		this->_pCBLine->Parent = pPanelColLine;
		this->_pCBLine->Align = alTop;
		this->_pCBLine->AlignWithMargins = true;
		this->_pCBLine->OnGetColors = this->_OnGetColors;
		this->_pCBLine->Style = TColorBoxStyle() << cbStandardColors << cbExtendedColors << cbPrettyNames << cbCustomColors;
		//Kontrolki ustwiania szerokości lini
		TPanel *pPanelWidLine = new TPanel(this->_pPanelSetups);
		if(!pPanelWidLine) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		pPanelWidLine->Parent = this->_pPanelSetups;
		pPanelWidLine->Align = alTop;
		pPanelWidLine->AlignWithMargins = true;
		pPanelWidLine->AutoSize = true;

		TLabel *pLabelWidLine =	 new TLabel(pPanelWidLine);
		if(!pLabelWidLine) throw(Exception("Błąd inicjalizacji objektu TLabel"));
		pLabelWidLine->Parent = pPanelWidLine;
		pLabelWidLine->Align = alTop;
		pLabelWidLine->AlignWithMargins = true;
		pLabelWidLine->Caption = "Szerokość lini";

		this->_pSpinEdit = new TSpinEdit(pPanelWidLine);
		if(!this->_pSpinEdit) throw(Exception("Błąd inicjalizacji objektu TSpinEdit"));
		this->_pSpinEdit->Parent = pPanelWidLine;
		this->_pSpinEdit->Align = alTop;
		this->_pSpinEdit->AlignWithMargins = true;
		this->_pSpinEdit->MinValue = 1;
		this->_pSpinEdit->MaxValue = 6;
		// Ustawianie przezroczystości
		TPanel *pTransparent = new TPanel(this->_pPanelSetups);
		if(!pTransparent) throw(Exception("Błąd inicjalizacji objektu TPanel"));
		pTransparent->Parent = this->_pPanelSetups;
		pTransparent->Align = alTop;
		pTransparent->AlignWithMargins = true;
		pTransparent->AutoSize = true;

		TLabel *pLabelTr =	new TLabel(pTransparent);
		if(!pLabelTr) throw(Exception("Błąd inicjalizacji objektu TLabel"));
		pLabelTr->Parent = pTransparent;
		pLabelTr->Align = alTop;
		pLabelTr->AlignWithMargins = true;
		pLabelTr->Caption = "Przezroczystość elementów";

		this->pCBoxIsTransparent = new TCheckBox(pTransparent);
		if(!this->pCBoxIsTransparent) throw(Exception("Błąd inicjalizacji objektu TCheckBox"));
		this->pCBoxIsTransparent->Parent = pTransparent;
		this->pCBoxIsTransparent->Align = alTop;
		this->pCBoxIsTransparent->Height = 42;
		this->pCBoxIsTransparent->AlignWithMargins = true;
		this->pCBoxIsTransparent->Caption = "Czy objekty maja być przezroczyste?";
		this->pCBoxIsTransparent->WordWrap = true;

		//Odczyt konfiguracji
		this->pCBoxIsTransparent->Checked = this->_pGsMasterRel->Global_IsTransparent;
		this->_pCBLine->Selected = this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_Line];
		this->_pCBRoot->Selected = this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_Rot];
		this->_pCBSelect->Selected = this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_Active];
		this->_pSpinEdit->Value = this->_pGsMasterRel->Global_iWidthLineScheme;
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::_OpenSelectTranslate()
/**
	OPIS METOD(FUNKCJI): Otwarcie panelu ustawień
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	int iTop, iLeft;
	// Wyszukanie akcji konfiguracji
	for(int i=0; i<this->ActionToolBarMain->ControlCount; ++i)
	{
		TControl *pControl = this->ActionToolBarMain->Controls[i];
		if(pControl->Action->Tag == enTag_SelectTrans)
		{
			iLeft = pControl->Left + this->ActionToolBarMain->Left;
			iTop	= this->ActionToolBarMain->Top + this->ActionToolBarMain->Height;
		}
	}

	this->_pPanelSelectTranslate = new TPanel(this);
	if(!this->_pPanelSelectTranslate) throw(Exception("Błąd inicjalizacji objektu TPanel"));
	this->_pPanelSelectTranslate->Parent = this;
	this->_pPanelSelectTranslate->Top = iTop; this->_pPanelSelectTranslate->Left = iLeft;
	this->_pPanelSelectTranslate->Width = 280; this->_pPanelSelectTranslate->Height = 280;
	this->_pPanelSelectTranslate->Visible = false;

	this->pLBox = new TListBox(this->_pPanelSelectTranslate);
	this->pLBox->Parent = this->_pPanelSelectTranslate;
	this->pLBox->Align = alClient;
	GsReadBibleTextItem *pGsReadBibleTextItem = nullptr;
	this->pLBox->Items->BeginUpdate();
	for(int i=0; i<GlobalVar::SDirTranslatesList.Length; ++i)
	{
		//--- Zwraca nazwę tłumaczenia niezależnie od jego statusu (aktywny, lub nie)
		pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(i);
		if(TPath::GetExtension(GlobalVar::SDirTranslatesList[i]) == GsReadBibleTextData::GsExtendNoAsteriskFileTranslateFull)
		{
			this->pLBox->Items->Add(Format("%s - %s",
				ARRAYOFCONST((TPath::GetFileNameWithoutExtension(GlobalVar::SDirTranslatesList[i]),
				pGsReadBibleTextItem->NameTranslate))));
		}
	}
	this->pLBox->ItemIndex = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeNumTranslate, 0);
	this->pLBox->Items->EndUpdate();

	TPanel *pPanelButtons = new TPanel(this->_pPanelSelectTranslate);
	if(!pPanelButtons) throw(Exception("Błąd inicjalizacji objektu TPanel"));
	pPanelButtons->Parent = this->_pPanelSelectTranslate;
	pPanelButtons->Align = alBottom;
	pPanelButtons->AlignWithMargins = true;

	TButton *pButtonSave = new TButton(pPanelButtons);
	if(!pButtonSave) throw(Exception("Błąd inicjalizacji objektu TPanel"));
	pButtonSave->Parent = pPanelButtons;
	pButtonSave->Align = alLeft;
	pButtonSave->AlignWithMargins = true;
	pButtonSave->Width = 70;
	pButtonSave->Margins->Left = 6; pButtonSave->Margins->Top = 6;
	pButtonSave->Margins->Bottom = 6;
	pButtonSave->Caption = "Zapisz";
	pButtonSave->OnClick = this->_OnAllButtonSetups;
	pButtonSave->Tag = enTag_ConfigAccept;

	TButton *pButtonExit = new TButton(pPanelButtons);
	if(!pButtonExit) throw(Exception("Błąd inicjalizacji objektu TPanel"));
	pButtonExit->Parent = pPanelButtons;
	pButtonExit->Align = alRight;
	pButtonExit->AlignWithMargins = true;
	pButtonExit->Width = 70;
	pButtonExit->Margins->Right = 6; pButtonExit->Margins->Top = 6;
	pButtonExit->Margins->Bottom = 6;
	pButtonExit->Caption = "Anuluj";
	pButtonExit->OnClick = this->_OnAllButtonSetups;
	pButtonExit->Tag = enTag_ConfigNoAccept;
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::_CloseSetupsPanels()
/**
	OPIS METOD(FUNKCJI): Zamykanie paneli konfiguracyjnych
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pPanelSetups->Visible = false;
	this->_pPanelSelectTranslate->Visible = false;
	this->Act_SetupsColors->Checked = false;
	this->Act_SelectTranslate->Checked = false;
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::_OnGetColors(TCustomColorBox *Sender, TStrings *Items)
/**
	OPIS METOD(FUNKCJI): Metoda do obsługi zdarzenia OnGetColors, kontrolki TColorBox
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	Items->AddStrings(GlobalVar::Global_ItemsColor); // Przyporządkowanie listy kolorów z ogólnej listy
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::_OnAllButtonSetups(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI): Metoda akceptacji i zapisu ustawień,
											 służy obsługi zdarzenia OnClick, kontrolki TButton w panelu ustawień kolorów
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TButton *pButt = dynamic_cast<TButton *>(Sender);
	if(!pButt) return;
	//---
	this->Act_SetupsColors->Checked = false;
	this->_pPanelSetups->Visible = false;
	this->Act_SelectTranslate->Checked = false;
	this->_pPanelSelectTranslate->Visible = false;

	switch(pButt->Tag)
	{
		case enTag_ConfigAccept:
			//Wypełnienie zmiennych konfiguracyjnych, by je zapisać
			this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_Line] = this->_pCBLine->Selected;
			//this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_InActive] = clCream;
			this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_Rot] = this->_pCBRoot->Selected;
			this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_Active] = this->_pCBSelect->Selected;
			this->_pGsMasterRel->Global_iWidthLineScheme = this->_pSpinEdit->Value;
			this->_pGsMasterRel->Global_IsTransparent = this->pCBoxIsTransparent->Checked;

			this->_WriteConfig(); // Zapis zmienionej konfiguracji
		break;
		//---
		case enTag_ConfigNoAccept:
			//Odczytanie starych ustawień do bufora, pliku ini, z TStringListy
			GlobalVar::Global_ConfigFile->SetStrings(this->_SListOldConfig);

			this->_ReadConfig(); // Ponowny odczyt zmienionej konfiguracji
			this->pLBox->ItemIndex = GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeNumTranslate, 0);
			// Ponowne przyporządkowanie kolorów do kontrolek
			this->_pCBLine->Selected = this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_Line];
			this->_pCBRoot->Selected = this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_Rot];
			this->_pCBSelect->Selected = this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_Active];
			this->_pSpinEdit->Value = this->_pGsMasterRel->Global_iWidthLineScheme;
			this->pCBoxIsTransparent->Checked = this->_pGsMasterRel->Global_IsTransparent;
		break;
	}
	this->_pGsMasterRel->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::_OnMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_CloseSetupsPanels(); // Zamykanie paneli konfiguracyjnych

	if(Sender->ClassNameIs("GsChild") && this->_IsSelectToCopyCut)
	// Aktywacja akcji wklejania skopiowanej gałęzi jeśli wybrano element docelowy i jest nim objekt klasy GsChild
	{
		this->Act_PasteFromCopy->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::_ReadConfig()
/**
	OPIS METOD(FUNKCJI): Odczyt konfiguracji kolorów
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pGsMasterRel->Global_IsTransparent =
		GlobalVar::Global_ConfigFile->ReadBool(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetIsTransparent, false);
	this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_Line] =
		(TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeColorLine, clBlue);
	this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_Active] =
		(TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeColorSelect, clAqua);
	this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_InActive] = clCream;
	this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_Rot] =
		(TColor)GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeColorRot, clYellow);
	this->_pGsMasterRel->Global_iWidthLineScheme =
		GlobalVar::Global_ConfigFile->ReadInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeWidthLine, 2);
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::_WriteConfig()
/**
	OPIS METOD(FUNKCJI): Zapis konfiguracji
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GlobalVar::Global_ConfigFile->WriteBool(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetIsTransparent, this->_pGsMasterRel->Global_IsTransparent);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeColorLine, this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_Line]);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeColorSelect, this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_Active]);
	this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_InActive] = clCream;
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeColorRot, this->_pGsMasterRel->Global_ColorsSchemeTable[enColorSchemeNum_Rot]);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeWidthLine, this->_pGsMasterRel->Global_iWidthLineScheme);
	GlobalVar::Global_ConfigFile->WriteInteger(GlobalVar::GlobalIni_SetupsSchemeVers, GlobalVar::GlobalIni_SetSchemeNumTranslate, this->pLBox->ItemIndex);
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::TrViewMainGetImageIndex(TObject *Sender,
					TTreeNode *Node)
/**
	OPIS METOD(FUNKCJI): Ikonki dla drzewa TTreeView
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TTreeView *pTV = dynamic_cast<TTreeView *>(Sender);
	if(!pTV) return;
	//---
	if(Node->Level == 0)
	{
		Node->ImageIndex = enImageSmall_Root;
		Node->SelectedIndex = enImageSmall_Root;;
	}
	else
	{
		Node->ImageIndex = enImageSmall_Child;
		Node->SelectedIndex = enImageSmall_Child;
	}
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::TrViewMainClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TTreeView *pTV = dynamic_cast<TTreeView *>(Sender);
	if(!pTV) return;
	//---

	TTreeNode *pNode = pTV->Selected; //Wybrany węzeł
	if(pNode)
	{
		GsChild *pGsChild = static_cast<GsChild *>(pNode->Data);
		this->_pGsMasterRel->SelectChildItem = pGsChild; // Zmiana zaznaczonej pozycji
//		for(int i=0; i<pTV->SelectionCount; ++i)
//		{
//
//		}
	}
}
//========================== AKCJE DLA OKNA =================================
void __fastcall TNewSchemeVersWindow::Act_AddItemExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	this->_CloseSetupsPanels(); // Zamykanie paneli konfiguracyjnych
	//Wypelnianie pól adresu wersetu
	unsigned char _ucBook, _ucChapt, _ucVers, _ucTrans;
	UnicodeString ustrText;

	this->_pGsBarSelectVers->GetSelectAdress(_ucBook, _ucChapt, _ucVers, _ucTrans); // _ucTrans nieużywane
	GsReadBibleTextData::GetTextVersOfAdress(_ucBook, _ucChapt+1, _ucVers, this->pLBox->ItemIndex, ustrText);

	this->_pGsMasterRel->AddNewObjectScheme(this->_pGsBarSelectVers->GetSelectVers(), ustrText);

	this->Act_DelItem->Enabled = true;
	this->Act_SaveAtGfx->Enabled = true;
	this->Act_RenameItem->Enabled = true;
	this->Act_Save->Enabled = true;
	this->Act_CreateAllText->Enabled = true;
	this->Act_CutCopyToPaste->Enabled = true;

	this->_pGsHelp->HelpText = ustrHelpText[enTagHelp_Exist];
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::Act_DelItemExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	this->_CloseSetupsPanels(); // Zamykanie paneli konfiguracyjnych
	int iResult = MessageBox(NULL, TEXT("Czy rzeczywiście chcesz skasować objekt razem ze wszystkimi jego pochodnymi?"), TEXT("Pytanie aplikacji"), MB_YESNO | MB_ICONWARNING | MB_TASKMODAL | MB_DEFBUTTON2);
	if(iResult == IDNO) return;
	this->_pGsMasterRel->DeleteObject();
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::Act_SetupsColorsExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Otwarcie panelu z ustawieniami kolorów
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	this->_pPanelSetups->Visible = pAction->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::Act_SelectTranslateExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Otwarcie panelu wyboru tłumaczeń
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	this->_pPanelSelectTranslate->Visible = pAction->Checked;
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::Act_OpenExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Otwarcie projektu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	this->_CloseSetupsPanels(); // Zamykanie paneli konfiguracyjnych
	UnicodeString ustrNameProject;
	bool bReturn = this->_pGsMasterRel->OpenProject(ustrNameProject);
	this->Caption = Format("%s - Uktualny projekt: \"%s\"", ARRAYOFCONST((custrTextWindow, TPath::GetFileName(ustrNameProject))));

	if(!bReturn) return;

	this->Act_DelItem->Enabled = true;
	this->Act_SaveAtGfx->Enabled = true;
	this->Act_RenameItem->Enabled = true;
	this->Act_Save->Enabled = true;
	this->Act_CreateAllText->Enabled = true;
	this->Act_CutCopyToPaste->Enabled = true;

	this->_pGsHelp->HelpText = ustrHelpText[enTagHelp_Exist];
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::Act_SaveExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Zapis projektu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	this->_CloseSetupsPanels(); // Zamykanie paneli konfiguracyjnych
	UnicodeString ustrNameProject;
	this->_pGsMasterRel->SaveProject(ustrNameProject);
	this->Caption = Format("%s - Uktualny projekt: \"%s\"", ARRAYOFCONST((custrTextWindow, TPath::GetFileName(ustrNameProject))));
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::Act_RenameItemExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Zmiana zawartosci objektu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	this->_CloseSetupsPanels(); // Zamykanie paneli konfiguracyjnych
	GsChild* pGsChild=nullptr;
	pGsChild = this->_pGsMasterRel->SelectChildItem;
	if(!pGsChild) return;

	int iResult = MessageBox(NULL, TEXT("Czy jesteś pewny, że chcesz zmienić zawartość zaznaczonej pozycji?"),
													 TEXT("Pytanie aplikacji"), MB_YESNO | MB_ICONWARNING | MB_TASKMODAL | MB_DEFBUTTON2);
	if(iResult == IDNO) return;
	//Wypełnianie pól adresu wersetu
	unsigned char _ucBook, _ucChapt, _ucVers, _ucTrans;
	UnicodeString ustrText;

	this->_pGsBarSelectVers->GetSelectAdress(_ucBook, _ucChapt, _ucVers, _ucTrans); // _ucTrans nieużywane
	GsReadBibleTextData::GetTextVersOfAdress(_ucBook, _ucChapt+1, _ucVers, this->pLBox->ItemIndex, ustrText);
	this->_pGsMasterRel->RenameTextItem(this->_pGsBarSelectVers->GetSelectVers(), ustrText);
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::Act_NewProjectExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Nowy projekt
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	this->_CloseSetupsPanels(); // Zamykanie paneli konfiguracyjnych
	int iResult = MessageBox(NULL, TEXT("Czy rzeczywiście chcesz porzucić aktualny projekt i rozpocząć nowy?"), TEXT("Pytanie aplikacji"), MB_YESNO | MB_ICONWARNING | MB_TASKMODAL | MB_DEFBUTTON2);
	if(iResult == IDNO) return;
	this->_pGsMasterRel->NewProject();

	this->Act_DelItem->Enabled = false;
	this->Act_SaveAtGfx->Enabled = false;
	this->Act_RenameItem->Enabled = false;
	this->Act_Save->Enabled = false;
	this->Act_CreateAllText->Enabled = false;
	this->Act_CutCopyToPaste->Enabled = false;
	this->Act_PasteFromCopy->Enabled = false;

	this->_pGsHelp->HelpText = ustrHelpText[enTagHelp_New];
	this->Caption = Format("%s - Uktualny projekt: \"%s\"", ARRAYOFCONST((custrTextWindow, custrProjectNameDefault)));
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::Act_SaveAtGfxExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Zapisz wykres jako grafikę
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	const UnicodeString ustrFileTypes[] = {"Pliki PNG", "*.png",
																				 "Plik JPG", "*.jpg"};
	UnicodeString ustrPathSave;
	TFileSaveDialog *pFileSaveDialog = new TFileSaveDialog(this);
	if(!pFileSaveDialog) throw(Exception("Błąd inicjalizacji objektu TFileSaveDialog"));
	pFileSaveDialog->Title = "Podaj nazwę pliku graficznego do zapisu";
	for(int i=0; i<ARRAYSIZE(ustrFileTypes); i+=2)
	{
		TFileTypeItem *pTFileTypeItem = pFileSaveDialog->FileTypes->Add();
		pTFileTypeItem->DisplayName = ustrFileTypes[i];
		pTFileTypeItem->FileMask = ustrFileTypes[i+1];
	}
	pFileSaveDialog->Options = TFileDialogOptions() << fdoOverWritePrompt << fdoFileMustExist;
	pFileSaveDialog->DefaultFolder = GlobalVar::Global_custrGetExeDir; //Katalog aplikacji
	pFileSaveDialog->DefaultExtension = ".png"; // Automatyczne dodawanie rozrzeżenia
	pFileSaveDialog->FileName = "Bez nazwy";

	try
	{
		try
		{
			if(pFileSaveDialog->Execute())
			{
				ustrPathSave = pFileSaveDialog->FileName;
				this->_pGsMasterRel->SaveToGfx(ustrPathSave);
			}
		}
		catch(const Exception& e)
		{
			MessageBox(NULL, Format("Błąd: \"%s\"", ARRAYOFCONST((ustrPathSave))).c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{
		if(pFileSaveDialog) {delete pFileSaveDialog; pFileSaveDialog = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::Act_CreateAllTextExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Stworzenie pliku typu txt z zawartością wszystkich pozycji
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	const UnicodeString ustrFileTypes[] = {"Pliki TXT", "*.txt"};
	UnicodeString ustrPathSave;
	TFileSaveDialog *pFileSaveDialog = new TFileSaveDialog(this);
	if(!pFileSaveDialog) throw(Exception("Błąd inicjalizacji objektu TFileSaveDialog"));
	pFileSaveDialog->Title = "Podaj nazwę pliku graficznego do zapisu";
	for(int i=0; i<ARRAYSIZE(ustrFileTypes); i+=2)
	{
		TFileTypeItem *pTFileTypeItem = pFileSaveDialog->FileTypes->Add();
		pTFileTypeItem->DisplayName = ustrFileTypes[i];
		pTFileTypeItem->FileMask = ustrFileTypes[i+1];
	}
	pFileSaveDialog->Options = TFileDialogOptions() << fdoOverWritePrompt << fdoFileMustExist;
	pFileSaveDialog->DefaultFolder = GlobalVar::Global_custrGetExeDir; //Katalog aplikacji
	pFileSaveDialog->DefaultExtension = ".txt"; // Automatyczne dodawanie rozrzeżenia
	pFileSaveDialog->FileName = "Bez nazwy";

	try
	{
		try
		{
			if(pFileSaveDialog->Execute())
			{
				ustrPathSave = pFileSaveDialog->FileName;
				this->_pGsMasterRel->SaveToAllText(ustrPathSave);
			}
		}
		catch(const Exception& e)
		{
			MessageBox(NULL, Format("Błąd: \"%s\"", ARRAYOFCONST((ustrPathSave))).c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{
		if(pFileSaveDialog) {delete pFileSaveDialog; pFileSaveDialog = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::Act_CutCopyToPasteExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Skopiowanie lub wycięcie zaznaczonego elementu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	this->_pGsMasterRel->CutCopyToPaste();
	this->_IsSelectToCopyCut = true; // Zaznaczono wybrany objekt, i wykonano akcje Act_CutCopyToPasteExecute()
}
//---------------------------------------------------------------------------
void __fastcall TNewSchemeVersWindow::Act_PasteFromCopyExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Wstawienie skopiowanego elementu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//---
	UnicodeString ustrText = UnicodeString("Chcesz pszenieść gałąź do tej samej lokalizacji, lub do własnego potomka.") +
																				 "Wybierz inna lokalizację dla przenoszonej gałęzi objektów" +
																				 "Powtórz całą operacje od początku, zaznaczająć prawidłowo miejsce przeznaczenie dla przeniesionej gałęzi objektów";
	bool bRet = this->_pGsMasterRel->PasteFromCopy();
	if(!bRet)
	{
		MessageBox(NULL, ustrText.c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
	}
	pAction->Enabled = false;
	this->_IsSelectToCopyCut = false; // Zaznaczono wybrany objekt, i wykonano akcje Act_CutCopyToPasteExecute()
}
//---------------------------------------------------------------------------

