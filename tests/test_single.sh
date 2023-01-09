#!/usr/bin/zsh

rm diff.txt
rm logft.txt
rm logstd.txt

make -s fclean && make -s TESTER="1" NAMESPACE="ft"
echo "Timing for Tester 1, NAMESPACE FT"
time ./container extras >> logft.txt
make -s fclean && make -s TESTER="1" NAMESPACE="std"
echo "Timing for Tester 1, NAMESPACE STD"
time ./container extras >> logstd.txt

# diff -y logft.txt logstd.txt >> diff.txt
diff logft.txt logstd.txt >> diff.txt
echo "Printing differences : "
cat diff.txt
if [ -s diff.txt ]
then
    echo -e "\033[0;31m There are some differences ! 😅"
else
	echo -e "\033[0;32m There are no differences ! 😘"
fi

rm logft.txt 
rm logstd.txt 