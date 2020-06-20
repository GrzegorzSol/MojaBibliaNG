#ifndef GsDirect2DLiteClassH
#define GsDirect2DLiteClassH
//---------------------------------------------------------------------------
#include <Vcl.ExtCtrls.hpp>
#include <d2d1.h>

//#define _DEBUGINFO_  //U¿ywanie okna konsoli do debugowania aplikacji
#if defined(_DEBUGINFO_)
	#include "GsDebugClass.h"
#endif
//---------------------------------------------------------------------------
class GsDirect2DLiteClass : public TCustomPanel
{
	public:
		__fastcall GsDirect2DLiteClass(TComponent* Owner);
		__fastcall virtual ~GsDirect2DLiteClass();
		//---
		void __fastcall GsD2DLite_LoadPicture(const UnicodeString custrPathImage, bool _bAutosize=true);
		//---
		BEGIN_MESSAGE_MAP
			VCL_MESSAGE_HANDLER(WM_SIZE, TWMSize, WMSize);
			VCL_MESSAGE_HANDLER(WM_PAINT, TWMPaint, WMPaint);
		END_MESSAGE_MAP(TCustomPanel);
		//---
		__property TNotifyEvent OnClick = {read=FOnClick, write=FOnClick};

	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
		void __fastcall WMSize(TWMSize &Message);
		void __fastcall WMPaint(TWMPaint &Message);
		DYNAMIC void __fastcall Click();
		HRESULT __fastcall CreateDeviceResources(HWND hWnd);
		
	private:
		UnicodeString _ustrPathImage;
		TNotifyEvent FOnClick;

		IWICImagingFactory *pIWICImagingFactory;
		ID2D1Factory *pID2D1Factory;
		ID2D1HwndRenderTarget *pID2D1HwndRenderTarget;
		ID2D1Bitmap *pID2D1Bitmap;
		IWICFormatConverter *pIWICFormatConverter;
};
//---------------------------------------------------------------------------
#endif