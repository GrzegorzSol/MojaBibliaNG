#include "GsDirect2DClass.h"
#include <Vcl.Graphics.hpp>
#include <System.IOUtils.hpp>
#include <d2d1_1.h>
//#include <d2d1_3.h>
#include <D2D1Effects_2.h>
/*
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug("");
#endif
MessageBox(NULL, TEXT("Aplikacja do uruchomienia wymaga systemu operacyjnego w wersji minimalnej 6.1 (Windows 7 sp1)"), TEXT("Błąd aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
*/
#if defined(__BORLANDC__) && defined(_WIN64)
	#pragma link "D2d1.a"
	#pragma link "dwrite.a"
#else
	#pragma link "D2d1.lib"
	#pragma link "dwrite.lib"
#endif

#pragma package(smart_init)

const float DEFAULT_DPI = 96.0f;	 // Domyślne DPI, które mapuje rozdzielczość obrazu bezpośrednio do rozdzielczości ekranu
//Funkcje pomocnicze
bool __fastcall D2D_CreateFontsList(THashedStringList *_pHSListFont);
//Nadanie wartości składnikom statycznym
const UnicodeString GsDirect2DClass::csVersion = "0.8.3875.8430";
bool GsDirect2DClass::IsInitListfonts = false; //Lista czcionek została wczytana, lub nie, w tej klasie
//---------------------------------------------------------------------------
template<class Interface>
inline void SafeRelease(Interface **ppInterfaceToRelease)
{
	if(*ppInterfaceToRelease != nullptr)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = nullptr;
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
	//Trzeba wszystkie wskaźniki zainicjować wartością nullptr!!!
	//Direct2D
	this->pID2D1Bitmap=nullptr;
	this->pIWICFormatConverter=nullptr;
	this->pIWICImagingFactory=nullptr;
	this->pID2D1Factory=nullptr;
	this->pID2D1HwndRenderTarget=nullptr;
	this->pID2D1DeviceContext=nullptr;
	this->pIWICBitmapScaler=nullptr;
	//DirectWrite
	this->pIDWriteFactory=nullptr;
	this->pIDWriteTextFormat=nullptr;
	this->pIDWriteTextLayout=nullptr;
	this->pID2D1SolidColorBrush1=nullptr;
	this->pID2D1SolidColorBrush2=nullptr;
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
	this->FIsApplyEfects = false;
	//Efekty
	this->FSetApplyEffect = EfGfx_NoEffect;

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
	SafeRelease(&this->pID2D1DeviceContext);
	SafeRelease(&this->pIWICBitmapScaler);
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
	IWICBitmapDecoder *pIWICBitmapDecoder=nullptr;
	IWICBitmapFrameDecode *pIWICBitmapFrameDecode=nullptr;

	try
	{
		try
		{
			hr = this->pIWICImagingFactory->CreateDecoderFromFilename(
				custrPathImage.c_str(),					 //Dekodowanie obrazu
				NULL,
				GENERIC_READ,										 //Prawo odczytu pliku
				WICDecodeMetadataCacheOnDemand,	 //Kesz metadanych, gdy trzeba
				&pIWICBitmapDecoder							 //Wskaźnik do dekodera
			);
			if(FAILED(hr)) throw(Exception("Błąd metody CreateDecoderFromFilename())"));

			//Pozyskanie pierwszej klatki obrazka dla dekodera
			hr = pIWICBitmapDecoder->GetFrame(0, &pIWICBitmapFrameDecode);
			if(FAILED(hr)) throw(Exception("Błąd metody GetFrame())"));

			SafeRelease(&this->pIWICFormatConverter);
			hr = this->pIWICImagingFactory->CreateFormatConverter(&this->pIWICFormatConverter);
			if(FAILED(hr)) throw(Exception("Błąd metody CreateFormatConverter())"));

			hr = this->pIWICFormatConverter->Initialize(
				pIWICBitmapFrameDecode,					 //Wejściowa bitmapa do konwersji
				GUID_WICPixelFormat32bppPBGRA,	 //Pikselowy format przeznaczenia
				WICBitmapDitherTypeNone,				 //Specyfikacja metody wygładzania
				NULL,														 //Specyfikacja palety
				0.f,														 //Przezroczystaść
				WICBitmapPaletteTypeCustom			 //Typ przeksztaucenia palety
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
		} //try catch
		catch(Exception &e)
		{
			MessageBox(NULL, e.Message.c_str(), TEXT("Informacje aplikacji"), MB_OK | MB_ICONERROR | MB_TASKMODAL);
		}
	} //try
	__finally
	{
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
	//---
	HRESULT hr=S_OK;
	IWICBitmap *tpIWICBitmap=nullptr;
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
				 pHDWindowDC,									//Uchwyt kontekstu urządzenia źródłowego.
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
	IWICBitmap *tpIWICBitmap=nullptr;
	//ID2D1RenderTarget *tpID2D1RenderTarget=nullptr; //Tymczasowo wyłączone

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
	IWICStream *pIWICStream=nullptr;
	IWICBitmapEncoder *pIWICBitmapEncoder=nullptr;
	IWICBitmapFrameEncode *pIWICBitmapFrameEncode=nullptr;

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
		this->FNameFont.c_str(),		 //Nazwa rodziny kroju pisma.
		NULL,												//Kolekcja czcionek (NULL ustawia ją na korzystanie z systemowej kolekcji czcionek).
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
	//RECT rRect;
	int iWidth, iHeight;

	//::GetClientRect(this->Handle, &rRect);

	//iWidth = rRect.right - rRect.left;
	//iHeight = rRect.bottom - rRect.top;
	iWidth = this->ClientWidth;
	iHeight = this->ClientHeight;

	#if defined(_DEBUGINFO_)
		GsDebugClass::WriteDebug(Format("iWidth: %d, iHeight: %d", ARRAYOFCONST((iWidth, iHeight))));
		GsDebugClass::WriteDebug(Format("ClientWidth: %d, ClientHeight: %d", ARRAYOFCONST((this->ClientWidth, this->ClientHeight))));
	#endif

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
	RECT rRect;

	::GetClientRect(this->Handle, &rRect);

	D2D1_RECT_F rectangle = D2D1::RectF(static_cast<float>(rRect.left) / this->_dpiScaleX, static_cast<float>(rRect.top) / this->_dpiScaleY,
																			static_cast<float>(rRect.right) / this->_dpiScaleX, static_cast<float>(rRect.bottom) / this->_dpiScaleY);

	hr = this->CreateDeviceResources(this->Handle);
	if(FAILED(hr)) return; //Wyjście jeśli metoda CreateDeviceResources zwróciła nie powodzenie.
												 //Błąd tworzenia objektu, klasy ID2D1HwndRenderTarget, lub ID2D1SolidColorBrush
	//---
	if(!this->FIsApplyEfects)
	{
		//Bez efektów
		this->_PaintNoEfects(rRect, rectangle);
	}
	else
	{
		this->_PaintApplyEfects(rRect, rectangle);
	}
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_PaintNoEfects(const RECT &rRect, const D2D1_RECT_F &rectangle)
/**
	OPIS METOD(FUNKCJI):Malowanie bez żadnych efektów
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	HRESULT hr = S_OK;
	PAINTSTRUCT Ps;
	int iWidth = rRect.right - rRect.left;
	int iHeight = rRect.bottom - rRect.top;

	if(BeginPaint(this->Handle, &Ps))
	{
		if(!(this->pID2D1HwndRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
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
		} //(this->pID2D1HwndRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
		EndPaint(this->Handle, &Ps);
	} //if(BeginPaint(this->Handle, &Ps))
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_PaintApplyEfects(const RECT &rRect, const D2D1_RECT_F &rectangle)
/**
	OPIS METOD(FUNKCJI): Malowaniez wybranymi efektami efektów
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	HRESULT hr = S_OK;
	PAINTSTRUCT Ps;
	int iWidth = rRect.right - rRect.left;
	int iHeight = rRect.bottom - rRect.top;
	ID2D1Image *pID2D1Image=nullptr;
	ID2D1Effect *pID2D1Effect=nullptr;

	//Skalowanie grafiki
	this->_ScaleBitmapSource(iWidth, iHeight);

	if(BeginPaint(this->Handle, &Ps))
	{
		if(!(this->pID2D1HwndRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
		{
			//D2DBitmapy mogły zostać zwolnione z powodu utraty urządzenia.
			//Jeśli tak, odtwórz ją ze źródłowej bitmapy

			this->pID2D1HwndRenderTarget->BeginDraw();
			this->pID2D1HwndRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

			//Rysowanie obrazu i skalowanie go do bieżących wymiarów okna
			if (this->pID2D1Bitmap)
			{
				pID2D1Effect = this->_ApplyEffect(pID2D1Image);
				//Czy metoda zwróciła niepusty wskaźnik (sprawdzanie sytemu Windows, dla efektów)
				if(pID2D1Effect) this->pID2D1DeviceContext->DrawImage(pID2D1Effect);
			}
			else
			{
				//Czyszczenie okna
				this->pID2D1HwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Gray));
			}

			if(this->FIsDisplayText)
			{
				if(this->FRotationText != 0.00f) this->pID2D1HwndRenderTarget->SetTransform(D2D1::Matrix3x2F::Rotation(this->FRotationText, D2D1::Point2F(this->ClientWidth / 2, this->ClientHeight / 2)));
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
		}//(this->pID2D1HwndRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
		EndPaint(this->Handle, &Ps);
	} //if(BeginPaint(this->Handle, &Ps))

	SafeRelease(&pID2D1Effect);
	SafeRelease(&pID2D1Image);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_ScaleBitmapSource(const int _iWidth, const int _iHeight)
/**
	OPIS METOD(FUNKCJI): Scalowanie objektu typu IWICBitmapSource, na objekt typu ID2D1Bitmap
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	HRESULT hr = S_OK;

	//Skalowanie grafiki
	SafeRelease(&this->pID2D1Bitmap);
	SafeRelease(&this->pIWICBitmapScaler);
	if(this->pIWICFormatConverter)// && !this->pID2D1Bitmap)
	{
		//Przeskalowanie grafiki, do wymiarów okna, gdyż objektu klasy ID2D1Image, nie da się skalować na okno
		this->pIWICImagingFactory->CreateBitmapScaler(&this->pIWICBitmapScaler);
		if(FAILED(hr)) throw(Exception("Błąd funkcji CreateBitmapScaler())"));
		//Skalowanie obrazka po konwersji
		hr = this->pIWICBitmapScaler->Initialize(this->pIWICFormatConverter, _iWidth, _iHeight, WICBitmapInterpolationModeFant);
		if(FAILED(hr)) throw(Exception("Błąd metody Initialize())"));

		hr = this->pID2D1HwndRenderTarget->CreateBitmapFromWicBitmap(this->pIWICBitmapScaler, NULL, &this->pID2D1Bitmap);
		if(FAILED(hr)) throw(Exception("Błąd metody CreateBitmapFromWicBitmap())"));
	} //if(this->pIWICFormatConverter)
}
//---------------------------------------------------------------------------
ID2D1Effect* __fastcall GsDirect2DClass::_ApplyEffect(ID2D1Image *Image, ID2D1Bitmap *pBitmap2)
/**
	OPIS METOD(FUNKCJI): Tworzenie efektów
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	HRESULT hr = S_OK;
	ID2D1Effect *pEffect=nullptr;
	CLSID effectId;

	switch(this->FSetApplyEffect)
	{
		case EfGfx_GaussianBlur: effectId = CLSID_D2D1GaussianBlur; break;
		case EfGfx_HueRotation: effectId = CLSID_D2D1HueRotation; break;
		case EfGfx_DirectionalBlur: effectId = CLSID_D2D1DirectionalBlur; break;
		case EfGfx_ConvolveMatrix: effectId = CLSID_D2D1ConvolveMatrix; break;
		case EfGfx_Morphology: effectId = CLSID_D2D1Morphology; break;
		case EfGfx_DiscreteTransfer: effectId = CLSID_D2D1DiscreteTransfer; break;
		case EfGfx_GammaTransfer: effectId = CLSID_D2D1GammaTransfer; break;
		case EfGfx_LuminanceToAlpha: effectId = CLSID_D2D1LuminanceToAlpha; break;
		case EfGfx_3DPerspectiveTransform: effectId = CLSID_D2D13DPerspectiveTransform; break;
		case EfGfx_BitmapSource: effectId = CLSID_D2D1BitmapSource; break;
		case EfGfx_Brightness: effectId = CLSID_D2D1Brightness; break;
		//EFEKTY KTÓRE DZIAŁAJA TYLKO W WERSJI SYTEMU MINIMUM WINDOWS 10
		case EfGfx_EdgeDetection: effectId = CLSID_D2D1EdgeDetection; break;
		case EfGfx_Emboss: effectId = CLSID_D2D1Emboss; break;
		case EfGfx_Posterize: effectId = CLSID_D2D1Posterize; break;
		case EfGfx_Vignette: effectId = CLSID_D2D1Vignette; break;
		case EfGfx_Grayscale: effectId = CLSID_D2D1Grayscale; break;
		case EfGfx_HighlightsShadows: effectId = CLSID_D2D1HighlightsShadows; break;
		case EfGfx_Invert: effectId = CLSID_D2D1Invert; break;
		case EfGfx_Sepia: effectId = CLSID_D2D1Sepia; break;
		case EfGfx_Sharpen: effectId = CLSID_D2D1Sharpen; break;

		default: effectId = CLSID_D2D1GaussianBlur;
	}

	hr = this->pID2D1DeviceContext->CreateEffect(effectId, &pEffect);
	if(!SUCCEEDED(hr)) throw(Exception("Błąd metody CreateEffect()"));

	pEffect->SetInput(0, this->pID2D1Bitmap);
	switch(this->FSetApplyEffect)
	{
		case EfGfx_NoEffect: SafeRelease(&pEffect); pEffect = nullptr; return 0;
		case EfGfx_GaussianBlur: break;
		case EfGfx_HueRotation: pEffect->SetValue(D2D1_HUEROTATION_PROP_ANGLE, 90.0f); break;
		case EfGfx_DirectionalBlur: pEffect->SetValue(D2D1_DIRECTIONALBLUR_PROP_STANDARD_DEVIATION, 7.0f); break;
		case EfGfx_ConvolveMatrix:
		{
			float matrix[9] = {-1, -1, -1, -1, 9, -1, -1, -1, -1};
			pEffect->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_MATRIX, matrix);
		}
		break;
		//---
		case EfGfx_Morphology:
		{
			pEffect->SetValue(D2D1_MORPHOLOGY_PROP_MODE, D2D1_MORPHOLOGY_MODE_ERODE);
			pEffect->SetValue(D2D1_MORPHOLOGY_PROP_WIDTH, 14);
		}
		break;
		//---
		case EfGfx_DiscreteTransfer:
		{
			float table[3] = {0.0f, 0.5f, 1.0f};
			pEffect->SetValue(D2D1_DISCRETETRANSFER_PROP_RED_TABLE, table);
			pEffect->SetValue(D2D1_DISCRETETRANSFER_PROP_GREEN_TABLE, table);
			pEffect->SetValue(D2D1_DISCRETETRANSFER_PROP_BLUE_TABLE, table);
		}
		break;
		//---
		case EfGfx_GammaTransfer:
		{
			pEffect->SetValue(D2D1_GAMMATRANSFER_PROP_RED_EXPONENT, 0.25f);
			pEffect->SetValue(D2D1_GAMMATRANSFER_PROP_GREEN_EXPONENT, 0.25f);
			pEffect->SetValue(D2D1_GAMMATRANSFER_PROP_BLUE_EXPONENT, 0.25f);
		}
		break;
		//---
		case EfGfx_LuminanceToAlpha:
		{
			//Wynik LuminanceToAlpha jest nakładany na białą powierzchnię, aby pokazać krycie.
			ID2D1Effect *floodEffect=nullptr;
			this->pID2D1DeviceContext->CreateEffect(CLSID_D2D1Flood, &floodEffect);
			if(!SUCCEEDED(hr)) throw(Exception("Błąd metody CreateEffect()"));

			floodEffect->SetValue(D2D1_FLOOD_PROP_COLOR, D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f));
			ID2D1Effect *compositeEffect=nullptr;
			this->pID2D1DeviceContext->CreateEffect(CLSID_D2D1Composite, &compositeEffect);
			if(!SUCCEEDED(hr)) throw(Exception("Błąd metody CreateEffect()"));

			compositeEffect->SetInputEffect(0, floodEffect);
			compositeEffect->SetInputEffect(1, pEffect);

			SafeRelease(&floodEffect);
			SafeRelease(&pEffect);
			return compositeEffect;
		}
		break;
		//---
		case EfGfx_3DPerspectiveTransform:
		{
			pEffect->SetValue(D2D1_3DPERSPECTIVETRANSFORM_PROP_PERSPECTIVE_ORIGIN, D2D1::Vector3F(0.0f, 192.0f, 0.0f));
			pEffect->SetValue(D2D1_3DPERSPECTIVETRANSFORM_PROP_ROTATION, D2D1::Vector3F(0.0f, 30.0f, 0.0f));
			//pEffect->SetValue(D2D1_3DPERSPECTIVETRANSFORM_PROP_DEPTH, 1000.0f);
			this->pID2D1HwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
		}
		break;
		//---
		case EfGfx_BitmapSource:
		{
			pEffect->SetValue(D2D1_BITMAPSOURCE_PROP_WIC_BITMAP_SOURCE, this->pIWICBitmapScaler);
			pEffect->SetValue(D2D1_BITMAPSOURCE_PROP_ORIENTATION, D2D1_BITMAPSOURCE_ORIENTATION_FLIP_HORIZONTAL);
		}
		break;
		//---
		case EfGfx_Brightness: pEffect->SetValue(D2D1_BRIGHTNESS_PROP_BLACK_POINT, D2D1::Vector2F(0.0f, 0.2f)); break;
		//EFEKTY KTÓRE DZIAŁAJA TYLKO W WERSJI SYTEMU MINIMUM WINDOWS 10
		case EfGfx_EdgeDetection:
		{
			pEffect->SetValue(D2D1_EDGEDETECTION_PROP_STRENGTH, 0.5f);
			pEffect->SetValue(D2D1_EDGEDETECTION_PROP_BLUR_RADIUS, 0.0f);
			pEffect->SetValue(D2D1_EDGEDETECTION_PROP_MODE, D2D1_EDGEDETECTION_MODE_SOBEL);
			pEffect->SetValue(D2D1_EDGEDETECTION_PROP_OVERLAY_EDGES, false);
			pEffect->SetValue(D2D1_EDGEDETECTION_PROP_ALPHA_MODE, D2D1_ALPHA_MODE_PREMULTIPLIED);
		}
		break;
		//---
		case EfGfx_Emboss:
		{
			pEffect->SetValue(D2D1_EMBOSS_PROP_HEIGHT, 9.0f);
			pEffect->SetValue(D2D1_EMBOSS_PROP_DIRECTION, 90.0f);
		}
		break;
		//---
		case EfGfx_Posterize:
		{
			pEffect->SetValue(D2D1_POSTERIZE_PROP_RED_VALUE_COUNT, 4);
			pEffect->SetValue(D2D1_POSTERIZE_PROP_GREEN_VALUE_COUNT, 4);
			pEffect->SetValue(D2D1_POSTERIZE_PROP_BLUE_VALUE_COUNT, 4);
		}
		break;
		//---
		case EfGfx_Vignette:
		{
			//pEffect->SetValue(D2D1_VIGNETTE_PROP_COLOR, );
			pEffect->SetValue(D2D1_VIGNETTE_PROP_TRANSITION_SIZE, 0.2f);
			pEffect->SetValue(D2D1_VIGNETTE_PROP_STRENGTH, 0.5f);
		}
		break;
		//---
		case EfGfx_Grayscale: break;
		//---
		case EfGfx_HighlightsShadows:
		{
			pEffect->SetValue(D2D1_HIGHLIGHTSANDSHADOWS_PROP_HIGHLIGHTS, 0.0f);
			pEffect->SetValue(D2D1_HIGHLIGHTSANDSHADOWS_PROP_SHADOWS, 0.5f);
			pEffect->SetValue(D2D1_HIGHLIGHTSANDSHADOWS_PROP_CLARITY, 0.2f);
			pEffect->SetValue(D2D1_HIGHLIGHTSANDSHADOWS_PROP_INPUT_GAMMA, D2D1_HIGHLIGHTSANDSHADOWS_INPUT_GAMMA_LINEAR);
			pEffect->SetValue(D2D1_HIGHLIGHTSANDSHADOWS_PROP_MASK_BLUR_RADIUS, 1.0f);
		}
		break;
		//---
		case EfGfx_Invert: break;
		//---
		case EfGfx_Sepia:
		{
			pEffect->SetValue(D2D1_SEPIA_PROP_INTENSITY, 0.75f);
			pEffect->SetValue(D2D1_SEPIA_PROP_ALPHA_MODE, D2D1_ALPHA_MODE_PREMULTIPLIED);
		}
		break;
		//---
		case EfGfx_Sharpen:
		{
			pEffect->SetValue(D2D1_SHARPEN_PROP_SHARPNESS, 1.0f);
			pEffect->SetValue(D2D1_SHARPEN_PROP_THRESHOLD, 0.5f);
		}
		break;
	}
	pEffect->GetOutput(&Image);

	return pEffect;
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
			//Stworzenie parametrów dla tworzenia i używania techniki D2D
			D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties = D2D1::RenderTargetProperties();

			//Ustawienie domyślnegj rozdzielczości DPI, dla wszystkich bezpośrednich odwzorowań
			renderTargetProperties.dpiX = DEFAULT_DPI;
			renderTargetProperties.dpiY = DEFAULT_DPI;

			//Stworzenie okienkowego celu przeksztauceń
			D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

			hr = this->pID2D1Factory->CreateHwndRenderTarget(renderTargetProperties, D2D1::HwndRenderTargetProperties(hWnd, size), &this->pID2D1HwndRenderTarget);
			if(FAILED(hr)) throw(Exception("Błąd funkcji CreateHwndRenderTarget())"));

			if (!this->pID2D1DeviceContext)
			{
				this->pID2D1HwndRenderTarget->QueryInterface(__uuidof(ID2D1DeviceContext), reinterpret_cast<void**>(&this->pID2D1DeviceContext));
				if(FAILED(hr)) throw(Exception("Błąd funkcji QueryInterface())"));
			}

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
	ID2D1GradientStopCollection *pGID2D1GradientStopCollection=nullptr;
	ID2D1LinearGradientBrush *pID2D1LinearGradientBrush=nullptr;

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
		this->FNameFont.c_str(),		 //Nazwa rodziny kroju pisma.
		NULL,												 //Kolekcja czcionek (NULL ustawia ją na korzystanie z systemowej kolekcji czcionek).
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
//---------------------------------------------------------------------------
void __fastcall GsDirect2DClass::_SetApplyEfects(const EnEffectsGfx _FSetApplyEffect)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	if(_FSetApplyEffect == EfGfx_NoEffect)
	{
		this->FIsApplyEfects = false;
	}
	else
	{
		this->FIsApplyEfects = true; //By wywołać this->_PaintApplyEfects, podczas odświerzania
	}
	this->FSetApplyEffect = _FSetApplyEffect;

	InvalidateRect(this->Handle, NULL, false);
}
//---------------------------------------------------------------------------
//=========================Funkcje swobodne==================================
bool __fastcall D2D_CreateFontsList(THashedStringList *_pHSListFont)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	IDWriteFactory *pWriteFactory=nullptr;
	//---
	bool bResult=true;
	HRESULT hr = S_OK;
	unsigned int familyCount=0;
	IDWriteFontCollection* pFontCollection=nullptr;

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
		IDWriteFontFamily* pFontFamily=nullptr;
		IDWriteLocalizedStrings* pFamilyNames=nullptr;
		wchar_t* name=nullptr;
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
			delete [] name; name = nullptr;
		}
	}

	SafeRelease(&pFontCollection);
	_pHSListFont->EndUpdate();
	SafeRelease(&pWriteFactory);
	//---
	return bResult;
}
//---------------------------------------------------------------------------

