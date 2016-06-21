CC := g++ # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity
SRCDIR := src
BUILDDIR := build
TARGET := server
COSOGTKMM := `pkg-config gtkmm-3.0 --cflags --libs`
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall -Dcompiling_server -std=c++98
LIB := -lpthread -pthread -L lib -lBox2D -ltinyxml -llog4cpp
INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB) $(COSOGTKMM)"; $(CC) $^ -o $(TARGET) $(LIB) $(COSOGTKMM)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo $(CC) $(CFLAGS) $(INC) -c -o $@ $< $(COSOGTKMM)

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)
posta:
	@echo " $(RM) -r $(BUILDDIR)/main.o "; $(RM) -r $(BUILDDIR)/main.o	
	@echo "make -f s"; make -f s
	
# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean
