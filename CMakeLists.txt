cmake_minimum_required(VERSION 3.10)

project(RSA C)

set(CMAKE_C_STANDARD 23)

add_executable(rsa
	main.c
	mod.c
	crypto.c
)

add_compile_options(-Wall -Wextra -Werror)

