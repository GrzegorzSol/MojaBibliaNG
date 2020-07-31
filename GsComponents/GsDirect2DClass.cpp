#include "GsDirect2DClass.h"
#include <Vcl.Graphics.hpp>
#include <System.IOUtils.hpp>
/*
	#if defined(__BORLANDC__) && defined(__clang__) && defined(_WIN32)
		//Your code.
	#endif
	#if defined(__BORLANDC__) && defined(__clang__)
    //Your code.
	#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
*/
#if defined(__BORLANDC__) && defined(_WIN64)
	#pragma link "D2d1.a"
  #pragma link "dwrite.a"
#else
	#pragma link "D2d1.lib"
	#pragma link "dwrite.lib"
#endif

#pragma package(smart_init)

const float DEFAULT_DPI = 96.0f;   // Domyślne DPI, które mapuje rozdzielczość obrazu bezpośrednio do rozdzielczości ekranu
//Nadanie wartości składnikom statycznym
const UnicodeString GsDirect2DClass::csVersion = "0.6.4689.9047";
bool GsDirect2DClass::IsInitListfonts = false; //Lista czcionek została wczytana, lub nie, w tej klasie
//---------------------------------------------------------------------------
template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	if(*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}
//---------------------------------------------------------------------------
__fastcall GsDirect2DClass::GsDirect2DClass(TComponent* Owner) : TCustomPanel(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->DoubleBuffered = true;
	//Trzeba wszystkie wskaźniki zainicjować wartością NULL!!!
	//Direct2D
	this->pID2D1Bitmap=NULL;
	this->pIWICFormatConverter=NULL;
	this->pIWICImagingFactory=NULL;
	this->pID2D1Factory=NULL;
	this->pID2D1HwndRenderTarget=NULL;
	//DirectWrite
	this->pIDWriteFactory=NULL;
	this->pIDWriteTextFormat=NULL;
	this->pIDWriteTextLayout=NULL;
	this->pID2D1SolidColorBrush1=NULL;
  this->pID2D1SolidColorBrush2=NULL;
	//Flagi i zmienne ustawień
	this->FIsDisplayText=CFIsDisplayText;
	this->FNameFont = CFNameFont;
	this->FSizeFont = CFSizeFont;
	this->FTextWrite = CFTextWrite;
	this->FD2DColorText = CFD2DColorText;
  this->FD2DColorText2 = CFD2DColorText2;
	this->FStandardColorText = CFStandardColorText;
	this->FStandardColorText2 = CFStandardColorText2;
	this->FRotationText = CFRotationText;
	this->FOpacityBrush = CFOpacityBrush;
	this->FIsModified = false;
	this->FIsDisplayText = false;
  this->FIsGradientColorFont = false;

	//Uzyskanie informacje o dpi
	HDC screen = GetDC(0);
	this->_dpiScaleX = GetDeviceCaps(screen, LOGPIXELSX) / 96.0f;
	this->_dpiScaleY = GetDeviceCaps(screen, LOGPIXELSY) / 96.0f;
	ReleaseDC(0, screen);

	this->FIsLoadedImage = false; //Czy obrazek został załadowany
}
//---------------------------------------------------------------------------
__fastcall GsDirect2DClass::~GsDirect2DClass()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //Direct2D
	SafeRelease(&this->pID2D1Bitmap);
	SafeRelease(&this->pIWICFormatConverter);
	SafeRelease(&this->pIWICImagingFactory);
	SafeRelease(&this->pID2D1Factory);
	SafeRelease(&this->pID2D1HwndRenderTarget);
	//DirectWrite
	SafeRelease(&this->pIDWriteFactory);
	SafeRelease(&this->pIDWriteTextFormat);
  SafeRelease(&this->pIDWriteTextLayout);
	SafeRelease(&this->pID2D1SolidColorBrush1);
	SafeRelease(&this->pID2D1SolidColorBrush2);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::GsD2D_LoadPicture(const UnicodeString custrPathImage, const bool _bAutosize)
/**
	OPIS METOD(FUNKCJI):Załaduj plik obrazu i utwórz D2DBitmap
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	HRESULT hr=S_OK;
	this->_ustrPathImage = custrPathImage;

	//Tworzenie dekodera
	IWICBitmapDecoder *pIWICBitmapDecoder=NULL;
	IWICBitmapFrameDecode *pIWICBitmapFrameDecode=NULL;

	try
	{
		hr = this->pIWICImagingFactory->CreateDecoderFromFilename(
			custrPathImage.c_str(),          //Dekodowanie obrazu
			NULL,
			GENERIC_READ,                    //Prawo odczytu pliku
			WICDecodeMetadataCacheOnDemand,  //Kesz metadanych, gdy trzeba
			&pIWICBitmapDecoder              //Wskaźnik do dekodera
		);
		if(FAILED(hr)) throw(Exception("Błąd metody CreateDecoderFromFilename())"));

		//Pozyskanie pierwszej klatki obrazka dla dekodera
		hr = pIWICBitmapDecoder->GetFrame(0, &pIWICBitmapFrameDecode);
		if(FAILED(hr)) throw(Exception("Błąd metody GetFrame())"));

		SafeRelease(&this->pIWICFormatConverter);
		hr = this->pIWICImagingFactory->CreateFormatConverter(&this->pIWICFormatConverter);
		if(FAILED(hr)) throw(Exception("Błąd metody CreateFormatConverter())"));

		hr = this->pIWICFormatConverter->Initialize(
			pIWICBitmapFrameDecode,          //Wejściowa bitmapa do konwersji
			GUID_WICPixelFormat32bppPBGRA,   //Pikselowy format przeznaczenia
			WICBitmapDitherTypeNone,         //Specyfikacja metody wygładzania
			NULL,                            //Specyfikacja palety
			0.f,                             //Przezroczystaść
			WICBitmapPaletteTypeCustom       //Typ przeksztaucenia palety
		);
		if(FAILED(hr)) throw(Exception("Błąd metody Initialize())"));

		if(!_bAutosize)
		//Jeśli brak dostosowywania widoku obrazu do wielkości okna. Czyli obraz nie będzie skalowany do wymiarów okna.
		{
			unsigned int uiWidth, uiHeight;
			//Odczytaj prawdziwą wymiary obrazu
			this->pIWICFormatConverter->GetSize(&uiWidth, &uiHeight);
			//Ustaw wymiary komponentu klasy, na wymiary obrazu, by móc umieścic objekt, klasy
			//w klasie, objektu TScrollBox, w celu skalowania obrazu
			this->Width = uiWidth; this->Height = uiHeight;
			#if defined(_DEBUGINFO_)
				GsDebugClass::WriteDebug(Format("%ux%u", ARRAYOFCONST((uiWidth, uiHeight))));
			#endif
		}

		hr = this->CreateDeviceResources(this->Handle);
		if(SUCCEEDED(hr))
		{
			SafeRelease(&this->pID2D1Bitmap);
			//Tworzy ID2D1Bitmap, kopiując określoną mapę bitową Microsoft Windows Imaging Component (WIC).
			hr = this->pID2D1HwndRenderTarget->CreateBitmapFromWicBitmap(this->pIWICFormatConverter, NULL, &this->pID2D1Bitmap);
			if(FAILED(hr)) throw(Exception("Błąd metody CreateBitmapFromWicBitmap())"));
			this->FIsLoadedImage = true; //Obrazek został załadowany
		}
		else
		{
			throw(Exception("Błąd metody CreateDeviceResources())"));
		}
	}
	__finally
	{
    #if defined(_DEBUGINFO_)
			GsDebugClass::WriteDebug("__finally");
		#endif
		SafeRelease(&pIWICBitmapDecoder);
		SafeRelease(&pIWICBitmapFrameDecode);
		//InvalidateRect(this->Handle, NULL, true);
	}
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::GsD2D_SavePicture(const UnicodeString custrPathSaveImage)
/**
	OPIS METOD(FUNKCJI): Zapianie obrazka o wymiarach wyswietlanych, nie realnych
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!this->pIWICImagingFactory) return;// || !this->pIWICFormatConverter) return;
  #if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug("GsDirect2DClass::GsD2D_SavePicture()");
	#endif
	//---
	HRESULT hr=S_OK;
	IWICBitmap *tpIWICBitmap=NULL;
	//HDC pHDWindowDC = GetDC(this->Handle);
	//Uchwyt kontekstu urządzenia źródłowego.
	HDC pHDWindowDC = GetWindowDC(this->Handle);
	if(!pHDWindowDC) throw(Exception("Błąd metody GetWindowDC())"));
  //Uchwyt kontekstu urządzenia docelowego.
	HDC pHDCompatibleDC = CreateCompatibleDC(pHDWindowDC);
	if(!pHDCompatibleDC) throw(Exception("Błąd metody CreateCompatibleDC())"));

	HBITMAP pHBmp = CreateCompatibleBitmap(pHDWindowDC, this->Width, this->Height);
	if(!pHBmp) throw(Exception("Błąd metody CreateCompatibleBitmap())"));
	//Wybierz (połącz) kompatybilną mapę bitową do kompatybilnej pamięci DC.
	HGDIOBJ pHGDIOBJ = SelectObject(pHDCompatibleDC, pHBmp);
	if(!pHGDIOBJ) throw(Exception("Błąd metody SelectObject())"));
	//Przesyłanie bloku bitów do naszej kompatybilnej pamięci DC.
	bool bRet = BitBlt(pHDCompatibleDC, //Uchwyt kontekstu urządzenia docelowego.
				 0, 0,
				 this->Width, this->Height,
				 pHDWindowDC,                 //Uchwyt kontekstu urządzenia źródłowego.
				 0, 0,
				 SRCCOPY);
	if(!bRet) throw(Exception("Błąd metody BitBlt())"));

	hr = this->pIWICImagingFactory->CreateBitmapFromHBITMAP(pHBmp, NULL, WICBitmapUseAlpha, &tpIWICBitmap);
	if(FAILED(hr)) throw(Exception("Błąd metody CreateBitmapFromHBITMAP())"));

	DeleteObject(pHBmp);
	DeleteObject(pHDCompatibleDC);
	ReleaseDC(this->Handle, pHDWindowDC);
	//--
	this->_SaveIWICBitmapSource(tpIWICBitmap, custrPathSaveImage, this->Width, this->Height);

	SafeRelease(&tpIWICBitmap);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::GsD2D_SavePictureOriginal(const UnicodeString custrPathSaveImage)
/**
	OPIS METOD(FUNKCJI):Zapisanie obrazka w realnych wymiarach, nie wymiarach okna
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!this->pIWICImagingFactory || !this->pIWICFormatConverter) return;
	//---
	HRESULT hr=S_OK;
	unsigned int uiWidth, uiHeight;
	IWICBitmap *tpIWICBitmap=NULL;
	//ID2D1RenderTarget *tpID2D1RenderTarget=NULL; //Tymczasowo wyłączone

  //Odczytaj prawdziwą wymiary obrazu
	this->pIWICFormatConverter->GetSize(&uiWidth, &uiHeight);

	hr = this->pIWICImagingFactory->CreateBitmapFromSource(this->pIWICFormatConverter, WICBitmapCacheOnDemand, &tpIWICBitmap);
	if(FAILED(hr)) throw(Exception("Błąd metody CreateBitmapFromSource())"));

  //Objekt klasy IWICBitmap, staje się objektem bitmapy, dla objektu docelowego dla renderowania grafiki (tpID2D1RenderTarget)
	//hr = this->pID2D1Factory->CreateWicBitmapRenderTarget(tpIWICBitmap, D2D1::RenderTargetProperties(), &tpID2D1RenderTarget);
	//if(FAILED(hr)) throw(Exception("Błąd metody CreateWicBitmapRenderTarget())"));

	this->_SaveIWICBitmapSource(tpIWICBitmap, custrPathSaveImage, uiWidth, uiHeight);

	SafeRelease(&tpIWICBitmap);
	//SafeRelease(&tpID2D1RenderTarget);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_SaveIWICBitmapSource(IWICBitmapSource *pIWICBitmapSource, const UnicodeString custrPathSaveImage, unsigned int _uiWidth, unsigned int _uiHeight)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	HRESULT hr=S_OK;
	GUID GUIDFormat = GUID_ContainerFormatJpeg;
	WICPixelFormatGUID format = GUID_WICPixelFormat32bppRGB;//GUID_WICPixelFormat32bppBGR;//GUID_WICPixelFormatDontCare;//
	IWICStream *pIWICStream=NULL;
	IWICBitmapEncoder *pIWICBitmapEncoder=NULL;
	IWICBitmapFrameEncode *pIWICBitmapFrameEncode=NULL;

	UnicodeString ustrPathToSave;

	ustrPathToSave = LowerCase(custrPathSaveImage);
	//Określenie kodera zapisujacego grafike, na podstawie rozszerzenia pliku wynikowego
	if(TPath::GetExtension(ustrPathToSave) == ".png") GUIDFormat = GUID_ContainerFormatPng;
	if(TPath::GetExtension(ustrPathToSave) == ".jpg") GUIDFormat = GUID_ContainerFormatJpeg;
	if(TPath::GetExtension(ustrPathToSave) == ".jpeg") GUIDFormat = GUID_ContainerFormatJpeg;
	if(TPath::GetExtension(ustrPathToSave) == ".bmp") GUIDFormat = GUID_ContainerFormatBmp;
	if(TPath::GetExtension(ustrPathToSave) == ".tiff") GUIDFormat = GUID_ContainerFormatTiff;
	if(TPath::GetExtension(ustrPathToSave) == ".tif") GUIDFormat = GUID_ContainerFormatTiff;
	//if(TPath::GetExtension(ustrPathToSave) == ".gif") {GUIDFormat = GUID_ContainerFormatGif; format = GUID_WICPixelFormatDontCare;}

  //Część kodu zapisująca grafikę i tekst
	hr = this->pIWICImagingFactory->CreateStream(&pIWICStream);
	if(FAILED(hr)) throw(Exception("Błąd metody CreateStream())"));

  hr = pIWICStream->InitializeFromFilename(custrPathSaveImage.c_str(), GENERIC_WRITE);
	if(FAILED(hr)) throw(Exception("Błąd metody InitializeFromFilename())"));

	hr = this->pIWICImagingFactory->CreateEncoder(GUIDFormat, NULL, &pIWICBitmapEncoder);
	if(FAILED(hr)) throw(Exception("Błąd metody CreateEncoder())"));

  hr = pIWICBitmapEncoder->Initialize(pIWICStream, WICBitmapEncoderNoCache);
	if(FAILED(hr)) throw(Exception("Błąd metody Initialize())"));

  hr = pIWICBitmapEncoder->CreateNewFrame(&pIWICBitmapFrameEncode, NULL);
	if(FAILED(hr)) throw(Exception("Błąd metody CreateNewFrame())"));

  hr = pIWICBitmapFrameEncode->Initialize(NULL);
	if(FAILED(hr)) throw(Exception("Błąd metody Initialize())"));

	hr = pIWICBitmapFrameEncode->SetSize(_uiWidth, _uiHeight);
	if(FAILED(hr)) throw(Exception("Błąd metody SetSize())"));

	hr = pIWICBitmapFrameEncode->SetPixelFormat(&format);
	if(FAILED(hr)) throw(Exception("Błąd metody SetPixelFormat())"));

	hr = pIWICBitmapFrameEncode->WriteSource(pIWICBitmapSource , NULL);
	if(FAILED(hr)) throw(Exception("Błąd metody WriteSource())"));

	hr = pIWICBitmapFrameEncode->Commit();
	if(FAILED(hr)) throw(Exception("Błąd metody Commit())"));

	hr = pIWICBitmapEncoder->Commit();
	if(FAILED(hr)) throw(Exception("Błąd metody Commit())"));

	SafeRelease(&pIWICStream);
	SafeRelease(&pIWICBitmapEncoder);
	SafeRelease(&pIWICBitmapFrameEncode);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	HRESULT hr=S_OK;
	TCustomPanel::CreateWnd();
	//---Własny kod...
	//---Tworzeniee silnika WIC
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pIWICImagingFactory));
	if(FAILED(hr)) throw(Exception("Błąd funkcji CoCreateInstance())"));

	//Tworzenie silnika D2D
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->pID2D1Factory);
	if(FAILED(hr)) throw(Exception("Błąd funkcji D2D1CreateFactory())"));

	//Stwórz wspólny silnik DirectWrite.
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&this->pIDWriteFactory));
	if(FAILED(hr)) throw(Exception("Błąd funkcji DWriteCreateFactory())"));

	//Twórzcie format tekstowy przy użyciu Gabrioli o rozmiarze czcionki 72.
	//To ustawia domyślną czcionkę, wagę, rozciągliwość, styl i lokalizację.
	hr = this->pIDWriteFactory->CreateTextFormat(
		this->FNameFont.c_str(),     //Nazwa rodziny kroju pisma.
		NULL,                       //Kolekcja czcionek (NULL ustawia ją na korzystanie z systemowej kolekcji czcionek).
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		this->FSizeFont,
		L"en-us",
		&this->pIDWriteTextFormat
	);
	if(FAILED(hr)) throw(Exception("Błąd funkcji CreateTextFormat())"));

	hr = this->pIDWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	if(FAILED(hr)) throw(Exception("Błąd funkcji SetTextAlignment())"));

	hr = this->pIDWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	if(FAILED(hr)) throw(Exception("Błąd funkcji SetParagraphAlignment())"));
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::DestroyWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	//---Własny kod.
	TCustomPanel::DestroyWnd();
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::WMSize(TWMSize &Message)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  //HRESULT hr = S_OK;
	RECT rRect;
	int iWidth, iHeight;

	::GetClientRect(this->Handle, &rRect);
	iWidth = rRect.right - rRect.left;
	iHeight = rRect.bottom - rRect.top;

	D2D1_SIZE_U size = D2D1::SizeU(iWidth, iHeight);

	if(this->pID2D1HwndRenderTarget)
	{
		//Jeśli nie możemy zmienić rozmiaru, zwolnij urządzenie i odtworzymy je
		//Podczas kolejnego renderu.
		if(FAILED(this->pID2D1HwndRenderTarget->Resize(size)))
		{
			SafeRelease(&this->pID2D1HwndRenderTarget);
			SafeRelease(&this->pID2D1Bitmap);
			throw(Exception("Błąd funkcji Resize())"));
		}
	}

	#if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug("WMSize");
	#endif
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::WMPaint(TWMPaint &Message)
/**
	OPIS METOD(FUNKCJI):Renderowanie za pomocą D2D
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  HRESULT hr = S_OK;
	TPaintStruct Ps;
	RECT rRect;
	int iWidth, iHeight;

	::GetClientRect(this->Handle, &rRect);
	iWidth = rRect.right - rRect.left;
	iHeight = rRect.bottom - rRect.top;
	#if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug("WMPaint");
	#endif

  #if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug(Format("iWidth=%d, iHeight=%d", ARRAYOFCONST((iWidth, iHeight))));
	#endif
	//D2D1_RECT_F rectangle = D2D1::RectF(0.0f, 0.0f, iWidth, iHeight);
	D2D1_RECT_F rectangle = D2D1::RectF(static_cast<float>(rRect.left) / this->_dpiScaleX, static_cast<float>(rRect.top) / this->_dpiScaleY,
																			static_cast<float>(rRect.right) / this->_dpiScaleX, static_cast<float>(rRect.bottom) / this->_dpiScaleY);

	if(BeginPaint(this->Handle, &Ps))
	{
		//Utwórz cel renderowania, jeśli nie został jeszcze utworzony
		hr = this->CreateDeviceResources(this->Handle);

		if(SUCCEEDED(hr) && !(this->pID2D1HwndRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
		{
			this->pID2D1HwndRenderTarget->BeginDraw();
			this->pID2D1HwndRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

			//D2DBitmapy mogły zostać zwolnione z powodu utraty urządzenia.
			//Jeśli tak, odtwórz ją ze źródłowej bitmapy
			if (this->pIWICFormatConverter && !this->pID2D1Bitmap)
			{
				//Tworzy ID2D1Bitmap, kopiując określoną mapę bitową Microsoft Windows Imaging Component (WIC).
				hr = this->pID2D1HwndRenderTarget->CreateBitmapFromWicBitmap(this->pIWICFormatConverter, NULL, &this->pID2D1Bitmap);
				if(FAILED(hr)) throw(Exception("Błąd metody CreateBitmapFromWicBitmap())"));
			}
			//Rysowanie obrazu i skalowanie go do bieżących wymiarów okna
			if (this->pID2D1Bitmap)
			{
				//Rysuje określoną bitmapę po skalowaniu jej do rozmiaru określonego prostokąta.
				this->pID2D1HwndRenderTarget->DrawBitmap(this->pID2D1Bitmap, rectangle);
			}
			else
			{
        //Czyszczenie okna
				this->pID2D1HwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Gray));
      }

			if(this->FIsDisplayText)
			{
				if(this->FRotationText != 0.00f) this->pID2D1HwndRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(this->FRotationText, D2D1::Point2F(this->Width / 2, this->Height / 2)));
        //tworzenie objektu klasy IDWriteTextLayout
				SafeRelease(&this->pIDWriteTextLayout);
				hr = this->pIDWriteFactory->CreateTextLayout(this->FTextWrite.c_str(), this->FTextWrite.Length(), this->pIDWriteTextFormat,
					iWidth, iHeight, &this->pIDWriteTextLayout);
				if(FAILED(hr)) throw(Exception("Błąd metody CreateTextLayout())"));
				//Pobieranie realnego wymiaru tekstu
				DWRITE_TEXT_METRICS textMetrics;
				ZeroMemory(&textMetrics, sizeof(DWRITE_TEXT_METRICS));
				hr = this->pIDWriteTextLayout->GetMetrics(&textMetrics);
				if(FAILED(hr)) throw(Exception("Błąd metody GetMetrics())"));

				D2D1_RECT_F rectTextMetric = D2D1::RectF(textMetrics.left, textMetrics.top, textMetrics.left + textMetrics.width, textMetrics.top + textMetrics.height);
        //Podjęcie akcji rysowania tekstu zależnie od ustawień
				if(this->FIsGradientColorFont) //Cieniowanie tekstu
				{
					this->_CreateGradientBrushDrawText(rectangle, rectTextMetric);
				}
				else
				{
					this->pID2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(0, 0), pIDWriteTextLayout, this->pID2D1SolidColorBrush1);
        }
			}

			hr = this->pID2D1HwndRenderTarget->EndDraw();
			//W przypadku utraty urządzenia, odrzucić D2D render target i D2DBitmapę
			//Będą odtworzone w następnej procesie renderingu
			if (hr == D2DERR_RECREATE_TARGET)
			{
				SafeRelease(&this->pID2D1Bitmap);
				SafeRelease(&this->pID2D1HwndRenderTarget);
				//Wymuszenie odświerzania
				hr = InvalidateRect(this->Handle, NULL, false)? S_OK : E_FAIL;
			}
		}
		EndPaint(this->Handle, &Ps);
	}

  //return SUCCEEDED(hr) ? 0 : 1;
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::WMErasebackground(TWMEraseBkgnd &Message)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  #if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug("WMErasebackground");
	#endif
	Message.Result = 1;
}
//---------------------------------------------------------------------------
HRESULT __fastcall GsDirect2DClass::CreateDeviceResources(HWND hWnd)
/**
	OPIS METOD(FUNKCJI): Ta metoda tworzy zasoby powiązane z określonym
											 Urządzenie D2D. Wszystko jest tutaj scentralizowane, na wypadek gdyby zasoby
											 należy odtworzyć w przypadku utraty urządzenia D2D
											 (np. zmiana wyświetlania, zdalne sterowanie, usunięcie karty graficznej itp.).
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	HRESULT hr = S_OK;

	if (!this->pID2D1HwndRenderTarget)
	{
    RECT rc;
		hr = ::GetClientRect(hWnd, &rc) ? S_OK : E_FAIL;

		if(SUCCEEDED(hr))
		{
      #if defined(_DEBUGINFO_)
				GsDebugClass::WriteDebug("CreateDeviceResources");
			#endif
			//Stworzenie parametrów dla tworzenia i używania techniki D2D
			D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties = D2D1::RenderTargetProperties();

			//Ustawienie domyślnegj rozdzielczości DPI, dla wszystkich bezpośrednich odwzorowań
			renderTargetProperties.dpiX = DEFAULT_DPI;
			renderTargetProperties.dpiY = DEFAULT_DPI;

			//Stworzenie okienkowego celu przeksztauceń
			D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

			hr = this->pID2D1Factory->CreateHwndRenderTarget(renderTargetProperties, D2D1::HwndRenderTargetProperties(hWnd, size), &this->pID2D1HwndRenderTarget);
			if(FAILED(hr)) throw(Exception("Błąd funkcji CreateHwndRenderTarget())"));
			this->pID2D1HwndRenderTarget->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_DEFAULT); //Antyaliasing dla tekstu
			//Tworzenie koloru pędzla do napisania tekstu
			hr = this->pID2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(this->D2DColorText), &this->pID2D1SolidColorBrush1);
			if(FAILED(hr)) throw(Exception("Błąd funkcji CreateSolidColorBrush())"));

			//Tworzenie 2 koloru pędzla do napisania tekstu
			hr = this->pID2D1HwndRenderTarget->CreateSolidColorBrush(D2D1::ColorF(this->D2DColorText2), &this->pID2D1SolidColorBrush2);
			if(FAILED(hr)) throw(Exception("Błąd funkcji CreateSolidColorBrush())"));
		}
	}
	return hr;
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::Click()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
  #if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug("Click");
	#endif
	//Jeśli istnieje zewnętrzna metoda OnClick() to ją wywołaj
	if(this->FOnClick) this->FOnClick(this);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_CreateGradientBrushDrawText(const D2D1_RECT_F &rectangle, const D2D1_RECT_F &rectTextMetric)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!this->pID2D1HwndRenderTarget) return;
	//---
  HRESULT hr=S_OK;
	ID2D1GradientStopCollection *pGID2D1GradientStopCollection=NULL;
	ID2D1LinearGradientBrush *pID2D1LinearGradientBrush=NULL;

	//Utwórz tablicę stopni gradientu, aby wstawić stop gradientu
	//kolekcja, która będzie używana w pędzlu gradientowym.
	D2D1_GRADIENT_STOP TableGradientStops[2];
	TableGradientStops[0].color = D2D1::ColorF(this->FD2DColorText, 1);
	TableGradientStops[0].position = 0.0f;
	TableGradientStops[1].color = D2D1::ColorF(this->FD2DColorText2, 1);
	TableGradientStops[1].position = 1.0f;

	//Utwórz ID2D1GradientStopCollection z poprzedniej
	//zadeklarowana tablica struktur D2D1_GRADIENT_STOP.
	hr = this->pID2D1HwndRenderTarget->CreateGradientStopCollection(
		TableGradientStops,
    2,
    D2D1_GAMMA_2_2,
    D2D1_EXTEND_MODE_CLAMP,
		&pGID2D1GradientStopCollection
		);
	if(FAILED(hr)) throw(Exception("Błąd metody CreateGradientStopCollection())"));

	//Linia określająca kierunek gradientu zaczyna się od
	//lewy górny róg kwadratu i kończy się w prawym dolnym rogu.
	hr = this->pID2D1HwndRenderTarget->CreateLinearGradientBrush(
        D2D1::LinearGradientBrushProperties(
						D2D1::Point2F(rectTextMetric.left, rectTextMetric.top),
						D2D1::Point2F(rectTextMetric.right, rectTextMetric.bottom)),
				pGID2D1GradientStopCollection,
				&pID2D1LinearGradientBrush
				);
	if(FAILED(hr)) throw(Exception("Błąd metody CreateLinearGradientBrush())"));
	pID2D1LinearGradientBrush->SetOpacity(this->FOpacityBrush);

  this->pID2D1HwndRenderTarget->DrawTextLayout(D2D1::Point2F(0, 0), pIDWriteTextLayout, pID2D1LinearGradientBrush);

	SafeRelease(&pGID2D1GradientStopCollection);
	SafeRelease(&pID2D1LinearGradientBrush);
}
//---------------------------------------------------------------------------
//------Metody obsługujace zmienne parametry, przy ich zmianie (write)-------
void __fastcall GsDirect2DClass::_SetDisplayText(const bool _IsDisplayText)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->FIsDisplayText = _IsDisplayText;
	InvalidateRect(this->Handle, NULL, false);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_SetNameFont(const UnicodeString _NameFont)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->FNameFont = _NameFont;
	this->_ReCreateTextFont();
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_SetSizeFont(const float _SizeFont)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->FSizeFont = _SizeFont;
	this->_ReCreateTextFont();
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_SetTextWrite(const UnicodeString _TextWrite)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->FTextWrite = _TextWrite;
  InvalidateRect(this->Handle, NULL, false);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_SetD2DColorText(const D2D1::ColorF::Enum _ColorText)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->FD2DColorText = _ColorText;
	unsigned char b=GetRValue(this->FD2DColorText), g=GetGValue(this->FD2DColorText), r=GetBValue(this->FD2DColorText);
	this->FStandardColorText = static_cast<TColor>(RGB(b, g, r));
	this->pID2D1SolidColorBrush1->SetColor(D2D1::ColorF(this->FD2DColorText));
	InvalidateRect(this->Handle, NULL, false);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_SetD2DColorText2(const D2D1::ColorF::Enum _ColorText)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->FD2DColorText2 = _ColorText;
	unsigned char b=GetRValue(this->FD2DColorText2), g=GetGValue(this->FD2DColorText2), r=GetBValue(this->FD2DColorText2);
	this->FStandardColorText2 = static_cast<TColor>(RGB(b, g, r));
	this->pID2D1SolidColorBrush2->SetColor(D2D1::ColorF(this->FD2DColorText2));
	InvalidateRect(this->Handle, NULL, false);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_ReCreateTextFont()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(!this->pIDWriteTextFormat) return;

  HRESULT hr = S_OK;
	SafeRelease(&this->pIDWriteTextFormat);
	//Twórzcie format tekstowy przy użyciu Gabrioli o rozmiarze czcionki 72.
	//To ustawia domyślną czcionkę, wagę, rozciągliwość, styl i lokalizację.
	hr = this->pIDWriteFactory->CreateTextFormat(
		this->FNameFont.c_str(),     //Nazwa rodziny kroju pisma.
		NULL,                        //Kolekcja czcionek (NULL ustawia ją na korzystanie z systemowej kolekcji czcionek).
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		this->FSizeFont,
		L"en-us",
		&this->pIDWriteTextFormat
	);
	if(FAILED(hr)) throw(Exception("Błąd funkcji CreateTextFormat())"));

	hr = this->pIDWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	if(FAILED(hr)) throw(Exception("Błąd funkcji SetTextAlignment())"));

	hr = this->pIDWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	if(FAILED(hr)) throw(Exception("Błąd funkcji SetParagraphAlignment())"));

	InvalidateRect(this->Handle, NULL, false);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_SetRotationText(const float _fRotationAngle)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->FRotationText = _fRotationAngle;
	InvalidateRect(this->Handle, NULL, false);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_SetOpacityBrush(const float _fOpacityBrush)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->FOpacityBrush = _fOpacityBrush;
	this->pID2D1SolidColorBrush1->SetOpacity(this->FOpacityBrush);
	this->pID2D1SolidColorBrush2->SetOpacity(this->FOpacityBrush);

  InvalidateRect(this->Handle, NULL, false);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_SetStandardColorText(const TColor _TColorText)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->FStandardColorText = _TColorText;
	unsigned char r=GetRValue(this->FStandardColorText), g=GetGValue(this->FStandardColorText), b=GetBValue(this->FStandardColorText);
	this->FD2DColorText = static_cast<D2D1::ColorF::Enum>(RGB(b, g, r));
	this->pID2D1SolidColorBrush1->SetColor(D2D1::ColorF(this->FD2DColorText));

	InvalidateRect(this->Handle, NULL, false);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_SetStandardColorText2(const TColor _TColorText)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->FStandardColorText2 = _TColorText;
	unsigned char r=GetRValue(this->FStandardColorText2), g=GetGValue(this->FStandardColorText2), b=GetBValue(this->FStandardColorText2);
	this->FD2DColorText2 = static_cast<D2D1::ColorF::Enum>(RGB(b, g, r));
	this->pID2D1SolidColorBrush2->SetColor(D2D1::ColorF(this->FD2DColorText2));

	InvalidateRect(this->Handle, NULL, false);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_SetGradientText(const bool _IsDoubleColorFont)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->FIsGradientColorFont = _IsDoubleColorFont;

	InvalidateRect(this->Handle, NULL, false);
}
//=========================Funkcje swobodne==================================
bool __fastcall D2D_CreateFontsList(THashedStringList *_pHSListFont)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	IDWriteFactory *pWriteFactory=NULL;
	//---
  bool bResult=true;
	HRESULT hr = S_OK;
	unsigned int familyCount=0;
	IDWriteFontCollection* pFontCollection=NULL;

	//Stwórz wspólny silnik DirectWrite.
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&pWriteFactory));
	if(FAILED(hr)) throw(Exception("Błąd funkcji DWriteCreateFactory())"));

	hr = pWriteFactory->GetSystemFontCollection(&pFontCollection);
	if(FAILED(hr)) throw(Exception("Błąd funkcji GetSystemFontCollection())"));
	//Uzyskaj liczbę rodzin czcionek w kolekcji.
	familyCount = pFontCollection->GetFontFamilyCount();

  _pHSListFont->BeginUpdate();
	_pHSListFont->Clear();
	//Pobierz systemową kolekcję czcionek.

	for (unsigned int i=0; i<familyCount; i++)
	{
		IDWriteFontFamily* pFontFamily=NULL;
		IDWriteLocalizedStrings* pFamilyNames=NULL;
		wchar_t* name=0;
		try
		{
			try
			{
				//Pobierz rodzinę czcionek.
				hr = pFontCollection->GetFontFamily(i, &pFontFamily);
				if(FAILED(hr)) throw(Exception("Błąd funkcji GetFontFamily())"));

				//Pobierz listę zlokalizowanych ciągów dla nazwiska.
				hr = pFontFamily->GetFamilyNames(&pFamilyNames);
				if(FAILED(hr)) throw(Exception("Błąd funkcji GetFamilyNames())"));

				unsigned int index=0;
				BOOL exists=false;
				wchar_t localeName[LOCALE_NAME_MAX_LENGTH];
				//Pobierz domyślne ustawienia regionalne dla tego użytkownika.
				int defaultLocaleSuccess = GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH);
				//Jeśli zwracane jest domyślne ustawienie regionalne, znajdź jego nazwę, w przeciwnym razie użyj „en-us”.
				if (defaultLocaleSuccess)
				{
					hr = pFamilyNames->FindLocaleName(localeName, &index, &exists);
				}
				if(SUCCEEDED(hr) && !exists) //Jeśli powyższe wyniki nie znalazły dopasowania, spróbuj ponownie z językiem angielskim (USA)
				{
					hr = pFamilyNames->FindLocaleName(L"en-us", &index, &exists);
					if(FAILED(hr)) throw(Exception("Błąd funkcji FindLocaleName())"));
				}
				if(!exists) index = 0; //Jeśli określone ustawienie regionalne nie istnieje, wybierz pierwsze z listy.
				//---
				unsigned int length=0;
				//Pobierz długość łańcucha.
				hr = pFamilyNames->GetStringLength(index, &length);
				if(FAILED(hr)) throw(Exception("Błąd funkcji GetStringLength())"));
				//Przydziel ciąg wystarczająco duży, aby pomieścić nazwę.
				name = new wchar_t[length+1];
				if(!name) throw(Exception("Błąd allokacji pamięci na nazwę czcionki"));
			//Wydobądź nazwe.
				hr = pFamilyNames->GetString(index, name, length+1);
				if(FAILED(hr)) throw(Exception("Błąd funkcji GetString())"));

				_pHSListFont->Add(name);
			}
			catch(const Exception& e)
			{
				MessageBox(NULL, e.Message.c_str() , TEXT("Informacje aplikacji"), MB_OK | MB_ICONINFORMATION | MB_TASKMODAL);
				bResult = false;
			}
		}
		__finally
		{
			SafeRelease(&pFontFamily);
			SafeRelease(&pFamilyNames);
			delete [] name;
		}
	}

	SafeRelease(&pFontCollection);
	_pHSListFont->EndUpdate();
	SafeRelease(&pWriteFactory);
	//---
	return bResult;
}
