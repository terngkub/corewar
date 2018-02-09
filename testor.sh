
d=~/Documents/42/corewar/champs/*.s

for files in $d;
do
	echo "==> $files <=="
	./asm $files
done
