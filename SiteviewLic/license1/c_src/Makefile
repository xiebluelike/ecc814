.SUFFIXES: .o .c 
CC=gcc


MAGICKWAND_SHARED_LIBADD = -Wl,-rpath,/usr/local/lib -L/usr/local/lib -Wl,-rpath,/usr/local/lib -L/usr/local/lib  
#MAGICKWAND_SHARED_LIBADD = -Wl,-rpath,/usr/local/lib -L/usr/local/lib -lMagickWand -Wl,-rpath,/usr/local/lib -L/usr/local/lib  -lMagickWand 
MAGICK_INCLUDES = 
#MAGICK_INCLUDES = -I/include/ImageMagick -I/usr/local/include/ImageMagick 
# Erlang

ERL_INCLUDE = -I/usr/lib/erlang/usr/include 
ERL_LIBS    = -L/usr/lib/erlang/usr/lib \
              -lerts
EI_INCLUDE  = -I/usr/lib/erlang/lib/erl_interface-3.6.4/include
EI_LIBS     = -L/usr/lib/erlang/lib/erl_interface-3.6.4/lib \
              -lei \
              -lerl_interface

TARGET_LIB = license_drv.so

ALL: $(TARGET_LIB)

.c.o:
	$(CC) $(CFLAGS) $(ERL_INCLUDE) $(EI_INCLUDE) $(MAGICK_INCLUDES) -c $<


license_drv.so: license_drv.o mac.o base64.o commons.o liclib.o sysinfo.o des.o cpuid.o md5.o
##license_drv.so: license_drv.o 
	$(CC) -o $@ $^ $(ERL_LIBS) $(EI_LIBS) $(MAGICKWAND_SHARED_LIBADD) -fpic -shared  -lcrypto
	cp license_drv.so ../priv/lib 
	mv license_drv.so ../../../priv/lib 
	rm -f *.o 

clean:
	rm -f *.o *.so
