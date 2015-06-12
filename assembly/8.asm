assume cs:codeseg,ds:dataseg
dataseg segment
	db 'BaSic'
	db 'iNfOrMaTiOn'
dataseg ends
codeseg segment
	start:
		mov ax,dataseg
		mov ds,ax
		mov dx,0
		
		mov cx,5
	s:  mov al,[dx]
		and al,11011111
		mov [bx],ax
		inc bx
		loop s
		
		mov bx,5
		mov cx,11
	
	s0: mov al,[dx]
		or al,00100000
		mov [bx],ax
		inc bx
		loop s0
		
	mov ax,4c00H
	int 21H
codeseg ends
end start