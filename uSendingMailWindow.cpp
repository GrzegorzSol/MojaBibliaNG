#include <vcl.h>
#pragma hdrstop

#include <mapi.h>
#include <System.IOUtils.hpp>
#include "uSendingMailWindow.h"
#include "uGlobalVar.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TSendingMailWindow *SendingMailWindow;
enum {enTag_ButtSendingMail=100};
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
//---------------------------------------------------------------------------
__fastcall TSendingMailWindow::TSendingMailWindow(TComponent* Owner, const UnicodeString &ustrTextHTML)
	: TForm(Owner), _ustrTextHTML(ustrTextHTML)
/**
	OPIS METOD(FUNKCJI): Konstruktor klasy TSendingMailWindow
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->ButtSendingMail->Tag = enTag_ButtSendingMail;
	this->ButtSendingMail->Hint = "Wyślij tekst emailem|Wysyłanie wybranego tekstu biblijneo mailem, na wybrany adres";
	//---
	if(TFile::Exists(GlobalVar::Global_custrPathLastUsedAddressFile))
	{
		this->CBoxLastUseAddress->Items->LoadFromFile(GlobalVar::Global_custrPathLastUsedAddressFile, TEncoding::UTF8);
	}
}
//---------------------------------------------------------------------------
void __fastcall TSendingMailWindow::FormClose(TObject *Sender, TCloseAction &Action)
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
void __fastcall TSendingMailWindow::ButtSendingMailClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Konstruktor klasy TSendingMailWindow
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->LEditAdressMail->Text.IsEmpty())
	{
		MessageBox(NULL, TEXT("Nie można wysłać wiadomości, ponieważ nie wpisałeś poprawnego adresu odbiorcy. Wpisz prawidłowy adres i spróbuj ponownie."), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		return;
	}
	//---
	int iIndexAddress = this->CBoxLastUseAddress->Items->IndexOf(this->LEditAdressMail->Text);
	if(iIndexAddress == -1) {this->CBoxLastUseAddress->ItemIndex = this->CBoxLastUseAddress->Items->Add(this->LEditAdressMail->Text);}
	this->CBoxLastUseAddress->Items->SaveToFile(GlobalVar::Global_custrPathLastUsedAddressFile, TEncoding::UTF8);
	//return;
	//---
	HINSTANCE hMAPI = LoadLibrary(L"mapi32.dll");
	if(!hMAPI) throw(Exception("Błąd załadowania biblioteki \"mapi32.dll\""));

	LPMAPISENDMAILW lpfnMAPISendMailW = (LPMAPISENDMAILW)GetProcAddress(hMAPI, "MAPISendMailW");
	if(!lpfnMAPISendMailW) throw(Exception("Błąd załadowania funkcji \"MAPISendMailW\" z biblioteki \"mapi32.dll\""));

	UnicodeString ustrTo;
	ustrTo += this->LEditAdressMail->Text;

	UnicodeString ustrName;
	ustrName += "Tekst biblijny";

	MapiRecipDescW recipient[1] = {0};
	recipient[0].ulRecipClass = MAPI_TO;
	recipient[0].lpszAddress = ustrTo.c_str();
	recipient[0].lpszName = ustrName.c_str();

	UnicodeString ustrSubject;
	ustrSubject += "Tekst biblijny";

	UnicodeString ustrText;
	ustrText += this->_ustrTextHTML;

	MapiMessageW MAPImsg = {0};
	MAPImsg.lpszSubject = ustrSubject.c_str();
	MAPImsg.lpRecips = recipient;
	MAPImsg.nRecipCount = 1;
	MAPImsg.lpszNoteText = ustrText.c_str();

	ULONG nSent = lpfnMAPISendMailW(0, 0, &MAPImsg, MAPI_LOGON_UI | MAPI_DIALOG, 0);

	FreeLibrary(hMAPI);

	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TSendingMailWindow::CBoxLastUseAddressChange(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TComboBox *pCBox = dynamic_cast<TComboBox *>(Sender);
	if(!pCBox) return;
	//---
	this->LEditAdressMail->Text = pCBox->Items->Strings[pCBox->ItemIndex];
}
//---------------------------------------------------------------------------

