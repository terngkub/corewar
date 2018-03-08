first=champs
second=vm_champs
files=*.cor

for file in $first/$files;
do
	if [ -f $second/${file:7} ]
	then
		echo "-----$file-----"
		diff $file $second/${file:7}
		echo ""
		echo ""
	fi
done
