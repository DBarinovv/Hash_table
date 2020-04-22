.686
.MODEL FLAT, C
.CODE

Hash_Xor proc arg1:ptr byte, len:WORD
        mov ax, 0
        movzx bx, byte ptr [arg1]
        mov cx, len

again:
        test cx, cx
        je return
        xor ax, bx
        inc bx
        rol ax, 1
        dec cx
        jmp again
return:
        ret
Hash_Xor endp

END
