OBJECT_DIR= ../bin
OBJ_DEBUG_DIR = ../bin/Debug
H_DIR = ../include
SRC_DIR = .

MAIN = main.cc
TEST = test.cc
TEST_APP = test_app.cc

SRC_FILES = app.cc button.cc country.cc file_manager.cc game.cc region.cc text.cc texture_manager.cc unit.cc utilities.cc 
H_FILES = app.h button.h country.h file_manager.h game.h region.h text.h texture_manager.h unit.h utilities.h 


SRC = $(SRC_FILES:%.cc= $(SRC_DIR)/%.cc)
HRS = $(H_FILES:%.h= $(H_DIR)/%.h)
OBJ = $(SRC:%.cc= $(OBJECT_DIR)/%.o)
DOBJ = $(SRC:%.cc= $(OBJ_DEBUG_DIR)/%.o)
SDL_H = $(H_DIR)/libSDL2.a $(H_DIR)/libSDL2_image.a

CXX = g++
CFLAGS = -c
LDFLAGS = -lm -std=c++20 -lSDL2 -lSDL2_image -lSDL2_ttf -O3 -Wall -Wextra -Wpedantic -O0 -finline-functions -funroll-loops  -fsanitize=address

diplomacy.x: $(MAIN) $(OBJ) $(HRS) $(SDL_H)
	$(CXX) $(LDFLAGS) $(MAIN) $(OBJ)  -o $@

test.x: $(TEST) $(OBJ) $(HRS) $(SDL_H)
	$(CXX) $(LDFLAGS) $(TEST) $(OBJ)  -o $@

app.x: $(TEST_APP) $(OBJ) $(HRS) 
	$(CXX) $(LDFLAGS) $(TEST_APP) $(OBJ)   -o $@

debug_test.x: $(TEST) $(DOBJ) $(HRS) $(SDL_H)
	$(CXX) -g3 $(LDFLAGS) $(TEST) $(OBJ) $(HRS) $(SDL_H) -o $@ 

debug_test_app.x: $(TEST_APP) $(DOBJ) $(HRS) $(SDL_H)
	$(CXX) -g3 $(LDFLAGS) $(TEST_APP) $(OBJ) $(HRS) $(SDL_H) -o $@ 


$(OBJ): $(OBJECT_DIR)/%.o: %.cc 
	@if [ ! -d $(OBJECT_DIR) ]; then mkdir $(OBJECT_DIR); fi
	$(CXX) $(CFLAGS) $(LDFLAGS)   $< -o $@

$(DOBJ): $(OBJ_DEBUG_DIR)/%.o: %.cc 
	$(CXX) -g3 $(CFLAGS) $(LDFLAGS) $< -o $@

fix:
	sudo sysctl vm.mmap_rnd_bits=28

clean:
	@rm -f $(OBJECT_DIR)/*.o
	@rm -f $(OBJ_DEBUG_DIR)/*.o
	@echo make clean: done
