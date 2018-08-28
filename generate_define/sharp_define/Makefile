#sp_define Makefile

GCC=/usr/bin/gcc

PROJDIR=$(HOME)/temp/XmlEditor

MODULE = sp_define
OBJS = sp_define.o
CFLAG = -m32 -I/usr/include -I/usr/include/libxml2 -I$(PROJDIR)/include
D_CFLAG = -g -m32 -I/usr/include -I/usr/include/libxml2 -I$(PROJDIR)/include
LDIR = -m32 -L. -L/usr/lib -L$(PROJDIR)/lib
LLIB = -lxml2 -lpub_str_api

all: $(OBJS)
    ln -nfs  /usr/lib/libxml2.so.2.7.6 libxml2.so
    $(GCC) -o sp_define $(OBJS) $(LDIR) $(LLIB)

sp_define.o: sp_define.c
    $(GCC) -c -o sp_define.o sp_define.c $(D_CFLAG)

clean: $(OBJS)
    rm -rf $(OBJS)
    rm -rf $(MODULE).so
