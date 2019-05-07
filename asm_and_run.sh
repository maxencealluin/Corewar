VAR=$( diff log ex/valid_all.s )
# printf "%d\n" $VAR
# if [ $VAR != 0 ]
# then
	cd ex/
	./asm valid_all.s
	cd ../
	sleep 3
	cat ex/valid_all.s > log

TMP="ex/valid_all.cor -g"
./corewar $TMP
