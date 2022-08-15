NAME = webserv

CC = c++
CFLAGS = 


RM = rm
RMFLAGS = -rf

INC_DIR = Includes/
SRC_DIR = Sources/
OBJ_DIR = obj/

INCS = 	Includes/tt.hpp\
		Includes/server.hpp\
		Includes/location.hpp\
		Includes/Firstline.hpp\
		Includes/Response.hpp\
		Includes/request.hpp\
		Includes/Header.hpp\
		Includes/Cgi.hpp\
		Includes/parsing.hpp



		
	
SRCS_CLIENT = Sources/client.cpp

SRCS = \
	Sources/parsing_request.cpp\
	Sources/main.cpp\
	Sources/vector_parsing.cpp\
	Sources/server.cpp\
	Sources/request.cpp\
	Sources/location.cpp\
	Sources/Firstline.cpp\
	Sources/Response.cpp\
	Sources/Header.cpp\
	Sources/Cgi.cpp\
	Sources/before_parsing.cpp\
	Sources/StatusCode.cpp


	



vpath %.cpp $(SRC_DIR)

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))


# ============================================================================ #
#                                   COLOR                                      #
# ============================================================================ #

CL_BOLD	 = \e[1m
CL_DIM	= \e[2m
CL_UDLINE = \e[4m

NO_COLOR = \e[0m

BG_TEXT = \e[48;2;45;55;72m
BG_BLACK = \e[48;2;30;31;33m

FG_WHITE = $(NO_COLOR)\e[0;37m
FG_TEXT = $(NO_COLOR)\e[38;2;189;147;249m
FG_TEXT_PRIMARY = $(NO_COLOR)$(CL_BOLD)\e[38;2;255;121;198m

LF = \e[1K\r$(NO_COLOR)
CRLF= \n$(LF)

all : $(NAME) $(CLIENT)

clean :
	@$(RM) $(RMFLAGS) $(OBJS)
	@printf "$(LF)🧹 $(FG_TEXT)Cleaning $(FG_TEXT_PRIMARY)$(NAME)'s Object files...\n"

fclean : clean
	@$(RM) $(RMFLAGS) $(NAME)
	@printf "$(LF)🧹 $(FG_TEXT)Cleaning $(FG_TEXT_PRIMARY)$(NAME)\n"

re : fclean all

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.cpp $(INCS) | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@
	@printf "$(LF)🚧 $(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@ $(FG_TEXT)from $(FG_TEXT_PRIMARY)$<"

$(NAME) : $(OBJS) $(INCS)
	@printf "$(LF)🚀 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@'s Object files $(FG_TEXT)!"
	@printf "$(CRLF)📚 $(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@$(FG_TEXT)!\n"
	@$(CC) $(CFLAGS) -I $(INC_DIR) $(OBJS) -o $@
	@printf "$(LF)🎉 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@ $(FG_TEXT)!\n$(NO_COLOR)"


$(CLIENT) :  $(INCS)
	@printf "$(LF)🚀 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@'s Object files $(FG_TEXT)!"
	@printf "$(CRLF)📚 $(FG_TEXT)Create $(FG_TEXT_PRIMARY)$@$(FG_TEXT)!\n"
	@$(CC) $(CFLAGS) -I $(INC_DIR) $(SRCS_CLIENT) -o $@
	@printf "$(LF)🎉 $(FG_TEXT)Successfully Created $(FG_TEXT_PRIMARY)$@ $(FG_TEXT)!\n$(NO_COLOR)"

.PHONY: all clean fclean re