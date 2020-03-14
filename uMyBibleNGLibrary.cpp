//---------------------------------------------------------------------------
#pragma hdrstop

#include "uMyBibleNGLibrary.h"
#include "uGlobalVar.h"
#include <System.IOUtils.hpp>
#include <Jpeg.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
#if defined(__BORLANDC__) && defined(__clang__) && defined(_WIN32)
*/
/****************************************************************************
*                        Klasa GsListBoxMultiMClass                         *
*****************************************************************************/
enum {enColumn_Name, enColumn_Size, enColumn_Count};
static const UnicodeString ustrColumsNames[] = {"Nazwa Pliku", "Wielkość pliku"};
static int iColumnIndex=enColumn_Name, //Na którą kolumnę kliknąłeś
					 iToSort=1; //Kierunek sortowania
typedef struct {
									UnicodeString ustrPathName, //Nazwa pliku
                                ustrName;     //Nazwa samego pliku
									int iSizeFile;              //Wielkość pliku
									int iIdIcon;                //Numer ikony, przyporządkowanej plikowi
							 }MULTIDATA, *PMULTIDATA;
//---------------------------------------------------------------------------
__fastcall GsListViewMultiMClass::GsListViewMultiMClass(TComponent* Owner) : TCustomListView(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->DoubleBuffered = true;
	this->OwnerDraw = true;
	this->OwnerData = true;
	this->StyleElements = TStyleElements();
	this->Color = clWebLemonChiffon;
	this->ReadOnly = true;
	this->RowSelect = true;
	this->ViewStyle = vsReport;
	this->ItemIndex = -1;
  this->_iLViewStartIndex=0; this->_iLViewEndIndex=0; //Zakres dolny i górny elementów w liście wirtualnej
	//---
	this->_pListFile = new TList(); //Lista plików
	if(!this->_pListFile) throw(Exception("Błąd inicjalizacji objektu TList"));
	//---
  SHFILEINFO shfi;
	DWORD iHnd;
	this->_pImageList = new TImageList(this);
	if(!this->_pImageList) throw(Exception("Błąd inicjalizacji objektu TImageList"));
	this->_pImageList->DrawingStyle = dsTransparent;
	this->_pImageList->ShareImages = true;
	this->_pImageList->ColorDepth = cd32Bit;
	iHnd = SHGetFileInfo(TEXT(""), 0, &shfi, sizeof(shfi), SHGFI_SYSICONINDEX |
			SHGFI_SHELLICONSIZE | SHGFI_SMALLICON);
	if(iHnd != 0) this->_pImageList->Handle = iHnd;
	DestroyIcon(shfi.hIcon);	//Musi być
  this->SmallImages = this->_pImageList;

	this->_CreateColumns();
  this->OnMouseLeave = this->_OnMouseLeave;
}
//---------------------------------------------------------------------------
__fastcall GsListViewMultiMClass::~GsListViewMultiMClass()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->_pImageList) {delete this->_pImageList; this->_pImageList = 0;}
	if(this->_pListFile)
	{
		this->ClearList();
		delete this->_pListFile;
		this->_pListFile = 0;
	}
}
//---------------------------------------------------------------------------
void __fastcall GsListViewMultiMClass::ClearList()
/**
	OPIS METOD(FUNKCJI): Czyszczenie listy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	PMULTIDATA pMultiData;//=0;
	for(int i=0; i<this->_pListFile->Count; i++)
	{
		pMultiData = static_cast<PMULTIDATA>(this->_pListFile->Items[i]);
		if(pMultiData) {delete pMultiData; /*pMultiData = 0;*/}
	}
	this->_pListFile->Clear();
}
//---------------------------------------------------------------------------
void __fastcall GsListViewMultiMClass::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomListView::CreateWnd();
	//Własny kod.
	if(!TDirectory::Exists(GlobalVar::Global_custrPathMultimediaFilesData))
		throw(Exception(Format("Katalog: %s, z danymi multimedialnymi nie istnieje!", ARRAYOFCONST((GlobalVar::Global_custrPathMultimediaFilesData)))));
	//Odczyt katalogu z plikami multimedialnymi
	this->Items->BeginUpdate();
	this->ClearList();

	TStringDynArray SDirMultiMList;
	TStringList *SListTemp = new TStringList(); //Tymczasowy objekt, z zawartością wszystkich ścieżek dostępu do katalogów z multimediami
	if(!SListTemp) throw(Exception("Błąd inicjalizacji objektu TStringList"));
	SListTemp->Add(GlobalVar::Global_custrPathMultimediaFilesData);
	SListTemp->Add(GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM1, ""));
	SListTemp->Add(GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM2, ""));
	SListTemp->Add(GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM3, ""));
	//Stworzenie listy wszystkich plików z grafiką, ze wszystkich katalogów z multimediami
	PMULTIDATA pMultiData;//=0;
	TWin32FileAttributeData fileInfo;
	SHFILEINFO shfiFile;
	UnicodeString ustrTempLowerName;
	//---
	for(int iSelectDir=0; iSelectDir<SListTemp->Count; iSelectDir++)
	{
		if(SListTemp->Strings[iSelectDir].IsEmpty()) continue;
		SDirMultiMList = TDirectory::GetFiles(SListTemp->Strings[iSelectDir]);//, "*.*", 0);
		for(int i=0; i<SDirMultiMList.Length; i++)
		{
			ustrTempLowerName = LowerCase(SDirMultiMList[i]);
			if((TPath::GetExtension(ustrTempLowerName) != ".jpg") &&
			   (TPath::GetExtension(ustrTempLowerName) != ".jpeg") &&
				 (TPath::GetExtension(ustrTempLowerName) != ".bmp")) continue;
			//---
			pMultiData = new MULTIDATA();
			if(!pMultiData) throw(Exception("Błąd inicjalizacji objektu MULTIDATA"));
			GetFileAttributesEx(SDirMultiMList[i].c_str(), GetFileExInfoStandard, &fileInfo);
			ZeroMemory(&shfiFile, sizeof(shfiFile));
			SHGetFileInfo(SDirMultiMList[i].c_str(), 0, &shfiFile, sizeof(shfiFile), SHGFI_ICON | SHGFI_SYSICONINDEX);
			//---
			pMultiData->ustrPathName = SDirMultiMList[i];
			pMultiData->ustrName = TPath::GetFileName(SDirMultiMList[i]);
			pMultiData->iSizeFile = fileInfo.nFileSizeLow;
			pMultiData->iIdIcon = shfiFile.iIcon;
			this->_pListFile->Add(pMultiData);
		}
		SDirMultiMList.Length = 0;
	}
	this->_pListFile->Sort(this->SortListFiles);
	if(SListTemp) {delete SListTemp; /*SListTemp = 0;*/}

	this->Items->Count = this->_pListFile->Count;
	this->Items->EndUpdate();
}
//---------------------------------------------------------------------------
void __fastcall GsListViewMultiMClass::_CreateColumns()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TListColumn  *NewColumn;//=0;
	for(unsigned int iColumns=0; iColumns<ARRAYSIZE(ustrColumsNames); iColumns++)
	{
		NewColumn = this->Columns->Add();
		NewColumn->Caption = ustrColumsNames[iColumns];
		NewColumn->AutoSize = true;
  }
}
//---------------------------------------------------------------------------
int __fastcall GsListViewMultiMClass::SortListFiles(void * Item1, void * Item2)
/**
	OPIS METOD(FUNKCJI): Sortowanie TList
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	PMULTIDATA pMultiData1 = static_cast<PMULTIDATA>(Item1);
	PMULTIDATA pMultiData2 = static_cast<PMULTIDATA>(Item2);
	if(!pMultiData1 || !pMultiData1) return 0;

	switch(iColumnIndex)
	{
    case enColumn_Name:
			return AnsiCompareStr(pMultiData1->ustrName, pMultiData2->ustrName) * iToSort;
		//break;

		case enColumn_Size:
			if(pMultiData1->iSizeFile == pMultiData2->iSizeFile) return 0;
			else if(pMultiData1->iSizeFile > pMultiData2->iSizeFile) return 1 * iToSort;
			else if(pMultiData1->iSizeFile < pMultiData2->iSizeFile) return -1 * iToSort;
		break;
  }
	return 0;
}
//---------------------------------------------------------------------------
void __fastcall GsListViewMultiMClass::DestroyWnd()
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
bool __fastcall GsListViewMultiMClass::OwnerDataFetch(Comctrls::TListItem* Item, Comctrls::TItemRequest Request)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if ((Item->Index > this->_iLViewEndIndex) || (Item->Index < this->_iLViewStartIndex)) return true;

  if(Request.Contains(irText) || Item->Caption.IsEmpty())
	{
		PMULTIDATA pMultiData = static_cast<PMULTIDATA>(this->_pListFile->Items[Item->Index]);
		if(pMultiData) Item->Caption = pMultiData->ustrPathName;
	}
  else if (Request.Contains(irImage))
	{
		//Item->ImageIndex = pItemInfoFile->iIconId;
		//Item->ImageIndex = pGSFList->ImageIndex;
	}

	return true;
}
//---------------------------------------------------------------------------
bool __fastcall GsListViewMultiMClass::OwnerDataHint(int StartIndex, int EndIndex)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->_iLViewStartIndex = StartIndex; //Dolny zakres, elementów listy
	this->_iLViewEndIndex = EndIndex;     //Górny zakres, elementów listy

	return true;
}
//---------------------------------------------------------------------------
int __fastcall GsListViewMultiMClass::OwnerDataFind(TItemFind Find, const System::UnicodeString FindString, const System::Types::TPoint &FindPosition,
			void *FindData, int StartIndex, TSearchDirection Direction, bool Wrap)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	PMULTIDATA pMultiData;
	for(int i=0; i<this->_pListFile->Count; i++)
	{
		pMultiData = static_cast<PMULTIDATA>(this->_pListFile->Items[i]);
		if (UpperCase(pMultiData->ustrPathName) == UpperCase(FindString)) return i;
  }
	return -1;
}
//---------------------------------------------------------------------------
void __fastcall GsListViewMultiMClass::DoSelectItem(TListItem* Item, bool Selected)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!Selected) return;
	//---
	GsPanelMultiM *pGsPanelMultiM = dynamic_cast<GsPanelMultiM *>(this->Parent);
	if(!pGsPanelMultiM) return;
	//Wyświetlenie wybranego zasobu multimedialnego w objekcie, klasy TImage
	if(!TFile::Exists(Item->Caption)) return;
	pGsPanelMultiM->_ImageView->Stretch = true;
	pGsPanelMultiM->_ImageView->Picture->LoadFromFile(Item->Caption);
}
//---------------------------------------------------------------------------
void __fastcall GsListViewMultiMClass::DrawItem(TListItem* Item, const System::Types::TRect &Rect, Winapi::Windows::TOwnerDrawState State)
/**
  OPIS METOD(FUNKCJI): Rysowanie zawartości klasy przez programiste, nie przez system
  OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
  OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TRect RectBounds = Item->DisplayRect(drBounds);
	TRect RectLabel = Item->DisplayRect(drLabel);
	TRect RectIcon = Item->DisplayRect(drIcon);
	TRect RectSubItem = RectLabel;
	TWin32FileAttributeData fileInfo;

	PMULTIDATA pMultiData = static_cast<PMULTIDATA>(this->_pListFile->Items[Item->Index]);
	if(!pMultiData) return;

	//Vcl::Comctrls::TCustomDrawState MyState = State;
	if(State.Contains(odSelected))
	{
		this->Canvas->Brush->Color = clWebDarkOrange;
	}
	this->Canvas->FillRect(RectBounds);
	this->Canvas->Font->Color = clWindowText;

	//MessageBox(NULL, UnicodeString(RectIcon.Left).c_str(), TEXT("Informacja aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
	this->_pImageList->Draw(this->Canvas, RectIcon.Left, RectIcon.Top + 1, pMultiData->iIdIcon);
	InflateRect(RectLabel, -2, 0);
	DrawText(this->Canvas->Handle, pMultiData->ustrName.c_str(), -1, &RectLabel, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
	for(int iColumn=0; iColumn<this->Columns->Count - 1; iColumn++)
	{
    //Wymiary następnej kolumny
		RectSubItem.Left += this->Column[0]->Width - RectIcon.Width() - 4;
		RectSubItem.Right += this->Column[1]->Width;
		if(State.Contains(odSelected)) this->Canvas->Brush->Color = clWebCoral; else this->Canvas->Brush->Color = clWebLinen;
		this->Canvas->FillRect(RectSubItem);
		if(iColumn == enColumn_Size - 1)
		{
      InflateRect(RectSubItem, -4, 0);
			DrawText(this->Canvas->Handle, Format("%u B", ARRAYOFCONST((pMultiData->iSizeFile))).c_str(), -1, &RectSubItem, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
    }
	}
}
//---------------------------------------------------------------------------
void __fastcall GsListViewMultiMClass::ColClick(TListColumn* Column)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Kliknąłeś po raz drugi na tą samą kolumne, sortowanie odwrotbe
	if(iColumnIndex == Column->Index) iToSort *= -1;
	else iToSort = 1;

	iColumnIndex = Column->Index;
	//MessageBox(NULL, TEXT(""), TEXT("Informacja aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
	//this->_pHSListFiles->CustomSort(this->MySort);
	this->_pListFile->Sort(this->SortListFiles);
	this->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall GsListViewMultiMClass::_OnMouseLeave(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Metoda wywoływana podczas wyjścia wskaźnika myszy poza objekt //[03-11-2019]
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TTabSheet *pTabSheet = dynamic_cast<TTabSheet *>(this->Parent->Parent); //1.Parent - TPanel
                                                                          //2.Parent - TTabSheet
	if(!pTabSheet) return;
	//---
  if(pTabSheet->OnMouseLeave)
	{
		pTabSheet->OnMouseLeave(pTabSheet);
	}
	#if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug(Format("GsListViewMultiMClass::_OnMouseLeave, parent: %s", ARRAYOFCONST((this->Parent->Parent->ClassName()))));
	#endif
}
//---------------------------------------------------------------------------
/****************************************************************************
*                           Klasa GsPanelMultiM                             *
*****************************************************************************/
__fastcall GsPanelMultiM::GsPanelMultiM(TComponent* Owner, TPageControl *_pPControl) : TCustomPanel(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW: TPageControl *_pPControl - zakładka w głównym oknie.
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pPControlMainWindow = _pPControl; //Objekt klasy TPageControl na głównym oknie aplikacji
	this->DoubleBuffered = true;
	this->BorderStyle = bsNone;
	//---
	this->_ImageView = new TImage(this);	//Objekt, klasy TImage do wyświetlania grafiki podglądu
	if(!this->_ImageView) throw(Exception("Błąd inicjalizacji objektu TImage"));
	this->_ImageView->Parent = this;
	this->_ImageView->Align = alBottom;
	this->_ImageView->Height = this->_ImageView->Width;
	this->_ImageView->OnClick = this->_ImageOnClick;
	//===
	this->_pSplitter = new TSplitter(this);
	if(!this->_pSplitter) throw(Exception("Błąd inicjalizacji objektu TSplitter"));
	this->_pSplitter->Parent = this;
	this->_pSplitter->Align = alBottom;
	//---
	this->_pGsListViewMultiMClass = new GsListViewMultiMClass(this);
	if(!this->_pGsListViewMultiMClass) throw(Exception("Błąd inicjalizacji objektu GsListViewMultiMClass"));
	this->_pGsListViewMultiMClass->Parent = this;
	this->_pGsListViewMultiMClass->Align = alClient;
}
//---------------------------------------------------------------------------
__fastcall GsPanelMultiM::~GsPanelMultiM()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
}
//---------------------------------------------------------------------------
void __fastcall GsPanelMultiM::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomPanel::CreateWnd();
	//Własny kod.
}
//---------------------------------------------------------------------------
void __fastcall GsPanelMultiM::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TCustomPanel::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsPanelMultiM::_ImageOnClick(System::TObject* Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->_pPControlMainWindow->Visible = true; //01-02-2020
	GsTabSheetGraphics *pGsTabSheetGraphics = new GsTabSheetGraphics(this->_pPControlMainWindow);
	if(!pGsTabSheetGraphics) throw(Exception("Błąd inicjalizacji objektu GsTabSheetGraphics"));
	//---
	pGsTabSheetGraphics->PageControl = this->_pPControlMainWindow; //Umieszczanie objektu klasy na objekcie typu TPageControl
	this->_pPControlMainWindow->ActivePage = pGsTabSheetGraphics; //Nowostworzona zakładka, staje się zakładką aktualną
	TListItem* pListItem = this->_pGsListViewMultiMClass->Selected;
	pGsTabSheetGraphics->Caption = Format("\"%s\"", ARRAYOFCONST((TPath::GetFileName(pListItem->Caption))));
	pGsTabSheetGraphics->_pImageFullDisplay->Picture->LoadFromFile(pListItem->Caption);
}
//---------------------------------------------------------------------------
/****************************************************************************
*                          Klasa GsTabSheetGraphics                         *
*****************************************************************************/
//---------------------------------------------------------------------------
__fastcall GsTabSheetGraphics::GsTabSheetGraphics(TComponent* Owner) : TTabSheet(Owner)
{
  this->DoubleBuffered = true;
  //---
	this->_pScrollBox = new TScrollBox(this);
	if(!this->_pScrollBox) throw(Exception("Błąd inicjalizacji objektu TScrollBox"));
	this->_pScrollBox->Parent = this;
	this->_pScrollBox->DoubleBuffered = true;
	this->_pScrollBox->Align = alClient;
	this->_pScrollBox->VertScrollBar->Tracking = true;
	this->_pScrollBox->HorzScrollBar->Tracking = true;
	this->_pScrollBox->OnMouseWheelUp = this->_OnMouseWhellUp;
	this->_pScrollBox->OnMouseWheelDown = this->_OnMouseWhellDown;
	//---
	this->_pImageFullDisplay = new TImage(this->_pScrollBox); //Główne object dla grafiki
	if(!this->_pScrollBox) throw(Exception("Błąd inicjalizacji objektu TImage"));
  //---
	this->_pImageFullDisplay->Parent = this->_pScrollBox;
  this->_pImageFullDisplay->AutoSize = true;
}
//---------------------------------------------------------------------------
__fastcall GsTabSheetGraphics::~GsTabSheetGraphics()
/**
	OPIS METOD(FUNKCJI): Główny Destruktor, klasy GsTabSheetSelectVersClass
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetGraphics::CreateWnd()
/**
	OPIS METOD(FUNKCJI): Tworzenie kontrolki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TTabSheet::CreateWnd();
	//Własny kod.
  Application->MainForm->ActiveControl = this->_pScrollBox;
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetGraphics::DestroyWnd()
/**
	OPIS METOD(FUNKCJI): Niszczenie kontrolki
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //Własny kod.
	TTabSheet::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsTabSheetGraphics::_OnMouseWhellUp(System::TObject* Sender, System::Classes::TShiftState Shift, const System::Types::TPoint &MousePos, bool &Handled)
/**
	OPIS METOD(FUNKCJI): Kółko myszki pokręcone zostało w górę
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	int iW = this->_pScrollBox->ClientWidth,
			iH = this->_pScrollBox->ClientHeight;

	TPoint PointClient  = ScreenToClient(MousePos);
	if(PointClient.Y <= iH / 2)
		this->_pScrollBox->VertScrollBar->Position -= 4;
	if(PointClient.Y > iW / 2)
    this->_pScrollBox->HorzScrollBar->Position -= 4;
}
//----------------------------------------------------------------------------
void __fastcall GsTabSheetGraphics::_OnMouseWhellDown(System::TObject* Sender, System::Classes::TShiftState Shift, const System::Types::TPoint &MousePos, bool &Handled)
/**
	OPIS METOD(FUNKCJI): Kółko myszki pokręcone zostało w dół
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  int iW = this->_pScrollBox->ClientWidth,
			iH = this->_pScrollBox->ClientHeight;

	TPoint PointClient  = ScreenToClient(MousePos);
	if(PointClient.Y <= iH / 2)
		this->_pScrollBox->VertScrollBar->Position += 4;
	if(PointClient.Y > iW / 2)
		this->_pScrollBox->HorzScrollBar->Position += 4;
}
//----------------------------------------------------------------------------
