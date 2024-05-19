NAME		=	./TCP
CXX			=	c++ 
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98
RM			=	rm -rf
SRCS		=	KQueueEvent.cpp \
				ListenSocket.cpp \
				ServerSocket.cpp \
				Socket.cpp \
				main.cpp
				
OBJS		=	${SRCS:.c=.o}

all	:
	@$(MAKE)  $(NAME)

$(NAME) : $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

%.o : %.c
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	@$(RM)

fclean : clean
	@$(RM) $(NAME)

re :
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY : all clean fclean re