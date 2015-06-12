assume cs:codeseg
codeseg segment
	
start:	mov ax,0
		jmp short s
		add ax,1
	s: 	inc ax
codeseg ends
end start