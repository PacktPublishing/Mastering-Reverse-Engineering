format PE CONSOLE                            ; this program is a Win32 PE file and in console mode
entry start                                  ; the start of this program is located at label "start"

include '%include%\win32a.inc'               ; functions from win32a.inc will be used

section '.data' data readable writeable      ; .data section has read and write permissions
  message db 0dh, 0ah, 'Hello World!',0                ; define contents of constant variable message
  message2 db 0dh, 0ah, 'World Hello!',0
  msgformat db '%s',0                        ; define contents of constant variable msgformat
  formatin db '%d', 0
  integer2 dw 0, 0


section '.code' code readable executable     ; .code section has read and execute permission
  start:                                     ; this is the start label, labels are denoted with colon (:)
    push integer2
    push formatin
    call [scanf]
    push dword [integer2]
    push formatin
    call [printf]
    cmp dword [integer2], 16h
    jb bellow
    push message
    jmp play
bellow:
    push message2
play:
    push msgformat
    call [printf]
    push 0                                   ; this is the parameter for ExitProcess API
    call [ExitProcess]                       ; execute ExitProcess(0)

section '.idata' import data readable writeable     ; import section has read and write permissions
  library kernel32, 'kernel32.dll', \               ; functions came from kernel32 and msvcrt dlls
          msvcrt, 'msvcrt.dll'
  import kernel32, ExitProcess, 'ExitProcess'       ; program will use ExitProcess and printf functions
  import msvcrt, printf, 'printf', \
                 scanf, 'scanf'