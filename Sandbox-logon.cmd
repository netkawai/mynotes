REM iRing Aegis folder

REM Install virtual printer
rundll32 printui.dll,PrintUIEntry /if  /f %windir%\inf\ntprint.inf /r "lpt1:" /m "Microsoft MS-XPS Class Driver 2"


XCOPY /E /I "C:\Users\WDAGUtilityAccount\Desktop\iBlast\Home\iRing Aegis" "C:\Users\WDAGUtilityAccount\Documents\iRing Aegis"


exit