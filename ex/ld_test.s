.name		"Celebration Funebre v0.99pl42"
.comment	"Jour J"

		ld  10, r4 		#set des octets 5-8
		ld   %112,r3
		ld   %9,r7
		lld   %9,r7
		#ld   %0,r3
		st r3, r5
		st r3, 568
		st r5, 600
		#ldi 12, %24, r7
	#	ldi r3, %24, r7
	#	ldi r3, r5, r6
	#	ldi r3, %24, r7
		st r7, 800
		sti r7, %20, %20
		sti r7, 1, %20
