# CS50 Week 5 — Master Makefile

CC = clang
CFLAGS = -Wall -Wextra -Wshadow -std=c11

.PHONY: all inheritance speller clean

# 'make all' komutu her iki projeyi de derler
all: inheritance speller

# lab5/inheritance dizinine gidip oradaki Makefile'ı çalıştırır
inheritance:
	$(MAKE) -C lab5/inheritance inheritance

# pset5/speller dizinine gidip oradaki Makefile'ı çalıştırır
speller:
	$(MAKE) -C pset5/speller speller

# Her iki alt dizindeki 'clean' komutlarını çalıştırarak temizlik yapar
clean:
	$(MAKE) -C lab5/inheritance clean
	$(MAKE) -C pset5/speller clean
