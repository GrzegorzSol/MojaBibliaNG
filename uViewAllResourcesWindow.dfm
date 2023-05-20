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
    Top = 485
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
    Top = 488
    Width = 1186
    Height = 392
    Align = alBottom
    ShowCaption = False
    TabOrder = 0
    object SplitterDisplay: TSplitter
      Left = 1
      Top = 221
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
      Height = 220
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
    end
    object PanelDisplay: TPanel
      Left = 1
      Top = 224
      Width = 1184
      Height = 167
      Align = alBottom
      Color = clGray
      ParentBackground = False
      ShowCaption = False
      TabOrder = 1
      StyleElements = [seFont, seBorder]
      OnResize = PanelDisplayResize
      ExplicitTop = 168
      ExplicitWidth = 1182
      object ImageDisplayResource: TImage
        Left = 484
        Top = 20
        Width = 105
        Height = 105
        Align = alCustom
        Stretch = True
        OnDblClick = ImageDisplayResourceDblClick
      end
    end
  end
end
