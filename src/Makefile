OBJ_DIR= ../bin
OBJ_DEBUG_DIR = ../bin/Debug
H_DIR = ../include
SRC_DIR = .
IMG_DIR = ../imgui

MAIN = main.cpp
TEST = imgui_test.cpp

DYP_SRC = 	$(SRC_DIR)/app.cpp \
		  	$(SRC_DIR)/game.cpp \
			$(SRC_DIR)/window.cpp \
		  	$(SRC_DIR)/button.cpp \
			$(SRC_DIR)/region.cpp \
			$(SRC_DIR)/unit.cpp \
		  	$(SRC_DIR)/country.cpp \
			$(SRC_DIR)/utilities.cpp \
			$(SRC_DIR)/devel_tool.cpp \
			$(SRC_DIR)/sdl_wrap.cpp

IMG_SRC = 	$(IMG_DIR)/imgui.cpp \
			$(IMG_DIR)/imgui_demo.cpp \
			$(IMG_DIR)/imgui_draw.cpp \
			$(IMG_DIR)/imgui_tables.cpp \
			$(IMG_DIR)/imgui_widgets.cpp


IMG_BCK_SRC =	$(IMG_DIR)/backends/imgui_impl_sdl2.cpp \
				$(IMG_DIR)/backends/imgui_impl_opengl3.cpp

DYP_H = $(H_DIR)/app.hpp \
		$(H_DIR)/button.hpp \
		$(H_DIR)/country.hpp \
		$(H_DIR)/game.hpp	\
		$(H_DIR)/globals.hpp \
		$(H_DIR)/log.hpp \
		$(H_DIR)/region.hpp \
		$(H_DIR)/resources_manager.hpp \
		$(H_DIR)/text.hpp \
		$(H_DIR)/unit.hpp \
		$(H_DIR)/user.hpp \
		$(H_DIR)/utilities.hpp\
		$(H_DIR)/window.hpp

IMG_H = $(IMG_DIR)/imconfig.h \
		$(IMG_DIR)/imgui.h \
		$(IMG_DIR)/imgui_internal.h \
		$(IMG_DIR)/imstb_rectpack.h \
		$(IMG_DIR)/imstb_textedit.h \
		$(IMG_DIR)/imstb_truetype.h


DYP_OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(notdir $(DYP_SRC)))))
IMG_OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(notdir $(IMG_SRC)))))
IMG_BCK_OBJ =$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(notdir $(IMG_BCK_SRC)))))

DYP_DEBUG_OBJ     = $(addprefix $(OBJ_DEBUG_DIR)/, $(addsuffix .o, $(basename $(notdir $(DYP_SRC)))))
IMG_DEBUG_OBJ     = $(addprefix $(OBJ_DEBUG_DIR)/, $(addsuffix .o, $(basename $(notdir $(IMG_SRC)))))
IMG_BCK_DEBUG_OBJ = $(addprefix $(OBJ_DEBUG_DIR)/, $(addsuffix .o, $(basename $(notdir $(IMG_BCK_SRC)))))


LINUX_GL_LIBS = -lGL

CXXFLAGS = -std=c++20 -I$(IMG_DIR) -I$(IMG_DIR)/backends -I$(H_DIR)
CXXFLAGS += -Wall -Wformat -Werror -fsanitize=address
LIBS =
LIBS =$(LINUX_GL_LIBS) -ldl `sdl2-config --libs` -lSDL2_image -lSDL2_ttf
CXXFLAGS += `sdl2-config --cflags`
CFLAGS = $(CXXFLAGS)
CXX = g++

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(IMG_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(IMG_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DEBUG_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -g -D DEBUG $(CXXFLAGS) -c -o $@ $<

$(OBJ_DEBUG_DIR)/%.o: $(IMG_DIR)/%.cpp
	$(CXX) -g -D DEBUG $(CXXFLAGS) -c -o $@ $<

$(OBJ_DEBUG_DIR)/%.o: $(IMG_DIR)/backends/%.cpp
	$(CXX) -g -D DEBUG $(CXXFLAGS) -c -o $@ $<


diplomacy.x: $(MAIN) $(DYP_OBJ) $(IMG_OBJ) $(IMG_BCK_OBJ)
	$(CXX) $(CXXFLAGS) $(MAIN) $(DYP_OBJ) $(IMG_OBJ) $(IMG_BCK_OBJ) $(LIBS) -o $@

diplomacy_debug.x: $(MAIN) $(DYP_OBJ) $(IMG_OBJ) $(IMG_BCK_OBJ)
	$(CXX) -g -D DEBUG $(CXXFLAGS) $(MAIN) $(DYP_OBJ) $(IMG_OBJ) $(IMG_BCK_OBJ) $(LIBS) -o $@

imgui_test.x: $(TEST) $(DYP_DEBUG_OBJ) $(IMG_DEBUG_OBJ) $(IMG_BCK_DEBUG_OBJ) $(DEV_DEBUG_OBJ)
	$(CXX) -g -D DEBUG $(CXXFLAGS) $(TEST) $(DYP_DEBUG_OBJ) $(IMG_DEBUG_OBJ) $(IMG_BCK_DEBUG_OBJ) $(DEV_DEBUG_OBJ) $(LIBS) -o $@


fix:
	sudo sysctl vm.mmap_rnd_bits=28

clean:
	@rm -f $(OBJ_DIR)/*.o
	@rm -f $(OBJ_DEBUG_DIR)/*.o
	@echo make clean: done
