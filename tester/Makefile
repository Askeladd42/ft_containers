# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plam <plam@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/30 17:07:52 by plam              #+#    #+#              #
#    Updated: 2022/12/30 17:07:56 by plam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = c++
SRCS = time_it.cpp

.PHONY: re clean fclean
.SILENT: all re clean fclean

NAME = time_it

all: $(NAME)

 $(NAME): $(SRCS)
	$(CXX) -o $(NAME) $(SRCS)

re: fclean all

clean: fclean

fclean:
	rm -f $(NAME)