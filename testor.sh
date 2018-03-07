dir=tests
#dir=~/ASM_Corewar_tests

rm $dir/*.cor
for file in $dir/*.s;
do
	echo "==> $file <=="
	./asm $file
	echo ""
	echo ""
done
