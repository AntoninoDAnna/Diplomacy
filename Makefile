OBJECT_DIR= bin

MAIN = main.cc
SOURCE_FILES = $(MAIN) \
							 region.cc

						  
HEADERS = global_variables.h \
					region.h  

OBJECT_FILES  = $(SOURCE_FILES:%.cc= $(OBJECT_DIR)/%.o)


CXX = g++ 
CFLAGS = -c
LDFLAGS = -lm -O3 -Wall -finline-functions -funroll-loops 

diplomacy.x: $(OBJECT_FILES) $(HEADERS)
	$(CXX) $(LDFLAGS) $(OBJECT_FILES) $(HEADERS) -o $@

$(OBJECT_FILES): $(OBJECT_DIR)/%.o: %.cc 
	@if [ ! -d $(OBJECT_DIR) ]; then mkdir $(OBJECT_DIR); fi
	$(CXX) $(CFLAGS) $(LDFLAGS) $< -o $@


clean:
	@rm -f $(OBJECT_DIR)/*.o
	@echo make clean: done
