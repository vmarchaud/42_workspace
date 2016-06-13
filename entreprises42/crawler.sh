
echo "Start : "
read start
echo "Max : "
read max

for (( i=$start; i <= $max; ++i ))
do
	    node index.js "$i"
done
