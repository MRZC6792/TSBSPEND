#!/bin/bash
#filename bsp3

bsp3() {
	echo $1
	$1
	if [ $? -eq 0 ]
	then
		echo "OK to "$1
	else
		echo "Fail to "$1
		i=1
		while(( $i<=5 ))
		do
			echo "---------------------"
			echo $i" try: "$1
			$1
			if [ $? -eq 0 ]
			then
				echo "OK to "$1
				break
			else
				echo "Fail to "$1
				i=`expr $i + 1`
			fi
		done
		if [ $i == 6 ]
		then
			echo "---------------------"
			echo "---------------------" >> log
			echo $1 | tee -a log
			$1 2>&1 | tee -a log
			echo "---------------------" >> log
			echo "Have wrote this to file log"
			exit 0
		fi
	fi
}

echo "#######################"
bsp3 "touch aaa"
echo "#######################"
bsp3 "ls"
echo "#######################"
bsp3 "ls -z"
echo "#######################"
bsp3 "touch bbb"
echo "#######################"
