#ifndef GsHelpH
#define GsHelpH

#include <Vcl.Controls.hpp>
//---------------------------------------------------------------------------
class GsHelp : public TGraphicControl
{
	public:
		// Kontruktory i destruktor
		__fastcall GsHelp(TComponent* Owner);
		__fastcall virtual ~GsHelp();
  // Pola typu __property
		__property UnicodeString HelpText = {read = FGetHelpText, write = FSetHelpText, nodefault};
		__property TColor HelpColor = {read = FGetHelpColor, write = FSetHelpColor, default = clWebAquamarine};
		__property int HelpFontSize = {read = FGetHelpFontSize, write = FSetHelpFontSize, default = 10};
	//---
	protected:
		virtual void __fastcall Paint();
	private:
		// ----- Pola prywatne dla właściwości __property -----
		UnicodeString FGetHelpText;
		TColor FGetHelpColor=clWebAquamarine;
		int FGetHelpFontSize=10;
		void __fastcall FSetHelpText(const UnicodeString &ustrToSet);
		void __fastcall FSetHelpColor(const TColor cColor);
		void __fastcall FSetHelpFontSize(int iSize);
};
//---------------------------------------------------------------------------
#endif
