# Makefile for mpLocators.c
# outputs plug.so

NO_TRANS_LINK = 

MAYA_LOCATION = /usr/autodesk/maya2008-x64

PLUGIN = plug.so

C++ = g++

CFLAGS = -DBits64_ -m64 -DUNIX -D_BOOL -DLINUX -DFUNCPROTO -D_GNU_SOURCE \
-DLINUX_64 -fPIC -fno-strict-aliasing -DREQUIRE_IOSTREAM -Wno-deprecated \
-O3 -Wall -Wno-multichar -Wno-comment -Wno-sign-compare -funsigned-char \
-Wno-reorder -fno-gnu-keywords -ftemplate-depth-25 -pthread

C++FLAGS = $(CFLAGS) $(WARNFLAGS) -Wno-deprecated -fno-gnu-keywords

INCLUDES = -I. -I.. -I$(MAYA_LOCATION)/include -I/usr/X11R6/include

LD = $(C++) $(NO_TRANS_LINK) $(C++FLAGS) -Wl,-Bsymbolic -shared

# Libraries and Objects
LIBS = -L$(MAYA_LOCATION)/lib -lOpenMaya -lOpenMayaAnim -lOpenMayaUI

LIBS_GL_EXTRA = -lGL -lGLU

OBJECTS = plug.o \
	mpLocator.o\
	mpBox.o

# standard stuff: tells the make program how to deal with different file types

.SUFFIXES: .cpp .cc .o .so .c

.cc.o:
	$(C++) -c $(INCLUDES) $(C++FLAGS) $<

.cpp.o:
	$(C++) -c $(INCLUDES) $(C++FLAGS) $<


.cc.i:
	$(C++) -E $(INCLUDES) $(C++FLAGS) $*.cc > $*.i

.cc.so:
	-rm -f $@
	$(LD) -o $@ $(INCLUDES) $< $(LIBS)

.cpp.so:
	-rm -f $@
	$(LD) -o $@ $(INCLUDES) $< $(LIBS)

.o.so:
	-rm -f $@
	$(LD) -o $@ $< $(LIBS)


# replace "plug" with the actual name of your plugin.
# in this example, the source file is "plug.cpp".'

all: $(PLUGIN)

$(PLUGIN): $(OBJECTS)
	-rm -f $@
	$(LD) -o $@ $(OBJECTS) $(LIBS)

clean:
	-rm -f *.o

Clean:
	-rm -f *.o *.so *.bak

# this line installs the plugin into the maya directory.
# you could also just put it in your user maya directory, load it by hand, etc.
install: plug.so
	cp plug.so /home/marin.pendjurov/Desktop/plug.so
