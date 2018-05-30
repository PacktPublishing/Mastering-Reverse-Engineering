
SECTION .text
	global main
	main:
		push message
		call printf
		call exit

SECTION .data
	extern exit, printf
	message dd 'Hello World!', 0
