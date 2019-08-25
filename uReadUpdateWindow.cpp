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
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Test"), TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
*/
bool GsTypeConnected(UnicodeString &_ustrInfoTypeConnected);

//---------------------------------------------------------------------------
__fastcall TReadUpdateWindow::TReadUpdateWindow(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENT�W:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{


  this->LabeledEdCurrentVersion->Text = GlobalVar::Global_ustrVerAplicMain;
	//--- Sprawdzenie po��czenia z internetem
	UnicodeString ustrReturnConect;
	bool bRet = GsTypeConnected(ustrReturnConect);

	if(bRet)
	//Je�li pol�czenei powiod�o si�
	{
		this->Caption = Format("%s - %s", ARRAYOFCONST((this->Caption, ustrReturnConect)));
	}
	else
	{
	 throw(Exception("Brak dost�pu do sieci"));
	}

	this->_GetIsUpdateVerify();
}
//---------------------------------------------------------------------------
void __fastcall TReadUpdateWindow::FormClose(TObject *Sender, TCloseAction &Action)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENT�W:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TReadUpdateWindow::_GetIsUpdateVerify()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENT�W:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //Uzyskanie �cie�ki dostepu do katalogu Temp
	TCHAR pathTemp[MAX_PATH];
	GetTempPath(MAX_PATH, pathTemp);
	const UnicodeString ustrDestinyDownloadVersion = pathTemp + GlobalVar::Global_custrNameIVerFile + "_ftp",
											ustrDestinyDownloadApplication = pathTemp + System::Sysutils::ExtractFileName(Application->ExeName) + "_ftp";
	bool bRetDownload=false;

	bRetDownload = this->_DownLoadFileFTP(ustrDestinyDownloadVersion, "/public_html/wp-content/uploads/MojaBibliaNG/MBibleNG.iver");
	if(!bRetDownload) this->Caption = "B��d procesu aktualizacji!";

	TStringBuilder *pStrBuilderDownload = new TStringBuilder();
	if(!pStrBuilderDownload) throw(Exception("B��d inicjalizacji objektu TStringBuilder"));

	__int64 i64DonloadFile=0, i64LocalFile=0;

	pStrBuilderDownload->Append(TFile::ReadAllText(ustrDestinyDownloadVersion, TEncoding::UTF8));
	TFile::Delete(ustrDestinyDownloadVersion);
	this->LabeledEdDownLoadversion->Text = pStrBuilderDownload->ToString();

	pStrBuilderDownload->Replace(".", ""); //Usuni�cie kropek

	if(!TryStrToInt64(pStrBuilderDownload->ToString(), i64DonloadFile))
	//je�li nie uda�o si� skonwertowa� na __int64, to musia� nast�pi� b��d
	{
		delete pStrBuilderDownload; return;
	}
	pStrBuilderDownload->Clear(); //Wyczyszczenie zawarto�ci
	pStrBuilderDownload->Append(GlobalVar::Global_ustrVerAplicMain);
	pStrBuilderDownload->Replace(".", ""); //Usuni�cie kropek
	if(!TryStrToInt64(pStrBuilderDownload->ToString(), i64LocalFile))
	//je�li nie uda�o si� skonwertowa� na __int64, to musia� nast�pi� b��d
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
		this->STextInfos->Caption = "Jest dost�pna nowsza wersja na serwerze aktualizacyjnym";
		GlobalVar::iReturnUpdate = 1;
    //Pobranie nowszej wersji
		bRetDownload = this->_DownLoadFileFTP(ustrDestinyDownloadApplication, "/public_html/wp-content/uploads/MojaBibliaNG/Moja Biblia NG.zip");
		if(!bRetDownload) this->Caption = "B��d procesu aktualizacji!";

		TFile::Delete(ustrDestinyDownloadApplication);
	}
	if(i64DonloadFile < i64LocalFile)
	{
		this->STextInfos->Caption = "Wersja lokalna jest nowsza ni� na serwerze aktualizacyjnym";
		GlobalVar::iReturnUpdate = -1;
	}

	delete pStrBuilderDownload;
}
//---------------------------------------------------------------------------
bool __fastcall TReadUpdateWindow::_DownLoadFileFTP(const UnicodeString _destPathDownload, const UnicodeString _ustrPathFTPFile)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENT�W:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  HINTERNET hInternetConnectHandle=NULL; 	//Wynik funkcji InternetConnect()
	HINTERNET hInternetOpenHandle=NULL;	//Wynik funkcji InternetOpen()
	const UnicodeString ustrHostName = "ftp.nasz-salem.pl",
											ustrMyUser = "naszsalem",
											ustrMyPassword = "JdgoG3OEc3v3";

	bool bRet=true;
  const unsigned int uiBufferSize = 4096;

  hInternetOpenHandle = InternetOpen(0, INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, INTERNET_FLAG_PASSIVE);
	if(!hInternetOpenHandle) return false;

	try
	{
		try
		{
			hInternetConnectHandle = InternetConnect(hInternetOpenHandle, ustrHostName.c_str(), INTERNET_DEFAULT_FTP_PORT,
																							 ustrMyUser.c_str(), ustrMyPassword.c_str(), INTERNET_SERVICE_FTP, INTERNET_FLAG_PASSIVE, 0);
			if(!hInternetConnectHandle) throw(Exception("B��d funkcji hInternetConnectHandle()"));

      HINTERNET hFileTransfer = NULL;
			HANDLE hFileDownload = NULL;

			hFileTransfer = FtpOpenFile(hInternetConnectHandle, _ustrPathFTPFile.c_str(), GENERIC_READ, FTP_TRANSFER_TYPE_BINARY, 0);
			if(!hFileTransfer) throw(Exception("B��d funkcji FtpOpenFile()"));
			//--- Wielko�� pliku na serwerze
			DWORD filesized = 0; //D�ugo�� pliku na serwerze
			filesized =  FtpGetFileSize(hFileTransfer, NULL);
      #if defined(_DEBUGINFO_)
				GsDebugClass::WriteDebug(Format("filesized: %u", ARRAYOFCONST((filesized))));
			#endif

			hFileDownload = CreateFile(_destPathDownload.c_str(), GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
      if(hFileDownload == INVALID_HANDLE_VALUE)
			{
				//Plik na serwerze musimy zamkn��, na dysku nie gdy� nie zosta� otwarty z powodu b��du.
				InternetCloseHandle(hFileTransfer); hFileTransfer = 0;
				throw(Exception("B��d funkcji CreateFile()"));
			}

      bool bActive = true, //Test czy koniec zciaganego pliku z serwera ju� nast�pi�
					 bSuccess = false, //Odczyt kolejnej porcji pliku z serwera powi�d� si�
					 bSuccesWrite = false; //Zapis pobranego pliku do lokalnego katalogu
			char Buffer[uiBufferSize]; //Bufor na porcje, odczytywanego pliku z serwera
			DWORD dwBytesAvailable = 0,
						dwRead = 0,	//Ilo�� odczytanych bajt�w z pliku, na serwerze
						dwWritten = 0;	//Ilo�� zapisanych danych na dysku lokalnym
			int progress=0; //Wska�nik na pozycje w czytanym pliku z serwera

			//---G��wna p�tla pobierania pliku z serwera i zapisu go na lokalny dysk twardy.
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
					break;	//Wyskoczenie z p�tli w przypadku b��du(bSucces==false), lub napotkania ko�ca pliku,
									//pobieranego z serwera(bActive==false)
				}
        //Zapisujemy pobran� porcj� danych z pliku na serwerze
				dwWritten = 0;	//Zerowanie ilo�ci zapisanej na lokalny dysk
				bSuccesWrite = WriteFile(hFileDownload, Buffer, dwRead, &dwWritten, NULL);

				if(!bSuccesWrite)
				{
          CloseHandle(hFileDownload); hFileDownload = 0;
					InternetCloseHandle(hFileTransfer);
					throw(Exception("B��d funkcji WriteFile()"));
        }
				progress += dwRead; //Przesuwanie wska�nika odczytu pliku pobieranego z serwera
				ZeroMemory(Buffer, uiBufferSize);
				dwRead = 0; //Zerowanie licznika odczytanych bajt�w z pliku pobieranego z serwera

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
//=====================FUNKCJE NIE B�D�CE METODAMI KLASY=====================
bool GsTypeConnected(UnicodeString &_ustrInfoTypeConnected)
/**
	OPIS METOD(FUNKCJI): Sprawdzanie czy komputer jest pod��czony do internetu
	OPIS ARGUMENT�W:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	bool bInternetConnect=false;
	DWORD State;
	if(InternetGetConnectedState(&State, 0))
	{
		UnicodeString ustrTypeConect;
		if(State & INTERNET_CONNECTION_MODEM)      ustrTypeConect = "Po��czenie prze modem";
		if(State & INTERNET_CONNECTION_LAN)        ustrTypeConect = "Po��czenie przez LAN";
		if(State & INTERNET_CONNECTION_PROXY)      ustrTypeConect = "Po��czenie przez PROXY";
		if(State & INTERNET_CONNECTION_MODEM_BUSY) ustrTypeConect = "Modem zaj�ty";

		_ustrInfoTypeConnected = "Typ po��czenia: " + ustrTypeConect;
		bInternetConnect = true;
	}
	else
	{
		//bInternetConnect = false;
		_ustrInfoTypeConnected = "Brak po��czenie z Internetem!!!";
	}
	return bInternetConnect;
}
