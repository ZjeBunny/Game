TARGET = "Yahul Clicker.exe"
CXX = g++

WINDRES = windres

CXXFLAGS = -Iinclude -Isrc -Wall -std=c++20 -O2 -fno-ident
LDFLAGS = -lSDL3 -lSDL3_image -lSDL3_ttf -lsqlite3 -s -Wl,--strip-all -mwindows

SOURCES = ./src/main.cpp \
          ./src/include/Helpers.cpp \
          ./src/source/Game.cpp \
          ./src/source/GameSave.cpp \
          ./src/source/ui/GameMain.cpp \
          ./src/source/ui/GameMenu.cpp \
          ./src/source/ui/GamePause.cpp \
          ./src/source/ui/GameSettings.cpp

RES_OBJ = resource.o

all: $(TARGET)

$(RES_OBJ): src/resource.rc
	$(WINDRES) src/resource.rc -o $(RES_OBJ)

$(TARGET): $(RES_OBJ)
	$(CXX) $(SOURCES) $(RES_OBJ) $(CXXFLAGS) -o $(TARGET) $(LDFLAGS)

clean:
	del $(TARGET) $(RES_OBJ)
