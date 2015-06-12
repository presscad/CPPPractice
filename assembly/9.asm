assume cs:codeseg,ds:dataseg,ss:stackseg
dataseg segment
	db 'ibm             '
	db 'dec             '
	db 'dos             '
	db 'vax             '
dataseg ends

stackseg segment
	dw 0,0,0,0,0,0,0,0
stackseg ends

codeseg segment
	
start:	mov ax,stackseg
		mov ss,ax
		mov sp,16
		
		mov ax,dataseg
		mov ds,ax
		mov bx,0
		
		mov cx,4
		
	s0: push cx
		mov si,0
		mov cx,3
		
	s: 	mov al,[bx+si]
		and al,11011111b
		mov [bx+si],al
		inc si
		loop s
		
		add bx,16
		pop cx
		loop s0
		
	mov ax,4c00H
	int 21H
codeseg ends
end start