NAME = container

CXX = clang++
CXX_FLAGS = -Wextra -Wall -Werror #-std=c++98

TESTER="0"
NAMESPACE="ft"

SRCS_DIR = ./

SRCS = 		main.cpp					\
			tests/compare/compare.cpp			\
			tests/extras/extras.cpp			\
			tests/map/mapTest.cpp			\
			tests/preliminary/preliminary.cpp		\
			tests/stack/stackTest.cpp			\
			tests/vector/vectorTest.cpp		\

OBJS_DIR = ./objects/
OBJ = $(SRCS:.cpp=.o)
OBJS = $(addprefix $(OBJS_DIR), $(OBJ))
DEP = $(OBJS:.o=.d)
$(NAME) : $(OBJS)
	$(CXX) $(CXX_FLAGS) $^ -o $@

-include $(DEP)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -MMD -o $@ -c $< -D TESTER=$(TESTER) -D NAMESPACE=$(NAMESPACE)
all : $(NAME)
	

clean :
	rm -rf $(OBJS_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re