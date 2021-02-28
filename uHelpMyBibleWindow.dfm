object HelpMyBibleWindow: THelpMyBibleWindow
  Left = 0
  Top = 0
  AlphaBlend = True
  AlphaBlendValue = 220
  BorderStyle = bsSingle
  Caption = 'HelpMyBibleWindow'
  ClientHeight = 531
  ClientWidth = 954
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
  object PanelImageHelp: TPanel
    Left = 0
    Top = 0
    Width = 954
    Height = 49
    Align = alTop
    BevelKind = bkSoft
    ParentBackground = False
    ShowCaption = False
    TabOrder = 0
    object LabelTitle: TLabel
      AlignWithMargins = True
      Left = 48
      Top = 7
      Width = 895
      Height = 31
      Margins.Left = 6
      Margins.Top = 6
      Margins.Right = 6
      Margins.Bottom = 6
      Align = alClient
      Alignment = taCenter
      AutoSize = False
      Color = clBtnFace
      Font.Charset = EASTEUROPE_CHARSET
      Font.Color = clRed
      Font.Height = -16
      Font.Name = 'Arial'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      Layout = tlCenter
      WordWrap = True
      ExplicitLeft = 44
      ExplicitTop = 6
      ExplicitWidth = 45
      ExplicitHeight = 13
    end
    object PanelPicture: TPanel
      AlignWithMargins = True
      Left = 4
      Top = 5
      Width = 35
      Height = 35
      Margins.Top = 4
      Margins.Bottom = 4
      Align = alLeft
      ShowCaption = False
      TabOrder = 0
      object ImageHelp: TImage
        Left = 1
        Top = 1
        Width = 32
        Height = 33
        Margins.Top = 1
        Margins.Bottom = 1
        Align = alLeft
        Transparent = True
        ExplicitLeft = 3
        ExplicitTop = 3
        ExplicitHeight = 32
      end
    end
  end
  object WBrowserHelp: TWebBrowser
    Left = 0
    Top = 49
    Width = 954
    Height = 482
    Align = alClient
    TabOrder = 1
    ExplicitLeft = 192
    ExplicitTop = 360
    ExplicitWidth = 300
    ExplicitHeight = 150
    ControlData = {
      4C00000099620000D13100000000000000000000000000000000000000000000
      000000004C000000000000000000000001000000E0D057007335CF11AE690800
      2B2E126208000000000000004C0000000114020000000000C000000000000046
      8000000000000000000000000000000000000000000000000000000000000000
      00000000000000000100000000000000000000000000000000000000}
  end
end
