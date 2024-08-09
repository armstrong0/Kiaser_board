all: kaiser_board.svg

gen_kaiser_board: Kaiser_board.cpp simple_svg_1.0.0.hpp
	g++ -std=c++11 Kaiser_board.cpp -o gen_kaiser_board

kaiser_board.svg: gen_kaiser_board
	./gen_kaiser_board
clean:
	rm -rf gen_kaiser_board
	rm -rf Kaiser_board.svg
	rm -rf *png
	rm -rf *jpeg
	rm -rf *~


