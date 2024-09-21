@SET BDS=D:\Develop\Embarcadero\Studio\23.0
@SET BDSINCLUDE=D:\Develop\Embarcadero\Studio\23.0\include
@SET BDSCOMMONDIR=C:\Users\Public\Documents\Embarcadero\Studio\23.0
@SET FrameworkDir=C:\Windows\Microsoft.NET\Framework\v4.0.30319
@SET FrameworkVersion=v4.5
@SET FrameworkSDKDir=
@SET PATH=%FrameworkDir%;%FrameworkSDKDir%;D:\Develop\Embarcadero\Studio\23.0\bin;D:\Develop\Embarcadero\Studio\23.0\bin64;D:\Develop\Embarcadero\Studio\23.0\cmake;%PATH%
@SET LANGDIR=EN
@SET PLATFORM=
@SET PlatformSDK=

::echo "Budowanie dla platformy x32"
msbuild "Moja Biblia NG.cbproj" /t:build /p:platform=Win32
pause
::echo "Budowanie dla platformy x64"
msbuild "Moja Biblia NG.cbproj" /t:build /p:platform=Win64
pause