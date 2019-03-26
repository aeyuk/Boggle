all:
	gcc -g -Wall -std=c11 trie.c board.c game.c -o boggle

clean:
	rm *.0 encode

