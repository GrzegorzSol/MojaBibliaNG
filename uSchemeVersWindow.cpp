﻿#include <vcl.h>
#pragma hdrstop

#include "uSchemeVersWindow.h"
#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSchemeVersWindow *SchemeVersWindow;
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
	GsDebugClass::WriteDebug("");
#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
const UnicodeString ustrCaptionWindow = "Projektowanie logicznych powiązań między wersetami";
enum {enImgScheme_AddLink,
			enImgScheme_DeleteLink,
			enImgScheme_Save,
			enImgScheme_Open,
			enImgScheme_CreateRtf,
			enImgScheme_Vieweditor,
			enImgScheme_RenameObject,
			enImgScheme_Setup,
			enImgScheme_NewProject,
			//--- Tagi
			enTagScheme_AddLink=100,
			enTagScheme_DeleteLink,
			enTagScheme_Save,
			enTagScheme_Open,
			enTagScheme_CreateRtf,
			enTagScheme_ViewEditor,
			enTagScheme_RenameObject,
			enTagScheme_Setup,
      enTagScheme_NewProject
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
	this->Width = Application->MainForm->Width - 120;
	this->Height = Application->MainForm->Height - 12;

	this->pGsMasterBibleScheme = new GsMasterBibleScheme(this);
	if(!this->pGsMasterBibleScheme) throw(Exception("Błąd inicjalizacji objektu GsMasterBibleScheme"));
	this->pGsMasterBibleScheme->Parent = this;
	this->pGsMasterBibleScheme->Align = alClient;
	//---
	this->Caption = ustrCaptionWindow;
	this->ActOpenProject->Tag = enTagScheme_Open;
	this->ActOpenProject->Hint = Format("%s|Otwiera istniejący, zapisany projekt na dysku.|%u", ARRAYOFCONST((this->ActOpenProject->Caption, this->ActOpenProject->ImageIndex)));
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
	this->ActRenameObject->Hint = Format("%s|Zmiana nazwy aktywnego objektu, na wybraną wcześniej z menu wybory wersetu|%u", ARRAYOFCONST((this->ActRenameObject->Caption, this->ActRenameObject->ImageIndex)));
	this->ActRenameObject->Tag = enTagScheme_RenameObject;
	this->ActSetupScheme->Hint = Format("%s|Ustawienia dotyczące modułu do tworzenia analizy logicznej tekstu|%u", ARRAYOFCONST((this->ActSetupScheme->Caption, this->ActSetupScheme->ImageIndex)));
	this->ActSetupScheme->Tag = enTagScheme_Setup;
	this->ActNew->Hint = Format("%s|Zacznij nowy projekt|%u", ARRAYOFCONST((this->ActNew->Caption, this->ActNew->ImageIndex)));
	this->ActNew->Tag = enTagScheme_NewProject;
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
	for(int i=0; i<this->ActToolBarScheme->ControlCount; ++i)
	{
		TControl *pControl = this->ActToolBarScheme->Controls[i];
		if(pControl->Action == this->ActSetupScheme)
		{
			this->pGsMasterBibleScheme->OpenSetupsScheme(this, this->ActSetupScheme, pControl->Left + this->ActToolBarScheme->Left,
				this->ActToolBarScheme->Top + this->ActToolBarScheme->Height);
		}
	}
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
	this->ActRenameObject->Enabled = true;
	this->ActSave->Enabled = true;
	this->ActNew->Enabled = true;
	if(!this->ActViewEditor->Checked)
	//28-03-2021 - Jeśli został dodany element do schematu, automatycznie wyświetlany jest edytor, by nie spowodować błędu fokusa
	//w wypadku próby wyświetlenia w edytorze dokumentu, przy równoczesnym jego ukryciu.
	//Edytor bedzie mógł być ukryty gdy nie będzie żadnego elementu.
	//Sprawdzane jest to w metodzie ActDeleteLinkExecute, gdy zostanie skasowany ostatni element
	{
		this->ActViewEditor->Checked = true;
		this->ActViewEditorExecute(this->ActViewEditor);
	}
	this->ActViewEditor->Enabled = false; //Zablokowanie wyłączania edytora - 28-03-2021
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
	//Brak elementów, można włączać i wyłączać edytor - 28-03-2021
	this->ActViewEditor->Enabled = (this->pGsMasterBibleScheme->GetCountObjectScheme() == 0);
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
	this->LabelNameProject->Caption = Format("Nazwa projektu: %s", ARRAYOFCONST(( TPath::GetFileNameWithoutExtension(this->pGsMasterBibleScheme->ProjectName) )));
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
	this->ActRenameObject->Enabled = this->ActDeleteLink->Enabled;
	this->ActCreateFileFromScheme->Enabled = this->ActDeleteLink->Enabled;
	this->ActSave->Enabled = this->ActDeleteLink->Enabled;
	this->ActNew->Enabled = true;
	this->LabelNameProject->Caption = Format("Nazwa projektu: %s", ARRAYOFCONST(( TPath::GetFileNameWithoutExtension(this->pGsMasterBibleScheme->ProjectName) )));
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
	this->pGsMasterBibleScheme->ViewProjectDocument(TPath::GetFileNameWithoutExtension(this->pGsMasterBibleScheme->ProjectName));
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
	GsEditorClass *pGsEditorClass = this->pGsMasterBibleScheme->GetEditor;
	if(pGsEditorClass)
	{
		pGsEditorClass->Visible = pAction->Checked;
	}
}
//---------------------------------------------------------------------------
void __fastcall TSchemeVersWindow::ActRenameObjectExecute(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TAction *pAction = dynamic_cast<TAction *>(Sender);
	if(!pAction) return;
	//--
  this->pGsMasterBibleScheme->SetObjectName();
}
//---------------------------------------------------------------------------
void __fastcall TSchemeVersWindow::ActSetupSchemeExecute(TObject *Sender)
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
	this->pGsMasterBibleScheme->VisibleSetupsScheme(pAction->Checked);
}
//---------------------------------------------------------------------------
void __fastcall TSchemeVersWindow::ActNewExecute(TObject *Sender)
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
	int iResult = MessageBox(NULL, TEXT("Czy chcesz zapisać aktualny projekt, przed jego usunięciem?"),
													 TEXT("Pytanie aplikacji"), MB_YESNO | MB_ICONWARNING | MB_TASKMODAL | MB_DEFBUTTON1);
	if(iResult == IDYES) this->ActSaveExecute(this->ActSave);

	this->pGsMasterBibleScheme->NewProject();
	this->LabelNameProject->Caption = "Nazwa projektu: Bez nazwy";

  this->ActDeleteLink->Enabled = false;
	this->ActRenameObject->Enabled = this->ActDeleteLink->Enabled;
	this->ActCreateFileFromScheme->Enabled = this->ActDeleteLink->Enabled;
	this->ActSave->Enabled = this->ActDeleteLink->Enabled;
}
//---------------------------------------------------------------------------
void __fastcall TSchemeVersWindow::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	GsChildBibleScheme *pSelectObject = this->pGsMasterBibleScheme->SelectObject;
	TWinControl *pGetDrawPanelScheme = this->pGsMasterBibleScheme->GetDrawPanelScheme;

	if(Shift.Contains(ssCtrl))
	{
  	if(pSelectObject)
  	{
  		switch(Key)
  		{
				case vkDown: pSelectObject->Top +=1; break;
  			case vkUp: pSelectObject->Top -=1; break;
  			case vkLeft: pSelectObject->Left -=1; break;
  			case vkRight: pSelectObject->Left +=1; break;
        default: break;
			}
			pGetDrawPanelScheme->Invalidate();
		}
	}
}
//---------------------------------------------------------------------------

