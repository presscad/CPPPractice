@echo off
@rem if exist /fq.bat type /fq.bat
@rem if not exist /fq.bat echo /fq.bat not exist
@rem if "%1" == "A" echo aaa
@rem if "%2" == "B" echo bbb
@rem if "%3" == "C" echo ccc
@rem xcopy C:/fq.bat d:/
@rem if errorlevel 1 echo copy failed!
for %%d in (*.bat *.txt) do type %%d
