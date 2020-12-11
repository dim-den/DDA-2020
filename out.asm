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
extrn get_ubyte : proc
extrn get_number : proc
extrn strcopy : proc
extrn strconcat : proc
extrn strlength : proc
extrn ToNumber : proc

.stack 4096

.const
lit_0 SDWORD 0
lit_1 SDWORD 0
lit_2 SDWORD 0
lit_3 BYTE 57
lit_4 BYTE 48
lit_5 SDWORD 3
lit_6 BYTE 0
lit_7 BYTE 46
lit_8 SDWORD 255
lit_9 SDWORD 0
lit_10 BYTE 0
lit_11 SDWORD 0
lit_12 SBYTE 0
lit_13 BYTE 0
lit_14 BYTE 0
lit_15 BYTE 0
lit_16 SDWORD 255
lit_17 SDWORD 3
lit_18 SDWORD 0
lit_19 BYTE 0
lit_20 BYTE 1
lit_21 SBYTE "¬ведите ip-адрес: ", 0
lit_22 BYTE 0
lit_23 SBYTE "¬веден не правильный ip-адрес.", 0
lit_24 SDWORD -1
lit_25 SBYTE "¬ведены верные данные сети!", 0
lit_26 SBYTE "¬ведите маску сети:", 0
lit_27 SBYTE "/", 0
lit_28 BYTE 1
lit_29 SDWORD 13
lit_30 SDWORD 3
lit_31 SDWORD 0

.data
CheckAddress_octets SDWORD ?
CheckAddress_numbers SDWORD ?
CheckAddress_length BYTE ?
CheckAddress_buff SBYTE 255 dup (?)
CheckAddress_i BYTE ?
main_ip SBYTE 255 dup (?)
main_mask SBYTE 255 dup (?)
main_res BYTE ?
main_value SDWORD ?

.code
CheckAddress PROC CheckAddress_address : SBYTE
push lit_0
pop CheckAddress_octets

push lit_1
pop CheckAddress_numbers

push dword ptr[ CheckAddress_address]
call strlength
pop ebx
push eax
pop eax
mov CheckAddress_length, al

mov eax, lit_2
mov CheckAddress_i, al
cycle_0:
mov ebx, 0 
mov bl, CheckAddress_length
cmp eax,ebx
jge cycle_end_0
mov ebx, 0
 mov bl, CheckAddress_i
mov eax, dword ptr [CheckAddress_address]
push [eax + ebx]
mov eax, 0
mov al, lit_3
push eax
pop ebx
pop eax
cmp al, bl
jg condition_0
push 1
jmp condition_end_0
condition_0:
push 0
condition_end_0:
mov ebx, 0
 mov bl, CheckAddress_i
mov eax, dword ptr [CheckAddress_address]
push [eax + ebx]
mov eax, 0
mov al, lit_4
push eax
pop ebx
pop eax
cmp al, bl
jl condition_1
push 1
jmp condition_end_1
condition_1:
push 0
condition_end_1:
pop ebx
pop eax
and eax, ebx
push eax
cmp eax, 0
je condition_2
push CheckAddress_numbers
push lit_5
pop ebx
pop eax
cmp eax, ebx
jle condition_3
mov eax, 0
mov al, lit_6
push eax
pop eax
ret

jmp if_end_1

condition_3:
if_end_1:
mov ebx, 0
 mov bl, CheckAddress_i
mov eax, dword ptr [CheckAddress_address]
push [eax + ebx]
mov ecx, CheckAddress_numbers
mov eax, offset CheckAddress_buff
pop ebx
mov [eax+ecx], bl
push CheckAddress_numbers
pop eax
inc eax
push eax
pop CheckAddress_numbers

jmp if_end_0

condition_2:
mov ebx, 0
 mov bl, CheckAddress_i
mov eax, dword ptr [CheckAddress_address]
push [eax + ebx]
mov eax, 0
mov al, lit_7
push eax
pop ebx
pop eax
cmp al, bl
jne condition_4
push offset CheckAddress_buff
call ToNumber
pop ebx
push eax
push lit_8
pop ebx
pop eax
cmp eax, ebx
jle condition_5
push 1
jmp condition_end_2
condition_5:
push 0
condition_end_2:
push CheckAddress_numbers
push lit_9
pop ebx
pop eax
cmp eax, ebx
jne condition_6
push 1
jmp condition_end_3
condition_6:
push 0
condition_end_3:
pop ebx
pop eax
or eax, ebx
push eax
cmp eax, 0
je condition_7
mov eax, 0
mov al, lit_10
push eax
pop eax
ret

jmp if_end_2

condition_7:
if_end_2:
push lit_11
pop CheckAddress_numbers

push CheckAddress_octets
pop eax
inc eax
push eax
pop CheckAddress_octets

push offset CheckAddress_buff
push offset lit_12
call strcopy
pop ebx
pop ebx
push eax
mov eax, 0
mov al, lit_13
push eax
pop ebx
pop eax
cmp al, bl
jne condition_8
mov eax, 0
mov al, lit_14
push eax
pop eax
ret

jmp if_end_3

condition_8:
if_end_3:
jmp if_end_0

condition_4:
mov eax, 0
mov al, lit_15
push eax
pop eax
ret

jmp if_end_0

if_end_0:
mov eax, 0
mov al, CheckAddress_i
push eax
pop eax
inc eax
push eax
pop eax
mov CheckAddress_i, al

jmp cycle_0
cycle_end_0:
push offset CheckAddress_buff
call ToNumber
pop ebx
push eax
push lit_16
pop ebx
pop eax
cmp eax, ebx
jle condition_9
push 1
jmp condition_end_4
condition_9:
push 0
condition_end_4:
push CheckAddress_octets
push lit_17
pop ebx
pop eax
cmp eax, ebx
je condition_10
push 1
jmp condition_end_5
condition_10:
push 0
condition_end_5:
pop ebx
pop eax
or eax, ebx
push eax
push CheckAddress_numbers
push lit_18
pop ebx
pop eax
cmp eax, ebx
jne condition_11
push 1
jmp condition_end_6
condition_11:
push 0
condition_end_6:
pop ebx
pop eax
or eax, ebx
push eax
cmp eax, 0
je condition_12
mov eax, 0
mov al, lit_19
push eax
pop eax
ret

jmp if_end_4

condition_12:
if_end_4:
mov eax, 0
mov al, lit_20
push eax
pop eax
ret

CheckAddress endp

main PROC C
push offset lit_21
call print_string
push offset main_ip
call get_string
push offset main_ip
call CheckAddress
pop ebx
push eax
mov eax, 0
mov al, lit_22
push eax
pop ebx
pop eax
cmp al, bl
jne condition_13
push offset lit_23
call print_string
push lit_24
jmp main_end
jmp if_end_5

condition_13:
push offset lit_25
call print_string
jmp if_end_5

if_end_5:
push offset lit_26
call print_string
push offset main_mask
call get_string
push offset main_ip
push offset lit_27
call strconcat
pop ebx
pop ebx
push eax
push offset main_ip
push offset main_mask
call strconcat
pop ebx
pop ebx
push eax
pop ebx
pop eax
and eax, ebx
push eax
pop eax
mov main_res, al

mov eax, 0
mov al, main_res
push eax
mov eax, 0
mov al, lit_28
push eax
pop ebx
pop eax
cmp al, bl
jne condition_14
push offset main_ip
call print_string
jmp if_end_6

condition_14:
if_end_6:
push lit_29
pop main_value

push main_value
pop eax
not eax
push eax
push offset main_mask
call ToNumber
pop ebx
push eax
pop ebx
pop eax
and eax, ebx
push eax
push lit_30
pop ebx
pop eax
or eax, ebx
push eax
call print_number
push lit_31
jmp main_end
main_end:
call ExitProcess
main ENDP

end
