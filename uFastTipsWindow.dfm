object FastTipsWindow: TFastTipsWindow
  Left = 0
  Top = 0
  Caption = 'Szybkie podpowiedzi'
  ClientHeight = 561
  ClientWidth = 800
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
  object PanelButtons: TPanel
    Left = 0
    Top = 520
    Width = 800
    Height = 41
    Align = alBottom
    Caption = 'PanelButtons'
    ShowCaption = False
    TabOrder = 0
    object TgSwitchVisibleTips: TToggleSwitch
      AlignWithMargins = True
      Left = 9
      Top = 9
      Width = 156
      Height = 23
      Margins.Left = 8
      Margins.Top = 8
      Margins.Right = 8
      Margins.Bottom = 8
      Align = alLeft
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      ParentShowHint = False
      ShowHint = True
      State = tssOn
      StateCaptions.CaptionOn = 'Pokazuj  przy starcie'
      StateCaptions.CaptionOff = 'Nie pokazuj przy starcie'
      SwitchHeight = 14
      SwitchWidth = 36
      TabOrder = 0
      ThumbColor = clHotLight
      OnClick = TgSwitchVisibleTipsClick
      ExplicitHeight = 15
    end
    object ButtNextTips: TButton
      AlignWithMargins = True
      Left = 181
      Top = 9
      Width = 106
      Height = 23
      Margins.Left = 8
      Margins.Top = 8
      Margins.Right = 8
      Margins.Bottom = 8
      Align = alLeft
      Caption = 'Nast'#281'pna porada'
      TabOrder = 1
      OnClick = ButtNextTipsClick
    end
    object ButtPrevTips: TButton
      AlignWithMargins = True
      Left = 680
      Top = 9
      Width = 111
      Height = 23
      Margins.Left = 8
      Margins.Top = 8
      Margins.Right = 8
      Margins.Bottom = 8
      Align = alRight
      Caption = 'Poprzednia porada'
      TabOrder = 2
      OnClick = ButtPrevTipsClick
    end
  end
  object PanelImagehelp: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 520
    Align = alLeft
    Caption = 'PanelImagehelp'
    ShowCaption = False
    TabOrder = 1
    object ImageTips: TImage
      Left = 1
      Top = 1
      Width = 183
      Height = 518
      Align = alClient
      ExplicitLeft = 56
      ExplicitTop = 320
      ExplicitWidth = 105
      ExplicitHeight = 105
    end
  end
  object WBrowserTips: TWebBrowser
    Left = 185
    Top = 0
    Width = 615
    Height = 520
    Align = alClient
    TabOrder = 2
    ExplicitLeft = 472
    ExplicitTop = 256
    ExplicitWidth = 300
    ExplicitHeight = 150
    ControlData = {
      4C000000903F0000BE3500000000000000000000000000000000000000000000
      000000004C000000000000000000000001000000E0D057007335CF11AE690800
      2B2E126209000000000000004C0000000114020000000000C000000000000046
      8000000000000000000000000000000000000000000000000000000000000000
      00000000000000000100000000000000000000000000000000000000}
  end
end
