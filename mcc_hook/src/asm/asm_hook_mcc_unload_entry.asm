.data
    p_scriptEntry qword 0
    p_ppOriginal qword 0

.code

asm_hook_mcc_unload_init proc
    mov p_scriptEntry, rcx
    mov p_ppOriginal, rdx
    ret
asm_hook_mcc_unload_init endp

asm_hook_mcc_unload_entry proc
    lea rcx, [rbx]

    mov rax, p_ppOriginal
    mov rax, [rax]
    push rax
    jmp p_scriptEntry
asm_hook_mcc_unload_entry endp
end
