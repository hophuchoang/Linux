CUR_DIR := .
SOURCE_DIR := $(CUR_DIR)/src
BIN_DIR := $(CUR_DIR)/bin

IPV4_TCP_DIR := $(SOURCE_DIR)/ipv4_tcp
IPV4_UDP_DIR := $(SOURCE_DIR)/ipv4_udp
UNIX_TCP_DIR := $(SOURCE_DIR)/unix_tcp
UNIX_UDP_DIR := $(SOURCE_DIR)/unix_udp

ipv4_tcp:
	gcc -o $(BIN_DIR)/ipv4_tcp_server $(IPV4_TCP_DIR)/server.c
	gcc -o $(BIN_DIR)/ipv4_tcp_client $(IPV4_TCP_DIR)/client.c

ipv4_udp:
	gcc -o $(BIN_DIR)/ipv4_udp_server $(IPV4_UDP_DIR)/server.c
	gcc -o $(BIN_DIR)/ipv4_udp_client $(IPV4_UDP_DIR)/client.c

unix_tcp:
	gcc -o $(BIN_DIR)/unix_tcp_server $(UNIX_TCP_DIR)/server.c
	gcc -o $(BIN_DIR)/unix_tcp_client $(UNIX_TCP_DIR)/client.c

unix_udp:
	gcc -o $(BIN_DIR)/unix_udp_server $(UNIX_UDP_DIR)/server.c
	gcc -o $(BIN_DIR)/unix_udp_client $(UNIX_UDP_DIR)/client.c
	

clean:
	rm -rf $(BIN_DIR)/*