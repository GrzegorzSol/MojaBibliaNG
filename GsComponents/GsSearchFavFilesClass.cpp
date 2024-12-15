#pragma hdrstop

#include "GsSearchFavFilesClass.h"
#include "GsSearchFavFilesDataImages.h"
#include "uGlobalVar.h"
#include <SHDocVw.hpp>			//TWebBrowser

#if defined(_DEBUGINFO_)
	#include "GsDebugClass.h"
#endif
//---------------------------------------------------------------------------
#pragma package(smart_init)

const UnicodeString custrPMenu[] = {"Sakasuj plik wyszukiwania"};
enum	{
				enSelectPopup_Delete = 100,
			};
//---------------------------------------------------------------------------
__fastcall GsSearchFavFilesClass::GsSearchFavFilesClass(TComponent* Owner) : TCustomListView(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pHSListSelect = new THashedStringList();
	if(!this->_pHSListSelect) throw(Exception("Nie dokonano inicjalizacji objektu THashedStringList"));

	this->_pImages = new TImageList(this);
	if(!this->_pImages) throw(Exception("Nie dokonano inicjalizacji objektu TImageList"));
	this->_pImages->ColorDepth = cd32Bit;			//Głębia kolorów przyszłych obrazków
	this->_pImages->DrawingStyle = dsTransparent;
	this->_pImages->Height = 32; this->_pImages->Width = 32;

	this->_pImages16 = new TImageList(this);
	if(!this->_pImages16) throw(Exception("Nie dokonano inicjalizacji objektu TImageList"));
	this->_pImages16->ColorDepth = cd32Bit;			//Głębia kolorów przyszłych obrazków
	this->_pImages16->DrawingStyle = dsTransparent;

	this->_InitAllImage();	//Inicjalizacja danych dla listy obrazków

	this->ViewStyle = TViewStyle::vsIcon;
	this->Font->Quality = TFontQuality::fqClearType;
	this->ParentFont = true;
	this->DoubleBuffered = true;
	//this->MultiSelect = true;
	this->ReadOnly = true;
	this->LargeImages = this->_pImages;
	//PopupMenu [13-10-2023]
	this->_pPopupM = new TPopupMenu(this);
	if(!this->_pPopupM) throw(Exception("Błąd inicjalizacji objektu klasy TPopupMenu"));
	this->_pPopupM->AutoHotkeys = maManual; //Brak podkreśleń
	this->_pPopupM->AutoPopup = false;
	this->_pPopupM->Images = this->_pImages16;
	for(int i=0; i<ARRAYSIZE(custrPMenu); ++i)
	{
		TMenuItem *NewItem = new TMenuItem(this->_pPopupM);
		if(!NewItem) throw(Exception("Błąd funkcji TMenuItem"));
		this->_pPopupM->Items->Add(NewItem);
		NewItem->Caption = custrPMenu[i];
		NewItem->Tag = enSelectPopup_Delete + i;
		NewItem->OnClick = this->_OnClick_PMenu;
		NewItem->ImageIndex = i;
	}
}
//---------------------------------------------------------------------------
__fastcall GsSearchFavFilesClass::~GsSearchFavFilesClass()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->_pHSListSelect) {delete this->_pHSListSelect; this->_pHSListSelect = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall GsSearchFavFilesClass::_InitAllImage()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TIcon *pIcon=nullptr;
	TMemoryStream *pMemoryStr=nullptr;

	try
	{
		pIcon = new TIcon();
		if(!pIcon) throw(Exception("Błąd metody TIcon"));
		pMemoryStr = new TMemoryStream();
		if(!pMemoryStr) throw(Exception("Błąd metody TMemoryStream"));

		pMemoryStr->WriteBuffer(chDataGfxSearchFavFiles, ARRAYSIZE(chDataGfxSearchFavFiles)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->_pImages->AddIcon(pIcon);												//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();

		pMemoryStr->WriteBuffer(chDataDeleteSelectItem, ARRAYSIZE(chDataDeleteSelectItem)); //Zapis do strumienia danych
		pMemoryStr->Position = 0;															//Ustawienia wskażnika strumienia na początek
		pIcon->LoadFromStream(pMemoryStr);										//Wczytanie danych ze strumienia do objektu, klasy TIcon
		this->_pImages16->AddIcon(pIcon);												//Dodanie ikony do listu, objektu klasy TImageList
		pMemoryStr->Clear();

	}
	__finally
	{
		//--- Zwolnienie objektu, klasy TIcon i TMemoryStream
		if(pIcon) {delete pIcon; pIcon = nullptr;}
		if(pMemoryStr) {delete pMemoryStr; pMemoryStr = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall GsSearchFavFilesClass::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomListView::CreateWnd();
	//Własny kod.
	this->ReadDirectoryFavSearch();
}
//---------------------------------------------------------------------------
void __fastcall GsSearchFavFilesClass::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TCustomListView::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsSearchFavFilesClass::DoSelectItem(TListItem* Item, bool Selected)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!Item) return;
	//---
	if(Selected)
	{
		this->_FustrSelectFile = TPath::Combine(GlobalVar::Global_custrPathSearchFavorities, Item->Caption);
	}
	if(this->_FOnSelectItem) this->_FOnSelectItem(this, Item, Selected);
}
//---------------------------------------------------------------------------
void __fastcall GsSearchFavFilesClass::DblClick()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TForm *mainForm = Application->MainForm;
	if(mainForm)
	{
		WideString wstrSelectFileToWeb = "file://" + this->SelectFile;
		TForm *pWindowTextSearch = new TForm(mainForm);
		if(pWindowTextSearch)
		{
			pWindowTextSearch->Height = 900; pWindowTextSearch->Width = 1100;
			pWindowTextSearch->Caption = TPath::GetFileNameWithoutExtension(this->SelectFile);

			TWebBrowser* pWebBrowser = new TWebBrowser(pWindowTextSearch);
			if(!pWebBrowser) throw(Exception("Błąd inicjalizacji klasy TWebBrowser"));
			pWebBrowser->TOleControl::Parent = pWindowTextSearch;
			pWebBrowser->Align = alClient;
			pWebBrowser->Offline = true;
			//pWebBrowser->Navigate(WideString("about:blank").c_bstr()); // wypełnienie kontrolki pustą stroną.
			pWebBrowser->Navigate(wstrSelectFileToWeb.c_bstr());

			pWindowTextSearch->Show();
		}
	}
	//Jeśli istnieje zewnętrzna metoda OnDblClick() to ją wywołaj
	if(this->_FOnDblClick) this->_FOnDblClick(this);
}
//---------------------------------------------------------------------------
void __fastcall GsSearchFavFilesClass::MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPoint popupPoint;
	if(!this->Selected || Button != mbRight) return;
	GetCursorPos(&popupPoint);

	this->_pPopupM->Popup(popupPoint.x, popupPoint.y);
}
//---------------------------------------------------------------------------
void __fastcall GsSearchFavFilesClass::_CreateListSelect()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TItemStates selected = TItemStates() << isSelected;
	TListItem *pListItem = this->Selected;

	this->_pHSListSelect->Clear();
	this->_pHSListSelect->BeginUpdate();
	while(pListItem)
	{
		this->_pHSListSelect->Add(TPath::Combine(GlobalVar::Global_custrPathSearchFavorities, pListItem->Caption));
		pListItem = this->GetNextItem(pListItem, sdAll, selected);
	}
	this->_pHSListSelect->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall GsSearchFavFilesClass::_OnClick_PMenu(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TMenuItem *pMItem = dynamic_cast<TMenuItem *>(Sender);
	if(!pMItem) return;
	//---
	switch(pMItem->Tag)
	{
		case enSelectPopup_Delete:
		{
			this->DeleteSelectFile();
		}
		break;
		//---
	}
}
//---------------------------------------------------------------------------
void __fastcall GsSearchFavFilesClass::ReadDirectoryFavSearch()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListItem *NewItem=nullptr;
	this->Clear();

	this->_SDirSearchFilesFav = TDirectory::GetFiles(GlobalVar::Global_custrPathSearchFavorities, "*" + GlobalVar::Global_custrFileSearchFavExtend, 0);
	this->Items->BeginUpdate();
	for(int i=0; i<this->_SDirSearchFilesFav.Length; ++i)
	{
		NewItem = this->Items->Add();
		if(NewItem)
		{
			NewItem->Caption = TPath::GetFileName(this->_SDirSearchFilesFav[i]);
		}
	}
	this->Items->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall GsSearchFavFilesClass::DeleteSelectFile()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->_FustrSelectFile.IsEmpty()) return;
	//---
	UnicodeString ustrTemp = Format("Czy rzeczywiście chcesz skasować plik: \"%s\"?", ARRAYOFCONST(( this->_FustrSelectFile )));
	int iResult = MessageBox(NULL, ustrTemp.c_str(), TEXT("Pytanie aplikacji"), MB_YESNO | MB_ICONQUESTION | MB_TASKMODAL | MB_DEFBUTTON2);
	if(iResult == IDNO) return;

	TFile::Delete(this->_FustrSelectFile);
	this->ReadDirectoryFavSearch();
}
//---------------------------------------------------------------------------

