OBJ_DIR= ../bin
OBJ_DEBUG_DIR = ../bin/Debug
H_DIR = ../include
SRC_DIR = .
IMG_DIR = ../imgui

MAIN = main.cpp


DYP_SRC = 	$(SRC_DIR)/app.cc \
		  	$(SRC_DIR)/game.cc \
			$(SRC_DIR)/window.cc \
		  	$(SRC_DIR)/button.cc \
			$(SRC_DIR)/region.cc \
			$(SRC_DIR)/unit.cc \
		  	$(SRC_DIR)/country.cc \
			$(SRC_DIR)/utilities.cc

IMG_SRC = 	$(IMG_DIR)/imgui.cpp \
			$(IMG_DIR)/imgui_draw.cpp \
			$(IMG_DIR)/imgui_widgets.cpp \
			$(IMG_DIR)/imgui_tables.cpp

IMG_BCK_SRC =	$(IMG_DIR)/backends/imgui_impl_sdl2.cpp \
				$(IMG_DIR)/backends/imgui_impl_opengl3.cpp

DYP_H = $(H_DIR)/app.h \
		$(H_DIR)/button.h \
		$(H_DIR)/country.h \
		$(H_DIR)/game.h	\
		$(H_DIR)/globals.h \
		$(H_DIR)/log.h \
		$(H_DIR)/region.h \
		$(H_DIR)/resources_manager.h \
		$(H_DIR)/text.h \
		$(H_DIR)/unit.h \
		$(H_DIR)/user.h \
		$(H_DIR)/utilities.h\
		$(H_DIR)/window.h

IMG_H = $(IMG_DIR)/imconfig.h \
		$(IMG_DIR)/imgui.h \
		$(IMG_DIR)/imgui_internal.h \
		$(IMG_DIR)/imstb_rectpack.h \
		$(IMG_DIR)/imstb_textedit.h \
		$(IMG_DIR)/imstb_truetype.h


DYP_OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(notdir $(DYP_SRC)))))
IMG_OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(notdir $(IMG_SRC)))))
IMG_BCK_OBJ =$(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(notdir $(IMG_BCK_SRC)))))

LINUX_GL_LIBS = -lGL

CXXFLAGS = -std=c++20 -I$(IMG_DIR) -I$(IMG_DIR)/backends -I$(H_DIR)
CXXFLAGS += -g -Wall -Wformat -Werror
LIBS =
LIBS =$(LINUX_GL_LIBS) -ldl `sdl2-config --libs` -lSDL2_image -lSDL2_ttf
CXXFLAGS += `sdl2-config --cflags`
CFLAGS = $(CXXFLAGS)


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(IMG_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(IMG_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

diplomacy.x: $(MAIN) $(DYP_OBJ) $(IMG_OBJ) $(IMG_BCK_OBJ)
	$(CXX) $(CXXFLAGS) $(MAIN) $(DYP_OBJ) $(IMG_OBJ) $(LIBS) -o $@


test:
	echo $(SRC) $(OBJ) $(HRS)

fix:
	sudo sysctl vm.mmap_rnd_bits=28

clean:
	@rm -f $(OBJ_DIR)/*.o
	@rm -f $(OBJ_DEBUG_DIR)/*.o
	@echo make clean: done
