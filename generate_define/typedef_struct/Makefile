#getDefStruct Makefile

MODULE = td_struct
OBJS = td_struct.o
CFLAG = -I/usr/include -I/usr/include/libxml2
D_CFLAG = -g -I/usr/include -I/usr/include/libxml2
LDIR = -L. -L/usr/lib
LLIB = -lxml2

all: $(OBJS) 
	ln -nfs  /usr/lib/libxml2.so.2.7.6 libxml2.so
	cc -m32 -o td_struct $(OBJS) $(LDIR) $(LLIB)

td_struct.o: td_struct.c
	cc -m32 -c -o td_struct.o td_struct.c $(D_CFLAG)

clean: 
	rm -rf $(OBJS)
	rm -rf $(MODULE)
