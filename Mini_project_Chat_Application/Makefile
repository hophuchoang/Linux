CUR_DIR := .
INC_DIR := $(CUR_DIR)/inc
SOURCE_DIR := $(CUR_DIR)/src
BIN_DIR := $(CUR_DIR)/bin
TEST_DIR := $(CUR_DIR)/test

C_FLAGS := -I $(INC_DIR)

all:
	mkdir $(BIN_DIR)
	gcc -o $(BIN_DIR)/chat_application $(SOURCE_DIR)/main.c $(SOURCE_DIR)/ui_display.c $(SOURCE_DIR)/socket.c $(SOURCE_DIR)/app_func.c $(C_FLAGS)

my_test:
	gcc -o $(TEST_DIR)/test $(TEST_DIR)/test.c
	
clean:
	rm -rf $(BIN_DIR) .vscode