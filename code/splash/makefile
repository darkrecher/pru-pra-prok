# Project: splash

CPP  = g++.exe
OBJ  = main.o ImageZoomable.o ListOfImg.o SE_Square.o SE_Sprite.o MoviePlayer.o Scene.o ConfigInfos.o BufferScreens.o ImagePlayer.o DataLoader.o SoundPlayer.o MovieEvent.o ME_Scene_childrens.o ME_Scene.o ME_Sound.o ME_Sprite.o ME_Sprite_childrens.o SceneElt.o ChainListOfImg.o ME_BreakPoint.o PercentageBar.o ChainListOfSprite.o ChainListOf_ListOfImg.o ChainListOfMovieEvent.o ChainListOfSDLSurface.o ChainListOfSound.o XMLParser.o ConfigXMLParser.o ChainListOfProcedure.o FileLoader.o $(RES)
LIBS = -L"../libs_includes/SDL-devel-1.2.15-mingw32/SDL-1.2.15/lib" -L"../libs_includes/SDL_image-devel-1.2.12-VC/SDL_image-1.2.12/lib/x86" -L"../libs_includes/SDL_mixer-devel-1.2.12-VC/SDL_mixer-1.2.12/lib/x86" -L"../libs_includes/zlib-1.2.3.win32/lib" -mwindows -lmingw32 -lSDLmain -lSDL -lSDL_mixer -lSDL_image -lzdll
INCS = -I"../libs_includes/SDL-devel-1.2.15-mingw32/SDL-1.2.15/include/SDL" -I"../libs_includes/SDL_image-devel-1.2.12-VC/SDL_image-1.2.12/include" -I"../libs_includes/SDL_mixer-devel-1.2.12-VC/SDL_mixer-1.2.12/include" -I"../libs_includes/zlib-1.2.3.win32/include"
BIN  = splash.exe
CXXFLAGS = $(INCS)


$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o "splash.exe" $(LIBS) $(CXXFLAGS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

ImageZoomable.o: ImageZoomable.cpp
	$(CPP) -c ImageZoomable.cpp -o ImageZoomable.o $(CXXFLAGS)

ListOfImg.o: ListOfImg.cpp
	$(CPP) -c ListOfImg.cpp -o ListOfImg.o $(CXXFLAGS)

SE_Square.o: SE_Square.cpp
	$(CPP) -c SE_Square.cpp -o SE_Square.o $(CXXFLAGS)

SE_Sprite.o: SE_Sprite.cpp
	$(CPP) -c SE_Sprite.cpp -o SE_Sprite.o $(CXXFLAGS)

MoviePlayer.o: MoviePlayer.cpp
	$(CPP) -c MoviePlayer.cpp -o MoviePlayer.o $(CXXFLAGS)

Scene.o: Scene.cpp
	$(CPP) -c Scene.cpp -o Scene.o $(CXXFLAGS)

ConfigInfos.o: ConfigInfos.cpp
	$(CPP) -c ConfigInfos.cpp -o ConfigInfos.o $(CXXFLAGS)

BufferScreens.o: BufferScreens.cpp
	$(CPP) -c BufferScreens.cpp -o BufferScreens.o $(CXXFLAGS)

ImagePlayer.o: ImagePlayer.cpp
	$(CPP) -c ImagePlayer.cpp -o ImagePlayer.o $(CXXFLAGS)

DataLoader.o: DataLoader.cpp
	$(CPP) -c DataLoader.cpp -o DataLoader.o $(CXXFLAGS)

SoundPlayer.o: SoundPlayer.cpp
	$(CPP) -c SoundPlayer.cpp -o SoundPlayer.o $(CXXFLAGS)

MovieEvent.o: MovieEvent.cpp
	$(CPP) -c MovieEvent.cpp -o MovieEvent.o $(CXXFLAGS)

ME_Scene_childrens.o: ME_Scene_childrens.cpp
	$(CPP) -c ME_Scene_childrens.cpp -o ME_Scene_childrens.o $(CXXFLAGS)

ME_Scene.o: ME_Scene.cpp
	$(CPP) -c ME_Scene.cpp -o ME_Scene.o $(CXXFLAGS)

ME_Sound.o: ME_Sound.cpp
	$(CPP) -c ME_Sound.cpp -o ME_Sound.o $(CXXFLAGS)

ME_Sprite.o: ME_Sprite.cpp
	$(CPP) -c ME_Sprite.cpp -o ME_Sprite.o $(CXXFLAGS)

ME_Sprite_childrens.o: ME_Sprite_childrens.cpp
	$(CPP) -c ME_Sprite_childrens.cpp -o ME_Sprite_childrens.o $(CXXFLAGS)

SceneElt.o: SceneElt.cpp
	$(CPP) -c SceneElt.cpp -o SceneElt.o $(CXXFLAGS)

ChainListOfImg.o: ChainListOfImg.cpp
	$(CPP) -c ChainListOfImg.cpp -o ChainListOfImg.o $(CXXFLAGS)

ME_BreakPoint.o: ME_BreakPoint.cpp
	$(CPP) -c ME_BreakPoint.cpp -o ME_BreakPoint.o $(CXXFLAGS)

PercentageBar.o: PercentageBar.cpp
	$(CPP) -c PercentageBar.cpp -o PercentageBar.o $(CXXFLAGS)

ChainListOfSprite.o: ChainListOfSprite.cpp
	$(CPP) -c ChainListOfSprite.cpp -o ChainListOfSprite.o $(CXXFLAGS)

ChainListOf_ListOfImg.o: ChainListOf_ListOfImg.cpp
	$(CPP) -c ChainListOf_ListOfImg.cpp -o ChainListOf_ListOfImg.o $(CXXFLAGS)

ChainListOfMovieEvent.o: ChainListOfMovieEvent.cpp
	$(CPP) -c ChainListOfMovieEvent.cpp -o ChainListOfMovieEvent.o $(CXXFLAGS)

ChainListOfSDLSurface.o: ChainListOfSDLSurface.cpp
	$(CPP) -c ChainListOfSDLSurface.cpp -o ChainListOfSDLSurface.o $(CXXFLAGS)

ChainListOfSound.o: ChainListOfSound.cpp
	$(CPP) -c ChainListOfSound.cpp -o ChainListOfSound.o $(CXXFLAGS)

XMLParser.o: XMLParser.cpp
	$(CPP) -c XMLParser.cpp -o XMLParser.o $(CXXFLAGS)

ConfigXMLParser.o: ConfigXMLParser.cpp
	$(CPP) -c ConfigXMLParser.cpp -o ConfigXMLParser.o $(CXXFLAGS)

ChainListOfProcedure.o: ChainListOfProcedure.cpp
	$(CPP) -c ChainListOfProcedure.cpp -o ChainListOfProcedure.o $(CXXFLAGS)

FileLoader.o: FileLoader.cpp
	$(CPP) -c FileLoader.cpp -o FileLoader.o $(CXXFLAGS)
