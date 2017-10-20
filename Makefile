TARGET := $(shell find src/ -name '*.*pp')
all:
	clear && g++ -o @t-m@n -g $(TARGET) -lncurses
clean:
	rm *.out && clear
