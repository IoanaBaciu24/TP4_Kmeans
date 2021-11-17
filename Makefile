#######################################
# Makefile PBM                        #
#                                     #
# E.B.                                #
#######################################


PROG = main

all : $(PROG)

# Variables for file compilation
CC        =  gcc
CFLAGS    =  -g -Wall
CPPFLAGS  =  -DDEBUG
LDFLAGS   =  -g -lm

#pxmtopxm : pxmtopxm.o Util.o

main : main.o ioUtils.o filteringUtils.o kmeans_utils.o
#colorfulboye: colorfulboye.o Util.o
#ppmtopgp: ppmtopgp.o Util.o

clean :
	@rm -f *.o

cleanall : clean
	@rm -f $(PROG)

