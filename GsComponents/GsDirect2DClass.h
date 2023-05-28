#ifndef GsDirect2DClassH
#define GsDirect2DClassH
//---------------------------------------------------------------------------
#include <Vcl.ExtCtrls.hpp>
#include <System.IniFiles.hpp>
#include <d2d1.h>
#include <d2d1_1.h>
#include <dwrite.h>

//#define _DEBUGINFO_  //Używanie okna konsoli do debugowania aplikacji
#if defined(_DEBUGINFO_)
	#include "GsDebugClass.h"
#endif
//Stałe efektów graficznych
enum EnEffectsGfx {
										//Efekty kompatybilne z Windows 7 i 8
										EfGfx_NoEffect=0x1000, EfGfx_GaussianBlur, EfGfx_HueRotation, EfGfx_DirectionalBlur, EfGfx_ConvolveMatrix,
										EfGfx_Morphology, EfGfx_DiscreteTransfer, EfGfx_GammaTransfer, EfGfx_LuminanceToAlpha, EfGfx_3DPerspectiveTransform,
										EfGfx_BitmapSource, EfGfx_Brightness,
										//Efekty kompatybilne z Windows 10 //Zlikwidować w wypadku obostrzenia na system min. Windows 10
										EfGfx_EdgeDetection, EfGfx_Emboss, EfGfx_Posterize, EfGfx_Vignette, EfGfx_Grayscale, EfGfx_HighlightsShadows,
										EfGfx_Invert, EfGfx_Sepia, EfGfx_Sharpen
									};
const UnicodeString ustrListNameEffects[] = { //Efekty działajace na Windows 7
																							"Bez efektu", "GaussianBlur", "HueRotation", "DirectionalBlur", "ConvolveMatrix",
																							"Morphology", "DiscreteTransfer", "GammaTransfer", "LuminanceToAlpha",
																							"3DPerspectiveTransform", "BitmapSource-Flip", "Brightness",
																							//Efekty działajace, tylko na minimum Windows 10 //Zlikwidować w wypadku obostrzenia na system min. Windows 10
																							"EdgeDetection", "Emboss", "Posterize", "Vignette",
																							"Grayscale", "HighlightsShadows", "Invert", "Sepia",
																							"Sharpen"
																						},
										//Zdefiniowane wielkości czcionek
                    ustrFontSize[] = {"10", "12", "16", "18", "20", "24", "28", "30", "36", "48", "64", "72", "98", "112", "124", "148"};
//Domyślne wartosci dla składowych klasy, które są stałe
const bool CFIsDisplayText = false;
const UnicodeString CFNameFont = "Arial",
										CFTextWrite = "Testowy tekst";
const float CFSizeFont = 72.0f,
						CFRotationText = 0.0f,
						CFOpacityBrush = 1.0f;
const D2D1::ColorF::Enum CFD2DColorText = D2D1::ColorF::Black, CFD2DColorText2 = D2D1::ColorF::White;
const TColor CFStandardColorText = clBlack, CFStandardColorText2 = clWhite;

bool __fastcall D2D_CreateFontsList(THashedStringList *_pHSListFont);
//---------------------------------------------------------------------------
class GsDirect2DClass : public TCustomPanel
{
	public:
		__fastcall GsDirect2DClass(TComponent* Owner);
		__fastcall virtual ~GsDirect2DClass();
		//---
		static bool IsInitListfonts; //Lista czcionek została wczytana, lub nie
		const static UnicodeString csVersion;
		//---
		void __fastcall GsD2D_LoadPicture(const UnicodeString custrPathImage, const bool _bAutosize=true);
		void __fastcall GsD2D_SavePicture(const UnicodeString custrPathSaveImage);
		void __fastcall GsD2D_SavePictureOriginal(const UnicodeString custrPathSaveImage);
		//---
		BEGIN_MESSAGE_MAP
			VCL_MESSAGE_HANDLER(WM_SIZE, TWMSize, WMSize);
			VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
			VCL_MESSAGE_HANDLER(WM_ERASEBKGND, TWMEraseBkgnd, WMErasebackground);
		END_MESSAGE_MAP(TCustomPanel);
		//---
		__property TNotifyEvent OnClick = {read=FOnClick, write=FOnClick};
		__property bool IsDisplayText = {read = FIsDisplayText, write = _SetDisplayText, default = false};
		__property UnicodeString NameFont = {read = FNameFont, write = _SetNameFont};
		__property float SizeFont = {read = FSizeFont, write = _SetSizeFont};
		__property UnicodeString TextWrite = {read = FTextWrite, write = _SetTextWrite};
		__property D2D1::ColorF::Enum D2DColorText = {read = FD2DColorText, write = _SetD2DColorText};
		__property D2D1::ColorF::Enum D2DColorText2 = {read = FD2DColorText2, write = _SetD2DColorText2};
		__property TColor StandartColorText = {read = FStandardColorText, write = _SetStandardColorText};
		__property TColor StandartColorText2 = {read = FStandardColorText2, write = _SetStandardColorText2};
		__property float RotationText = {read = FRotationText, write = _SetRotationText};
		__property float OpacityBrush = {read = FOpacityBrush, write = _SetOpacityBrush};
		__property bool IsModified = {read = FIsModified, write = FIsModified, default = false};
		__property bool IsGradientColorFont = {read = FIsGradientColorFont, write = _SetGradientText, default = false};
		__property bool IsLoadedImage = {read = FIsLoadedImage, default = false};
      //Efekty
		__property bool IsApplyEfects = {read = FIsApplyEfects, default = false};
		__property EnEffectsGfx SetApplyEffect = {read = FSetApplyEffect, write = _SetApplyEfects};

	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		void __fastcall WMSize(TWMSize &Message);
		void __fastcall WMPaint(TWMPaint &Message);
		void __fastcall WMErasebackground(TWMEraseBkgnd &Message);
		DYNAMIC void __fastcall Click();
		HRESULT __fastcall CreateDeviceResources(HWND hWnd);
		
	private:
		void __fastcall _ScaleBitmapSource(const int _iWidth, const int _iHeight); //Scalowanie objektu typu IWICBitmapSource, na objekt typu ID2D1Bitmap
		void __fastcall _PaintNoEfects(const RECT &rRect, const D2D1_RECT_F &rectangle); //Malowanie bez żadnych efektów
		void __fastcall _PaintApplyEfects(const RECT &rRect, const D2D1_RECT_F &rectangle); //Malowaniez wybranymi efektami efektów
		ID2D1Effect* __fastcall _ApplyEffect(ID2D1Image *Image, ID2D1Bitmap *pBitmap2=NULL); //Wywoływanie efektów
		//Metody obsługujace zmienne i parametry
			//Prywatne flagi
		bool FIsDisplayText, FIsModified, FIsGradientColorFont, FIsLoadedImage, FIsApplyEfects;
		EnEffectsGfx FSetApplyEffect;
		UnicodeString FNameFont;
		float FSizeFont,
					FRotationText,
					FOpacityBrush;
		UnicodeString FTextWrite;
		D2D1::ColorF::Enum FD2DColorText, FD2DColorText2;
		TColor FStandardColorText, FStandardColorText2;
			//Zachowanie całej klasy
		TNotifyEvent FOnClick;
			//Metody obsługujace parametry
		void __fastcall _SetDisplayText(const bool _IsDisplayText);
		void __fastcall _SetNameFont(const UnicodeString _NameFont);
		void __fastcall _SetSizeFont(const float _SizeFont);
		void __fastcall _SetTextWrite(const UnicodeString _TextWrite);
		void __fastcall _SetD2DColorText(const D2D1::ColorF::Enum _ColorText);
		void __fastcall _SetD2DColorText2(const D2D1::ColorF::Enum _ColorText);
		void __fastcall _SetStandardColorText(const TColor _TColorText);
    void __fastcall _SetStandardColorText2(const TColor _TColorText);
		void __fastcall _ReCreateTextFont();
		void __fastcall _SetRotationText(const float _fRotationAngle);
		void __fastcall _SetOpacityBrush(const float _fOpacityBrush);
		void __fastcall _SetGradientText(const bool _IsDoubleColorFont);
		//Metody efektów graficznych
		void __fastcall _SetApplyEfects(const EnEffectsGfx _FSetApplyEffect);
		//---
		void __fastcall _CreateGradientBrushDrawText(const D2D1_RECT_F &rectangle, const D2D1_RECT_F &rectTextMetric);
		void __fastcall _SaveIWICBitmapSource(IWICBitmapSource *pIWICBitmapSource , const UnicodeString custrPathSaveImage, unsigned int _uiWidth, unsigned int _uiHeight);
		//Prywatne zmienne
		UnicodeString _ustrPathImage;
		//Ile skalować projekt, który zakłada 96-DPI pikseli
		float _dpiScaleX;
		float _dpiScaleY;
		//Direct2D
		IWICImagingFactory *pIWICImagingFactory;
		ID2D1Factory *pID2D1Factory;
		ID2D1HwndRenderTarget *pID2D1HwndRenderTarget;
		ID2D1Bitmap *pID2D1Bitmap;
		IWICFormatConverter *pIWICFormatConverter;
		ID2D1DeviceContext *pID2D1DeviceContext;
		IWICBitmapScaler *pIWICBitmapScaler; //Przeskalowana bitmapa do wymierów aktualnych okna.
                                         //W metodzie _ScaleBitmapSource, przeksztaucana jest w objet, klasy ID2D1Bitmap
		//DirectWrite
		IDWriteFactory* pIDWriteFactory;
		IDWriteTextFormat* pIDWriteTextFormat;
    IDWriteTextLayout *pIDWriteTextLayout;
		ID2D1SolidColorBrush *pID2D1SolidColorBrush1, *pID2D1SolidColorBrush2;
};
//---------------------------------------------------------------------------
#endif