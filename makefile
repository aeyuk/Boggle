all:
	gcc -g -Wall -std=c11 -lm trie.c board.c game.c -o boggle

clean:
	rm *.0 encode

