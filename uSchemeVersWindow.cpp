#include <vcl.h>
#pragma hdrstop

#include "uSchemeVersWindow.h"
#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSchemeVersWindow *SchemeVersWindow;
const UnicodeString ustrCaptionWindow = "Projektowanie logicznych powiązań między wersetami";
enum {enImgScheme_AddLink,
			enImgScheme_DeleteLink,
			enImgScheme_Save,
			enImgScheme_Open,
			enImgScheme_CreateRtf,
			enImgScheme_Vieweditor,
			//--- Tagi
			enTagScheme_AddLink=100,
			enTagScheme_DeleteLink,
			enTagScheme_Save,
			enTagScheme_Open,
			enTagScheme_CreateRtf,
			enTagScheme_ViewEditor
};
//---------------------------------------------------------------------------
__fastcall TSchemeVersWindow::TSchemeVersWindow(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->pGsMasterBibleScheme = new GsMasterBibleScheme(this);
	if(!this->pGsMasterBibleScheme) throw(Exception("Błąd inicjalizacji objektu GsMasterBibleScheme"));
	this->pGsMasterBibleScheme->Parent = this;
	this->pGsMasterBibleScheme->Align = alClient;
  //---
  this->Caption = ustrCaptionWindow;
	this->ActNewLink->Tag = enTagScheme_AddLink;
	this->ActNewLink->Hint = Format("%s|Dodaje nowe dowiązanie do aktualnego elementu|%u", ARRAYOFCONST((this->ActNewLink->Caption, this->ActNewLink->ImageIndex)));
	this->ActDeleteLink->Tag = enTagScheme_DeleteLink;
	this->ActDeleteLink->Hint = Format("%s|Usuwa aktualne dowiązanie|%u", ARRAYOFCONST((this->ActDeleteLink->Caption, this->ActDeleteLink->ImageIndex)));
	this->ActSave->Tag = enTagScheme_Save;
	this->ActSave->Hint = Format("%s|Zapis bierzącego schematu|%u", ARRAYOFCONST((this->ActSave->Caption, this->ActSave->ImageIndex)));
	this->ActCreateFileFromScheme->Tag = enTagScheme_CreateRtf;
	this->ActCreateFileFromScheme->Hint = Format("%s|Utworzenie widoku projektu, w formie dokumentu|%u", ARRAYOFCONST((this->ActCreateFileFromScheme->Caption, this->ActCreateFileFromScheme->ImageIndex)));
	this->ActViewEditor->Tag = enTagScheme_ViewEditor;
	this->ActViewEditor->Hint = Format("%s|Utworzenie widoku projektu, w formie dokumentu|%u", ARRAYOFCONST((this->ActViewEditor->Caption, this->ActViewEditor->ImageIndex)));
}
//---------------------------------------------------------------------------
void __fastcall TSchemeVersWindow::FormClose(TObject *Sender, TCloseAction &Action)
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
void __fastcall TSchemeVersWindow::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	///
}
//---------------------------------------------------------------------------
void __fastcall TSchemeVersWindow::FormDestroy(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  ///
}
//---------------------------------------------------------------------------
void __fastcall TSchemeVersWindow::ActNewLinkExecute(TObject *Sender)
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
	this->pGsMasterBibleScheme->AddNewObjectScheme();
	this->ActCreateFileFromScheme->Enabled = true;
	this->ActDeleteLink->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TSchemeVersWindow::ActDeleteLinkExecute(TObject *Sender)
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
	this->pGsMasterBibleScheme->DeleteObjectScheme();
	this->ActCreateFileFromScheme->Enabled = (this->pGsMasterBibleScheme->GetCountObjectScheme() > 0);
	this->ActDeleteLink->Enabled = this->ActCreateFileFromScheme->Enabled;
}
//---------------------------------------------------------------------------
void __fastcall TSchemeVersWindow::ActSaveExecute(TObject *Sender)
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
  this->pGsMasterBibleScheme->SaveProjectObjectSchemeToFile();
}
//---------------------------------------------------------------------------
void __fastcall TSchemeVersWindow::ActOpenProjectExecute(TObject *Sender)
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
	this->ActDeleteLink->Enabled = this->pGsMasterBibleScheme->OpenProjectObjectScheme();
	this->ActCreateFileFromScheme->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TSchemeVersWindow::ActCreateFileFromSchemeExecute(TObject *Sender)
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
  this->pGsMasterBibleScheme->ViewProjectDocument();
}
//---------------------------------------------------------------------------
void __fastcall TSchemeVersWindow::ActViewEditorExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//Wyłuskanie edytora dokumentu, dla projektu
	GsEditorClass *pGsEditorClass = this->pGsMasterBibleScheme->GetEditorClass();
	if(pGsEditorClass)
	{
		pGsEditorClass->Visible = pAction->Checked;
	}
}
//---------------------------------------------------------------------------

