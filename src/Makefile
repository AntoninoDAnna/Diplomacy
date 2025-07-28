OBJECT_DIR= ../bin
OBJ_DEBUG_DIR = ../bin/Debug
H_DIR = ../include
SRC_DIR = .
IMG_DIR = ../imgui

MAIN = main.cpp


DYP_SRC = $(notdir $(wildcard $(SRC_DIR)/*.cc))
IMG_SRC = $(notdir $(wildcard $(IMG_DIR)/*.cpp))

SRC = $(DYP_SRC) $(IMG_SRC)

DYP_H = $(wildcard $(H_DIR)*.h)
IMG_H = $(wildcard $(IMG_DIR)/*.h)
HRS   = $(DYP_H) $(IMG_H)

DYP_OBJ = $(DYP_SRC:%.cc=$(OBJECT_DIR)/%.o)
IMG_OBJ = $(IMG_SRC:%.cpp=$(OBJECT_DIR)/%.o)


SDL_H = $(H_DIR)/libSDL2.a $(H_DIR)/libSDL2_image.a

CXX     = g++
CFLAGS  = -c
LDFLAGS = -lm -std=c++20 -lSDL2 -lSDL2_image -lSDL2_ttf -Werror -Wall -Wextra -Wpedantic -fsanitize=address

diplomacy.x: $(MAIN) $(DYP_OBJ) $(IMG_OBJ) $(HRS) $(SDL_H)
	$(CXX) $(LDFLAGS) $(MAIN) $(DYP_OBJ) $(IMG_OBH)  -o $@

$(DYP_OBJ): $(OBJECT_DIR)/%.o: %.cc
	@if [ ! -d $(OBJECT_DIR) ]; then mkdir $(OBJECT_DIR); fi
	$(CXX) $(CFLAGS) $(LDFLAGS)   $< -o $@

$(IMG_OBJ): $(OBJECT_DIR)/%.o: $(IMG_DIR)/%.cpp
	@if [ ! -d $(OBJECT_DIR) ] ; then mkdir $(OBJECT_DIR); fi
	$(CXX) $(CFLAGS) $(LDFLAGS)   $< -o $@

test:
	echo $(SRC) $(OBJ) $(HRS)

fix:
	sudo sysctl vm.mmap_rnd_bits=28

clean:
	@rm -f $(OBJECT_DIR)/*.o
	@rm -f $(OBJ_DEBUG_DIR)/*.o
	@echo make clean: done
