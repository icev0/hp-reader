#define MyAppName "HP Reader"
#define MyAppVersion "1.0.0"
#define MyAppPublisher "ICE"
#define MyAppURL "icev0.github.com"
#define MyAppExeName "hp reader.exe"
#define MyAppAssocName "HP Reader"
#define MyAppAssocExt ".hp"
#define MyAppAssocKey StringChange(MyAppAssocName, " ", "") + MyAppAssocExt

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{DF166C2C-B4CB-49CC-8561-F546C54C2EF0}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
AppCopyright=Copyright (C) 2023 ICE, Inc.
DefaultDirName={autopf}\{#MyAppName}
ChangesAssociations=yes
DisableProgramGroupPage=yes
UninstallDisplayIcon={app}\{#MyAppExeName}
LicenseFile=D:\C & C++ Projects\hp reader\hp reader\LICENSE
; Uncomment the following line to run in non administrative install mode (install for current user only.)
;PrivilegesRequired=lowest
OutputBaseFilename=HP Reader Setup
SetupIconFile=D:\C & C++ Projects\hp reader\hp reader\icon.ico
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Code]
function InitializeUninstall(): Boolean;
begin
  Result := MsgBox('HP Reader developer:' #13#13 'Uninstall is initializing. Do you really want to start Uninstall?', mbConfirmation, MB_YESNO) = idYes;
  if Result = False then
    MsgBox('HP Reader developer:' #13#13 'Ok, bye bye.', mbInformation, MB_OK);
end;

procedure DeinitializeUninstall();
begin
  MsgBox('HP Reader developer:' #13#13 'Bye bye!', mbInformation, MB_OK);
end;

procedure CurUninstallStepChanged(CurUninstallStep: TUninstallStep);
begin
  case CurUninstallStep of
    usUninstall:
      begin
        MsgBox('HP Reader developer:' #13#13 'Uninstall is about to start.', mbInformation, MB_OK)
      end;
    usPostUninstall:
      begin
        MsgBox('HP Reader developer:' #13#13 'Uninstall just finished.', mbInformation, MB_OK);
      end;
  end;
end;

[Languages]
Name: "en"; MessagesFile: "compiler:Default.isl"

[Messages]
en.BeveledLabel=English

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1\api-ms-win-crt-heap-l1-1-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1\api-ms-win-crt-locale-l1-1-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1\api-ms-win-crt-math-l1-1-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1\api-ms-win-crt-runtime-l1-1-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1\api-ms-win-crt-stdio-l1-1-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1\api-ms-win-crt-string-l1-1-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1\doc.pdf"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1\hp reader.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1\vcruntime140.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1\example\*"; DestDir: "{app}\example"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Registry]        
Root: HKCR; Subkey: "{#MyAppAssocExt}"; ValueType: string; ValueName: ""; ValueData: "{#MyAppName}"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: "{#MyAppName}"; ValueType: string; ValueName: ""; ValueData: "{#MyAppName}"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: "{#MyAppName}\DefaultIcon"; ValueType: string; ValueName: ""; ValueData: "{app}\{#MyAppExeName},0"; Flags: uninsdeletekeyifempty
Root: HKCR; Subkey: "{#MyAppName}\shell\open\command"; ValueType: string; ValueName: ""; ValueData: """{app}\{#MyAppExeName}"" ""%1"""; Flags: uninsdeletekeyifempty

[Icons]
Name: "{autoprograms}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

