.data
    p_scriptEntry qword 0
    p_ppOriginal qword 0

.code

asm_mcc_hook_load_init proc
    mov p_scriptEntry, rcx
    mov p_ppOriginal, rdx
    ret
asm_mcc_hook_load_init endp

asm_mcc_hook_load_entry proc
    lea rcx, [r14]

    mov rax, p_ppOriginal
    mov rax, [rax]
    push rax
    jmp p_scriptEntry
asm_mcc_hook_load_entry endp
end
