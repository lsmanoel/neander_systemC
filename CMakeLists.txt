# *****************************************************************************
# lucas on 29/03/19.
# *****************************************************************************

#https://medium.com/aprendacpp/usando-cmake-para-compilar-c-c-abf52c7dcbc8
#http://derekmolloy.ie/hello-world-introductions-to-cmake/

#[[
	$ mkdir build && cd build
	$ cmake ../
	$ make
	$ ./neander

	to Clear:
		rm -rf build

	to Build:
		mkdir build && cd build && cmake ../ && make && ./neander && cd ..
	
	to ReBuild:
		rm -rf build && mkdir build && cd build && cmake ../ && make && ./neander && cd ..

]]

cmake_minimum_required(VERSION 3.7)
project(neander)

set(CMAKE_CXX_STANDARD 14)

add_executable(neander main.cpp)

include_directories("/usr/local/systemc233/include")
target_link_libraries(neander "/usr/local/systemc233/lib-linux64/libsystemc.a")