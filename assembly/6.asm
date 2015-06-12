assume cs:codesg
codesg segment
	dw 0123h,0456h,0789h,0abch,0defh,0fedh,0cbah,0987h
		
	mov ax,4c00H
	int 21H
codesg ends
end