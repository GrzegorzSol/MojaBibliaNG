#pragma hdrstop

#include <Vcl.Dialogs.hpp>
#include "GsSchemeVersClass.h"
#include "uGlobalVar.h"
#include <Strsafe.h>
#pragma package(smart_init)
//---------------------------------------------------------------------------
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
*/
enum {
			//--- Numery identyfikacyjne kolorów
			enColorNum_Active = 0,
			enColorNum_InActive,
			enColorNum_Rot
		 };
TColor ColorObject[] = {clLime, clCream, clWebDarkOrange};
/****************************************************************************
*          Klasa całkowicie PRYWATNA GsCoreBibleScheme,                     *
*                    pochodna TCustomPanel.                                 *
*****************************************************************************/
__fastcall GsCoreBibleScheme::GsCoreBibleScheme(TComponent* Owner) : TCustomPanel(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->Font->Quality = TFontQuality::fqClearType;
}
//---------------------------------------------------------------------------
__fastcall GsCoreBibleScheme::~GsCoreBibleScheme()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
}
/****************************************************************************
*          Klasa całkowicie PRYWATNA GsChildBibleScheme,                    *
*                    pochodna GsCoreBibleScheme.                            *
*****************************************************************************/
__fastcall GsChildBibleScheme::GsChildBibleScheme(TComponent* Owner, PReadWriteDataObject _PReadWriteDataObject) : GsCoreBibleScheme(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW: PReadWriteDataObject _PReadWriteDataObject - Czy object jest tworzony (_PReadWriteDataObject=0 - domyślnie), czy wczytywany (_PReadWriteDataObject != 0)
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //Inicjalizacja listy potomków
	this->ListChildren = new TList();
	if(!this->ListChildren) throw(Exception("Nie dokonano inicjalizacji objektu TList"));
	//---
	this->Font->Quality = TFontQuality::fqClearType;
  this->StyleElements = TStyleElements();
	this->SListVers = new THashedStringList(); //Lista wersetów ze wszystkich tłumaczeñ
	if(!this->SListVers) throw(Exception("Nie dokonano inicjalizacji objektu THashedStringList"));
	//---
	this->DoubleBuffered = true;
	this->ParentColor = false;
	this->ParentBackground = false;
  this->ParentCtl3D = false;
	this->BevelOuter = bvNone;
	this->BorderStyle = bsSingle;
	this->Color = ColorObject[enColorNum_Active];
	this->Ctl3D = false;
	this->ParentObjectScheme = nullptr; //Wskaźnik na przodka, domyślnie to korzeń
  this->ShowHint = true;
	if(_PReadWriteDataObject) this->IDChild = _PReadWriteDataObject->RW_ID; else this->IDChild = Random(INT_MAX);
	//this->ID64Child = (__int64)this->IDChild * (__int64)Random(INT_MAX);
	this->Level = 0; //Poziom
}
//---------------------------------------------------------------------------
__fastcall  GsChildBibleScheme::~GsChildBibleScheme()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	int iIndex;
	for(int i=0; i<this->ListChildren->Count; i++)
	//Kasowanie wszystkich potomków
	{
		GsChildBibleScheme *pGsChildBibleScheme = static_cast<GsChildBibleScheme *>(this->ListChildren->Items[i]);
		if(pGsChildBibleScheme)
		{
			//Kasowanie potomka z listy głównej
			iIndex = this->DrawPanelScheme->_GsChildBibleSchemeList->IndexOf(pGsChildBibleScheme);
			if(iIndex > -1) this->DrawPanelScheme->_GsChildBibleSchemeList->Delete(iIndex);
			//Wlaściwe kasowanie potomka
			delete pGsChildBibleScheme; pGsChildBibleScheme = nullptr;
		}
  }
	delete this->ListChildren; this->ListChildren = nullptr; //Kasowanie listy potomków, po ich usunięciu
	//Kasowanie objektu z listy głównej
	iIndex = this->DrawPanelScheme->_GsChildBibleSchemeList->IndexOf(this);
	if(iIndex > -1) this->DrawPanelScheme->_GsChildBibleSchemeList->Delete(iIndex);

	if(this->SListVers) {delete this->SListVers; this->SListVers = nullptr;} //Lista wersetów ze wszystkich tłumaczeñ
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsCoreBibleScheme::CreateWnd();
	//Własny kod.
	//UnicodeString _ustrVers;
	//Wyłuskanie wskaźnika na objekt do rysowania
	this->DrawPanelScheme = dynamic_cast<GsDrawPanelBibleScheme *>(this->Parent);
	if(!this->DrawPanelScheme) throw(Exception("Błąd wyluskania wskaźnika na objekt, klasy GsDrawPanelBibleScheme"));
	//Wyłuskanie na objekt, klasy TScrollBox
	this->pGsScrollBibleScheme = dynamic_cast<GsScrollBibleScheme *>(this->DrawPanelScheme->Parent);
	if(!this->pGsScrollBibleScheme) throw(Exception("Błąd wyluskania wskaźnika na objekt, klasy GsScrollBibleScheme"));
	//Wyłuskanie wskaźnika na główny objekt, klasy
	this->pGsMasterBibleScheme = dynamic_cast<GsMasterBibleScheme *>(this->pGsScrollBibleScheme->Parent);
	if(!this->pGsMasterBibleScheme) throw(Exception("Błąd wyluskania wskaźnika na objekt, klasy GsMasterBibleScheme"));
	//---
	this->ustrVers = this->pGsMasterBibleScheme->_pGsBarSelectVers->GetSelectVers();
	this->pGsMasterBibleScheme->_pGsBarSelectVers->SetSListVers(this->SListVers); //Wypełnienie listy wszystkimi tłumaczeniami danego wersetu.
	//Wypelnianie pól adresu wersetu
	this->pGsMasterBibleScheme->_pGsBarSelectVers->GetSelectAdress(this->ucBook, this->ucChapt, this->ucVers, this->ucTrans);
	//Podpowiedź w formie zawartości wersetucodeString
	//GsReadBibleTextData::GetTextVersOfAdres(this->ucBook, this->ucChapt+1, this->ucVers, this->ucTrans, _ustrVers);
	//_ustrVers = this->SListVers->Strings[this->ucTrans];
	this->Hint = Format("%s\n\"%s\"", ARRAYOFCONST((this->ustrVers, this->SListVers->Strings[this->ucTrans])));
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	GsCoreBibleScheme::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if((Button == mbLeft) || (Button == mbRight))
	{
		this->GetStartX = X;
		this->GetStartY = Y;
		this->StartMove = true;
		if(this->DrawPanelScheme->_pSelectObject != this)
		{
			this->DrawPanelScheme->_pSelectObject->Color = ColorObject[enColorNum_InActive]; //Dezaktywacja poprzedniego objektu
			this->DrawPanelScheme->_pSelectObject = this;           //Objekt kliknięty, staje się aktualny
			if(this->DrawPanelScheme->_pRootObject == this)
				this->DrawPanelScheme->_pSelectObject->Color = ColorObject[enColorNum_Rot];  //Zmiana koloru tła aktualnego objektu
			else this->DrawPanelScheme->_pSelectObject->Color = ColorObject[enColorNum_Active];  //Zmiana koloru tła , aktualnego objektu
		}
   this->ViewSelectObject();
	}
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::ViewSelectObject()
/**
	OPIS METOD(FUNKCJI): Wyświetlenie wersetu wybranego objektu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	UnicodeString _ustrVers;
	GsReadBibleTextData::GetTextVersOfAdress(this->ucBook, this->ucChapt+1, this->ucVers, this->ucTrans, _ustrVers);
	this->pGsMasterBibleScheme->_pVersDisplayText->Caption = Format("%s \"%s\"", ARRAYOFCONST((this->ustrVers, _ustrVers))); //Wybrany werset
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->StartMove = false; //Koniec przesuwania
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::MouseMove(System::Classes::TShiftState Shift, int X, int Y)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!this->ParentObjectScheme) return; //Nie przesuwaj korzenia
	if(this->StartMove)
	{
		//Pilnowanie odpowiedniego położenia objektu, wzglądem wymiarów obszaru roboczego
		if(((this->Left + (X - this->GetStartX)) < 0) || //Nie przesuwaj poza obszar roboczy od lewej strony
			 //Nie przesuwaj poza okno od prawej, więcej niż szerokość ponad 32 od szerokości oknobszaru roboczego
			 ((this->Left + (X - this->GetStartX) + this->Width - 32) > (this->Parent->Parent->Width)) ||
			 //Nie przesuwaj ponad objekt przodka, od lini na 8 pikseli poniżej jego dolnego rogu
			 ((this->Top + (Y - this->GetStartY - 8) < (this->ParentObjectScheme->Top + this->ParentObjectScheme->Height))) ||
			 //Nie przesuwaj poniżej poza dolne obszar roboczy więcej
			 (((this->Top + (Y - this->GetStartY) + this->Height - 4) > (this->Parent->Parent->Height)))) return;

		this->Left += (X - this->GetStartX);
		this->Top += (Y - this->GetStartY);
		//--- Odświerzenie głównego okna, w celu odrysowania wszystkich objektów
		//this->DrawPanelScheme->Repaint();
		this->DrawPanelScheme->Invalidate();
	}
}
//---------------------------------------------------------------------------
void __fastcall GsChildBibleScheme::Paint()
/**
	OPIS METOD(FUNKCJI): Wirtualna metoda odrysowywania klasy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsCoreBibleScheme::Paint();
	//Własny kod
  this->Canvas->Font->Color = clRed;
	this->Canvas->Font->Style = TFontStyles() << fsBold;
	this->Canvas->TextOut(1, 0, this->ustrVers);
	this->Width = this->Canvas->TextWidth(this->ustrVers) + 4;
	this->Height = this->Canvas->TextHeight(this->ustrVers) + 4;
	//--- Odrysowanie objektu i połączen
	if((this->ParentObjectScheme) && (this->DrawPanelScheme))
	{
		//Rysowanie połączenia z przodkiem
		this->DrawPanelScheme->Canvas->Pen->Width = 2;
		this->DrawPanelScheme->Canvas->Pen->Color = clBlue;
		this->DrawPanelScheme->Canvas->MoveTo(this->Left + (this->Width / 2), this->Top);
		this->DrawPanelScheme->Canvas->LineTo(this->ParentObjectScheme->Left + (this->ParentObjectScheme->Width / 2), this->ParentObjectScheme->Top + this->ParentObjectScheme->Height);
	}
}
//---------------------------------------------------------------------------
/****************************************************************************
*          Klasa całkowicie PRYWATNA GsDrawPanelBibleScheme,                *
*                    pochodna TCustomPanel.                                 *
*****************************************************************************/
__fastcall GsDrawPanelBibleScheme::GsDrawPanelBibleScheme(TComponent* Owner) : TCustomPanel(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->Font->Quality = TFontQuality::fqClearType;
	//this->StyleElements = TStyleElements();
	this->DoubleBuffered = true;
	this->AutoSize = true;
  this->BevelOuter = bvNone;
	this->_GsChildBibleSchemeList = new TList();
	if(!this->_GsChildBibleSchemeList) throw(Exception("Nie dokonano inicjalizacji objektu TList"));
	//---
}
//---------------------------------------------------------------------------
__fastcall GsDrawPanelBibleScheme::~GsDrawPanelBibleScheme()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //--- Likwidowanie listy objektów, klasy GsChildBibleScheme
	if(this->_pRootObject)
	//Usuwany główny korzeń, a wraz z nim wszyscy jego potomkowie
	{
		delete this->_pRootObject; this->_pRootObject = nullptr;
	}
	if(this->_GsChildBibleSchemeList) {delete this->_GsChildBibleSchemeList; this->_GsChildBibleSchemeList = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::CreateWnd()
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
void __fastcall GsDrawPanelBibleScheme::DestroyWnd()
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
void __fastcall GsDrawPanelBibleScheme::Paint()
/**
	OPIS METOD(FUNKCJI): Wirtualna metoda odrysowywania klasy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomPanel::Paint();
	//Własny kod
	GsChildBibleScheme *pGsChildBibleScheme;//=0;
	for(int i=0; i<this->_GsChildBibleSchemeList->Count; i++)
	{
    pGsChildBibleScheme = static_cast<GsChildBibleScheme *>(this->_GsChildBibleSchemeList->Items[i]);
		if(!pGsChildBibleScheme) throw(Exception("Błąd wyłuskania objektu, klasy GsChildBibleScheme"));
		pGsChildBibleScheme->Repaint();
  }
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::_AddNewObject()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	int left=0, top=100;

	GsChildBibleScheme *pGsChildBibleScheme, *prevGsChildBibleScheme; //Domyślnie to korzeń

	pGsChildBibleScheme = new GsChildBibleScheme(this);
  if(!pGsChildBibleScheme) throw(Exception("Błąd inicjalizacji objektu GsChildBibleScheme"));
	pGsChildBibleScheme->Parent = this;

  if(this->_GsChildBibleSchemeList->Count > 0) //Tylko jeden korzeń!
	{
		prevGsChildBibleScheme = this->_pSelectObject;
		//Ustawienie pól na poprzedni objekt
		pGsChildBibleScheme->ParentObjectScheme = prevGsChildBibleScheme;
		prevGsChildBibleScheme->ListChildren->Add(pGsChildBibleScheme); //Dodanie aktualnego objektu, do list potomków, przodka
		pGsChildBibleScheme->Level = prevGsChildBibleScheme->Level + 1;

		left = prevGsChildBibleScheme->Left + 10; top = prevGsChildBibleScheme->Top + prevGsChildBibleScheme->Height + 16;
	}
	else //Dodawanie korzenia
	{
		this->_pRootObject = pGsChildBibleScheme;   //Okno głównego korzenia
		this->_pRootObject->Color = ColorObject[enColorNum_Rot];
	}
	pGsChildBibleScheme->Top = top; pGsChildBibleScheme->Left = left;
	if(this->_pSelectObject) {this->_pSelectObject->Color = ColorObject[enColorNum_InActive];} //Kolor nieaktywny dla poprzedniego objektu
	this->_pSelectObject = pGsChildBibleScheme;	//Aktualnie aktywny nowo dodany objekt

	this->_GsChildBibleSchemeList->Add(pGsChildBibleScheme); //Dodanie do głównej listy objektów
	//this->Caption = Format("%s. Ilość objektów: %u", ARRAYOFCONST((ustrCaptionWindow, this->_GsChildBibleSchemeList->Count)));
	//this->ActDeleteLink->Enabled = true;
	this->Invalidate(); //Całe odświerzenie
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::_DeleteObject()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  if(this->_pSelectObject)	//Aktualnie aktywny objekt
	{
		int iResult = MessageBox(NULL, TEXT("Czy rzeczywiście chcesz skasować objekt razem ze wszystkimi jego pochodnymi?"), TEXT("Pytanie aplikacji"), MB_YESNO | MB_ICONWARNING | MB_TASKMODAL | MB_DEFBUTTON2);
		if(iResult == IDNO) return;

		if(this->_pSelectObject!=this->_pRootObject)
		//Nie jest korzeniem i posiada przodków
		{
			GsChildBibleScheme *pParent = this->_pSelectObject->ParentObjectScheme;
			if(pParent)
			{
				int iIndexParent = pParent->ListChildren->IndexOf(this->_pSelectObject);
				if(iIndexParent > -1)
				{
					//Kasowanie objektu z listy przodka
					pParent->ListChildren->Delete(iIndexParent);
				}
			}
			delete this->_pSelectObject; this->_pSelectObject = nullptr;
			this->_pSelectObject = this->_pRootObject;
		}
		else
    //Skasowanie korzenia
		{
			//this->ActDeleteLink->Enabled = false;
			delete this->_pRootObject; this->_pRootObject = nullptr;
			this->_pSelectObject = nullptr;
		}

		//this->Caption = Format("%s. Ilość objektów: %u", ARRAYOFCONST((ustrCaptionWindow, this->_GsChildBibleSchemeList->Count)));
		if(this->_pRootObject)
		{
		}
		this->Repaint();
	}
	else
	{
		MessageBox(NULL, TEXT("Nie wybrałeś objektu do skasowania"), TEXT("Informacja aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
  }

}
//---------------------------------------------------------------------------
bool __fastcall GsDrawPanelBibleScheme::_OpenProjectObject()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //int left=0, top=0;
	GsChildBibleScheme *pGsChildBibleScheme, *prevGsChildBibleScheme;
	bool bReturn=false;
	//---
	TFileStream *pOpenFile;//=0;
	PReadWriteDataObject pDataToOpen;//=0;
	UnicodeString _ustrVers;
	//---
	TOpenDialog *pOpenDialog = new TOpenDialog(this);
	if(!pOpenDialog) throw(Exception("Błąd inicjalizacji objektu TOpenDialog"));

	pOpenDialog->Title = "Podaj nazwę projektu do odczytu";
	pOpenDialog->Filter =  "Pliki projektu schematu(*.svp)|*.SVP|Każdy plik (*.*)|*.*"; //Może dać do globalnej zmiennej?
	pOpenDialog->Options << ofHideReadOnly << ofPathMustExist << ofFileMustExist;
	pOpenDialog->InitialDir = GlobalVar::Global_custrGetExeDir; //Katalog aplikacji
  pOpenDialog->DefaultExt = "svp";

	try
	{
		try
		{
			if(pOpenDialog->Execute()) //Element został wybrany
			{
				//Wykasowanie całej zawartości schematu, ze wszystkimi aktualnymi objektami
				delete this->_pRootObject; this->_pRootObject = nullptr; //Niszczenie rozpoczyna siê od korzenia
				this->_pSelectObject = nullptr;
				pOpenFile = new TFileStream(pOpenDialog->FileName, fmOpenRead);
				if(!pOpenFile) throw(Exception("Błąd inicjalizacji objektu TFileStream"));
				int iSizeFile = pOpenFile->Size, //Wielkość pliku
						iSizeStructData = sizeof(ReadWriteDataObject); //Wielkość struktury
				//Struktura pomocnicza pojedyńczego objektu
				pDataToOpen = new ReadWriteDataObject();
				if(!pDataToOpen) throw(Exception("Nie dokonano inicjalizacji objektu ReadWriteDataObject"));
				for(int i=0; i<iSizeFile; i+=iSizeStructData)
				//for(int i=0; i<iSizeStructData; i+=iSizeStructData) //Tymczasowo, odczytywany tylko korzeñ
				{
					ZeroMemory(pDataToOpen, iSizeStructData); //Wyczyszczenie struktury ReadWriteDataObject, do zapisu i odczytu objektów
					pOpenFile->ReadBuffer(pDataToOpen, iSizeStructData);
					//--- Stworzenie objektu
					pGsChildBibleScheme = new GsChildBibleScheme(this, pDataToOpen);
					if(!pGsChildBibleScheme) throw(Exception("Błąd inicjalizacji objektu GsChildBibleScheme"));
					pGsChildBibleScheme->Parent = this;
					//--- Typ objektu: korzeń, lub potomstwo
					if(pDataToOpen->RW_IDListParent == -1) //Korzeñ
					{
						this->_pRootObject = pGsChildBibleScheme;   //To jest korzeń
						this->_pRootObject->Color = ColorObject[enColorNum_Rot]; //Kolor korzenia
					}
					else if(pDataToOpen->RW_IDListParent > -1)//Potomstwo
					{
						//Wyłuskiwanie adresu przodka, po ijego odczytanym indeksie z globalnej listy objektów
						prevGsChildBibleScheme = static_cast<GsChildBibleScheme *>(this->_GsChildBibleSchemeList->Items[pDataToOpen->RW_IDListParent]);
						if(prevGsChildBibleScheme)
						{
              //Ustawienie pól na poprzedni objekt
							pGsChildBibleScheme->ParentObjectScheme = prevGsChildBibleScheme;
              prevGsChildBibleScheme->ListChildren->Add(pGsChildBibleScheme); //Dodanie aktualnego objektu, do list potomków, przodka
            }
					}
					//---
					pGsChildBibleScheme->Top = pDataToOpen->RW_Top; pGsChildBibleScheme->Left = pDataToOpen->RW_Left;
					pGsChildBibleScheme->ustrVers = pDataToOpen->RW_AdressVers; //Werset
					//Składniki adresu
					pGsChildBibleScheme->ucBook = pDataToOpen->RW_Book;
					pGsChildBibleScheme->ucChapt = pDataToOpen->RW_Chapt;
					pGsChildBibleScheme->ucVers = pDataToOpen->RW_Vers;
					pGsChildBibleScheme->ucTrans = pDataToOpen->RW_Trans;
					//Podpowiedź w formie zawartości wersetu codeString
					GsReadBibleTextData::GetTextVersOfAdress(pGsChildBibleScheme->ucBook, pGsChildBibleScheme->ucChapt+1, pGsChildBibleScheme->ucVers, pGsChildBibleScheme->ucTrans, _ustrVers);
					pGsChildBibleScheme->Hint = Format("%s\n\"%s\"", ARRAYOFCONST((pGsChildBibleScheme->ustrVers, _ustrVers)));

					if(this->_pSelectObject) {this->_pSelectObject->Color = ColorObject[enColorNum_InActive];} //Kolor nieaktywny dlapoprzedniego objektu
					this->_pSelectObject = pGsChildBibleScheme;	//Aktualnie aktywny nowo dodany objekt
					this->_GsChildBibleSchemeList->Add(pGsChildBibleScheme); //Dodanie do g³ównej listy objektów
				}

				//this->Caption = Format("%s. Ilość objektów: %u", ARRAYOFCONST((ustrCaptionWindow, this->_GsChildBibleSchemeList->Count)));
        this->Invalidate(); //Całe odświerzenie
				if(pDataToOpen) {delete pDataToOpen; pDataToOpen = nullptr;}
				if(pOpenFile) {delete pOpenFile; pOpenFile = nullptr;}
				bReturn = true;
			}
		}
    catch(const Exception& e)
		{
			MessageBox(NULL, Format("Błąd otwarcia pliku, do odczytu, o nazwie: %s", ARRAYOFCONST((pOpenDialog->FileName))).c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{
		if(pOpenDialog) {delete pOpenDialog; pOpenDialog = nullptr;}
    //this->ActDeleteLink->Enabled = true;
	}
  return bReturn;
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::_SaveProjectObjectToFile()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TFileStream *pSaveFile;//=0;
	PReadWriteDataObject pDataToSave;//=0;
	//---
  TSaveDialog *pSaveDialog = new TSaveDialog(this);
	if(!pSaveDialog) throw(Exception("Błąd inicjalizacji objektu TSaveDialog"));
	pSaveDialog->Title = "Podaj nazwę projektu do zapisu";
	pSaveDialog->Filter =  "Pliki projektu schematu(*.svp)|*.SVP|Każdy plik (*.*)|*.*"; //Może daĉ do globalnej zmiennej?
	pSaveDialog->Options << ofOverwritePrompt << ofHideReadOnly;
	pSaveDialog->InitialDir = GlobalVar::Global_custrGetExeDir; //Katalog aplikacji
	pSaveDialog->DefaultExt = "svp";

	//---
	try
	{
		try
		{
			if(this->_pRootObject)
			//Jeśli istnieje główny korzeñ
			{
				if(pSaveDialog->Execute())
				{
					pSaveFile = new TFileStream(pSaveDialog->FileName, fmCreate);
					if(!pSaveFile) throw(Exception("Błąd inicjalizacji objektu TFileStream"));
					int iSizeStructData = sizeof(ReadWriteDataObject); //Wielkoĉ struktury
					//Struktura pomocnicza pojedyñczego objektu
					pDataToSave = new ReadWriteDataObject();
					if(!pDataToSave) throw(Exception("Nie dokonano inicjalizacji objektu ReadWriteDataObject"));
					//---
					for(int i=0; i<this->_GsChildBibleSchemeList->Count; i++)
					{
						GsChildBibleScheme *pChild = static_cast<GsChildBibleScheme *>(this->_GsChildBibleSchemeList->Items[i]);
						if(pChild)
						{
							ZeroMemory(pDataToSave, iSizeStructData); //Wyczyszczenie struktury ReadWriteDataObject, do zapisu i odczytu objektów
							//Wypełnienie struktury danych do zapisu
							pDataToSave->RW_ID = pChild->IDChild; //Numer identyfikacyjny
							pDataToSave->RW_IDList = i;           //Pozycja w globalnej liście objektu _GsChildBibleSchemeList, klasy TList
							pDataToSave->RW_Left = pChild->Left; pDataToSave->RW_Top = pChild->Top; //Wspólrzędne objektu
							pDataToSave->RW_IDListParent = -1;    //Domyślnie objekt nie ma przodka, więc jest korzeniem
							if(pChild->ParentObjectScheme) //Jeśli objekt posiada przodka, czyli nie jest korzeniem
							{
								//Indeks przodka w głównej liście
								pDataToSave->RW_IDListParent = this->_GsChildBibleSchemeList->IndexOf(pChild->ParentObjectScheme);
							}
							StringCchCopy(pDataToSave->RW_AdressVers, SIZE_ADDR_VERS-1, pChild->ustrVers.c_str()); //Skopiowanie adresu wersetu, objektu
							//Składniki adresu
							pDataToSave->RW_Book = pChild->ucBook;
							pDataToSave->RW_Chapt = pChild->ucChapt;
							pDataToSave->RW_Vers = pChild->ucVers;
							pDataToSave->RW_Trans = pChild->ucTrans;
							pSaveFile->WriteBuffer(pDataToSave, sizeof(ReadWriteDataObject)); //Główny zapis struktury pomocniczej objektu
						}
					}
					if(pDataToSave) {delete pDataToSave; pDataToSave = nullptr;}
					if(pSaveFile) {delete pSaveFile; pSaveFile = nullptr;}
				}
			}
		}
		catch(const Exception& e)
		{
			MessageBox(NULL, Format("Błąd otwarcia pliku, do zapisu, o nazwie: %s", ARRAYOFCONST((pSaveDialog->FileName))).c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{
		if(pSaveDialog) {delete pSaveDialog; pSaveDialog = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall GsDrawPanelBibleScheme::_ViewProjectDocument()
/**
	OPIS METOD(FUNKCJI): Metoda zapisuje projekt jako plik dokumentu rtf
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
 	if(this->_GsChildBibleSchemeList->Count==0) return;
	//---
	TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true);
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));

	UnicodeString _ustrVers;
  const UnicodeString GlobalHeaderRtf = UnicodeString("{\\urtf1\\ansi\\ansicpg1250\\deff0\\nouicompat\\deflang1045{\\fonttbl{\\f0\\fnil\\fcharset238 Calibri;}{\\f1\\fnil\\fcharset0 Calibri;}}") +
																		 "{\\colortbl ;\\red0\\green0\\blue0;\\red255\\green0\\blue0;\\red255\\green0\\blue255;}" +
																		 "{\\*\\generator Msftedit 5.41.21.2510;}\\viewkind4\\uc1" +
																		 "\\pard\\sa200\\sl276\\slmult1\\cf3\\fs32\\b Dokument projektu, schematu logicznego wersetów, wykonany w aplikacji Moja Biblia NG\\cf0\\b0\\f1\\fs22\\lang21\\par\\fs28",
                      //---
											custrAdressVersRtf = "\\f1\\line\\cf2\\b",
											custrVersRtf = "\\cf1\\b0\\f0",
											custrEndVersRtf = "\\cf2\\b\\f1";

  try
	{
		pStringStream->WriteString(GlobalHeaderRtf);
		for(int i=0; i<this->_GsChildBibleSchemeList->Count; i++)
		{
			GsChildBibleScheme *pChild = static_cast<GsChildBibleScheme *>(this->_GsChildBibleSchemeList->Items[i]);
			if(pChild)
			{
				GsReadBibleTextData::GetTextVersOfAdress(pChild->ucBook, pChild->ucChapt+1, pChild->ucVers, pChild->ucTrans, _ustrVers);
				pStringStream->WriteString(Format("%s %s %s \"%s\" %s" ,ARRAYOFCONST((custrAdressVersRtf, pChild->ustrVers, custrVersRtf, _ustrVers, custrEndVersRtf))));
			}
		}
		pStringStream->WriteString("}");
		pStringStream->Position = 0;

		GsMasterBibleScheme *pGsMasterBibleScheme = dynamic_cast<GsMasterBibleScheme *>(this->Parent->Parent);
		if(pGsMasterBibleScheme)
		{
			//Wczytanie z objektu TStringStream, do objektu, klasy pGsEditorClass
			pGsMasterBibleScheme->pGsEditorClass->LoadEditorFromStream(pStringStream);
		}
	}
	__finally
	{
		if(pStringStream) {delete pStringStream; pStringStream = nullptr;}
	}
}
//---------------------------------------------------------------------------
/****************************************************************************
*                Główna klasa GsScrollBibleScheme,                          *
*                        pochodna TScrollBox.                               *
*****************************************************************************/
__fastcall GsScrollBibleScheme::GsScrollBibleScheme(TComponent* Owner) : TScrollBox(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  this->Font->Quality = TFontQuality::fqClearType;
	this->DoubleBuffered = true;
	this->HorzScrollBar->Tracking = true;
	this->VertScrollBar->Tracking = true;
	this->_pGsDrawPanelBibleScheme = new GsDrawPanelBibleScheme(this);
	if(!this->_pGsDrawPanelBibleScheme) throw(Exception("Błąd inicjalizacji objektu GsDrawPanelBibleScheme"));
	this->_pGsDrawPanelBibleScheme->Parent = this;
}
//---------------------------------------------------------------------------
__fastcall GsScrollBibleScheme::~GsScrollBibleScheme()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void __fastcall GsScrollBibleScheme::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TScrollBox::CreateWnd();
	//Własny kod.
}
//---------------------------------------------------------------------------
void __fastcall GsScrollBibleScheme::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//Własny kod.
	TScrollBox::DestroyWnd();
}
/****************************************************************************
*          								Klasa GsMasterBibleScheme,                   			*
*                    				pochodna TCustomPanel.                          *
*****************************************************************************/
__fastcall GsMasterBibleScheme::GsMasterBibleScheme(TComponent* Owner) : TCustomPanel(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  Randomize();  //Uruchomienie generatora liczb losowych.
	//---
	this->DoubleBuffered = true;
	this->Font->Quality = TFontQuality::fqClearType;
  //this->StyleElements = TStyleElements();
}
//---------------------------------------------------------------------------
__fastcall GsMasterBibleScheme::~GsMasterBibleScheme()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{

}
//---------------------------------------------------------------------------
void __fastcall GsMasterBibleScheme::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TCustomPanel::CreateWnd();
	//Własny kod.
  this->_pGsBarSelectVers = new GsBarSelectVers(this);
	if(!this->_pGsBarSelectVers) throw(Exception("Błąd inicjalizacji objektu GsBarSelectVers"));
	this->_pGsBarSelectVers->Parent = this;
	this->_pGsBarSelectVers->Align = alTop;
  //Utworzenie objektu, klasy do scrollowania
	this->_pGsScrollBibleScheme = new GsScrollBibleScheme(this);
	if(!this->_pGsScrollBibleScheme) throw(Exception("Błąd inicjalizacji objektu GsScrollBibleScheme"));
	//Stworzenie panelu do rysowania połączeń i objektów
	this->_pGsScrollBibleScheme->Parent = this;
	this->_pGsScrollBibleScheme->Align = alClient;
	//---
	this->_pGsDrawPanelBibleScheme = this->_pGsScrollBibleScheme->_pGsDrawPanelBibleScheme;
	//---
	this->pSplitter = new TSplitter(this);
	if(!this->pSplitter) throw(Exception("Błąd inicjalizacji objektu TSplitter"));
	this->pSplitter->Parent = this;
	this->pSplitter->Align = alBottom;
	this->pSplitter->Color = clCream;
	this->pSplitter->Height = 6;
	this->pSplitter->Beveled = true;
	//---
  this->_pVersDisplayText = new TLabel(this); //Wyświetlenie wybranego wersetu
	if(!this->_pVersDisplayText) throw(Exception("Błąd inicjalizacji objektu TLabel"));
	this->_pVersDisplayText->Parent = this;
	this->_pVersDisplayText->Align = alBottom;
  this->_pVersDisplayText->Color = clCream;
	this->_pVersDisplayText->AutoSize = true;
	this->_pVersDisplayText->WordWrap = true;
	this->_pVersDisplayText->Font->Color = clGreen;
	this->_pVersDisplayText->Font->Style = TFontStyles() << fsBold;
  this->_pVersDisplayText->Font->Size = 11;
	this->_pVersDisplayText->Caption = "Tu bedzie sie pojawiał tekst objektu z wersetem biblijnym";
	//---
	this->pGsEditorClass = new GsEditorClass(this);
	if(!this->pGsEditorClass) throw(Exception("Błąd inicjalizacji objektu GsEditorClass"));
	this->pGsEditorClass->Parent = this;
	this->pGsEditorClass->Align = alBottom;
	this->pGsEditorClass->Height = this->Parent->Height / 4;
}
//---------------------------------------------------------------------------
void __fastcall GsMasterBibleScheme::DestroyWnd()
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

