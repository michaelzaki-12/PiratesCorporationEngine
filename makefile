CC = clang
CXX = clang++
CFLAGS = -Wall -Wextra -lGL -lglfw -Wno-unused-command-line-argument
CXXFLAGS = -Wall -Werror -Wextra -lGL -lglfw -std=c++20 -O0 -stdlib=libc++ -Wno-unused-command-line-argument
LDLink = -Wall -fuse-ld=lld -stdlib=libc++ -lGL -lglfw
cppfiles = $(wildcard *.cpp) $(wildcard GeneralDeps/*.cpp) $(wildcard imgui-docking/*.cpp) imgui-docking/backends/imgui_impl_glfw.cpp imgui-docking/backends/imgui_impl_opengl3.cpp
OBJ = $(wildcard *.o)
CFILES = glad/glad.c
all:
	$(CC) $(CFLAGS) -c $(CFILES)
	$(CXX) $(CXXFLAGS) -c $(cppfiles)
	$(CXX) $(LDLink) -o Engine.elf $(OBJ)
	./Engine.elf
run:
	./Engine.elf
clean:
	rm $(wildcard *.o)