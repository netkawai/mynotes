There are two extensions
1. enableextensions
2. enabledelayedexpansion

For enabledelayedexpansion
To allow to use !var! variable.
```batch
@echo off
setlocal EnableDelayedExpansion
set "var=Original"
set "var=New" & echo Normal: "%var%", Delayed: "!var!"
```
result
Normal: "Original", Delayed: "New"

For enableextensions
I am not sure list of extension.
One thing is to proivde %ERRORLEVEL% as analogy of $? of sh(bash)

IF ERRORLEVEL vs %ERRORLEVEL% vs !ERRORLEVEL!
https://devblogs.microsoft.com/oldnewthing/20080926-00/?p=20743
exit1.py
```python
import sys
sys.exit(1)
```

```batch
setlocal enableextensions
setlocal enabledelayedexpansion	

py exit1.py
IF "!ERRORLEVEL!" NEQ "0" (
   EXIT \B %ERRORLEVEL%
)
```
