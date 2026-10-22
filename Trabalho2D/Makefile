CXX ?= g++
CXXFLAGS ?= -std=gnu++11 -Wall -Wextra
LDLIBS ?= -lfreeglut -lglu32 -lopengl32

TARGET := trabalhocg.exe
SOURCES := main.cpp configuracoes.cpp tinyxml2.cpp \
	source/barril.cpp source/inimigo.cpp source/jogador.cpp source/tiro.cpp
OBJECTS := $(SOURCES:.cpp=.o)
DEPS := $(OBJECTS:.o=.d)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MMD -MP -c -o $@ $<

-include $(DEPS)

clean:
	del /Q /F $(subst /,\,$(TARGET) $(OBJECTS) $(DEPS))
