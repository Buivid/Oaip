cmake_minimum_required(VERSION 3.23)
project(Labs C)

set(CMAKE_C_STANDARD 99)

add_executable(2Lab1 2Lab1/main.c 2Lab1/func.c 2Lab1/func.h)
<<<<<<< HEAD
add_executable(2Lab2 2Lab2/compressor/main.c 2Lab2/compressor/functions.c 2Lab2/compressor/functions.h)
add_executable(2Lab2_dec 2Lab2_dec/decompressor/main_decompress.c 2Lab2_dec/decompressor/func_decompress.c 2Lab2_dec/decompressor/func_decompress.h)
=======
add_executable(compressor 2Lab2/compressor/main.c 2Lab2/compressor/functions.c 2Lab2/compressor/functions.h)
add_executable(decompressor 2Lab2/decompressor/main_decompress.c 2Lab2/decompressor/func_decompress.c 2Lab2/decompressor/func_decompress.h)
>>>>>>> a9bddcb47982e21ad693ba296a0cce06159c6bc9
