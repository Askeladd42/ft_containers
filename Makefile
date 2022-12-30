# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plam <plam@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 09:31:35 by plam              #+#    #+#              #
#    Updated: 2022/12/30 14:25:57 by plam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = containers_test

CXX = c++
CXXFLAGS = -Wextra -Wall -Werror -std=c++98 -g3

INCL = ./includes
SRC_FILES = main.cpp
OBJS = $(SRC_FILES:.cpp=.o)
OBJS_F	= _objFiles/

all: $(NAME)

$(NAME): 

			@echo "     - Creating object directory..."
					@mkdir -p $(OBJS_F)
					@echo "     - Making object files..."
					$(CXX) $(CXXFLAGS) -c $(SRC_FILES)
					@echo "     - Moving object files to $(OBJS_F)..."
					@mv $(OBJS) $(OBJS_F)
					@echo "     - Compiling $(NAME)..." 
					$(CXX) $(CXXFLAGS) -I $(INCL) $(addprefix $(OBJS_F), $(OBJS)) -o $(NAME)
					@echo "- $(NAME) Compiled -"

clean:
					@rm -rf $(OBJS_F)
					@rm -f ${OBJS_BONUS} ${OBJS}

fclean: 	clean
					@rm -f $(NAME)

re:			fclean all