

NAME	= 	containers

CC		=	c++

FLAGS	=	#-Wall -Werror -Wextra -std=c++98

SRC		=	tests/test_time_stack.cpp
#SRC		=	tests/test_time_vector.cpp
#SRC		=	tests/test_time_map.cpp
#SRC		=	tests/test_time_set.cpp
#SRC		=	tests/test_subject.cpp



HDR =		stack/stack.hpp map/map.hpp set/set.hpp utils/iterator_traits.hpp utils/reverse_iterator.hpp utils/utils.hpp \
 			vector/vector.hpp vector/vector_capacity.hpp vector/vector_constructor.hpp vector/vector_element_access.hpp \
			vector/vector_modifiers.hpp vector/vector_iter_func.hpp vector/vector_iterator.hpp \
			RBTree/RBTree.hpp RBTree/RBTree_capacity.hpp RBTree/RBTree_constructor.hpp RBTree/RBTree_iter_func.hpp \
			RBTree/RBTree_lookup.hpp RBTree/RBTree_modifiers.hpp

OBJS	=	$(SRC:.cpp=.o)

RM		=	rm -rf

.PHONY:		all clean fclean re

all:		$(NAME)

$(NAME):	$(OBJS)
				@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
				@echo "Compiled "$(NAME)" successfully!"

%.o:%.cpp $(HDR)
				@$(CC) $(FLAGS) -c $< -o $@
				@echo "---Compiled "$<" successfully!---"

clean:
				$(RM) $(OBJS)

fclean:		clean
				$(RM) $(NAME)

re:			fclean all