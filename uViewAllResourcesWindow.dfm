object ViewAllResourcesWindow: TViewAllResourcesWindow
  Left = 0
  Top = 0
  Caption = 'Przegl'#261'd wszystkich dost'#281'pnych zasob'#243'w aplikacji'
  ClientHeight = 880
  ClientWidth = 1186
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
  object SplitterViews: TSplitter
    Left = 0
    Top = 541
    Width = 1186
    Height = 3
    Cursor = crVSplit
    Align = alBottom
    Color = clSkyBlue
    ParentColor = False
    ResizeStyle = rsLine
    StyleElements = [seFont, seBorder]
    ExplicitTop = 0
    ExplicitWidth = 528
  end
  object PanelViews: TPanel
    Left = 0
    Top = 544
    Width = 1186
    Height = 336
    Align = alBottom
    ShowCaption = False
    TabOrder = 0
    ExplicitTop = 540
    ExplicitWidth = 1184
    object SplitterDisplay: TSplitter
      Left = 1
      Top = 165
      Width = 1184
      Height = 3
      Cursor = crVSplit
      Align = alBottom
      Color = clMoneyGreen
      ParentColor = False
      StyleElements = [seFont, seBorder]
      ExplicitTop = 1
      ExplicitWidth = 209
    end
    object REditInfoSelectItem: TRichEdit
      Left = 1
      Top = 1
      Width = 1184
      Height = 164
      Align = alClient
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
      ExplicitWidth = 1182
    end
    object PanelDisplay: TPanel
      Left = 1
      Top = 168
      Width = 1184
      Height = 167
      Align = alBottom
      Color = clGray
      ParentBackground = False
      ShowCaption = False
      TabOrder = 1
      StyleElements = [seFont, seBorder]
      OnResize = PanelDisplayResize
      ExplicitWidth = 1182
      object ImageDisplayResource: TImage
        Left = 484
        Top = 20
        Width = 105
        Height = 105
        Align = alCustom
        Stretch = True
      end
    end
  end
end
