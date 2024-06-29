OBJECT_DIR= bin

MAIN = main.cc
TEST = test.cc

MAIN_OBJ = $(MAIN_FILES:%.cc= $(OBJECT_DIR)/%.o)
TEST_OBJ = $(TEST_FILES:%.cc= $(OBJECT_DIR)/%.o) 

SOURCE_FILES = country.cc \
							 region.cc \
							 utilities.cc
						  
HEADERS = diplomacy.h \
					global_variables.h \
          country.h \
					region.h \
					utilities.h

OBJECT_FILES  = $(SOURCE_FILES:%.cc= $(OBJECT_DIR)/%.o)


CXX = g++ 
CFLAGS = -c
LDFLAGS = -lm -O3 -Wall -finline-functions -funroll-loops  -fsanitize=address

diplomacy.x: $(MAIN) $(OBJECT_FILES) $(HEADERS)
	$(CXX) $(LDFLAGS) $(MAIN) $(OBJECT_FILES) $(HEADERS) -o $@

test.x: $(TEST) $(OBJECT_FILES) $(HEADERS)
	$(CXX) $(LDFLAGS) $(TEST) $(OBJECT_FILES) $(HEADERS) -o $@


$(OBJECT_FILES): $(OBJECT_DIR)/%.o: %.cc 
	@if [ ! -d $(OBJECT_DIR) ]; then mkdir $(OBJECT_DIR); fi
	$(CXX) $(CFLAGS) $(LDFLAGS) $< -o $@



clean:
	@rm -f $(OBJECT_DIR)/*.o
	@echo make clean: done
