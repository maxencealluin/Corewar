.name		"Celebration Funebre v0.99pl42"
.comment	"Jour J"

		#ldi  %4, %:code, r15 		#set des octets 5-8
		ldi  %4, %5, r15 		#set des octets 5-8
		ldi  4, %5, r15 		#set des octets 5-8
		ld   %0,r3
		zjmp %3			# 3
		zjmp %200			# 3
		#zjmp %-200			# 3
		st r5,-4			# 6
		st r5,r10			# 6
		ld   %0,r3
code:		live %42			# 5
