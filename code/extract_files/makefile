# Project: extract_files

CPP  = g++.exe
OBJ  = main.o XMLParserPouillave.o
LIBS = -L"../libs_includes/zlib-1.2.3.win32/lib" -mwindows -lmingw32 -lzdll
INCS = -I"../libs_includes/zlib-1.2.3.win32/include"
BIN  = extract_files.exe
CXXFLAGS = $(INCS)


$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o "extract_files.exe" $(LIBS) $(CXXFLAGS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

XMLParserPouillave.o: XMLParserPouillave.cpp
	$(CPP) -c XMLParserPouillave.cpp -o XMLParserPouillave.o $(CXXFLAGS)
