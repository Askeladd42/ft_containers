#!/usr/bin/zsh

rm diff.txt
rm logft.txt
rm logstd.txt

make -s fclean && make -s TESTER="1" NAMESPACE="ft"
echo "Timing for Tester Vector, NAMESPACE FT"
time ./ft_containers 400 vector >> logft.txt
make -s fclean && make -s TESTER="1" NAMESPACE="std"
echo "Timing for Tester Vector, NAMESPACE STD"
time ./stl_containers 400 vector >> logstd.txt

# diff -y logft.txt logstd.txt >> diff.txt
diff logft.txt logstd.txt > diff.txt
rm logft.txt logstd.txt

make -s fclean && make -s TESTER="2" NAMESPACE="ft"
echo "Timing for Tester Stack, NAMESPACE FT"
time ./ft_containers 400 stack >> logft.txt
make -s fclean && make -s TESTER="2" NAMESPACE="std"
echo "Timing for Tester Stack, NAMESPACE STD"
time ./stl_containers 400 stack >> logstd.txt

# diff -y logft.txt logstd.txt >> diff.txt
diff logft.txt logstd.txt > diff.txt
rm logft.txt logstd.txt


make -s fclean && make -s TESTER="3" NAMESPACE="ft"
echo "Timing for Tester Map, NAMESPACE FT"
time ./ft_containers 400 map >> logft.txt
make -s fclean && make -s TESTER="3" NAMESPACE="std"
echo "Timing for Tester Map, NAMESPACE STD"
time ./stl_containers 400 map >> logstd.txt

# diff -y logft.txt logstd.txt >> diff.txt
diff logft.txt logstd.txt > diff.txt
rm logft.txt logstd.txt

make -s fclean && make -s TESTER="4" NAMESPACE="ft"
echo "Timing for Tester Extras, NAMESPACE FT"
time ./ft_containers 400 extras >> logft.txt
make -s fclean && make -s TESTER="4" NAMESPACE="std"
echo "Timing for Tester Extras, NAMESPACE STD"
time ./stl_containers 400 extras >> logstd.txt

# diff -y logft.txt logstd.txt >> diff.txt
diff logft.txt logstd.txt > diff.txt

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