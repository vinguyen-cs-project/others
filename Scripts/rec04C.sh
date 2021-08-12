#! /bin/bash

let x=$RANDOM%10+1
while :
do
	read -p "Enter a number between 1 and 10: " y
	if [ $y -eq $x ]
	then
		echo "Congratulations, the number is $x."
		break
	else
		echo "Sorry, you are not correct. Try again!"
	fi
done

