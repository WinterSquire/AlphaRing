.data
    p_scriptEntry qword 0
    p_ppOriginal qword 0

.code

asm_mcc_hook_unload_init proc
    mov p_scriptEntry, rcx
    mov p_ppOriginal, rdx
    ret
asm_mcc_hook_unload_init endp

asm_mcc_hook_unload_entry proc
    lea rcx, [rbx]

    mov rax, p_ppOriginal
    mov rax, [rax]
    push rax
    jmp p_scriptEntry
asm_mcc_hook_unload_entry endp
end
