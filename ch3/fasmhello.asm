format PE CONSOLE
entry start

include '%include%\win32a.inc' 

section '.data' data readable writeable 
  message db 'Hello World!',0
  msgformat db '%s',0

section '.code' code readable executable 
  start:
    push message
    push msgformat
    call [printf]
    push 0
    call [ExitProcess]

section '.idata' import data readable writeable 
  library kernel32, 'kernel32.dll', \
          msvcrt,   'msvcrt.dll'
  import kernel32, ExitProcess, 'ExitProcess'
  import msvcrt,   printf,      'printf'
