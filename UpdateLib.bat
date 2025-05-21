cd /d %~dp0

xcopy /y .\Engine\Public\*.h	.\EngineSDK\Include\

xcopy /y .\Server\Public\*.h	.\EngineSDK\Server\

xcopy /y .\Engine\Bin\Engine.lib	.\EngineSDK\Lib\

xcopy /y .\Engine\Bin\Engine.dll	.\Client\Bin\
