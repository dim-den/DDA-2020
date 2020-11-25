.586P
.model flat, stdcall
includelib libucrt.lib
includelib user32.lib
includelib kernel32.lib

ExitProcess PROTO : DWORD

extrn print_number : proc
extrn print_string : proc
extrn print_bool : proc
extrn print_ubyte : proc
extrn get_string : proc
extrn get_bool : proc
extrn get_number : proc
extrn strcopy : proc
extrn strconcat : proc

.stack 4096

.const
lit_0 SDWORD 11
lit_1 SDWORD 5
lit_2 SDWORD 5
lit_3 BYTE 1
lit_4 BYTE 0
lit_5 SBYTE "hey there", 0
lit_6 BYTE 0
lit_7 SBYTE "успешное копирование", 0
lit_8 SBYTE "скопировать строку не удалось", 0
lit_9 SBYTE " you are welcome", 0
lit_10 SDWORD 6
lit_11 SDWORD 29
lit_12 SDWORD 0

.data
fi_z SDWORD ?
main_x SDWORD ?
main_sa SBYTE 255 dup (?)
main_sb SBYTE 255 dup (?)
main_res BYTE ?
main_ua BYTE ?
main_ub BYTE ?
main_b BYTE ?
main_z SDWORD ?
main_test SDWORD ?

.code
fi PROC fi_y : SDWORD, fi_x : SDWORD
push fi_x
push lit_0
pop ebx
pop eax
add eax, ebx
push eax
push fi_y
pop ebx
pop eax
cmp eax, ebx
jl condition_0
push fi_x
push fi_x
push fi_y
pop ebx
pop eax
add eax, ebx
push eax
pop ebx
pop eax
imul eax, ebx
push eax
pop fi_z

jmp if_end_0

condition_0:
push fi_x
push lit_1
pop ebx
pop eax
cmp eax, ebx
jne condition_1
push fi_x
push fi_y
pop ebx
pop eax
or eax, ebx
push eax
pop fi_z

jmp if_end_0

condition_1:
push fi_x
push fi_y
pop ebx
pop eax
cmp eax, ebx
jge condition_2
push fi_x
push fi_y
pop ebx
pop eax
and eax, ebx
push eax
push lit_2
pop ebx
pop eax
imul eax, ebx
push eax
pop fi_z

jmp if_end_0

condition_2:
push fi_y
pop eax
not eax
push eax
push fi_x
pop ebx
pop eax
add eax, ebx
push eax
pop fi_z

jmp if_end_0

if_end_0:
push fi_z
pop eax
ret

fi endp

IsRoot PROC IsRoot_j : BYTE, IsRoot_i : BYTE
mov eax, 0
mov al, IsRoot_j
push eax
mov eax, 0
mov al, IsRoot_i
push eax
mov eax, 0
mov al, IsRoot_i
push eax
pop ebx
pop eax
imul eax, ebx
push eax
pop ebx
pop eax
cmp eax, ebx
jne condition_3
mov eax, 0
mov al, lit_3
push eax
pop eax
ret

jmp if_end_1

condition_3:
if_end_1:
mov eax, 0
mov al, lit_4
push eax
pop eax
ret

IsRoot endp

main PROC
push offset global__IsRoot
call get_bool
push offset main_sa
push offset lit_5
call strcopy
push offset main_sb
push offset main_sa
call strcopy
push eax
mov eax, 0
mov al, lit_6
push eax
pop ebx
pop eax
cmp eax, ebx
jne condition_4
push offset lit_7
call print_string
jmp if_end_2

condition_4:
push offset lit_8
call print_string
jmp if_end_2

if_end_2:
push offset main_sa
push offset lit_9
call strconcat
push eax
pop eax
mov main_res, al

push lit_10
pop eax
mov main_ua, al

mov eax, 0
mov al, main_ua
push eax
pop eax
mov main_ub, al

mov eax, 0
mov al, main_ua
push eax
mov eax, 0
mov al, main_ub
push eax
call IsRoot
push eax
pop eax
mov main_b, al

push main_x
push lit_11
call fi
push eax
pop main_z

push offset main_sa
call print_string
push main_z
call print_number
mov eax, 0
mov al, main_ua
push eax
pop main_test

push main_test
call print_number
push lit_12
call ExitProcess
main ENDP

end main