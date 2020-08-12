CC=arm-linux-gcc
C_SOURCE=$(wildcard ./src/*.c)
TARGET=./bin/main
include_path=-I ./include
lib_path=-L ./lib -lmy2

$(TARGET):$(C_SOURCE)
	$(CC) $^ -o $@ $(include_path) $(lib_path)
	
.PHONY:clean

clean:
	$(RM) $(TARGET)