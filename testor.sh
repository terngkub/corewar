
d=tests/*.s

for files in $d;
do
	echo "==> $files <=="
	./asm $files
done
