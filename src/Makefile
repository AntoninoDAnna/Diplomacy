OBJECT_DIR= ../bin
OBJ_DEBUG_DIR = ../bin/Debug

SRC_DIR = ./
H_DIR = ../include

MAIN = main.cc
TEST = test.cc

MAIN_OBJ = $(MAIN_FILES:%.cc= $(OBJECT_DIR)/%.o)
TEST_OBJ = $(TEST_FILES:%.cc= $(OBJECT_DIR)/%.o) 

SRC_FILES = country.cc \
						region.cc \
						utilities.cc
						  
H_FILES = diplomacy.h \
          country.h \
					region.h \
					utilities.h

SRC = $(SRC_FILES:%.cc= $(SRC_DIR)/%.cc)
HRS = $(H_FILES:%.h= $(H_DIR)/%.h)
OBJ = $(SRC:%.cc= $(OBJECT_DIR)/%.o)
DOBJ = $(SRC:%.cc= $(OBJ_DEBUG_DIR)/%.o)

CXX = g++ 
CFLAGS = -c
LDFLAGS = -lm -O3 -Wall -Wextra -Wpedantic -O0 -finline-functions -funroll-loops  -fsanitize=address

diplomacy.x: $(MAIN) $(OBJ) $(HRS)
	$(CXX) $(LDFLAGS) $(MAIN) $(OBJ) $(HRS) -o $@

test.x: $(TEST) $(OBJ) $(HRS)
	$(CXX) $(LDFLAGS) $(TEST) $(OBJ) $(HRS) -o $@

debug_test.x: $(TEST) $(DOBJ) $(HRS)
	LSAN_OPTIONS=verbosity=1:log_threads=1;
	$(CXX) -g3 $(LDFLAGS) $(TEST) $(OBJ) $(HRS) -o $@ 

$(OBJ): $(OBJECT_DIR)/%.o: %.cc 
	@if [ ! -d $(OBJECT_DIR) ]; then mkdir $(OBJECT_DIR); fi
	$(CXX) $(CFLAGS) $(LDFLAGS) $< -o $@

$(DOBJ): $(OBJ_DEBUG_DIR)/%.o: %.cc 
	$(CXX) -g3 $(CFLAGS) $(LDFLAGS) $< -o $@


clean:
	@rm -f $(OBJECT_DIR)/*.o
	@echo make clean: done
