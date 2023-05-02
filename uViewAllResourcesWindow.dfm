object ViewAllResourcesWindow: TViewAllResourcesWindow
  Left = 0
  Top = 0
  Caption = 'Przegl'#261'd wszystkich dost'#281'pnych zasob'#243'w aplikacji'
  ClientHeight = 780
  ClientWidth = 1149
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Font.Quality = fqClearType
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  TextHeight = 13
  object REditInfoSelectItem: TRichEdit
    Left = 0
    Top = 515
    Width = 1149
    Height = 265
    Align = alBottom
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    Font.Quality = fqClearType
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 0
  end
end
