@echo off

set FILENAME=pages
set FILES=*.c

set CFLAGS=-O0 -s -mconsole
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