
rm diff.txt
rm logft.txt
rm logstd.txt

make -s fclean && make -s ft_containers
echo "Timing for Test, NAMESPACE FT"
time ./ft_containers 150 1> logft.txt
make -s fclean && make -s stl_containers
echo "Timing for Test, NAMESPACE STD"
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