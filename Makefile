TARGET = main
BUILD_DIR = build

CC = g++
CFLAGS = -O2 -Wall -Werror -g
LINKFLAGS =

INCLUDES = -I include
SRC_DIR = src
LIBS = -lSDL2

C_SRC_DIR = $(SRC_DIR)
C_SOURCES = $(foreach d,$(C_SRC_DIR),$(wildcard $(d)/*.c) )
C_OBJS = $(patsubst %.c, $(BUILD_DIR)/%.o, $(C_SOURCES))

CPP_SRC_DIR = $(SRC_DIR)
CPP_SOURCES = $(foreach d,$(CPP_SRC_DIR),$(wildcard $(d)/*.cpp) )
CPP_OBJS = $(patsubst %.cpp, $(BUILD_DIR)/%.o, $(CPP_SOURCES))

default: init compile

$(C_OBJS): $(BUILD_DIR)/%.o:%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

$(CPP_OBJS): $(BUILD_DIR)/%.o:%.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

init:
	$(foreach d,$(SRC_DIR), mkdir -p $(BUILD_DIR)/$(d);)

compile: $(C_OBJS) $(CPP_OBJS)
	$(CC)  $^ -o $(BUILD_DIR)/$(TARGET) $(LINKFLAGS) $(LIBS)

clean:
	rm -rf $(BUILD_DIR)

# install: $(TARGET)
# 	cp $(TARGET) $(PREFIX_BIN)

# uninstall:
# 	rm -f $(PREFIX_BIN)/$(TARGET)

rebuild: clean init compile

run: default
	$(BUILD_DIR)/$(TARGET)