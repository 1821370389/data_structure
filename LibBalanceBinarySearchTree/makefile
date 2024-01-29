# 动态库编译
OBJ=$(patsubst %.c, %.o, $(wildcard ./*.c))
TARGET=main

$(TARGET):$(OBJ)
	gcc $^ -lSoMyAVL -o $@

%.o:%.c
	gcc -c $^ -o $@

clean:
	rm $(OBJ)
	rm $(TARGET)