CUR_DIR := .
BIN_DIR := $(CUR_DIR)/bin
INC_DIR := $(CUR_DIR)/inc
OBJ_DIR := $(CUR_DIR)/obj
SRC_DIR := $(CUR_DIR)/src
LIB_DIR := $(CUR_DIR)/lib
LIB_STATIC_DIR := $(LIB_DIR)/static
LIB_SHARED_DIR := $(LIB_DIR)/shared

C_FLAGS := -I $(INC_DIR)

create_objs_static_lib:
# Static lib
	gcc -c $(SRC_DIR)/helloThanh.c -o $(OBJ_DIR)/helloThanh.o $(C_FLAGS)
	gcc -c $(SRC_DIR)/helloWorld.c -o $(OBJ_DIR)/helloWorld.o $(C_FLAGS)
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o $(C_FLAGS)

create_objs_shared_lib:
# Shared lib
	gcc -c -fPIC $(SRC_DIR)/helloThanh.c -o $(OBJ_DIR)/helloThanh.o $(C_FLAGS)
	gcc -c -fPIC $(SRC_DIR)/helloWorld.c -o $(OBJ_DIR)/helloWorld.o $(C_FLAGS)
	gcc -c $(SRC_DIR)/main.c -o $(OBJ_DIR)/main.o $(C_FLAGS)

create_lib_static:
	ar rcs $(LIB_STATIC_DIR)/libhello.a $(OBJ_DIR)/helloThanh.o $(OBJ_DIR)/helloWorld.o

create_lib_shared:
	gcc -shared $(OBJ_DIR)/helloThanh.o $(OBJ_DIR)/helloWorld.o -o $(LIB_SHARED_DIR)/libhello.so

static: create_objs_static_lib create_lib_static
	gcc $(OBJ_DIR)/main.o -L$(LIB_STATIC_DIR) -lhello -o $(BIN_DIR)/statically-linked
shared: create_objs_shared_lib create_lib_shared
	gcc $(OBJ_DIR)/main.o -L$(LIB_SHARED_DIR) -lhello -o $(BIN_DIR)/use-shared-library

all: static shared
	@echo "Completed"
	
clean:
	rm -rf $(OBJ_DIR)/*.o
	rm -rf $(LIB_SHARED_DIR)/*.so
	rm -rf $(LIB_STATIC_DIR)/*.a
	rm -rf $(BIN_DIR)/use-shared-library
	rm -rf $(BIN_DIR)/statically-linked

# all:
# 	gcc -c -o helloThanh.o helloThanh.c -I .
# 	gcc -c -o helloWorld.o helloWorld.c -I .
# 	gcc -c -o main.o main.c

# clean:
# 	rm -rf *.o