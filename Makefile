# Library directories
SDL_DIR := Libraries/SDL2
SDL_IMG_DIR := Libraries/SDL2_image
SDL_MIX_DIR := Libraries/SDL2_mixer
SDL_TTF_DIR := Libraries/SDL2_ttf
SQLITE_DIR := Libraries/SQLite3

# Source directory
SRC_DIR := Source

# Executable output directory
EXE_DIR := Executables

# Compiler and flags
CC := g++
LDFLAGS := -L$(SDL_DIR)/lib -L$(SDL_IMG_DIR)/lib -L$(SDL_MIX_DIR)/lib -L$(SDL_TTF_DIR)/lib
LIBS := -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# CHANGE: if more folders are added or deleted under "Source"
CFLAGS := -I$(SDL_DIR)/include -I$(SDL_IMG_DIR)/include -I$(SDL_MIX_DIR)/include -I$(SDL_TTF_DIR)/include -I$(SQLITE_DIR)/include -I$(SRC_DIR) \
	-I$(SRC_DIR)/physics -I$(SRC_DIR)/renderables -I$(SRC_DIR)/database -I$(SRC_DIR)/pages -I$(SRC_DIR)/creators -I$(SRC_DIR)/interfaces \
	-I$(SRC_DIR)/characters -I$(SRC_DIR)/animators

# CHANGE: if more folders are added or deleted under "Source" 
SUBSRC_CPP := -ISource/pages Source/*.cpp Source/renderables/*.cpp Source/physics/*.cpp Source/database/*.cpp Source/pages/*.cpp Source/creators/*.cpp\
	Source/interfaces/*.cpp Source/characters/*.cpp Source/animators/*.cpp

# Targets
all: SourceCompile ObjectLinking Clean

# Compiling everything in source to object file
SourceCompile: 
	$(CC) -c $(SUBSRC_CPP) $(CFLAGS) $(LDFLAGS) $(LIBS)
	del Main.o

# Linking all the objects. Sneaked the "Assets" folder in here so the file handler can load assets from this folder.
ObjectLinking:
	$(CC) $(CFLAGS) $(LDFLAGS) -IAssets -o $(EXE_DIR)/Play.exe $(SRC_DIR)/Main.cpp *.o $(EXE_DIR)/SQLite3.dll $(LIBS) 

# Delete all object files
Clean:	
	del *.o