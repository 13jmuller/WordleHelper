# Makefile

# Compiler
CXX ?= g++

ADD ?= -lm

# Compiler flags
CXXFLAGS ?= --std=c++11 -Wall -Werror -pedantic -g3 -DDEBUG

cosine: cosine.exe
  ./cosine.exe -m <c> -s <5>


cosine.exe: main.cpp wordleFunctions.cpp
  $(CXX) $(CXXFLAGS) $^ -o $@ $(ADD)
  

  
