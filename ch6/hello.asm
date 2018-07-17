format ELF executable 3
entry start

include 'import32.inc'

interpreter '/lib/ld-linux.so.2'   
needed 'libc.so.6'
import printf, exit

segment readable executable

start:
    push msg
    call [printf]
    call [exit]

segment readable writeable
    msg db "Hello asm world!", 0dh, 0ah
