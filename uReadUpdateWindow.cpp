#include <vcl.h>
#pragma hdrstop

#include "uReadUpdateWindow.h"
#include "uGlobalVar.h"
#include <System.IOUtils.hpp>
#include <wininet.h>
#include <urlmon.h>
#if defined(_WIN64)
	#pragma link "urlmon.a"
	#pragma link "wininet.a"
#else
	#pragma link "urlmon.lib"
	#pragma link "wininet.lib"
#endif
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TReadUpdateWindow *ReadUpdateWindow;

enum {enTagUp_UpYes=0x1000, enTagUp_UpNo};
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
bool GsTypeConnected(UnicodeString &_ustrInfoTypeConnected);
bool bIsPushButton=false;
//---------------------------------------------------------------------------
__fastcall TReadUpdateWindow::TReadUpdateWindow(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->ButtYes->Tag = enTagUp_UpYes;
	this->ButtonNo->Tag = enTagUp_UpNo;

  this->LabeledEdCurrentVersion->Text = GlobalVar::Global_ustrVerAplicMain;
	//--- Sprawdzenie połączenia z internetem
	UnicodeString ustrReturnConect;
	bool bRet = GsTypeConnected(ustrReturnConect);

	if(bRet)
	//Jeśli polączenei powiodło się
	{
		this->Caption = Format("%s - %s", ARRAYOFCONST((this->Caption, ustrReturnConect)));
	}
	else
	{
	 throw(Exception("Brak dostępu do sieci"));
	}

	this->_GetIsUpdateVerify();
}
//---------------------------------------------------------------------------
void __fastcall TReadUpdateWindow::FormClose(TObject *Sender, TCloseAction &Action)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!bIsPushButton) GlobalVar::iReturnUpdate = -1;
	Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TReadUpdateWindow::_GetIsUpdateVerify()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //Uzyskanie ścieżki dostepu do katalogu Temp
	TCHAR pathTemp[MAX_PATH];
	GetTempPath(MAX_PATH, pathTemp);

	bool bRetDownload;//=false;

	//bRetDownload = this->_DownLoadFileFTP(GlobalVar::Global_custrLocalVersionFile, GlobalVar::Global_custrFTPSourceVersionFile);
	bRetDownload = this->_DownLoadFileFTPGet(GlobalVar::Global_custrLocalVersionFile, GlobalVar::Global_custrFTPSourceVersionFile);
	if(!bRetDownload) this->Caption = "Błąd procesu aktualizacji!";

	TStringBuilder *pStrBuilderDownload = new TStringBuilder();
	if(!pStrBuilderDownload) throw(Exception("Błąd inicjalizacji objektu TStringBuilder"));

	__int64 i64DonloadFile=0, i64LocalFile=0;

	pStrBuilderDownload->Append(TFile::ReadAllText(GlobalVar::Global_custrLocalVersionFile, TEncoding::UTF8));
	this->LabeledEdDownLoadversion->Text = pStrBuilderDownload->ToString();

	pStrBuilderDownload->Replace(".", ""); //Usunięcie kropek

	if(!TryStrToInt64(pStrBuilderDownload->ToString(), i64DonloadFile))
	//jeśli nie udało się skonwertować na __int64, to musiał nastąpić błąd
	{
		delete pStrBuilderDownload; return;
	}
	pStrBuilderDownload->Clear(); //Wyczyszczenie zawartości
	pStrBuilderDownload->Append(GlobalVar::Global_ustrVerAplicMain);
	pStrBuilderDownload->Replace(".", ""); //Usunięcie kropek
	if(!TryStrToInt64(pStrBuilderDownload->ToString(), i64LocalFile))
	//jeśli nie udało się skonwertować na __int64, to musiał nastąpić błąd
	{
		delete pStrBuilderDownload; return;
	}

	if(i64DonloadFile == i64LocalFile)
	{
		this->STextInfos->Caption = "Wersja lokalna jest taka sama jak na serwerze aktualizacyjnym";
		GlobalVar::iReturnUpdate = 0;
	}
	else if(i64DonloadFile > i64LocalFile)
	{
		this->STextInfos->Caption = "Jest dostępna nowsza wersja na serwerze aktualizacyjnym, czy zaktualizować aplikację? Spowoduje to zaknięcie aplikacji, by pobrać i zainstalować poprawkę";
		GlobalVar::iReturnUpdate = 1;
		this->PanelButtons->Visible = true;
    //Pobranie nowszej wersji
		//bRetDownload = this->_DownLoadFileFTP(GlobalVar::Global_custrLocalApplicFile, GlobalVar::Global_custrFTPSourceApplicFile);
		bRetDownload = this->_DownLoadFileFTPGet(GlobalVar::Global_custrLocalApplicFile, GlobalVar::Global_custrFTPSourceApplicFile);
		if(!bRetDownload) this->Caption = "Błąd procesu aktualizacji!";
	}
	if(i64DonloadFile < i64LocalFile)
	{
		this->STextInfos->Caption = "Wersja lokalna jest nowsza niż na serwerze aktualizacyjnym";
		GlobalVar::iReturnUpdate = -1;
	}

	delete pStrBuilderDownload;
}
//---------------------------------------------------------------------------
bool __fastcall TReadUpdateWindow::_DownLoadFileFTPGet(const UnicodeString _destPathDownload, const UnicodeString _ustrPathFTPFile)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  HINTERNET hInternetConnectHandle=NULL; 	//Wynik funkcji InternetConnect()
	HINTERNET hInternetOpenHandle=NULL;	//Wynik funkcji InternetOpen()

	bool bRet=true;

  hInternetOpenHandle = InternetOpen(0, INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, INTERNET_FLAG_PASSIVE);
	if(!hInternetOpenHandle) return false;

	try
	{
		try
		{
			hInternetConnectHandle = InternetConnect(hInternetOpenHandle, GlobalVar::Global_custrHostName.c_str(), INTERNET_DEFAULT_FTP_PORT,
																							 GlobalVar::Global_custrUserHost.c_str(), GlobalVar::Global_custrPassword.c_str(), INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
			if(hInternetConnectHandle)
			{
				bRet = FtpGetFile(hInternetConnectHandle, _ustrPathFTPFile.c_str(), _destPathDownload.c_str(), FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_BINARY, 0 );
			}
		}
		catch(...) {bRet = false;}
	}
	__finally
	{
    if(hInternetConnectHandle) InternetCloseHandle(hInternetConnectHandle);
		if(hInternetOpenHandle) InternetCloseHandle(hInternetOpenHandle);
	}
	return bRet;
}
//=====================FUNKCJE NIE BĘDĄCE METODAMI KLASY=====================
bool GsTypeConnected(UnicodeString &_ustrInfoTypeConnected)
/**
	OPIS METOD(FUNKCJI): Sprawdzanie czy komputer jest podłączony do internetu
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	bool bInternetConnect=false;
	DWORD State;
	if(InternetGetConnectedState(&State, 0))
	{
		UnicodeString ustrTypeConect;
		if(State & INTERNET_CONNECTION_MODEM)      ustrTypeConect = "Połączenie prze modem";
		if(State & INTERNET_CONNECTION_LAN)        ustrTypeConect = "Połączenie przez LAN";
		if(State & INTERNET_CONNECTION_PROXY)      ustrTypeConect = "Połączenie przez PROXY";
		if(State & INTERNET_CONNECTION_MODEM_BUSY) ustrTypeConect = "Modem zajęty";

		_ustrInfoTypeConnected = "Typ połączenia: " + ustrTypeConect;
		bInternetConnect = true;
	}
	else
	{
		//bInternetConnect = false;
		_ustrInfoTypeConnected = "Brak połączenie z Internetem!!!";
	}
	return bInternetConnect;
}
//---------------------------------------------------------------------------
void __fastcall TReadUpdateWindow::ButtAllClick(TObject *Sender)
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
	bIsPushButton = true;
	switch(pButt->Tag)
	{
		case enTagUp_UpYes:
			GlobalVar::iReturnUpdate = 1;
		break;
		//---
		case enTagUp_UpNo:
			GlobalVar::iReturnUpdate = -1;

		break;
    //---
	}

	this->Close();
}
//---------------------------------------------------------------------------

