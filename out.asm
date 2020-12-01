.586P
.model flat, stdcall
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
lit_2 SDWORD 10
lit_3 SDWORD 4
lit_4 SDWORD 3
lit_5 SDWORD 5
lit_6 BYTE 57
lit_7 BYTE 48
lit_8 SBYTE "число", 0
lit_9 BYTE 1
lit_10 BYTE 0
lit_11 SBYTE "hey", 0
lit_12 BYTE 1
lit_13 SBYTE "успешное копирование", 0
lit_14 SBYTE "скопировать строку не удалось", 0
lit_15 SBYTE ", you are welcome!", 0
lit_16 BYTE 100
lit_17 SDWORD 3
lit_18 SDWORD 29
lit_19 SDWORD 0

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
push 1
jmp condition_end_0
condition_1:
push 0
condition_end_0:
push fi_x
push lit_2
pop ebx
pop eax
cmp eax, ebx
jle condition_2
push 1
jmp condition_end_1
condition_2:
push 0
condition_end_1:
pop ebx
pop eax
or eax, ebx
push eax
cmp eax, 0
je condition_3
push fi_x
push fi_y
pop ebx
pop eax
or eax, ebx
push eax
pop fi_z

jmp if_end_0

condition_3:
push fi_x
push fi_y
pop ebx
pop eax
cmp eax, ebx
jge condition_4
push 1
jmp condition_end_2
condition_4:
push 0
condition_end_2:
push fi_x
push lit_3
pop ebx
pop eax
sub eax, ebx
push eax
push lit_4
pop ebx
pop eax
cmp eax, ebx
je condition_5
push 1
jmp condition_end_3
condition_5:
push 0
condition_end_3:
pop ebx
pop eax
and eax, ebx
push eax
cmp eax, 0
je condition_6
push fi_x
push fi_y
pop ebx
pop eax
and eax, ebx
push eax
push lit_5
pop ebx
pop eax
imul eax, ebx
push eax
pop fi_z

jmp if_end_0

condition_6:
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
mov al, IsRoot_i
push eax
mov eax, 0
mov al, lit_6
push eax
pop ebx
pop eax
cmp eax, ebx
jg condition_7
push 1
jmp condition_end_4
condition_7:
push 0
condition_end_4:
mov eax, 0
mov al, IsRoot_i
push eax
mov eax, 0
mov al, lit_7
push eax
pop ebx
pop eax
cmp eax, ebx
jl condition_8
push 1
jmp condition_end_5
condition_8:
push 0
condition_end_5:
pop ebx
pop eax
and eax, ebx
push eax
cmp eax, 0
je condition_9
push offset lit_8
call print_string
jmp if_end_1

condition_9:
if_end_1:
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
jne condition_10
mov eax, 0
mov al, lit_9
push eax
pop eax
ret

jmp if_end_2

condition_10:
if_end_2:
mov eax, 0
mov al, lit_10
push eax
pop eax
ret

IsRoot endp

main PROC C
push offset main_x
call get_number
push main_x
pop eax
inc eax
push eax
pop main_x

push offset main_sa
push offset lit_11
call strcopy
push offset main_sb
push offset main_sa
call strcopy
push eax
mov eax, 0
mov al, lit_12
push eax
pop ebx
pop eax
cmp eax, ebx
jne condition_11
push offset lit_13
call print_string
jmp if_end_3

condition_11:
push offset lit_14
call print_string
jmp if_end_3

if_end_3:
push offset main_sa
push offset lit_15
call strconcat
push eax
pop eax
mov main_res, al

mov eax, 0
mov al, lit_16
push eax
pop eax
mov main_ua, al

mov ebx, lit_17
mov eax, 0
mov al, main_sa[ebx]
push eax
pop eax
mov main_ub, al

mov eax, 0
mov al, main_ub
push eax
call print_ubyte
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
push lit_18
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
push lit_19
call ExitProcess
main ENDP

end
