################################################################################
#
# Change history:
# Created: 4 Jul 2017 ; PASW
#

CPPFLAGS =	-std=c++11 -g -D_DEBUG -I../../inc 

OBJS =		tuple.o
OTHERSRCS =	invariant.h tuple.h


all:	$(OBJS) test_tuple

test_%: test_%.cpp $(OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $^ 

%.o:	%.cpp %.h $(OTHERSRCS)
	$(CXX) -c -o $@ $(CPPFLAGS) $<

clean:
	rm -f core *~ *~%~ *.o 

realclean:
	make clean ; rm -f test_tuple
