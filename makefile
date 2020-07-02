# Compiler name
CC = g++ 
# File extension
LANG = .cpp
# Program name
NAME = snake
# Compiler flags
CFLAGS = -Wall -O2
# Linker flags
LDFLAGS = 
# Libs
LIBS = -lSDL2
# Source directory
DIR = source/

SRC_FILES = $(wildcard $(DIR)*$(LANG))

# Creating object files
OBJECTS := $(notdir $(patsubst %$(LANG), %.o, $(SRC_FILES)))

# Linking debug version
all: $(OBJECTS)
	$(CC) -g $(LDFLAGS) $(LIBS) $(OBJECTS) -o $(NAME)_d

# Compiling and linking release version
release: 
	$(CC) $(CFLAGS) $(LDFLAGS) $(LIBS) $(SRC_FILES) -o $(NAME)

# Compiling debug
%.o: $(DIR)%$(LANG) 
	$(CC) -g -c $(CFLAGS) $< -o $@

# Clean rep
clean:
	rm $(OBJECTS)
	rm $(NAME)_d
