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
lit_0 SDWORD 11
lit_1 SDWORD 5
lit_2 SDWORD 10
lit_3 SDWORD 4
lit_4 SDWORD 3
lit_5 SDWORD 5
lit_6 SDWORD -6
lit_7 BYTE 57
lit_8 BYTE 48
lit_9 SBYTE "число", 0
lit_10 SDWORD 0
lit_11 SDWORD 99
lit_12 SDWORD 1
lit_13 BYTE 1
lit_14 BYTE 0
lit_15 SDWORD 0
lit_16 SDWORD 0
lit_17 SDWORD 0
lit_18 SDWORD 256
lit_19 SDWORD 0
lit_20 BYTE 57
lit_21 BYTE 48
lit_22 SDWORD 3
lit_23 BYTE 0
lit_24 BYTE 46
lit_25 SDWORD 1
lit_26 SDWORD 255
lit_27 BYTE 0
lit_28 SDWORD 255
lit_29 SDWORD 0
lit_30 BYTE 0
lit_31 SDWORD 0
lit_32 SDWORD 0
lit_33 BYTE 0
lit_34 SDWORD 0
lit_35 SDWORD 128
lit_36 SDWORD 192
lit_37 SDWORD 224
lit_38 SDWORD 240
lit_39 SDWORD 248
lit_40 SDWORD 252
lit_41 SDWORD 254
lit_42 SDWORD 255
lit_43 BYTE 0
lit_44 SDWORD 0
lit_45 SBYTE 0
lit_46 BYTE 0
lit_47 SDWORD 4
lit_48 BYTE 0
lit_49 BYTE 1
lit_50 SBYTE "hey", 0
lit_51 BYTE 1
lit_52 SBYTE "успешное копирование", 0
lit_53 SBYTE "скопировать строку не удалось", 0
lit_54 SBYTE ", you are welcome!", 0
lit_55 BYTE 100
lit_56 SDWORD 3
lit_57 SDWORD 29
lit_58 SDWORD 0

.data
fi_z SDWORD ?
IsRoot_sum SDWORD ?
CheckMask_octets SDWORD ?
CheckMask_numbers SDWORD ?
CheckMask_numb SDWORD ?
CheckMask_prevNumber SDWORD ?
CheckMask_maskSize BYTE ?
CheckMask_buff SBYTE 255 dup (?)
CheckMask_i BYTE ?
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
push lit_6
pop IsRoot_sum

mov eax, 0
mov al, IsRoot_i
push eax
mov eax, 0
mov al, lit_7
push eax
pop ebx
pop eax
cmp al, bl
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
mov al, lit_8
push eax
pop ebx
pop eax
cmp al, bl
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
push offset lit_9
call print_string
jmp if_end_1

condition_9:
if_end_1:
mov eax, lit_10
mov IsRoot_i, al
cycle_0:
mov ebx, lit_11
cmp eax,ebx
jge cycle_end_0
push IsRoot_sum
push lit_12
pop ebx
pop eax
add eax, ebx
push eax
pop IsRoot_sum

mov eax, 0
mov al, IsRoot_i
push eax
pop eax
inc eax
push eax
pop eax
mov IsRoot_i, al

jmp cycle_0
cycle_end_0:
push IsRoot_sum
call print_number
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
cmp al, bl
jne condition_10
mov eax, 0
mov al, lit_13
push eax
pop eax
ret

jmp if_end_2

condition_10:
if_end_2:
mov eax, 0
mov al, lit_14
push eax
pop eax
ret

IsRoot endp

CheckMask PROC CheckMask_mask : SBYTE
push lit_15
pop CheckMask_octets

push lit_16
pop CheckMask_numbers

push lit_17
pop CheckMask_numb

push lit_18
pop CheckMask_prevNumber

push dword ptr[ CheckMask_mask]
call strlength
push eax
pop eax
mov CheckMask_maskSize, al

mov eax, lit_19
mov CheckMask_i, al
cycle_1:
mov ebx, 0 
mov bl, CheckMask_maskSize
cmp eax,ebx
jge cycle_end_1
mov ebx, 0
 mov bl, CheckMask_i
mov eax, dword ptr [CheckMask_mask]
push [eax + ebx]
mov eax, 0
mov al, lit_20
push eax
pop ebx
pop eax
cmp al, bl
jg condition_11
push 1
jmp condition_end_6
condition_11:
push 0
condition_end_6:
mov ebx, 0
 mov bl, CheckMask_i
mov eax, dword ptr [CheckMask_mask]
push [eax + ebx]
mov eax, 0
mov al, lit_21
push eax
pop ebx
pop eax
cmp al, bl
jl condition_12
push 1
jmp condition_end_7
condition_12:
push 0
condition_end_7:
pop ebx
pop eax
and eax, ebx
push eax
cmp eax, 0
je condition_13
push CheckMask_numbers
push lit_22
pop ebx
pop eax
cmp eax, ebx
jle condition_14
mov eax, 0
mov al, lit_23
push eax
pop eax
ret

jmp if_end_4

condition_14:
if_end_4:
mov ebx, 0
 mov bl, CheckMask_i
mov eax, dword ptr [CheckMask_mask]
push [eax + ebx]
mov ecx, CheckMask_numbers
mov eax, offset CheckMask_buff
pop ebx
mov [eax+ecx], bl
push CheckMask_numbers
pop eax
inc eax
push eax
pop CheckMask_numbers

jmp if_end_3

condition_13:
mov ebx, 0
 mov bl, CheckMask_i
mov eax, dword ptr [CheckMask_mask]
push [eax + ebx]
mov eax, 0
mov al, lit_24
push eax
pop ebx
pop eax
cmp al, bl
jne condition_15
push 1
jmp condition_end_8
condition_15:
push 0
condition_end_8:
mov eax, 0
mov al, CheckMask_i
push eax
mov eax, 0
mov al, CheckMask_maskSize
push eax
push lit_25
pop ebx
pop eax
sub eax, ebx
push eax
pop ebx
pop eax
cmp al, bl
jne condition_16
push 1
jmp condition_end_9
condition_16:
push 0
condition_end_9:
pop ebx
pop eax
or eax, ebx
push eax
cmp eax, 0
je condition_17
push offset CheckMask_buff
call ToNumber
push eax
pop CheckMask_numb

push CheckMask_numb
push lit_26
pop ebx
pop eax
cmp eax, ebx
jle condition_18
mov eax, 0
mov al, lit_27
push eax
pop eax
ret

jmp if_end_5

condition_18:
push CheckMask_prevNumber
push lit_28
pop ebx
pop eax
cmp eax, ebx
jge condition_19
push 1
jmp condition_end_10
condition_19:
push 0
condition_end_10:
push CheckMask_numb
push lit_29
pop ebx
pop eax
cmp eax, ebx
je condition_20
push 1
jmp condition_end_11
condition_20:
push 0
condition_end_11:
pop ebx
pop eax
and eax, ebx
push eax
cmp eax, 0
je condition_21
mov eax, 0
mov al, lit_30
push eax
pop eax
ret

jmp if_end_5

condition_21:
push CheckMask_octets
push lit_31
pop ebx
pop eax
cmp eax, ebx
jne condition_22
push 1
jmp condition_end_12
condition_22:
push 0
condition_end_12:
push CheckMask_numb
push lit_32
pop ebx
pop eax
cmp eax, ebx
jne condition_23
push 1
jmp condition_end_13
condition_23:
push 0
condition_end_13:
pop ebx
pop eax
and eax, ebx
push eax
cmp eax, 0
je condition_24
mov eax, 0
mov al, lit_33
push eax
pop eax
ret

jmp if_end_5

condition_24:
push CheckMask_numb
push lit_34
pop ebx
pop eax
cmp eax, ebx
je condition_25
push 1
jmp condition_end_14
condition_25:
push 0
condition_end_14:
push CheckMask_numb
push lit_35
pop ebx
pop eax
cmp eax, ebx
je condition_26
push 1
jmp condition_end_15
condition_26:
push 0
condition_end_15:
pop ebx
pop eax
and eax, ebx
push eax
push CheckMask_numb
push lit_36
pop ebx
pop eax
cmp eax, ebx
je condition_27
push 1
jmp condition_end_16
condition_27:
push 0
condition_end_16:
pop ebx
pop eax
and eax, ebx
push eax
push CheckMask_numb
push lit_37
pop ebx
pop eax
cmp eax, ebx
je condition_28
push 1
jmp condition_end_17
condition_28:
push 0
condition_end_17:
pop ebx
pop eax
and eax, ebx
push eax
push CheckMask_numb
push lit_38
pop ebx
pop eax
cmp eax, ebx
je condition_29
push 1
jmp condition_end_18
condition_29:
push 0
condition_end_18:
pop ebx
pop eax
and eax, ebx
push eax
push CheckMask_numb
push lit_39
pop ebx
pop eax
cmp eax, ebx
je condition_30
push 1
jmp condition_end_19
condition_30:
push 0
condition_end_19:
pop ebx
pop eax
and eax, ebx
push eax
push CheckMask_numb
push lit_40
pop ebx
pop eax
cmp eax, ebx
je condition_31
push 1
jmp condition_end_20
condition_31:
push 0
condition_end_20:
pop ebx
pop eax
and eax, ebx
push eax
push CheckMask_numb
push lit_41
pop ebx
pop eax
cmp eax, ebx
je condition_32
push 1
jmp condition_end_21
condition_32:
push 0
condition_end_21:
pop ebx
pop eax
and eax, ebx
push eax
push CheckMask_numb
push lit_42
pop ebx
pop eax
cmp eax, ebx
je condition_33
push 1
jmp condition_end_22
condition_33:
push 0
condition_end_22:
pop ebx
pop eax
and eax, ebx
push eax
cmp eax, 0
je condition_34
mov eax, 0
mov al, lit_43
push eax
pop eax
ret

jmp if_end_5

if_end_5:
push CheckMask_numb
pop CheckMask_prevNumber

push lit_44
pop CheckMask_numbers

push CheckMask_octets
pop eax
inc eax
push eax
pop CheckMask_octets

push offset CheckMask_buff
push offset lit_45
call strcopy
jmp if_end_3

condition_34:
mov eax, 0
mov al, lit_46
push eax
pop eax
ret

jmp if_end_3

if_end_3:
mov eax, 0
mov al, CheckMask_i
push eax
pop eax
inc eax
push eax
pop eax
mov CheckMask_i, al

jmp cycle_1
cycle_end_1:
push CheckMask_octets
push lit_47
pop ebx
pop eax
cmp eax, ebx
je condition_35
mov eax, 0
mov al, lit_48
push eax
pop eax
ret

jmp if_end_6

condition_35:
if_end_6:
mov eax, 0
mov al, lit_49
push eax
pop eax
ret

CheckMask endp

main PROC C
push offset main_x
call get_number
push main_x
pop eax
inc eax
push eax
pop main_x

push offset main_sa
push offset lit_50
call strcopy
push offset main_sb
push offset main_sa
call strcopy
push eax
mov eax, 0
mov al, lit_51
push eax
pop ebx
pop eax
cmp al, bl
jne condition_36
push offset lit_52
call print_string
jmp if_end_7

condition_36:
push offset lit_53
call print_string
jmp if_end_7

if_end_7:
push offset main_sa
push offset lit_54
call strconcat
push eax
pop eax
mov main_res, al

mov eax, 0
mov al, lit_55
push eax
pop eax
mov main_ua, al

mov ebx, lit_56
mov eax, dword ptr [main_sa]
push [eax + ebx]
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
push lit_57
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
push lit_58
jmp main_end
main_end:
call ExitProcess
main ENDP

end
