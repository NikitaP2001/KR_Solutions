@echo off

set FILENAME=count
set FILES=main.c tree.c

set CFLAGS=-O3 -s -mconsole
set LKFLAGS=-Wl,--gc-sections

@echo on
gcc %CFLAGS% %LKFLAGS% %FILES% -o %FILENAME%
@echo off
	if errorlevel 1 goto terminate
@echo on
	dir
	:terminate
	pause
© 2021 GitHub, Inc.