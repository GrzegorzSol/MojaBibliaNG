object SearchTextWindow: TSearchTextWindow
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Zaawansowane wyszukiwanie tekstu.'
  ClientHeight = 951
  ClientWidth = 1194
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Tahoma'
  Font.Style = []
  Font.Quality = fqClearType
  KeyPreview = True
  Position = poScreenCenter
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnDeactivate = FormDeactivate
  OnKeyUp = FormKeyUp
  TextHeight = 16
  object STW_PControlSetupsSearch: TPageControl
    AlignWithMargins = True
    Left = 3
    Top = 80
    Width = 1188
    Height = 437
    ActivePage = STW_TabSheetInputText
    Align = alTop
    Images = ImgListSmallSearch
    OwnerDraw = True
    TabOrder = 0
    OnChanging = STW_PControlChanging
    OnDrawTab = STW_PControlViewsTextDrawTab
    ExplicitTop = 3
    object STW_TabSheetInputText: TTabSheet
      Caption = 'Szukany tekst'
      ImageIndex = 8
      object STW_GrBoxFlags: TGroupBox
        AlignWithMargins = True
        Left = 3
        Top = 66
        Width = 646
        Height = 337
        Align = alLeft
        Caption = 'Wszystkie parametry dla wyszukiwania'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        Font.Quality = fqClearType
        ParentFont = False
        TabOrder = 0
        object STW_GrBoxRegularExpressions: TGroupBox
          AlignWithMargins = True
          Left = 5
          Top = 21
          Width = 636
          Height = 92
          Align = alTop
          Caption = 
            'Ustawienia dotycz'#261'ce wyszukiwania za pomoc'#261' wyra'#380'e'#324' regularnych ' +
            '(dla zaawansowanych)'
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = []
          Font.Quality = fqClearType
          ParentBackground = False
          ParentColor = False
          ParentFont = False
          TabOrder = 0
          ExplicitWidth = 579
          object STW_ChBoxIsRegEx: TCheckBox
            AlignWithMargins = True
            Left = 14
            Top = 21
            Width = 617
            Height = 17
            Margins.Left = 12
            CustomHint = BalloonHintSearch
            Align = alTop
            Caption = 
              'Zastosuj wyszukiwanie za pomoc'#261' wyra'#380'e'#324' regularnych (dla zaawans' +
              'owanych)'
            Ctl3D = True
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clRed
            Font.Height = -13
            Font.Name = 'Tahoma'
            Font.Style = []
            Font.Quality = fqClearType
            ParentCtl3D = False
            ParentFont = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 0
            OnClick = STW_ChBoxIsRegExClick
            ExplicitLeft = 5
            ExplicitWidth = 569
          end
          object STW_ButtonHelpRegExp: TButton
            AlignWithMargins = True
            Left = 5
            Top = 44
            Width = 626
            Height = 45
            Cursor = crHandPoint
            CustomHint = BalloonHintSearch
            Align = alTop
            Caption = 
              'Pomoc w wyszukiwaniu za pomoc'#261' wyra'#380'e'#324' regularnych, przeznaczona' +
              ' raczej dla zaawansowanych u'#380'ytkownik'#243'w'
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Tahoma'
            Font.Style = []
            Font.Quality = fqClearType
            ImageIndex = 0
            ImageMargins.Left = 6
            Images = ImgListLargeSearch
            ParentFont = False
            ParentShowHint = False
            ShowHint = True
            TabOrder = 1
            WordWrap = True
            OnClick = STW_ButtonHelpRegExpClick
            ExplicitWidth = 569
          end
        end
        object STW_GrBoxNormalSearch: TGroupBox
          AlignWithMargins = True
          Left = 5
          Top = 119
          Width = 636
          Height = 202
          Align = alTop
          Caption = 'Wsp'#243'lne parametry wyszukiwania'
          Color = clBtnFace
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          Font.Quality = fqClearType
          ParentBackground = False
          ParentColor = False
          ParentFont = False
          TabOrder = 1
          object STW_ChBoxMemoSetupsSearch: TCheckBox
            AlignWithMargins = True
            Left = 14
            Top = 21
            Width = 420
            Height = 17
            Margins.Left = 12
            Margins.Right = 200
            Align = alTop
            Caption = 'Czy zapami'#281'ta'#263' parametry wyszukiwania?'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Tahoma'
            Font.Style = []
            Font.Quality = fqClearType
            ParentFont = False
            TabOrder = 0
            ExplicitLeft = 5
            ExplicitWidth = 492
          end
          object STW_ChBoxSizeTextSearch: TCheckBox
            AlignWithMargins = True
            Left = 14
            Top = 44
            Width = 420
            Height = 17
            Margins.Left = 12
            Margins.Right = 200
            Align = alTop
            Caption = 'Czy podczas wyszukiwania uwzgl'#281'dnia'#263' wielko'#347#263' liter?'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Tahoma'
            Font.Style = []
            Font.Quality = fqClearType
            ParentFont = False
            TabOrder = 1
            ExplicitLeft = 7
            ExplicitWidth = 429
          end
          object STW_ChBoxOnlyWord: TCheckBox
            AlignWithMargins = True
            Left = 14
            Top = 67
            Width = 420
            Height = 17
            Margins.Left = 12
            Margins.Right = 200
            Align = alTop
            Caption = 'Wyszukiwanie tylko ca'#322'ych s'#322#243'w'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Tahoma'
            Font.Style = []
            Font.Quality = fqClearType
            ParentFont = False
            TabOrder = 2
            ExplicitLeft = 5
            ExplicitWidth = 627
          end
          object STW_GroBoxSetupSearchText: TGroupBox
            AlignWithMargins = True
            Left = 5
            Top = 90
            Width = 626
            Height = 106
            Align = alTop
            Caption = 'Ustawianie wsp'#243'lne, zakres'#243'w wyszukiwania tekstu biblijnego.'
            Color = clCream
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            Font.Quality = fqClearType
            ParentBackground = False
            ParentColor = False
            ParentFont = False
            TabOrder = 3
            ExplicitLeft = 2
            ExplicitTop = 87
            ExplicitWidth = 632
            object STW_LabelInfoRange: TLabel
              Left = 9
              Top = 23
              Width = 139
              Height = 22
              AutoSize = False
              Caption = 'Zakres wyszukiwania:'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Tahoma'
              Font.Style = []
              Font.Quality = fqClearType
              ParentFont = False
              Layout = tlCenter
            end
            object STW_LabelInfoSelectTranslates: TLabel
              Left = 9
              Top = 51
              Width = 139
              Height = 22
              AutoSize = False
              Caption = 'Wybierz t'#322'umaczenie:'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Tahoma'
              Font.Style = []
              Font.Quality = fqClearType
              ParentFont = False
              Layout = tlCenter
            end
            object STW_LabelInfoTo: TLabel
              Left = 268
              Top = 79
              Width = 23
              Height = 22
              AutoSize = False
              Caption = 'do:'
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Tahoma'
              Font.Style = []
              Font.Quality = fqClearType
              ParentFont = False
              Layout = tlCenter
            end
            object STW_CBoxSelectRangeSearch: TComboBox
              Left = 154
              Top = 23
              Width = 201
              Height = 22
              CustomHint = BalloonHintSearch
              Style = csOwnerDrawFixed
              Ctl3D = True
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Tahoma'
              Font.Style = []
              Font.Quality = fqClearType
              ParentCtl3D = False
              ParentFont = False
              ParentShowHint = False
              ShowHint = True
              TabOrder = 0
              OnCloseUp = CBoxCloseUp
              OnDrawItem = STW_CBoxSearchDrawItem
            end
            object STW_CBoxSelectTranslates: TComboBox
              Left = 154
              Top = 51
              Width = 241
              Height = 22
              CustomHint = BalloonHintSearch
              Style = csOwnerDrawFixed
              Ctl3D = False
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Tahoma'
              Font.Style = []
              Font.Quality = fqClearType
              ParentCtl3D = False
              ParentFont = False
              ParentShowHint = False
              ShowHint = True
              TabOrder = 1
              OnCloseUp = CBoxCloseUp
              OnDrawItem = STW_CBoxSearchDrawItem
            end
            object STW_CBoxStartSelectRange: TComboBox
              Left = 9
              Top = 79
              Width = 232
              Height = 22
              Hint = 'Pocz'#261'tkowa ksi'#281'ga w wyszukiwaniu u'#380'ytkownika'
              CustomHint = BalloonHintSearch
              Style = csOwnerDrawFixed
              Ctl3D = True
              Enabled = False
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Tahoma'
              Font.Style = []
              Font.Quality = fqClearType
              ParentCtl3D = False
              ParentFont = False
              ParentShowHint = False
              ShowHint = True
              TabOrder = 2
              OnCloseUp = CBoxCloseUp
              OnDrawItem = STW_CBoxSearchDrawItem
            end
            object STW_CBoxStopSelectRange: TComboBox
              Left = 316
              Top = 79
              Width = 219
              Height = 22
              CustomHint = BalloonHintSearch
              Style = csOwnerDrawFixed
              Ctl3D = True
              Enabled = False
              Font.Charset = DEFAULT_CHARSET
              Font.Color = clWindowText
              Font.Height = -13
              Font.Name = 'Tahoma'
              Font.Style = []
              Font.Quality = fqClearType
              ParentCtl3D = False
              ParentFont = False
              ParentShowHint = False
              ShowHint = True
              TabOrder = 3
              OnCloseUp = CBoxCloseUp
              OnDrawItem = STW_CBoxSearchDrawItem
            end
          end
        end
      end
      object STW_GrBoxListGroupSearchedTexts: TGroupBox
        AlignWithMargins = True
        Left = 655
        Top = 66
        Width = 522
        Height = 337
        Align = alClient
        Caption = 'Lista wszystkich jednocze'#347'nie  wyszukiwanych tekst'#243'w'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        Font.Quality = fqClearType
        ParentFont = False
        TabOrder = 1
        ExplicitLeft = 598
        ExplicitWidth = 579
        object STW_ChBoxAllSearchTexts: TCheckBox
          AlignWithMargins = True
          Left = 5
          Top = 21
          Width = 512
          Height = 32
          Align = alTop
          Caption = 
            'Aktywyj jednoczesne wyszukiwanie tekst'#243'w Pisma '#346'wietego, kt'#243're s' +
            #261' na li'#347'cie poni'#380'ej'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = []
          Font.Quality = fqClearType
          ParentFont = False
          TabOrder = 0
          WordWrap = True
          OnClick = STW_ChBoxAllSearchTextsClick
          ExplicitWidth = 569
        end
        object STW_PanelListButtons: TPanel
          AlignWithMargins = True
          Left = 8
          Top = 279
          Width = 506
          Height = 53
          Margins.Left = 6
          Margins.Right = 6
          Align = alBottom
          BevelOuter = bvLowered
          ParentColor = True
          ShowCaption = False
          TabOrder = 1
          ExplicitTop = 264
          ExplicitWidth = 563
          object STW_ButtClearAllListSearch: TButton
            AlignWithMargins = True
            Left = 4
            Top = 7
            Width = 185
            Height = 39
            Margins.Top = 6
            Margins.Bottom = 6
            Align = alLeft
            Caption = 'Usu'#324' ca'#322#261' zawarto'#347#263' listy wyra'#380'e'#324
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Tahoma'
            Font.Style = []
            Font.Quality = fqClearType
            ImageIndex = 1
            Images = ImgListLargeSearch
            ParentFont = False
            TabOrder = 0
            WordWrap = True
            OnClick = STW_ButtAllListSearchClick
          end
          object STW_DeleteSelectPos: TButton
            AlignWithMargins = True
            Left = 195
            Top = 7
            Width = 182
            Height = 39
            Margins.Top = 6
            Margins.Bottom = 6
            Align = alLeft
            Caption = 'Usu'#324' wybrana pozycje z listy wyra'#380'e'#324
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Tahoma'
            Font.Style = []
            Font.Quality = fqClearType
            ImageIndex = 2
            Images = ImgListLargeSearch
            ParentFont = False
            TabOrder = 1
            WordWrap = True
            OnClick = STW_ButtAllListSearchClick
          end
        end
        object STW_PanelListWords: TPanel
          Left = 2
          Top = 56
          Width = 518
          Height = 173
          Align = alClient
          Caption = 'STW_PanelListWords'
          ShowCaption = False
          TabOrder = 2
          ExplicitWidth = 575
          ExplicitHeight = 158
          object STW_LBoxSearchTexts: TListBox
            AlignWithMargins = True
            Left = 4
            Top = 4
            Width = 309
            Height = 165
            Align = alClient
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Tahoma'
            Font.Style = []
            Font.Quality = fqClearType
            ParentFont = False
            Sorted = True
            TabOrder = 0
            ExplicitWidth = 366
            ExplicitHeight = 150
          end
          object STW_ButtGrSelectActionList: TButtonGroup
            AlignWithMargins = True
            Left = 319
            Top = 4
            Width = 195
            Height = 165
            Align = alRight
            BorderStyle = bsNone
            ButtonHeight = 42
            ButtonOptions = [gboFullSize, gboGroupStyle, gboShowCaptions]
            Enabled = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Tahoma'
            Font.Style = []
            Font.Quality = fqClearType
            Images = ImgListLargeSearch
            Items = <>
            TabOrder = 1
            OnClick = STW_ButtGrSelectActionListClick
            ExplicitLeft = 376
            ExplicitHeight = 150
          end
        end
        object STW_PanelInfosSelectActionSearch: TPanel
          AlignWithMargins = True
          Left = 5
          Top = 232
          Width = 512
          Height = 41
          Align = alBottom
          BevelOuter = bvNone
          Caption = 'STW_PanelInfosSelectActionSearch'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = []
          Font.Quality = fqClearType
          ParentFont = False
          ShowCaption = False
          TabOrder = 3
          ExplicitTop = 217
          ExplicitWidth = 569
          object STW_LabelInfosSelectActionSearch: TLabel
            AlignWithMargins = True
            Left = 3
            Top = 3
            Width = 506
            Height = 35
            Align = alClient
            Alignment = taCenter
            AutoSize = False
            Caption = 'Test'
            Color = clWindow
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            Font.Quality = fqClearType
            ParentColor = False
            ParentFont = False
            Transparent = True
            Layout = tlCenter
            WordWrap = True
            ExplicitLeft = 288
            ExplicitTop = 24
            ExplicitWidth = 37
            ExplicitHeight = 16
          end
        end
      end
      object STW_GrBoxSearchText: TGroupBox
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 1174
        Height = 57
        Align = alTop
        Caption = 
          'Wprowad'#378' tekst, do wyszukania w ksi'#281'gach Biblijnych. Wielko'#347#263' li' +
          'ter nie jest brana pod uwag'#281'.'
        TabOrder = 2
        object STW_CBoxHistorySearchText: TComboBox
          AlignWithMargins = True
          Left = 5
          Top = 21
          Width = 957
          Height = 24
          Align = alClient
          TabOrder = 0
          TextHint = 'Wpisz szukany tekst'
          OnChange = STW_CBoxHistorySearchTextChange
        end
        object STW_ButtAddListTextSearch: TButton
          AlignWithMargins = True
          Left = 968
          Top = 21
          Width = 201
          Height = 25
          Margins.Bottom = 9
          Align = alRight
          Caption = 'Dodaj do listy wyszukiwania'
          Enabled = False
          ImageIndex = 0
          ImageMargins.Left = 6
          Images = ImgListSmallSearch
          TabOrder = 1
          OnClick = STW_ButtAddListTextSearchClick
        end
      end
    end
    object STW_TabSheetStatistick: TTabSheet
      Caption = 'Statystyka wyszukiwania'
      ImageIndex = 7
      ParentShowHint = False
      ShowHint = False
      object STW_LViewStatistic: TListView
        Left = 0
        Top = 0
        Width = 579
        Height = 406
        CustomHint = BalloonHintSearch
        Align = alLeft
        Columns = <>
        ColumnClick = False
        Ctl3D = False
        FlatScrollBars = True
        GridLines = True
        StyleElements = [seFont, seBorder]
        OwnerDraw = True
        GroupView = True
        ReadOnly = True
        RowSelect = True
        TabOrder = 0
        ViewStyle = vsReport
        OnDrawItem = STW_LViewStatisticDrawItem
        OnSelectItem = STW_LViewAllSelectItem
        ExplicitHeight = 391
      end
      object STW_PanelDisplaySearchBook: TPanel
        Left = 579
        Top = 0
        Width = 601
        Height = 406
        Align = alClient
        BorderStyle = bsSingle
        ShowCaption = False
        TabOrder = 1
        ExplicitHeight = 391
        object STW_WebBrowserSelectBookStatistic: TWebBrowser
          Left = 1
          Top = 18
          Width = 595
          Height = 383
          Align = alClient
          TabOrder = 0
          ExplicitHeight = 203
          ControlData = {
            4C0000007F3D0000962700000000000000000000000000000000000000000000
            000000004C000000000000000000000001000000E0D057007335CF11AE690800
            2B2E126209000000000000004C0000000114020000000000C000000000000046
            8000000000000000000000000000000000000000000000000000000000000000
            00000000000000000100000000000000000000000000000000000000}
        end
        object STW_STextInfoSelectBookSearch: TStaticText
          Left = 1
          Top = 1
          Width = 595
          Height = 17
          Align = alTop
          Alignment = taCenter
          AutoSize = False
          BevelInner = bvNone
          BevelOuter = bvNone
          Color = clMoneyGreen
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clFuchsia
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          Font.Quality = fqClearType
          ParentColor = False
          ParentFont = False
          TabOrder = 1
          Transparent = False
        end
      end
    end
    object STW_TabSheetSettings: TTabSheet
      Caption = 'Dodatkowe ustawienia'
      ImageIndex = 11
      object STW_GrBoxSetupsStatistic: TGroupBox
        Left = 0
        Top = 0
        Width = 1180
        Height = 75
        Align = alTop
        Caption = 'Ustawienia dotycz'#261'ce zak'#322'adki statystyki'
        TabOrder = 0
        object STW_LabelBackGroundSearchList: TLabel
          Left = 12
          Top = 17
          Width = 394
          Height = 13
          AutoSize = False
          Caption = 'Kolor podk'#322'adu listy wyszukanych werset'#243'w'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          Font.Quality = fqClearType
          ParentFont = False
        end
        object STW_ColorBoxBackGroundSearchList: TColorBox
          Left = 12
          Top = 36
          Width = 145
          Height = 22
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
          TabOrder = 0
          OnChange = STW_ColorBoxChange
          OnGetColors = STW_ColorBoxGetColors
        end
      end
      object STW_GrBoxSetupsAllSearchResult: TGroupBox
        Left = 0
        Top = 75
        Width = 1180
        Height = 75
        Align = alTop
        Caption = 'Ustawienia dotycz'#261'ce zak'#322'adki wyniku wyszukiwa'#324
        TabOrder = 1
        object STW_LabelBackGroundStatisticList: TLabel
          Left = 12
          Top = 16
          Width = 305
          Height = 16
          Caption = 'Kolor podk'#322'adu listy statystyki wyszukanych werset'#243'w'
        end
        object STW_ColorBoxBackGroundSelectVers: TColorBox
          Left = 12
          Top = 35
          Width = 145
          Height = 22
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
          TabOrder = 0
          OnChange = STW_ColorBoxChange
          OnGetColors = STW_ColorBoxGetColors
        end
      end
      object STW_GrBoxSetupsSelectVer: TGroupBox
        Left = 0
        Top = 150
        Width = 1180
        Height = 256
        Align = alClient
        Caption = 
          'Ustawienia dotycz'#261'ce zak'#322'adki wybory pojedy'#324'czego wersetu z list' +
          'y wyszukanych tekst'#243'w'
        TabOrder = 2
        ExplicitHeight = 241
        object STW_LabelBackGroundSelectVers: TLabel
          Left = 12
          Top = 17
          Width = 437
          Height = 13
          AutoSize = False
          Caption = 
            'Kolor podk'#322'adu wybranego wersetu z listy wszystkich znalezionych' +
            ' tekst'#243'w'
        end
        object STW_ColorBoxBackGroundStatisticList: TColorBox
          Left = 12
          Top = 36
          Width = 145
          Height = 22
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
          TabOrder = 0
          OnChange = STW_ColorBoxChange
          OnGetColors = STW_ColorBoxGetColors
        end
      end
    end
  end
  object STW_GroBoxViewSearchText: TGroupBox
    Left = 0
    Top = 520
    Width = 1194
    Height = 383
    Align = alClient
    Caption = 'R'#243#380'ne widoki wyniku wyszukiwania tekstu biblijnego.'
    Color = clBtnFace
    ParentBackground = False
    ParentColor = False
    TabOrder = 1
    ExplicitTop = 513
    ExplicitHeight = 340
    object STW_PControlViewsText: TPageControl
      AlignWithMargins = True
      Left = 5
      Top = 21
      Width = 1184
      Height = 357
      ActivePage = STW_TabSheetViewListSearch
      Align = alClient
      Images = ImgListSmallSearch
      OwnerDraw = True
      TabOrder = 0
      OnChanging = STW_PControlChanging
      OnDrawTab = STW_PControlViewsTextDrawTab
      ExplicitHeight = 314
      object STW_TabSheetViewListSearch: TTabSheet
        Caption = 'Lista wszystkich wynik'#243'w wyszukiwania w formia przegl'#261'darki'
        ImageIndex = 9
        object STW_WBrowserResultSearch: TWebBrowser
          Left = 0
          Top = 0
          Width = 1176
          Height = 326
          Align = alClient
          TabOrder = 0
          ExplicitTop = 3
          ControlData = {
            4C0000008B790000B12100000000000000000000000000000000000000000000
            000000004C000000000000000000000001000000E0D057007335CF11AE690800
            2B2E126209000000000000004C0000000114020000000000C000000000000046
            8000000000000000000000000000000000000000000000000000000000000000
            00000000000000000100000000000000000000000000000000000000}
        end
      end
      object STW_TabSheetViewListView: TTabSheet
        Caption = 
          'Lista wszystkich wynik'#243'w wyszukiwania, w formie wybieralnej list' +
          'y'
        ImageIndex = 10
        object STW_LViewResultSearch: TListView
          Left = 0
          Top = 0
          Width = 1176
          Height = 81
          Align = alTop
          Columns = <>
          HotTrack = True
          OwnerData = True
          ReadOnly = True
          SmallImages = ImgListSmallSearch
          TabOrder = 0
          ViewStyle = vsList
          OnData = STW_LViewResultSearchData
          OnDataHint = STW_LViewResultSearchDataHint
          OnGetImageIndex = STW_LViewResultSearchGetImageIndex
          OnSelectItem = STW_LViewAllSelectItem
        end
        object STW_WBrowserSelectItemResult: TWebBrowser
          Left = 0
          Top = 81
          Width = 1176
          Height = 245
          Align = alClient
          TabOrder = 1
          ExplicitHeight = 237
          ControlData = {
            4C0000008B790000521900000000000000000000000000000000000000000000
            000000004C000000000000000000000001000000E0D057007335CF11AE690800
            2B2E126209000000000000004C0000000114020000000000C000000000000046
            8000000000000000000000000000000000000000000000000000000000000000
            00000000000000000100000000000000000000000000000000000000}
        end
      end
    end
  end
  object STW_StBarInfos: TStatusBar
    Left = 0
    Top = 932
    Width = 1194
    Height = 19
    Anchors = []
    Panels = <>
    ParentFont = True
    SimplePanel = True
    SizeGrip = False
    UseSystemFont = False
    ExplicitTop = 882
  end
  object STW_PanelButtons: TPanel
    Left = 0
    Top = 903
    Width = 1194
    Height = 29
    Align = alBottom
    ParentColor = True
    ShowCaption = False
    TabOrder = 3
    ExplicitTop = 853
    object STW_ButtonSearchStart: TButton
      AlignWithMargins = True
      Left = 10
      Top = 3
      Width = 87
      Height = 23
      Margins.Left = 9
      Margins.Top = 2
      Margins.Bottom = 2
      CustomHint = BalloonHintSearch
      Align = alLeft
      Caption = 'Szukaj...'
      Enabled = False
      ImageIndex = 0
      Images = ImgListSmallSearch
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnClick = STW_ButtonSearchStartClick
    end
    object STW_ButtonSaveSearch: TButton
      AlignWithMargins = True
      Left = 109
      Top = 3
      Width = 236
      Height = 23
      Margins.Left = 9
      Margins.Top = 2
      Margins.Bottom = 2
      CustomHint = BalloonHintSearch
      Align = alLeft
      Caption = 'Zapisz rezultat wyszukiwania do pliku'
      Enabled = False
      ImageIndex = 12
      Images = ImgListSmallSearch
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnClick = STW_ButtonSaveSearchClick
    end
  end
  object STW_PanelLogo: TPanel
    Left = 0
    Top = 0
    Width = 1194
    Height = 77
    Align = alTop
    BevelOuter = bvNone
    Caption = 'STW_PanelLogo'
    ShowCaption = False
    TabOrder = 4
    object STW_ImageLogoSearch: TImage
      AlignWithMargins = True
      Left = 335
      Top = 5
      Width = 69
      Height = 69
      Margins.Left = 12
      Transparent = True
    end
    object STW_STextLogoSearch: TStaticText
      AlignWithMargins = True
      Left = 411
      Top = 5
      Width = 448
      Height = 111
      Margins.Left = 12
      AutoSize = False
      Caption = 'STW_STextLogoSearch'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clMaroon
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      Font.Quality = fqClearType
      ParentFont = False
      TabOrder = 0
    end
  end
  object ImgListSmallSearch: TImageList
    ColorDepth = cd32Bit
    DrawingStyle = dsTransparent
    Left = 56
    Top = 713
    Bitmap = {
      494C01010E009801040010001000FFFFFFFF2110FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000004000000001002000000000000040
      0000000000000000000000000000000000000000000031313233696992AA5454
      AFDE626197C269697A9358585B6539393A3D1F1F1F200D0D0D0E030303040000
      0001000000000000000000000000000000000000000000000000000000000000
      000100000001030303040A0A0A0B131313141414141510101011121212131E1E
      1E1F343434374A4A4A534B4B4B55303030320000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000020202036A69909D4340EBFE4C4C
      F1FF4645EEFF6463D4FE9094BDF88383A1EA79788CD371707FB168676E875252
      545D3838383B3C3C3D403B3B3C3F0909090A0000000000000000040404051313
      13141E1E1E1F262626273737373B4747474F48484850414141474545454C5F5F
      607E6C6969D5989695E8717170A54747474F0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000070707086D6CA5B55150F1FF5152
      F1FF4B4BF1FF7372D7FF9D9DC9FFCFBAB0FFB3A193FF8B8788FF7A7984FD5962
      81F6435680EA3F618DF047668EE963666C8600000000000000011A1A1A1B4545
      464C53535362737272968F8E8ECC8D8B8AD1747474AF7C7C7CBD828180D9433A
      3DFA643D43FFB9969AFFA7A7A7DB3B3B3B3F0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000E0E0E0F706EB4C65C5DF2FF5658
      F2FF5051F1FF7D7DD1FFC8B3B2FFFDE5BAFFEBD6B1FFA39C96FF86898FFF3B5F
      91FF3565A2FF3F7ABEFF4181C4FF475789E1000000000606060768818F9E419F
      C6E98C939AE4D6C6BEFFF2B79BFFF9B897FFE3B7A4FFB1AEADFFC3C5C4FFC6B3
      B5FFB86C75FF986C72FF7D7D7D95171717180000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000161616177373C0D46567F3FF5B5E
      F2FF5557F1FF8E8CCCFFE0BEA5FFFFDCACFFF9D8A9FFB8ADA1FFA3A7ADFF4C7D
      B6FF4487CDFF4A94DDFF488CDCFF535E93D5000000002D2D2E2F1FAAE5F474B2
      C8FFD3CECBFFECBAA0FFFFCB97FFFFD19EFFFFB989FFE8B39CFFB7B8B8FFD7D1
      CFFF625557E46060607915151516030303040000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000212121227877CCE06C70F4FF6065
      F3FF5A5DF1FF8280D2FFE1BAA5FFFED2A7FFFACB9EFFC9B9ABFFC4C4C4FF889F
      BEFF4C72C5FF3751D6FF313CDDFF5D5C99C2000000016677818A0BBDF9FF9CBD
      CAFFDBD7D5FFEEC2A2FFFFEAB8FFFFE7B7FFFFD7A4FFFFB58AFFC9B4ADFF8C95
      9DF2606060834A4A4A5323232324070707080000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000002D2D2E2F7F7FD6EA7278F4FF676D
      F3FF7687F5FF889CE9FFD3B4AFFFFEDBC4FFF8D4BDFFD9CEC6FFD6D5D6FF7473
      BDFF3D3ADBFF322DECFF2E29ECFF65638EAE0707070854A1C2D10DC6FDFF96C6
      D8FFECE5E3FFE6C4B0FFFFEBBDFFFFF2C5FFFFE0AEFFFFBA8AFFD0B8ABFF57B2
      CDF35A889CCE62676A8C40404046111111120000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003B3B3C3E888AE0F27881F5FF7381
      F2FFB8DFFCFFC4F5FAFFC4C1BBFFF8E1D7FFEFDBD2FFE8E3E1FFDDE1E2FF8CBA
      E0FF76AEF9FF5169F3FF312CE9FF676681982B2C2C2D2FBEF0F919CDFFFF68C7
      E6FFF5F2F1FFEAE3E2FFEBC1A2FFFFD9A7FFFFCF9CFFFFAD84FFC5C0BBFF6AED
      FCFF69F2FFFF5F889BCB4C4C4C56171717180000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000048484C4E9093E7F87189F2FF3F94
      E2FF99D2E3FFC6EBEEFFB9D1D1FFBEADA5FFC4B5AFFFD1D1D0FFB9D2D4FFA9EF
      F4FFA5F6FCFF80BBF9FF3736E5FD6363728254595C6033D3FDFF2AD2FFFF50D3
      F2FFD9E9E4FFFBFDFFFFE5E0DFFFE4BEADFFF0B69BFFDEBDB0FF9DDCE0FF77F7
      FEFF85FBFFFF6697A8D44E4E4E591919191A0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000057575D61999EEEFC5B92F2FF12C7
      FAFF2ED7EAFF81C9D8FF9FD6E0FFA8D2D9FFBDE0E2FFBADFE2FFB7E5E8FFB4E7
      EAFFAFE9EDFF84B4F8FF3A38E0FB5B5B636E697C858D43DFFFFF37D5FEFF65D7
      F0FFE3E4D5FFF1D9CDFFDFD8D4FFCCCBC9FFA6C3CCFF85D5E6FF88F2FCFF8FF8
      FFFF9FF5F5FB72A1AFD74E4F4F5A1919191A0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000666670769DA6F0FE3E9BF1FF10D4
      FEFF17EBFEFF1DE3F7FF24DFF2FF73CCDDFFC9EFF1FFC6F1F4FFC1F1F4FFBDF1
      F5FFB8F4F9FF83A9F8FF403DDAF74F4F545A6E93A2AD56EAFFFF47DAFDFF85E5
      F8FFDFD0BAFFF5D1C1FFFBD7C7FFDDCCBFFF86D4E2FF83E4FBFF7CD9F2FF81DB
      F3FFA3E2E8F878A2B0D74C4D4D57181818190000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007073828C54A8EBFF11B8F9FF10D5
      FFFF12DEFFFF14E3FFFF1CDCF7FF9CD7E5FFD2F0F2FFCDEFF1FFC8EDF0FFC4ED
      EFFFC0F0F4FF809CF7FF4645D0F24343454970A8BCC76FFAFFFF5FE7FDFF7DDD
      F8FFB8E6E7FFDCE4DDFFF1F3EEFFE7E5DCFFABEAF1FF96E1F6FF92DEF4FF8ED9
      F1FFA4D5E2F7799CABD14747474F141414150000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000006C7F94A315BFF6FF09C5FEFF0CC9
      FFFF0DCEFFFF0FD4FFFF18CEF5FF9ACEDDFFD6EEF0FFD2EEF0FFCEEEF0FFCAEE
      F0FFC8F4F8FF7A90F5FF4F4EC8EB363636395C64686B75A9B8C26BC7DEE95EDB
      F6FF62DEFAFF6BDEF9FF86E2F4FF9DE4F4FFAEEBFBFFC9F8FEFFCAF7FEFFC4EC
      F5FDD4EAEBF6788F9CB9323232350D0D0D0E0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000888BA9B97CB5F1FF1BADF2FF07BF
      FEFF09BFFFFF0EC3FDFF1BC5F8FF7DC5DEFFDEF2F3FFDCF3F4FFD8F2F4FFD3F2
      F4FFCFF4FAFF7687EDFF5959B9E129292A2B0000000000000000141414153434
      3536575E62656F868E946F9FB1BD5DC7E3F067E6FBFF68DCF7FF78DCF7FF8FC3
      DAF0ABC5D3E46C757A8412121213040404050000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009597BBCFB4C0F7FF67A5EEFF0FC2
      FBFF11AFFAFF76CCF2FFBCE6F8FFD9F1FAFFEBFBFEFFE7F9FDFFE2F7FCFFDDF6
      FCFFD2ECF9FE7982E0F66C6C97AC121212130000000000000000000000000000
      0000000000000000000000000000626C727677F4FEFF76F9FFFF6AF0FEFF6779
      83942F2F2F311010101101010102000000010000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000007E7F94A3979AC0D48A94B8CD58A2
      C1CF698EAFC08F92A4B28E8F9EAB898A97A2848490997E7E8890787882897273
      7A806A6B71774C4C4F5214141415000000000000000000000000000000000000
      00000000000000000000000000000E0E0E0F575D606370858B916E828C951919
      191A050505060000000100000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000010101020909090A111111121212121310101011121212131D1D
      1D1E323232354747474F4949495230303032020202030F0F0F105B5B5B716262
      628D6A676492776E6897786F689A7870689B7870689B786F6999766E6896746D
      6891726C678B5654535F10101011030303040F0F0F1074747489757575992020
      20211919191A20202021262626282A2A2A2C2A2A2A2C27272729212121221A1A
      1A1B121212130A0A0A0B03030304000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000001000000000000000000000000030303040E0E
      0E0F1818181923232324353535384343434A4545454D424242484545454C5E5F
      60774F6487CD3472A8DF5F6A79A74A4A4A5300000000040404053B3B3BED1717
      17FF684A33FFDC8B4AFFDC8B4BFFDD8C4CFFDE8D4CFFDE8D4DFFDF8E4EFFDF8F
      4FFFE08F50FFB18F76BF0000000000000000353535376B6B6BFFA6A6A6FF8585
      85CD141414150000000000000000000000000000000000000000000000000303
      030478716E8791847CB13F3E3E42000000000000000000000000000000000000
      0000000000000000000027272728616161740A0A0A0B00000000000000000000
      0000000000000D0D0D0E60747BA14D4F4F580000000000000001121212133636
      363A4D4D4D58616B7390528396C04E8098C85A6B7FB3546B88BD3C75A1DA2855
      8AFA3A5E9BFF2DAAD6FF3792B6E143434349000000000F0F0F10373737FA2323
      23FF72553EFFE19051FFE19152FFE29153FFE39254FFE39355FFE49456FFE595
      57FFE69558FFBA9579C60000000000000000252525267E7E7EF0797979FF9C9C
      9CFF8A8A8AD620202021070707080707070807070708313131335957565FA294
      8DB2FEDBC1FFFED7B9FFCF9E87EA060606070000000101010102010101020101
      01020101010201010102656564775353535E7A7A7AAA0909090A010101020101
      010213131314557F8CBC0CCAEFFF607C849E00000000040404057A696585A673
      6AD73A77A9E121C9EBFFA3AEA8FFC8AF96FF85B1B3FF0A98E1FF00C2FCFF1FB9
      E8FF4E91DEFF4988C0FF668299BA20202021000000000F0F0F10373737FA2424
      24FF71543FFFE59457FFE59558FFE69659FFE7975AFFE8985BFFE8985CFFE999
      5DFFEA9A5FFFC1997BCC0000000000000000242424259C9C9CC6929292FF8282
      82FF8F8F8FFF7C7C7CE8868686B9817F80B97D7C7CB9BBAEA6E3FDE0CDFFFEE8
      D7FFFFE5D1FFFFE1C9FFBF9E8EE8323232341A1A1A1B3737373A3737373A3737
      373A3737373A3737373A51504F598C8C8CE8393A39FF7674729F3838383B3A39
      393D607C84B01FCEF0FF5B8590B5060606070000000025252526DA6540F16D79
      A2FF00C9FFFFA1B7B1FFFFC58EFFFFD39EFFFFBE88FFB1AB9DFF0DABE8FF14D1
      FDFF2C69A7F8656C77A42727282906060607000000000F0F0F10323232FB2222
      22FF6E523DFFE8985BFFE8995CFFE9995DFFEA9A5EFFEB9B60FFEC9C61FFEC9D
      63FFED9E64FFC79B7CD100000000000000007F7F7F84F2F6F6FFE9ECEDFFA1A2
      A2FF999999FF898989FF929292FFCED1D2FFB3B6B6FF929393FF827A78FFFDE8
      DBFFFFECDDFFFEE6D3FFD2B2A1FF7E7E7E906965627EB17A59FF0B0705FF0C08
      05FF0C0805FF0D0805FF0D0805FF201C19FF767573FF434443FF313030FF025E
      7DFF00BEEAFE1C7186FF68696882000000000000000171656279E9623BFF428C
      B2FF00E2FFFFC1B5A4FFFFE7B2FFFFE8BAFFFFDBA8FFFFBB87FF44A4CAFF0E7E
      D9F7646669974A4A4A54212121220606060700000000101010112F2F2FFB2020
      20FF694E3AFFE9995CFFE9995DFFEA9A5EFFEA9A5FFFEB9B5FFFEB9C61FFEB9E
      63FFEC9D62FFCB9C79D7000000000000000081818286F4F8F8FF782013FF9A57
      50FF9A8B88FF9F9F9FFFA7A7A7FF635854FF86706AFF568693FFCAB6ACFFFEF0
      E8FFFEEDE1FFFEE0CCFFB8A8A0FF808080926A65627F805432FF764928FF6937
      18FF6C3918FF713D19FF743F1BFF794623FF734D32FF807770FF616160FF8EA0
      A2FF3C8B9CFF515F55FF6A6663810000000004040405AB7B6CC1F16F46FF5394
      A3FF07FEFFFF90B8BCFFFFE1B1FFFFF5C9FFFFE3B1FFFFC58FFF6AA4B9FF8271
      87F5906A5FC8666361853E3E3E441010101100000000101010112C2C2CFB1E1E
      1EFF654A36FFE79659FFE7975AFFE8985BFFE8985BFFE8995DFFE99C62FFE99B
      60FFEA9A5FFFCE9B75DD000000000000000081818286F4F7F8FF923221FF962B
      18FF8A2B19FF7A4B41FF8C7874FF92756DFFD09982FF6CC5D3FFFCF5F1FFE6CA
      BDFFD0AF9DFFD0B2A3FF727373FF808080926C68637F8D5E35FF8F6036FF8E5D
      32FF7D4820FF794118FF784219FF764018FF72411DFF766050FFB7B5B4FF6062
      62FF464F4AFF50270EFF69646281000000001F1F1F20D97D5DF4F08359FF997D
      7DFF4DF8FAFF5BE9F5FFC4ADA4FFFFD5A1FFFFD49EFFFFB383FF43A9CAFFCF9F
      8BFFFD9E72FF976E62C84A4A4A54171717180000000010101011282828FB1D1D
      1DFF604531FFE59456FFE59557FFE59557FFE69658FFE69A60FFE7995EFFE797
      5BFFE8985CFFD19A70E2000000000000000081818286F4F7F8FFA64B33FFA53C
      25FF8C351EFF84402DFF7D7674FFCC8D71FFEADBD4FF92CFDDFFC4E6E7FF6AB7
      CAFFE39E84FFC69984FF9E9E9EFF757575926D68647E8F643AFF91653AFF9266
      3AFF93663AFF87572EFF7D491EFF7D491EFF8A684DFFADA197FF855F45FF9387
      7DFF949494FF706964FF736F6CC30E0E0E0F4D4A4950EB8F68FFED8F67FFE08D
      6EFF7DC3D9FF6EFDFEFF3AE3F4FF8EB8B9FFBCB09BFF5EB0C4FF4CB4CCFFF2AB
      89FFF8B38CFFA67B6CD24B4B4B55181818190000000011111112232323FB1A1A
      1AFF593F2CFFE39253FFE39254FFE39354FFE4965BFFE4985EFFE59557FFE595
      57FFE6965AFFD4996AE8000000010000000081818186F3F7F7FFB86B4FFFBB5B
      3CFFA75B3AFF775547FFA78C81FFDD9C7CFFFEEFE7FFFCDDD1FF96C3D2FFEDA9
      94FFFAC4B0FFBC8B74FFBCB9B8FF727272986E68647E94683BFF96683CFF986A
      3CFF9A6B3CFF9C6C3CFF946335FF896A52FFB09F92FF835838FF754929FF6B4B
      33FFB0B1AFFFB2B3B2FF9A9A9AE862626275796D6881EF9E77FFED936BFFEEAC
      86FFA5D1DFFF5BD1F0FF18DAF5FF00C3F7FF24ACDEFF80A1ADFFF0BC9AFFFABE
      97FFE6BE9DF6A48273CD4C4B4B551818181900000000111111121E1E1EFB1616
      16FF523926FFE08F50FFE19050FFE19152FFE29A62FFE29254FFE39254FFE394
      56FFE49456FFD59666EC020202030000000081818186F3F7F7FFC48B6EFFC87A
      59FF93311CFF664946FFB69787FFE4A78FFFFEE2D3FFFDDACAFFD2C1BFFF6BAD
      DCFFB5B6C2FFA67466FFC0B7B4FF797979A56E69647E927A51FF9B794BFFA375
      44FFA57744FFA67844FFB3A08AFFBCB0A2FF956A45FF7A4923FF683714FF6234
      15FFB2AAA5FFCEC8C5FF6B67658308080809957C74A1F5AF88FFF19B73FFECBA
      98FF7CD8EAFF8ECEEBFF97D0F3FF75B8DEFFC5A394FFFFBB8CFFF3B088FFF1B3
      8CFFDCB598F2A48576CC4A4A4A53181818190000000011111112181818FB1212
      12FF4B3421FFDE8D4DFFDF8D4DFFE0975EFFE09154FFE08F4FFFE19050FFE193
      56FFE29152FFD69461F0040404050000000081818186F2F6F6FFCDA28BFFB659
      35FF801F11FF673C35FFA78E82FFDAA58DFFFAC5ACFFFAC8B1FFDBD0C8FF0BCD
      FDFF189CEEFF8C7075FFBFBCBCFF737373986F6A657EA8A27AFFA0885BFF9D74
      43FF9F7543FFA37643FFAA8556FFAD8656FFA57746FF966538FF784119FF7039
      14FF8F715FFFDFDEDEFF848382B300000001BB8E7BCAFCC8A1FFF3AB84FFF7B2
      88FFBEDDCDFFA2D5E2FFCFEBF1FFB0D7E3FFDBBA9DFFF7BF96FFF3BF98FFF0B0
      8AFFD3B69BEDA5897BCC4646464E151515160000000011111112111111FC0E0E
      0EFF442E1CFFDC8B49FFDD9052FFDE945AFFDD8C4CFFDE8D4CFFDF8F51FFDF90
      52FFDF8E4FFFD89159F4060606070000000081818186F2F6F6FFD3B09DFFC46F
      4AFF992F14FF853A27FF907C75FFCD9A80FFF4E3D8FFF8C0A5FFFED8C0FF97D7
      D9FF0DC7FBFF5384C6FF90929FFF74747492706B657EB0946CFFB68D57FFB586
      4AFFB5874BFFB3864BFFB0844BFFAF854CFFAA7D48FFA67946FF9D7142FF7246
      24FF5B3016FF58311BFF6B666381000000007C6E6982C89883D5F0A982FCF3AB
      86FFF8A980FFF8B78DFFE2BD9EFFE0C0A4FFFCDFB7FFFBE5BEFFF9DCB5FFEFD0
      ADFBD4C4A9E99C8479BA353535380E0E0E0F00000000121212130C0C0CFC0909
      09FF3D2717FFDB8B4BFFDE9E6BFFDB8A48FFDB8A49FFDC8A49FFDD9256FFDD8B
      4BFFDD8C4CFFD98E54F70A0A0A0B0000000081818186F1F5F4FFD5B6A4FFD392
      70FFB44D2BFFB14A27FF6A544CFFC2947DFFD8A289FFEDAC90FFF7C7AEFFFEE3
      CEFF9EAFC3FF486AFCFF2D47B9FF7F7F7F92706B657EAD9C85FFAF8C5BFFB085
      49FFB08549FFB08549FFB08449FFAE8248FFAC7D47FFA87A45FFA67844FFA475
      43FF8F5C31FF662F0EFF6C65628100000000000000000A0A0A0B212121224C48
      474E81726D879B837AA4C28C77D1EDA07BFAF3AD87FFF1AB85FFF3B791FFDFB4
      92F4CCB8A0DF7D736E8915151516050505060000000012121213070707FC0303
      03FF362314FFDD9A64FFDB9359FFD98745FFDA8846FFDB8F51FFDB8D4FFFDB89
      48FFDC8A49FFD78C50FA0E0E0E0F0000000081818186F1F5F4FFCDB3A2FFD2A9
      93FFBF795EFFBA7357FFA26550FF716D6BFFA78778FFBC8771FFB4705FFFB880
      6FFFA7867DFF6B77B4FF9D9FAFFF808080926C686378B3894BFFB48A4DFFB58B
      4EFFB68C4FFFB68C50FFB68C51FFB58A50FFB2884FFFAE844DFFAA804BFFA479
      48FF9F7344FF8F6339FF6A65627B000000000000000000000000000000000000
      0000000000000000000006060607796B677EFAC29BFFFDC8A1FFFABE97FF9A79
      6FB33D3C3C402323232402020203000000010000000012121213565656FC7D7D
      7DFF908D8AFFC0B1A5FFC1AFA1FFC2B0A2FFC4B2A3FFC6B4A7FFC7B4A5FFC8B5
      A7FFC9B6A8FFA5876FDC00000001000000007E7E7E83F0F3F3FFE7E9EAFFE4E7
      E7FFE2E4E5FFE0E2E3FFDCDFDFFFCACBCBFF868686FF6D6D6DFF7B7B7BFF7B7B
      7BFF898989FFA3A29FFFB1AFABFF7B7B7B890000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000F0F0F10776B677C9F867CA9AB8578B92A29
      292B0707070800000001000000000000000000000000020202035F5F5F726464
      647A676665776B6967766A67657469666472676562706563616F6462606E6462
      606E63615F6D4B4A494F00000000000000001E1E1E1F8787878A8B8B8B8E8B8B
      8B8E8B8B8B8E8B8B8B8E8B8B8B8E8B8B8B8E8A8A8A8E8787878E8283838E8686
      868E8888888E8888888E8484848A1F1F1F200000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000E0E0F0F675E6C6C876F
      98C4866E99C5866E99C5866E99C58E739DB26D6374785F5D6771595B616F595B
      616F595B616F595B616F4E4F515A000000000000000000000000000000001818
      1819595959633F3F3F4314141415070707080101010200000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000010101111716477775354
      6AEB8972949F8771919B8E7497A88D74929E7E699CB61F3095EF1C3093EF1C30
      93EF1C3093EF1C3093EF515A86C200000000000000000000000000000000B0B0
      B0D1E7E7E7FFE0E0E0FFC3C3C3F5919191C67070708D494949501A1A1A1B0909
      090A020202030000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000909090A25252526030303040303
      0304000000000000000000000000000000007B7774AE877B6BEB897B6DEB8474
      65EB597962EB599173EB599173EB51866AEB517997EB5B8298EB5B8298EB4D69
      92EB525391EB555794EB545693EB707281AE000000001010111171647777605B
      77E54C484E4E1C1C1C1D71656D7A504C4C51818798A662E7EFFF62E7EFFF62E7
      EFFF62E7EFFF62E7EFFF70A8ACCF0000000000000000000000003B3B3B3DE5E5
      E5FFEBEBEBFFEAEAEAFFEAEAEAFFE9E9E9FFE5E5E5FFDBDBDBFFBFBFBFF68F8F
      8FC87070708F4A4A4A5214141415000000010000000000000000000000000000
      00000000000000000000000000000303030464757BB0507A87D74D4D4D576063
      647C1010101100000000000000000000000066625F77CA996AFFCF9F70FFBB88
      5AFF2F934BFF32E28AFF32E28AFF19BB67FF1B92F8FF3CAFFCFF3CAFFCFF0A61
      EBFF1C1CE5FF2727EFFF2424ECFF5D5D6A77000000001010111171647777605B
      77E54A464C4C04040405806B61A854504C55737C7A955CB1B6EF5CB1B6EF5CB1
      B6EF5CB1B6EF5CB1B6EF6D9395C2000000000000000000000000969696A5EAEA
      EAFFE7E7E7FFE7E7E7FFE6E6E6FFE5E5E5FFE4E4E4FFE2E2E2FFDEDEDEFFD8D8
      D8FFD2D2D2FFC8C8C8FF8C8C8CD3141414150000000000000000000000000000
      000000000000000000001919191A3838383C2DADD1F825B3DBFE2E7892FB269C
      BEFE4D4D4E5700000001000000000000000066625F77CA996AFFCF9F70FFBB88
      5AFF2F934BFF32E28AFF32E28AFF19BB67FF1B92F8FF3CAFFCFF3CAFFCFF0A61
      EBFF1C1CE5FF2727EFFF2424ECFF5D5D6A77000000001010111171647777605B
      77E54A464C4C040404057E5943D1655E5667737D79955CB1B6EF5CB1B6EF5CB1
      B6EF5CB1B6EF5CB1B6EF6D9395C2000000000000000013131314D9D9D9F8E6E6
      E6FFE5E5E5FFE4E4E4FFDEDCDDFFD0B8CBFFC38FB7FFB480A9FFA5A5A5FFA4A4
      A4FFABABABFFB8B8B8FF999999EB1C1C1C1D0000000000000000000000000000
      0000000000000101010265747AAC5B7179C5478495E224BCE6FF24BBE5FF24B6
      DFFF62696B8102020203000000000000000066625F77CA996AFFCF9F70FFBB88
      5AFF2F934BFF32E28AFF32E28AFF19BB67FF1B92F8FF3CAFFCFF3CAFFCFF0A61
      EBFF1C1CE5FF2727EFFF2424ECFF5D5D6A77000000001010111171647777605B
      77E54A464C4C040404057C6D61993938373A7284849F5BD8DFFF5BD8DFFF5BD8
      DFFF5BD8DFFF5BD8DFFF6EA4A6CF000000000000000070707076E5E5E5FFD8CD
      D6FFC192B7FFB667A5FFB3489DFFB945A1FFBB46A2FFC473B3FFC3C2C2FF9B94
      9AFFA7A7A7FFAEAEAEFE6666667D060606070000000003030304040404050000
      000107070708272828292AB1D6FB2889A7FE24AFD6FF24BAE4FE24BCE6FF26A8
      CDFE656F729C565756661E1E1E1F0000000066625F77CA996AFFCF9F70FFBB88
      5AFF2F934BFF32E28AFF32E28AFF19BB67FF1B92F8FF3CAFFCFF3CAFFCFF0A61
      EBFF1818E2FF2121EAFF1F1FE8FF5D5D6A77000000001010111171647777605B
      77E54A464C4C040404056A625D782E2E2D2F6F7E7E9566CAD0EF66CAD0EF66CA
      D0EF66CAD0EF66CAD0EF729DA0C20000000000000001C2C2C2DCE2E2E2FFB67D
      AAFFA43D8EFFA93F93FFAF4198FFB3439CFFB7449FFFC372B2FFDDDBDDFFBCA4
      B6FFCECECEFF767676950909090A000000001010101163636D94606065814E4E
      4F5A616171A85051525D667A809D24BBE5FF24BCE6FF25B9E3FE449CA4E728BA
      D7FE359084F83B8E4DFE666B678F0808080966625F77CA996AFFCF9F70FFBB88
      5AFF2F934BFF32E28AFF32E28AFF19BB67FF1B92F8FF3CAFFCFF3CAFFCFF4A84
      CAD655555D6655555D6655555D662D2D2D2F000000001010111171647777605B
      77E54A464C4C040404056A625D782E2E2D2F6E7A7B955CB1B6EF5CB1B6EF5CB1
      B6EF5CB1B6EF5CB1B6EF6D9395C2000000003939393BDFDFDFFFDFDFDFFFB076
      A4FF9B3986FFA13C8CFFA63E90FFAC4095FFB14299FFBF70AFFFDFDFDFFFBFA5
      B9FF888888B00909090A000000000000000062626B841A178BFE141379FE1614
      7FFE1A1790FF3E3E79DF6570739328B7DEFC32B1D3F426A2C6FE4D9468EB40BC
      7CFE40AB62FE42B66AFE5E8268CD5454546266625F77CA996AFFCF9F70FFBB88
      5AFF2F934BFF32E28AFF32E28AFF19BB67FF1B92F8FF3CAFFCFF3CAFFCFF628A
      B1BA00000000000000000000000000000000000000001010111171647777605B
      77E54A464C4C040404056A625D782E2E2D2F6E7B7B955CB1B6EF5CB1B6EF5CB1
      B6EF5CB1B6EF5CB1B6EF6D9396C20000000031313132D2D2D2FDDADADAFFB674
      AAFF92367DFFA35391FFC187B4FFCBA0C1FFAE529AFFBA6EAAFFDFDFDFFF9285
      8EC90E0E0E0F000000000000000000000000646379A41B1894FF201CA5FF201C
      A5FF201CA4FF181681FD2A387EF02D5793F0535455615C929AC83DA262FE42BD
      6EFF43BE6FFF40A961FE357239FF607E67C666625F77AA7246FFAD7549FFA369
      3EFF2F934BFF32E28AFF32E28AFF19BB67FF1B92F8FF3CAFFCFF3CAFFCFF628A
      B1BA00000000000000000000000000000000000000001010111171647777605B
      77E54A464C4C040404056A625D782E2E2D2F7388889F69F7FFFF69F7FFFF69F7
      FFFF69F7FFFF69F7FFFF73AFB2CF00000000000000002D2D2D2E64646469AA77
      A1D8C78BBDFFDACAD6FFDEC9D8FFD7C4D2FFAB5C9AFFB46BA5FFDFDFDFFF5855
      576000000000000000000000000000000000272728296867869F59595F6C4140
      94E3201CA5FF201C9FFE1A1791FF1E1A98FE615B70C05C5B5B706A7A6FA9666E
      698D43B96DFE43BC6FFE44B76DFC6B8173A4060606070F0F0F100F0F0F100F0F
      0F1062977ABF32E28AFF32E28AFF19BB67FF1B92F8FF3CAFFCFF3CAFFCFF628A
      B1BA00000000000000000000000000000000000000001010111171647777605B
      77E54A464C4C0404040573696085514E4952737D7A955CB1B6EF5CB1B6EF5CB1
      B6EF5CB1B6EF5CB1B6EF6D9396C2000000000000000000000000000000008F6E
      88B2C48EB9FFE1CCDDFFDCC3D6FFCFABC8FF9E4A8CFFAD689FFFDFDFDFFF5E5A
      5D66000000000000000000000000000000000000000000000000000000006666
      7B942E2AA4F6605F8ABC2E2AA2F6413E85E3824734FB774737F46A3C2DF7676C
      58D755A872E86A9279BE52A66DEC0C0C0C0D0000000000000000000000000000
      000062957ABA32E28AFF32E28AFF19BB67FF1189F7FF279CF9FF279CF9FF6089
      B1BA00000000000000000000000000000000000000001010111171647777605B
      77E54A464C4C040404057B5137DC6760586A737D7A955CB1B6EF5CB1B6EF5CB1
      B6EF5CB1B6EF5CB1B6EF6D9395C2000000000000000000000000000000008B6A
      84B8A15491FFA45493FF9E428CFFB873ABFFC9A2C1FFD8CED5FFDFDFDFFF645F
      636E000000000000000000000000000000000000000000000000000000000000
      000005050506000000017A6262CE603231FE8B4933FFA25940FE9E553DFF846C
      64C512121213070707080B0B0B0C000000000000000000000000000000000000
      000062957ABA32E28AFF32E28AFF1ABA68FE3030303230303032303030322323
      232400000000000000000000000000000000000000001010111171647777605B
      77E54A464C4C0404040580685BB2403E3C41707E7D9561BDC3EF61BDC3EF61BD
      C3EF61BDC3EF61BDC3EF70999BC2000000000000000000000000000000008769
      81BBA46297FFAE70A2FFCF9CC8FFD2A9CCFFBC82B2FFB974AEFFA26996E9524F
      5157000000000000000000000000000000000000000000000000000000000000
      00000000000000000000796E6A9FA65B41FFA75B41FFA16049F69D644FEE7C69
      63BD050505060000000000000000000000000000000000000000000000000000
      000062957ABA32E28AFF32E28AFF1ABA68FE0000000000000000000000000000
      000000000000000000000000000000000000000000001010111171647777605B
      77E54B474D4D1515151674686F802D2D2D2E7E8695A462E7EFFF62E7EFFF62E7
      EFFF62E7EFFF62E7EFFF70A8ACCF00000000000000000000000000000000605B
      5F6B9F7397FEB895B1FEA885A1D88675839D5C575B6225252526000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000004947474D7C716C9695756AC77C6C67B41F1F1F201717
      1718000000000000000000000000000000000000000000000000000000000000
      000062957ABA32E28AFF32E28AFF1ABA68FE0000000000000000000000000000
      0000000000000000000000000000000000000000000010101111716477775A58
      72E87E6D86897A6A808388718F9776687B7D8881A1B45DAFB6EF5CB1B6EF5CB1
      B6EF5CB1B6EF5CB1B6EF6D9395C2000000000000000000000000000000000000
      00001E1E1E1F1414141500000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000707070801010102000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000648C78AC35B170EB35B170EB2CA566EB0000000000000000000000000000
      000000000000000000000000000000000000000000000F0F10106B6070707865
      8DD678658DD678658DD678658DD68D719FC080758D93788A91A0748B8D9F748B
      8D9F748B8D9F748B8D9F68727381000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000001010102151515163E3E
      3E43525252615151515E4545454D3636363A272727291B1B1B1C181818192121
      2122333333364A4A4A53525252603E3E3E430000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000A0A0A0B313131344848484F49494950323232350A0A0A0B0000
      000000000000000000000000000000000000000000000E0E0F0F675E6C6C876F
      98C4866E99C5866E99C5866E99C58E739DB26F667578636569715E63636F5E63
      636F5E63636F5E63636F5052535A0000000000000000070707088C7E7798E4B1
      94F5BD9A87E19D8678C97B746EA6616264845858586C4F4F4F5C4F4F4F5B6061
      647F54627ECC1675C3F7497294CB525252610000000000000000000000002323
      23244747484F0202020300000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000002828
      282A858585A1D1CDC8EFD4C4B7FFBEA595FFA38B7BFF89746BFF6C6460F16C6B
      6AA52C2C2C2E0000000000000000000000000000000010101111716477775354
      6AEB8972949F8771919B8E7497A88D74929E8A83A4B662BBC4EF61BDC3EF61BD
      C3EF61BDC3EF61BDC3EF70999BC200000000000000013938383BEDB8A0FAFFFF
      FFFFFFFBF7FFD2CBCFFF62B7C9FF37A1C1F34182A3DC486D93CC2681BDE81B70
      AAF93A64A0FF3F92CBFF23CAEAFF4343434A0000000000000000000000006680
      90A52981BCF76166698810101011000000000000000000000000000000004C50
      525562828AAA12121213000000000000000000000000010101025E5E5D6BE1DE
      DCF5E0C3ADFFC38D63FFBB7847FFB0693CFF9E5E3CFF935C45FF946A5BFF876B
      62FF675D59F8605F5F730101010200000000000000001010111171647777605B
      77E54C484E4E1C1C1C1D71656D7A504C4C51818798A662E7EFFF62E7EFFF62E7
      EFFF62E7EFFF62E7EFFF70A8ACCF0000000003030304958179A1FBECE4FFFFF3
      ECFFAAB5D7FF0AB9FDFF72B6BDFFE2B18CFFE3B991FF6CB4C1FF00ABF2FF11D7
      FBFF3D96DEFF3A70B4FF677D92B21C1C1C1D00000000000000000B0B0B0C338D
      C5F4709EC0FF6491B6FE4F7085CA4646474E0909090A0000000000000000618A
      A0AA17EFFEFF46A9B7DB628C92AF272828290000000058575764D2BFAFFDC093
      6DFFCC8640FFD97D2BFFCF7026FFBA6024FFA24F23FF904324FF843C24FF8048
      37FF957163FF9F8D84FE5E5E5E6D00000000000000001010111171647777605B
      77E54A464C4C04040405806B61A854504C55737C7A955CB1B6EF5CB1B6EF5CB1
      B6EF5CB1B6EF5CB1B6EF6D9395C2000000001B1B1B1CDBA690EDFFFFFFFFF5C9
      BCFF2095D8FF22D2F7FFE99276FFFF9064FFFF986EFFFF9F6FFF5AA6C1FF02B7
      FDFF3892C2FF727277A31E1E1E1F0303030400000000000000005055575C2F97
      DCFFD8C2B9FFFDCAAEFFC0B3B0FF4D84AFFB4D6F85CB5F63667E5F686E7D15B7
      F0F912DDFFFF14E3FFFF26C8E0F50D0D0D0E16161617ACA299EDBB8D66FFDB86
      30FFE38D2FFFDF8A2FFFD9822CFFD2792BFFC76F29FFB56027FF984A25FF7A36
      24FF853F27FF9A725FFFB2A8A1F31B1B1B1C000000001010111171647777605B
      77E54A464C4C040404057E5943D1655E5667737D79955CB1B6EF5CB1B6EF5CB1
      B6EF5CB1B6EF5CB1B6EF6D9395C2000000004F4C4B52F5CABAFFFFFEF9FFE9AD
      A0FF07C3EBFF2BE4F3FFE8B297FFFFCCA0FFFAAA83FFFF956AFFB7A192FF1C86
      D7FF958C8BC72F2F2F310707070800000000000000000000000065869BB75892
      BEFFFEE5D1FFFDCEB4FFFDCCB0FFFDC9AAFFDABFAEFF96A5B2FF20C0ECFF09C4
      FFFF0CC9FFFF0ED0FFFF21B7DEF51313131457575763B69E8BFFD9802FFFE492
      32FFE6A33BFFE49634FFE38D2FFFE3892DFFE2852BFFE28128FFE17B26FFD06C
      24FFA04D23FF9E5028FFAD9586FF5E5E5E6D000000001010111171647777605B
      77E54A464C4C040404057C6D61993938373A7284849F5BD8DFFF5BD8DFFF5BD8
      DFFF5BD8DFFF5BD8DFFF6EA4A6CF0000000084736E8DF8DCD1FFFFFDF5FFF9B5
      A3FF4EC7D3FF28FFFFFFA5BBB8FFFFE8B7FFFFEFBDFFFFCD96FFB2A79CFF7E9F
      ACF95B5A59691919191A000000010000000000000000161616176C849DFBC98C
      7AFF8E8D9AFFF0D3BFFFFFE0C7FFFFDCC0FFFFD9BBFFFED3B1FFF4C1A3FF4AC4
      DEFF05B5FFFF1DA5DDF45D8999B7202020217170708EC38E60FFE38C2FFFE597
      35FFE59736FFEDB87BFFF7DFC7FFF5E3D2FFF5E2D1FFF6DDC8FFEDB07BFFE179
      27FFE07523FFC06224FFB57C57FF78767699000000001010111171647777605B
      77E54A464C4C040404056A625D782E2E2D2F6F7E7E9566CAD0EF66CAD0EF66CA
      D0EF66CAD0EF66CAD0EF729DA0C200000000A78276B7FBE9DFFFFEEADCFFFFBB
      9EFFBAA4A4FF6FF3F9FF5DEBF9FFABB1AEFFF7BC92FFE9B08AFF4AB4CAFF868A
      8AD23E3E3E430D0D0D0E0000000000000000000000005C63686FBA9B93FF6182
      B1FF4181C5FF686C83FFDAB29EFFD3B8A5FFF3D2B7FFFED0B1FFFDCAABFFBFBC
      B2FF2EB2E8FF6693B1FB4D738ED8434343497E7C7A9FD28F4FFFE38D2FFFE490
      35FFF7DEC4FFF0CEADFFE39243FFE3862DFFE2832BFFE1883AFFEEC3A1FFF7DD
      C9FFE27B2CFFE07623FFC97C43FF8A8785AD000000001010111171647777605B
      77E54A464C4C040404056A625D782E2E2D2F6E7A7B955CB1B6EF5CB1B6EF5CB1
      B6EF5CB1B6EF5CB1B6EF6D9395C200000000BA8676CDFFEBDEFFFFEADAFFFFDD
      CAFFFBAF96FFADA9AEFF3FE5F1FF0CE4FCFF20BEE9FF31BAE7FF6FADC7FF8376
      71A730303032060606070000000000000000000000005C88A8CA8B7DB9FFBCBE
      CBFF4B8BCDFF5C82AEFFB7B5B4FF9D9A98FFAA9A8EFFFDCCAFFFFDCFB4FFFFE0
      C6FFFEE2CBFFFFE6D2FF52958AFD2F2F2F317E7D7B8FDC954BFFE3872CFFF1C4
      96FFF1CFADFFE3892DFFE3882CFFEFBE8EFFF1C39AFFE17D27FFE17925FFEFC0
      9CFFF1C39FFFE17523FFDB833BFF8D8B8A9F000000001010111171647777605B
      77E54A464C4C040404056A625D782E2E2D2F6E7B7B955CB1B6EF5CB1B6EF5CB1
      B6EF5CB1B6EF5CB1B6EF6D9396C200000000BA8575CCFCC8ADFFFBBC9DFFFBC3
      A9FFFFDBC6FFFFC5ABFFCDB5AFFF98BAC9FF9ABAD2FFDAE5EFFFFABBA4FD6865
      638024242425010101020000000000000000262626273C7FDBFEB1B2E6FFFDE0
      D3FFC2B5B4FFAEADACFFD7C2A8FFF8E0B4FFDBBFA6FFFBD7BFFFFDCDB5FFFDD2
      BBFFFEE6D3FFEDDFC2FF4F7E75CF030303044949494DE19343FFE3882CFFF9EA
      DAFFE7A255FFE38D2FFFE38C2EFFF0C190FFF1C59CFFE28229FFE17C27FFE48A
      3FFFFBEFE6FFE17523FFE08031FF5757575D000000001010111171647777605B
      77E54A464C4C040404056A625D782E2E2D2F7388889F69F7FFFF69F7FFFF69F7
      FFFF69F7FFFF69F7FFFF73AFB2CF000000003A3A3A3BF2E0D3F3FCE4D7FFF2AD
      94FFF39875FFFDC2A7FFFFC0A4FFFFCCB1FFFFEBD5FFFFFCF2FFD19E8AEF5757
      56681E1E1E1F000000010000000000000000657177816695E5FFF5E2E0FFFDDB
      CAFFE9DBD2FFE6C2AFFFFDD0AFFFF5D1B6FFE2C2B0FFFCCBB4FFFEDCC7FFFFE9
      D8FFFFEBDCFFA1BDC7FF5E6366780000000001010102CA975DDDE38E30FFF9EA
      D9FFE9AA5CFFE49634FFE49433FFEDBF8BFFECB984FFE3872CFFE28229FFE58F
      44FFFAEDE4FFE17523FFD18748E905050506000000001010111171647777605B
      77E54A464C4C0404040573696085514E4952737D7A955CB1B6EF5CB1B6EF5CB1
      B6EF5CB1B6EF5CB1B6EF6D9396C200000000000000004D4C4B4EFCEFE3FCFDF4
      EEFFF6AD8EFFFFDCC3FFFEDEC6FFFDCEB6FFFED4BEFFFFF4EAFFBD8976E55151
      515E1B1B1B1C0000000000000000000000006E8694A16FC0EAFFF0DFDAFFFDE0
      D4FFFCDDCFFFD4BDB2FFE0C4B7FFE9D4C5FFFDDBC7FFFEDECBFFFDE1D2FFFEE7
      D9FFFFF2E8FF5996BEF9222222230000000000000000877A6B91E59634FFEFC8
      95FFF6DDBAFFE6A23BFFE69F39FFECB872FFECB778FFE38C2FFFE2862BFFF3CB
      A7FFEFBF98FFE17523FF967F6AA100000000000000001010111171647777605B
      77E54A464C4C040404057B5137DC6760586A737D7A955CB1B6EF5CB1B6EF5CB1
      B6EF5CB1B6EF5CB1B6EF6D9395C2000000000000000000000000716D6972FFF1
      E5FFFCBE9DFFFFD1B0FFFFDEC2FFFFE4CCFFFFE6D0FFFFF3E9FFB98774E24D4D
      4D581818181900000000000000000000000005050506575C60646B99B2CA7CB6
      D8FEB0CEE1FFCFD7DDFFE0DBD8FFE4D2C9FFFDD8C7FFFCCDB9FFFDDAC9FFFFF2
      E8FFDCD9DAFF607E8EBF0101010200000000000000001A1A1A1BD8A04EEEE7AA
      42FFF4E1BEFFF7E4C1FFEBBA60FFE6A43EFFE49B39FFE8A14FFFF4D3B2FFF3D8
      C0FFE2812DFFD98036F42424242500000000000000001010111171647777605B
      77E54A464C4C0404040580685BB2403E3C41707E7D9561BDC3EF61BDC3EF61BD
      C3EF61BDC3EF61BDC3EF70999BC2000000000000000000000000000000009996
      939BF6AF91FFFDD6BEFFFFE7CEFFFFE2C5FFFFE2C5FFFCE1D0FF9F786CCD4848
      4850151515160000000000000000000000000000000000000000000000001B1B
      1B1C4D515356636E747B6977808B6A7B869475AACAF3D0D8DEFFFCF2ECFFFFFC
      F9FF9EC5DEFF56595A66000000000000000000000000000000003B3A393DD9B1
      57EDEAC24DFFEDD585FFF4E6C4FFF6EAD6FFF6E7D5FFF3DBBFFFE9B073FFE285
      2CFFD8873BF2454442480000000000000000000000001010111171647777605B
      77E54B474D4D1515151674686F802D2D2D2E7E8695A462E7EFFF62E7EFFF62E7
      EFFF62E7EFFF62E7EFFF70A8ACCF000000000000000000000000000000000202
      02037A6C687FB17F72C3DA947FF2F1B9A6FFF8D7C6FFF7D5C5FF9F7A6FBD3535
      35380E0E0E0F0000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000131313145E666A70738F9FB27E9F
      B2D06F8FA0BB0E0E0E0F00000000000000000000000000000000000000001B1B
      1B1C968D729FE4CE5DF7EBC950FFE8B646FFE6A53CFFE59835FFDE9039F99B85
      6CA6212121220000000000000000000000000000000010101111716477775A58
      72E87E6D86897A6A808388718F9776687B7D7F6D9AB42A4693EF294692EF2946
      92EF294692EF294692EF566486C2000000000000000000000000000000000000
      000000000000000000001C1C1C1D5A54525D90766F9ABF7D6AD67F6F69891010
      1011040404050000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000B0B0B0C40403F435B5955625B595562434241460E0E0E0F0000
      000000000000000000000000000000000000000000000F0F10106B6070707865
      8DD678658DD678658DD678658DD68D719FC07C6C8A93676785A06065809F6065
      809F6065809F6065809F5F616D8100000000424D3E000000000000003E000000
      2800000040000000400000000100010000000000000200000000000000000000
      000000000000000000000000FFFFFF00800FE000000000000000C00000000000
      0000800000000000000080000000000000008000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000C00000000000
      0000FE00000000000001FE0300000000F80000000000FFFDC00000000000FC78
      8000000000000000800000000000000080000000000000010000000000000001
      0000000000000001000000000000000000000000000000000000000000000000
      0000000000000000000000000000000100000000000000018000000000000001
      FC0000000000FFFFFE0300000000FFFF8001E07FFFFFFFFF8001E007FF0F0000
      8001C000FE0700008001C000FC03000080018000F80300008001800080010000
      8001000100000000800100030000000F800100070000000F8001800F0000000F
      8001E00FE000F00F8001E00FF001F00F8001E00FFC07F0FF8001E03FFC0FF0FF
      8001F3FFFF3FF0FF8001FFFFFFFFFFFF8000FFFFF81F80018000E3FFE0078001
      0000E1E3800180010000C060800180010000C000000080010001C00000008001
      0001800000008001000380000000800100038000000080010003000000008001
      00030001000080018007000180018001C007000180018001E007E003C0038001
      E007FF03E0078001FC07FFFFF81F800100000000000000000000000000000000
      000000000000}
  end
  object BalloonHintSearch: TBalloonHint
    Images = ImgListSmallSearch
    HideAfter = 750
    Left = 187
    Top = 713
  end
  object ImgListLargeSearch: TImageList
    ColorDepth = cd32Bit
    DrawingStyle = dsTransparent
    Height = 32
    Width = 32
    Left = 296
    Top = 705
    Bitmap = {
      494C010105000800040020002000FFFFFFFF2110FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000800000004000000001002000000000000080
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000040404051E1E1E1F2F2F2F3126262628181818190909090A0303
      0304000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000010E0E0E0F2020
      20212A2A2A2C1D1D1D1E06060607000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000001010102353535388B7D76AE887B74B46F6C69905958586A424242483131
      31341B1B1B1C0D0D0D0E03030304000000000000000000000000000000000000
      000000000000000000000000000000000000060606071B1B1B1C5B5E62735E6D
      82A9606976A15A5A5B702D2D2D2F070707080000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000034333336C59A86D7F4AB84FFF5B18EFFF5AF88FEE2A685F7B0907ED98A7C
      74BC6D6A68925F5E5D734545454C323232351E1E1E1F11111112060606070101
      0102030303040F0F0F101919191A212121225A5B5C6E55637ECB1A55A0FF0881
      DCFF00ABFFFF1D87C6EE5D5E5F78232323240000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00018B7D779BEDA179FDF8D5C3FFFCEBE1FFFADDCEFFF8C9B0FFF6B894FFF5B0
      88FEE0A886F3C99B82E6928079C86E7074A95D5E60784F4F505C3B3B3B3F2626
      2628343434375A5C5F705E60637C656871A9395279EF2A4B7EFE2F568DFF2D63
      A1FF03C2EBFF00E5FFFF5C707DB0323232350000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000003A3A
      3A3DED9C75FDF6C6B1FFFFFFFFFFFFFEFEFFFFFEFEFFFFFFFFFFFFFEFDFFF0E8
      E7FFB4BDC1FF54BECAFF02D9F2FF00E0FFFF00C4F6FE19A0D1F154778EC9676E
      78AF267FC4E900A0FEFF0098F0FF0F6DB3FF2D538DFF3363A0FF3C79BBFF488D
      D4FF33A9D6FF20F8FAFF558692C12B2B2B2D0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000005050506897A
      749AF0A886FFFBEEE8FFFFFEFDFFFFFEFDFFFFFEFEFFFFFFFDFFBBD1F0FF4DA2
      F0FF19E2F7FF00E4FFFF46BDD3FF7BB2B7FF7DB5B7FF57C2CBFF0CC7F4FE0E99
      E3FD0098E3FF00C4F7FF00CBFFFF00D5F7FF2482BFFF417DC4FF4C99E6FF50A3
      F1FF4A99D5FF67ECF2FF646E7692141414150000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000003737373ACE91
      76E2F6CFBEFFFFFFFEFFFDFCFBFFFEF0EAFFFAE2D8FF96A8CDFF0081F5FF12CD
      FEFF19DEF7FF8DA0ABFFFFA474FFFFB082FFFFAE81FFFFA676FFDAA586FF53C6
      CEFF00A1F1FF007BE0FF04D4F8FF04DCFEFF4DD9F1FF4D9DE9FF4B96E0FF3E79
      BDFF426A9BF66E8397B618181819000000010000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000006D666476E790
      6BFCFCF3F1FFFFFDFBFFFEFCFAFFFCC1ABFFD39083FF248ADEFF01A6FEFF22EB
      FEFF44B1D7FFEA9171FFFA9E74FFFAAC82FFFCBB8DFFFCBE91FFFEB085FFEBA4
      7CFF3DC4D9FF009BEBFF37C2E5FF15E0FAFF42DEF9FF419BD5FF2C5E9EFF3A57
      80ED5E6063761C1C1C1D00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000004040405C38C75D6F0AE
      95FFFFFEFEFFFFFBF8FFFEF1EBFFFFC6AFFF8CA0BDFF00A8FAFF08C2FEFF21EE
      FFFF8996ADFFFD8F67FFF8906AFFF88F69FFF8906AFFF8956EFFF99F76FFFAA1
      76FFDDA280FF2EC5E4FF0E95E2FF05C0EEFF00D1FFFF1E93BCFF928485EF5B5B
      5A69050505060000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000027272728E38563FBF5CF
      C1FFFFFCFBFFFFFBF7FFFCE2D7FFFFBCA1FF63A6CEFF00BFFEFF0AD6FEFF24EE
      FFFFA196A1FFFCA074FFF8936CFFF88C67FFF88E69FFF8906AFFF8906AFFF991
      6BFFFA916AFF87B7AEFF00A5F2FF009FE6FF00AAFDFF72A0BEFF837C76991B1B
      1B1C000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000066605E70EA8D69FFFAE8
      E1FFFFF9F3FFFFFAF6FFFAC5B1FFFFB698FF60B2CEFF00DDFEFF05EDFEFF2AF7
      FFFF81A3BCFFFFD6A5FFFEE7BBFFFDD7AEFFFABA92FFF9A57DFFF8976FFFF891
      6BFFFA8F68FFE09A78FF01C1F8FF0886DFFF658DBFFDA19087CA1B1B1B1C0000
      0001000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000006060607937B72A5EB9B7CFFFCF3
      F0FFFFF7F0FFFFF8F2FFF9A88CFFFF966EFF78A4AEFF00EEFDFF06FCFEFF30FF
      FDFF59AFD4FFEEC79FFFFFF8CDFFFFF6CBFFFEECBFFFFEE2B3FFFDCEA0FFFCBA
      8EFFFB9F76FFFB946CFF0FC6F2FF699DC0FFD8A88BEE5F5D5C6D060606070000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000020202021B9816DCEEFB6A2FFFEFB
      F7FFFFF3EBFFFFF7F0FFFDDACDFFFEB79BFFB9A8A4FF1EE7F1FF27FEFDFF3DFE
      FCFF3BDEF6FFA7A7AAFFFFEEBEFFFFF5CAFFFFEDC0FFFFE6B7FFFFDDACFFFED3
      A1FFFDB88BFFF7A177FF0BC8F4FF7AA5B9FF918178B022222223000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000033323235C9785EE2F4C9BBFFFFF7
      F2FFFFF1E8FFFFF5ECFFFDE5D8FFFBBCA4FFE4B2A4FF51CBDCFF47FFFDFF57FD
      FAFF4FF9FCFF3EB9E4FFE8B896FFFFE6B4FFFFE8B8FFFFE2B2FFFFDAA7FFFCCC
      9BFFFEAF82FFD3A288FF00CEFAFF90A6AEFE595757650B0B0B0C000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000514E4D55D96D4BF7F8E2DBFFFFF4
      ECFFFDF0E4FFFCDACAFFFDDCCBFFFAC2ACFFFDB89EFFB9ABAEFF60EDF7FF81FD
      FAFF8CFCF8FF59FCFDFF43B3DFFFC2A698FFFEC795FFFFCD99FFFEC593FFFEB5
      86FFEA9F7CFF4FBCCFFF18CCE9FF988B87D72626262801010102000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000072676479DD6B48FEFBF1EDFFFFF1
      E5FFFEEEE0FFFAC1AAFFF99D7AFFF89A76FFFAA07DFFF7A98DFF8BB2C7FF92F5
      F9FF96FCF9FF79FDF9FF41F5FCFF3BCAEBFF83A0B6FFC39E94FFD69F8AFFBC9B
      93FF47B8D4FF01EAFCFF66A4B6FE837772A91515151600000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008D756E9ADF704DFFFEFBF8FFFFEB
      DCFFFFEADBFFFFEFE2FFFEECDEFFFDDECCFFFAB79DFFF99B77FFED9072FF93A1
      AFFF54EDF5FF42FDFDFF2AFEFDFF27FFFDFF24F5FFFF17E5FFFF0BE3FFFF01E3
      FEFF19E4F6FF64B0C3FFD79073F0615F5E740808080900000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000A27D72B0E68363FFFEF5F0FFFFEA
      D9FFFFEADAFFFFEBDBFFFFECDDFFFFEEE0FFFEEBDDFFFBCBB6FFFBAF92FFF1A8
      8EFF91A9B5FF27D1E7FF00F5FFFF00EFFFFF04DAFEFF0ACBFFFF1CBBF1FF63CA
      E6FFC9E3F2FFEFB9A5FFBC8973E14D4C4C550202020300000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000AA7F70B7ED8864FFFBBCA1FFFBBE
      A1FFFCC8AEFFFCC5ACFFFDD5C0FFFEE2D1FFFFEBDCFFFFF0E3FFFDD8C5FFFBC0
      A8FFFFB89CFFF0AD99FFA4A5AEFF76A6C1FF69A1CDFF8E8FAEFFE6C4C0FFFFFA
      F0FFFEF5F2FFF1AA8DFF967C70C3333333360000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000004A48484FD59781E7F7B996FFFCBF
      99FFF8AC89FFF69974FFF99974FFFAA281FFFCB99CFFFBCCB5FFFEE4D4FFFEEA
      DBFFFDDDCBFFFDD2BDFFFECEB7FFFFD6C3FFFCE7DAFFFFEBDBFFFFF0E5FFFFF5
      EEFFFBEEE9FFEFA07DFF85766EAC262626270000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000005857575AF3EEEBF5FEF2
      E8FFFCDEC9FFF6C2A7FFED9B78FFE9845FFFEE8661FFF89670FFF99A76FFF9A3
      82FFFAB99EFFFDD0BBFFFEE4D4FFFEEDDFFFFFF2E5FFFFF2E6FFFFF0E7FFFFF4
      ECFFFAE6DEFFED9571FF706A678A1919191A0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000001010102918A8591FAEE
      E4FBFFFDFDFFFEF9F5FFFAE8E1FFF0BCA8FFE16D49FFF6A485FFFDD1B9FFFBCC
      B4FFFAB698FFF9A484FFF89C7AFFF9A688FFFBC3ABFFFCDDCBFFFFEFE3FFFFF4
      EAFFF8DFD5FFEB8D66FF605E5D73121212130000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000F0F0F109089
      8397FFF7F1FFFFF3EAFFFFECDEFFFFFFFFFFEA926FFFF6A382FFFED8BFFFFFE5
      CFFFFFE8D4FFFFE9D5FFFEE0CCFFFBCEB7FFFAB093FFFAAB8BFFFFEADBFFFFF6
      EFFFF5D0C2FFE2845FFC5352525F0C0C0C0D0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000001111
      1112CBBBAFCBFFFAF5FFFFF4EBFFFFFDFCFFF0A584FFF6A684FFFED5BBFFFFE1
      C9FFFFE1C9FFFFE2CCFFFFE6D2FFFFE7D5FFFEE7D5FFFEE6D5FFFFE9D8FFFFF6
      EFFFF4CABCFFD17E5EF4494948510909090A0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000024242425C4B6ACC5FFFDFCFFFFFEFDFFF6B996FFF8AA86FFFED2B3FFFFDD
      C0FFFFDDC2FFFFE0C5FFFFE0C8FFFFE3CBFFFFE3CFFFFFE6D2FFFFE6D3FFFFF8
      F1FFF1BBA9FFC4775DEC40404046060606070000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000135343436F4E6DDF4FFFFFFFFFBC6A4FFF9AA85FFFECEADFFFFD9
      BAFFFFDBBEFFFFDCC0FFFFDEC4FFFFDEC5FFFFE2CAFFFFE3CCFFFFE3CDFFFFF7
      F0FFEFB19CFFB8745BE43D3D3D42060606070000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000056555459EAE8E6ECFCCAA8FFFBB494FFFED4B8FFFFD8
      B8FFFFD5B5FFFFD6B6FFFFD8BAFFFFDABFFFFFDCC3FFFFDFC4FFFFE0C7FFFFF6
      EEFFEEAF9BFFB77059E53D3D3D42060606070000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000070707087372727AF3AB8AFFF5A385FFF9DDD3FFFEF6
      EFFFFFF2E5FFFFE5CFFFFFD9BDFFFFD7B7FFFFD8B9FFFFDABEFFFFDDC4FFFFF6
      F0FFEA9F87FFB76E57E53D3D3D42060606070000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000776B6882CC846DDAD45A39F8DA64
      45FEE89A86FFF0C0B4FFF8E1DCFFFBEFE8FFFFEEE0FFFFE6D2FFFFDFC5FFFFF7
      F0FFE79175FFB66C54E53D3D3D42060606070000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000070707082B2B2B2D5852515B8C71
      6A96BE6B53D9D55635FCDD6647FFE38165FFEDB0A0FFF4D3C9FFFDF7F3FFFAEE
      E9FFE17251FFB56C55E43B3B3B3F050505060000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000011F1F1F205F5A58688E726A9EBA725CD1CA6448EADA623FFEDB5F
      3CFFDC5F3BFFAC7361D123232324010101020000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000003030304232323243D3C3B3F7A6B6680A57A
      6CB6B97863D1645E5B6D08080809000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000001010102141414152727
      27292A2A2A2C212121220F0F0F10050505060000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000001010102181818192A2A2A2C272727291919191A0909090A0303
      0304000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000010606
      0607131313141F1F1F20252525262A2A2A2C2A2A2A2C25252526202020211414
      1415070707080000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000050505061A1A1A1B2A2A
      2A2C2C2C2C2E2020202106060607000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000001C1C1C1D756D698B8775
      6FAE7B6F6BA0676463824C4C4C56363636391717171805050506000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000202020218177729D887B74B16F6C69905959586B4343434A3131
      31341C1C1C1D0E0E0E0F04040405000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000121212133A3A3A3E655F
      5E797C6965A3866A62B88C6B61C4936D5FCE87685EC1826962B77566639F605D
      5D784A4A4A532B2B2B2D0E0E0E0F000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000F0F0F103B3B3B3F7474729F7675
      75B2707070A65C5C5C742D2D2D2F070707080000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000011919191AAC8D81B7FFCBA9FFFFCF
      ABFFFEBB97FFFAA784FEC38971E587736DB96260607B4444444B1A1A1A1B0404
      0405000000000000000000000000000000000000000000000000000000000000
      00001D1D1D1EA68C81BBF5AB84FFF5B18CFFF5B088FEE8AA86F9B18F7CDB8C7D
      73BD6E6B69945F5E5D744646464E343434371F1F1F2011111112060606070101
      0102000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000070707084A4948518A6D66B1C86E53F0F28E
      67FFFDAA84FFFFC29CFFFFD2ABFFFFE1B9FFFFEAC2FFFFEBC4FFF9CCA8FFDE91
      6CFCA36756DF716462A4535252612828282A0606060700000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000002020203080808090E0E0E0F0E0E0E0F0909090A04040405000000000000
      0000070707080C0C0C0D131313143737373B6565669F414142EE595757FF9F9F
      9EFFBFBDBBFF969593ED605F5F7B262626270000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000060606071C1C1C1D4F4E4E58CD9D89DEFFDCBBFFFFD9
      B8FFFED5B4FFFECFACFFFCBC98FFF6AA86FCBF8A72E484716CB35050505D2828
      282A030303040000000000000000000000000000000000000000000000000000
      00006B666476E69D78F7F7CAB4FFFCEAE1FFFADECFFFF8CBB3FFF6B996FFF5B1
      8AFEDFA789F4C69E84E6A08979CC807872AA6262617B4F4F4F5B3939393D2727
      2729131313140909090A00000001000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000A0A0A0B7A6A6691DB6C4BF8FE966FFFFEAE89FFFCBD
      97FFF8C29CFFF5BF99FFF4BE97FFF2BE98FFF2BE98FFF4C9A5FFF9E0BDFFFEEE
      C6FFFFDDB5FFF19B75FD995F50DB646060843232323504040405000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000002020203000000010000000000000000010101020B0B
      0B0C2828282A4646464D525252605252525F4444444B31313134161616171515
      1516434343495050505C62626287555457CD302D30FB352B2FFF473438FF594D
      4FFFC8C8C7FFD5D4D3FF757574B8353535380000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000006060607605D5C6DA9887CC6D49D86EBEEA98AF9FCB592FFFAB4
      93FFFED1B0FFFFD7B6FFFFD5B4FFFECCA9FFFCB894FFFDAE89FFA87E6ED76462
      6281212121220101010200000000000000000000000000000000000000001D1D
      1D1ED9997CECF4BA9DFFFEFEFFFFFFFEFEFFFFFEFEFFFFFFFFFFFEFBFAFFFDE7
      D9FFF2B49CFFC18B92FF4E49BAFF4945BCFFDDA794FED4A889ED9D897CCB7A74
      6FA866656481545353613A3A3A3E2929292B161616170A0A0A0B020202030000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000007E6C6791F67852FFFFA883FFFAC6A0FFF6CEA7FFF3C7
      A1FFF2BF99FFF2BA94FFF3BC96FFF2BD97FFEEB38DFFEBA882FFE6956DFFE386
      5FFFE99972FFF9BF99FFFFB48DFFB2604AEA6360608023232324000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000001202020214343444A3737373B1E1E1E1F1A1A1A1B4545454C6D6D
      6C8E939191DEAFAEADF8B4B4B3FCAAA9A8F8878585DD717070B4646464847F7F
      7EB8A3A19FF99D9B9AFA6A6768FF3D3438FF4B373BFF614348FF85555BFF9C5E
      64FF988C8EFFECEEECFF858584CA333333360000000000000000000000000000
      0000000000000000000000000000040404050909090A05050506000000000000
      0000020202035251505AE8B196F1FDD5B9FEFFDDC2FFFFDBC0FFFED8BBFFFCD0
      B2FFFDD3B5FFFFD8BAFFFFD7B7FFFFD7B5FFFDCAA7FFFCB995FFF6AA87FC9879
      6EC83939393D0505050600000000000000000000000000000000000000006662
      6071F09E78FFFAE2D8FFFFFEFEFFFFFEFDFFFFFEFEFFFEF7F4FFFFD7C3FFDAA9
      A9FF5954BBFF1636DFFF0032FBFF002FFCFF544FB6FFEBBFA3FFF9BE97FEEFB6
      92FAD2A98CECB19784DB887F77B6736F6C95555555654444444B2C2C2C2E1212
      1213000000000000000000000000000000000000000000000000000000000000
      00000000000044424248EA704FF7FDBB96FFF9E2BBFFF8D1A9FFF9B791FFFBB3
      8EFFFBBB95FFFDC6A0FFFDD2ACFFFEDEB8FFFEEFC7FFFFFBD4FFFDF6CFFFF7D0
      AAFFEB9C75FFDE6E4AFFEA8962FFFD9B72FF906256CF4545454C050505060000
      0000000000000000000000000000000000000000000000000000000000000000
      000017171718677D8AA054809ED162727CAB6061617B6E6E6D96969494DEC1BF
      BEFAD0D2D2FFD9CBC6FFE0C9C0FFE0CBC2FFD6CFCDFFB8BBBCFB8A8988EDA2A0
      9FFCCFCECCFFD0CECDFFBFBDBCFF928A8BFF71484EFF925C62FFBB7179FFD480
      87FF987277FFE6E7E6FF7F7E7EB8222222230000000000000000000000000000
      000000000000020202032D2D2D2F555353605B59596B494949522E2E2E301B1B
      1B1C4746464CD7A591E2FFE5CEFFFFE1C8FFFFE0C6FFFFDFC5FFFFDEC3FFFFDD
      C2FFFFDCBFFFFFDBBDFFFDD7B8FFFECBAAFFFDC3A1FFFBBB98FFFCB995FFD294
      7AE93737373B050505060000000000000000000000000000000022222223BD8E
      7BCEF3BDA6FFFEFBF9FFFFFDFCFFFEFCFAFFFDE2D8FFF7BFABFF9777A9FF3B57
      D6FF0E46FFFF083CFFFF0A3EFFFF0A3DFFFF0536F4FF606DD7FFFAF7F4FFFDEA
      DDFFFCD9C2FFFDCFB1FFFDC7A1FFFFC99EFFD7B198F49F8E8CDE797470A85252
      525F0D0D0D0E0000000000000000000000000000000000000000000000000000
      0000000000008A70699AFCB891FFFCE6BFFFFAB08BFFFA9D77FFFAA681FFFBB1
      8BFFFBBB96FFFCC6A0FFFCD0AAFFFDDCB5FFFDE9C2FFFFF8CFFFFFFCD5FFFFEE
      C7FFFFE1B9FFF9BF9AFFE37A56FFE9724EFFC66A4FF055545363080808090000
      0000000000000000000000000000000000000000000000000000000000000000
      00005F666B762D9BD9F80DC1FDFF24ABE2FF8B9399FBB2B0ADFFDCDBDBFFD2CE
      CBFFEAA98FFFF9A077FFFBA578FFFBA277FFF9A27BFFF4B9A2FFD8CDC9FFA5A5
      A4FF8E8B8AFFB8B6B4FFD9D8D7FFDBDDDCFFB58D90FFCB7882FFC37580FF9D62
      69FF695357FFADACACEC43434349060606070000000000000000000000000000
      00000000000028282829A9897DC4CEA693E7C59A88E49F7E72CD726B67976461
      607BA38579C4FBD3BAFDFFE3CCFFFFE1CBFFFFE0C8FFFFE1C8FFFFE0C5FFFFDF
      C5FFFFDCC1FFFFDDC0FFFDDABDFFFECAAAFFFBB895FFFCB794FFFDB794FFB18B
      7CC81919191A0000000100000000000000000000000000000000514F4E56DC8D
      6AF2F9E3D9FFFFFDFCFFFFFDFBFFFCEAE2FFFDBEA4FFB289A4FF3865E8FF609E
      FBFF376EFEFF0D41FFFF1145FFFF0F43FFFF0D43FEFF0934E8FFAEAEDDFFFFFF
      FFFFFEFDFEFFFFEDE4FFFAC5A9FFBF8E96FF4647C0FF2334DEFF89769FF5726F
      6C991D1D1D1E0000000100000000000000000000000000000000000000000000
      000005050506A57F73B5FEE4BDFFFA9F78FFFA966FFFFAA27CFFFAA984FFFBB2
      8CFFFBBB96FFFCC6A0FFFCD0AAFFFDDCB5FFFDE9C2FFFFF7CFFFFFFAD2FFFDE9
      C2FFFDD8B1FFFCCBA4FFFDBD98FFEB7B57FFBF563AF255555464080808090000
      0000000000000000000000000000000000000000000000000000000000000A0A
      0A0B4E97C1D91DA1E8FF1CBCF2FF69A4B3FFB6B0ACFFC8C7C6FFD8D7D5FFDEAF
      9CFFFCAA7CFFFCBB8EFFFBC092FFFCBD90FFFAB286FFFBA679FFF6AD8EFFDDCD
      C8FF959593FF9B9998FFDDDCDBFFDFE0DEFFD9C7C9FFAF6E74FF774F54FF4333
      37FF6B6A6BCA5353535D04040405000000000000000000000000000000000000
      000011111112AC8D82B6FFE4CFFFFFEBD8FFFFEBD8FFFFE6D2FFFDCFB6FEFEC1
      A5FFFFDDC7FFFFE7D2FFFFE4D0FFFFE3CFFFFFE4CDFFFFE3CCFFFFE2CAFFFFE1
      C8FFFFE0C6FFFFDDC4FFFFDDC2FFFED8BBFFFBBC9AFFFAA582FFB28270D94D4C
      4C56020202030000000000000000000000000000000000000000A58679B3ED9C
      7CFFFFFFFFFFFFFAF7FFFFFCFAFFFEEBE4FFFDBCA2FFBA8EA3FF578CEAFF80BC
      FDFF81BDFCFF3A71FEFF164BFFFF194DFFFF184CFFFF154CFFFF1E42E1FFB2AF
      DCFFFBD0B8FFCD9BA3FF3A40C4FF022DEEFF0032FFFF0031FFFF0D2EE4FE5B5B
      7CC44646464E1313131400000000000000000000000000000000000000000000
      000006060607A68174B6FCAD89FFF9916BFFFA9C75FFFAA17BFFFAA984FFFBB2
      8CFFFBBB96FFFCC6A0FFFCD0AAFFFDDCB5FFFDE9C2FFFFF7CFFFFFFAD2FFFDE9
      C2FFFDD8B2FFFCC8A2FFFCBA95FFFEA984FFC56549F155545464080808090000
      000000000000000000000000000000000000000000000000000000000000575B
      5E6612B1F3FF0CB3F5FF45A3CEFFADAFAFFFBEBCBBFFD8D7D8FFD3C4C0FFF2A6
      83FFFDCB9BFFFED7A4FFFFD8A6FFFED5A3FFFECB9BFFFBBE90FFFBA97CFFFAA7
      86FFD0CBC8FFA1A09FFFC3C3C2FFD4D3D2FFD4D1D0FF5A4F52FD585859CD5B5B
      5B70080808090000000000000000000000000000000000000000000000000000
      000028282829D0A998D5FFEDDCFFFFE7D5FFFFE7D5FFFFE9D7FFFFEAD8FFFFE9
      D7FFFFE9D6FFFFE6D3FFFFE7D2FFFFE6D2FFFFE4CFFFFFE5CDFFFFE4CDFFFFE3
      CAFFFFE0C8FFFFE0C6FFFFDFC5FFFFDCC2FFFDC4A3FFFDBF9EFFA47F70D24D4D
      4C5706060607000000000000000000000000000000000909090AD1886BE7F2BB
      A7FFFFFEFDFFFFF9F5FFFFF9F7FFFFFCF9FFFDD1C1FFF7BAA1FF7B72B5FF76B1
      F3FF88C4FDFF7AB8FCFF2359FEFF1D52FEFF1F54FDFF1D52FEFF164CFAFF3748
      CDFF8B6EA4FF283ED4FF083CFBFF083EFFFF0537FFFF0034FFFF0031FDFF152F
      C7F56262678F3838383C03030304000000000000000000000000000000000000
      000005050506A5796CB5FA936DFFF99771FFFA9B75FFFAA17BFFFAA984FFFBB2
      8CFFFBBB96FFFCC6A0FFFCD0AAFFFDDCB5FFFDE9C2FFFFF7CFFFFFFAD2FFFDE9
      C2FFFDD8B2FFFCC8A2FFFBB893FFFFAE88FFCC7055F155545464080808090000
      00000000000000000000000000000000000000000000000000000F0F0F106685
      99B10ABFFCFF07BDFDFF6198B9FFBEBBB8FFC5C4C2FFDCDBDCFFD6BFB5FFF6B2
      89FFFEDAA8FFFFE0AFFFFFE0B0FFFFDEADFFFDD8A6FFFECD9CFFFBB98CFFFBA3
      77FFEFBEABFFAFAEAEFF9C9B9AFFCAC9C8FFB8B7B6F96E6E6EB52E2E2E300404
      0405000000000000000000000000000000000000000000000000000000000000
      00000B0B0B0CA78C82A9FEE8D8FFFFECDCFFFFEBDBFFFFEBDBFFFFE9D9FFFFE9
      D9FFFFEAD7FFFFE8D8FFFFE9D7FFFFE8D6FFFFE7D3FFFFE5D3FFFFE4D1FFFFE3
      D0FFFFE3CDFFFFE2CBFFFFE1C7FFFFDFC6FFFCC8A9FFFDC5A5FFCC9780E95D5B
      5B6E0909090A0000000000000000000000000000000043424146E8855FFFF8DE
      D4FFFFFAF6FFFFF7F2FFFFF9F3FFFFF9F5FFFEF7F2FFFCCDBCFFE8ADA0FF7674
      B8FF83C0FAFF89C7FDFF6BA7FCFF2E64FCFF265BFEFF265BFEFF2359FEFF1D54
      FDFF1347F9FF174EFEFF1448FFFF1044FFFF093EFFFF063AFFFF0033FFFF0032
      FFFF3842A4E15252546107070708000000000000000000000000000000000000
      000005050506A5786CB5FA946EFFF99771FFFA9B75FFFAA17BFFFAA984FFFBB2
      8CFFFBBB96FFFCC6A0FFFCD0AAFFFDDCB5FFFDE9C2FFFFF7CFFFFFFAD2FFFDE9
      C2FFFDD8B2FFFCC8A2FFFBB893FFFFAD87FFCB7054F155545464080808090000
      00000000000000000000000000000000000000000000000000004445454A3AA4
      D6EC0BC5FFFF05C3FFFF79A1B6FFCCC7C4FFCECDCBFFE1E0E1FFD6BFB5FFF6BA
      8FFFFFE4B5FFFFE9BBFFFFE8BAFFFFE5B6FFFFDEAEFFFFD9A7FFFDC797FFFBB4
      87FFF8A787FFD7CBC8FF9D9A99FFB3AFACFE8B8A87D041414147040404050000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000031303032E4B09AE8FEE5D4FFFFEEDFFFFFEEDFFFFFEEDFFFFFF0
      E1FFFFECDCFFFFEBDAFFFFE9DAFFFFE8D7FFFFE9D8FFFFE8D6FFFFE7D2FFFFE6
      D1FFFFE3D0FFFFE2CEFFFFE1CAFFFFE1C9FFFCCAACFFFDC7A8FFCE9883E95957
      576706060607000000000000000000000000000000006B656278E98E6BFFFAEB
      E5FFFFF7F0FFFFF7F1FFFFF8F2FFFFF7F2FFFFFAF5FFFEF2EBFFFCC0A7FFD8A0
      9FFF5D7DD4FF84C0FDFF7CB9FDFF538DFCFF2C63FEFF2B63FEFF285EFEFF265D
      FEFF2257FEFF1E52FDFF184DFFFF1349FFFF0F41FFFF0A3EFFFF0338FFFF0032
      FCFF50579CC93636363901010102000000000000000000000000000000000000
      000005050506A5796CB5FA946EFFF99771FFFA9B75FFFAA27CFFFAAA86FFFBB4
      8FFFFDBE99FFFECAA4FFFED6AEFFFFE2B9FFFFEEC6FFFFFCD3FFFFFED6FFFDEB
      C5FFFDD8B2FFFCC8A2FFFBB893FFFFAD87FFCB7054F155545464080808090000
      00000000000000000000000000000000000000000000000000006777818C19B5
      F2FE10C6FFFF09C6FFFF71A8BEFFD1CCCAFFD5D4D3FFE2E1E1FFD6C8C3FFF2B6
      90FFFFEBBCFFFFF0C5FFFFEEC2FFFFE9BBFFFFE2B1FFFFDCABFFFECF9EFFFCBB
      8EFFFAA37BFFE7CBC0FF999B9CFF6E8A9FFA6A6D70A54F4F4F5B303030321919
      191A040404050000000000000000000000000000000000000000000000000000
      0000000000000000000021212122776D697DA28A82A6A28A81A7AD8F85B1DAAB
      98E0FEEBDCFFFFEDDFFFFFEDDCFFFFECDDFFFFEBDBFFFFEAD9FFFFE9D7FFFFE8
      D6FFFFE7D3FFFFE4D1FFFFE4CEFFFFE2CBFFFCCBADFFFDCBACFFB78B7AD94544
      444B000000010000000000000000000000000C0C0C0DA37F73B5ECA087FFFDF7
      F5FFFFF3EAFFFFF4ECFFFFF6EFFFFFF7F1FFFFF6F1FFFFF9F4FFFCE6DBFFFEC3
      A8FFB98FA4FF6185DAFF619EFEFF447BFEFF3167FEFF356CFEFF3268FEFF2F65
      FEFF285EFEFF255BFEFF2055FDFF1A4FFDFF1449FFFF0F44FFFF2040D6F36264
      83A7181818190000000100000000000000000000000000000000000000000000
      000005050506A5796CB5FA946EFFF99771FFFA9D76FFFDA47DFFFFAB7DFFFFAE
      7CFFFFAE7DFFFFAF7BFFF9B284FFF4B68DFFFFC895FFFFDEAAFFFFEDBAFFFFE9
      B9FFFFDDB4FFFCCBA6FFFBB994FFFFAD87FFCB7054F155545464080808090000
      0000000000000000000000000000000000000000000004040405529BC2D919C4
      FAFF17C8FFFF10CAFFFF54A8CBFFD3CFCDFFDEDDDDFFE3E3E2FFDDDBDAFFE1AC
      93FFFFE8B8FFFFF9CFFFFFF3C8FFFFEDBFFFFFE3B6FFFFDEAEFFFED2A0FFFCBF
      91FFFAA479FFE8C4B6FF9FB0B4FF49C8EAFF3CB0E1F9498EB3E461727DB26064
      6684333333360707070800000000000000000000000000000000000000000000
      00000000000000000000000000000000000102020203030303040A0A0A0B5955
      535DFED7C4FFFFF0E3FFFFEDDFFFFFECDEFFFFEBDEFFFFECDCFFFFE9D8FFFFE8
      D8FFFFE7D4FFFFE7D3FFFFE4D0FFFFE3CCFFFCCCADFFFECAABFF997E73C02E2E
      2E300000000000000000000000000000000023232324BB7F6AD1EFB29EFFFEFA
      F6FFFFF1E7FFFFF4EAFFFFF3ECFFFFF5ECFFFFF6F0FFFFF7EFFFFEF7F2FFFDD8
      CAFFF6B89FFF9679A9FF2B62F8FF194FFEFF386FFEFF3D74FEFF376EFEFF356A
      FEFF3065FEFF2B61FEFF2359FEFF1F53FEFF184CFCFF253FCDF45E5E67771717
      1718000000000000000000000000000000000000000000000000000000000000
      000005050506A5796CB5FB9670FFFF9C71FFFF9966FFF1875FFFC26964FF8F4F
      73FF683E86FF563894FF47339EFF3C30A6FF533C9CFF5B4299FF875C8CFFB67A
      80FFE39E7CFFFFB886FFFFBB8FFFFFB18BFFCB6F54F155545464080808090000
      00000000000000000000000000000000000000000000262626272BABE6FB1CCA
      FEFF1CC9FFFF18CBFFFF39A8D8FFC5C7CAFFE6E5E5FFE8E8E6FFE7E8E7FFD2BB
      B4FFFBC598FFFFF4C9FFFFF3C7FFFFECBFFFFFE4B5FFFFDEADFFFED1A0FFFCBD
      90FFFAA47AFFE6C6B9FFA5B3B4FF60DEEAFF5CE9FDFF57E0FAFF4BC3E9FB4891
      B9E8545555641616161700000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000001635E
      5C6CFEE0D0FFFFF2E6FFFFF0E2FFFFEFE2FFFFEEDFFFFFECDFFFFFECDDFFFFEB
      DBFFFFEAD8FFFFE7D6FFFFE7D3FFFFE1CBFFFECDAFFFFEC2A1FF736B698D1616
      1617000000000000000000000000000000003E3D3D41C87458E5F3C9BDFFFFF5
      EEFFFFEFE3FFFFF0E6FFFFF2E7FFFFF3EAFFFFF3EAFFFFF5EDFFFDF5EFFFFEDE
      D0FFF5B89DFFA27DA2FF1E51F3FF4580FEFF4882FEFF457DFEFF4178FEFF3D74
      FEFF376EFEFF3268FEFF295FFEFF255CFFFF3847A8E658585B6B060606070000
      0000000000000000000000000000000000000000000000000000000000000000
      000005050506A5796CB5FF9665FFE0755AFF834271FF2E1F9FFF0816C0FF0016
      D5FF001CE2FF001FEAFF0024F0FF0026F7FF0026F8FF0027FDFF0024F5FF001D
      DCFF181FB9FF603A8BFFC16F6AFFFFA472FFD07254F155545363070707080000
      000000000000000000000000000000000000000000005C62657026BEF5FF24CF
      FFFF22CCFFFF1FCEFFFF26AFE9FF8CADBCFFF2EFEEFFEFF0F0FFF2F2F2FFE3E7
      E7FFD7AF9FFFF8C396FFFFE5B5FFFFE5B5FFFFDFAEFFFFD9A7FFFEC898FFFCB4
      87FFF6A382FFDCCDC7FF96B1B4FF67E5F2FF68EEFFFF68EEFFFF69F1FEFF4DC7
      F1FF636A6F902525252600000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000023232324AE92
      87C3FFF2E9FFFFF2E7FFFFF0E4FFFFEFE4FFFFEEE1FFFFEFE1FFFFECDFFFFFEC
      DDFFFFEBD9FFFFEAD8FFFFE8D6FFFFDFC8FFFECFB1FFF7B090FC4F4E4E590A0A
      0A0B00000000000000000000000000000000665E5C6BD46A48F5F7DED7FFFFF3
      E9FFFFEDDFFFFFEFE2FFFFF0E5FFFFF0E5FFFFF3E9FFFFF5ECFFFFD8C5FFFEC0
      A2FF876BA8FF4161DCFF518DFEFF538DFEFF4F89FEFF4D87FEFF4882FEFF437A
      FEFF3B72FEFF366DFEFF2E64FEFF2960FFFF434D98DD5B5B5C731919191A0000
      0001000000000000000000000000000000000000000000000000000000000000
      000004040405AA7A69B3A55265FF251AA0FF0011C9FF0519D6FF0921DCFF0923
      E1FF0724E4FF0725E5FF0725E5FF0626E6FF0428EDFF022BF3FF0031FEFF0033
      FFFF002EFFFF0020F0FF0B1AC2FF6F3F83FFC06048F1575656670A0A0A0B0000
      00000000000000000000000000000000000006060607698191A52ACCFBFF2AD1
      FFFF27CEFFFF25D0FFFF29B7F0FF61C0D6FFD8D4D3FFF8F9F9FFF9FAF9FFF5F6
      F5FFDBD9D7FFD7AF9DFFFCB688FFFFCD9BFFFED1A0FFFEC999FFFDB588FFFCA0
      72FFE8B6A4FFD0C9C9FF86BCBFFF6DF0FBFF6EF2FFFF6EF2FFFF73F1FCFE62D6
      F1FD63727DA82F2F2F3100000000000000000000000000000000000000000000
      00000000000003030304040404050000000000000000030303049085809DFAD3
      C2FDFFF5EDFFFFF2E8FFFFF3E9FFFFF2E6FFFFF1E6FFFFEEE4FFFFEFE0FFFFEC
      DFFFFFECDDFFFFE9D9FFFFE9D7FFFDDAC1FFFDCFB2FFBC8F7DDB2A2A2A2C0202
      02030000000000000000000000000000000084716B8FD96643FCFAEDE7FFFFEF
      E1FFFFEADBFFFFEDDCFFFFEEDFFFFFEFE2FFFEE4D6FFFEC8AFFFC7949BFF5052
      BCFF427BF7FF5C9AFEFF5D98FEFF5C97FEFF5994FEFF5590FEFF4F89FEFF4983
      FEFF4278FEFF3B72FEFF346AFEFF2D63FEFF2753EAFC525681C94D4D4D581919
      191A000000000000000000000000000000000000000000000000000000000000
      0000101010117F637CC50D11B6FF0614CCFF0C1DD3FF0922DEFF0823DDFF0B1F
      D0FF0D1BC5FF0D1ABFFF0E19BDFF0F18BBFF0F18BAFF1017BAFF1017BEFF0D1B
      CAFF0921DCFF0528EEFF0027F2FF0019DAFF3D2889F76462648C2929292B0101
      010200000000000000000000000000000000202020215B99BACE32D6FFFF31D4
      FFFF2FD2FFFF2CD4FFFF2DB7EEFF62E4F8FF9BBFBBFFE5E0DFFFFEFEFEFFFEFE
      FEFFF4F4F4FFE0E5E4FFD0BCB5FFE1A891FFEFA584FFF2A380FFECA589FFDFB8
      AAFFD0CFCFFFA9AEADFF75EBEFFF76F7FFFF78F6FFFF77F5FFFF7EEDF5FC7BDC
      E4F55C798BBE3838383C00000000000000000000000000000000000000000000
      0000040404052222222331313134141414150000000136363639EFBBA7F5FEF3
      EBFFFFF5EDFFFFF3EAFFFFF3EBFFFFF4EAFFFFF1E7FFFFF1E6FFFFEEE2FFFFEF
      E0FFFFEDDFFFFFECDDFFFFE8D6FFFED7BDFFFCC5A8FE8E7B74B0171717180000
      0000000000000000000000000000000000009F7E73ACE2704EFEFDF4EEFFFFEB
      DAFFFFEAD9FFFFEADAFFFFECDDFFFEE2D1FFFCBDA1FFD19A9AFF3A51D0FF457C
      F8FF629EFDFF629EFCFF659FFCFF649FFCFF5F9AFCFF5B96FEFF538FFEFF4D87
      FEFF4680FEFF3E75FEFF376CFEFF3066FEFF275EFDFF2548D9FA62616CA14343
      43490909090A0000000000000000000000000000000000000000000000000000
      000058595F6B0910B3FF0F16C8FF0823E0FF0625E1FF0C1BC4FF1314ACFF0B15
      ACFF0419BAFF021DC6FF0120CDFF0121D2FF0123D7FF0323D5FF0620CBFF0B1A
      BBFF1213ACFF1413B3FF0F1ACCFF0A21DDFF071BD5FF454581D64F4F4F5B1111
      1112000000000000000000000000000000003232333550A6CEE239DBFFFF36D6
      FFFF34D5FFFF32D8FFFF30B6EDFF6AE4F7FFADD5CBFFD0B9ACFFE8E9EAFFFDFD
      FCFFF4F4F4FFEDEDEDFFE3E4E5FFDCDBDAFFD6CDCAFFD7CAC4FFD6D2D0FFD2CE
      CCFFAAB3B3FF85D1D4FF81F9FFFF81F6FFFF81F7FFFF81F5FEFF88E5ECF88CDD
      DFF0587E96CB3E3F3F4401010102000000000000000000000000000000000000
      0000353536384F9FC8D161717CA95555556536363639A88F87BBFEF3ECFFFFF8
      F2FFFFF5F0FFFFF4EDFFFFF6EEFFFCE3D6FFFBCCB8FFFFF2E8FFFFF1E6FFFFF0
      E4FFFEEADCFFFDECDEFFFDE4CFFFFED9BEFFE0A890F1605D5C71070707080000
      000000000000000000000000000000000000A07C72AAE77E5AFCFABA9FFFFABC
      9FFFFDC8AFFFFED5BFFFFEE4D1FFFDD6C0FFFDB694FFA77B9CFF4B86F3FF74B1
      FDFF7BB8FDFF6FACFDFF6DABFDFF6DAAFDFF69A5FDFF609BFBFF5A95F9FF6EAB
      FDFF73B0FCFF4D87FCFF386FFEFF3369FEFF285EFEFF235BFFFF2D45BCF06262
      6C9E353535380909090A00000000000000000000000000000000000000000000
      0000504D9CD11017C5FF0428ECFF0822D1FF1213ACFF1313B8FF1314B6FF0512
      A7FF0015B1FF0015B4FF0017B9FF0019BDFF001AC1FF001CC7FF001FCDFF0021
      D3FF0020D0FF0919B8FF1312A9FF1212BAFF0E1AD0FF1217B3FE63626B952020
      2021000000000000000000000000000000004D50525641BCE8F741DDFFFF3FDC
      FFFF3DD9FFFF3BDCFFFF38B4EBFF7DECF8FFB2E0D9FFFDDEC9FFCFC3B8FFCBC8
      C6FFE0DFDEFFDEDEDDFFD7D7D6FFD1D1D0FFD0CECDFFC7C5C6FFABBBBDFF94C8
      C7FF8AF2F3FF8BFAFFFF8BF6FFFF8BF6FFFF8DF7FEFF8CF3FCFF94DDE0F195DB
      DCED5786A3D54A4B4B5404040405000000000000000000000000000000000000
      00003A3A3B3E2DC2E8EA21BBE6F657778DC0776F6D9FEAC2B2F2FFFBF7FFFFF6
      F1FFFFF6F0FFFFF7F0FFFFF6EFFFFAC1AAFFFCE3D6FFFFF4EBFFFFF1E7FFFFF2
      E7FFFAC3ADFFFEEADCFFFEDCC4FFFEDABFFFB78D7DD63F3F3F44000000010000
      0000000000000000000000000000000000003B3A3A3EC89281D8F6B593FFFCC0
      9AFFF9B38FFFF7AF8EFFFAB89BFFFCC1A6FFFCB79AFFF0AE95FF646CBEFF77B5
      F8FF86C1FDFF82BEFDFF76B3FDFF76B3FDFF66A1F8FF5A6CCBFF656EC1FF73AE
      F6FF76B2FDFF65A1FCFF3C73FEFF3369FEFF2A61FEFF2459FEFF1C4EF8FE3944
      A1E55B5B5C722929292B00000001000000000000000000000000000000000000
      00002B2CABEF0329F1FF0822CFFF150FA6FF1313BEFF0F18CCFF1018BFFF060C
      96FF000B97FF010D9BFF010D9FFF010FA2FF0110A6FF0112AAFF0013AEFF0014
      B1FF0016B8FF001AC0FF0318B6FF1211A4FF1313BCFF1315C0FF605F74AD2222
      222300000000000000000000000000000000616B727941C9F3FE48E0FFFF45DF
      FFFF42DCFFFF42DEFFFF3BB4EAFF86EDF9FFC3D5CBFFFEE8D9FFFCE7D6FFE8CC
      BCFFCCC6BEFFBEBEBAFFB6B6B4FFB2ADA9FF9BA09EFF72AABEFF40A0D4FF5DC5
      E9FF85E7F6FF96F8FDFF9AFDFFFF96F9FFFF94F7FEFF94EFF7FD9BD8D9ED9EDB
      DAEC5A91AEDB4E4F505A05050506000000000000000000000000000000000000
      00002728282951B0D0D628E7FFFF2CDAFAFFD1AEA5FBFFF4EDFFFFF9F5FFFFF9
      F3FFFFF9F4FFFFF8F3FFFCE6DCFFFAC6B1FFFFF9F2FFFFF3EAFFFFF4EBFFFCD3
      C1FFFCD1BEFFFFE9D9FFFEDBC1FFFEC8ABFF736B688912121213000000000000
      0000000000000000000000000000000000000000000035353537EBE7E4EBFEF5
      EDFFFDE2CFFFF7C6ACFFEEA280FFEA8B67FFED9170FFFCB292FFD69B95FF6B7A
      C5FF89C8FEFF8AC8FDFF7BB7F7FF6492E4FF8488C6FFE6B2A6FFE1A59AFF666E
      C0FF68A7FDFF64A0FCFF4E88FEFF356CFEFF2B61FEFF255BFEFF1B52FEFF1549
      FBFF4C508ACF4F4F4F5B07070708000000000000000000000000000000000000
      00002B3CC2EB022AEAFF1411AAFF1313BCFF0F18C6FF0C1DD2FF0E1BC6FF0708
      8BFF000484FF010689FF01078CFF01088EFF010990FF010A94FF010B97FF010C
      9AFF010D9DFF010FA1FF0111A5FF11119FFF1313B0FF1413BEFF5F5F74AE2222
      2223000000000000000000000000000000006A84939F4BD5F8FF51E3FFFF4FE1
      FFFF4CE2FFFF48E0FEFF48B7E9FF95F4FCFFD2D2C0FFDFBBA5FFCDB6ABFFF7C7
      B4FFFEC2A9FFFDC4ABFFF5C8B3FFFADFCCFF9DABA2FF99F6F8FF93ECF8FF71CF
      ECFF4EB1E2FF45AADEFF58BAE5FF70D0EDFF8AE4F5FF9CE4EBF9A4D7D6ECA6DC
      DBED5B91AFDC4C4C4D5603030304000000000000000000000000000000000000
      00001C1C1C1D5FA3C1C93CEBFFFF74CDCFFFFFD6C6FFFFFCFAFFFFF9F6FFFFFA
      F6FFFFF8F4FFFFFDF9FFFCCEBBFFFDE2D5FFFFF7EFFFFFF5EDFFFEEEE3FFFBBD
      A6FFFEEDDFFFFFE1C9FFFFD9BEFFCD9986DF2C2C2C2E02020203000000000000
      00000000000000000000000000000000000000000000000000006F6D6C70F2E0
      D4F3FFFFFEFFFEFBF6FFFBEDE7FFF4CABBFFDF6D48FFF3A080FFFBB393FFBD8C
      98FF5681DAFF6497E5FF6C78C6FFB1A8CAFFF5E9DDFFFEE4D2FFFCB89BFFC893
      9BFF496FE0FF5794FFFF4D87FEFF3B73FEFF2B61FEFF255BFEFF1C51FEFF154D
      FFFF3C49ADE14646474E03030304000000000000000000000000000000000000
      00002B3DC3EB0920CDFF1510AFFF1115C2FF0D1ACCFF0A20D9FF0D1ECBFF0704
      7DFF010070FF030076FF040178FF04027AFF03027CFF02037DFF010381FF0004
      85FF00068AFF01088EFF020990FF1110A3FF1513AFFF1315BCFF605F74AD2323
      2324000000000000000000000000000000006891AABA54E0F9FF58E7FFFF55E6
      FFFF52E5FFFF4EE1FDFF51B9E9FFA4F9FDFFBBE9E1FFF2CAA4FFD2BDB1FFF8F8
      F5FFFEF3ECFFFEE9DEFFFEE1D2FFFFE5D5FFA0B1AAFF94E9F7FF96E8F7FFADFC
      FEFFAEFBFDFFA1EFF9FF85DCF2FF6AC6E9FF4FACDFFE4AA4D6FB90C6D4EFABDC
      DCEE5886A2D24242424800000001000000000000000000000000000000000303
      03044A4B4D5351BCDEE959E9F9FFC5BBAFFFFFFAF7FFFFFCFAFFFFFCF9FFFFFA
      F7FFFFFBF8FFFEF0E9FFEAA890F5FAE3D9FDFEF1E9FFFDEADFFFDDAA96E6D7A5
      92DEF8CBB4FBF4C6ACF8B29083C23D3D3D410101010200000000000000000000
      0000000000000000000000000000000000000000000000000000060606077672
      6F7AF9ECE3FAFFF6F0FFFFEAD9FFFFFDFCFFEC9E81FFF39E79FFFDCBB0FFFFE2
      C8FFD3BEC3FFC6B3C3FFFFEBD4FFFFEDD8FFFFEADAFFFFEDDDFFFCD7C4FFFFBF
      9EFFA17CA6FF3E64E0FF3D75FEFF3369FEFF285EFEFF235AFEFF1F4DF0FC4B56
      ACD5414142470707070800000000000000000000000000000000000000000000
      0000273AC2ED0C1CC3FF1410B5FF0F17C7FF0C1CD1FF0822DFFF0B1FCEFF0E0C
      94FF0B12A4FF0C18B5FF0B1DC4FF0B1CC4FF0C18B7FF0C14AAFF0C0E9AFF0908
      88FF05037BFF00017AFF01037DFF100FA2FF1413B3FF1216C0FF606074AC1E1E
      1E1F000000000000000000000000000000005F9FC0D460E8FBFF61EBFFFF5FE9
      FFFF5DEBFFFF4ED8F7FF68C5ECFFB8FDFEFFB3FDFFFFC2E8E0FFE9C4B0FFF4DF
      D6FFFAEAE3FFFEF0EAFFFFF8F4FFFDDED3FFA0BDBBFF94E3F6FF4FACDFFF4AA9
      DFFF5CB7E4FF79CDECFF99E5F5FFACF1F9FFB6F5F9FDAED6DDF1ADD4D8EDB1DC
      DEEE5B7F96C93838383C00000000000000000000000000000000020202033131
      32345C92AEC849E1FCFD6DE4EEFFDBC5B8FFFFFFFEFFFFFBF9FFFFFBFAFFFFFC
      FAFFFFFDFAFFF3C4B1FA6F68657F897A758FAB9288B08C7D77923C3B3B3F3131
      31335955535A54514F561F1F1F20020202030000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000707
      0708B0A39AB0FFF8F3FFFFF3EBFFFFFDFBFFF1B092FFF5A47DFFFDCEB2FFFFE1
      C8FFFFE4CBFFFFE6CEFFFFE4D0FFFFE5D2FFFFE8D5FFFFE9D7FFFEE8D7FFFDCE
      B9FFF1AB93FF785596FF265EFBFF245BFEFF184DFDFF1A40E3FF646788A73333
      3336010101020000000000000000000000000000000000000000000000000000
      00003A46B5E10D1CC4FF1411B7FF0F19C9FF0A1ED6FF0624E5FF0A1ECCFF0922
      D3FF022DF9FF012DF9FF012DF8FF022CF7FF022BF4FF0429EFFF0726E6FF0C20
      D3FF0F17B6FF0C0B91FF040276FF100D9EFF1414B6FF1117BCFF63636F920D0D
      0D0E000000000000000000000000000000005EA2C3D869ECFCFF69EFFFFF67EE
      FFFF65EEFFFF5BE3FBFF4DB0E6FF8AD5F0FFACEDF9FFBCFBFFFFC8F4EFFFCBEC
      E7FFD2E1D9FFDBDACEFFE9D4C7FFEFC2B1FFB2E6E7FFBBFBFFFFB8F9FCFFADEF
      F8FF95DDF2FF7ACBEBFF5DB5E3FF52ADE0FF5EB1DEFD86BDD7F5B2D3D7EDB0D8
      E0F15F7B8EBE31313134000000000000000000000000000000003333333445A6
      D1DC2FE6FFFF4BE9FFFF76E5EEFFDEC5B7FFFFFFFFFFFFFCFCFFFFFDFAFFFFFD
      FCFFFDE6DEFF9E827CCF35353538050505060000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000131313149E968FA8FFFCF9FFFFFFFFFFF7C3A5FFF7A984FFFDCAABFFFFDC
      C0FFFFDCC2FFFFDEC5FFFFE1C9FFFFE1CAFFFFE3CDFFFFE6D1FFFFE6D3FFFFF1
      E7FFF8BBA4FFD57E5EF3555B92C84257C2DC636587A742424348010101020000
      0000000000000000000000000000000000000000000000000000000000000000
      00006464798A1214ABFF1312BAFF0E19CAFF0A1ED8FF0525E9FF0B1EC8FF0527
      E1FF002EFAFF002EF8FF002EF7FF012CF6FF012BF3FF0329EFFF0427EAFF0625
      E5FF0922DFFF0D1ED1FF1113A8FF1310A2FF1413B5FF393997E53A3A3A3E0000
      0000000000000000000000000000000000005DA1C5D75FD9F3FF6BEAF9FF6DEF
      FCFF6FF2FEFF6EF4FFFF62E6F9FF4ACAEFFF42BAEAFF45B3E8FF5FBEEAFF77CB
      EFFF97DEF5FFAAE9F8FFBCF4FCFFC4FAFCFFC9FEFFFFC8FCFFFFC5FBFFFFC4FB
      FFFFC5FBFFFFC9FCFFFFCAFEFFFFC3F8FDFFA6D5E8FA87B9D5F4A7C8D5EEACD5
      E2F4637580A92626262800000000000000000000000000000000494B4B4C17C7
      F8FA29E8FFFF48E9FFFF6EEAF8FFD0BCADFFFFFAF8FFFFFEFDFFFFFEFDFFFFFF
      FFFFE7C2B2FF64859EDB5151515E1C1C1C1D0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000001D1D1D1EE0D1C4E0FFFEFDFFFCCEB0FFF9AC86FFFDC6A5FFFFD9
      B9FFFFDABDFFFFDCC0FFFFDEC3FFFFDFC4FFFFE1C9FFFFE3CBFFFFE3CDFFFFF2
      E6FFF3C6B8FFD17A57F253525461363636390B0B0B0C00000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000015151516545298CB1312B7FF0E19CBFF0920DAFF0723E1FF0D1BBEFF022C
      F0FF002FFBFF0030FBFF002FFBFF002EF9FF012CF4FF032AF0FF0428EAFF0624
      E3FF0921DBFF0B1ED4FF0F19C8FF1312AEFF1916A4FC5C5C6173020202030000
      000000000000000000000000000000000000393A3B3D687882886A94ACBA60A4
      C6D84CBDE8FC56D0F2FF64E2F7FF6CEEFBFF6EF4FEFF69F0FBFF5EE3F8FF54D5
      F4FF4CC5EFFF4ABBEBFF53B5E8FF67BDEAFF8FD1EFFFADE3F5FFCAF7FDFFD3FD
      FEFFD5FDFFFFD0FCFFFFCDFBFFFFCBF8FDFFC8E4E9F7C9D8D7ECCAD7D7EAA1CF
      E5F7646F76961E1E1E1F00000000000000000000000000000000080808094345
      46496890A7AA53BEE0E45DECFEFF8DDDE0FFF3C1AEFFFEEEE9FFFFF9F6FFFDD4
      C5FF96C8C3FF3DE0FFFF5D7586B95050505D0F0F0F1000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000038373739D7D3D3D9FCD0B0FFFBB695FFFDCEB2FFFFD9
      BBFFFFD5B5FFFFD6B5FFFFD8B9FFFFDABDFFFFDDC2FFFFDFC3FFFFDFC7FFFFF4
      EAFFF1BDADFFCC7256F24A4A4A530A0A0A0B0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000041404346211FABF71018C8FF0A20DAFF0D1BC2FF0920CEFF002F
      FBFF0030FDFF0030FEFF0030FDFF002FFAFF012CF4FF032AF0FF0427E9FF0724
      E2FF0920DAFF0B1CD2FF1016C0FF1512AFFF5A5981BD1A1A1A1B000000000000
      0000000000000000000000000000000000000000000000000000000000000202
      02031D1D1D1E4244454860686E786A8697A26799B4C362AAC9DA5CC1E0F15BD5
      F1FD63E5F8FF69EEFAFF66EDFDFF5FE5FAFF4BCEF2FF41BFEDFF43B3E9FF54B8
      E9FF76C4ECFF94D3F1FFB3E3F6FFC5EDF9FFCDDFE1F3CFD7D7EBD2DAD9EB82BD
      DFF85C5E61721010101100000000000000000000000000000000000000000000
      00000A0A0A0B38393B3C61ABCFD462ECFEFF9ED5D4FFD4C3B4FFE5C2B2FFB9C5
      BBFF5AEBFAFF41EBFFFF32B5E0F3636C749F2D2D2D2F03030304000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000030303044F4F4F52F2B092FEF4A282FFF7CDC0FFFDF5
      EEFFFFF3E7FFFFEAD6FFFFDBC0FFFFD7B7FFFFD7B8FFFFD9BCFFFFDCC1FFFFF5
      ECFFEDAC98FFCB6D4FF24A4A4A530A0A0A0B0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000162618FB11215BFFF0F18BFFF0E19B9FF0427EAFF002D
      F5FF002FFBFF0031FEFF0030FCFF002EF9FF012BF3FF0329EEFF0526E7FF0823
      DFFF0B1ED7FF0D1ACEFF1314B2FF26229FF55050525D00000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000005050506181818192B2B2B2D46494B4D5D66
      6C706C8A9CA7669CB9C850B3DDF150C6ECFD6DF3FEFF6AF0FEFF64EAFCFF5BE2
      F9FF52D6F6FF4CCCF1FF48BCECFF4BAAE1FD6BACD5F28EBFDFF4B1D2E5F762AC
      DDF63C3C3C400606060700000000000000000000000000000000000000000000
      000000000000000000002222222366A7C7CB5DF0FFFF64EFFFFF67EEFEFF59E6
      FEFE53C7E9EF4AC6E6EB22D2F9FA4F9BC2D22323232402020203000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000635D5B69C38670D0D15E40F3D95C
      3AFFE38C72FFEEB8AAFFF6DCD6FFFAECE6FFFEF0E4FFFFE7D4FFFFE0C6FFFFF5
      EBFFECA893FFCA6A4CF2494949520A0A0A0B0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000002020202148469DD91312AEFF0C1ED4FF0624E3FF0329
      ECFF012CF3FF002DF7FF002DF6FF012CF4FF032AEEFF0527E8FF0724E1FF0920
      D9FF0C1DD2FF1016BAFF1512A4FF62616B830404040500000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000F0F0F10688292A46DEAFAFF75F6FFFF71F3FFFF6FF2
      FFFF6DF1FFFF6BF1FFFF69F1FDFF45ACDBF74A4B4C543737383A5B62676F555A
      5D63050505060000000000000000000000000000000000000000000000000000
      00000000000000000000000000005F686F7642E5FFFF4DEAFFFF4DD2F3F96789
      A0B54446464B3A3A3B3E4F545759404243450404040500000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000005050506232323244E4A49507E6B
      6685B5715DCCD55838F8DC6140FFE1775BFFEBA591FFF2CABEFFFCF3EEFFFCF4
      F1FFE38465FFCB684BF34646464E080808090000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000323233354D4C9ED31017C0FF0B1ED6FF0823
      E1FF0526E8FF0328EBFF0328ECFF0427EAFF0526E5FF0723E0FF0920DAFF0C1C
      D2FF1116BDFF2220A1F75E5E6678020202030000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000005B60646E6AE1F6FF86FDFFFF7CF9FFFF79F7
      FFFF75F5FFFF73F4FFFF64E4F9FF5495B9DC2121212201010102000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000101010113CBAE9EC2AE8FFFF638397B42525
      2526000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000014141415504D4C55836F6990B37564C6C4694EE2D8603EFDDB60
      3DFFDC5F3BFFBA715BDF2A2A2A2C030303040000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000D0D0D0E646477873637A8E80E19
      C4FF0B1ED4FF0921DCFF0922DEFF0921DDFF0A1FD9FF0C1DD3FF0F19C6FF2121
      AFF75C5B8ABC3F3F404400000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000028282829659DBCCC65B2D0E064C9E4F467DB
      F3FE70E9F8FF74EDFAFF549EC3E24D4E4F570303030400000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000677D8B8E41AEDCE23A3A3B3E0606
      0607000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000001818181934343336675E5B6B9A78
      6EA7BB7662D3766966810A0A0A0B000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000001E1E1E1F5454
      5B62656588A354559DC84344A6DC3739A9E650519FCE5C5C95BB646375873A3A
      3B3E040404050000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000001D1D1D1E31313133474A4C4E606A
      70756C8797A26A91A7B65154565C0C0C0C0D0000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000080000000400000000100010000000000000400000000000000000000
      000000000000000000000000FFFFFF00F80FFF81000000000000000000000000
      F001FF00000000000000000000000000F0000000000000000000000000000000
      E0000000000000000000000000000000E0000000000000000000000000000000
      C0000000000000000000000000000000C0000000000000000000000000000000
      C000000300000000000000000000000080000007000000000000000000000000
      8000000F0000000000000000000000008000000F000000000000000000000000
      0000001F0000000000000000000000000000003F000000000000000000000000
      0000003F0000000000000000000000000000003F000000000000000000000000
      0000007F0000000000000000000000000000007F000000000000000000000000
      0000007F000000000000000000000000000000FF000000000000000000000000
      000000FF000000000000000000000000800000FF000000000000000000000000
      800000FF000000000000000000000000C00000FF000000000000000000000000
      E00000FF000000000000000000000000F00000FF000000000000000000000000
      F00000FF000000000000000000000000FC0000FF000000000000000000000000
      FC0000FF000000000000000000000000FF0000FF000000000000000000000000
      FF0000FF000000000000000000000000FFF000FF000000000000000000000000
      FFFE01FF000000000000000000000000FFFF80FFF80FFFFFFFC007FFFFFFFF81
      FFFF803FF801FFFFFF8001FFFFFFFF00FFFE000FF0000FFFFE00007FFFF03000
      FFFC0007F00001FFFC00003FFCC00000FFF80003E000001FFC00003FF0000000
      FE300003E000000FF800001FF0000000F8000003C0000007F800001FF0000000
      F8000003C0000003F000001FE0000001F0000007C0000003F000001FE0000007
      F000000780000001F000001FC000000FF000000780000001F000001FC000001F
      F800000780000001F000001FC0000007FC00000700000003F000001F80000003
      FE00000F0000000FF000001F80000003FFC0000F0000001FF000001F80000003
      FFC0000F0000000FF000001F00000003F980000F0000000FF000000F00000003
      F000001F00000007F000000F00000001F000001F00000003F000000F00000001
      F000001F00000001F000000F00000001F000003F80000001F000000F00000001
      F000003FC0000001F000000F00000001E000007FC0000003F000000F00000003
      C00000FFE0000007F000000F00000003C000FFFFF000001FF000001F00000003
      C000FFFFF800007FF000001F00000003C0007FFFFC0000FFF800003FE0000003
      F0003FFFFC0000FFF800007FFE000003FC003FFFFF0000FFFC00007FFFFC0007
      FE007FFFFF0000FFFE0000FFFFFE003FFE0FFFFFFFF800FFFF0003FFFFFE007F
      FF0FFFFFFFFF01FFFFC007FFFFFF00FF00000000000000000000000000000000
      000000000000}
  end
end
