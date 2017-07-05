# Makefile for preview form

main.out : main.cc form.cc form.h
	clang++ -ansi -Wall -Wextra -pedantic-errors -std=c++11 `fltk-config --cxxflags` -g main.cc form.cc `fltk-config --ldflags` -lfltk_images -lfltk_jpeg -o main.out

clean :
	rm main.out