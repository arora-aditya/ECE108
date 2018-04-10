################################################################################
#
# Change history:
# Created: 25 March 2018 ; PASW
#

CPPFLAGS =	-std=c++11 -g -D_DEBUG -I../../inc

OBJS =		task.o tasks.o ../Matrix/matrix.o
OTHERSRCS =	invariant.h task.o matrix.h tasks.h


all:	$(OBJS) test_tasks

test_%: test_%.cpp $(OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $^

%.o:	%.cpp %.h $(OTHERSRCS)
	$(CXX) -c -o $@ $(CPPFLAGS) $<

clean:
	rm -f core *~ *~%~ *.o

realclean:
	make clean ; rm -f test_tasks ; rm -rf test_tasks.dSYM
