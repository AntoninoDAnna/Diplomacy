OBJ_DIR= ../bin
OBJ_DEBUG_DIR = ../bin/Debug


HDIR = ../include

APP_DIR = ./app
CORE_DIR = ./core
IMG_DIR = ../imgui

MAIN = main.cpp

DYP_SRC=$(APP_DIR)/app.cpp \
	$(APP_DIR)/game.cpp \
	$(CORE_DIR)/window.cpp \
	$(CORE_DIR)/button.cpp \
	$(APP_DIR)/region.cpp \
	$(APP_DIR)/unit.cpp \
	$(APP_DIR)/country.cpp \
	$(CORE_DIR)/utilities.cpp \
	$(APP_DIR)/devel_tool.cpp \
	$(CORE_DIR)/sdl_wrap.cpp \
	$(CORE_DIR)/color.cpp

IMG_SRC = 	$(IMG_DIR)/imgui.cpp \
		$(IMG_DIR)/imgui_demo.cpp \
		$(IMG_DIR)/imgui_draw.cpp \
		$(IMG_DIR)/imgui_tables.cpp \
		$(IMG_DIR)/imgui_widgets.cpp


IMG_BCK_SRC =	$(IMG_DIR)/backends/imgui_impl_sdl2.cpp \
		$(IMG_DIR)/backends/imgui_impl_sdlrenderer2.cpp

CORE_HDIR = $(HDIR)/core
APP_HDIR  = $(HDIR)/app

DYP_H = $(APP_HDIR)/app.hpp \
	$(CORE_HDIR)/button.hpp \
	$(APP_HDIR)/country.hpp \
	$(APP_HDIR)/game.hpp	\
	$(APP_HDIR)/globals.hpp \
	$(CORE_HDIR)/log.hpp \
	$(APP_HDIR)/region.hpp \
	$(CORE_HDIR)/manager.hpp \
	$(CORE_HDIR)/text.hpp \
	$(APP_HDIR)/unit.hpp \
	$(CORE_HDIR)/utilities.hpp\
	$(CORE_HDIR)/window.hpp

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

IMG_IMPL = #-DIMGUI_IMPL_OPENGL_ES3


LINUX_GL_LIBS = #-lGL

CXXFLAGS = -std=c++20 -I$(IMG_DIR) -I$(IMG_DIR)/backends -I$(HDIR)/app -I$(HDIR)/core
CXXFLAGS += `sdl2-config --cflags` -Wall -Wformat -Werror -fsanitize=address 
LIBS =
LIBS =$(LINUX_GL_LIBS) -ldl `sdl2-config --libs` -lSDL2_image -lSDL2_ttf
CFLAGS = $(CXXFLAGS)
CXX = g++

diplomacy.x: $(MAIN) $(DYP_OBJ) $(IMG_OBJ) $(IMG_BCK_OBJ)
	$(CXX) $(IMG_IMPL) $(CXXFLAGS) $(MAIN) $(DYP_OBJ) $(IMG_OBJ) $(IMG_BCK_OBJ) $(LIBS) -o $@

diplomacy_debug.x: $(MAIN) $(DYP_DEBUG_OBJ) $(IMG_DEBUG_OBJ) $(IMG_BCK_DEBUG_OBJ)
	$(CXX) -g -DDEBUG $(IMG_IMPL) $(CXXFLAGS) $(MAIN) $(DYP_DEBUG_OBJ) $(IMG_DEBUG_OBJ) $(IMG_BCK_DEBUG_OBJ) $(LIBS) -o $@

imgui_test.x: $(TEST) $(DYP_DEBUG_OBJ) $(IMG_DEBUG_OBJ) $(IMG_BCK_DEBUG_OBJ) $(DEV_DEBUG_OBJ)
	$(CXX) -g -DDEBUG $(IMG_IMPL) $(CXXFLAGS) $(TEST) $(DYP_DEBUG_OBJ) $(IMG_DEBUG_OBJ) $(IMG_BCK_DEBUG_OBJ) $(DEV_DEBUG_OBJ) $(LIBS) -o $@


$(OBJ_DIR)/%.o: $(APP_DIR)/%.cpp $(OBJ_DIR)
	$(CXX) $(IMG_IMPL) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(CORE_DIR)/%.cpp $(OBJ_DIR)
	$(CXX) $(IMG_IMPL) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(IMG_DIR)/%.cpp $(OBJ_DIR)
	$(CXX) $(IMG_IMPL) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(IMG_DIR)/backends/%.cpp $(OBJ_DIR)
	$(CXX) $(IMG_IMPL) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DEBUG_DIR)/%.o: $(SRC_DIR)/%.cpp $(OBJ_DEBUG_DIR)
	$(CXX) -g -DDEBUG $(IMG_IMPL) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DEBUG_DIR)/%.o: $(IMG_DIR)/%.cpp $(OBJ_DEBUG_DIR)
	$(CXX) -g -DDEBUG $(IMG_IMPL) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DEBUG_DIR)/%.o: $(IMG_DIR)/backends/%.cpp $(OBJ_DEBUG_DIR)
	$(CXX) -g -DDEBUG $(IMG_IMPL) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR):
	@ mkdir $(OBJ_DIR)

$(OBJ_DEBUG_DIR): $(OBJ_DIR)
	@ mkdir $(OBJ_DEBUG_DIR)
	@ mkdir $(OBJ_DIR)/log
fix:
	sudo sysctl vm.mmap_rnd_bits=28

clean:
	@ rm -rf $(OBJ_DIR)
	@ rm -f $(SRC_DIR)/*.x
	@echo make clean: done
