TARGET	= ./test

# -------------------------------------------------------------------------------------------

SOURCES = main.cpp AudioFile.cpp
HEADERS = AudioFile.h

# -------------------------------------------------------------------------------------------

CXX          = arm-linux-gnueabi-g++
CXX_FLAGS    = -c -Wall -Wextra -fno-permissive -std=c++0x  -marm -march=armv7-a $(COMMON_CXX_FLAGS) 
LINK_FLAGS   = -marm -march=armv7-a -pthread -lasound -lsndfile


OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(HEADERS) $(TARGET) Makefile
	rm -f $(OBJECTS)

$(TARGET): $(OBJECTS) $(HEADERS)  Makefile
	$(CXX) $(OBJECTS) $(LINK_FLAGS) $(API_LIBS) -o $@
	
.cpp.o: $(SOURCES)  $(HEADERS) 
	$(CXX) $(CXX_FLAGS) -c -o $@ $<

clean:
	rm -f $(TARGET)
	rm -f $(OBJECTS)
	rm -f *.bin
	rm -f *.result*
	
	
	