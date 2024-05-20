NAME		=	./TCP
CXX			=	c++ 
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++11
RM			=	rm -rf
SRCS		=	ListenSocket.cpp \
				ServerSocket.cpp \
				KQueueEvent.cpp \
				ISocket.cpp \
				IEvent.cpp	\
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