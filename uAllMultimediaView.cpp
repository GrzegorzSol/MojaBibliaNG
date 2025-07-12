#include <vcl.h>
#pragma hdrstop

#include "uAllMultimediaView.h"
#include "uGlobalVar.h"
#include <System.IOUtils.hpp>

#include "MyBibleLibrary\MyBibleLibrary.h"
#include "MyBibleLibrary\GsReadBibleTextData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAllMultimediaView *AllMultimediaView;

enum {//Indeksy głównych zakładek
			enSheet_Translates, enSheet_Graphics, enSheet_Comments, enSheet_FavVerses, enSheet_Count,
			//Indeksy grafik dla list
			enImage_Translates=0, enImage_Graphics, enImage_Comments, enImage_FavVerses,
			//Tagi dla objektów, klasy TControlList
			enCList_Translates = 100, enCList_Graphics, enCList_Comments, enCList_FavVerses,
			//Indeksy dla nagłówka, dla listy tłumaczeń
			enHeaderTranslates_Name=0, enHeaderTranslates_Type,
			//Indeksy dla nagłówka listy komentarzy
			enHeaderComments_Name=0,
			//Indeksy dla nagłówka ulubionych wersetów
			enHeaderFav_Name=0,
			//Indeksy dla nagłowka, dla grafik
			enHeaderGraphics_Name=0, enHeaderGraphics_Size};
//Nazwy zakładek
const UnicodeString //Nazwy zakładek
										cstrGroupName[] = {"Dostępne tłumaczenia", "Zarejestrowana grafika", "Lista komentarzy do wersetów", "Lista ulubionych wersetów"},
										//Nazwy nagłówków dla tłumaczeń
										cstrNameHeaderTranslates[] = {"Nazwa tłumaczenia", "Typ tłumaczenia"},
										//Nazwy nagłówków dla grafik
										cstrNameHeaderGraphics[] = {"Nazwa grafiki", "Wielkość grafiki"},
										//Nazwy nagłówków komentarzy
										cstrNameHeaderComments[] = {"Werset, z komentarzem"},
										//Nazwy nagłówków ulubionych wersetów
										cstrNameHeaderFav[] = {"Ulubione wersety"};

/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
*/
//---------------------------------------------------------------------------
__fastcall TAllMultimediaView::TAllMultimediaView(TComponent* Owner)
	: TForm(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->ImageSelectDisplay->Height = this->PanelDisplay->Height - 8;
	this->ImageSelectDisplay->Width = this->ImageSelectDisplay->Height;
	this->ImageSelectDisplay->Left = this->PanelDisplay->Width / 2 - (this->ImageSelectDisplay->Width / 2);
	this->ImageSelectDisplay->Top = 4;
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::FormCreate(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TTabSheet *pTSheet=nullptr;

	for(int i=0; i<this->PControlAllMultimedia->PageCount; ++i)
	{
		pTSheet = this->PControlAllMultimedia->Pages[i];
		pTSheet->Caption = cstrGroupName[i];
	}
	this->PControlAllMultimedia->ActivePage = this->TabSheetTranslates;

	this->_pHListGraphics = new THashedStringList();
	if(!this->_pHListGraphics) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
	this->_pHListComments	 = new THashedStringList();
	if(!this->_pHListComments) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
	this->_pHListFavVerses	= new THashedStringList();
	if(!this->_pHListFavVerses) throw(Exception("Błąd inicjalizacji objektu THashedStringList"));
	this->_pListAllFullTranslates = new TList();
	if(!this->_pListAllFullTranslates) throw(Exception("Błąd inicjalizacji objektu TList"));

	this->_SetTagsAndHints();
	this->_LoadAllTraslates(); //Tworzenie listy katalogów z grafiką
	this->_LoadAllGraphics();	 //Tworzenie listy grafik
	this->_LoadAllComments();	 //Tworzenie listy komentarzy
	this->_LoadAllFavVerses(); //Tworzenie listy ulubionych

	this->_pDisplayWindow = new TForm(this);
	if(!this->_pDisplayWindow) throw(Exception("Błąd inicjalizacji objektu TForm"));

	this->_pDisplayWindow->Width = Screen->Width;
	this->_pDisplayWindow->Height = Screen->Height;
	this->_pDisplayWindow->Left = 0; this->_pDisplayWindow->Top = 0;
	this->_pDisplayWindow->BorderStyle = bsNone;
	this->_pDisplayWindow->KeyPreview = true;
	this->_pDisplayWindow->OnKeyPress = this->_OnKeyPress;
	this->_pDisplayWindow->StyleElements = TStyleElements();
	this->_pDisplayWindow->Color = clBlack;

	this->_pImageScr = new TImage(this->_pDisplayWindow);
	if(!this->_pImageScr) throw(Exception("Błąd inicjalizacji objektu TImage"));
	this->_pImageScr->Parent = this->_pDisplayWindow;
	this->_pImageScr->Stretch = true;
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::FormDestroy(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(this->_pHListGraphics) {delete this->_pHListGraphics; this->_pHListGraphics = nullptr;}
	if(this->_pHListComments) {delete this->_pHListComments; this->_pHListComments = nullptr;}
	if(this->_pDisplayWindow) {delete this->_pDisplayWindow; this->_pDisplayWindow = nullptr;}
	if(this->_pHListFavVerses) {delete this->_pHListFavVerses; this->_pHListFavVerses = nullptr;}
	if(this->_pListAllFullTranslates) {delete this->_pListAllFullTranslates; this->_pListAllFullTranslates = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::FormClose(TObject *Sender, TCloseAction &Action)
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
void __fastcall TAllMultimediaView::_SetTagsAndHints()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->CListTranlates->Tag = enCList_Translates;
	this->CListGraphics->Tag = enCList_Graphics;
	this->CListComments->Tag = enCList_Comments;
	this->CListFavVerses->Tag = enCList_FavVerses;

	this->HeaderControlTranslates->Tag = enCList_Translates;
	this->HeaderControlGraphics->Tag = enCList_Graphics;
	this->HeaderControlComments->Tag = enCList_Comments;
	this->HeaderControlFavVerses->Tag = enCList_FavVerses;
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::_LoadAllTraslates()
/**
	OPIS METOD(FUNKCJI): Załadowanie wszystkich tłumaczeń
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TStringDynArray SDirList;
	UnicodeString ustrExt, ustrTempLowerName;
	THeaderSection *Section=nullptr;
	GsReadBibleTextItem *pGsReadBibleTextItem=nullptr;
	TList *pListAllTranslates=nullptr;

	//List wszystkich tłumaczeń
	pListAllTranslates = GsReadBibleTextData::GetGlobalListAllTraslates(); // Lista wszystkich tłumaczeń
	for(int i=0; i<pListAllTranslates->Count; ++i)
	{
		pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(pListAllTranslates->Items[i]);
		if((pGsReadBibleTextItem)	 && (pGsReadBibleTextItem->enTypeTranslate == enTypeTr_Full))
		{
			this->_pListAllFullTranslates->Add(pGsReadBibleTextItem);
		}
	}

	//Parametry list tłumaczeń
	this->CListTranlates->ItemCount = this->_pListAllFullTranslates->Count;
	this->CListTranlates->ItemHeight = this->ImgListAllView->Height;
	this->ImgListAllView->GetIcon(enImage_Translates, this->ImageTranslates->Picture->Icon);
	//THeaderControlTranslates
	for(int i=0; i<ARRAYSIZE(cstrNameHeaderTranslates); ++i)
	{
		Section = this->HeaderControlTranslates->Sections->Add();
		Section->Text = cstrNameHeaderTranslates[i];
	}
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::_LoadAllGraphics()
/**
	OPIS METOD(FUNKCJI): Załadowanie wszystkich grafik
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TStringDynArray SDirMultiMList;
	UnicodeString ustrExt, ustrTempLowerName;
	THeaderSection *Section=nullptr;
	NativeUInt nuiFile=0;
	int iSize=0;

	TStringList *SListTemp = new TStringList(); //Tymczasowy objekt, z zawartością wszystkich ścieżek dostępu do katalogów z multimediami
	if(!SListTemp) throw(Exception("Błąd inicjalizacji objektu TStringList"));
	SListTemp->Add(GlobalVar::Global_custrPathMultimediaFilesData);
	SListTemp->Add(GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM1, ""));
	SListTemp->Add(GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM2, ""));
	SListTemp->Add(GlobalVar::Global_ConfigFile->ReadString(GlobalVar::GlobalIni_MainSection_Main, GlobalVar::GlobalIni_PathMultiM3, ""));

	//Lista grafik
	for(int iSelectDir=0; iSelectDir<SListTemp->Count; iSelectDir++)
	{
		if(SListTemp->Strings[iSelectDir].IsEmpty()) continue;
		SDirMultiMList = TDirectory::GetFiles(SListTemp->Strings[iSelectDir]);
		for(int i=0; i<SDirMultiMList.Length; ++i)
		{
			ustrTempLowerName = LowerCase(SDirMultiMList[i]);
			if((TPath::GetExtension(ustrTempLowerName) != ".jpg") &&
				 (TPath::GetExtension(ustrTempLowerName) != ".jpeg") &&
				 (TPath::GetExtension(ustrTempLowerName) != ".png") &&
				 (TPath::GetExtension(ustrTempLowerName) != ".bmp")) continue;

			try
			{
				nuiFile = FileOpen(SDirMultiMList[i], fmOpenRead);
				if(nuiFile) iSize = FileSeek(nuiFile, 0, 2);
			}
			__finally
			{
				if(nuiFile) FileClose(nuiFile);
			}
			this->_pHListGraphics->Add(Format("%s=%d", ARRAYOFCONST((SDirMultiMList[i], iSize))));
		}
		SDirMultiMList.Length = 0;
	}
	//Parametry listy grafik
	this->CListGraphics->ItemCount = this->_pHListGraphics->Count;
	this->CListGraphics->ItemHeight = this->ImgListAllView->Height;
	this->ImgListAllView->GetIcon(enImage_Graphics, this->ImageGraphics->Picture->Icon);
	//THeaderControlGraphics
	for(int i=0; i<ARRAYSIZE(cstrNameHeaderGraphics); ++i)
	{
		Section = this->HeaderControlGraphics->Sections->Add();
		Section->Text = cstrNameHeaderGraphics[i];
	}

	if(SListTemp) {delete SListTemp; SListTemp = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::_LoadAllComments()
/**
	OPIS METOD(FUNKCJI): Załadowanie wszystkich komentarzy
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TStringDynArray SDCommentFile;
	THeaderSection *Section=nullptr;

	//Lista komentarzy
	SDCommentFile = TDirectory::GetFiles(GlobalVar::Global_custrPathDirComments);
	for(int i=0; i<SDCommentFile.Length; ++i)
	{
		this->_pHListComments->Add(SDCommentFile[i]);
	}
	SDCommentFile.Length = 0;
	//Parametry listy komentarzy
	this->CListComments->ItemCount = this->_pHListComments->Count;
	this->CListComments->ItemHeight = this->ImgListAllView->Height;
	this->ImgListAllView->GetIcon(enImage_Comments, this->ImageComments->Picture->Icon);
	//HeaderControlComments
	for(int i=0; i<ARRAYSIZE(cstrNameHeaderComments); ++i)
	{
		Section = this->HeaderControlComments->Sections->Add();
		Section->Text = cstrNameHeaderComments[i];
	}
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::_LoadAllFavVerses()
/**
	OPIS METOD(FUNKCJI): Załadowanie wszystkich ulubionych wersetów
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	THeaderSection *Section=nullptr;
	TStringList *SListTemp = new TStringList(); //Tymczasowy objekt, z zawartością wszystkich ścieżek dostępu do katalogów z multimediami
	if(!SListTemp) throw(Exception("Błąd inicjalizacji objektu TStringList"));

	//Lista ulubionych wersetów
	if(TFile::Exists(GlobalVar::Global_custrPathFileFavoriteVers))
	{
		SListTemp->LoadFromFile(GlobalVar::Global_custrPathFileFavoriteVers);
		for(int i=0; i<SListTemp->Count; ++i)
		{
			this->_pHListFavVerses->Add( SListTemp->Strings[i]);
		}
	}
	//Parametry listy ulubionych
	this->CListFavVerses->ItemCount = this->_pHListFavVerses->Count;
	this->CListFavVerses->ItemHeight = this->ImgListAllView->Height;;
	this->ImgListAllView->GetIcon(enImage_FavVerses, this->ImageFavVerses->Picture->Icon);
	//HeaderControlFavVerses
	for(int i=0; i<ARRAYSIZE(cstrNameHeaderFav); ++i)
	{
		Section = this->HeaderControlFavVerses->Sections->Add();
		Section->Text = cstrNameHeaderFav[i];
	}

	if(SListTemp) {delete SListTemp; SListTemp = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::_DisplaySelectVersAllTrans(const UnicodeString ustrCodeVers)
/**
	OPIS METOD(FUNKCJI): Wyświetlanie zaznaczonego komentarza
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//return;
	int iBook, iChapt, iVers;
	UnicodeString ustrAdress, ustrNameTr, ustrText;
	const UnicodeString GlobalSizeFontText = "\\fs32",
											GlobalHeaderRtf = UnicodeString("{\\urtf1\\ansi\\ansicpg1250\\deff0\\nouicompat\\deflang1045{\\fonttbl{\\f0\\fnil\\fcharset238 Calibri;}{\\f1\\fnil\\fcharset0 Calibri;}}") +
																		 "{\\colortbl ;\\red0\\green0\\blue0;\\red255\\green0\\blue0;\\red0\\green200\\blue0;\\red0\\green0\\blue255;\\red200\\green0\\blue200;}" +
																		 "{\\*\\generator Msftedit 5.41.21.2510;}\\viewkind4\\uc1" +
																		 "\\pard\\sa200\\sl276\\slmult1\\cf4\\fs45\\b Podgląd wersetu z listy ulubionych, lub wersetu, który posiada komentarz\\cf0\\b0\\f1\\fs22\\lang21\\par\\fs28",// + GlobalSizeFontText,
											GlobalAdressVersRtf = "\\f1\\cf2\\b",
											GlobalVersRtf = "\\cf1\\b0\\f0",
											GlobalNameTransRtf = "\\cf5\\f1",
											GlobalSizeNameTransRtf = "\\fs26";

	this->ImageSelectDisplay->Picture->Assign(nullptr);
	this->ImageSelectDisplay->Visible = false;

	TStringStream *pStringStream = new TStringStream("", TEncoding::UTF8, true);
	if(!pStringStream) throw(Exception("Błąd inicjalizacji objektu TStringStream"));

	iBook = ustrCodeVers.SubString(1, 3).ToInt()-1;
	iChapt = ustrCodeVers.SubString(4, 3).ToInt();
	iVers = ustrCodeVers.SubString(7, 3).ToInt();
	ustrAdress = Format("%s %d:%d", ARRAYOFCONST((AppCTable_InfoAllBooks[iBook].FullNameBook, iChapt, iVers)));

	pStringStream->WriteString(GlobalHeaderRtf);

	for(int iLicz=0; iLicz<this->_pListAllFullTranslates->Count; ++iLicz)
	{
		//ustrText = "";
		GsReadBibleTextItem *pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(this->_pListAllFullTranslates->Items[iLicz]);
		if(pGsReadBibleTextItem->enTypeTranslate != enTypeTr_Full) continue;
		GsReadBibleTextData::GetTextVersOfAdress(iBook, iChapt, iVers, iLicz, ustrText);

		if(ustrText.Length() > 0)
		{
			pStringStream->WriteString(Format("%s%s %s " ,ARRAYOFCONST((GlobalSizeFontText, GlobalAdressVersRtf, ustrAdress))));
			pStringStream->WriteString(Format("%s %s" ,ARRAYOFCONST((GlobalVersRtf, ustrText))));
			ustrNameTr = Format("%s%s	[%s]%s" ,ARRAYOFCONST((GlobalNameTransRtf, GlobalSizeNameTransRtf, pGsReadBibleTextItem->NameTranslate, "\\line")));
			pStringStream->WriteString(ustrNameTr);
		}
	}

	pStringStream->WriteString("}");
	pStringStream->Position = 0;
	this->RichEditInfo->Lines->LoadFromStream(pStringStream);

	if(pStringStream) {delete pStringStream; pStringStream = nullptr;}
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::_DisplayImage(const UnicodeString _pathImages)
/**
	OPIS METOD(FUNKCJI): Wyświetlanie zaznaczonej grafiki w mini podglądzie
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	UnicodeString	 ustrSelectItem;
	TWICImage *pWICImage=nullptr;

	this->ImageSelectDisplay->Visible = true;
	try
	{
		try
		{
			pWICImage = new TWICImage();
			if(!pWICImage) throw(Exception("Błąd inicjalizacji objektu TWICImage"));
			//---
			pWICImage->LoadFromFile(_pathImages);
			this->_fFactorProp = (float)pWICImage->Width / (float)pWICImage->Height;
			this->ImageSelectDisplay->Picture->Assign(pWICImage);
			this->PanelDisplay->OnResize(this->PanelDisplay);

			ustrSelectItem = Format("Ścieżka dostępu do pliku graficznego: \"%s\" - Rozmiar: %d x %d", ARRAYOFCONST((_pathImages, pWICImage->Width, pWICImage->Height)));
			this->RichEditInfo->Lines->Text = ustrSelectItem;
		}
		catch(Exception &e)
		{
			MessageBox(NULL, e.Message.c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{
		if(pWICImage) {delete pWICImage; pWICImage = nullptr;}
	}
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::CListTranlatesBeforeDrawItem(int AIndex,
					TCanvas *ACanvas, TRect &ARect, TOwnerDrawState AState)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	THeaderSection *Section=nullptr;
	GsReadBibleTextItem *pGsReadBibleTextItem=nullptr;
	UnicodeString ustrExt, ustrInfo;

	this->ImageTranslates->Width = this->ImageTranslates->Height;
	pGsReadBibleTextItem = static_cast<GsReadBibleTextItem *>(this->_pListAllFullTranslates->Items[AIndex]);
	if(pGsReadBibleTextItem)
	{
		this->LabelNameTranlate->Caption = pGsReadBibleTextItem->NameTranslate;
		ustrExt = TPath::GetExtension(pGsReadBibleTextItem->FullPathTranslate);
		ustrInfo = pGsReadBibleTextItem->PathInfoTranslate;
	}

	//Rozróżnianie typu tłumaczenia po rozszerzeniu plików
	if(ustrExt == GsReadBibleTextData::GsExtendNoAsteriskFileTranslateFull) this->LabelTypeTranslate->Caption = "Pełne tłumaczenie";
			else if(ustrExt == GsReadBibleTextData::GsExtendNoAsteriskFileTranslateGrecOrg) this->LabelTypeTranslate->Caption = "Oryginalne greckie tłumaczenie";
			else if(ustrExt == GsReadBibleTextData::GsExtendNoAsteriskFileTranslateHbrOrg) this->LabelTypeTranslate->Caption = "Oryginalne hebrajskie tłumaczenie";

	for(int i=0; i<this->HeaderControlTranslates->Sections->Count; ++i)
	{
		Section = this->HeaderControlTranslates->Sections->Items[i];
		if(i==enHeaderTranslates_Name) Section->Width = this->LabelNameTranlate->Left + this->LabelNameTranlate->Width;
		else if(i==enHeaderTranslates_Type) Section->Width = this->LabelTypeTranslate->Left + this->LabelTypeTranslate->Width;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::CListGraphicsBeforeDrawItem(int AIndex, TCanvas *ACanvas,
					TRect &ARect, TOwnerDrawState AState)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	THeaderSection *Section=nullptr;
	TColor cSelectImg = clHighlight;

	this->ImageGraphics->Width = this->ImageGraphics->Height;
	this->LabelNameGraphics->Caption = this->_pHListGraphics->Names[AIndex];

	this->LabelSizeGraphics->Caption = this->_pHListGraphics->ValueFromIndex[AIndex];

	for(int i=0; i<this->HeaderControlGraphics->Sections->Count; ++i)
	{
		Section = this->HeaderControlGraphics->Sections->Items[i];
		if(i==enHeaderGraphics_Name) Section->Width = this->LabelNameGraphics->Left + this->LabelNameGraphics->Width;
		else if(i == enHeaderGraphics_Size) Section->Width = this->LabelSizeGraphics->Width;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::CListCommentsBeforeDrawItem(int AIndex, TCanvas *ACanvas,
					TRect &ARect, TOwnerDrawState AState)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	THeaderSection *Section=nullptr;
	int iBook, iChap, iVers;
	UnicodeString ustrComm = TPath::GetFileNameWithoutExtension(this->_pHListComments->Strings[AIndex]);
	TColor cSelectImg = clHighlight;

	iBook = ustrComm.SubString(1, 3).ToInt()-1;
	iChap = ustrComm.SubString(4, 3).ToInt();
	iVers = ustrComm.SubString(7, 3).ToInt();

	this->ImageComments->Width = this->ImageComments->Height;
	this->LabelComments->Caption = Format("%s %d:%d", ARRAYOFCONST((AppCTable_InfoAllBooks[iBook].FullNameBook, iChap, iVers)));

	for(int i=0; i<this->HeaderControlComments->Sections->Count; ++i)
	{
		Section = this->HeaderControlComments->Sections->Items[i];
		if(i==enHeaderComments_Name) Section->Width = this->LabelComments->Left + this->LabelComments->Width;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::CListFavVersesBeforeDrawItem(int AIndex,
					TCanvas *ACanvas, TRect &ARect, TOwnerDrawState AState)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	THeaderSection *Section=nullptr;
	int iBook, iChapt, iVers;
	UnicodeString _ustrFavCodeVers=this->_pHListFavVerses->Strings[AIndex];
	TColor cSelectImg = clHighlight;

	iBook = _ustrFavCodeVers.SubString(1, 3).ToInt()-1;
	iChapt = _ustrFavCodeVers.SubString(4, 3).ToInt();
	iVers = _ustrFavCodeVers.SubString(7, 3).ToInt();

	this->ImageFavVerses->Width = this->ImageFavVerses->Height;
	this->LabelFavVerses->Caption =	 Format("%s %d:%d", ARRAYOFCONST((AppCTable_InfoAllBooks[iBook].FullNameBook, iChapt, iVers)));

	for(int i=0; i<this->HeaderControlFavVerses->Sections->Count; ++i)
	{
		Section = this->HeaderControlFavVerses->Sections->Items[i];
		if(i==enHeaderFav_Name) Section->Width = this->LabelFavVerses->Left + this->LabelFavVerses->Width;
	}
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::CListAllItemClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI): Wybór pozycji z list
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TControlList *pCList = dynamic_cast<TControlList *>(Sender);
	if(!pCList) return;
	//---
	UnicodeString	ustrSelectItem;

	switch(pCList->Tag)
	{
		case enCList_Translates:
		{
			GsReadBibleTextItem *pGsReadBibleTextItem=nullptr;

			this->ImageSelectDisplay->Picture->Assign(nullptr);
			this->ImageSelectDisplay->Visible = false;

			pGsReadBibleTextItem = GsReadBibleTextData::GetTranslate(pCList->ItemIndex);
			if(pGsReadBibleTextItem)
			{
				ustrSelectItem = pGsReadBibleTextItem->PathInfoTranslate;
				if(TFile::Exists(ustrSelectItem))
				{
					this->RichEditInfo->Lines->LoadFromFile(ustrSelectItem);
				}
			}
		}
		break;
		//---
		case enCList_Graphics:
			this->_DisplayImage(this->_pHListGraphics->Names[pCList->ItemIndex]);
			break;
		//---
		case enCList_Comments:
			this->RichEditInfo->Lines->LoadFromFile(this->_pHListComments->Strings[pCList->ItemIndex]);
			break;
		//---
		case enCList_FavVerses:
			this->_DisplaySelectVersAllTrans(this->_pHListFavVerses->Strings[pCList->ItemIndex]);
			break;
		//---
	}
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::PanelDisplayResize(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPanel *pPanel = dynamic_cast<TPanel *>(Sender);
	if(!pPanel) return;
	//---
	this->ImageSelectDisplay->Height = pPanel->Height - 8;
	this->ImageSelectDisplay->Width = this->_fFactorProp * this->ImageSelectDisplay->Height;
	this->ImageSelectDisplay->Left = pPanel->Width / 2 - (this->ImageSelectDisplay->Width / 2);
	this->ImageSelectDisplay->Top = 4;//(pPanel->Height / 2 - (this->ImageSelectDisplay->Height / 2)) + 4;

//	#if defined(_DEBUGINFO_)
//		GsDebugClass::WriteDebug(Format("H: %d, W: %d", ARRAYOFCONST((this->ImageSelectDisplay->Height, this->ImageSelectDisplay->Width ))));
//	#endif
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::HeaderControlAllSectionResize(THeaderControl *HeaderControl,
					THeaderSection *Section)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	switch(HeaderControl->Tag)
	{
		case enCList_Translates:
			if(Section->Index == enHeaderTranslates_Name)
				{this->LabelNameTranlate->Width = Section->Width - this->ImageTranslates->Width;}
			else if(Section->Index == enHeaderTranslates_Type)
				{this->LabelTypeTranslate->Width = Section->Width;}
			this->CListTranlates->Invalidate();
			break;
		//---
		case enCList_Graphics:
			if(Section->Index == enHeaderGraphics_Name)
				{this->LabelNameGraphics->Width = Section->Width - this->ImageGraphics->Width;}
			this->CListGraphics->Invalidate();
			break;
		//---
		case enCList_Comments:
			this->CListComments->Invalidate();
			break;
		//---
		case enCList_FavVerses:
			this->CListFavVerses->Invalidate();
			break;
		//---
	}
}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::PControlAllMultimediaDrawTab(TCustomTabControl *Control,
					int TabIndex, const TRect &Rect, bool Active)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TPageControl *pPControl = dynamic_cast<TPageControl *>(Control);
	if(!pPControl) return;
	//---
	TRect MyRect(Rect);
	TColor ColorBackG=clBtnFace, ColorSelect=clRed, ColorFont=clWindowText;

	if(TStyleManager::Enabled)
	{
		ColorBackG = TStyleManager::ActiveStyle->GetStyleColor((TStyleColor)clBackground);
		pPControl->Canvas->Font->Color =	TStyleManager::ActiveStyle->GetStyleFontColor((TStyleFont)sfTabTextActiveNormal);
	}
	//pPControl->Canvas->Font->Color = clGreen;
	if(Active)
		{pPControl->Canvas->Brush->Color = ColorSelect;}
	else {pPControl->Canvas->Brush->Color = ColorBackG;}

	pPControl->Canvas->FillRect(MyRect);
	MyRect.Inflate(-6, 0);

	TTabSheet *pSheet = pPControl->Pages[TabIndex];
	DrawText(pPControl->Canvas->Handle, pSheet->Caption.c_str(), -1, &MyRect, DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS);
}
//---------------------------------------------------------------------------
/////////////////////////////////////////////////////////////////////////////
//																																				 //
//							OTWARCIE PEŁNOEKRANOWEGO PODGLADU WYBRANEJ								 //
//										GRAFIKI I JEGO PRYWATNE METODY											 //
//																																				 //
/////////////////////////////////////////////////////////////////////////////
void __fastcall TAllMultimediaView::ImageSelectDisplayDblClick(TObject *Sender)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TImage *pImg = dynamic_cast<TImage *>(Sender);
	if(!pImg) return;
	//---
	TWICImage *pWICImg=nullptr;
	UnicodeString _ustrCurrentPathImage = this->_pHListGraphics->Names[this->CListGraphics->ItemIndex];
	//---
	try
	{
		try
		{
			pWICImg = new TWICImage();
			if(!pWICImg) throw(Exception("Błąd inicjalizacji objektu TWICImage"));

			pWICImg->LoadFromFile(_ustrCurrentPathImage);
			float fSizeFactorWH = (float)pWICImg->Width / (float)pWICImg->Height, //Proporcje szerokości do wysokości, wczytanej grafiki
						fSizeFactorHW = (float)pWICImg->Height / (float)pWICImg->Width; //Proporcje wysokości do szerokości, wczytanej grafiki
			//--- Sprawdzanie wysokości grafiki
			if(pWICImg->Height > this->_pDisplayWindow->ClientHeight)
				{this->_pImageScr->Height = this->_pDisplayWindow->ClientHeight;}
			else
				{this->_pImageScr->Height = pWICImg->Height;}
			this->_pImageScr->Width = fSizeFactorWH * this->_pImageScr->Height;
			//---

			this->_pImageScr->Left = this->_pDisplayWindow->ClientWidth / 2 - (this->_pImageScr->Width / 2);
			this->_pImageScr->Top = this->_pDisplayWindow->ClientHeight / 2 - (this->_pImageScr->Height / 2);
			this->_pImageScr->Picture->Assign(pWICImg); //Skopiwanie bitmapy wczytanej grafiki do bitmapy objektu, klasy TImage

			this->_pDisplayWindow->Show();
		}
		catch(Exception &e)
		{
			MessageBox(NULL, e.Message.c_str(), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	}
	__finally
	{
		if(pWICImg) {delete pWICImg; pWICImg = nullptr;}
	}

}
//---------------------------------------------------------------------------
void __fastcall TAllMultimediaView::_OnKeyPress(TObject *Sender, System::WideChar &Key)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	TForm *pForm = dynamic_cast<TForm *>(Sender);
	if(!pForm) return;
	//---
	if(this->CListGraphics->ItemIndex == -1) return;
	//---
	switch(Key)
	{
		case vkEscape:
			pForm->Hide(); //Schowanie okna
		break;
		//---
		case vkSpace: //Następna grafika
			if(this->CListGraphics->ItemIndex < this->CListGraphics->ItemCount)
			{
				++this->CListGraphics->ItemIndex;
				this->ImageSelectDisplayDblClick(this->ImageSelectDisplay);
				this->_DisplayImage(this->_pHListGraphics->Names[this->CListGraphics->ItemIndex] );
			}
		break;
		//---
		case vkBack: //Poprzednia grafika
			if(this->CListGraphics->ItemIndex > 0)
			{
				--this->CListGraphics->ItemIndex;
				this->ImageSelectDisplayDblClick(this->ImageSelectDisplay);
				this->_DisplayImage(this->_pHListGraphics->Names[this->CListGraphics->ItemIndex] );
			}
		break;
	}
}
//---------------------------------------------------------------------------


