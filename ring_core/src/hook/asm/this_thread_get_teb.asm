.code
this_thread_get_teb proc
	mov rax, qword ptr gs:[58h]
	ret
this_thread_get_teb endp
end