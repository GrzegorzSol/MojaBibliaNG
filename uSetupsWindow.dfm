object SetupsWindow: TSetupsWindow
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'G'#322#243'wne ustawienia aplikacji'
  ClientHeight = 762
  ClientWidth = 1188
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
  object SW_PControlSelected: TPageControl
    Left = 185
    Top = 0
    Width = 1003
    Height = 679
    CustomHint = SW_BalloonHint
    ActivePage = SW_SheetTranslates
    Align = alClient
    Images = SW_ImgListMainSmall
    ParentShowHint = False
    ShowHint = True
    TabOrder = 0
    OnChange = SW_PControlSelectedChange
    ExplicitWidth = 999
    ExplicitHeight = 678
    object SW_SheetLajout: TTabSheet
      CustomHint = SW_BalloonHint
      Caption = 'Ustawienia wygl'#261'du aplikacji'
      object LabelInfoPreview: TLabel
        AlignWithMargins = True
        Left = 3
        Top = 391
        Width = 989
        Height = 32
        CustomHint = SW_BalloonHint
        Align = alTop
        Caption = 
          'Podgl'#261'd kolor'#243'w tekstu biblijnego jest tylko pogl'#261'dowy i nie jes' +
          't dok'#322'adn'#261' kopi'#261' ostatecznego wygl'#261'du, lecz jest tylko zgrubnym ' +
          'widokiem stworzonym dla og'#243'lnego doboru kolor'#243'w'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        Font.Quality = fqClearType
        ParentFont = False
        Layout = tlCenter
        WordWrap = True
        StyleElements = [seClient, seBorder]
        ExplicitWidth = 985
      end
      object GrBoxSetColors: TGroupBox
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 989
        Height = 382
        CustomHint = SW_BalloonHint
        Align = alTop
        Caption = 'Ustawienia kolor'#243'w aplikacji'
        TabOrder = 0
        object GrBoxSetupsFullTr: TGroupBox
          AlignWithMargins = True
          Left = 5
          Top = 18
          Width = 979
          Height = 105
          CustomHint = SW_BalloonHint
          Align = alTop
          Caption = 'Kolory dla pe'#322'nych przek'#322'ad'#243'w Pisma '#346'wi'#281'tego'
          TabOrder = 0
          object LabelColorBacground: TLabel
            Left = 170
            Top = 22
            Width = 337
            Height = 13
            CustomHint = SW_BalloonHint
            AutoSize = False
            Caption = 'Kolor podk'#322'adu dla tekstu werset'#243'w, w g'#322#243'wnym oknie'
            Layout = tlCenter
          end
          object LabelColorNameTranslate: TLabel
            Left = 170
            Top = 50
            Width = 337
            Height = 13
            CustomHint = SW_BalloonHint
            AutoSize = False
            Caption = 'Kolor czcionki, nazwy pe'#322'nego t'#322'umaczenia'
            Layout = tlCenter
          end
          object LabelColorAdresFullTranslates: TLabel
            Left = 170
            Top = 78
            Width = 337
            Height = 13
            CustomHint = SW_BalloonHint
            AutoSize = False
            Caption = 'Kolor czcionki, adresu wersetu, dla pe'#322'nego t'#322'umaczenia'
            Layout = tlCenter
          end
          object SW_ColorBoxBackground: TColorBox
            Left = 12
            Top = 19
            Width = 145
            Height = 22
            CustomHint = SW_BalloonHint
            Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
            TabOrder = 0
            OnChange = SW_ColorAllChange
            OnGetColors = SW_ColorBoxGetColors
          end
          object SW_ColorBoxNameTranslate: TColorBox
            Left = 12
            Top = 47
            Width = 145
            Height = 22
            CustomHint = SW_BalloonHint
            Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
            TabOrder = 1
            OnChange = SW_ColorAllChange
            OnGetColors = SW_ColorBoxGetColors
          end
          object SW_ColorBoxColorAdressFulltranslates: TColorBox
            Left = 12
            Top = 75
            Width = 145
            Height = 22
            CustomHint = SW_BalloonHint
            Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
            TabOrder = 2
            OnChange = SW_ColorAllChange
            OnGetColors = SW_ColorBoxGetColors
          end
        end
        object GrBoxSelectAndCommentsSetups: TGroupBox
          AlignWithMargins = True
          Left = 5
          Top = 129
          Width = 979
          Height = 105
          CustomHint = SW_BalloonHint
          Align = alTop
          Caption = 
            'Koloru dla ulubionych werset'#243'w, ora takich, kt'#243're posiadaj'#261' kome' +
            'ntarze'
          TabOrder = 1
          object LabelColorFavorities: TLabel
            Left = 170
            Top = 50
            Width = 337
            Height = 13
            CustomHint = SW_BalloonHint
            AutoSize = False
            Caption = 'Kolor zaznaczenie ulubionych werset'#243'w'
            Layout = tlCenter
          end
          object LabelColorComment: TLabel
            Left = 170
            Top = 22
            Width = 337
            Height = 13
            CustomHint = SW_BalloonHint
            AutoSize = False
            Caption = 
              'Kolor czcionki znacznika dla  werset'#243'w, do kt'#243'rego istnieje kome' +
              'ntarz'
            Layout = tlCenter
          end
          object LabelColorBackgroundMarkComments: TLabel
            Left = 170
            Top = 81
            Width = 337
            Height = 13
            CustomHint = SW_BalloonHint
            AutoSize = False
            Caption = 'Kolor podk'#322'adu, znacznika istnienia komentarza do wersetu.'
            Layout = tlCenter
          end
          object SW_ColorBoxFavorities: TColorBox
            Left = 12
            Top = 47
            Width = 145
            Height = 22
            CustomHint = SW_BalloonHint
            Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
            TabOrder = 0
            OnChange = SW_ColorAllChange
            OnGetColors = SW_ColorBoxGetColors
          end
          object SW_ColorBoxComment: TColorBox
            Left = 12
            Top = 19
            Width = 145
            Height = 22
            CustomHint = SW_BalloonHint
            Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
            TabOrder = 1
            OnChange = SW_ColorAllChange
            OnGetColors = SW_ColorBoxGetColors
          end
          object SW_ColorBackgroundMarkerComment: TColorBox
            Left = 12
            Top = 75
            Width = 145
            Height = 22
            CustomHint = SW_BalloonHint
            Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
            TabOrder = 2
            OnChange = SW_ColorAllChange
            OnGetColors = SW_ColorBoxGetColors
          end
        end
        object GrBoxOryginalPartTranslates: TGroupBox
          AlignWithMargins = True
          Left = 5
          Top = 240
          Width = 979
          Height = 137
          CustomHint = SW_BalloonHint
          Align = alClient
          Caption = 'Kolory dla przek'#322'ad'#243'w niekompletnych, lub oryginalnych'
          TabOrder = 2
          object LabelColorAdressOryg: TLabel
            Left = 170
            Top = 50
            Width = 337
            Height = 13
            CustomHint = SW_BalloonHint
            AutoSize = False
            Caption = 'Kolor adresu oryginalnego t'#322'umaczenia'
          end
          object LabelColorNameOrygTrans: TLabel
            Left = 170
            Top = 22
            Width = 337
            Height = 13
            CustomHint = SW_BalloonHint
            AutoSize = False
            Caption = 'Kolor nazwy oryginalnego t'#322'umaczenia'
            Layout = tlCenter
          end
          object LabelColorOrygTr: TLabel
            Left = 170
            Top = 77
            Width = 337
            Height = 13
            CustomHint = SW_BalloonHint
            AutoSize = False
            Caption = 'Kolor tekstu, dla oryginalnych t'#322'umacze'#324
            Layout = tlCenter
          end
          object LabelColorBorderFavoritiesVers: TLabel
            Left = 170
            Top = 104
            Width = 337
            Height = 13
            CustomHint = SW_BalloonHint
            AutoSize = False
            Caption = 'Kolor ramki naoko'#322'o ulubionego wersetu'
          end
          object SW_ColorBoxAdressOryg: TColorBox
            Left = 12
            Top = 47
            Width = 145
            Height = 22
            CustomHint = SW_BalloonHint
            Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
            TabOrder = 0
            OnChange = SW_ColorAllChange
            OnGetColors = SW_ColorBoxGetColors
          end
          object SW_ColorBoxColorNameOrygTran: TColorBox
            Left = 12
            Top = 19
            Width = 145
            Height = 22
            CustomHint = SW_BalloonHint
            Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
            TabOrder = 1
            OnChange = SW_ColorAllChange
            OnGetColors = SW_ColorBoxGetColors
          end
          object SW_ColorBoxColorOrygTr: TColorBox
            Left = 12
            Top = 74
            Width = 145
            Height = 22
            CustomHint = SW_BalloonHint
            Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
            TabOrder = 2
            OnChange = SW_ColorAllChange
            OnGetColors = SW_ColorBoxGetColors
          end
          object SW_ColorBoxBorderFavoritiesVers: TColorBox
            Left = 12
            Top = 101
            Width = 145
            Height = 22
            CustomHint = SW_BalloonHint
            Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
            TabOrder = 3
            OnChange = SW_ColorAllChange
            OnGetColors = SW_ColorBoxGetColors
          end
        end
      end
      object WebBrowserPreview: TWebBrowser
        Left = 0
        Top = 426
        Width = 995
        Height = 224
        CustomHint = SW_BalloonHint
        Align = alClient
        TabOrder = 1
        ControlData = {
          4C000000D6660000271700000100000001020000000000000000000000000000
          000000004C000000000000000000000001000000E0D057007335CF11AE690800
          2B2E126209000000000000004C0000000114020000000000C000000000000046
          8000000000000000000000000000000000000000000000000000000000000000
          00000000000000000100000000000000000000000000000000000000}
      end
    end
    object SW_SheetFlags: TTabSheet
      AlignWithMargins = True
      CustomHint = SW_BalloonHint
      Caption = 'Flagi i prze'#322#261'czniki aplikacji'
      ImageIndex = 1
      object ToggleSwitchIsDisplayInfos: TToggleSwitch
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 983
        Height = 20
        CustomHint = SW_BalloonHint
        Align = alTop
        SwitchWidth = 24
        TabOrder = 0
        ThumbWidth = 10
        ExplicitWidth = 46
      end
      object ToggleSwitchIsRequestClose: TToggleSwitch
        AlignWithMargins = True
        Left = 3
        Top = 29
        Width = 983
        Height = 20
        CustomHint = SW_BalloonHint
        Align = alTop
        SwitchWidth = 24
        TabOrder = 1
        ThumbWidth = 10
        ExplicitWidth = 46
      end
      object ToggleSwitchIsOneInstance: TToggleSwitch
        AlignWithMargins = True
        Left = 3
        Top = 55
        Width = 983
        Height = 20
        CustomHint = SW_BalloonHint
        Align = alTop
        SwitchWidth = 24
        TabOrder = 2
        ThumbWidth = 10
        ExplicitWidth = 46
      end
      object ToggleSwitchIsUpdatesOnStartup: TToggleSwitch
        AlignWithMargins = True
        Left = 3
        Top = 81
        Width = 983
        Height = 20
        CustomHint = SW_BalloonHint
        Align = alTop
        SwitchWidth = 24
        TabOrder = 3
        ThumbWidth = 10
        ExplicitWidth = 46
      end
      object ToggleSwitchIsReopenSchets: TToggleSwitch
        AlignWithMargins = True
        Left = 3
        Top = 107
        Width = 983
        Height = 20
        CustomHint = SW_BalloonHint
        Align = alTop
        SwitchWidth = 24
        TabOrder = 4
        ThumbWidth = 10
        ExplicitWidth = 46
      end
      object ToggleSwitchIsHintsOnStart: TToggleSwitch
        AlignWithMargins = True
        Left = 3
        Top = 133
        Width = 983
        Height = 20
        CustomHint = SW_BalloonHint
        Align = alTop
        SwitchWidth = 24
        TabOrder = 5
        ThumbWidth = 10
        ExplicitWidth = 46
      end
      object ToggleSwitchisInfosOnStatusBar: TToggleSwitch
        AlignWithMargins = True
        Left = 3
        Top = 159
        Width = 983
        Height = 20
        CustomHint = SW_BalloonHint
        Align = alTop
        SwitchWidth = 24
        TabOrder = 6
        ThumbWidth = 10
        ExplicitWidth = 46
      end
    end
    object SW_SheetPaths: TTabSheet
      AlignWithMargins = True
      CustomHint = SW_BalloonHint
      Caption = 'Scie'#380'ki dost'#281'pu'
      ImageIndex = 2
      object SW_GrBoxSelectPathDirMulti: TGroupBox
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 983
        Height = 117
        CustomHint = SW_BalloonHint
        Align = alTop
        Caption = 'Wyb'#243'r katalog'#243'w z multimediami - uwaga nr. 1'
        TabOrder = 0
        object SW_LEditPath3: TLabeledEdit
          Left = 161
          Top = 80
          Width = 505
          Height = 21
          CustomHint = SW_BalloonHint
          AutoSize = False
          EditLabel.Width = 148
          EditLabel.Height = 21
          EditLabel.CustomHint = SW_BalloonHint
          EditLabel.Caption = 'Wybierz katalog z multimediami'
          LabelPosition = lpLeft
          ParentShowHint = False
          ReadOnly = True
          ShowHint = True
          TabOrder = 0
          Text = ''
          TextHint = 'Wybierz katalog z multimediami...'
        end
        object SW_LEditPath1: TLabeledEdit
          Left = 161
          Top = 26
          Width = 505
          Height = 21
          CustomHint = SW_BalloonHint
          AutoSize = False
          EditLabel.Width = 148
          EditLabel.Height = 21
          EditLabel.CustomHint = SW_BalloonHint
          EditLabel.Caption = 'Wybierz katalog z multimediami'
          LabelPosition = lpLeft
          ParentShowHint = False
          ReadOnly = True
          ShowHint = True
          TabOrder = 1
          Text = ''
          TextHint = 'Wybierz katalog z multimediami...'
        end
        object SW_LEditPath2: TLabeledEdit
          Left = 161
          Top = 53
          Width = 505
          Height = 21
          CustomHint = SW_BalloonHint
          AutoSize = False
          EditLabel.Width = 148
          EditLabel.Height = 21
          EditLabel.CustomHint = SW_BalloonHint
          EditLabel.Caption = 'Wybierz katalog z multimediami'
          LabelPosition = lpLeft
          ParentShowHint = False
          ReadOnly = True
          ShowHint = True
          TabOrder = 2
          Text = ''
          TextHint = 'Wybierz katalog z multimediami...'
        end
        object SW_ButtSelectDirMulti_1: TButton
          Left = 672
          Top = 26
          Width = 106
          Height = 21
          CustomHint = SW_BalloonHint
          Caption = 'Wybierz katalog'
          ImageIndex = 0
          Images = SW_ImgListSmallMain
          ParentShowHint = False
          ShowHint = True
          TabOrder = 3
          OnClick = SW_ButtSetups_Click
        end
        object SW_ButtSelectDirMulti_2: TButton
          Left = 672
          Top = 53
          Width = 106
          Height = 21
          CustomHint = SW_BalloonHint
          Caption = 'Wybierz katalog'
          ImageIndex = 0
          Images = SW_ImgListSmallMain
          ParentShowHint = False
          ShowHint = True
          TabOrder = 4
          OnClick = SW_ButtSetups_Click
        end
        object SW_ButtSelectDirMulti_3: TButton
          Left = 672
          Top = 80
          Width = 106
          Height = 21
          CustomHint = SW_BalloonHint
          Caption = 'Wybierz katalog'
          ImageIndex = 0
          Images = SW_ImgListSmallMain
          ParentShowHint = False
          ShowHint = True
          TabOrder = 5
          OnClick = SW_ButtSetups_Click
        end
      end
      object SW_GrBoxSelectBackground: TGroupBox
        AlignWithMargins = True
        Left = 3
        Top = 126
        Width = 983
        Height = 63
        CustomHint = SW_BalloonHint
        Align = alTop
        Caption = 'Wyb'#243'r grafiki podk'#322'adu, w g'#322#243'wnym oknie'
        TabOrder = 1
        object SW_LEditPathBackGround: TLabeledEdit
          Left = 161
          Top = 24
          Width = 505
          Height = 21
          CustomHint = SW_BalloonHint
          EditLabel.Width = 111
          EditLabel.Height = 21
          EditLabel.CustomHint = SW_BalloonHint
          EditLabel.Caption = 'Wyb'#243'r grafiki podk'#322'adu'
          LabelPosition = lpLeft
          TabOrder = 0
          Text = ''
        end
        object SW_ButtSelectBackground: TButton
          Left = 672
          Top = 24
          Width = 106
          Height = 21
          CustomHint = SW_BalloonHint
          Caption = 'Wybierz grafik'#281
          ImageIndex = 0
          Images = SW_ImgListSmallMain
          ParentShowHint = False
          ShowHint = True
          TabOrder = 1
          OnClick = SW_ButtSetups_Click
        end
      end
    end
    object SW_OthersSetups: TTabSheet
      AlignWithMargins = True
      CustomHint = SW_BalloonHint
      Caption = 'Inne ustawienia'
      ImageIndex = 3
      object LabelSizeMainFont: TLabel
        Left = 19
        Top = 16
        Width = 331
        Height = 22
        CustomHint = SW_BalloonHint
        AutoSize = False
        Caption = 'Czcionka i wielko'#347#263' czcionki g'#322#243'wnego tekstu biblijnego'
        ParentShowHint = False
        ShowHint = True
        Layout = tlCenter
      end
      object LabelSizeFontAdress: TLabel
        Left = 19
        Top = 62
        Width = 331
        Height = 22
        CustomHint = SW_BalloonHint
        AutoSize = False
        Caption = 'Czcionka i wielko'#347#263' czcionki adresu, wersetu w g'#322#243'wnym oknie'
        ParentShowHint = False
        ShowHint = True
        Layout = tlCenter
      end
      object LabelFontNameTranslates: TLabel
        Left = 19
        Top = 110
        Width = 331
        Height = 22
        CustomHint = SW_BalloonHint
        AutoSize = False
        Caption = 'Czcionka i wielko'#347#263' czcionki nazwy t'#322'umacze'#324' w g'#322#243'wnym oknie'
        ParentShowHint = False
        ShowHint = True
        Layout = tlCenter
      end
      object SpEditSizeMainFont: TSpinEdit
        Left = 356
        Top = 17
        Width = 47
        Height = 22
        CustomHint = SW_BalloonHint
        AutoSize = False
        Ctl3D = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Font.Quality = fqClearType
        MaxLength = 2
        MaxValue = 24
        MinValue = 8
        ParentCtl3D = False
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        Value = 8
        OnChange = SpEditSizeFontChange
      end
      object SpEditSizeTranslatesFont: TSpinEdit
        Left = 356
        Top = 111
        Width = 47
        Height = 22
        CustomHint = SW_BalloonHint
        AutoSize = False
        Ctl3D = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Font.Quality = fqClearType
        MaxLength = 2
        MaxValue = 14
        MinValue = 8
        ParentCtl3D = False
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        Value = 8
        OnChange = SpEditSizeFontChange
      end
      object SpEditSizeAdressFont: TSpinEdit
        Left = 356
        Top = 63
        Width = 47
        Height = 22
        CustomHint = SW_BalloonHint
        AutoSize = False
        Ctl3D = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        Font.Quality = fqClearType
        MaxLength = 2
        MaxValue = 14
        MinValue = 8
        ParentCtl3D = False
        ParentFont = False
        ParentShowHint = False
        ShowHint = True
        TabOrder = 2
        Value = 8
        OnChange = SpEditSizeFontChange
      end
      object ButtFontNameMainText: TButton
        Left = 424
        Top = 12
        Width = 220
        Height = 32
        CustomHint = SW_BalloonHint
        Caption = 'Typ czcionki'
        ImageIndex = 5
        Images = SW_ImgListSmallMain
        ParentShowHint = False
        ShowHint = True
        TabOrder = 3
        OnClick = ButtFontSelectClick
      end
      object ButtFontNameAdress: TButton
        Left = 424
        Top = 58
        Width = 220
        Height = 32
        CustomHint = SW_BalloonHint
        Caption = 'Typ czcionki'
        ImageIndex = 5
        Images = SW_ImgListSmallMain
        ParentShowHint = False
        ShowHint = True
        TabOrder = 4
        OnClick = ButtFontSelectClick
      end
      object ButtFontNameTranslates: TButton
        Left = 424
        Top = 106
        Width = 220
        Height = 32
        CustomHint = SW_BalloonHint
        Caption = 'Typ czcionki'
        ImageIndex = 5
        Images = SW_ImgListSmallMain
        ParentShowHint = False
        ShowHint = True
        TabOrder = 5
        OnClick = ButtFontSelectClick
      end
    end
    object SW_SheetTranslates: TTabSheet
      CustomHint = SW_BalloonHint
      Caption = 'Wyb'#243'r t'#322'umacze'#324
      ImageIndex = 4
      object SW_ListViewAllTranslates: TListView
        AlignWithMargins = True
        Left = 12
        Top = 35
        Width = 971
        Height = 603
        Margins.Left = 12
        Margins.Top = 12
        Margins.Right = 12
        Margins.Bottom = 12
        CustomHint = SW_BalloonHint
        Align = alClient
        Checkboxes = True
        Columns = <>
        GroupView = True
        ReadOnly = True
        RowSelect = True
        SmallImages = SW_ImgListMainSmall
        TabOrder = 0
        ViewStyle = vsReport
        OnItemChecked = SW_ListViewAllTranslatesItemChecked
        ExplicitWidth = 967
        ExplicitHeight = 602
      end
      object SW_STextInfoHeadSelectTranslates: TStaticText
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 989
        Height = 17
        CustomHint = SW_BalloonHint
        Align = alTop
        Alignment = taCenter
        AutoSize = False
        BorderStyle = sbsSunken
        Caption = 'Wyb'#243'r u'#380'ywanych t'#322'umacze'#324' w aplikacji - uwaga nr. 1 '
        Color = clInfoBk
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        Font.Quality = fqClearType
        ParentColor = False
        ParentFont = False
        TabOrder = 1
        Transparent = False
        ExplicitWidth = 985
      end
    end
    object SW_SheetReadingPlan: TTabSheet
      CustomHint = SW_BalloonHint
      Caption = 'Plan czytania Biblii'
      ImageIndex = 7
      object PanelReadingPlanSetupLeft: TPanel
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 389
        Height = 644
        CustomHint = SW_BalloonHint
        Align = alLeft
        BevelOuter = bvNone
        ShowCaption = False
        TabOrder = 0
        object GrBoxSelectTranslate: TGroupBox
          AlignWithMargins = True
          Left = 3
          Top = 3
          Width = 383
          Height = 53
          CustomHint = SW_BalloonHint
          Align = alTop
          Caption = 'Wyb'#243'r przek'#322'adu Pisma '#346'wi'#281'tego dla planu czytania'
          TabOrder = 0
          object CBoxSelectTranslate: TComboBox
            AlignWithMargins = True
            Left = 5
            Top = 18
            Width = 373
            Height = 21
            Hint = 'Wyb'#243'r t'#322'umaczenia u'#380'ywanego w planie czytania.'
            Margins.Bottom = 12
            ParentCustomHint = False
            Align = alTop
            TabOrder = 0
            TextHint = 'Wybierz t'#322'umaczenie'
          end
        end
        object GrBoxSelectReadingPlan: TGroupBox
          AlignWithMargins = True
          Left = 3
          Top = 62
          Width = 383
          Height = 123
          CustomHint = SW_BalloonHint
          Align = alTop
          Caption = 'Wyb'#243'r Planu czytania Pisma '#346'wi'#281'tego'
          TabOrder = 1
          object LabelInfoSelectAndactivatePlan: TLabel
            AlignWithMargins = True
            Left = 5
            Top = 45
            Width = 373
            Height = 73
            CustomHint = SW_BalloonHint
            Align = alClient
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -13
            Font.Name = 'Tahoma'
            Font.Style = []
            Font.Quality = fqClearType
            ParentFont = False
            Layout = tlCenter
            WordWrap = True
            ExplicitWidth = 4
            ExplicitHeight = 16
          end
          object CBoxSelectPlan: TComboBox
            AlignWithMargins = True
            Left = 5
            Top = 18
            Width = 373
            Height = 21
            Hint = 'Wyb'#243'r planu czytania biblii z listy.'
            ParentCustomHint = False
            Align = alTop
            TabOrder = 0
            TextHint = 'Wybierz plan czytania'
            OnChange = CBoxSelectPlanChange
          end
        end
        object GrBoxSelectFont: TGroupBox
          AlignWithMargins = True
          Left = 3
          Top = 191
          Width = 383
          Height = 56
          CustomHint = SW_BalloonHint
          Align = alTop
          Caption = 'Wybierz typ czcionki dla Planu czytania'
          TabOrder = 2
          object CBoxSelectFontReadingPlan: TComboBox
            AlignWithMargins = True
            Left = 5
            Top = 18
            Width = 373
            Height = 21
            Hint = 'Wyb'#243'r kroju pisma u'#380'ywanego w tek'#347'cie planu czytania.'
            Margins.Bottom = 12
            ParentCustomHint = False
            Align = alTop
            Sorted = True
            TabOrder = 0
            Text = 'Wybierz czcionke'
          end
        end
        object GrBoxSizeFont: TGroupBox
          AlignWithMargins = True
          Left = 3
          Top = 253
          Width = 383
          Height = 52
          CustomHint = SW_BalloonHint
          Align = alTop
          Caption = 'Wybierz wysoko'#347#263' czcionki dla Planu czytania'
          TabOrder = 3
          object CBoxSelectSizeFontPlan: TComboBox
            AlignWithMargins = True
            Left = 5
            Top = 18
            Width = 128
            Height = 21
            Hint = 'Wysoko'#347#263' czciomki u'#380'ywanej w planie czytania.'
            Margins.Right = 248
            ParentCustomHint = False
            Align = alTop
            TabOrder = 0
            Text = 'Wybierz wysoko'#347#263' czcionki'
          end
        end
        object GrBoxSelectDate: TGroupBox
          AlignWithMargins = True
          Left = 3
          Top = 311
          Width = 383
          Height = 82
          CustomHint = SW_BalloonHint
          Align = alTop
          Caption = 
            'Ustalenie daty rozpocz'#281'cia czytania Pisma '#346'wi'#281'tego wed'#322'ug wybran' +
            'ego planu'
          TabOrder = 4
          object SpButtonStartPlan: TSpeedButton
            Left = 2
            Top = 51
            Width = 379
            Height = 22
            Hint = 'Rozpoczecie wybranego planu.'
            ParentCustomHint = False
            Align = alTop
            AllowAllUp = True
            GroupIndex = 1
            Caption = 'Rozpocznij wybrany plan czytania Pisma '#346'wi'#281'tego'
            OnClick = SpButtonStartStopReadingPlanClick
            ExplicitTop = 75
            ExplicitWidth = 311
          end
          object DateTimePickerSelectStartDatePlan: TDateTimePicker
            AlignWithMargins = True
            Left = 5
            Top = 18
            Width = 373
            Height = 21
            Hint = 'Wyb'#243'r daty rozpocz'#281'cia wybranego planu.'
            Margins.Bottom = 12
            ParentCustomHint = False
            Align = alTop
            Date = 45010.000000000000000000
            Time = 45010.000000000000000000
            Color = clBtnFace
            MaxDate = 54818.999988425920000000
            TabOrder = 0
            OnChange = DateTimePickerSelectStartDatePlanChange
          end
        end
        object GrBoxSetupsSpeak: TGroupBox
          AlignWithMargins = True
          Left = 3
          Top = 399
          Width = 383
          Height = 242
          CustomHint = SW_BalloonHint
          Align = alClient
          Caption = 'Ustawienia parametr'#243'w komputerowego  czytania tekstu'
          TabOrder = 5
          ExplicitHeight = 241
          object TrackBarSetRate: TTrackBar
            AlignWithMargins = True
            Left = 5
            Top = 18
            Width = 373
            Height = 30
            Hint = 'Ustawienie szybko'#347'ci czytania tekstu'
            ParentCustomHint = False
            Align = alTop
            Min = -10
            PageSize = 1
            PositionToolTip = ptTop
            SelEnd = 10
            SelStart = -10
            ShowSelRange = False
            TabOrder = 0
          end
          object TrackBarSetVolume: TTrackBar
            AlignWithMargins = True
            Left = 5
            Top = 54
            Width = 373
            Height = 30
            Hint = 'Ustawienia g'#322'o'#347'no'#347'ci czytania'
            ParentCustomHint = False
            Align = alTop
            Max = 100
            PageSize = 20
            Frequency = 10
            Position = 100
            PositionToolTip = ptTop
            SelEnd = 100
            ShowSelRange = False
            TabOrder = 1
          end
        end
      end
      object PanelViewSelectPlan: TPanel
        AlignWithMargins = True
        Left = 398
        Top = 3
        Width = 594
        Height = 644
        CustomHint = SW_BalloonHint
        Align = alClient
        ShowCaption = False
        TabOrder = 1
        ExplicitWidth = 590
        ExplicitHeight = 643
        object LabelTitleDisplayListPlan: TLabel
          AlignWithMargins = True
          Left = 4
          Top = 4
          Width = 232
          Height = 13
          CustomHint = SW_BalloonHint
          Align = alTop
          Alignment = taCenter
          Caption = 'Przegl'#261'd wybranego planu czytania biblii.'
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clRed
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          Font.Quality = fqClearType
          ParentColor = False
          ParentFont = False
          Transparent = True
          Layout = tlCenter
        end
        object LViewDisplayselectPlan: TListView
          AlignWithMargins = True
          Left = 4
          Top = 23
          Width = 586
          Height = 617
          CustomHint = SW_BalloonHint
          Align = alClient
          Color = clCream
          Columns = <>
          ColumnClick = False
          FlatScrollBars = True
          OwnerDraw = True
          ReadOnly = True
          RowSelect = True
          SmallImages = SW_ImgListMainSmall
          TabOrder = 0
          ViewStyle = vsReport
          OnChanging = LViewDisplayselectPlanChanging
          OnDrawItem = LViewDisplayselectPlanDrawItem
          ExplicitWidth = 582
          ExplicitHeight = 616
        end
      end
    end
    object SW_SheetSelectThemes: TTabSheet
      CustomHint = SW_BalloonHint
      Caption = 'Tematy graficzne'
      ImageIndex = 9
      object PanelListThemes: TPanel
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 185
        Height = 644
        CustomHint = SW_BalloonHint
        Align = alLeft
        Ctl3D = True
        ParentBackground = False
        ParentCtl3D = False
        ShowCaption = False
        TabOrder = 0
        object SW_LBoxSelectTheme: TListBox
          AlignWithMargins = True
          Left = 4
          Top = 4
          Width = 177
          Height = 636
          CustomHint = SW_BalloonHint
          Align = alClient
          BorderStyle = bsNone
          ItemHeight = 13
          TabOrder = 0
          OnClick = SW_LBoxSelectThemeClick
        end
      end
      object PanelDisplaySelectTheme: TPanel
        AlignWithMargins = True
        Left = 194
        Top = 3
        Width = 419
        Height = 644
        ParentCustomHint = False
        Align = alLeft
        BevelOuter = bvNone
        ShowCaption = False
        TabOrder = 1
        ExplicitHeight = 643
        object SW_ImagePreviewSelectStyle: TImage
          AlignWithMargins = True
          Left = 4
          Top = 3
          Width = 411
          Height = 316
          Margins.Left = 4
          Margins.Right = 4
          ParentCustomHint = False
          Align = alTop
          ExplicitLeft = 5
          ExplicitTop = 4
          ExplicitWidth = 412
        end
        object SW_ButtDisplaySelectTheme: TButton
          AlignWithMargins = True
          Left = 3
          Top = 325
          Width = 413
          Height = 25
          Align = alTop
          Caption = 'Poka'#380' wybrany temat'
          ImageIndex = 6
          ImageMargins.Left = 4
          Images = SW_ImgListSmallMain
          TabOrder = 0
          OnClick = SW_ButtSetups_Click
        end
      end
    end
  end
  object SW_GrPanelButtons: TGridPanel
    AlignWithMargins = True
    Left = 3
    Top = 730
    Width = 1182
    Height = 29
    Align = alBottom
    Caption = 'SW_GrPanelButtons'
    ColumnCollection = <
      item
        Value = 25.000000000000000000
      end
      item
        Value = 25.000000000000000000
      end
      item
        Value = 25.000000000000000000
      end
      item
        Value = 25.000000000000000000
      end>
    ControlCollection = <
      item
        Column = 0
        Control = SW_ButtSetupSave
        Row = 0
      end
      item
        Column = 2
        Control = SW_ButtSetupCancel
        Row = 0
      end
      item
        Column = 1
        Control = SW_ButtSetupReturn
        Row = 0
      end
      item
        Column = 3
        Control = SW_ButtSetupHelp
        Row = 0
      end>
    RowCollection = <
      item
        Value = 100.000000000000000000
      end>
    ShowCaption = False
    TabOrder = 1
    ExplicitTop = 729
    ExplicitWidth = 1178
    DesignSize = (
      1182
      29)
    object SW_ButtSetupSave: TButton
      Left = 89
      Top = 3
      Width = 118
      Height = 22
      CustomHint = SW_BalloonHint
      Anchors = []
      Caption = 'Zapisz konfiguracje'
      ImageIndex = 1
      Images = SW_ImgListSmallMain
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
      OnClick = SW_ButtSetups_Click
    end
    object SW_ButtSetupCancel: TButton
      Left = 701
      Top = 3
      Width = 75
      Height = 22
      CustomHint = SW_BalloonHint
      Anchors = []
      Caption = 'Anuluj'
      ImageIndex = 2
      Images = SW_ImgListSmallMain
      ParentShowHint = False
      ShowHint = True
      TabOrder = 1
      OnClick = SW_ButtSetups_Click
      ExplicitLeft = 698
    end
    object SW_ButtSetupReturn: TButton
      Left = 365
      Top = 2
      Width = 157
      Height = 25
      CustomHint = SW_BalloonHint
      Anchors = []
      Caption = 'Cofnij wprowadzone zmiany'
      ImageIndex = 3
      Images = SW_ImgListSmallMain
      ParentShowHint = False
      ShowHint = True
      TabOrder = 2
      OnClick = SW_ButtSetups_Click
      ExplicitLeft = 363
    end
    object SW_ButtSetupHelp: TButton
      Left = 996
      Top = 3
      Width = 75
      Height = 22
      Anchors = []
      Caption = 'Pomoc...'
      TabOrder = 3
      OnClick = SW_ButtSetups_Click
      ExplicitLeft = 992
    end
  end
  object SW_STextInfo: TStaticText
    AlignWithMargins = True
    Left = 3
    Top = 682
    Width = 1182
    Height = 42
    Align = alBottom
    AutoSize = False
    BevelInner = bvNone
    BevelOuter = bvNone
    BorderStyle = sbsSunken
    Color = clInfoBk
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    Font.Quality = fqClearType
    ParentColor = False
    ParentFont = False
    TabOrder = 2
    Transparent = False
    ExplicitTop = 681
    ExplicitWidth = 1178
  end
  object SW_PanelSelectListButtons: TPanel
    Left = 0
    Top = 0
    Width = 185
    Height = 679
    Align = alLeft
    TabOrder = 3
    ExplicitHeight = 678
    object SW_ButGroupSections: TButtonGroup
      Left = 1
      Top = 1
      Width = 183
      Height = 494
      CustomHint = SW_BalloonHint
      Align = alClient
      BevelInner = bvNone
      BevelOuter = bvNone
      BevelKind = bkFlat
      ButtonHeight = 46
      ButtonWidth = 46
      ButtonOptions = [gboAllowReorder, gboFullSize, gboGroupStyle, gboShowCaptions]
      Images = SW_ImgListMain
      Items = <
        item
          Caption = 'Wygl'#261'd aplikacji'
          ImageIndex = 0
        end
        item
          Caption = 'Prze'#322#261'czniki i flagi aplikacji'
          ImageIndex = 1
        end
        item
          Caption = #346'cie'#380'ki dost'#281'pu do danych aplikacji'
          ImageIndex = 2
        end
        item
          Caption = 'Inne ustawienia aplikacji'
          ImageIndex = 3
        end
        item
          Caption = 'Wyb'#243'r u'#380'ywanych t'#322'umacze'#324
          ImageIndex = 4
        end
        item
          Caption = 'Ustawienia planu czytania Biblii'
          ImageIndex = 5
        end
        item
          Caption = 'Wyb'#243'r temet'#243'w graficznych aplikacji'
          ImageIndex = 6
        end>
      ShowHint = True
      TabOrder = 0
      OnButtonClicked = SW_ButGroupSectionsButtonClicked
      OnKeyUp = SW_ButGroupSectionsKeyUp
      ExplicitHeight = 493
    end
    object SW_PanelImageLogo: TPanel
      Left = 1
      Top = 495
      Width = 183
      Height = 183
      Align = alBottom
      ShowCaption = False
      TabOrder = 1
      ExplicitTop = 494
      object SW_SetupsImageLogo: TImage
        AlignWithMargins = True
        Left = 27
        Top = 27
        Width = 129
        Height = 129
        Margins.Left = 26
        Margins.Top = 26
        Margins.Right = 26
        Margins.Bottom = 26
        Align = alClient
        ExplicitLeft = 1
        ExplicitTop = 6
        ExplicitWidth = 181
        ExplicitHeight = 181
      end
    end
  end
  object SW_ImgListMain: TImageList
    ColorDepth = cd32Bit
    DrawingStyle = dsTransparent
    Height = 32
    Width = 32
    Left = 1024
    Top = 152
    Bitmap = {
      494C010107001800040020002000FFFFFFFF2110FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000800000004000000001002000000000000080
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000909090A4848484A5C5C5B603F3F3F410909090A000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000909090A212121223131
      3134343434373434343734343437343434373434343734343437343434373434
      3437343434373434343734343437343434373434343734343437343434373434
      3437343434373434343734343437303030331F1F1F2007070708000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000404040501010102000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00003C3C3C3D918375CE6F4F30EC623E18F8785D43E68E7E6EDC797876862929
      292A000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000012B2B2B2D61646A886165
      6D9D60646CA060646EA060646CA060626AA0606068A0606067A0606066A06060
      68A0606269A0606269A0606169A0606068A0606067A0606068A0606168A06062
      69A0606269A0606168A0606065A06161649B4343434A11111112000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000001C1C1C1D7970639240403F44020202030000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000001919
      191A89725CDF5A2F06FF5A2F06FF5B3007FE5A2F06FF592F05FF5C3208FE8B76
      61E27372717B0808080900000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000001595B5F6C002D74FF002E
      75FF002668FF002E75FF002A6FFF001F60FF001857FF001351FF00114EFF0014
      52FF001958FF001957FF001551FF00134EFF00124DFF00124EFF00134FFF0016
      53FF001856FF00114CFF000842FF000131FF6162658F16161617000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000001919191AA27F44D4C47D06FFC88B16F64949474F0000
      0001000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000706E
      6C785B3007FE5B3007FE5B3007FE5B3007FE5C3107FE5D3107FE5E3208FF6236
      0BFE744F2CF3938E88B21F1F1F20000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000015A5C606E003A88FF003B
      87FE002F74FF003985FE003480FF002D72FE00276BFF002467FE002264FF0024
      67FE002366FF002062FE001C5DFF001D5DFE001E5DFF001F5EFE001D5CFF001F
      5FFE001E5FFF001855FE000F4BFF00073DFE6162669516161617000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000040404058C7B5EB0BE7907FFC57D06FFD28B06FFC08B26EC2121
      2122000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000897D
      71B85A2F06FF5B3006FF5B3007FE735335F07E7975914B4A4A4E4949484C6B68
      6674918376BD784D24F8978D84C1202020210000000000000000000000000000
      0000000000000000000000000000000000000000000000000000060606070000
      000000000000000000000000000000000000000000015A5D616E033F91FF0340
      91FF01347CFF003B8AFF003887FF00337DFF002E75FF002C72FF002C71FF002A
      6FFF002669FF002264FF002063FF002163FF002164FF002062FF002061FF001F
      5FFF001D5CFF001B59FF001450FF000840FF6162669616161617000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000101010206060607070707080505050601010102000000000000
      0000000000004C4B4952BD7909FEBF7907FFC58007FFD28B06FFD18A06FF8A7C
      61A7020202030000000001010102040404050606060705050506000000010000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000030303048773
      62CE5A2F06FF5C3107FE6C4A27F3565555590000000000000000000000000000
      0000000000012B2B2B2C8A8078A397918BB40808080900000000000000000000
      0000000000000000000000000000000000001919191A6666666A3B3B3B3C0000
      000000000000000000000000000000000000000000015A5D616E074397FF0845
      96FE043683FF023F8EFE013D8EFF003C8AFE003784FF003781FE00337DFF002E
      75FE00296EFF00296CFE00276BFF00286CFE00266AFF002669FE002466FF0020
      62FE001D5DFF002061FE001B59FF00104CFE6263679816161617000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000034343336878469A38F8B67AF7F7D68975B5A5665222222230808
      0809050505069E814DCBBF7908FFBF7908FFC58007FFD28B07FFD18A06FFCB89
      0DFB323231341F1F1F205553525F746968917F6C68A97A6B689E343333360000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000B0B0B0C826D
      58D25A2F05FF5C3006FF90877DBA010101020000000000000000000000000000
      00000000000000000000000000013939393A5353535600000000000000000000
      0000000000000909090A3C3C3C3D7A787583937F6BD9807D7B8E000000000000
      000000000000000000000000000000000000000000015A5D616E0A479DFF0B48
      9EFF073A88FF064195FF054194FF044193FF023F90FF003D8DFF003987FF0032
      7BFF002E75FF002D73FF002C72FF002B70FF00296EFF00286CFF00286CFF0023
      66FF002062FF002365FF002264FF001858FF68696CAD16161617000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000087846498CFBC1CFFDBC82EFFDCC92EFFDBC82DFFD5C234F99590
      67B466645E75BE7A0AFEBF7A09FFBF7908FFC58008FFD18B07FFCB8607FFBB72
      0FFF9A654EDE9E4A3DF6A04132FFA14132FFA14031FFA64435FF86726E9D0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000008080809836E
      5AD25B2F06FF603409FE7D7A768D000000000000000000000000000000000000
      00000000000000000000000000000000000022222223242424256867676D7E7C
      798A938C85AE9C8772DC885D39F2754214FE90755CE535353536000000000000
      000000000000000000000000000000000000000000015A5D616E0C4BA1FF0E4C
      A0FE0A3E8EFF0C499CFE0A469BFF0C489CFE094599FF074294FE013D8EFF0038
      84FE003480FF00337CFE003079FF002F77FE002D73FF002C72FE002B70FF002B
      71FE00276CFF00296EFE00296DFF002062FE656771E11C1C1C1D000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000908C63A1C4B00BFFCFBC1CFFDBC82EFFDCC92EFFDCC82DFFDBC7
      2CFFC79C1AFFC07A0AFFBF7A09FFBF7A09FFC37D08FFC37D0BFFAB5723FFA142
      33FFA14233FFA14233FFA14132FFA14132FFA64536FFAC4A3AFF8F746FA80000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000008878
      69C55E3208FF65370BFF79767487010101024545444648484849000000000000
      000000000000000000000000000000000000000000000000000032323233967D
      65D37C4717FF7C4717FF7C4617FF794515FF7D5029F695816BE182807E903333
      333400000000000000000000000000000000000000015A5D616E0E4CA4FF0D4C
      A3FF0B4192FF0E4DA5FF0E4BA2FF0E4BA3FF0D499FFF0A479BFF054193FF003C
      8DFF003787FF003482FF003380FF00337DFF00327CFF003179FF003078FF0031
      7AFF002F77FF002F76FF002F75FF002368FF5F626EFE3E3E3E43000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000007C7A6287C4B10CFFC4B00BFFCFBC1CFFDBC82EFFDCC92EFFDAC7
      2DFFC38B12FFC07A0AFFC07A0AFFBE7909FFB36D10FFA44A2EFFA14334FFA242
      34FFA24234FFA14233FFA14233FFA64637FFAC4A3BFFAD4B3BFF7E6E6B8E0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000857A
      70AD62350AFF6B3B0FFE8F8983AB8F8A85A3978F88B207070708000000000000
      0000151515161A1A1A1B6461A8BE5855B3D16663A7BC6363757B171717180F0F
      0F10928479B47D4718FE7D4718FF7D4718FE784415FF764314FE714012FE8D74
      5EE1807E7D8D1B1B1B1C0000000000000000000000015A5D616E104FA8FF1151
      A7FE0D4395FF1251A9FE1050A9FF1150A7FE0E4BA3FF0E4A9EFE084498FF043F
      8FFE3A5F95FF4C6D9DFE385E99FF003784FE003786FF003783FE003583FF0038
      84FE003785FF003782FE003480FF00296FFE606571FF6E6E6E8B000000010000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000004F4F4952C4B10CFFC4B10CFFC4B00BFFCFBC1CFFDBC82EFFD9C6
      2DFFC0820EFFC07B0BFFBF7A0AFFB46E0FFFA24831FFA24435FFA24334FFA243
      34FFA24234FFA24234FFA74637FFAC4B3BFFAD4B3BFFAD4B3BFF555150590000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003B3B3B3C4D4C4C4F525252558C85
      7CAC66380CFF6F3D10FF794A1EFB85572FF65151515300000000000000005959
      65694641C0E6000000005C59B1CC251FCCFF251FCCFF251FCCFF3833C5F25353
      5A5D0808080990857AAF7D4717FF7F4B1EFC7C4818FE7A4516FF784415FF7442
      13FE643A10FD918577D03B3B3B3C00000000000000015A5D616E1352ADFF1453
      ADFF0F4699FF1554B0FF1454AFFF1151ACFF0F4EA6FF0B499FFF084599FF053F
      92FF808387FF949494FF627594FF003A89FF003C8CFF003C8CFF003D8DFF003E
      8EFF013E8FFF003B8BFF003887FF002E77FF626774FF909090D4040404050000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000010101011C2AE1EF6C4B10CFFC4B10CFFC4B00BFFD0BC1CFFD9C6
      2DFFC07C0CFFC07B0BFFBD790BFFA65129FFA34536FFA24435FFA14334FF9F42
      33FF9D4133FFA14536FFA8493AFFAA4A3BFFAB4A3BFFAC5345F8141414150000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000404040561605F67735335EF6336
      0CFE6A3A0EFF734112FE784415FF9C8975D60B0B0B0C000000005A5A666B251F
      CAFE2620CBFE1D1D1D1E65647A82433FC0E8605EACC43732C4F2251FCCFF2721
      C9FD53535A5D0E0E0E0F977F6AD0977E66E04A49494C958474BF794616FE7945
      16FE67390DFE5D3108FE8E7E6DD930303031000000015A5D616E1656B2FF1958
      B4FE11499EFF1757B2FE1655B2FF1554ADFE104FA8FF0D4B9FFE09469BFF0640
      91FEBDBFC3FFE2E2E2FE7D92AFFF003D8CFE033F91FF064293FE074296FF0743
      94FE054195FF044191FE003D8DFF00347FFE5A616EFFA1A1A2FC2C2C2C2D0000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000040404058E8962ACC5B10DFFC4B10CFFC4B10CFFC4B00BFFCEBA
      1CFFC1810EFFBF7A0CFFB56F11FF9E4335FF9E4334FF9D4334FF983E34FF9936
      3AFF9B333FFF9E3442FF9E3540FF9E393DFF9F403AFF886F6BB2040404050000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000001262626278A75
      61D06D3D0FFF744213FF7A4616FF827F7C8F0000000021212122312BC7F7251F
      CCFF251FCCFF4F4E55582020202112121213161616170E0E0E0F69679BAC251F
      CCFF3934C4F1171717182B2B2B2C998470DB0909090A03030304726E697F7946
      16FE64370BFF5B3007FF5A2F06FF8F8B86AC000000015A5E616E1858B7FF1A5A
      B9FF134BA1FF1757B5FF1757B4FF1554B0FF1251ABFF0D4BA2FF08459AFF043F
      91FFC0C3C7FFFFFFFFFFA1B6D3FF013D8EFF054195FF084598FF08479AFF0845
      99FF084498FF064296FF044093FF003887FF5B6370FFA6A6A7FF6B6B6C7D0000
      0000000000000000000000000000000000000000000000000000000000000202
      02031B1B1B1C657072816DB8B2E3C4B111FFC5B10DFFC4B10CFFC4B10CFFC3B0
      0BFFC08A0EFFB9780EFFC1955DFFD0B0ABFFD0B0ABFFAF7472FF9C2E46FFA32D
      49FFA32D4AFFA32C49FFA32C49FFA32B48FFA22A47FF984C5EE26A62647F1A1A
      1A1B020202030000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000E0E
      0E0F928170C2774415FE83542AF64D4C4C4F0000000068678089251FCCFF3C36
      C3EE65647B8369688995000000006360A8BF2C26C8FB5151595C070707084D4A
      BADD251FCCFF6362747A00000000626261660A0A0A0B00000000010101028980
      77A567380CFF5E3208FE5A2F06FF836C57E4000000015A5E616E195AB8FF1B5C
      B9FE144DA4FF1A5AB6FE1757B4FF1756B0FE1352ACFF0F4DA3FE08459AFF0440
      90FEBFC2C6FFFDFDFDFEA2B7D4FF023E8DFE074296FF0A4799FE0C489DFF0B48
      9BFE09479AFF094597FE074296FF023E8DFE5E6674FFA9A9AAFE9B9B9CCB0303
      030400000000000000000000000000000000000000000000000007070708575B
      5C6557C4DCE840DAFCFF40DAFCFF96C167FFC5B10DFFC5B10DFFC4B10CFFC4B1
      0CFFBF9C10FFDDC7A3FFF9F9F9FFFAFAFAFFFAFAFAFFF9F9F9FFD3ADB7FF9F2D
      49FFA22D49FFA22D4AFFA32C49FFA32C49FFA32B48FFA32B48FFA22A47FF9B47
      5BE7585555630707070800000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000F0F0F10937C66CF937458E233333334000000005E5BAFC9251FCCFF5A5A
      666B3E3E40425F5CAEC6000000006764A2B6251FCCFF4843BFE4010101026362
      767D251FCCFF6563A6BB00000000111111120404040500000000000000005C5A
      59606A3A0EFF603409FF5A3006FF846D58DE000000015B5E616E1B5CBBFF1B5E
      BDFF154FA6FF1859B8FF1757B5FF1655B2FF1352ADFF0F4DA5FF084599FF003D
      8EFFBCBFC3FFFDFDFDFFA2B6D4FF003C8EFF064295FF09469AFF0C489FFF0C48
      9FFF0B489DFF09479BFF084699FF033F91FF6C7585FFA8A8A9FFBEBEBFFA2626
      26270000000000000000000000000000000000000000060606076C80859642D9
      FBFE41DBFDFF40DBFDFF40DBFDFF4AD7EBFFB5B72FFFC5B10DFFC5B10DFFC4B0
      0CFFD0C358FFF9F9F9FFFAFAFAFFFAFAFAFFFAFAFAFFFAFAFAFFF9F9F9FFB46B
      87FF992A4CFF9C2B47FFA22C49FFA32C49FFA32C49FFA32B48FFA32B48FFA22A
      47FFA02A47FE77686C9506060607000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000232323249B897BCC1515151600000000514EB9DA251FCCFF2F2F
      303169678792696799A9000000005B5A676C251FCCFF251FCAFE1F1F1F204646
      4B4D251FCCFF5956B2CF00000000000000000000000000000000000000006E6C
      6A766B3B0EFF63360BFE5B3006FF91887FBC000000015B5E616E1B5EBDFF1D60
      BEFE1652A9FF1B5DBBFE1959B8FF1757B2FE1453AEFF0F4DA3FE074398FF023E
      8DFEB4B7BBFFF4F4F4FEA0B4D1FF013D8DFE064396FF0B499CFE0D4BA1FF0E4C
      A0FE0D499FFF0D499DFE0B489DFF064293FE687181FF9E9E9FFEC6C6C7FF6868
      687400000000000000000000000000000000000000005B63656B43D9FBFE41DA
      FDFF41DAFDFF40DAFDFF40DAFDFF3FDAFDFF57D3D5FFBAB627FFC5B10DFFC4B0
      0DFFE2DB9FFFFAFAFAFFFAFAFAFFFAFAFAFFFAFAFAFFFAFAFAFFFAFAFAFFD7A9
      C9FFA4267DFF9F266CFF9A2A4CFFA12C49FFA32C49FFA32C49FFA32B48FFA32B
      48FFA22A47FFA02B48FE605A5B6B000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000005050505208080809000000005C59B0CB251FCCFF3F3F
      42445E5D6C715551B7D6030303044B4B5153251FCCFF251FCCFF252525264646
      4B4D251FCCFF6462A7BD00000000000000000000000000000000101010119782
      6ED46C3B0EFF62350AFF78593BEE3F3F3F41000000015B5E616E1B5FBDFF1C60
      BFFF1653AAFF1C5FBFFF1B5CBBFF1857B5FF1250ACFF0C49A1FF064295FF003C
      8CFFA3A6AAFFE4E4E4FF99ADCAFF003C8EFF064397FF0B489FFF0D4BA2FF0E4C
      A3FF0E4CA3FF0D4AA0FF0C489EFF054093FF747D8DFFABABACFFC5C5C6FF9A9A
      9BC402020203000000000000000000000000000000005B6367683DC4FAFE3BC5
      FBFF3BC5FBFF3AC4FBFF3AC4FBFF39C4FBFF39C4FBFF4BC2DFFFA0B854FFC5B2
      11FFE4DDA0FFFAFAFAFFFAFAFAFFFAFAFAFFFAFAFAFFFAFAFAFFFAFAFAFFD8A9
      CAFFA52781FFA62680FFA32678FFA12E57FFA93154FFAA3154FFAA3153FFAA31
      53FFA93053FFA93255FE60585A66000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000A0A0A0B07070708000000006968848D251FCCFF6967
      96A50E0E0E0F504DB8DA5552B7D5433FC0E8251FCCFF5856B3D0010101026967
      8B97251FCCFF6362767D0000000000000000000000000303030487837F947442
      14FE6B3B0EFF765333F06262616700000001000000015B5E616E1C60BCFF1E63
      BDFE1654AAFF1C60BDFE1B5EBCFF1958B3FE3E6DB6FF3D6AADFE3963A7FF365F
      9FFE979A9FFFC9C9C9FE9AAAC3FF3661A3FE3865ABFF3C6CB1FE3769B2FF0E4D
      A3FE0E4DA5FF0F4DA2FE0A479DFF054090FE6B7483FFAAAAAAFEC8C8C8FFCDCD
      CDF81F1F1F2000000000000000000000000000000000000000016D848C8E3DC4
      FAFE3BC5FBFF3BC5FBFF3AC4FBFF3AC4FBFF39C4FBFF39C4FBFF39C3FAFF4EC2
      D9FF91D3D5FFF9F9FAFFFAFAFAFFFAFAFAFFFAFAFAFFFAFAFAFFF9F9F9FFB068
      B0FFA3277DFFA62781FFA62680FFA32676FFA42F55FFAA3154FFAB3254FFAB32
      54FFAA3456FE7D6B718C00000001000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000606060620909090A00000000252525262E28C9F92620
      CBFE5B5A676C111111126262747B6A6894A2646479811313131446464A4C2C28
      CAFA3530C7F41A1A1A1B000000000000000008080809827F7C8D814F24FB7240
      12FF8F755CE0525151540000000000000000000000015B5E616E1D62BBFF1D62
      BDFF1754AAFF1B5EBCFF1A5DBBFF1955ABFFCFD0D1FFBABABBFFABACACFFADAE
      AEFFAEAEAFFFB4B4B4FFBEBEBEFFC8C9C9FFD3D4D4FFDEDFE0FFC7D1E0FF0B4B
      A3FF0D4BA3FF0E4CA4FF0A489EFF043F92FF7A8592FFC2C2C3FFC8C8C8FFD6D6
      D7FF6161616B0000000000000000000000000000000000000000000000005156
      585959BCE2E73BC5FBFF3BC5FBFF3AC4FBFF3AC4FBFF39C4FBFF39C4FBFF38C4
      FBFF39C4FAFFB5E6FAFFF9F9FAFFFAFAFAFFFAFAFAFFF9F9F9FFC6AAE7FF691C
      C1FF982480FFA52780FFA62781FFA52680FFA2296BFFA83154FFAB3255FFA954
      6DE5524E4F560000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000001414141582807E8B000000010000000000000000605F7076251F
      CAFE2620CBFE6461A8BE58586367414144464D4D5356696894A32A24C9FC251F
      CAFE5857626600000000000000012A2A2A2B948C85AC815125FA8F6B4CE97F7B
      778B1B1B1B1C000000000000000000000000000000015B5E616E1C61BAFF1E64
      BBFE1857AAFF1D61BAFE1A5DBBFF1B58ACFEEEEEEFFFFAFAFAFEE0E0E0FFB9B9
      B9FEA8A8A8FFA8A8A8FEADADADFFB2B2B2FEBBBBBBFFC5C5C5FEB4BECDFF0E4E
      A6FE0F4DA6FF104FA6FE0C49A0FF064193FE6C7585FFB2B2B2FEC4C4C4FFD6D6
      D7FE979797BC0000000100000000000000000000000000000000000000000000
      00000D0D0D0E636F74765BB4D8E33CC5FBFF3AC4FBFF3AC4FBFF39C4FBFF39C4
      FBFF38C4FBFF3BC1FAFF64AFF5FFA0C7F6FFA0C6F5FF8E6ED8FF691DC8FF681B
      C7FF842198FFA4277DFFA62781FFA62781FFA5267DFFA05472E06A6164730C0C
      0C0D000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000051504F5387827E99000000000000000000000000000000005F5F
      6F752E28C9F9251FCCFF251FCCFF251FCCFF251FCCFF251FCCFF322DC6F65A5A
      6569010101023D3D3D3E797775819C8A7ACC95877ABA6A6866701C1C1C1D0000
      000000000000000000000000000000000000000000015B5E616E1C61B9FF1C63
      BBFF1758ABFF1D63BCFF1B60BBFF1858B2FF4B6B9AFF4D6C98FF4B6A95FF4866
      90FFB7B9BBFFBDBDBDFF818EA1FF314F80FF335183FF375588FF345893FF1251
      ACFF1352ADFF1150A9FF0E4BA3FF064296FF717A89FFCBCBCCFFDDDDDDFFCDCD
      CDFFDADADAF71717171800000000000000000000000000000000000000000000
      0000000000000101010261809FB31D93F6FF29A3F8FF2FADF9FF31B0F9FF2FA9
      F7FF2799F4FF147BF1FF0E73F0FF0D73F0FF0E6FEAFF5F24C4FF691CC8FF681B
      C8FF791FA8FFA3277DFFA62881FFA62781FFA62781FF84687CAA000000010000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000089827BA08F8781AD000000000000000000000000000000000000
      0000242424256766838C5D5BAFC9524FB7D85E5BAEC769687F87202020211C1C
      1C1D2929292A12121213141414150D0D0D0E0000000100000000000000000000
      000000000000000000000000000000000000000000015B5E616E1C61B9FF1E64
      B9FE1757AAFF1A5FB2FE185BB2FF1959B4FE1554B0FF104FA6FE0D4AA1FF0D4A
      9EFEC1C4C8FFFBFBFBFEA0B6D5FF0B489DFE0D4AA2FF104EA6FE1150AAFF1554
      AEFE1555B1FF1351AAFE0F4CA4FF084496FE747D8DFFB9B9B9FECDCDCDFFD4D4
      D5FEE4E4E4FE5B5B5B6200000000000000000000000000000000000000000000
      0000000000001A1A1A1B1D87EEF91286F6FF1186F6FF1185F5FF107BF3FF1074
      F0FF0F74F0FF0F74F0FF0E73F0FF0E72EFFF2C52D4FF671CC5FF691CC8FF691C
      C8FF7A20B0FFA72987FFA62881FFA62881FFA62781FFA33484F5131313140000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000001010102937F6CD096897CCB020202030000000000000000000000000000
      00000000000000000000000000000000000003030304323232337573727D9692
      8EA70D0D0D0E0000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000015B5E616E1B60B7FF1D62
      B9FF1656A7FF073C8EFF05398DFF1656B0FF1757B4FF1252AEFF1150AAFF104F
      A8FFC0C4C8FFFDFDFDFFA9C0DEFF0D4BA3FF104FA8FF1251ACFF1352AEFF1554
      B1FF1554B1FF1351ACFF0F4CA5FF084499FF88919EFFD2D2D3FFE6E6E6FFD3D3
      D3FFE7E7E8FF959595B300000001000000000000000000000000000000000000
      00000000000052575B5F1286F5FF1286F6FF1285F5FF117CF3FF1175F0FF1074
      F0FF1074F0FF0F74F0FF0F74F0FF1767ECFF5F25C4FF691DC8FF691DC8FF691C
      C8FF8022ADFFAC2D91FFAA2A8AFFA62881FFA62881FFA52781FF504C4F550000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000E0E0E0F86694FE08E7760DF2A2A2A2B0000000000000000000000003232
      32334C4C4C4E4E4D4D5062616167878480979E8D7ED0906846EF7E491AFE5D5C
      5B60000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000015A5E616E185CB4FF1B60
      B5FE1453A5FF011880FE00227BFF1658AEFE1959B6FF1959B4FE1858B5FF1353
      ACFE234E8DFF2B548CFE205096FF1251A8FE1252ADFF1655AEFE1555B1FF1555
      AEFE1252ADFF1553ADFE104EA8FF0A479BFE8B94A2FFC1C1C1FED1D1D6FFD3D3
      E3FED9D9DAFFDEDEDEF114141415000000000000000000000000000000000000
      00000000000066798C921387F6FF1286F5FF127CF3FF1276F0FF1175F0FF1175
      F0FF1074F0FF1074EFFF1A64EBFF511DEAFF691EC9FF6A1EC9FF691DC8FF691D
      C8FF8B26A4FFAD2D92FFAE2D93FFAA2A8AFFA62881FFA62881FF776671870000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000131313147A5C3FE3704821F76564646A0000000000000000000000000404
      04055A59585E926D4FE67C4717FF7C4717FF7C4617FF7D4718FF96785DE22020
      2021000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000015A5D616E1354ADFF185A
      B3FF1350A4FF002098FF002588FF1457ADFF185AB6FF1A5DB7FF1A5AB7FF1453
      AEFF104FA9FF0F4FA8FF1151ABFF1353AEFF1453AEFF1453AFFF1655B2FF1352
      ADFF1150AAFF1454AFFF1151ACFF0B4AA2FF8D97A5FFC7C7C7FF9F9CE3FFACAA
      E6FF766EDAFFD1CFEEFF54545459000000000000000000000000000000000000
      0000000000006484A4AB1386F5FF137DF3FF1276F0FF1276F0FF1276F0FF1175
      F0FF1174EFFF2D4DE8FF5916EDFF600FF5FF691EC9FF6A1EC9FF6A1EC9FF6A1E
      C8FF9B2A97FFAE2E94FFAF2E94FFAE2D93FFAA2A8AFFA62881FF886A80A00000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000F0F0F10775A3EE362350AFF95887BCE1B1B1B1C00000000000000000000
      000000000000464646488C6440EE7D4718FE7D4718FF7D4718FE978D84B80000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000015A5C616E0B4BA0FF1253
      AAFE104CA1FF0125A3FE002995FF1455AAFE175AB4FF195CB4FE1657B3FF1353
      AAFE1150AAFF1352AAFE1252ADFF1453ACFE1353AEFF1454ACFE1454AFFF1353
      ACFE1050AAFF1555AEFE1454AFFF0F4EA5FE8F99A8FFDCDCDCFECCCCCFFFDCDC
      DCFEC9C7E5FFC4C2EFFE8888889F000000000000000000000000000000000000
      00000000000066809A9E147DF3FF1376F0FF1376F0FF1376F0FF257EE8F76882
      A5AA6853CFDE6011F3FF6110F5FF6110F5FF6A1FC9FF6A1FC9FF6A1EC9FF7848
      B2E18C6D87ADAF3E98F7AF2F94FFAF2E94FFAE2D93FFAA2A8AFF806A7A920000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000003030304836F5AD35C3006FF613A11FC928C85B93A3A3A3B0A0A0A0B2E2E
      2E2F78767480906C4DEC794515FF7A4516FF7A4515FF7A4515FF72706E7B0000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000001595C606E054393FF0948
      9BFF0D499CFF001E96FF002894FF1152AAFF1758B2FF1657B2FF1353ADFF0E4E
      A5FF0D4DA3FF0E4CA4FF0F4EA6FF104FA9FF1050AAFF104FA9FF1251ACFF1454
      AFFF1252ACFF1554B0FF1656B2FF0D4CA5FF919BA9FFE2E2E2FFF8F8F8FFEEEE
      EEF7AFAFAFC46A6A6A741E1E1E1F000000000000000000000000000000000000
      00000000000031323233697D969B6882A1A66775888B4D505456121212130000
      0000635D6F726211F5FF6211F6FF6110F5FF6A1FC9FF6A1FC9FF6A1FC9FF6661
      6C7C0000000111111112514D50547C6A78888D6F87A1846D7F942929292A0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000857D74A85A2F06FF5B3006FE5B3108FE7F6349E882684FEA7E5E
      40EC724113FE754213FE734112FF744314FE8D6B4DE6754416FE525252550000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000001595B5F6D003D8CFF0243
      91FE0A4595FF001A8BFE002286FF1152A6FE1253ABFF1252A8FE0F4EA6FF0C4B
      9EFE0A489DFF09489AFE09489CFF0D4B9EFE0D4BA1FF0E4CA1FE0E4DA5FF1554
      ADFE1555B1FF1757B1FE1656B3FF0D4BA0FE9098A4F89D9D9DC06363636C2020
      2021020202030000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000C0C0C0D743BDAE56211F6FF6211F5FF6B20C9FF6B20C9FF7842B8E71414
      1415000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000004F4E4E525A2F06FF5A2F05FF5A3006FF5B3007FE5A2F06FF5B31
      07FE613409FF6F3E10FE744B24F78A847F9C282828298C7057DC464646480000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000001585B606C003F8DFF0343
      94FF0A4595FF00219DFF002790FF0E4FA5FF0E4FA5FF0B4A9EFF0B4B9EFF0644
      96FF024192FF024091FF034192FF064598FF09489CFF09489CFF0B4A9FFF1050
      A9FF1656B2FF1655B1FF1454B0FF0A479CFF63656B9615151516000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000504D55576314F3FE6211F5FF6B20C9FF6D22C8FE5553575F0000
      0001000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000005050506877664CB5A3006FE5A2F06FF5B3007FE5A2F06FF5C31
      07FE5F3208FF896F58E15757565A030303040000000055545358404040420000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000055595E65003B88FF0444
      92FE094494FF00198BFE00268EFF094899FE054495FF023D88FE013B89FF0038
      82FE00337BFF00337BFE00347DFF003A84FE013D8CFF03408FFE054395FF0B49
      9CFE0E4DA5FF0E4DA2FE0B4A9FFF033C88FE5B5C5F7308080809000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000007266888C6314F3FE6D23C9FE72697F93020202030000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000002323232486725FD45A2F06FF5A2F05FF5B3107FE8065
      4CE47B78758A1B1B1B1C00000000000000000000000004040405262626270000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000001C1C1C1D52565B605357
      5C6153565C6152545C6152555C6153575C6153575C6152565C6152565B615256
      5B6152565B6152565B6152565B6152565B6152565C6153575C6153575C615357
      5C6153575D6153575D6153575C615255595F0E0E0E0F00000001000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000015C5865675E59636902020203000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000006060607454544475F5D5C65404040421010
      1011000000000000000000000000000000000000000000000000000000000000
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
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000010101020F0F0F102323
      232434343437303030321F1F1F20101010110606060701010102000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00005F5F5F76161616F4000000FF000000FF000000FF000000FF161616F45F5F
      5F76000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000909090A262626273A3A
      3A3E3A3A3A3E2323232408080809000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000003030304202020215D61647A596D
      79B4516A7AC25E6A72AA5E60617B4E4E4E593939393D26262628131313140808
      0809000000010000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000010101021717
      17183B3B3B3F494949524444444B3333333622222223131313140909090A0303
      0304000000010000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000002222
      2223000000FE000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FE222222230000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000272828295F6382AE3040AFE81C30
      C1F62D3DADEA535983C35C5D5E760E0E0E0F0000000000000000000000000000
      0000000000000000000000000000000000000000000008080809212121222727
      27291B1B1B1C0707070800000000000000004445464B457594D32486C5FF40A2
      E2FF41A8E8FF3499D7FF2381B8FC2F7199EC4E6C7EC95F696FA85F6263805252
      52603A3A3A3E2828282A141414150909090A0202020300000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000202020340404046685C
      57BC6A4635E976432CF571442FF1664739E4625048D2665C58BA6763629E5F5F
      5E7E5151515F404040462E2E2E301C1C1C1D0F0F0F1006060607010101020000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000003A3A
      3A3E000000FF000003FF0000BBFF0000DFFF0000DFFF0000BBFF000003FF0000
      00FF3A3A3A3E0000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000646881902E46DAFF5A6DE3FF5D70
      E3FF596DE3FF2840D9FF626680A3080808090000000000000000000000000000
      0000000000000000000000000000000000012121212261727FA943759BDD4170
      93DB566B7BBE5D5E5F7921212122000000005F7A8BAD2684CFFF43A6EBFF49AC
      EDFF5BA9E0FF4EB0F1FF46B4F7FF48B0EEFF3FA2DEFE3691C7FA34779FEC3D69
      85DA586973B662676A9253535463434343492C2C2C2E1A1A1A1B0B0B0B0C0303
      0304000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000002929292B6B4B3CE28E4C
      2EFFAF613DFFB2623EFFB3633EFFB4643FFFB2633EFFA85C39FF9C5431FF914B
      2AFF81462AFA704633EE644A3DDF63554ECA66605DB2656362955C5B5B734C4C
      4C573B3B3B3F2828282A181818190C0C0C0D0404040500000001000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000003C3C
      3C40000000FF000020FF0000FFFF0000FFFF0000FFFF0000FFFF00001DFF0000
      00FF3C3C3C400000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00010F0F0F100D0D0D0E0202020300000000040404054A4A4D516E6F7A847576
      828E6E6F7A8348484C4F05050506000000000000000000000000010101021818
      18191515151603030304030303044546464C4483AEE32F97DCFF2E97DBFF2A92
      D9FF228BD5FF2374B4F55E60617D08080809547D96C22F8DDAFF41A3E9FF4AA7
      E7FFE08D6DFFDA9781FFAC9598FF889CB4FF66A9D6FF5BB6EDFF55BFFCFF51BC
      F8FF41A8E2FF2D8BBFFF27658BF4406780DB5B6870B2626668925858596B4545
      454C2B2B2B2D1313131401010102000000000000000000000000000000000000
      00000000000000000000000000000000000000000000676361848D4D2FFF9E58
      38FFB2633EFF724028FF3E2315FF502D1CFF6B3C26FF8A4E31FF9A5838FFA45E
      3CFFAD6440FFB56943FFBA6B45FFB56842FFA85E3AFF9C5533FF8F4C2CFE7D47
      2CF76B4837E9624C42D9655852C466625FA96362618A565656694747474F3333
      3336161616170101010200000000000000000000000000000000000000004848
      484F5A5A5A6D1919191A0000000000000000000000000F0F0F10656565871F1F
      1FEF000000FF000020FF0000FFFF0000FFFF0000FFFF0000FFFF00001CFF0000
      00FF1F1F1FEF65656587101010110000000000000000000000001919191A5A5A
      5A6D4747474F00000000000000000000000000000000000000000C0C0C0D5553
      52617C6157BA6D64619D565656673A3A3A3E1D1D1D1E0909090A000000010000
      00000000000000000000000000000000000000000000060606075B5F61724E73
      8ECE5E6972AB55565666636A708D3D9AD5F93BA3E4FF45AEEAFF44ACE9FF3CA4
      E4FF339BDEFF2891D8FF5F6D79AD0B0B0B0C547D96C2318FDAFF40A2E9FF49A3
      E5FFE6A992FFFEE7DDFFFAD7CBFFF0BCAAFFDB9886FFBF887AFF978F99FF76A2
      C3FF5CBCF4FF4FB0E6FF428DB6FF408AB1FF367BA3FC336F92F33A657FE14C67
      75C86165688E4A4A4A5417171718010101020000000000000000000000000000
      00000000000000000000000000000000000000000000726662AA975637FFA15A
      39FFB2643FFF060201FF000000FF000000FF000000FF000000FF0B0603FF2012
      0BFF362015FF4E3020FF69412CFF8A5439FFA86745FFB56E4AFFB9714BFFBD71
      4BFFBE714AFFBE7049FFB46843FFA75E3AFF9A5331FF8B4B2BFD754730F36749
      3BE3675C57BC4343434A02020203000000000000000000000000656565860000
      00FF000000FF181818F36161617B060606074646464C2C2C2CE8000000FF0000
      00FF000010FF000067FF0000EDFF0000EDFF0000EDFF0000EDFF000069FF0000
      14FF000000FF000000FF2B2B2BE84646464C060606076161617A181818F30000
      00FF000000FF656565860000000000000000010101023938383C846155BEB93B
      14FEDA603CFFCF5832FFBA4722FC8E4A33E4785C53C0696362904F4F4F5B3232
      3235161616170606060700000001000000000E0E0E0F63727EA22C92D7FE268F
      D7FF2089D3FF227DC2FA4DB5EEFF4BB3EEFF54BCF4FF50B9F2FF4AB2EDFF43AB
      E9FF3298DAFE5487ACCF3B3C3C3F00000001557D96C23391DBFF3FA0E7FF47A1
      E4FFE6AF9AFFFEF6F1FFF6EEE8FFFAF6EFFFFFFAF6FFFEF3EBFFF9CFBEFFF3AB
      94FFDE8D73FFA7756DFF6E6F7AFF5E7C96FF518EAFFF4D97BDFF4B96BEFF458E
      B4FF296C94FA4E6775C74B4B4B55131313140000000000000000000000000000
      00000000000000000000000000000000000000000000736762AC9A5939FFA35D
      3BFFB1633FFF000000FF000000FF000000FF000000FF000000FF000000FF0000
      00FF010101FF020202FF040404FF050505FF080707FF1C1410FF39271DFF5339
      2AFF714D37FF946246FFB17351FFCD865CFFCE855BFFCB8157FFC77A52FFC072
      4BFFB06540FF724E3DE42A2A2A2C0000000000000000252525260B0B0BF90000
      00FF000000FF000000FF000000FF313131E5020202FD000000FF00001EFF0000
      A0FF0000F8FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FAFF0000A9FF000025FF000000FF020202FD313131E5000000FF000000FF0000
      00FF000000FF0B0B0BF9252525260000000044424147AD411DF6CE4723FFD64E
      2AFFE56A47FFCA9978FFD5A386FFEE8561FFDE6843FFCC562FFFB04724F8864E
      3CDB74615BB463615F804747474F3333333652759CC0309EEBFF369FE1FF2C94
      DAFF2B93D9FF2A93D9FF48B1ECFF5EC6FAFF5AC2F8FF55BDF4FF4599CDF36572
      7B8F2829292A000000000000000000000000557E96C23493DCFF3C9EE7FF459F
      E3FFE7B19BFFFFF8F4FF9691CDFF9692CCFFFFFAE4FFFEEFDDFFFDEFE3FFFEF1
      E5FFFCEBE1FFD2BBB3FFB18C83FFA77368FF945E54FF805E5EFF657487FF548A
      A9FF4EA2CCFF2C84B3FA6165688D262626280000000000000000000000000000
      00000000000000000000000000000000000000000000736762AC9E5C3CFFA65F
      3DFFB26540FF000000FF000000FF000000FF000000FF000000FF000000FF0101
      01FF030303FF050505FF060707FF080808FF0A0A0AFF0B0B0BFF0C0C0CFF0D0D
      0EFF0E0E0FFF0F0F0FFF0F0F0FFF131211FF2E231DFF4D382CFF855C45FFE39D
      6FFFCD8257FFB36742FF676361850000000000000000626262B3000000FF083A
      00FF24E500FF189A00FF021300FF000000FF000000FF000060FF0000F4FF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000F7FF00006BFF000000FF000000FF120013FF980099FFE500
      E6FF3C003DFF000000FF616161B300000000665D5A6ECB4622FFD74F2CFFD750
      2DFFE56946FF8AB193FF0EE9CDFFC6F683FFFCEA4EFFF7C456FFF4A35FFFED80
      5BFFDB6641FFC8522BFF9E4527F231609BEA0063DDFF2194F1FF3DA5E5FF329B
      DEFF43ACE9FF3EA6E5FF369FE0FF37A0E1FF48B0ECFF38A0E2FF606971A30B0B
      0B0C00000000000000000000000000000000557E96C23695DEFF3B9DE6FF439D
      E1FFE8B39EFFFFF8F3FFCAC9E0FF2E39C6FF9390CCFF3740C9FF9792C5FFFFED
      D7FFF6DFCBFFC8B3A2FFBEADA0FFBCB3AAFFBBB1ABFFB9A29BFFB38172FFB858
      3FFF82A4BAFF4FBBEDFF5B6B75B12D2D2D2F0000000000000000000000000000
      00000000000000000000000000000000000000000000736762ACA25F3FFFA962
      40FFB36641FF000000FF000000FF000000FF000000FF000000FF020202FF0404
      04FF060606FF080808FF0A0A0AFF0B0B0CFF0D0D0DFF0F0F0FFF101010FF1111
      11FF121212FF121212FF131313FF131313FF121313FF121212FF121212FF5A42
      33FFE9A071FFC2754DFF746761AE0000000040404045000000FE000100FF21D2
      00FF28FF00FF28FF00FF25EF00FF116E00FF00007AFF0000FEFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF000088FF69006BFFEE00EEFFFF00FFFFFF00
      FFFFD300D4FF010002FF000000FE40404045675E5A6ECC4824FFD8522FFFD854
      31FFE46845FF89B092FF00E9CCFF08E9CCFF9FF395FFFFFE3FFFEFED56FFE0D9
      69FFFBDE54FFF1B467FF583C36FF165093FF007DF8FF0F99FAFF44ACE9FF4DB5
      EFFF5BC3F8FF56BEF5FF4DB6F0FF44ADEAFF3CA5E4FF359EE0FF626D77A30707
      070800000000000000000000000000000000567F96C23898DFFF3A9BE6FF429C
      E0FFE8B5A0FFFFF8F3FFF9F6EDFF6C71CBFF0019DDFF4C55CBFFE3DBD9FFFEDF
      C9FFF2CFBBFFC0AD9EFFC1A997FFD0B097FFD7B69CFFDDBDA3FFE5D7C9FFEFB0
      9DFF8B97A6FF4EBBEEFF5B6B76B22D2D2D2F0000000000000000000000000000
      00000000000000000000000000000000000000000000736762ACA66342FFAC65
      42FFB46742FF000000FF000000FF000000FF000000FF020202FF040404FF0606
      06FF090909FF0B0B0BFF0D0D0DFF0F0F0FFF111111FF121212FF131314FF1515
      15FF161616FF171717FF171718FF171718FF171718FF171717FF161616FF1817
      16FFE7A072FFC67850FF766861B1000000004E4E4ECE000000FF0E5D00FF28FF
      00FF28FF00FF28FF00FF28FF00FF178E5DFF0000FEFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF7000EDFFFF00FFFFFF00FFFFFF00
      FFFFFF00FFFF5E005FFF000000FF4E4E4ECE675E5B6ECD4B26FFD95633FFDA59
      35FFE36744FF89AF92FF00E9CCFF00E9CCFF00E9CCFF6EEFB1FF6466ADFF1A27
      BEFFAFAB87FF5E5788FF362D2FFF2B405EFF00ADFFFF00CAFEFF31A4EFFF44AD
      EAFF4DB5EFFF54BCF3FF5AC2F7FF5AC2F7FF54BCF4FF42A2DCFB4445454B0000
      000000000000000000000000000000000000567F96C23A9AE1FF3998E4FF4099
      DFFFE9B7A1FFFFF9F5FF888AD2FF1D2FD0FF595FCAFF444DC5FFEEEAE0FFFFDD
      CAFFD5A089FF372E2CFF596777FFA0BEDDFFB9C9DBFFD8BAAFFFF5BB9EFFF4AE
      9AFF8999AAFF4DBAEDFF5B6B76B22D2D2D2F0000000000000000000000000000
      00000000000000000000000000000000000000000000736762ACAA6745FFAF68
      45FFB66944FF000000FF000000FF000000FF020202FF040404FF060607FF0909
      09FF0C0C0CFF0E0E0EFF101010FF121212FF141414FF161616FF181818FF1919
      1AFF1B1B1BFF1B1B1CFF1C1C1CFF1C1C1CFF1C1C1CFF1B1B1CFF1B1B1BFF1919
      19FFDF9A6DFFC97B53FF766861B100000000080808FB000000FF0D5400FF27FD
      00FF28FF00FF28FF00FF22D919FF0005F1FF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000E7FF0000B7FF0000B7FF0000E7FF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FBFFC300F2FFFF00FFFFFF00
      FFFFFD00FDFF560057FF000000FF060606FC675E5B6ECE4E29FFDA5B37FFDB5E
      3AFFE36743FF88AE91FF00E9CCFF00E9CCFF00E9CCFF13EACEFF454ABFFF1A2B
      C5FF1827C0FF31285AFF413337FF433539FF03C3F1FF00F5FFFF00E3FFFF03B9
      FCFF19A3F4FF33A2EDFF47AFEBFF4EB7F0FF4AA3D7F6575A5C67010101020000
      000000000000000000000000000000000000567F96C23C9CE2FF3897E4FF3E97
      DEFFE9B9A3FFFFF8F5FFD8D5E7FFCBC9E4FFEEEAEEFF4F54C6FF9190CAFFFFF5
      E4FFDED4C7FF4F5965FF73B5EAFF71BEFFFF9E889CFFC8563DFFD7512DFFE05B
      35FF86A1B4FF4BBAEDFF5B6B76B22D2D2D2F0000000000000000000000000000
      00000000000000000000000000000000000000000000746862ACAF6B48FFB26B
      47FFB76A45FF000000FF000000FF0A0A0AFF5C5C5CFF767676FF565656FF1313
      13FF0F0F0FFF111111FF131313FF161616FF181818FF1A1A1BFF1C1C1DFF1E1E
      1EFF202020FFC7C7C7FFA9A9A9FF868686FF646464FF424242FF212121FF1D1E
      1EFFD9966AFFCB8055FF766861B100000000646464AB000000FF000000FF0837
      00FF20CA00FF28FF00FF0D5796FF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000E8FF000054FF000000FF000000FF000000FF000000FF000053FF0000
      E8FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF3C00EFFFFE00FFFFCA00
      CBFF370037FF000000FF000000FF646464AC675E5B6ECF522DFFDC603CFFDD64
      40FFE26643FF80AD8FFF00E9CCFF00E9CCFF00E9CCFF21EAD1FF2632C0FF1A2B
      C5FF1A2BC5FF21259CFF443350FF523B3FFF395E81FF1099C5FF00C2FAFF00C4
      FFFF00B4FFFF00A1FFFF068FFBFF3D84C5FF6F6463B30E0E0E0F000000000000
      000000000000000000000000000000000000567F96C23DA0E3FF3595E3FF3C95
      DDFFEABBA6FFFFF8F5FFFFFBF8FFE3EDDCFF89C786FFEFEDE7FFF0E6E4FFFFF1
      E6FFF5EADFFF96C1E9FF78BAF4FFB28F99FFFC895EFFEA734FFFD54927FFD847
      22FFB27067FF57ABD9FF5A6B76B32E2E2E300000000000000000000000000000
      00000000000000000000000000000000000000000000746862ACB46F4CFFB66E
      4AFFB86B46FF000000FF141414FFD6D6D6FFFFFFFFFFF3F3F3FFFDFDFDFFE1E1
      E1FF373737FF141414FF171717FF767676FF5B5B5BFF1F1F1FFF212121FF2828
      28FF292929FF424243FF636363FF858585FFA2A2A2FFC0C0C0FF393939FF2222
      23FFD49167FFCE8257FF766861B1000000000707070863636381121212F60000
      00FF000000FF0E5A07FF0003F2FF0000FFFF0000FFFF0000FFFF0000FFFF0000
      EAFF000022FF000000FF000000FF001026FF001026FF000000FF000000FF0000
      22FF0000E9FF0000FFFF0000FFFF0000FFFF0000FFFF0000FCFF500062FF0000
      00FF000000FF121212F66464648207070708675E5B6ED15731FFDE6642FFDF6A
      46FFE26642FF70AB8CFF00E9CCFF00E9CCFF00E9CCFF26EAD2FF1F2DBFFF172C
      CCFF142ED5FF1230DAFF353089FF624448FF593F43FF513A3EFF433A46FF3960
      90FF107CC9FF008EFCFF508CE1FFDC7454FF76625BB20E0E0E0F000000000000
      000000000000000000000000000000000000567F96C23FA1E4FF3593E2FF3B92
      DCFFEABDA7FFFFF8F5FFFDFBF9FF90D398FF2DC347FFD0E5CDFFFFF6EDFFFFF2
      E9FFFDF0E3FFA2CFF7FF9B91AAFFF38862FFF9936CFFF9936DFFE46845FFD549
      26FFD84C27FFA76760FF576B76B73A3A3A3E0202020300000000000000000000
      00000000000000000000000000000000000000000000746862ACB9744FFFBA72
      4CFFB96D47FF000000FF8E8E8EFFFFFFFFFF7B7B7BFF0B0A0BFF2F2F30FFE2E2
      E2FFD4D4D4FF181818FF1A1A1BFFBEBEBEFFACACACFF232323FF252526FF8080
      80FFABABACFF2A2A2AFF2B2B2BFF2B2B2BFF2B2B2BFF2A2A2BFF292929FF2727
      27FFCE8C63FFD08559FF766861B10000000000000000000000001E1E1E1F5757
      57C2000000FF000041FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      5AFF000000FF000D1FFF0055CFFF0068FFFF0068FFFF0055CFFF000D20FF0000
      00FF00005AFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF000048FF0000
      00FF565656C31F1F1F200000000000000000675E5B6ED25B36FFE06D49FFE271
      4DFFE16642FF6FAA8BFF00E9CCFF00E9CCFF00E9CCFF26EAD3FF1A30CFFF0C34
      EEFF0B38F7FF0D3BFBFF3E368EFF6F4A54FF6C494EFF69484DFF724C51FF593F
      44FF7C5155FF914D8DFFFA37C9FFE3724DFF76625BB20E0E0E0F000000000000
      000000000000000000000000000000000000567F96C242A4E5FF3392E1FF3891
      DBFFEBC0ABFFFFF9F5FFC5DFC5FF68C978FF46D163FF70D081FFFEF8F5FFFEE7
      DBFFFEE5D6FFBEC3D2FFEAA787FFFBA47CFFF88F69FFF9926CFFF9936DFFE972
      4EFFD44926FFDB4923FF935C4FDB646160822A2A2A2C07070708000000000000
      00000000000000000000000000000000000000000000746862ACBE7853FFBD75
      4FFFBA6E48FF010101FFCCCCCCFFFAFAFAFF101010FF0D0D0DFF101010FF6464
      65FFB3B3B3FF2C2C2DFF1E1E1EFF202021FF262627FF272728FF2A2A2AFFB3B3
      B3FF7B7B7BFF2F2F2FFF303030FF303030FF303030FF2F2F2FFF2D2D2EFF2B2B
      2CFFC8875FFFD2885CFF766962B1000000000000000000000000000000006565
      659A000000FF000072FF0000FFFF0000FFFF0000FFFF0000FFFF0000EEFF0000
      02FF000000FF0054CBFF0068FFFF0068FFFF0068FFFF0068FFFF0054CCFF0000
      00FF000002FF0000EEFF0000FFFF0000FFFF0000FFFF0000FFFF00007AFF0000
      00FF6565659A000000000000000000000000675E5B6ED4613BFFE27450FFE479
      54FFE16542FF6FA989FF00E9CCFF00E9CCFF00E9CCFF26EAD3FF1B38DFFF1946
      FEFF2853FFFF315AFFFF3055F5FF2947E4FF6F4B6EFF905B60FF8B585EFF8E5A
      60FF66865AFF75D175FFF349C4FFE2704AFF76625BB20E0E0E0F000000000000
      000000000000000000000000000000000000577F96C243A6E6FF3290E0FF378E
      DAFFEBC2ADFFFFFAF6FFECF3EBFFEBF2EBFFA9DCB1FF40D264FFD4E6D2FFFEE0
      D4FFFBB59BFFE99A80FFFBCAA2FFFECAA4FFF89973FFF8906AFFF9926CFFF993
      6DFFE46844FFD54926FFD34D2BFC995E4ED75858586B2A2A2A2C020202030000
      00000000000000000000000000000000000000000000746862ACC37D57FFC178
      52FFBB6F49FF020202FFD5D5D5FFEEEEEEFF0A0A0AFF0F0F0FFF121212FF1616
      16FF1A1A1AFF1E1E1EFF212122FF252525FF282829FF2B2B2CFF2E2E2EFFE4E4
      E4FF4E4E4FFF333434FF333334FF353535FF343435FF333334FF323233FF3030
      31FFC1825AFFD58A5EFF766962B1000000000000000000000000000000006060
      60B0000000FF00008CFF0000FFFF0000FFFF0000FFFF0000FFFF0000C2FF0000
      00FF000D1FFF0068FFFF0068FFFF0068FFFF0068FFFF0068FFFF0068FFFF000D
      20FF000000FF0000C2FF0000FFFF0000FFFF0000FFFF0000FFFF000095FF0000
      00FF606060B0000000000000000000000000675E5B6ED66641FFE57C57FFE683
      5CFFE06542FF6EA888FF00E9CCFF00E9CCFF00E9CCFF26EAD3FF2742DFFF3A5B
      F2FF5173FFFF5B7CFFFF5C7CFFFF5476FFFF5546A0FF3B43C0FF5F438DFF5B85
      72FF2CFD44FF21FF3CFF69E65BFFE16E48FF76625BB324242425040404050000
      000000000000000000000000000000000000578097C246A8E8FF308EDEFF348C
      D9FFECC4B0FFFFF9F6FFFFFDFBFFFFFCFAFFFBFBFAFFB3DEB9FF6EC97DFFE2ED
      DFFFFFFAF5FFFBE5DAFFF1AC8BFFFCCAA3FFFECAA3FFF9A17BFFF8906AFFF992
      6CFFF8936DFFE8714DFFD54926FFD74B28FF985E50D562605F7F2929292B0808
      08090000000000000000000000000000000000000000746862ACC9835AFFC57C
      55FFBD704AFF040404FFBABABAFFF9F9F9FF131313FF111111FF141415FF1818
      19FF1D1D1DFF212121FF252425FF747475FF5F5F5FFF2F2F30FF474747FFEDED
      EDFF373737FF344049FF1192CFFF275263FF393939FF383839FF373737FF3434
      35FFBA7A56FFD78D60FF776962B1000000000000000000000000000000006060
      60B0000000FF00008CFF0000FFFF0000FFFF0000FFFF0000FFFF0000C2FF0000
      00FF000D20FF0068FFFF0068FFFF0068FFFF0068FFFF0068FFFF0068FFFF000D
      20FF000000FF0000C2FF0000FFFF0000FFFF0000FFFF0000FFFF000095FF0000
      00FF606060B0000000000000000000000000675E5B6ED76C47FFE8865FFFE98B
      64FFE06542FF6DA687FF00E9CCFF00E9CCFF00E9CCFF26EAD3FF2C4FF1FF2540
      DDFF5064E0FF859DFDFF879FFFFF7B96FFFF6787FFFF4B6EFEFF4472B6FF2CFD
      44FF21FF3CFF21FF3CFF67E75BFFC57444FF458637F041C15DF366766A9A0E0E
      0E0F1919191A151515160000000000000000577F97C247ABE8FF2F8CDDFF3389
      D8FFECC7B1FFFFF9F5FFFFFDFCFFFCFBFAFFE1ECDEFFFEFBFAFFC1DDC1FFC6DB
      C0FFFFF8F3FFFFF6EFFFF6D8CAFFF1AC8BFFFED2AAFFFECAA3FFF89973FFF890
      6AFFF9926CFFF8936DFFE36743FFD54926FFD04E2EFB985E4ED45858586C3535
      35380B0B0B0C00000000000000000000000000000000746862ACCE885EFFC981
      57FFBD714BFF050505FF686868FFFFFFFFFF6C6C6CFF121213FF161617FF6969
      69FF858585FF2C2C2DFF272728FFCCCCCCFFB4B4B4FF333333FF797979FFC0C0
      C0FF3B3B3CFF2B5A7AFF0CCAFFFF19E8F7FF246881FF31424FFF303E4AFF3838
      39FFB37452FFD98F62FF776962B1000000000000000000000000000000006565
      659A000000FF000072FF0000FFFF0000FFFF0000FFFF0000FFFF0000EEFF0000
      02FF000000FF0054CCFF0068FFFF0068FFFF0068FFFF0068FFFF0054CCFF0000
      00FF000002FF0000EEFF0000FFFF0000FFFF0000FFFF0000FFFF00007AFF0000
      00FF6565659A000000000000000000000000675F5B6ED9734DFFEA8F68FFEC94
      6DFFE06642FF6EA586FF00E9CCFF00E9CCFF00E9CCFF26EAD3FF2D4DECFF2548
      EEFF2447EEFF344AD9FF7585E2FF9CAEFAFF89A0FEFF556EC7FF66B45BFF4BB8
      4AFF1FD134FF1FF138FF59E852FF4FAF3CFF1DC437FF2CD04BFF35D657FE598D
      62C844CB64F464A87BD83737373A00000000578097C24AADEAFF2D8ADCFF3086
      D6FFEDC9B3FFFFFAF6FFFFFDFEFFB0DAB4FF35B745FFDFEDDFFFFFFCFBFFFFFC
      FAFFFFF7F2FFFFF6EFFFFFF6EEFFF9E1D6FFF1AC8BFFFCCCA3FFFEC9A3FFF9A0
      7AFFF8906AFFF9926CFFF8926CFFE86E4AFFC85538FFBA7561FF907F78E26C6C
      6BA63E3E3E430C0C0C0D000000000000000000000000746862ACD38C62FFCC84
      5AFFBE724CFF060606FF0C0C0DFFBBBBBBFFFBFBFBFFAEAEAEFFA4A4A4FFF8F8
      F8FFE1E1E1FF2A2A2AFF2A2A2BFF303030FF383839FF363637FFA9A9AAFF9494
      94FF3F3F40FF1C74B0FF10D7FFFF16EBFFFF17EEFEFF18EDFCFF1CBBD4FF3B3B
      3CFFAC6F4DFFDB9265FF776962B10000000000000000000000001F1F1F205757
      57C3000000FF000040FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      5AFF000000FF000D20FF0055CFFF0068FFFF0068FFFF0055CFFF000D20FF0000
      00FF00005AFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF000048FF0000
      00FF565656C31F1F1F200000000000000000685F5B6EDC7A53FFED9870FFEF9E
      76FFE06642FFD96443FFA99172FF6CB89CFF30DEC4FF2AEBD4FF2F4CE7FF2747
      E9FF2648ECFF2548EFFF2447EFFF233FDEFF3D3EBDFF974359FFC4565AFFE4A6
      A1FFDEA9A1FF969E73FF52D249FF48BE47FF1EC539FF20C73BFF1EC537FF24CA
      40FF34D757FF51EF81FF63AD7DDA2929292B578098C24BAFEBFF2C88DCFF2F84
      D6FFEDCBB5FFFFFAF7FFE2F0E4FF54C669FF2CCF4EFFA1D7A8FFFFFDFCFFFFFA
      F6FFFFFCF9FFFFFAF7FFFFF6EFFFFFF6EFFFF6D6C7FFF1AC8BFFFFD1ABFFFEC9
      A2FFF89872FFF8906AFFFA906AFFDA8E72FFB6A79EFF9798ACFF5360BEFF545A
      9CF35F5F5F7B2B2B2B2D020202030000000000000000746862ACD79165FFD087
      5DFFBF734DFF070707FF0A0A0AFF131313FF777777FFC6C6C6FFD8D8D9FFB1B1
      B1FF414141FF282828FF2C2C2DFF313131FF353536FF393939FFD8D8D8FF6769
      6AFF246C96FF08B5FAFF10D9FFFF12DEFFFF13E3FFFF15E7FFFF2588A1FF3F40
      40FFA56949FFDD9467FF776962B1000000000707070864646482121212F60000
      00FF000000FF595907FF0404F1FF0000FFFF0000FFFF0000FFFF0000FFFF0000
      E9FF000021FF000000FF000000FF001026FF001026FF000000FF000000FF0000
      21FF0000E9FF0000FFFF0000FFFF0000FFFF0000FFFF0000FBFF520022FF0000
      00FF000000FF121212F66464648207070708685F5C6EDE835AFFF0A17AFFF2A8
      82FFDF6643FFDA5431FFDB5633FFDC5835FFDD5A36FFD77659FF2E3FD3FF2742
      DEFF2746E6FF2647EAFF2548EDFF2549EFFF5047BFFFBF494EFFC04E52FFDB90
      8DFFE1A19CFFE4A7A2FF5FA94BFF68B953FF2BCF49FF14BD2AFF20C338FF1AC1
      32FF31D552FF44E46DFF68746B8D494B4A50578098C24DB2ECFF2A87DAFF2B82
      D5FFEECDB8FFFFFBF7FFD2E7D3FFBCDDBFFF7AD48EFF49D069FFEFF3EEFFFDDB
      CFFFFAB69DFFFBC7B4FFFDDDD0FFFDE9DFFFFEF4ECFFF9E1D6FFF1AD8CFFFDCB
      A4FFFEC8A2FFFBA077FFD79982FFC4C2BFFF6A73C5FF2546E9FF1142FFFF0737
      FDFF464D8DD25D5D5F7A262626270505050600000000746862ACDC9569FFD38B
      5FFFC0744DFF070708FF0B0B0BFF0F0F0FFF121213FF171717FF1B1B1BFF2020
      20FF252525FF29292AFF2E2E2FFF333333FF373738FF3B3B3CFF8F8F8FFF2878
      8AFF1DC2A7FF0CC3EDFF0CCBFFFF0ED0FFFF0FD5FFFF11DAFFFF27718DFF4242
      43FF9E6344FFDF9768FF776962B100000000646464AC000000FF000000FF3535
      00FFC8C800FFFFFF00FF595993FF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000E7FF000052FF000000FF000000FF000000FF000000FF000053FF0000
      E7FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF3F00BBFFFF0035FFCB00
      2AFF38000BFF000000FF000000FF646464AC685F5C6EE08A61FFF3AC86FFF6B2
      8CFFDF6743FFD9522FFFDA5430FFDB5632FFDC5734FFDB5937FF2E35C2FF2735
      CBFF2636CFFF263AD6FF263FDEFF2544E7FF2747E9FFB5505FFFC4575AFFD075
      75FFDD9592FFDF9C97FFBD8A7BFF848F5AFF3CDE62FF18C02FFF37AF37FF36C1
      45FF23CA3FFF38DA5BFF67796C9E00000000578198C24FB4EDFF2985D9FF2A7D
      D3FFEECFB9FFFFFBF6FFFEFEFFFFFFFFFFFFE2F0E3FF66D683FF98DAA6FFFBF7
      F4FFFDEAE2FFFDDBCEFFFAC4AFFFF9B79EFFFAB79EFFFCCDB9FFF5D5C8FFF1B1
      91FFFFD4ABFFECBB99FFD4CCC8FF8A90CCFF3C5DF2FF355EFEFF234FFFFF1846
      FFFF0F39EBFB49508CD05050505D1818181900000000746862ACE1996CFFD68D
      61FFC0754EFF080808FF0C0C0CFF101010FF131313FF181818FF1C1C1DFF2121
      21FF262626FF2B2B2BFF303030FF343435FF39393AFF3D3D3EFF315B36FF1AA3
      2FFF37DA5AFF0FBAB0FF08BDFCFF0AC3FFFF0BC8FFFF0DCDFFFF1898C2FF4343
      44FF975E40FFE1996AFF776962B100000000080808FB000000FF535300FFFDFD
      00FFFFFF00FFFFFF00FFDBDB17FF0606F0FF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000E6FF0000B6FF0000B6FF0000E6FF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000F9FFC70054FFFF0035FFFF00
      35FFFE0035FF540011FF000000FF060606FC685F5C6EE39269FFF7B690FFF9BD
      96FFE47954FFD74F2CFFD8512EFFD95330FFDA5532FFDA5635FF3032BCFF2833
      C4FF2734C8FF2735CCFF2636CFFF2537D2FF2439D7FF8C4F89FFC86062FFCC6A
      6BFFD88987FFDB908DFFDD9692FFC86D6BFF59DB74FF3BDD60FF0FB821FF62AC
      54FF2ACF49FF2BD04BFF5B9067C904040405578198C251B6EFFF2783D8FF277A
      D2FFEED1BCFFF7F4F1FFEEEEEEFFFCFBFBFFFFFFFFFFF5F8F5FF86C990FFC5DF
      C6FFFFFDFCFFFFFCF8FFFFFEFAFFFFFBF6FFFEEAE0FFFCD6C6FFFFF6F1FFF2C6
      B9FFE59671FFD5C1AFFFB1B4DEFF5D76EDFF5879FFFF486CFFFF335CFFFF1745
      FFFF0435FFFF0335FDFF6363739B2222222300000000746963ACE59D6FFFD990
      64FFC2764EFF090809FF0C0C0CFF101010FF131414FF181819FF1D1D1DFF2222
      22FF272727FF2C2C2CFF303031FF353536FF3A3A3BFF3E3E3FFF386F43FF1BB6
      30FF1DC436FF37D95AFF13B6B9FF05B4FFFF0EABECFF2788B0FF316F8FFF4546
      46FF91593CFFE39B6CFF776962B1000000004F4F4FCD000000FF5B5B00FFFFFF
      00FFFFFF00FFFFFF00FFFFFF00FF929259FF0000FEFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF76008EFFFF0035FFFF0035FFFF00
      35FFFF0035FF5C0013FF000000FF4C4C4CCF655E5A6BE4986FFFFAC19BFFFCC8
      A1FFF9BF98FFDA5B37FFD74E2BFFD8512DFFD9522FFFDB5530FF4A36A2FF5139
      A0FF623F96FF2834C5FF2935C8FF2735CCFF2636D0FF89508BFFCC696AFFCD6E
      6FFFD37B7AFFD68483FFD98B89FFD78684FFAE856BFF56EC82FF3CDD61FF21BC
      33FF34D757FF25CA42FF3FAC53EB16161617588199C253BAF0FF2681D8FF2678
      D1FFF4D5BBFFDAD7D1FFADABABFFBEBDBCFFD4D2D2FFEEECECFFF4F9F4FFE9F2
      E9FFFFFEFEFFFFFCF9FFFFFBF7FFFFF8F4FFFFF8F2FFFFF7F1FFFFF9F5FFFBD0
      BEFF9A8890FFB6B7B4FF8992DFFF7491FBFF6585FFFF5778FFFF2752FFFF1241
      FFFF1240FFFF1342FFFF62626C871313131400000000756963ACE9A172FFDC93
      66FFC67850FF2C1D16FF0A0A0AFF0E0E0EFF121212FF161617FF1B1B1CFF2121
      22FF272727FF2C2C2CFF313131FF363636FF3A3A3BFF3F3F40FF434344FF376B
      3FFF14BD29FF359649FF10C4DDFF0C99E8FF445968FF4E4E4FFF4B4A4BFF4747
      48FF8B5438FFE49C6DFF776962B1000000003F3F3F44000000FE010100FFD0D0
      00FFFFFF00FFFFFF00FFEEEE00FF6C6C00FF000075FF0000FEFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000FFFF0000FEFF000087FF6C0018FFEF0032FFFF0035FFFF00
      35FFD1002CFF010000FF000000FE41414146413F3F43D37B53FFFECCA5FFFECE
      A7FFFFCDA6FFFCC69FFFEF9C74FFE57854FFDB5A36FFD8512EFFD55334FFD755
      36FFC45246FF4738A9FF694192FF8D4A79FF2734CBFF964F76FFCF706EFFD177
      77FFD17777FFD17776FFD47D7CFFD88B88FFD07575FFAF866DFF63E789FF4AE9
      75FF24CA40FF16BF2DFF22C33DFD35353538617C8CAA51B7E9FF3D9DE6FF1E74
      D1FF95A6BBFFB0A69FFFCDCBCBFFDCDCDBFFCAC8C7FFBAB8B7FFBAB8B7FFC7C5
      C5FFDDDBDAFFEAE9E9FFFAF8F6FFFEFBF8FFFFFAF5FFFFF8F0FFFFF9F5FFFFD1
      BEFF7C99B6FF71AACBFF8289D3FE8FA4FCFF7996FFFF5073FFFF2D57FFFF3158
      FFFF315AFEFF4B5BB9DE272727290202020300000000756963ACEDA475FFDF95
      68FFC67850FFAE6A48FF3A261CFF14100EFF0D0D0EFF101010FF131313FF1717
      17FF1A1A1BFF1E1E1FFF232324FF282829FF2D2D2EFF323233FF373738FF3842
      3AFF377044FF434643FF396577FF435563FF4E4E4FFF4D4D4EFF4A4A4BFF4647
      48FF864F35FFE69E6FFF786962B10000000000000000626262B1000000FF3A3A
      00FFE3E300FF979700FF121200FF000000FF000000FF00005BFF0000F2FF0000
      FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      FFFF0000FFFF0000F6FF000068FF000000FF000000FF130003FF9A0020FFE600
      30FF3B000CFF000000FF616161B30000000000000001977163B2DE9469FFFCC9
      A1FFFECBA4FFFEC8A2FFFEC69FFFFEC39DFFFDC19AFFF6AB85FFED8C65FFE36E
      4AFFDC5935FFDC5733FFDD5935FFDC5B38FFAC515FFFD95D40FFD97062FFD582
      81FFD58382FFCC6B6CFFCF7172FFCD6D6EFFC55B5DFFD47D7DFFC5726DFF94A9
      79FE73B085C56BC686D6687D6D8A0D0D0D0E4C4F51563A8BB7EF5BC3FAFF3997
      E3FF1B74D4FF3D76B5FFD5CFCAFFD1D0D0FFD3D2D1FFDBDAD9FFDBDAD9FFD7D6
      D5FFCBC9C8FFBFBEBDFFBDBBB9FFCAC8C5FFE7E4E0FFFCF6F1FFFFFEFBFFFFD2
      BFFF829CB8FF3DA4E3FF4F668BDD7580C7EC8BA4FFFF5577FFFF4E71FFFF5175
      FFFF566CD7ED59595E6C060606070000000000000000766964ACF0A777FFE197
      69FFC67951FFC97B53FFCB8055FFCE8357FFC88056FFBD7953FFAF714FFF9F69
      4AFF956348FF875D45FF775541FF6C4F3FFF5F493CFF534339FF483E37FF3A36
      34FF323232FF333334FF353536FF363636FF353536FF343435FF333334FF3433
      33FF895539FFE9A171FF786962B10000000000000000242424250B0B0BF90000
      00FF000000FF000000FF000000FF303030E5020202FD000000FF00001BFF0000
      9BFF0000F6FF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      F9FF0000A4FF000022FF000000FF020202FD303030E5000000FF000000FF0000
      00FF000000FF0B0B0BF924242425000000000000000004040405655D5A6B9B6F
      5FBABC603DF5D78258FFEEA881FFFCBE98FFFDBB95FFFCB791FFFCB48EFFFCB0
      8BFFFAAA84FFF3936CFFEA7955FFE26642FFDD5A37FFDE5C39FFDD674DFFD98B
      89FFDB908EFFCC6A6BFFCA6667FFC96365FFC55A5DFFD37A7AFFD58381FFA17E
      7DD404040405000000000000000000000000010101024B4E50554A84A5D7429B
      C9F63EA1E0FF3A98DCFFA4AFB7FFEFECEAFFE5E5E4FFC9C9C8FFCDCCCAFFD3D2
      D1FFDBDADAFFE5E4E4FFE7E6E5FFDBDAD9FFC4C2C1FFBBB9B7FFC7C7C6FFFAD3
      C0FF819AB9FF39A1E5FF5C6B74B04F4E515A7A82C3DA809AFBFF7C94F5FC7480
      C3DB4747494F05050506000000000000000000000000796C65A4F3AA7AFFE59B
      6DFFC67951FFC97B53FFCB8055FFCD8257FFD08559FFD2875BFFD48A5DFFD68C
      60FFD98F62FFDB9164FFDD9466FFDF9668FFE1996AFFE39B6CFFE69D6EFFE49C
      6DFF9C5332FF9A5636FF965A3DFF8B553BFF774832FF714A36FF664F56FF5C44
      53FFC3876EFFEAA272FF786962B1000000000000000000000000656565850000
      00FF000000FF171717F36161617A060606074646464C2C2C2CE8000000FF0000
      00FF00000DFF000060FF0000EDFF0000EEFF0000EEFF0000EDFF000066FF0000
      11FF000000FF000000FF2B2B2BE84646464C060606076161617A181818F30000
      00FF000000FF6565658500000000000000000000000000000000000000000000
      00000909090A434140457C6B6688A46954CDC35F3AFCDC8157FFF29F77FFFBA9
      84FFFAA47DFFFA9F78FFF99A74FFF9966FFFF58C66FFEC7653FFE46946FFDD90
      89FFDE9996FFD37C7BFFC65A5DFFC86163FFC96365FFCE6E6FFFD17575FF6460
      60700000000000000000000000000000000000000000000000002829292A4D51
      5358627A87A14782A4D8357CA6FD7A94A1FFBCBFC0FFBBB9B8FFBCB9BAFFC2C1
      C0FFC9C8C7FFCECDCCFFD7D6D5FFDDDDDCFFE4E4E4FFE9EAEAFFB9AFACFFF7BB
      9EFF819DBAFF389FE5FF5B6B76B22C2C2C2E3B3B3C3F747692A1686875823232
      33350202020300000000000000000000000000000000645F5D73E1996BFFF3AA
      79FFCD8257FFC97B53FFCB8055FFCD8257FFD08559FFD2875BFFD48A5DFFD68C
      60FFD98F62FFDB9164FFDD9466FFDF9668FFE1996AFFE39B6CFFE59D6EFFE098
      6AFFA05332FFC4774FFFB06541FFA35835FFBB6D46FFA55937FF5F4DA0FF4347
      CEFF3135B9FFE7A073FF7B6C65AD000000000000000000000000000000004848
      484F5A5A5A6D1919191A0000000000000000000000000F0F0F10656565871F1F
      1FEF000000FF00001CFF0000FFFF0000FFFF0000FFFF0000FFFF000020FF0000
      00FF1E1E1EEF656565870F0F0F100000000000000000000000001919191A5A5A
      5A6D4848484F0000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000014141415534F4D56896F669AAD5E
      43DFCA5E36FEE07650FFF38C65FFF58A64FFF1825CFFED7854FFE9704DFFE288
      74FFE2A29DFFE09D99FFC14F52FFC35559FFC65C5FFFC96365FFB76C6DF01313
      1314000000000000000000000000000000000000000000000000000000000000
      000000000000000000002B2B2C2D555A5D65788992C9BDB9B6FEA3A1A0FFABA9
      A7FFB3B2B1FFBBB8B7FFC0BFBEFFD5D4D4FFE6E6E6FFE8E7E6FF97989EFFAD93
      93FF6EA2CDFF389DE2FF5D6C76AC262626270000000000000000000000000000
      000000000000000000000000000000000000000000000C0C0C0D8D6B59D1E39B
      6DFFF2A878FFE19669FFDC9265FFDA8F63FFD88D61FFD68C60FFD68C60FFD78D
      60FFD88F62FFDB9164FFDD9466FFDF9668FFE1986AFFE39B6CFFE59D6EFFE199
      6AFFA35734FFDD9466FFBF7650FFA75C39FFD58B5FFFBB724CFF6352A7FF545A
      E6FF4148D1FFDE996EFF726A658C000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000003C3C
      3C40000000FF00001DFF0000FFFF0000FFFF0000FFFF0000FFFF000020FF0000
      00FF3C3C3C400000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000023232324645C5969946F62AEB35533EDC9522BFFD85E39FFE1623FFFDF6C
      50FFE6ABA6FFE8B1ABFFC75F62FFBF4A4EFFC25054FFC4575AFF7B6E6E9A0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000004F4F4F54C1C0BFF1CFCECDFFB5B3
      B2FFA4A2A1FFA4A3A1FFADABAAFFB1B0AFFFD9D5D4FFDAD2CDFF5C93BEFF40A0
      E9FF42A1E6FF2386C5FF5E64677C0F0F0F100000000000000000000000000000
      00000000000000000000000000000000000000000000000000000C0C0C0D6660
      5E74857268AD8E7365C1946F5BD597684FE69E6445F5A3623FFEAA6743FFB16D
      48FFB5714BFFB9744EFFBE7852FFC37C55FFC68258FFC8835AFFC8845AFFCA85
      5BFFB06A46FFAA6440FFB46E49FFB06945FFB06843FFB36B47FF8C6588FF6656
      AEFF584AA6FF95624AED21212122000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000003A3A
      3A3E000000FF000003FF0000BCFF0000DFFF0000DFFF0000BBFF000003FF0000
      00FF3A3A3A3E0000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000003030304363534377264607BA06652C8A950
      34E6D4A59EEEECB9B2FFECBCB5FFE3A5A0FFD78886FFB86E6FEC2929292A0000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000040404055454545B9C9B9BC4BBBA
      B9E2D8D7D6FCD7D7D6FFCAC7C5FF8E9599F1527388CA477999E22F8CCAFA3584
      B7F0537A8FC15B61647407070708000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000C0C0C0D1E1E1E1F2D2C
      2C2E3E3D3D414F4D4C555D59576767615E767369658B7A6D6799826F66AC876C
      60C0886554D3875B47E2844C33F5814427FE854528FF854628FF834427FF7F48
      2EF6816E65AE2626262700000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000002222
      2223000000FE000000FF000000FF000000FF000000FF000000FF000000FF0202
      02FD222222230000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000022222223716C6B74B2A19EB8E5C4BEF18A82819612121213000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000181818193333
      33356363636D8A8989A8A09E9CCF6B6C6C7F21212122323333354D5153584142
      4247181818190101010200000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000B0B0B0C1919191A2A29292B2929282A0707
      0708000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00005F5F5F76161616F4000000FF000000FF000000FF000000FF161616F45F5F
      5F76000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000080000000400000000100010000000000000400000000000000000000
      000000000000000000000000FFFFFF00F83FFFFF8000003FFFFF3FFF00000000
      F00FFFFF0000003FFFFE1FFF00000000E003FFFF0000003FFFFC0FFF00000000
      E001FFFF0000003FFFF80FFF00000000E000FFDF0000003FF838041F00000000
      C0F07F1F0000003FF800001F00000000C0FC783F0000003FF800001F00000000
      C1FF003F0000003FF800001F00000000E03FC00F0000003FF800001F00000000
      E03000030000001FF800001F00000000006400010000001FF800001F00000000
      004000000000001FF800001F00000000808000000000001FE000000700000000
      E08202400000000FC000000300000000F08202600000000F8000000100000000
      F88203E00000000F8000000100000000FC8003C0000000078000000100000000
      FC800380000000078000000100000000FC80030300000007E000000700000000
      F8C0040700000003F000000F00000000F9E0001F00000003F800001F00000000
      F9F0007F00000003F800001F00000000F0FF07FF00000001F800001F00000000
      F0E00FFF00000001F800001F00000000F0E00FFF00000001F800001F00000000
      F0781FFF00000001F800001F00000000F0001FFF00000001F810001F00000000
      F8001FFF00000007FFF00FFF00000000F8001FFF0000003FFFF80FFF00000000
      F8009FFF8000003FFFFC1FFF00000000FC039FFF8000003FFFFC3FFF00000000
      FE0FFFFFFFFFFFFFFFFFFFFF00000000FFFFFFFF803FFFFFFFFFFFFFFFF00FFF
      FF81FFFF0007FFFFC007FFFFFFE007FFFF00FF8300007FFF80001FFFFFE007FF
      FF00FE0100000FFF8000003FFFE007FFE101C000000001FF80000003E38001C7
      C01F8000000000FF80000001C000000300010000000000FF8000000180000001
      00000007000000FF80000001800000010000000F000000FF8000000100000000
      0000000F000000FF80000001000000000000001F000000FF8000000100000000
      0000001F000000FF80000001000000000000003F000000FF8000000100000000
      0000003F0000007F80000001C00000030000003F0000003F80000001E0000007
      0000003F0000001F80000001E00000070000001F0000000F80000001E0000007
      000000030000000780000001E0000007000000010000000380000001C0000003
      0000000000000001800000010000000000000000000000008000000100000000
      0000000100000000800000010000000000000000000000008000000100000000
      0000000000000000800000010000000000000000000000008000000180000001
      00000000000000018000000180000001800000070000000380000001C0000003
      F000000FC000000780000001E38001C7FF00000FFC0000FF80000001FFE007FF
      FFF0001FFF0000FFC0000001FFE007FFFFFE001FFF0001FFFF800003FFE007FF
      FFFFF03FFFC003FFFFFFFE0FFFF00FFF00000000000000000000000000000000
      000000000000}
  end
  object SW_ImgListSmallMain: TImageList
    ColorDepth = cd32Bit
    DrawingStyle = dsTransparent
    Left = 1021
    Top = 104
    Bitmap = {
      494C010107001800040010001000FFFFFFFF2110FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000002000000001002000000000000020
      0000000000000000000000000000000000000000000000000000000000000000
      0000101010113F3F3F45656666826E6F7094606061762D2D2D2F040404050909
      090A000000000000000000000000000000000000000000000000000000000000
      00002E2E2E306C6D83985B60B9DA373FCAFA2B33C5FA4E54B6DB686A849A3131
      3133000000000000000000000000000000000202020303030304030303040303
      030432323334777791987070D3D95858F3F95858F3F96F6FCFD976768D983232
      3334030303040303030403030304020202030000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000001C1C
      1C1D6A6B6C969BA0A8F5C5CBD1FFD8DDE1FFD1D6DBFFA2A5ABF47E6C5CCD9176
      5EAB88756299967F63A727272628000000000000000000000000070707086C6D
      8699343FCEFD313CD0FF303BCFFF222DC8FF1D28C6FF1D28C7FF1D28C8FF1F2A
      C8FE686B889D0909090A000000000000000003030304050505060E0E0E0F7474
      909D5454F5FD5252F7FF5252F7FF5252F7FF5050F2FF4949DFFF4949DEFF4C4C
      DCFD73738B9C0E0E0E0F05050506030303040000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000C0C0C0D2C2C2C2E6262
      637A939CA6FBADB6BEFFC5CBD1FFD8DDE1FFD1D6DBFFBEC4CBFF9EA4AAFFA254
      0CFFCE8129FFB68E61D3242424250E0E0E0F0000000007070708696DA4C0323F
      D2FF323FD2FF313ED1FF222DC5FF1D28C3FF1D28C3FF1D29C4FF1D29C7FF1E2A
      CAFF1E2BCBFF5D64A5C40909090A00000000030303040E0E0E0F7575B2C45252
      F7FF5252F7FF5252F7FF5252F7FF5050F2FF4949E0FF4949DEFF4949DEFF4949
      DEFF4949DEFF7272A9C30E0E0E0F030303040000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000004F4F505496A0AAF6C6CCD2FFBDC4
      CBFF9EA8B1FFADB6BEFFC5CBD1FFD8DDE1FFD1D6DBFFBEC4CBFFA3ACB5FFA168
      39FFD1904FFF978572A5645E5769C98B2FEE000000006C6E85973342D4FF3342
      D4FF3342D4FF6F6EA5FFBDA765FFBDA866FFBDA967FFBEA968FF666394FF1F2C
      CBFF1F2CCCFF1F2DCDFF696B899D00000000030303047474909D5252F7FF5252
      F7FF5252F7FF5252F7FF5050F2FF4949E0FF4949DEFF4949DEFF4949DEFF4949
      DEFF4949DEFF4949DEFF73738B9C030303040000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008C9298C495999DBB3C3C3C3D8C8F
      92AF96A1ABFFADB6BEFFC5CBD1FFD8DDE1FFD1D6DBFFBEC4CBFFA3ACB5FF9C82
      6FE08073688D635D586800000000000000002C2C2C2E3748D5FD3444D7FF3444
      D7FF3444D7FF5A60B6FFB29E6CFFD5B752FFD5B954FFB09D6EFF4C50ADFF1F2E
      CDFF1F2ECDFF1F2ECEFF2130CEFE31313133323233345454F5FD5252F7FF5252
      F7FF5252F7FF5050F2FF4949E0FF4949DEFF4949DEFF4949DEFF4949DEFF4949
      DEFF4949DEFF4949DEFF4C4CDCFD323232340000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009C9FA2BAABB2B9F587898A9A979D
      A3D096A1ABFFADB6BEFFC5CBD1FFD8DDE1FFD1D6DBFFBEC4CBFFA3ACB5FF9589
      82DE4C49484F0000000000000000000000006B6D82943547D9FF3547D9FF3547
      D9FF3547D9FF3547D9FF595FB5FFD3B34AFFD1AC3DFF4A4B9FFF202FCDFF202F
      CEFF2030CFFF2030D0FF2030D1FF696C869A777792985252F7FF5252F7FF5252
      F7FF5A5AF3FF9C9CE6FFD1D1EAFFE5E7E0FFE5E6E0FFCDCDE5FF9291DAFF5151
      DDFF4949DEFF4949DEFF4949DEFF76768D980000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000018181819969899A1CED3D7F5B5BD
      C4FFA0AAB3FFB4BABFFFA4AAB0FF9D9C9FFFAAB1A6FFC4CCCBFFABB4BCFF8C92
      98CD00000000000000000000000000000000626DBCD5364ADBFF364ADBFF364A
      DBFF364ADBFF3549DBFF3C49C8FFD3BC6CFFD2B046FF353BABFF2030CEFF2031
      CFFF2031D0FF2032D1FF2032D2FF515BBEDB6F6FD3D95252F7FF5252F7FF7373
      F5FFDEDEEDFFEDEDECFFC4C599FF74631EFF74631EFFC4C599FFECECEBFFCFCF
      DCFF6666DAFF4949DEFF4A4AE2FF7070D1D90000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000D0D0D0E9AA5
      ABFD86A383FF324638FF606A75FF4F5454FF8A6A4CFF5E8A4BFF6F8D69FF9AA4
      ABF3000000010000000000000000000000004458D7F5374DDDFF374DDDFF374D
      DDFF364CDDFF2638D0FF4453CEFFBFBFB0FFD3B662FF4649A4FF2132D0FF2132
      D1FF2133D1FF2133D2FF2134D3FF2A3BD0FA5858F3F95252F7FF6565F3FFE4E4
      EDFFEEEEEDFFE8EAE0FF74631EFF593A00FF593A00FF74631EFFE8EAE0FFEEEE
      EDFFD8D7DFFF5E5EDFFF5151F5FF5858F3F90000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000002727272891A9
      93FF4D823CFF5F6B72FF818C97FF5D7064FFA98769FF543F19FF507A3FFFA1A8
      A9FF1C1C1C1D000000000000000000000000465BD8F43850E0FF3850E0FF374F
      DEFF2B3DC9FF2031CBFF3344CEFFDAE7EAFFCDCCBDFF3742B8FF2133D1FF2537
      CBFF2033CEFF2135D3FF2235D4FF2C3ED1FA5858F3F95252F7FF6464F1FFD9D8
      E1FFEEEEEDFFE8EAE0FF74631EFF593A00FF7A6C24FF979742FFE8EAE0FFEEEE
      EDFFE4E4EDFF6666F3FF5252F7FF5858F3F90000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000004040404384A8
      79FF3A5E35FF7C8893FF8B959EFF677B6BFF929369FF614139FF909596FFA9A9
      A8FF404040430000000000000000000000006373BFD43853E2FF3853E2FF657B
      E3FFCDDAE4FF2637C3FF4354CEFFD4E0E3FFE2EDF0FF4B5BCBFF273AD2FFCCD9
      E6FF5768CFFF2136D4FF2338D6FF5D6DC4DA6F6FD3D95252F7FF5252F7FF6D6D
      EFFFD9D9E8FFEEEEEDFFC4C599FF74631EFF8A8233FFD0D7A6FFEEEEEDFFDEDE
      EEFF7373F5FF5252F7FF5252F7FF7070D3D90000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000222222238E85
      7AFF647072FF87929BFF959EA7FF768278FF8F9D84FFA2A2A0FF616A73FFAFAF
      AFFFA09F9ED91313131400000000000000006B6F82923956E4FF3956E4FF6983
      E6FFDBE8ECFF8694D2FF7284D3FFDBE8ECFFE0EBEFFF7586D1FF8493DAFFDBE8
      ECFF5B6DD1FF2439D7FF3550E1FF6D728798777791985252F7FF5252F7FF5252
      F7FF5B5BF6FFA0A0F2FFD3D3EEFFE5E7E0FFE5E7E0FFD3D3EEFFA0A0F2FF5B5B
      F7FF5252F7FF5252F7FF5252F7FF777791980000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000525252579C97
      93DC959FA6F7919BA5FF9EA8B0FF8D8B8CFFA5A2A0FFAAAAA9FF838689F58F90
      91AB9B9A99FF7D8084B1000000000000000029292A2B3F5BE3FC3A59E6FF6B86
      E9FFDFECF0FFDFECF0FFDFECF0FFDFECF0FFDFECF0FFDFECF0FFDFECF0FFDFEC
      F0FF5E71D5FF3552E3FF3D5AE4FD2E2E2E30323233345454F5FD5252F7FF5252
      F7FF5252F7FF5252F7FF5252F7FF5252F7FF5252F8FF5252F7FF5252F7FF5252
      F7FF5252F7FF5252F7FF5454F5FD323233340000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000008B8887A14C4C
      4C50212121227D7F808BA4A8ABC7A19F9FEBA3A2A2D6A8A7A6FE7F7E7E9F0404
      040580868FC65F6C79FF827876AD00000000000000006C7185933B5CE9FF4B69
      EAFF6F8BECFF6F8BECFF6F8BECFF6F8BECFF6F8BECFF6F8BECFF6F8BECFF6F8B
      ECFF4B68E7FF3B5CE9FF6D738B9900000000030303047474909D5252F7FF5252
      F7FF5252F7FF5252F7FF5252F7FF5252F7FF5252F7FF5252F7FF5252F7FF5252
      F7FF5252F7FF5252F7FF7474909D030303040000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000002020202170899ED70202
      02030000000000000000000000006F727480404040437B8C9DD66E839BCF0000
      0000403E3D42D4942CFEB5824BE10404040500000000060606076E7AAABB3C5E
      EBFF3C5EEBFF3C5EEBFF3C5EEBFF3C5EEBFF3C5EEBFF3C5EEBFF3C5EEBFF3C5E
      EBFF3C5EEBFF6C7AAEC00707070800000000030303040E0E0E0F7575B2C45252
      F7FF5252F7FF5252F7FF5252F7FF5252F7FF5252F7FF5252F7FF5252F7FF5252
      F7FF5252F7FF7575B3C40E0E0E0F030303040000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000656B7380677F97B90000
      00000000000000000000000000005F80A0CB47494B4E73808EA16193C4FD1515
      1516000000005B57525E21212122000000000000000000000000060606076D72
      86934063EAFC3D61EDFF3D61EDFF3D61EDFF3D61EDFF3D61EDFF3D61EDFF4062
      EBFD6D748A9707070708000000000000000003030304050505060E0E0E0F7474
      909D5454F5FD5252F7FF5252F7FF5252F7FF5252F7FF5252F7FF5252F7FF5454
      F5FD7474909D0E0E0E0F05050506030303040000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000003C3D3E40131313140000
      00000000000000000000000000006569717F0B0B0B0C3838393B5355575D0404
      0405000000000000000000000000000000000000000000000000000000000000
      000029292A2B6C718492667DC7D44C6CE5F44A6CE6F5667CC9D56D7286942C2C
      2C2E000000000000000000000000000000000202020303030304030303040303
      030432323334777791987070D3D95858F3F95858F3F97070D4DA777791983232
      3334030303040303030403030304020202030000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000010D0D
      0D0E303030324545454C404040462D2D2D2F1A1A1A1B0C0C0C0D030303040000
      00010000000000000000000000000000000000000000020202030C0C0C0D1616
      16171B1B1B1C1818181915151516101010110909090A03030304000000010000
      0000000000000000000000000000000000000000000004040405141414153030
      30324545454D4545454D2A2A2A2C0B0B0B0C0000000100000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000002020203080808090F0F0F100808
      0809000000000000000000000000000000000000000000000000030303045459
      5C625792ACC95F7D8DB963686B925A5A5A704D4D4D583A3A3A3E262626271515
      15160909090A010101020000000000000000000000000C0C0C0D2E2E2E304A4A
      4A535151515E4E4E4E5949494952424242483737373B2A2A2A2C1F1F1F201616
      16170F0F0F10070707080101010200000000050505061D1D1D1E55555965545A
      93C440489CDB62636B965151515F272727290606060700000001030303040E0E
      0E0F181818191111111204040405000000000000000000000000000000000000
      00000101010206060607101010111F1F1F2043434349606C698658877BB62222
      22230000000100000000000000000000000000000000000000001414141543A2
      CBDF1BC9FDFF22CDFEFF2DB7E6F84E90ABD9627680B15F626282565656694848
      4850343434371F1F1F200F0F0F10050505060000000054545B625E5DA7CD5353
      AFE15251A0DA64638BCE6C6C81BF626272A6626266895B5B5C73535353624A4A
      4A5340404046313131341B1B1B1C0606060713131314656880961539DEFB063C
      FFFF063EFFFF2E42B4E96262648D4B4B4B55202020210F0F0F10222222233E3E
      3E434C4C4C573E3E3E4318181819020202030000000000000000020202031616
      16173939393D5D65637A59857BB426A783E800AA65FF00994BFF55897CBB1313
      13140000000000000000000000000000000000000000000000005054565A0FBC
      FAFE2EC6F7FF3BDBFFFF39DBFFFF3ADBFFFF3AD3FCFF43B0D6F258869ACE646F
      74A15C5C5C77525252613E3E3E431E1E1E1F0000000066649BB75150F8FF4F51
      F6FF4F4FF2FF979AD7FF8C95E0FFAFAFCAFF9A9AB9FA717099E8616187D16465
      7FBB62626D9D5D5D5F7A4343434914141415686B8799558FFAFF316BFFFF0B3F
      FFFF1146FFFF0F46FFFF454D95D85E5E5E7E4A4A4A544545454C63657897273E
      BEEB515586C65C5C5C773E3E3E431515151600000000000000001F1F1F203BA6
      8FD902AD6DFD009446FE00781CFF006600FE006400FF009040FE607972A52F2F
      2F310E0E0E0F0000000100000000000000000000000001010102668FA3B013C9
      FFFF33C7F6FF52EAFFFF51E6FFFF51E4FFFF51E5FFFF52E7FFFF52E6FFFF50D6
      F4FD53A7C4E8607C8ABF606365833E3E3E44000000016766A5C35D5EF8FF5153
      F2FF5859EEFF898AD9FF676DF1FFCBCBD9FFDADADAFFD1D1CAFFADB3CFFF6168
      E7FF2620DEFD45439DDD5151515E1B1B1B1C61626F7781BCFDFF80BCFFFF285E
      FEFF174CFFFF1B51FFFF184AFAFF565981C262626F9F3546B1E60736F4FF0037
      FFFF0330EEFD5B5E78B55858586C303030330000000000000000020202035D8C
      85AD00A832FF007C00FF006900FF006400FF006400FF006500FF00852FFF2F8C
      69E25D626179101010110000000000000000000000000B0B0B0C48AED4E41ECD
      FFFF3ACBF7FF77DAE1FF61DCECFF60EFFFFF63F3FFFF68F0FFFF67EEFFFF68F0
      FFFF6AF2FFFF65EBFDFF5F8699CA4C4C4C56060606076665B6D6676AF7FF565A
      F3FF6465E8FF7574DCFF4443E9FFD5D5E4FFDDDCE4FFD4D3D4FF9B9DD7FF4748
      E9FF2922F1FF413EAFE55050505D1A1A1A1B00000000737A9AAD95D6FFFF6EAA
      FEFF285FFEFF245AFEFF2359FFFF2049E7FD1A42E4FD134AFFFF0D43FFFF073B
      FFFF0036FFFF1234DAF76363789E303030320000000000000000000000002121
      212217C29AF2009304FE008C00FF007C00FE006C00FF006500FE006300FF0058
      00FE005F22FE5F65637F0000000000000000000000003839393B37C8F4FB2BD2
      FFFF43D0F8FFDCC7AEFFDBBBA3FFA2B6AAFF89C9C7FF7AEFF5FF7BFAFFFF79F6
      FFFF79F6FFFF85FFFFFF659FB1DA4C4C4C560C0C0C0D6868C6E76E73F7FF5B60
      F3FF5F5FE8FF8984D5FF7A75D4FFD8D6ECFFDEDCE7FFE0DED8FF8482DAFF2E2B
      E8FF2C25EFFF4744A7DF4E4E4E5A1919191A00000000161616177793C6DD8BCA
      FFFF518CFDFF2E64FEFF2E64FEFF295FFFFF235AFFFF1D52FEFF154AFFFF0D43
      FFFF053CFFFF1D39CFF262627082121212130000000000000000000000000000
      00015D69677A00B358FF008800FF008200FF007A00FF007300FF006800FF0056
      00FF004400FF144D24F4070707080000000000000000606A6F7442DAFFFF3DDC
      FFFF53D6FAFFDFDFCEFFFFCEB3FFFFC8A8FFEEB699FF82C7D0FF81F2FCFF8EF8
      FFFF8FF9FFFF9FFAFAFD6E99A8D34B4B4B551919191A6D6CD3F5747AF8FF686F
      F3FF8197F6FF859EF4FF7C91EDFF6E7AE4FF7176E2FF7B7CDDFF4B49DBFF2A24
      E7FF2F28F2FF4D4AA2D94C4C4C5717171718000000000101010238383A3C5D80
      D4EC3870FFFF3970FEFF3970FEFF3369FEFF2C62FEFF255AFEFF1D52FFFF1446
      FBFF3F52B8DD4444464B0A0A0A0B010101020000000000000000000000000000
      00000909090A3FA792D5008E16FF008613FE008B22FF007000FE006800FF0054
      00FE004200FF003400FE13131314000000000404040567757B834FDEF4FF3BCA
      CAFF6AD3E4FFEECDB4FFEDC1AFFFFFDCCCFFF2CEBBFF8FC4CEFF84E4FBFF80DB
      F2FF89E3F6FFA6E5ECF97299A8D24A4A4A542E2E2F307B7DDEFA757BF7FF8DA0
      F7FFCFFFFFFFC8FFFFFFBCFBFFFFB1F3FFFFA5EBFFFF93D8FFFF87C9FCFF78B5
      F9FF434EF5FF504D9AD44A4A4A54161616170101010210101011303030324D5B
      ADD73D77FFFF4883FEFF437BFEFF3D73FEFF356CFEFF2C63FFFF2253F6FF5359
      8BC74D4D4D581A1A1A1B01010102000000000000000000000000000000000000
      0000000000004142424700BA78FE0EA561F75F6A6781489378CD008A3CFE0054
      05FF003F00FF003100FF13131314000000000F0F0F10698F97BB3AC479FF3BD6
      59FF52D18BFFB3D2D1FFF0CBB7FFFAE9E0FFF5E2D6FFADDADEFF8CDDF6FF91DF
      F4FF90DCF3FFA4D9E4F8789BAAD2484848503E3E40438C8FE9FD7984F7FFA0B5
      FAFFD6FBF8FFC6E9EBFFC1E9EAFFBDEBECFFB9EFF1FFB4F4F4FFB0FBF9FFADFF
      FDFF6184FBFF514D92CF48484851141414150A0A0A0B49494C525665A8D4528C
      FDFF5995FFFF538EFEFF4E88FEFF457DFEFF3D74FEFF346CFFFF2759F5FF5A5D
      7CBC5B5B5B743737373B0E0E0E0F000000010000000000000000000000000000
      000000000000020202035F857DA75E827AAA0F0F0F10040404053D3E3E424F7E
      6FC3005928FE003000FE13131314000000006171628624AA3EFA2BC546FF46EC
      6DFF41D470FF54C4D2FF7BE2FFFF96E0F2FFB2E1E8FFB8F1FCFFCCF9FEFFCEFA
      FEFFB7E7F6FECDE3E7F57F9AA8C73737373B5050555A9CA2F2FF808AF7FFAFC3
      FAFFE1FDFCFFD4F6F8FFD0F8FBFFCAF7FBFFC3F2F5FFBDEEF2FFB7EAECFFB1F2
      F6FF5D72F8FF55538CC94545454D1212121349494D514063DAF35E9DFFFF65A1
      FEFF639FFEFF5F9BFEFF5996FFFF4C87FEFF427AFEFF3970FEFF2F66FFFF2351
      EFFE606070AC565656682D2D2D2F0B0B0B0C0000000000000000000000000000
      000000000000000000001B1B1B1C2C2C2C2E010101020000000000000000595B
      596F002A11FE00441FFE13131314000000005B9B65C71ECF37FF22C93DFF33D7
      54FF3DDC61FF3ECF6CFF3DB88EFD5FBDD9ED57D1F3FA6CE4F9FF78DEF7FF8ADE
      F6FFA0D3E6F7C3D5DEEB6F7C8391171717185E5E666DA3ABF4FF8996F7FFBED0
      FCFFE4FAF6FFD2E9EAFFCFEBECFFCBEBEDFFC7EAECFFC2EAEDFFBEEDEEFFB8F1
      F9FF5967F4FF585787C44343434910101011696B829171B1FFFF7AB8FEFF6FAB
      FDFF72B1FFFF6BA9FDFF588EF4FF6EACFDFF609BFDFF3C73FEFF3268FEFF265F
      FFFF2E49C3F0626268964F4F4F5B252525260000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000595B
      596E001800FF063A15FB1313131400000000677D6B9138B54CF117BD2DFF23CA
      3FFF34D957FF46EE6EFF3CB44AF34D4E4E586571797F74F2FDFF76FAFFFF72F9
      FFFF6B8E9EB447494A4F1F1F1F20030303046B6B7681ABB5F6FF95A5FAFFCDDC
      FCFFECFAF9FFE0F4F6FFDAF2F3FFD6F1F3FFD1F1F3FFCDF0F3FFC9F3F3FFC1F2
      FCFF555DF2FF5F5D86BC3E3E3E430D0D0D0E242424257794CBE191D2FFFF8AC9
      FFFF76B1F8FF647ABCE0636370816A91D8F174B4FFFF4A84FEFF3269FEFF285E
      FFFF1D54FFFF404EA6DE606066812F2F2F310000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000595B
      596E001800FF002C00FE0E0E0E0F0000000000000000292A292B27A333F115C3
      2DFF23BC3CFD40CD60FC5E9264C11F1F1F201515151660696D70738F9BA37493
      9EA82E2E2F3007070708000000010000000072708495ADB8F6FF7C8BEBFFD8E3
      FBFFE9F1EFFFDEEBEBFFDBEBECFFD8EBECFFD4EBECFFCFEAECFFCEEEEDFFC6EF
      FBFF4B4EE2FF65657EA63030303208080809000000003B3B3D3F6C89CBEB7699
      D3EA68697B8D25252526050505065D5E69705D97FBFF518DFFFF366DFEFF285F
      FFFF1D56FFFF1E44DEF9646579941A1A1A1B0000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000595B
      596E001800FF103710F6040404050000000000000000000000003EA54CE721CE
      3DFF369F41E7585C586B1F1F1F20020202030000000100000000000000000000
      0000000000000000000000000000000000007A7B94A8B2BEF8FF7683E9FFF0F8
      FFFFFFFFFFFFFFFFFFFFFCFFFFFFFDFFFFFFF9FFFFFFF5FFFFFFF2FFFFFFCFED
      FFFF4244D6FF5B5B616F151515160101010200000000000000001C1C1C1D1A1A
      1A1B020202030000000100000000000000006A708C9C3E77FFFF2D66FFFF245B
      FEFF244AE6FA6365788B1C1C1C1D040404050000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000595B
      596E001800FF6168618E00000000000000000000000000000000414341476B86
      7098627064820D0D0D0E04040405000000000000000000000000000000000000
      00000000000000000000000000000000000074748DA0A0A7D9F19BA2D7F2A9AA
      CBE5A4A4BFD8A4A5C1D9A2A3BFD88C8CA9C48A8AA5BE8A8AA7C08687A2BB7979
      90A45B5B646D1111111203030304000000000000000000000000000000000000
      0000000000000000000000000000000000000D0D0D0E5862ADCB2749DEF56468
      8FA63838393B0808080901010102000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000004C4C
      4C565B5D5B74010101020000000000000000424D3E000000000000003E000000
      2800000040000000200000000100010000000000000100000000000000000000
      000000000000000000000000FFFFFF00F00FF00F00000000E001C00300000000
      8000800100000000000080010000000000030000000000000007000000000000
      000F000000000000C007000000000000C007000000000000C007000000000000
      C003000000000000C003000000000000C0018001000000008E10800100000000
      9E09C003000000009E0FF00F00000000C00F801F807FFF0FC00380010001F007
      C00080000000C00FC00080000000C003800000000000C003800000008000E003
      800000008000E001800000008000F001000000000001F801000000000000F801
      000000000000FC61000000000000FFE1000000000000FFE1800100008000FFE1
      C07F0000C300FFE3C1FF0001FF01FFE300000000000000000000000000000000
      000000000000}
  end
  object SW_BalloonHint: TBalloonHint
    Images = SW_ImgListSmallMain
    Delay = 1200
    HideAfter = 750
    Left = 1021
    Top = 56
  end
  object SW_ImgListMainSmall: TImageList
    ColorDepth = cd32Bit
    DrawingStyle = dsTransparent
    Left = 1021
    Top = 200
    Bitmap = {
      494C01010A003001040010001000FFFFFFFF2110FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000003000000001002000000000000030
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000002929282A6D63
      5B70000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000004D4A474F6C63
      5A6F0F0F0F100000000000000000000000000000000041403E43E58222EBD282
      36DE000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000B3935D00CA85090000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000072685F78FF7D
      00FFD78334DE55504D5704040405000000004C49464EED7F17F2FF7D00FFB282
      56BE000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000BE7B0A00CA850900C98C1E00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000025252526FA7C
      02FDFF7D00FFFD7D00FEB98452C1937A6299F47D0CF8FD7D00FEFF7D00FF8372
      628B00000000000000000000000000000000000000000000000000000000CFBC
      1E00DBC83000D2C13D00B88C3100BE7B0A00C7820A00B4661D00A24D3900A043
      3400A04334000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000AE81
      58BAFF7D00FFFF7D00FFFF7D00FFFF7D00FFFF7D00FFFF7D00FFFF7D00FF5551
      4E5900000000000000000000000000000000000000000000000000000000C4B0
      0E00CFBC1E00DBC72F00C7820A00BE7B0A00A7522B00A0433400A0433400A24D
      3900AD4D3D000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000504D
      4A53FF7D00FFFD7D00FEFF7D00FFFD7D00FEFF7D00FFFD7D00FEFF7D00FF413F
      3E4300000000000000000000000000000000000000000000000000000000C1B0
      2500C4B00E00CFBC1E00C07E0E00AD612000A0443600A04436009E3D3C00A342
      3F00A7564B000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000001515
      1516FB7B00FEFF7D00FFFF7D00FFFF7D00FFFF7D00FFFF7D00FFFF7D00FFC184
      4BCA2626262700000000000000000000000000000000000000007CBCCB0080C5
      9000C4B00E00C4B00E00C59A3500E1CEBF00DCC6C400AC4F6500A02E4C00A02E
      4C00A2324D00A2727E0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000010101028C76
      6393FF7D00FFFD7D00FEFF7D00FFFD7D00FEFF7D00FFFD7D00FEFF7D00FFFD7D
      00FEEF7E14F47B6D618008080809000000000000000053CEEB0042DAFD0042DA
      FD00A3BC5000C4B00E00E9E4BB00FAFAFA00FAFAFA00DFC2D1009E2A6100A02E
      4C00A02E4C00A02E4C009F3F5600000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000020202038B766392FD7D
      00FEFF7D00FFFF7D00FFFF7D00FFFF7D00FFFF7D00FFFF7D00FFFF7D00FFFF7D
      00FFFF7D00FFFF7D00FFC38448CD151515160000000054CBFA003CC4FB003CC4
      FB003FC3F4007CBC8F00DAE9DA00FAFAFA00FAFAFA00DFC2DB00A5288000A32A
      7300A9335600A9335600B44B6A00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000010101028F786397FE7C00FFFD7D
      00FEFF7D00FFFD7D00FEFF7D00FFFD7D00FEFF7D00FFFD7D00FEFF7D00FFFD7D
      00FEFC7C00FEE87C17F2B88251C42525252600000000000000008EDBFA0043C4
      F8003CC4FB003CC4FB005ACCFA00BEDAF700C8CAF0008141CE0099278600A528
      8000A6356C00CD899D0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000044424046FD7D00FEFF7D00FFFD7D
      00FEF2790AF9F37A0AF9FF7D00FFFF7D00FFFF7D00FFFE7C00FF8472628B3535
      3437151515160202020300000000000000000000000000000000000000002A8D
      EB002097F7002097F7001880F1001175EF004242D2006A1EC80090269800A528
      8000A53B85000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000909090A3B3A393D363635381C1C
      1C1D0707070810101011CB843FD6FD7D00FEFF7D00FFDE8026E9030303040000
      0000000000000000000000000000000000000000000000000000000000001486
      F500137EF3001276F0001276F0002659EC006921C7006A1EC800992A9D00AA2C
      8A00A52880000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000005A55515EFE7D00FFFF7D00FFA9805CB3000000000000
      000000000000000000000000000000000000000000000000000000000000137E
      F300137EF3002E85F1004347ED006113F3006C20C9006921C700AD449C00AE30
      9400AA2C8A000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000008080809DD8128E7FF7D00FF786B607E000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000A175F6006113F3006C20C9009473BC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000786B607EFE7C00FF3E3D3C40000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000007631F400793CC40000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000C0C0C0D8271618704040405000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000434343458781
      7BA4767471832B2B2B2C00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000004848FFFF4848FFFF4848FFFF4848
      FFFF4848FFFF4848FFFF4848FFFF9E9EE4FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0D0D0D0E5152535F5858596B5858
      596B5858596B5858596B5858596B5858596B5858596B5858596B5858596B5656
      5769202020210000000000000000000000000000000023232324684421F75B30
      07FE5B3107FE6D4825F77B78768A070707080000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000001C1C
      1C1D575757645757576457575764575757645757576457575764575757645757
      5764242424250000000000000000000000004848FFFF4848FDFE4848FFFF4848
      FDFE4848FFFF4848FDFE4848FFFF7E7EE3FEFEFEFEFFFDFDFDFEFFFFFFFFFDFD
      FDFEFFFFFFFFFDFDFDFEFFFFFFFFFDFDFDFE3434353700347DFF002F75FF002A
      70FF001D5EFF001B5BFF001D5DFF001856FF001855FF001957FF001855FF0007
      3EFF4A4A4B54000000000000000000000000000000005B5A59625A3006FF8876
      64CF373636382F2F2F306F6C6978807C798E0101010200000000000000000000
      0000202020210F0F0F1000000000000000000000000000000000000000007A7A
      7AA1EFEFEFFFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3
      F3FF8A8A8AB80000000000000000000000004848FFFF4848FFFF4848FFFF4848
      FFFF4848FFFF4848FFFF4848FFFF6060E6FFFCFCFCFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF34343537054194FF013986FF0039
      88FF00327AFF002E74FF00266AFF002467FF002366FF002162FF001D5CFF0011
      4DFF4C4C4D57000000000000000000000000000000006361606E5C3007FF4F4F
      4E520000000000000000000000000D0D0D0E272727283B3B3B3D61605F658F86
      7EAC8A847FA10000000000000000000000000000000000000000000000007F7F
      7FA7979797FFE3E3E3FEAEAEAEFFADADADFEAEAEAEFFADADADFEAEAEAEFFBFBF
      BFFE909090BE0000000000000000000000004848FFFF4848FDFE4848FFFF4848
      FDFE4848FFFF4848FDFE4848FFFF4E4EF1FEF1F1F1FFFDFDFDFEFFFFFFFFFDFD
      FDFEFFFFFFFFFDFDFDFEFFFFFFFFFDFDFDFE343435370C499FFF094092FF0844
      98FF044093FF003886FF003078FF002E74FF002A70FF00286DFF002568FF0021
      62FF5D5D5D71000000000000000000000000000000005655545C64360BFF6E6D
      6B7650505052000000000B0B0B0C56565D634A494C4E4949494C8C6340EC7B46
      17FF845934F58C857FA92929292A000000000000000000000000000000007F7F
      7FA7DCDCDCFFE6E6E6FFAEAEAEFFAEAEAEFFAEAEAEFFAEAEAEFFAEAEAEFFE1E1
      E1FF909090BE0000000000000000000000004848FFFF8888FEFFDADAFEFFCACA
      FEFF7A7AFEFF4848FFFF6363FFFFB9B9FEFFB1B1B2FFFAFAFAFFFAFAFAFFE5E5
      E6FF959596FF8B8B8BFFF7F7F7FFFFFFFFFF343435370F4EA6FF0E489DFF0F4D
      A6FF0C499FFF044092FF204E8FFF0C3E87FF003481FF00337DFF00337CFF002C
      72FF757678B30000000000000000000000003D3D3D3E8D8176BC6C3C0FFF8960
      3DF117171718605F6E74646479805B58B2CD3E39C3ED5A57B5D3464547498F68
      49EB92806FC2784415FE745233F24E4D4D510000000000000000000000007F7F
      7FA7ABABABFFE3E3E3FEABABABFFAAAAAAFEABABABFFABABABFEAEAEAEFFBFBF
      BFFE909090BE0000000000000000000000004848FFFF4848FDFE8989FEFF9191
      FDFE4848FFFF4848FDFE4848FFFF8C8CFDFE909090FF505050FE282828FFE1E1
      E1FEFFFFFFFF7C7C7CFE454545FFFDFDFDFE343435371554B0FF134EA7FF1353
      AFFF0E4CA4FF074296FFADAEB0FF375F96FF013E90FF034091FF023E90FF0036
      83FF818388F30B0B0B0C0000000000000000000000003F3F3E41835B36EF9286
      7CB52A2A2A2B2F2AC8F86A688F9C39393C3D53535C5F6A6895A46E6D93A05756
      565B050505067A746F8962350AFE816852E30000000000000000000000007F7F
      7FA7C9C9C9FFE4E4E4FFA3A3A3FFA3A3A3FFA3A3A3FFBDBDBDFFE4E4E4FFE8E8
      E8FF909090BE0000000000000000000000004848FFFF4848FFFF4B4BFFFFB6B6
      FEFF4848FFFF4848FFFF4747FFFFD0D0FEFFE4E4E4FFD2D2D2FF070707FFB7B7
      B7FFFFFFFFFFF4F4F4FF020202FFD8D8D8FF34343537195AB8FF1652ACFF1656
      B2FF104FA7FF064296FFDFE1E3FF5079B1FF074397FF09479BFF074498FF033E
      90FF83878EFF4E4E4E53000000000000000000000000000000003F3F3E417472
      707E5D5D6569696897A669688791424246482F2AC8F838383A3B4A46BDE20303
      0304000000013434333566380CFF7D6249E60000000000000000000000007F7F
      7FA7BDBDBDFFE2E2E2FEA2A2A2FFA1A1A1FEA2A2A2FFA1A1A1FEBABABAFFC9C9
      C9FE909090BE0000000000000000000000004848FFFF4848FDFE4848FFFFA6A6
      FDFEB8B8FEFFADADFDFEBABAFEFFFCFCFDFE9191CEFFAFAFB0FE868686FF3C3C
      3DFEDBDBDCFFF0F0F0FE060606FFE6E6E6FE343435371B5EBDFF1755B1FF1757
      B5FF114FA9FF044093FFD8DADCFF4F77B0FF084499FF0D4AA0FF0B489DFF0743
      97FF888C93FF8A8A8AA500000000000000000000000000000000000000001B1B
      1B1C4F4F53566563A5BA6767838C65657D853731C6F33E3E41435A57B2CE0000
      00000000000189837C9E6B4118FB61605F660000000000000000000000007F7F
      7FA7AAAAAAFFDFDFDFFF919191FF919191FF919191FF919191FFB7B7B7FFC9C9
      C9FF909090BE0000000000000000000000004848FFFF4848FFFF4848FFFF6262
      FEFF9B9BFEFF4848FFFFA6A6FEFFE4E4FEFF5050D9FF676768FF797979FFA0A0
      A0FF424242FF5F5F5FFF969696FFFFFFFFFF343435371C60BDFF1959B4FF195A
      B8FF265CACFF1D509AFFBABBBEFF597CB0FF2157A4FF1853A7FF0E4CA3FF0844
      98FF8E939AFFBBBBBBEE07070708000000000000000000000000040404053D3D
      3D3E08080809514CBADB6867858F5E5D6D72565660645956B3D053535A5D0A0A
      0A0B827D798F93775EDB51515054000000000000000000000000000000007F7F
      7FA7DCDCDCFFEFEFEFFEE6E6E6FFE3E0D6FEDCCB9AFFE1DBC8FEE6E6E6FFE8E8
      E8FE909090BE0000000000000000000000004848FFFF4848FDFE4848FFFF4848
      FDFEB4B4FEFF4B4BFDFEEAEAFEFF9E9EFDFE4C4CF3FFBABABAFE767676FFB2B2
      B2FE7B7B7BFFF0F0F0FEFFFFFFFFFDFDFDFE343435371D62BCFF1A5AB3FF1A59
      B3FFDCDDDDFFBDBDBDFFADADADFFB9BABAFFCCCDCDFF648BBEFF0E4DA5FF0844
      99FF989CA3FFCECECFFF4747474A0000000000000000000000003A3A3A3C4F4F
      4F52000000001C1C1C1D69689AAA4340C1E85955B5D35C5C64671E1E1E1F5958
      575C4948484B0606060700000000000000000000000000000000000000005656
      5662535353FD515151FFB3B3B3FFF2F2F2FFE6D195FFDAB036FFE5CD8AFFF1EF
      E8FF909090BE0000000000000000000000004848FFFF4848FFFF4848FFFF4848
      FFFF8C8CFEFFA5A5FEFFFCFCFEFF5A5AFEFF4747FEFF39394AFF1A1A1AFF6A6A
      6AFFAEAEAEFFFDFDFDFFFFFFFFFFFFFFFFFF343435371C62BAFF195CB1FF195B
      B5FF2F5EA2FF2B5999FFCCCDCFFF5676A5FF214F95FF1B53A6FF1352ADFF0A47
      9DFF9CA0A7FFD3D3D3FF8989899C000000000000000000000000696765706E6C
      6A76000000000B0B0B0C262626273D3D3D3F716E6F7D8D8782A0020202030000
      0000000000000000000000000000000000000000000000000000000000000000
      00005151515C373737FA808080FFF1F1F1FEF2F2F2FFEADCB6FEDDB74AFFDBB4
      46FE9C937CC70000000000000000000000004848FFFF4848FDFE4848FFFF4848
      FDFE4F4FFEFFF2F2FDFEC9C9FEFF4848FDFE4848FFFFB5B5E3FE1D1D1DFF9797
      97FE757575FFF7F7F8FEFFFFFFFFFDFDFDFE343435371B5FB6FF0C3F97FF0C42
      9AFF1757B3FF1352ADFF849AB8FF396AB0FF1252ACFF1454B0FF1452AEFF0C49
      A1FFAAAEB5FFD8D8DDFFC7C7C8E80404040500000000000000006D6A687B8F80
      71CB06060607000000015F5D5C63825025FA7C4617FF6867656F000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000004646464C767676F5D3D3D3FFD3D3D3FFD3D3D3FFD2D1CCFFD6C3
      8BFFBE9F48F2B09E68C125252526000000004848FFFF4848FFFF4848FFFF4848
      FFFF4848FFFFB5B5FEFF8383FEFF4848FFFF4848FFFF6D6DBCFF262626FFCBCB
      CBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF343435371253ABFF0938A0FF093E
      9DFF185BB5FF1555B1FF1150A9FF1252ADFF1353AEFF1453AFFF1252ACFF104F
      A9FFB0B5BCFFBDBCDDFFB6B2E7FF3C3C3C3E0000000000000000595857605C32
      08FE8D847BB777757184927961DA774415FE7F5127F833333234000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000017171718242424252424242524242425242424252525
      25264D4C484F867F6A8E9A8F6DA62F2F2E304848FFFF4848FDFE4848FFFF4848
      FDFE4848FFFF4C4CFDFE4949FEFF4848FDFE4848FFFF7777E3FEFEFEFEFFFDFD
      FDFEFFFFFFFFFDFDFDFEFFFFFFFFFDFDFDFE34343537044393FF053195FF073B
      9BFF1455AEFF0F4EA6FF0B4AA0FF0D4CA3FF0E4DA5FF1251ACFF1454B0FF1150
      ABFFA9AEB3ED919191A14C4C4C4F060606070000000000000000151515166A48
      27F25B3007FE5B3107FE704923F773706E7C5453525721212122000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000001F1F1F2052514D55000000014848FFFF4848FFFF4848FFFF4848
      FFFF4848FFFF4848FFFF4848FFFF4848FFFF4848FFFF5B5BE8FFFBFBFBFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF3132323402408FFF043094FF0439
      97FF084698FF044090FF003A87FF013D8BFF054395FF0B499FFF1251ABFF0B48
      9DFF4343444A0000000000000000000000000000000000000000000000003F3E
      3E40867C73AA7B77738D28282829000000000000000108080809000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000004848FFFF4848FDFE4848FFFF4848
      FDFE4848FFFF4848FDFE4848FFFF4848FDFE4848FFFF4B4BF4FEEDEDEEFFFDFD
      FDFEFFFFFFFFFDFDFDFEFFFFFFFFFDFDFDFE060606072E2E2F302E2E2F302E2E
      2F302E2E2F302E2E2F302E2E2F302E2E2F302E2E2F302E2E2F302E2E2F302E2E
      2F30030303040000000000000000000000000000000000000000000000000000
      0000010101021818181917171718010101020000000000000000000000000000
      000000000000000000000000000000000000080808094D4E4E585C5E5F753C3C
      3C411A1A1A1B0606060700000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000005050506232323241F1F
      1F200C0C0C0D0202020300000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000007070708404040D9000000FF000000FF404040D9070707080000
      0000000000000000000000000000000000000000000000000000000000000000
      0000666983993D50CAF7404FB1EA4545464C0000000000000000000000000000
      00003233333561666A804C4C4D56070707085F798BB23C9EDFFF47A6E4FF3792
      CAF94B7995DA606D75A958595A6C303030321212121303030304000000000000
      0000000000000000000000000000000000000A0A0A0B71655EB88C5136F78C52
      39F47D5847E2756258C66F6763A362605F7D4D4D4D57313131331919191A0808
      0809000000010000000000000000000000000000000000000000000000000000
      0000000000001E1E1E1F000007FF0000E6FF0000E6FF000007FF1E1E1E1F0000
      000000000000000000000000000000000000000000001A1A1A1B5251505D2929
      292A1E1E1E1F404141443232323400000001000000014C4E4F564344454A5F65
      69753D99D3F8369EE0FF288ACDFC4748484F4685B2E045A3E7FFE7AD97FFC7B1
      B0FF979FB1FF6CABD4FF46A7DEFF397598F3536D7DCC62696D98424242480606
      0607000000000000000000000000000000004645444B985535FF764229FF2213
      0BFF3B2114FF593320FF78472EFF995A3BFFA8623FFFA05C3DFC8B5940F07C5D
      4FDA74665EBB6B6664964241414700000000000000005D5D5D756363639E1F1F
      1F20494949513A3A3ADD000025FF0000F6FF0000F6FF000026FF3A3A3ADD4949
      49511F1F1F206363639E5D5D5D75000000005753525EB04E33EED66E4BFFBE6A
      4BF7916252D3726763984C4C4C54202020216575839C2D94D9FE268AD0FD4FB7
      F0FF54BDF4FF5897BDE0636C737D0F0F0F104786B2E0419FE5FFF2D3C6FFC7C1
      DCFFFEF5E8FFF9D6C6FFD4AA9EFF8A7A7DFF6B7788FF5289A8FF3C799BEE4141
      4147000000000000000000000000000000004F4D4D56A05C3BFF56311EFF0000
      00FF000000FF000000FF020202FF050606FF0E0C0BFF291E18FF483326FF6746
      33FF86573EFFBB7854FFA36343F82A2A2A2C33333336041002FD0E5D00FF0E12
      0DF8000017FE0000ADFF0000FDFF0000FFFF0000FFFF0000FDFF0000B1FF0000
      1AFE120D12F85D005DFF110211FD333333369D6F62B6D7512EFFB78D6BFF36EC
      BAFFE4E75DFFECBA5EFFE39349FF4F4D63F60B84F0FF40A8E6FF4CB4EEFF3FA8
      E6FF3CA4E4FF4C4D4E5600000000000000004888B3E03E9CE3FFF3D6C9FF989B
      D7FF454FCFFFDDCECFFFDCC3B1FFC2AE9EFFCAB1A1FFCF9886FF69ACCEFF5A5C
      5D70000000000000000000000000000000004F4D4D56A76240FF57321FFF0000
      00FF000000FF040404FF080808FF0C0C0CFF0F0F0FFF121212FF141414FF1515
      15FF141415FF26201CFFD68C60FF504E4E57545454C4158C00FF28FF00FF1DBB
      16FF0000DEFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      E1FFB200D2FFFF00FFFF8D008EFF545454C49F7163B6DA5A36FFB58B69FF00E9
      CCFF1FEAC5FF3740BBFF55538AFF39353FFF00CBFBFF1DBBF5FF3BADF0FF52BA
      F2FF6094B3D51212121300000000000000004A8AB4E03B97E1FFF4D8CBFF9296
      DBFF767AD0FFDFD3D6FF8F7D77FF76A6CFFFBD9899FFE88665FF68ABCEFF5A5C
      5D70000000000000000000000000000000004F4E4D56AE6946FF593321FF0101
      01FF363636FF1E1E1EFF0E0E0EFF121212FF171717FF1A1A1BFF464647FF5858
      58FF373737FF1C1C1CFFD38B5FFF514F4F58292929E90E6100FF26F100FF0B4C
      A8FF0000FFFF0000FFFF0000CFFF000066FF000066FF0000CEFF0000FFFF0000
      FFFF3E00F7FFF100F2FF610062FF292929E99F7364B6DD6541FFAD8A67FF00E9
      CCFF10E9CEFF1D2DC4FF182BC4FF4B3857FF3C5B70FF1E89B4FF0398F0FF5B85
      BDFF555353600000000000000000000000004C8CB5E03893DFFFF4DACDFFDBED
      D9FF9DD7A0FFFBEFE8FFCADAE8FFAE98A6FFF68961FFD9502DFFA27371FF5C5E
      6076000000000000000000000000000000004F4E4D56B7704CFF5B3523FF9E9E
      9EFF9F9E9FFFBCBCBCFF4D4D4DFF585859FF515151FF3B3B3BFF4F4F50FF4F4F
      4FFF6C6C6DFF2A2A2BFFD0895EFF514F4F58212121225D5D5DB5021511FF0000
      FBFF0000FFFF0000D1FF00010FFF00337CFF00337CFF00010FFF0000D1FF0000
      FFFF0000FEFF13002AFF5D5D5DB6212121229F7667B6E2724EFFA98865FF00E9
      CCFF12E9CFFF1638E6FF1C48FCFF4147AFFF744D5AFF784F54FF797C6BFFEC58
      8AFF555352600000000000000000000000004D8EB6E03590DDFFF5DDD0FFC1E3
      C5FF67D37DFFF3E9DDFFE8BDB0FFF7B792FFF8926CFFF58B65FFDA502CFF8D61
      56CC303030320000000000000000000000004F4E4D56BF7852FF5D3825FFE2E2
      E2FF0D0D0DFF272727FF454545FF212121FF282829FF7A7A7AFF4A4B4BFF3232
      32FF313132FF2E2E2FFFCC865CFF51504F58000000004949495200003EFF0000
      FFFF0000FFFF00006BFF003179FF0068FFFF0068FFFF003279FF00006BFF0000
      FFFF0000FFFF000042FF4949495200000000A1786AB6E7845DFFA78763FF00E9
      CCFF12E9CFFF2C4BE7FF5F7BF6FF6C8AFFFF505FD7FF4A8E7DFF23FE3EFF9EAC
      50FF6C7966AE292A292B0B0B0B0C000000004E90B7E0318BDBFFF5DFD3FFFEFC
      FAFFE3F0E2FFB6DBB7FFFEF3ECFFF5BEA0FFFCC19BFFF8926CFFF48A64FFD951
      2DFF8D6257C83333333602020203000000004F4E4D56C98259FF5F3A27FFC7C7
      C7FF282828FF2A2A2BFF3B3B3BFF626263FF5C5C5DFF9C9C9CFF34434DFF17A6
      CAFF314650FF34383BFFC7835AFF50504F58000000004949495200003EFF0000
      FFFF0000FFFF00006BFF003279FF0068FFFF0068FFFF003279FF00006BFF0000
      FFFF0000FFFF000042FF4949495200000000A27C6DB6EC966EFFC27452FF43C6
      AAFF1FE7CDFF2A4AEAFF2848E8FF556DEAFF6B63B7FF979A67FF6BC25FFF50C9
      47FF21C83DFF37B54EF14DCB6DF2484A494F5191B8E02E87D9FFF6E2D5FFB9E3
      C0FF77D287FFFFFBF9FFFFF8F4FFFDF0E8FFF5BEA0FFFDC09BFFF8926CFFED88
      64FFB38377FF6C6C87DE3A3A3A3E000000004F4E4D56D18A5FFF613C29FF3838
      38FFBABABAFFC9C9C9FF5C5C5CFF2D2D2EFF373737FF9FA0A0FF2174A0FF12DE
      FFFF15E9FEFF2E6E7BFFC28058FF51504F58212121225D5D5DB6151511FF0000
      FBFF0000FFFF0000D1FF00010FFF00337CFF00337CFF00010FFF0000D1FF0000
      FFFF0000FEFF130019FF5D5D5DB621212122A27F71B6F2A984FFDC5C39FFDB56
      32FFDA603EFF2A3ACFFF263FDDFF2545E8FF794996FFCB6A6BFFE09E99FF839E
      5CFF24CA41FF29BD39FF34D756FF5357545E5293B8E02A83D6FFF6E4D7FFE2F0
      E4FF84DA97FFDFE7D5FFFBD0C0FFFBD0BFFFFBD6C6FFF5BFA2FFF9BD97FFBEAD
      B5FF405DE7FF1443FEFF50598AC527272728504E4D56D99165FF623E2AFF0D0D
      0DFF151515FF1E1E1EFF272728FF313131FF3A3A3BFF40825EFF1BC6A8FF0BC6
      FEFF0ED1FFFF316374FFBD7B55FF51504F582A2A2AE9606000FFF1F100FF4D4D
      A7FF0000FFFF0000FFFF0000CEFF000065FF000065FF0000CEFF0000FFFF0000
      FFFF4000C2FFF20032FF610014FF292929E9A38273B5F9BF98FFE37853FFD850
      2DFFDA5431FF3C35B0FF3637BBFF2635CDFF5643AEFFCB6869FFD78684FFD585
      83FF65CA6FFF33BF42FF2BD04BFF606860745396BAE0267CD4FFECDCCEFFD5D4
      D4FFEDEDECFFCAE4CCFFFFFCFAFFFFFBF6FFFEEBE2FFFAE1D7FFC2A599FF8393
      E9FF5778FFFF204DFFFF0B3BFEFF4C4C4D56504E4D56E0986AFF6E442FFF0D0D
      0DFF141515FF1E1E1FFF292929FF333333FF3C3C3DFF33743DFF27BC40FF0DB1
      DFFF317595FF425159FFB87853FF51504F58545454C48C8C00FFFFFF00FFBBBB
      15FF0000DCFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000FFFF0000
      E1FFB50043FFFF0035FF8C001CFF545454C4756A667DF5BD96FFFDC9A2FFF4A7
      82FFE9865FFFDF6846FFB14E55FFAC4F5DFF914C77FFD37571FFD07676FFD279
      78FFC6746FFF81BA79FE50C36AE65E68607363889DBB3B9BE5FF668EB8FFD3D1
      D0FFCCCBCAFFCCCBCAFFD4D2D2FFDFDDDBFFF8F3EDFFFFE6DBFF6AA0C7FF7082
      C2F1698AFFFF3F65FFFF5C6AABCD0B0B0B0C504E4D56E79D6FFFC0754FFF784D
      35FF674531FF5D4130FF543E31FF4B3B33FF443A35FF3C3B37FF37463BFF3949
      51FF414142FF3D3D3EFFB77753FF5150505832323235101002FD5C5C00FF1212
      0DF8000016FE0000AAFF0000FCFF0000FFFF0000FFFF0000FDFF0000AFFF0000
      19FE120C0EF85E0013FF100205FD33333336000000014745444985746D90BB87
      70D4E5936CFEF9AB85FFF8A078FFEF845EFFE76D4AFFDD7968FFD68483FFC861
      63FFCB696AFFA47F7ED0000000010000000014141415657781934D8CB3DD8FAA
      B9FEC9C9C9FFC7C6C5FFD5D4D4FFDDDCDBFFD3D2D1FFDCC1B4FF5B9DCFFF5D60
      637A767B98AE73768DA3151515160000000042414045EBA272FFC97B53FFCC81
      56FFD1865AFFD58B5EFFDA9063FFDE9567FFE29A6BFFE39B6CFFA65C3AFF9D5B
      3BFF935639FF594986FFB18084FF504F4F57000000005E5E5E756363639E1F1F
      1F20494949513A3A3ADD000022FF0000F6FF0000F6FF000025FF3A3A3ADD4949
      49511F1F1F206363639E5E5E5E75000000000000000000000000000000000000
      00001919191A5A55545E94786DA2C57456E6DF6A45FFE27154FFE4A6A1FFC253
      56FFC5595CFF5F5B5B6700000000000000000000000000000000000000002323
      2324959799C3B4B2B1FFADABAAFFBCBBBAFFE0DDDBFF7797B6FF4299D6FF4C4D
      4E5700000000000000000000000000000000020202037E726C94AC8269DBB27A
      5AEEBB7651FCC27A52FFC88257FFCF885DFFD48E62FFD68F63FFB66D48FFB26A
      45FFBC734DFF6959B0FF846288FA2A29292B0000000000000000000000000000
      0000000000001E1E1E1F000007FF0000E6FF0000E6FF000007FF1E1E1E1F0000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000012B2B2A2C655E5C6B998B89A1D9B5
      AFE9948281A50909090A00000000000000000000000000000000000000000000
      0000171717187170707DA1A0A0C4979898CF61686D80647A87A24C4D4F540101
      0102000000000000000000000000000000000000000000000000000000000000
      000002020203121212132424242535353437454443495452515B625F5D6D6E67
      647F776C67907369658933333335000000000000000000000000000000000000
      00000000000007070708404040D9000000FF000000FF404040D9070707080000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000300000000100010000000000800100000000000000000000
      000000000000000000000000FFFFFF00FFCFFFFF00000000C78FFE7F00000000
      C10FFE3F00000000C00FE00700000000E00FE00700000000E00FE00700000000
      E007C00300000000C00180010000000080008001000000000000C00300000000
      0003E00700000000001FE00700000000FC3FE00700000000FC3FFC3F00000000
      FE3FFE7F00000000FE3FFFFF00000000C3FFFFFF0000000080FFE00700000000
      8073E007000000008E07E007000000008401E007000000000000E00700000000
      8000E00700000000C000E00700000000E010E00700000000C001E00700000000
      C803E00700000000C81FF00700000000C03FF80100000000C03FFC0000000000
      C03FFFF800000000E13FFFFF00000000F0FF000083FFF81FF0F000000007F81F
      8000000000018001000000000000000000030000000000000003000000000000
      0007000000000000000700000000800100010000000080010000000000000000
      0000000000000000000000000000000000000000000000000001000000008001
      F00300000000F81FFE030000F001F81F00000000000000000000000000000000
      000000000000}
  end
end
