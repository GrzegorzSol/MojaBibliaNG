object DisplayPreviewWindow: TDisplayPreviewWindow
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'DisplayPreviewWindow'
  ClientHeight = 700
  ClientWidth = 640
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Font.Quality = fqClearType
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  TextHeight = 15
  object WebBrowserPreview: TWebBrowser
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 634
    Height = 694
    Align = alClient
    TabOrder = 0
    ExplicitLeft = 384
    ExplicitTop = 384
    ExplicitWidth = 300
    ExplicitHeight = 150
    ControlData = {
      4C00000087410000BA4700000000000000000000000000000000000000000000
      000000004C000000000000000000000001000000E0D057007335CF11AE690800
      2B2E126209000000000000004C0000000114020000000000C000000000000046
      8000000000000000000000000000000000000000000000000000000000000000
      00000000000000000100000000000000000000000000000000000000}
  end
end
