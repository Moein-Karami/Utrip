make 

for i in {1..11}
do
	./utrip.out ./assets/hotels.csv ./assets/ratings.csv < "$i.in" > tst
	diff -w tst "$i.out" > tmp
	if [ -s tmp ]
	then 
		echo "WRONG ON $i"
	else
		echo "ACCEPT ON $i"
	fi
done