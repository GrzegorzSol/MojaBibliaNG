object SetupsWindow: TSetupsWindow
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'SetupsWindow'
  ClientHeight = 627
  ClientWidth = 890
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
  object SW_ButGroupSections: TButtonGroup
    Left = 0
    Top = 0
    Width = 193
    Height = 556
    CustomHint = SW_BalloonHint
    Align = alLeft
    BevelInner = bvNone
    BevelOuter = bvNone
    BevelKind = bkFlat
    ButtonHeight = 46
    ButtonWidth = 46
    ButtonOptions = [gboFullSize, gboGroupStyle, gboShowCaptions]
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
      end>
    ShowHint = True
    TabOrder = 0
    OnButtonClicked = SW_ButGroupSectionsButtonClicked
  end
  object SW_PControlSelected: TPageControl
    Left = 193
    Top = 0
    Width = 697
    Height = 556
    CustomHint = SW_BalloonHint
    ActivePage = SW_SheetFlags
    Align = alClient
    Images = SW_ImgListMainSmall
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnChange = SW_PControlSelectedChange
    object SW_SheetLajout: TTabSheet
      CustomHint = SW_BalloonHint
      Caption = 'Ustawienia wygl'#261'du aplikacji'
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object GrBoxSetColors: TGroupBox
        Left = 0
        Top = 0
        Width = 689
        Height = 354
        CustomHint = SW_BalloonHint
        Align = alTop
        Caption = 'Ustawienia kolor'#243'w aplikacji'
        TabOrder = 0
        object LabelColorFavorities: TLabel
          Left = 163
          Top = 117
          Width = 337
          Height = 13
          CustomHint = SW_BalloonHint
          AutoSize = False
          Caption = 'Kolor zaznaczenie ulubionych werset'#243'w'
          Layout = tlCenter
        end
        object LabelColorComment: TLabel
          Left = 163
          Top = 145
          Width = 337
          Height = 13
          CustomHint = SW_BalloonHint
          AutoSize = False
          Caption = 
            'Kolor czcionki znacznika dla  werset'#243'w, do kt'#243'rego istnieje kome' +
            'ntarz'
          Layout = tlCenter
        end
        object LabelColorBacground: TLabel
          Left = 163
          Top = 33
          Width = 337
          Height = 13
          CustomHint = SW_BalloonHint
          AutoSize = False
          Caption = 'Kolor podk'#322'adu dla tekstu werset'#243'w, w g'#322#243'wnym oknie'
          Layout = tlCenter
        end
        object LabelColorNameTranslate: TLabel
          Left = 163
          Top = 61
          Width = 337
          Height = 13
          CustomHint = SW_BalloonHint
          AutoSize = False
          Caption = 'Kolor czcionki, nazwy pe'#322'nego t'#322'umaczenia'
          Layout = tlCenter
        end
        object LabelColorAdresFullTranslates: TLabel
          Left = 163
          Top = 89
          Width = 337
          Height = 13
          CustomHint = SW_BalloonHint
          AutoSize = False
          Caption = 'Kolor czcionki, adresu wersetu, dla pe'#322'nego t'#322'umaczenia'
          Layout = tlCenter
        end
        object LabelColorBackgroundMarkComments: TLabel
          Left = 163
          Top = 173
          Width = 337
          Height = 13
          CustomHint = SW_BalloonHint
          AutoSize = False
          Caption = 'Kolor podk'#322'adu, znacznika istnienia komentarza do wersetu.'
          Layout = tlCenter
        end
        object LabelColorOrygTr: TLabel
          Left = 163
          Top = 201
          Width = 337
          Height = 13
          CustomHint = SW_BalloonHint
          AutoSize = False
          Caption = 'Kolor tekstu, dla oryginalnych t'#322'umacze'#324
          Layout = tlCenter
        end
        object LabelColorNameOrygTrans: TLabel
          Left = 163
          Top = 229
          Width = 337
          Height = 13
          CustomHint = SW_BalloonHint
          AutoSize = False
          Caption = 'Kolor nazwy oryginalnego t'#322'umaczenia'
          Layout = tlCenter
        end
        object LabelColorAdressOryg: TLabel
          Left = 163
          Top = 257
          Width = 337
          Height = 13
          CustomHint = SW_BalloonHint
          AutoSize = False
          Caption = 'Kolor adresu oryginalnego t'#322'umaczenia'
        end
        object SW_ColorBoxFavorities: TColorBox
          Left = 12
          Top = 114
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
          Top = 142
          Width = 145
          Height = 22
          CustomHint = SW_BalloonHint
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
          TabOrder = 1
          OnChange = SW_ColorAllChange
          OnGetColors = SW_ColorBoxGetColors
        end
        object SW_ColorBoxNameTranslate: TColorBox
          Left = 12
          Top = 58
          Width = 145
          Height = 22
          CustomHint = SW_BalloonHint
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
          TabOrder = 2
          OnChange = SW_ColorAllChange
          OnGetColors = SW_ColorBoxGetColors
        end
        object SW_ColorBoxBackground: TColorBox
          Left = 12
          Top = 30
          Width = 145
          Height = 22
          CustomHint = SW_BalloonHint
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
          TabOrder = 3
          OnChange = SW_ColorAllChange
          OnGetColors = SW_ColorBoxGetColors
        end
        object SW_ColorBoxColorAdressFulltranslates: TColorBox
          Left = 12
          Top = 86
          Width = 145
          Height = 22
          CustomHint = SW_BalloonHint
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
          TabOrder = 4
          OnChange = SW_ColorAllChange
          OnGetColors = SW_ColorBoxGetColors
        end
        object SW_ColorBackgroundMarkerComment: TColorBox
          Left = 12
          Top = 170
          Width = 145
          Height = 22
          CustomHint = SW_BalloonHint
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
          TabOrder = 5
          OnChange = SW_ColorAllChange
          OnGetColors = SW_ColorBoxGetColors
        end
        object SW_ColorBoxColorOrygTr: TColorBox
          Left = 12
          Top = 198
          Width = 145
          Height = 22
          CustomHint = SW_BalloonHint
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
          TabOrder = 6
          OnChange = SW_ColorAllChange
          OnGetColors = SW_ColorBoxGetColors
        end
        object SW_ColorBoxColorNameOrygTran: TColorBox
          Left = 12
          Top = 226
          Width = 145
          Height = 22
          CustomHint = SW_BalloonHint
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
          TabOrder = 7
          OnChange = SW_ColorAllChange
          OnGetColors = SW_ColorBoxGetColors
        end
        object SW_ColorBoxAdressOryg: TColorBox
          Left = 12
          Top = 254
          Width = 145
          Height = 22
          CustomHint = SW_BalloonHint
          Style = [cbStandardColors, cbExtendedColors, cbPrettyNames, cbCustomColors]
          TabOrder = 8
          OnChange = SW_ColorAllChange
          OnGetColors = SW_ColorBoxGetColors
        end
      end
      object SW_ScrBoxViewSetupColors: TScrollBox
        Left = 0
        Top = 354
        Width = 689
        Height = 173
        CustomHint = SW_BalloonHint
        HorzScrollBar.Tracking = True
        VertScrollBar.Tracking = True
        Align = alClient
        TabOrder = 1
        object SW_PBoxViewSetupColors: TPaintBox
          Left = 0
          Top = 0
          Width = 900
          Height = 217
          CustomHint = SW_BalloonHint
          Color = clBtnFace
          Font.Charset = EASTEUROPE_CHARSET
          Font.Color = clWindowText
          Font.Height = -16
          Font.Name = 'Times New Roman'
          Font.Style = []
          Font.Quality = fqClearType
          ParentColor = False
          ParentFont = False
          OnPaint = SW_PBoxViewSetupColorsPaint
        end
      end
    end
    object SW_SheetFlags: TTabSheet
      CustomHint = SW_BalloonHint
      Caption = 'Flagi i prze'#322#261'czniki aplikacji'
      ImageIndex = 1
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object SW_CBoxIsDisplaySplashScreen: TCheckBox
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 683
        Height = 17
        CustomHint = SW_BalloonHint
        Align = alTop
        Caption = 
          'Czy wy'#347'wietla'#263' ekran informacyjny podczas uruchamiania aplikacji' +
          '?'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 0
        OnClick = SW_CBox_Click
      end
      object SW_CBoxIsRequestEnd: TCheckBox
        AlignWithMargins = True
        Left = 3
        Top = 26
        Width = 683
        Height = 17
        CustomHint = SW_BalloonHint
        Align = alTop
        Caption = 'Czy przed zamkni'#281'ciem aplikacji pyta'#263' o zgod'#281'?'
        ParentShowHint = False
        ShowHint = True
        TabOrder = 1
        OnClick = SW_CBox_Click
      end
      object SW_CBoxOnlyOne: TCheckBox
        AlignWithMargins = True
        Left = 3
        Top = 49
        Width = 683
        Height = 17
        CustomHint = SW_BalloonHint
        Align = alTop
        Caption = 'Dozwolona tylko jedna kopia aplikacji'
        TabOrder = 2
      end
    end
    object SW_SheetPaths: TTabSheet
      CustomHint = SW_BalloonHint
      Caption = 'Scie'#380'ki dost'#281'pu'
      ImageIndex = 2
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object SW_GrBoxSelectPathDirMulti: TGroupBox
        Left = 0
        Top = 0
        Width = 689
        Height = 117
        CustomHint = SW_BalloonHint
        Align = alTop
        Caption = 'Wyb'#243'r katalog'#243'w z multimediami - uwaga nr. 1'
        TabOrder = 0
        object SW_LEditPath3: TLabeledEdit
          Left = 161
          Top = 80
          Width = 241
          Height = 21
          CustomHint = SW_BalloonHint
          AutoSize = False
          EditLabel.Width = 148
          EditLabel.Height = 13
          EditLabel.CustomHint = SW_BalloonHint
          EditLabel.Caption = 'Wybierz katalog z multimediami'
          LabelPosition = lpLeft
          ParentShowHint = False
          ReadOnly = True
          ShowHint = True
          TabOrder = 0
          TextHint = 'Wybierz katalog z multimediami...'
        end
        object SW_LEditPath1: TLabeledEdit
          Left = 161
          Top = 26
          Width = 241
          Height = 21
          CustomHint = SW_BalloonHint
          AutoSize = False
          EditLabel.Width = 148
          EditLabel.Height = 13
          EditLabel.CustomHint = SW_BalloonHint
          EditLabel.Caption = 'Wybierz katalog z multimediami'
          LabelPosition = lpLeft
          ParentShowHint = False
          ReadOnly = True
          ShowHint = True
          TabOrder = 1
          TextHint = 'Wybierz katalog z multimediami...'
        end
        object SW_LEditPath2: TLabeledEdit
          Left = 161
          Top = 53
          Width = 241
          Height = 21
          CustomHint = SW_BalloonHint
          AutoSize = False
          EditLabel.Width = 148
          EditLabel.Height = 13
          EditLabel.CustomHint = SW_BalloonHint
          EditLabel.Caption = 'Wybierz katalog z multimediami'
          LabelPosition = lpLeft
          ParentShowHint = False
          ReadOnly = True
          ShowHint = True
          TabOrder = 2
          TextHint = 'Wybierz katalog z multimediami...'
        end
        object SW_ButtSelectDirMulti_1: TButton
          Left = 408
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
          Left = 408
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
          Left = 408
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
    end
    object SW_OthersSetups: TTabSheet
      CustomHint = SW_BalloonHint
      Caption = 'Inne ustawienia'
      ImageIndex = 3
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
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
        Top = 44
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
        Top = 72
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
        MaxLength = 2
        MaxValue = 14
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
        Top = 73
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
        Top = 45
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
        Top = 16
        Width = 148
        Height = 23
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
        Top = 44
        Width = 148
        Height = 23
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
        Top = 72
        Width = 148
        Height = 23
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
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object SW_ListViewAllTranslates: TListView
        AlignWithMargins = True
        Left = 12
        Top = 35
        Width = 665
        Height = 480
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
      end
      object SW_STextInfoHeadSelectTranslates: TStaticText
        AlignWithMargins = True
        Left = 3
        Top = 3
        Width = 683
        Height = 17
        CustomHint = SW_BalloonHint
        Align = alTop
        Alignment = taCenter
        AutoSize = False
        BorderStyle = sbsSunken
        Caption = 'Wyb'#243'r u'#380'ywanych t'#322'umacze'#324' w aplikacji - uwaga nr. 1 '
        TabOrder = 1
      end
    end
  end
  object SW_GrPanelButtons: TGridPanel
    Left = 0
    Top = 598
    Width = 890
    Height = 29
    Align = alBottom
    Caption = 'SW_GrPanelButtons'
    ColumnCollection = <
      item
        Value = 33.468126601646180000
      end
      item
        Value = 33.642191107269060000
      end
      item
        Value = 32.889682291084750000
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
      end>
    RowCollection = <
      item
        Value = 100.000000000000000000
      end>
    ShowCaption = False
    TabOrder = 2
    DesignSize = (
      890
      29)
    object SW_ButtSetupSave: TButton
      Left = 90
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
      Left = 705
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
    end
    object SW_ButtSetupReturn: TButton
      Left = 368
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
    end
  end
  object SW_STextInfo: TStaticText
    Left = 0
    Top = 556
    Width = 890
    Height = 42
    Align = alBottom
    AutoSize = False
    BevelInner = bvNone
    BevelOuter = bvNone
    BorderStyle = sbsSunken
    Color = clInfoBk
    ParentColor = False
    TabOrder = 3
  end
  object SW_ImgListMain: TImageList
    ColorDepth = cd32Bit
    DrawingStyle = dsTransparent
    Height = 32
    Width = 32
    Left = 816
    Top = 136
    Bitmap = {
      494C010105000800040020002000FFFFFFFF2110FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000800000004000000001002000000000000080
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000909090A4848484A5C5C5B603F3F3F410909090A000000000000
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
      00003C3C3C3D918375CE6F4F30EC623E18F8785D43E68E7E6EDC797876862929
      292A000000000000000000000000000000000000000000000000000000000000
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
      0000000000000000000000000000000000000000000000000000000000001919
      191A89725CDF5A2F06FF5A2F06FF5B3007FE5A2F06FF592F05FF5C3208FE8B76
      61E27372717B0808080900000000000000000000000000000000000000000000
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
      000000000000000000000000000000000000000000000000000000000000706E
      6C785B3007FE5B3007FE5B3007FE5B3007FE5C3107FE5D3107FE5E3208FF6236
      0BFE744F2CF3938E88B21F1F1F20000000000000000000000000000000000000
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
      000000000000000000000000000000000000000000000000000000000000897D
      71B85A2F06FF5B3006FF5B3007FE735335F07E7975914B4A4A4E4949484C6B68
      6674918376BD784D24F8978D84C1202020210000000000000000000000000000
      0000000000000000000000000000000000000000000000000000060606070000
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
      0000000000000000000000000000000000000000000000000000030303048773
      62CE5A2F06FF5C3107FE6C4A27F3565555590000000000000000000000000000
      0000000000012B2B2B2C8A8078A397918BB40808080900000000000000000000
      0000000000000000000000000000000000001919191A6666666A3B3B3B3C0000
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
      00000000000000000000000000000000000000000000000000000B0B0B0C826D
      58D25A2F05FF5C3006FF90877DBA010101020000000000000000000000000000
      00000000000000000000000000013939393A5353535600000000000000000000
      0000000000000909090A3C3C3C3D7A787583937F6BD9807D7B8E000000000000
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
      000000000000000000000000000000000000000000000000000008080809836E
      5AD25B2F06FF603409FE7D7A768D000000000000000000000000000000000000
      00000000000000000000000000000000000022222223242424256867676D7E7C
      798A938C85AE9C8772DC885D39F2754214FE90755CE535353536000000000000
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
      0000000000000000000000000000000000000000000000000000000000008878
      69C55E3208FF65370BFF79767487010101024545444648484849000000000000
      000000000000000000000000000000000000000000000000000032323233967D
      65D37C4717FF7C4717FF7C4617FF794515FF7D5029F695816BE182807E903333
      3334000000000000000000000000000000000000000000000000000000000000
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
      000000000000000000000000000000000000000000000000000000000000857A
      70AD62350AFF6B3B0FFE8F8983AB8F8A85A3978F88B207070708000000000000
      0000151515161A1A1A1B6461A8BE5855B3D16663A7BC6363757B171717180F0F
      0F10928479B47D4718FE7D4718FF7D4718FE784415FF764314FE714012FE8D74
      5EE1807E7D8D1B1B1B1C00000000000000000000000000000000000000000000
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
      0000000000000000000000000000000000003B3B3B3C4D4C4C4F525252558C85
      7CAC66380CFF6F3D10FF794A1EFB85572FF65151515300000000000000005959
      65694641C0E6000000005C59B1CC251FCCFF251FCCFF251FCCFF3833C5F25353
      5A5D0808080990857AAF7D4717FF7F4B1EFC7C4818FE7A4516FF784415FF7442
      13FE643A10FD918577D03B3B3B3C000000000000000000000000000000000000
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
      0000000000000000000000000000000000000404040561605F67735335EF6336
      0CFE6A3A0EFF734112FE784415FF9C8975D60B0B0B0C000000005A5A666B251F
      CAFE2620CBFE1D1D1D1E65647A82433FC0E8605EACC43732C4F2251FCCFF2721
      C9FD53535A5D0E0E0E0F977F6AD0977E66E04A49494C958474BF794616FE7945
      16FE67390DFE5D3108FE8E7E6DD9303030310000000000000000000000000000
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
      0000000000000000000000000000000000000000000000000001262626278A75
      61D06D3D0FFF744213FF7A4616FF827F7C8F0000000021212122312BC7F7251F
      CCFF251FCCFF4F4E55582020202112121213161616170E0E0E0F69679BAC251F
      CCFF3934C4F1171717182B2B2B2C998470DB0909090A03030304726E697F7946
      16FE64370BFF5B3007FF5A2F06FF8F8B86AC0000000000000000000000000000
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
      0000000000000000000000000000000000000000000000000000000000000E0E
      0E0F928170C2774415FE83542AF64D4C4C4F0000000068678089251FCCFF3C36
      C3EE65647B8369688995000000006360A8BF2C26C8FB5151595C070707084D4A
      BADD251FCCFF6362747A00000000626261660A0A0A0B00000000010101028980
      77A567380CFF5E3208FE5A2F06FF836C57E40000000000000000000000000000
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
      00000F0F0F10937C66CF937458E233333334000000005E5BAFC9251FCCFF5A5A
      666B3E3E40425F5CAEC6000000006764A2B6251FCCFF4843BFE4010101026362
      767D251FCCFF6563A6BB00000000111111120404040500000000000000005C5A
      59606A3A0EFF603409FF5A3006FF846D58DE0000000000000000000000000000
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
      000000000000232323249B897BCC1515151600000000514EB9DA251FCCFF2F2F
      303169678792696799A9000000005B5A676C251FCCFF251FCAFE1F1F1F204646
      4B4D251FCCFF5956B2CF00000000000000000000000000000000000000006E6C
      6A766B3B0EFF63360BFE5B3006FF91887FBC0000000000000000000000000000
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
      000000000000000000005050505208080809000000005C59B0CB251FCCFF3F3F
      42445E5D6C715551B7D6030303044B4B5153251FCCFF251FCCFF252525264646
      4B4D251FCCFF6462A7BD00000000000000000000000000000000101010119782
      6ED46C3B0EFF62350AFF78593BEE3F3F3F410000000000000000000000000000
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
      000000000000000000000A0A0A0B07070708000000006968848D251FCCFF6967
      96A50E0E0E0F504DB8DA5552B7D5433FC0E8251FCCFF5856B3D0010101026967
      8B97251FCCFF6362767D0000000000000000000000000303030487837F947442
      14FE6B3B0EFF765333F062626167000000010000000000000000000000000000
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
      00000000000000000000606060620909090A00000000252525262E28C9F92620
      CBFE5B5A676C111111126262747B6A6894A2646479811313131446464A4C2C28
      CAFA3530C7F41A1A1A1B000000000000000008080809827F7C8D814F24FB7240
      12FF8F755CE05251515400000000000000000000000000000000000000000000
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
      0000000000001414141582807E8B000000010000000000000000605F7076251F
      CAFE2620CBFE6461A8BE58586367414144464D4D5356696894A32A24C9FC251F
      CAFE5857626600000000000000012A2A2A2B948C85AC815125FA8F6B4CE97F7B
      778B1B1B1B1C0000000000000000000000000000000000000000000000000000
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
      00000000000051504F5387827E99000000000000000000000000000000005F5F
      6F752E28C9F9251FCCFF251FCCFF251FCCFF251FCCFF251FCCFF322DC6F65A5A
      6569010101023D3D3D3E797775819C8A7ACC95877ABA6A6866701C1C1C1D0000
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
      00000000000089827BA08F8781AD000000000000000000000000000000000000
      0000242424256766838C5D5BAFC9524FB7D85E5BAEC769687F87202020211C1C
      1C1D2929292A12121213141414150D0D0D0E0000000100000000000000000000
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
      000001010102937F6CD096897CCB020202030000000000000000000000000000
      00000000000000000000000000000000000003030304323232337573727D9692
      8EA70D0D0D0E0000000000000000000000000000000000000000000000000000
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
      00000E0E0E0F86694FE08E7760DF2A2A2A2B0000000000000000000000003232
      32334C4C4C4E4E4D4D5062616167878480979E8D7ED0906846EF7E491AFE5D5C
      5B60000000000000000000000000000000000000000000000000000000000000
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
      0000131313147A5C3FE3704821F76564646A0000000000000000000000000404
      04055A59585E926D4FE67C4717FF7C4717FF7C4617FF7D4718FF96785DE22020
      2021000000000000000000000000000000000000000000000000000000000000
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
      00000F0F0F10775A3EE362350AFF95887BCE1B1B1B1C00000000000000000000
      000000000000464646488C6440EE7D4718FE7D4718FF7D4718FE978D84B80000
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
      000003030304836F5AD35C3006FF613A11FC928C85B93A3A3A3B0A0A0A0B2E2E
      2E2F78767480906C4DEC794515FF7A4516FF7A4515FF7A4515FF72706E7B0000
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
      000000000000857D74A85A2F06FF5B3006FE5B3108FE7F6349E882684FEA7E5E
      40EC724113FE754213FE734112FF744314FE8D6B4DE6754416FE525252550000
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
      0000000000004F4E4E525A2F06FF5A2F05FF5A3006FF5B3007FE5A2F06FF5B31
      07FE613409FF6F3E10FE744B24F78A847F9C282828298C7057DC464646480000
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
      00000000000005050506877664CB5A3006FE5A2F06FF5B3007FE5A2F06FF5C31
      07FE5F3208FF896F58E15757565A030303040000000055545358404040420000
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
      000000000000000000002323232486725FD45A2F06FF5A2F05FF5B3107FE8065
      4CE47B78758A1B1B1B1C00000000000000000000000004040405262626270000
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
      000000000000000000000000FFFFFF00F83FFFFF000000000000000000000000
      F00FFFFF000000000000000000000000E003FFFF000000000000000000000000
      E001FFFF000000000000000000000000E000FFDF000000000000000000000000
      C0F07F1F000000000000000000000000C0FC783F000000000000000000000000
      C1FF003F000000000000000000000000E03FC00F000000000000000000000000
      E030000300000000000000000000000000640001000000000000000000000000
      0040000000000000000000000000000080800000000000000000000000000000
      E0820240000000000000000000000000F0820260000000000000000000000000
      F88203E0000000000000000000000000FC8003C0000000000000000000000000
      FC800380000000000000000000000000FC800303000000000000000000000000
      F8C00407000000000000000000000000F9E0001F000000000000000000000000
      F9F0007F000000000000000000000000F0FF07FF000000000000000000000000
      F0E00FFF000000000000000000000000F0E00FFF000000000000000000000000
      F0781FFF000000000000000000000000F0001FFF000000000000000000000000
      F8001FFF000000000000000000000000F8001FFF000000000000000000000000
      F8009FFF000000000000000000000000FC039FFF000000000000000000000000
      FE0FFFFF000000000000000000000000FFFFFFFF803FFFFFFFFFFFFFFFF00FFF
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
    Left = 813
    Top = 88
    Bitmap = {
      494C010106000800040010001000FFFFFFFF2110FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000002000000001002000000000000020
      0000000000000000000000000000000000000000000000000000000000000000
      0000101010113F3F3F45656666826E6F7094606061762D2D2D2F040404050909
      090A000000000000000000000000000000000000000000000000000000000000
      00002E2E2E306C6D83985B60B9DA373FCAFA2B33C5FA4E54B6DB686A849A3131
      3133000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000001C1C
      1C1D6A6B6C969BA0A8F5C5CBD1FFD8DDE1FFD1D6DBFFA2A5ABF47E6C5CCD9176
      5EAB88756299967F63A727272628000000000000000000000000070707086C6D
      8699343FCEFD313CD0FF303BCFFF222DC8FF1D28C6FF1D28C7FF1D28C8FF1F2A
      C8FE686B889D0909090A00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000C0C0C0D2C2C2C2E6262
      637A939CA6FBADB6BEFFC5CBD1FFD8DDE1FFD1D6DBFFBEC4CBFF9EA4AAFFA254
      0CFFCE8129FFB68E61D3242424250E0E0E0F0000000007070708696DA4C0323F
      D2FF323FD2FF313ED1FF222DC5FF1D28C3FF1D28C3FF1D29C4FF1D29C7FF1E2A
      CAFF1E2BCBFF5D64A5C40909090A000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000004F4F505496A0AAF6C6CCD2FFBDC4
      CBFF9EA8B1FFADB6BEFFC5CBD1FFD8DDE1FFD1D6DBFFBEC4CBFFA3ACB5FFA168
      39FFD1904FFF978572A5645E5769C98B2FEE000000006C6E85973342D4FF3342
      D4FF3342D4FF6F6EA5FFBDA765FFBDA866FFBDA967FFBEA968FF666394FF1F2C
      CBFF1F2CCCFF1F2DCDFF696B899D000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000008C9298C495999DBB3C3C3C3D8C8F
      92AF96A1ABFFADB6BEFFC5CBD1FFD8DDE1FFD1D6DBFFBEC4CBFFA3ACB5FF9C82
      6FE08073688D635D586800000000000000002C2C2C2E3748D5FD3444D7FF3444
      D7FF3444D7FF5A60B6FFB29E6CFFD5B752FFD5B954FFB09D6EFF4C50ADFF1F2E
      CDFF1F2ECDFF1F2ECEFF2130CEFE313131330000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009C9FA2BAABB2B9F587898A9A979D
      A3D096A1ABFFADB6BEFFC5CBD1FFD8DDE1FFD1D6DBFFBEC4CBFFA3ACB5FF9589
      82DE4C49484F0000000000000000000000006B6D82943547D9FF3547D9FF3547
      D9FF3547D9FF3547D9FF595FB5FFD3B34AFFD1AC3DFF4A4B9FFF202FCDFF202F
      CEFF2030CFFF2030D0FF2030D1FF696C869A0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000018181819969899A1CED3D7F5B5BD
      C4FFA0AAB3FFB4BABFFFA4AAB0FF9D9C9FFFAAB1A6FFC4CCCBFFABB4BCFF8C92
      98CD00000000000000000000000000000000626DBCD5364ADBFF364ADBFF364A
      DBFF364ADBFF3549DBFF3C49C8FFD3BC6CFFD2B046FF353BABFF2030CEFF2031
      CFFF2031D0FF2032D1FF2032D2FF515BBEDB0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000D0D0D0E9AA5
      ABFD86A383FF324638FF606A75FF4F5454FF8A6A4CFF5E8A4BFF6F8D69FF9AA4
      ABF3000000010000000000000000000000004458D7F5374DDDFF374DDDFF374D
      DDFF364CDDFF2638D0FF4453CEFFBFBFB0FFD3B662FF4649A4FF2132D0FF2132
      D1FF2133D1FF2133D2FF2134D3FF2A3BD0FA0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000002727272891A9
      93FF4D823CFF5F6B72FF818C97FF5D7064FFA98769FF543F19FF507A3FFFA1A8
      A9FF1C1C1C1D000000000000000000000000465BD8F43850E0FF3850E0FF374F
      DEFF2B3DC9FF2031CBFF3344CEFFDAE7EAFFCDCCBDFF3742B8FF2133D1FF2537
      CBFF2033CEFF2135D3FF2235D4FF2C3ED1FA0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000004040404384A8
      79FF3A5E35FF7C8893FF8B959EFF677B6BFF929369FF614139FF909596FFA9A9
      A8FF404040430000000000000000000000006373BFD43853E2FF3853E2FF657B
      E3FFCDDAE4FF2637C3FF4354CEFFD4E0E3FFE2EDF0FF4B5BCBFF273AD2FFCCD9
      E6FF5768CFFF2136D4FF2338D6FF5D6DC4DA0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000222222238E85
      7AFF647072FF87929BFF959EA7FF768278FF8F9D84FFA2A2A0FF616A73FFAFAF
      AFFFA09F9ED91313131400000000000000006B6F82923956E4FF3956E4FF6983
      E6FFDBE8ECFF8694D2FF7284D3FFDBE8ECFFE0EBEFFF7586D1FF8493DAFFDBE8
      ECFF5B6DD1FF2439D7FF3550E1FF6D7287980000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000525252579C97
      93DC959FA6F7919BA5FF9EA8B0FF8D8B8CFFA5A2A0FFAAAAA9FF838689F58F90
      91AB9B9A99FF7D8084B1000000000000000029292A2B3F5BE3FC3A59E6FF6B86
      E9FFDFECF0FFDFECF0FFDFECF0FFDFECF0FFDFECF0FFDFECF0FFDFECF0FFDFEC
      F0FF5E71D5FF3552E3FF3D5AE4FD2E2E2E300000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000008B8887A14C4C
      4C50212121227D7F808BA4A8ABC7A19F9FEBA3A2A2D6A8A7A6FE7F7E7E9F0404
      040580868FC65F6C79FF827876AD00000000000000006C7185933B5CE9FF4B69
      EAFF6F8BECFF6F8BECFF6F8BECFF6F8BECFF6F8BECFF6F8BECFF6F8BECFF6F8B
      ECFF4B68E7FF3B5CE9FF6D738B99000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000002020202170899ED70202
      02030000000000000000000000006F727480404040437B8C9DD66E839BCF0000
      0000403E3D42D4942CFEB5824BE10404040500000000060606076E7AAABB3C5E
      EBFF3C5EEBFF3C5EEBFF3C5EEBFF3C5EEBFF3C5EEBFF3C5EEBFF3C5EEBFF3C5E
      EBFF3C5EEBFF6C7AAEC007070708000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000656B7380677F97B90000
      00000000000000000000000000005F80A0CB47494B4E73808EA16193C4FD1515
      1516000000005B57525E21212122000000000000000000000000060606076D72
      86934063EAFC3D61EDFF3D61EDFF3D61EDFF3D61EDFF3D61EDFF3D61EDFF4062
      EBFD6D748A970707070800000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000003C3D3E40131313140000
      00000000000000000000000000006569717F0B0B0B0C3838393B5355575D0404
      0405000000000000000000000000000000000000000000000000000000000000
      000029292A2B6C718492667DC7D44C6CE5F44A6CE6F5667CC9D56D7286942C2C
      2C2E000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
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
    Left = 813
    Top = 40
  end
  object SW_ImgListMainSmall: TImageList
    ColorDepth = cd32Bit
    DrawingStyle = dsTransparent
    Left = 813
    Top = 184
    Bitmap = {
      494C010107003001040010001000FFFFFFFF2110FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000002000000001002000000000000020
      0000000000000000000000000000000000000000000000000000434343458781
      7BA4767471832B2B2B2C00000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000004848FFFF4848FFFF4848FFFF4848
      FFFF4848FFFF4848FFFF4848FFFF9E9EE4FFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000023232324684421F75B30
      07FE5B3107FE6D4825F77B78768A070707080000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000001C1C
      1C1D575757645757576457575764575757645757576457575764575757645757
      5764242424250000000000000000000000004848FFFF4848FDFE4848FFFF4848
      FDFE4848FFFF4848FDFE4848FFFF7E7EE3FEFEFEFEFFFDFDFDFEFFFFFFFFFDFD
      FDFEFFFFFFFFFDFDFDFEFFFFFFFFFDFDFDFE0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000005B5A59625A3006FF8876
      64CF373636382F2F2F306F6C6978807C798E0101010200000000000000000000
      0000202020210F0F0F1000000000000000000000000000000000000000007A7A
      7AA1EFEFEFFFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3F3FFF3F3
      F3FF8A8A8AB80000000000000000000000004848FFFF4848FFFF4848FFFF4848
      FFFF4848FFFF4848FFFF4848FFFF6060E6FFFCFCFCFFFFFFFFFFFFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000006361606E5C3007FF4F4F
      4E520000000000000000000000000D0D0D0E272727283B3B3B3D61605F658F86
      7EAC8A847FA10000000000000000000000000000000000000000000000007F7F
      7FA7979797FFE3E3E3FEAEAEAEFFADADADFEAEAEAEFFADADADFEAEAEAEFFBFBF
      BFFE909090BE0000000000000000000000004848FFFF4848FDFE4848FFFF4848
      FDFE4848FFFF4848FDFE4848FFFF4E4EF1FEF1F1F1FFFDFDFDFEFFFFFFFFFDFD
      FDFEFFFFFFFFFDFDFDFEFFFFFFFFFDFDFDFE0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000005655545C64360BFF6E6D
      6B7650505052000000000B0B0B0C56565D634A494C4E4949494C8C6340EC7B46
      17FF845934F58C857FA92929292A000000000000000000000000000000007F7F
      7FA7DCDCDCFFE6E6E6FFAEAEAEFFAEAEAEFFAEAEAEFFAEAEAEFFAEAEAEFFE1E1
      E1FF909090BE0000000000000000000000004848FFFF8888FEFFDADAFEFFCACA
      FEFF7A7AFEFF4848FFFF6363FFFFB9B9FEFFB1B1B2FFFAFAFAFFFAFAFAFFE5E5
      E6FF959596FF8B8B8BFFF7F7F7FFFFFFFFFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003D3D3D3E8D8176BC6C3C0FFF8960
      3DF117171718605F6E74646479805B58B2CD3E39C3ED5A57B5D3464547498F68
      49EB92806FC2784415FE745233F24E4D4D510000000000000000000000007F7F
      7FA7ABABABFFE3E3E3FEABABABFFAAAAAAFEABABABFFABABABFEAEAEAEFFBFBF
      BFFE909090BE0000000000000000000000004848FFFF4848FDFE8989FEFF9191
      FDFE4848FFFF4848FDFE4848FFFF8C8CFDFE909090FF505050FE282828FFE1E1
      E1FEFFFFFFFF7C7C7CFE454545FFFDFDFDFE0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000003F3F3E41835B36EF9286
      7CB52A2A2A2B2F2AC8F86A688F9C39393C3D53535C5F6A6895A46E6D93A05756
      565B050505067A746F8962350AFE816852E30000000000000000000000007F7F
      7FA7C9C9C9FFE4E4E4FFA3A3A3FFA3A3A3FFA3A3A3FFBDBDBDFFE4E4E4FFE8E8
      E8FF909090BE0000000000000000000000004848FFFF4848FFFF4B4BFFFFB6B6
      FEFF4848FFFF4848FFFF4747FFFFD0D0FEFFE4E4E4FFD2D2D2FF070707FFB7B7
      B7FFFFFFFFFFF4F4F4FF020202FFD8D8D8FF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000003F3F3E417472
      707E5D5D6569696897A669688791424246482F2AC8F838383A3B4A46BDE20303
      0304000000013434333566380CFF7D6249E60000000000000000000000007F7F
      7FA7BDBDBDFFE2E2E2FEA2A2A2FFA1A1A1FEA2A2A2FFA1A1A1FEBABABAFFC9C9
      C9FE909090BE0000000000000000000000004848FFFF4848FDFE4848FFFFA6A6
      FDFEB8B8FEFFADADFDFEBABAFEFFFCFCFDFE9191CEFFAFAFB0FE868686FF3C3C
      3DFEDBDBDCFFF0F0F0FE060606FFE6E6E6FE0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000001B1B
      1B1C4F4F53566563A5BA6767838C65657D853731C6F33E3E41435A57B2CE0000
      00000000000189837C9E6B4118FB61605F660000000000000000000000007F7F
      7FA7AAAAAAFFDFDFDFFF919191FF919191FF919191FF919191FFB7B7B7FFC9C9
      C9FF909090BE0000000000000000000000004848FFFF4848FFFF4848FFFF6262
      FEFF9B9BFEFF4848FFFFA6A6FEFFE4E4FEFF5050D9FF676768FF797979FFA0A0
      A0FF424242FF5F5F5FFF969696FFFFFFFFFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000040404053D3D
      3D3E08080809514CBADB6867858F5E5D6D72565660645956B3D053535A5D0A0A
      0A0B827D798F93775EDB51515054000000000000000000000000000000007F7F
      7FA7DCDCDCFFEFEFEFFEE6E6E6FFE3E0D6FEDCCB9AFFE1DBC8FEE6E6E6FFE8E8
      E8FE909090BE0000000000000000000000004848FFFF4848FDFE4848FFFF4848
      FDFEB4B4FEFF4B4BFDFEEAEAFEFF9E9EFDFE4C4CF3FFBABABAFE767676FFB2B2
      B2FE7B7B7BFFF0F0F0FEFFFFFFFFFDFDFDFE0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000003A3A3A3C4F4F
      4F52000000001C1C1C1D69689AAA4340C1E85955B5D35C5C64671E1E1E1F5958
      575C4948484B0606060700000000000000000000000000000000000000005656
      5662535353FD515151FFB3B3B3FFF2F2F2FFE6D195FFDAB036FFE5CD8AFFF1EF
      E8FF909090BE0000000000000000000000004848FFFF4848FFFF4848FFFF4848
      FFFF8C8CFEFFA5A5FEFFFCFCFEFF5A5AFEFF4747FEFF39394AFF1A1A1AFF6A6A
      6AFFAEAEAEFFFDFDFDFFFFFFFFFFFFFFFFFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000696765706E6C
      6A76000000000B0B0B0C262626273D3D3D3F716E6F7D8D8782A0020202030000
      0000000000000000000000000000000000000000000000000000000000000000
      00005151515C373737FA808080FFF1F1F1FEF2F2F2FFEADCB6FEDDB74AFFDBB4
      46FE9C937CC70000000000000000000000004848FFFF4848FDFE4848FFFF4848
      FDFE4F4FFEFFF2F2FDFEC9C9FEFF4848FDFE4848FFFFB5B5E3FE1D1D1DFF9797
      97FE757575FFF7F7F8FEFFFFFFFFFDFDFDFE0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000006D6A687B8F80
      71CB06060607000000015F5D5C63825025FA7C4617FF6867656F000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000004646464C767676F5D3D3D3FFD3D3D3FFD3D3D3FFD2D1CCFFD6C3
      8BFFBE9F48F2B09E68C125252526000000004848FFFF4848FFFF4848FFFF4848
      FFFF4848FFFFB5B5FEFF8383FEFF4848FFFF4848FFFF6D6DBCFF262626FFCBCB
      CBFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000595857605C32
      08FE8D847BB777757184927961DA774415FE7F5127F833333234000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000017171718242424252424242524242425242424252525
      25264D4C484F867F6A8E9A8F6DA62F2F2E304848FFFF4848FDFE4848FFFF4848
      FDFE4848FFFF4C4CFDFE4949FEFF4848FDFE4848FFFF7777E3FEFEFEFEFFFDFD
      FDFEFFFFFFFFFDFDFDFEFFFFFFFFFDFDFDFE0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000151515166A48
      27F25B3007FE5B3107FE704923F773706E7C5453525721212122000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000001F1F1F2052514D55000000014848FFFF4848FFFF4848FFFF4848
      FFFF4848FFFF4848FFFF4848FFFF4848FFFF4848FFFF5B5BE8FFFBFBFBFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000003F3E
      3E40867C73AA7B77738D28282829000000000000000108080809000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000004848FFFF4848FDFE4848FFFF4848
      FDFE4848FFFF4848FDFE4848FFFF4848FDFE4848FFFF4B4BF4FEEDEDEEFFFDFD
      FDFEFFFFFFFFFDFDFDFEFFFFFFFFFDFDFDFE0000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
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
      2800000040000000200000000100010000000000000100000000000000000000
      000000000000000000000000FFFFFF00C3FFFFFF0000000080FFE00700000000
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
