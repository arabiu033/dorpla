dorpla: ./core/src/main.c
	$(CC) -Wall -pedantic -Werror -Wextra -std=gnu89 ./core/src/main.c -o dorpla
	rm -f *~
	rm -f ./core/src/*~
	rm -f ./core/include/*~
