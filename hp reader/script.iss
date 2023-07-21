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

[Languages]
Name: "en"; MessagesFile: "compiler:Default.isl"

[Messages]
en.BeveledLabel=English

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1.0.0\{#MyAppExeName}"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1.0.0\api-ms-win-crt-heap-l1-1-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1.0.0\api-ms-win-crt-locale-l1-1-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1.0.0\api-ms-win-crt-math-l1-1-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1.0.0\api-ms-win-crt-runtime-l1-1-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1.0.0\api-ms-win-crt-stdio-l1-1-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1.0.0\api-ms-win-crt-string-l1-1-0.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1.0.0\doc.pdf"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1.0.0\hp reader.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1.0.0\vcruntime140.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1.0.0\LICENSE"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\C & C++ Projects\hp reader\hp reader\hp reader v1.0.0\examples\*"; DestDir: "{app}\examples"; Flags: ignoreversion recursesubdirs createallsubdirs
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

