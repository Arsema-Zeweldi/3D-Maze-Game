build:
		gcc src/*.c -Wall -Werror -Wextra -pedantic -lSDL2 -lSDL2_image -lm -o maze

run:
		./maze
	
clean:
		rm maze
