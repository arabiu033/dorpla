dorpla: ./core/src/main.c ./core/include/main.h ./modules/*.c
	$(CC) -Wall -pedantic -Werror -Wextra -std=gnu89 ./core/src/main.c ./modules/*.c -o dorpla
	rm -f *~
	rm -f ./core/src/*~
	rm -f ./core/include/*~
