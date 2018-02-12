
d=champs/*.s

for files in $d;
do
	echo "==> $files <=="
	./asm $files
	echo ""
	echo ""
done
