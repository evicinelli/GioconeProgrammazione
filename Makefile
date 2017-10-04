all:
	clear && g++ -g *.cpp -lncurses

debug:
	clear && g++ -DDEBUG -c *.cpp -lncurses 
clean:
	rm *.out && clear
