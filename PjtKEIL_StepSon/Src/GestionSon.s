	PRESERVE8
	THUMB   
		
	EXPORT CallbackSon
; ====================== zone de réservation de données,  ======================================
;Section RAM (read only) :
	area    mesdata,data,readonly


;Section RAM (read write):
	area    maram,data,readwrite
		
SortieSon DCW 0
Index DCW 0
	export SortieSon
	export Index
	import Son
	import LongueurSon 
; ===============================================================================================
	


		
;Section ROM code (read only) :		
	area    moncode,code,readonly
; écrire le code ici		

CallbackSon proc
	push {r4-r11}
	ldr r1, =Son				;stockage adresse tableau des valeurs
	ldr r2, =Index
	ldr r5, [r2]
	ldr r0, =LongueurSon
	ldr r0, [r0]
	cmp r5, r0
	beq sortie
	ldrsh r3, [r1, r5, lsl#1]
	add r3, #32768
	mov r0, #91
	udiv r3, r0
	ldr r0, =SortieSon
	strh r3, [r0]
	add r5, #1
	str r5, [r2]
sortie
	pop {r4-r11}			;remise en etat des registres
	bx lr
	endp


		
	END	