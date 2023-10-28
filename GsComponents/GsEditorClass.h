#ifndef GsEditorClassH
#define GsEditorClassH
//---------------------------------------------------------------------------
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
//#define _DEBUGINFO_	 //Używanie okna konsoli do debugowania aplikacji
#if defined(_DEBUGINFO_)
	#include "GsDebugClass.h"
#endif
static UnicodeString sustrVersionGsEditorClass = "0.7.8844.2132";
//Flagi komponentu
enum {enSetButton_Save = 100, enSetButton_SaveAs, enSetButton_Open};
typedef Set <int, enSetButton_Save, enSetButton_Open> DisplaySelectIOButtons;

class GsEditorClass : public TCustomPanel
{
	public:
		__fastcall GsEditorClass(TComponent* Owner);
		__fastcall virtual ~GsEditorClass();
		void __fastcall LoadEditorFromFile(const UnicodeString _ustrInFilePath);
		void __fastcall LoadEditorFromStream(TStream* Stream);
		void __fastcall SaveEditorToFile(const UnicodeString _ustrInFilePath);
		void __fastcall ClearEditor();
		bool inline __fastcall IsModified() {return this->pTRichEdit->Modified;}
		inline static UnicodeString __fastcall GetVersionClass() {return Format("Klasa \"GsEditorClass\" v%s", ARRAYOFCONST((sustrVersionGsEditorClass)));};	//Metoda inline zwracająca wersje klasy
		inline TRichEdit *__fastcall GetRichEditObject() {return this->pTRichEdit;};
		//---
		__property UnicodeString EditorFileName = {read=FEditorFileName};
		__property bool IsVisibleAllIOButton = {read=FIsVisibleAllIOButtons, write=FSetupVisibleAllIOButtons, default=true};
		__property DisplaySelectIOButtons SetDisplaySelectButtons = {read = FDisplaySelectIOButtons, write = FSetupDisplaySelectIOButtons};
		__property TNotifyEvent OnSave = {read=FOnSave, write=FOnSave}; //Zdarzenie OnSave
	protected:
		virtual void __fastcall CreateWnd();
		virtual void __fastcall DestroyWnd();
	private:
    TBalloonHint *pBalloonHint=nullptr;
		TRichEdit *pTRichEdit=nullptr;
		TImageList *pTImageListActive=nullptr,
							 *pTImageListInActive=nullptr;
		TToolBar *pToolBar=nullptr;
		TToolButton *pTButtBold=nullptr, *pTButtItalic=nullptr, *pTButtUnderline=nullptr, *pTButtStrikeOut=nullptr,
								*pTButtLeft=nullptr, *pTButtCenter=nullptr, *pTButtRight=nullptr, *pTButtSave=nullptr,
								*pTButtSaveAs=nullptr,*pTButtLoad=nullptr, *pTButtPrint=nullptr, *pTButtInsert=nullptr,
								*pTButtUndo=nullptr, *pTButtRedo=nullptr, *pTButtParagraf=nullptr,
								*pTButtClear=nullptr; //[27-10-2023]
		TComboBox *pCBoxSelectFontName=nullptr,
							*pCBoxSelectFontSize=nullptr;
		TColorBox *pColBoxFont=nullptr,
							*pColBoxBackground=nullptr;
		TStatusBar *pSBar=nullptr;
		void __fastcall _InitInterface();
		void __fastcall _OnClickTButt(System::TObject* Sender);
		void __fastcall _OnSelectionChangeEdit(System::TObject *Sender);
		void __fastcall _OnChangeCBox(System::TObject *Sender);
		void __fastcall _OnChangeColor(System::TObject *Sender);
		void __fastcall _OnChangeEdit(System::TObject *Sender);
		//---
		void __fastcall _InitImageList();
		void __fastcall _PrintEditor(); //Drukowanie zawartości edytora
		//---
		UnicodeString FEditorFileName;
		bool FIsVisibleAllIOButtons=true; //Prywatny wskażnik modyfikacji
		void __fastcall FSetupVisibleAllIOButtons(bool _IsVisibleIOButtons);
		void __fastcall FSetupDisplaySelectIOButtons(const DisplaySelectIOButtons _SetDisplayButtons);
		DisplaySelectIOButtons FDisplaySelectIOButtons;
		TNotifyEvent FOnSave;
};
#endif
