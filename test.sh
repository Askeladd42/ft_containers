
rm diff.txt
rm logft.txt
rm logstd.txt

make -s fclean && make -s TESTER="1" NAMESPACE="ft"
echo "Timing for Tester 1, NAMESPACE FT"
time ./ft_containers 150 1> logft.txt
make -s fclean && make -s TESTER="1" NAMESPACE="std"
echo "Timing for Tester 1, NAMESPACE STD"
time ./stl_containers 150 1> logstd.txt

diff -y logft.txt logstd.txt >> diff.txt
echo "Printing differences : "
cat diff.txt
if [ -s diff.txt ]
then
	echo -e "\033[0;32m There are no differences ! 😘"
else
	echo -e "\033[0;31m There are some differences ! 😅"
fi

rm logft.txt
rm logstd.txt