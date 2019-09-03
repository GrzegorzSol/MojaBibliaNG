#include <vcl.h>
#pragma hdrstop

#include "uReadUpdateWindow.h"
#include "uGlobalVar.h"
#include <System.IOUtils.hpp>
#include <wininet.h>
#include <urlmon.h>

#pragma link "urlmon.lib"
#pragma link "wininet.lib"
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
	//--- Sprawdzenie po³¹czenia z internetem
	UnicodeString ustrReturnConect;
	bool bRet = GsTypeConnected(ustrReturnConect);

	if(bRet)
	//Jeœli pol¹czenei powiod³o siê
	{
		this->Caption = Format("%s - %s", ARRAYOFCONST((this->Caption, ustrReturnConect)));
	}
	else
	{
	 throw(Exception("Brak dostêpu do sieci"));
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
  //Uzyskanie œcie¿ki dostepu do katalogu Temp
	TCHAR pathTemp[MAX_PATH];
	GetTempPath(MAX_PATH, pathTemp);

	bool bRetDownload=false;

	bRetDownload = this->_DownLoadFileFTP(GlobalVar::Global_custrLocalVersionFile, GlobalVar::Global_custrFTPSourceVersionFile);
	if(!bRetDownload) this->Caption = "B³¹d procesu aktualizacji!";

	TStringBuilder *pStrBuilderDownload = new TStringBuilder();
	if(!pStrBuilderDownload) throw(Exception("B³¹d inicjalizacji objektu TStringBuilder"));

	__int64 i64DonloadFile=0, i64LocalFile=0;

	pStrBuilderDownload->Append(TFile::ReadAllText(GlobalVar::Global_custrLocalVersionFile, TEncoding::UTF8));
	this->LabeledEdDownLoadversion->Text = pStrBuilderDownload->ToString();

	pStrBuilderDownload->Replace(".", ""); //Usuniêcie kropek

	if(!TryStrToInt64(pStrBuilderDownload->ToString(), i64DonloadFile))
	//jeœli nie uda³o siê skonwertowaæ na __int64, to musia³ nast¹piæ b³¹d
	{
		delete pStrBuilderDownload; return;
	}
	pStrBuilderDownload->Clear(); //Wyczyszczenie zawartoœci
	pStrBuilderDownload->Append(GlobalVar::Global_ustrVerAplicMain);
	pStrBuilderDownload->Replace(".", ""); //Usuniêcie kropek
	if(!TryStrToInt64(pStrBuilderDownload->ToString(), i64LocalFile))
	//jeœli nie uda³o siê skonwertowaæ na __int64, to musia³ nast¹piæ b³¹d
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
		this->STextInfos->Caption = "Jest dostêpna nowsza wersja na serwerze aktualizacyjnym, czy zaktualizowaæ aplikacjê?";
		GlobalVar::iReturnUpdate = 1;
		this->PanelButtons->Visible = true;
    //Pobranie nowszej wersji
		bRetDownload = this->_DownLoadFileFTP(GlobalVar::Global_custrLocalApplicFile, GlobalVar::Global_custrFTPSourceApplicFile);
		if(!bRetDownload) this->Caption = "B³¹d procesu aktualizacji!";
	}
	if(i64DonloadFile < i64LocalFile)
	{
		this->STextInfos->Caption = "Wersja lokalna jest nowsza ni¿ na serwerze aktualizacyjnym";
		GlobalVar::iReturnUpdate = -1;
	}

	delete pStrBuilderDownload;
}
//---------------------------------------------------------------------------
bool __fastcall TReadUpdateWindow::_DownLoadFileFTP(const UnicodeString _destPathDownload, const UnicodeString _ustrPathFTPFile)
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
  const unsigned int uiBufferSize = 4096;

  hInternetOpenHandle = InternetOpen(0, INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, INTERNET_FLAG_PASSIVE);
	if(!hInternetOpenHandle) return false;

	try
	{
		try
		{
			hInternetConnectHandle = InternetConnect(hInternetOpenHandle, GlobalVar::Global_custrHostName.c_str(), INTERNET_DEFAULT_FTP_PORT,
																							 GlobalVar::Global_custrUserHost.c_str(), GlobalVar::Global_custrPassword.c_str(), INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
			if(!hInternetConnectHandle) throw(Exception("B³¹d funkcji hInternetConnectHandle()"));

      HINTERNET hFileTransfer = NULL;
			HANDLE hFileDownload = NULL;

			hFileTransfer = FtpOpenFile(hInternetConnectHandle, _ustrPathFTPFile.c_str(), GENERIC_READ, FTP_TRANSFER_TYPE_BINARY, 0);
			if(!hFileTransfer) throw(Exception("B³¹d funkcji FtpOpenFile()"));
			//--- Wielkoœæ pliku na serwerze
			DWORD filesized = 0; //D³ugoœæ pliku na serwerze
			filesized =  FtpGetFileSize(hFileTransfer, NULL);
      #if defined(_DEBUGINFO_)
				GsDebugClass::WriteDebug(Format("filesized: %u", ARRAYOFCONST((filesized))));
			#endif

			hFileDownload = CreateFile(_destPathDownload.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
      if(hFileDownload == INVALID_HANDLE_VALUE)
			{
				//Plik na serwerze musimy zamkn¹æ, na dysku nie gdy¿ nie zosta³ otwarty z powodu b³êdu.
				InternetCloseHandle(hFileTransfer); hFileTransfer = 0;
				throw(Exception("B³¹d funkcji CreateFile()"));
			}

      bool bActive = true, //Test czy koniec zciaganego pliku z serwera ju¿ nast¹pi³
					 bSuccess = false, //Odczyt kolejnej porcji pliku z serwera powiód³ siê
					 bSuccesWrite = false; //Zapis pobranego pliku do lokalnego katalogu
			char Buffer[uiBufferSize]; //Bufor na porcje, odczytywanego pliku z serwera
			DWORD dwBytesAvailable = 0,
						dwRead = 0,	//Iloœæ odczytanych bajtów z pliku, na serwerze
						dwWritten = 0;	//Iloœæ zapisanych danych na dysku lokalnym
			int progress=0; //Wska¿nik na pozycje w czytanym pliku z serwera

			//---G³ówna pêtla pobierania pliku z serwera i zapisu go na lokalny dysk twardy.
      do
			{
				Application->ProcessMessages();
				bSuccess = InternetReadFile(hFileTransfer, Buffer, uiBufferSize, &dwRead);
				if(!bSuccess || dwRead == 0)
				{
					bActive = false;
					if(!bSuccess)
					{
					}
					break;	//Wyskoczenie z pêtli w przypadku b³êdu(bSucces==false), lub napotkania koñca pliku,
									//pobieranego z serwera(bActive==false)
				}
        //Zapisujemy pobran¹ porcjê danych z pliku na serwerze
				dwWritten = 0;	//Zerowanie iloœci zapisanej na lokalny dysk
				bSuccesWrite = WriteFile(hFileDownload, Buffer, dwRead, &dwWritten, NULL);

				if(!bSuccesWrite)
				{
          CloseHandle(hFileDownload); hFileDownload = 0;
					InternetCloseHandle(hFileTransfer);
					throw(Exception("B³¹d funkcji WriteFile()"));
        }
				progress += dwRead; //Przesuwanie wskaŸnika odczytu pliku pobieranego z serwera
				ZeroMemory(Buffer, uiBufferSize);
				dwRead = 0; //Zerowanie licznika odczytanych bajtów z pliku pobieranego z serwera

			} while(bActive);

      //---Zamykanie uchwytu na otwarty plik na serwerze i na dysku
			CloseHandle(hFileDownload); hFileDownload = 0;
			InternetCloseHandle(hFileTransfer);

		}
		catch(...) {bRet = false;}
	}
	__finally
	{
		if(hInternetConnectHandle) InternetCloseHandle(hInternetConnectHandle);
		if(hInternetOpenHandle) InternetCloseHandle(hInternetOpenHandle);
		#if defined(_DEBUGINFO_)
			GsDebugClass::WriteDebug("__finally");
		#endif
	}
	return bRet;

}
//=====================FUNKCJE NIE BÊD¥CE METODAMI KLASY=====================
bool GsTypeConnected(UnicodeString &_ustrInfoTypeConnected)
/**
	OPIS METOD(FUNKCJI): Sprawdzanie czy komputer jest pod³¹czony do internetu
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
		if(State & INTERNET_CONNECTION_MODEM)      ustrTypeConect = "Po³¹czenie prze modem";
		if(State & INTERNET_CONNECTION_LAN)        ustrTypeConect = "Po³¹czenie przez LAN";
		if(State & INTERNET_CONNECTION_PROXY)      ustrTypeConect = "Po³¹czenie przez PROXY";
		if(State & INTERNET_CONNECTION_MODEM_BUSY) ustrTypeConect = "Modem zajêty";

		_ustrInfoTypeConnected = "Typ po³¹czenia: " + ustrTypeConect;
		bInternetConnect = true;
	}
	else
	{
		//bInternetConnect = false;
		_ustrInfoTypeConnected = "Brak po³¹czenie z Internetem!!!";
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
			TFile::Delete(GlobalVar::Global_custrLocalVersionFile);
			TFile::Delete(GlobalVar::Global_custrLocalApplicFile);
		break;
    //---
  }
	this->Close();
}
//---------------------------------------------------------------------------

