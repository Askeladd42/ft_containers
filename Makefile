# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: plam <plam@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/03 09:31:35 by plam              #+#    #+#              #
#    Updated: 2023/01/09 12:09:59 by plam             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

STL_NAME = stl_containers
FT_NAME = ft_containers

CXX = c++
CXXFLAGS = -Wextra -Wall -Werror -std=c++98

INCL = ./includes
SRC_FILES = main.cpp
OBJS = $(SRC_FILES:.cpp=.o)
OBJS_F	= _objFiles/

all: $(STL_NAME) $(FT_NAME)

$(STL_NAME):

			@echo "     - Creating object directory..."
					@mkdir -p $(OBJS_F)
					@echo "     - Making object files..."
					$(CXX) $(CXXFLAGS) -D NAMESPACE=STL -c $(SRC_FILES)
					@echo "     - Moving object files to $(OBJS_F)..."
					@mv $(OBJS) $(OBJS_F)
					@echo "     - Compiling $(STL_NAME)..."
					$(CXX) $(CXXFLAGS) $(addprefix $(OBJS_F), $(OBJS)) -o $(STL_NAME)
					@echo "- $(STL_NAME) Compiled -"

$(FT_NAME):

			@echo "     - Creating object directory..."
					@mkdir -p $(OBJS_F)
					@echo "     - Making object files..."
					$(CXX) $(CXXFLAGS) -I $(INCL) -D NAMESPACE=FT -c $(SRC_FILES)
					@echo "     - Moving object files to $(OBJS_F)..."
					@mv $(OBJS) $(OBJS_F)
					@echo "     - Compiling $(FT_NAME)..."
					$(CXX) $(CXXFLAGS) $(addprefix $(OBJS_F), $(OBJS)) -o $(FT_NAME)
					@echo "- $(FT_NAME) Compiled -"


clean:
					@rm -rf $(OBJS_F)
					@rm -f ${OBJS_BONUS} ${OBJS}

fclean: 	clean
					@rm -f $(STL_NAME)
					@rm -f $(FT_NAME)
					@rm -f main.d
					@rm -f diff.txt

re:			fclean all