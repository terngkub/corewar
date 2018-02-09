
d=~/test_corewar/champs/*.s

for files in $d;
do
	echo "==> $files <=="
	./asm $files
done
