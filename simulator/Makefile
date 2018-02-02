
DUKTAPE = ../../duktape/lib/duktape/src
KK_SRC = ../src
KK_INCLUDE = ../include

LIBRARY = -L/usr/lib -lxml2
INCLUDE = -I../src -I/usr/include/libxml2 -I$(DUKTAPE) -I$(KK_INCLUDE) -I../lib
CFLAGS = -DKK_SIMULATOR
CPPFLAGS = -DKK_SIMULATOR -std=gnu++11 

OUTPUT = .
TARGET = $(OUTPUT)/libgame.a
OBJOUTPUT = ./objs


OBJECTS := $(OBJOUTPUT)/duktape.o $(OBJOUTPUT)/kk.o $(OBJOUTPUT)/kk-object.o \
	$(OBJOUTPUT)/kk-property.o $(OBJOUTPUT)/kk-event.o $(OBJOUTPUT)/kk-element.o \
	$(OBJOUTPUT)/kk-document.o $(OBJOUTPUT)/kk-app.o $(OBJOUTPUT)/kk-gl.o 

$(TARGET):$(OBJECTS)
	ar crv $(TARGET) $(OBJECTS)
 
$(OBJOUTPUT)/duktape.o:$(DUKTAPE)/duktape.c $(DUKTAPE)/duktape.h
	cc $(CFLAGS) $(INCLUDE) -c $(DUKTAPE)/duktape.c -o $(OBJOUTPUT)/duktape.o

$(OBJOUTPUT)/kk.o:$(KK_SRC)/kk.cpp $(KK_INCLUDE)/kk.h
	gcc $(CPPFLAGS) $(INCLUDE) -c $(KK_SRC)/kk.cpp -o $(OBJOUTPUT)/kk.o

$(OBJOUTPUT)/kk-object.o:$(KK_SRC)/kk-object.cpp $(KK_INCLUDE)/kk-object.h 
	gcc $(CPPFLAGS) $(INCLUDE) -c $(KK_SRC)/kk-object.cpp -o $(OBJOUTPUT)/kk-object.o

$(OBJOUTPUT)/kk-property.o:$(KK_SRC)/kk-property.cpp $(KK_INCLUDE)/kk-property.h 
	gcc $(CPPFLAGS) $(INCLUDE) -c $(KK_SRC)/kk-property.cpp -o $(OBJOUTPUT)/kk-property.o

$(OBJOUTPUT)/kk-event.o:$(KK_SRC)/kk-event.cpp $(KK_INCLUDE)/kk-event.h 
	gcc $(CPPFLAGS) $(INCLUDE) -c $(KK_SRC)/kk-event.cpp -o $(OBJOUTPUT)/kk-event.o

$(OBJOUTPUT)/kk-element.o:$(KK_SRC)/kk-element.cpp $(KK_INCLUDE)/kk-element.h 
	gcc $(CPPFLAGS) $(INCLUDE) -c $(KK_SRC)/kk-element.cpp -o $(OBJOUTPUT)/kk-element.o

$(OBJOUTPUT)/kk-document.o:$(KK_SRC)/kk-document.cpp $(KK_INCLUDE)/kk-document.h 
	gcc $(CPPFLAGS) $(INCLUDE) -c $(KK_SRC)/kk-document.cpp -o $(OBJOUTPUT)/kk-document.o

$(OBJOUTPUT)/kk-app.o:$(KK_SRC)/kk-app.cpp $(KK_INCLUDE)/kk-app.h 
	gcc $(CPPFLAGS) $(INCLUDE) -c $(KK_SRC)/kk-app.cpp -o $(OBJOUTPUT)/kk-app.o

$(OBJOUTPUT)/kk-gl.o:$(KK_SRC)/kk-gl.cpp $(KK_INCLUDE)/kk-gl.h 
	gcc $(CPPFLAGS) $(INCLUDE) -c $(KK_SRC)/kk-gl.cpp -o $(OBJOUTPUT)/kk-gl.o

clean:
	rm -rf $(OBJOUTPUT)/*.o $(TARGET) 
