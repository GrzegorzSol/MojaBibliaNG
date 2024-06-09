#ifndef uStrongWindowH
#define uStrongWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <System.IniFiles.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Mask.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <SHDocVw.hpp>
#include <Vcl.OleCtrls.hpp>
#include <Vcl.ControlList.hpp>
//---------------------------------------------------------------------------
class TStrongWindow : public TForm
{
__published:	// IDE-managed Components
	TPanel *PanelSetStrong;
	TLabeledEdit *LEditSearchNumberStr;
	TComboBox *CBoxSelectDict;
	TLabel *LabelSelectDict;
	TImageList *ImageListMain;
	TImageList *ImageListMainDis;
	TButton *ButtStartSearch;
	TPanel *PanelResult;
	TWebBrowser *WebBrowserStrong;
	TStaticText *STextInfos;
	TControlList *ControlListVerses;
	TLabel *LabelItemAdresVers;
	TPanel *PanelVers;
	TWebBrowser *WebBrowserVers;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall CBoxSelectDictChange(TObject *Sender);
	void __fastcall LEditSearchNumberStrChange(TObject *Sender);
	void __fastcall ButtStartSearchClick(TObject *Sender);
	void __fastcall LEditSearchNumberStrKeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall ControlListVersesBeforeDrawItem(int AIndex, TCanvas *ACanvas,
          TRect &ARect, TOwnerDrawState AState);
	void __fastcall ControlListVersesItemClick(TObject *Sender);

private:	// User declarations
	THashedStringList *_pHSListStrong=nullptr,
										*_pHListWordInVersesExist=nullptr, // Lista wystąpień słów, poszczególnych wersetach
										*_pHListVerses=nullptr; // Lista wystąpień dla wybranego słowa
	int _iSearchNumber=-1, // [07-06-2024]
			_iNumberTranslate=-1;// Numer tłumaczenia używany do wyświetlania wersetów
public:		// User declarations
	__fastcall TStrongWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TStrongWindow *StrongWindow;
//---------------------------------------------------------------------------
#endif
