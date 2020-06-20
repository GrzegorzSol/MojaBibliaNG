#include "GsDirect2DLiteClass.h"
//#include <System.IOUtils.hpp>

/*
	#if defined(__BORLANDC__) && defined(__clang__) && defined(_WIN32)
		//Your code.
	#endif
	#if defined(__BORLANDC__) && defined(__clang__)
    //Your code.
	#endif
#if defined(_DEBUGINFO_)
	GsDebugClass::WriteDebug(Format("", ARRAYOFCONST(( ))));
	GsDebugClass::WriteDebug("");
#endif
*/
#if defined(__BORLANDC__) && defined(_WIN64)
	#pragma link "D2d1.a"
#else
	#pragma link "D2d1.lib"
#endif

#pragma package(smart_init)

const FLOAT DEFAULT_DPI = 96.f;   // Default DPI that maps image resolution directly to screen resoltuion
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
__fastcall GsDirect2DLiteClass::GsDirect2DLiteClass(TComponent* Owner) : TCustomPanel(Owner)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	this->pID2D1Bitmap=NULL;
	this->pIWICFormatConverter=NULL;
	this->pIWICImagingFactory=NULL;
	this->pID2D1Factory=NULL;
	this->pID2D1HwndRenderTarget=NULL;
}
//---------------------------------------------------------------------------
__fastcall GsDirect2DLiteClass::~GsDirect2DLiteClass()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	SafeRelease(&this->pID2D1Bitmap);
	SafeRelease(&this->pIWICFormatConverter);
	SafeRelease(&this->pIWICImagingFactory);
	SafeRelease(&this->pID2D1Factory);
	SafeRelease(&this->pID2D1HwndRenderTarget);
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DLiteClass::GsD2DLite_LoadPicture(const UnicodeString custrPathImage, bool _bAutosize)
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	HRESULT hr;
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
		//Jeśli brak dostosowywania widoku obrazu do wielkości okna
		{
			unsigned int uiWidth, uiHeight;
			this->pIWICFormatConverter->GetSize(&uiWidth, &uiHeight);
			this->Width = uiWidth; this->Height = uiHeight;
			#if defined(_DEBUGINFO_)
				GsDebugClass::WriteDebug(Format("%ux%u", ARRAYOFCONST((uiWidth, uiHeight))));
			#endif
		}

		hr = this->CreateDeviceResources(this->Handle);
		if(SUCCEEDED(hr))
		{
			SafeRelease(&this->pID2D1Bitmap);
			hr = this->pID2D1HwndRenderTarget->CreateBitmapFromWicBitmap(this->pIWICFormatConverter, NULL, &this->pID2D1Bitmap);
			if(FAILED(hr)) throw(Exception("Błąd metody CreateBitmapFromWicBitmap())"));
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
	}
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DLiteClass::CreateWnd()
/**
	OPIS METOD(FUNKCJI):
	OPIS ARGUMENTÓW:
	OPIS ZMIENNYCH:
	OPIS WYNIKU METODY(FUNKCJI):
*/
{
	HRESULT hr=S_OK;
	TCustomPanel::CreateWnd();
	//---Własny kod
	//---Tworzeniee silnika WIC
	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pIWICImagingFactory));
	if(FAILED(hr)) throw(Exception("Błąd funkcji CoCreateInstance())"));

	//Tworzenie silnikaD2D
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->pID2D1Factory);
	if(FAILED(hr)) throw(Exception("Błąd funkcji D2D1CreateFactory())"));
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DLiteClass::DestroyWnd()
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
void __fastcall GsDirect2DLiteClass::WMSize(TWMSize &Message)
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
		//If we couldn't resize, release the device and we'll recreate it
		//during the next render pass.
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
void __fastcall GsDirect2DLiteClass::WMPaint(TWMPaint &Message)
/**
	OPIS METOD(FUNKCJI):
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

	D2D1_RECT_F rectangle = D2D1::RectF(0.0f, 0.0f, iWidth, iHeight);

	if(BeginPaint(this->Handle, &Ps))
	{
		// Create render target if not yet created
		hr = this->CreateDeviceResources(this->Handle);

		if(SUCCEEDED(hr) && !(this->pID2D1HwndRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
		{
			this->pID2D1HwndRenderTarget->BeginDraw();
			this->pID2D1HwndRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
			//Clear the background
			this->pID2D1HwndRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
			//D2D1_SIZE_F rtSize = this->pID2D1HwndRenderTarget->GetSize();
			//Create a rectangle same size of current window
			//D2D1_RECT_F rectangle = D2D1::RectF(0.0f, 0.0f, rtSize.width, rtSize.height);

			//D2DBitmap may have been released due to device loss.
			//If so, re-create it from the source bitmap
			if (this->pIWICFormatConverter && !this->pID2D1Bitmap)
			{
				hr = this->pID2D1HwndRenderTarget->CreateBitmapFromWicBitmap(this->pIWICFormatConverter, NULL, &this->pID2D1Bitmap);
				if(FAILED(hr)) throw(Exception("Błąd metody CreateBitmapFromWicBitmap())"));
			}
			//Draws an image and scales it to the current window size
			if (this->pID2D1Bitmap)
			{
				this->pID2D1HwndRenderTarget->DrawBitmap(this->pID2D1Bitmap, rectangle);
			}

			hr = this->pID2D1HwndRenderTarget->EndDraw();
			//In case of device loss, discard D2D render target and D2DBitmap
			//They will be re-create in the next rendering pass
			if (hr == D2DERR_RECREATE_TARGET)
			{
				SafeRelease(&this->pID2D1Bitmap);
				SafeRelease(&this->pID2D1HwndRenderTarget);
				//Force a re-render
				hr = InvalidateRect(this->Handle, NULL, TRUE)? S_OK : E_FAIL;
			}
		}		
		EndPaint(this->Handle, &Ps);
	}

  //return SUCCEEDED(hr) ? 0 : 1;
}
//---------------------------------------------------------------------------
HRESULT __fastcall GsDirect2DLiteClass::CreateDeviceResources(HWND hWnd)
/**
	OPIS METOD(FUNKCJI):
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

			hr = this->pID2D1Factory->CreateHwndRenderTarget(
				renderTargetProperties,
				D2D1::HwndRenderTargetProperties(hWnd, size),
				&this->pID2D1HwndRenderTarget
			);
		}
	}
  return hr;
}
//---------------------------------------------------------------------------
void __fastcall GsDirect2DLiteClass::Click()
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
