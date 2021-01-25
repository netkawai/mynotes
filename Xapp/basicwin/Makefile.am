bin_PROGRAMS = basicwin jpwin	#プログラム名 
basicwin_SOURCES = basicwin.c   #そのプログラムのソース
basicwin_DEPENDENCIES = basicwin.c basicwin_icon.xbm #依存
basicwin_LDADD = -lX11 #リンクするライブラリ
basicwin_LDFLAGS = @X_LIBS@ #リンクオプション

jpwin_SOURCES = ujiswin.c ujiscode.c
jpwin_DEPENDENCIES = ujiswin.c ujiscode.c basicwin_icon.xbm jpcode.h
jpwin_LDADD = -lX11
jpwin_LDFLAGS = @X_LIBS@

INCLUDES = @X_CFLAGS@ #インクルードファイルディレクトリの指定