#!/bin/bash

if [ "$1" == "clean" ] 
then
	rm -f ft_output
	rm -f stl_output
	make fclean > /dev/null
	make -C tests fclean > /dev/null
	exit 0
fi

make > /dev/null

./ft_containers > ft_output
./stl_containers > stl_output

output=$(diff ft_output stl_output)

if [ "$output" ]
then
	echo "Result: FAIL"
	echo "$output"
else
	make -C tester > /dev/null
	./tester/time_it stl_containers ft_containers
	make -C tests fclean > /dev/null
	echo "Result: DONE"
	make fclean &> /dev/null
	rm -f ft_output &> /dev/null
	rm -f stl_output &> /dev/null
fi