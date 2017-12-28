# Project: xml_optimizer

CPP  = g++.exe
OBJ  = main.o XMLParserPouillave.o
LIBS = -mwindows -lmingw32
INCS =
BIN  = xml_optimizer.exe
CXXFLAGS = $(INCS)


$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o "xml_optimizer.exe" $(LIBS) $(CXXFLAGS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

XMLParserPouillave.o: XMLParserPouillave.cpp
	$(CPP) -c XMLParserPouillave.cpp -o XMLParserPouillave.o $(CXXFLAGS)
