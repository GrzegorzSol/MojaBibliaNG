object ViewAllResourcesWindow: TViewAllResourcesWindow
  Left = 0
  Top = 0
  Caption = 'Przegl'#261'd wszystkich dost'#281'pnych zasob'#243'w aplikacji'
  ClientHeight = 785
  ClientWidth = 1153
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object REditInfoSelectItem: TRichEdit
    Left = 0
    Top = 664
    Width = 1153
    Height = 121
    Align = alBottom
    Font.Charset = EASTEUROPE_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    TabOrder = 0
    Zoom = 100
  end
end
