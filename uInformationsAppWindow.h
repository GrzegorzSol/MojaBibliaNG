#ifndef uInformationsAppWindowH
#define uInformationsAppWindowH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
//---------------------------------------------------------------------------
class TInformationsAppWindow : public TForm
{
__published:	// IDE-managed Components
	TImage *ImageMainInfo;
	TPanel *PanelInfo;
	TStaticText *STextInfoLicence;
	TStaticText *STextInfoVersions;
	TStaticText *STextInfoSystem;
	TBevel *BevelPartSystemInfo;
	TTimer *TimerInfoSystem;
	TPanel *PanelHeaderInfos;
	TLabel *LabelHeaderInfos;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall TimerInfoSystemTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TInformationsAppWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInformationsAppWindow *InformationsAppWindow;
//---------------------------------------------------------------------------
#endif
