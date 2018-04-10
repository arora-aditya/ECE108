################################################################################
#
# Change history:
# Created: 25 March 2018 ; PASW
#

CPPFLAGS = -std=c++11 -g -D_DEBUG -I../../inc -Wall -Werror

OBJS =		../Matrix/matrix.o ../Tasks/tasks.o ../Tasks/task.o
OTHERSRCS =	invariant.h matrix.h tasks.h

run: critical
	./critical ../../PSF/sampleProject.psf

all:	$(OBJS) critical

critical: critical.cpp $(OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $^

../Matrix/matrix.o:
	cd ../Matrix ; make

../Tasks/tasks.o:
	cd ../Tasks ; make

%.o:	%.cpp %.h $(OTHERSRCS)
	$(CXX) -c -o $@ $(CPPFLAGS) $<

clean:
	rm -f core *~ *~%~ *.o 

realclean:
	make clean ; rm -f critical ; rm -rf critical.dSYM ; cd ../Matrix ; make realclean ; cd ../Tasks ; make realclean
