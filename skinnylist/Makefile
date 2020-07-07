a.out: main.o SkinnyList.o SkinnyNode.o
	g++ -std=c++17 -Wall -Wextra -Werror -o a.out main.o SkinnyList.o SkinnyNode.o

main.o: main.cpp SkinnyList.h
	g++ -std=c++17 -Wall -Wextra -Werror -c -o main.o main.cpp

SkinnyList.o: SkinnyList.cpp SkinnyList.h
	g++ -std=c++17 -Wall -Wextra -Werror -c -o SkinnyList.o SkinnyList.cpp

SkinnyNode.o: SkinnyNode.cpp SkinnyList.h
	g++ -std=c++17 -Wall -Wextra -Werror -c -o SkinnyNode.o SkinnyNode.cpp

clean:
	rm -f a.out main.o SkinnyList.o SkinnyNode.o
