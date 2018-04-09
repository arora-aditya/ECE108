################################################################################
#
# Change history:
# Created: 4 Jul 2017 ; PASW
# Updated: 24 Jan 2018 ; BROEHL
#

CPPFLAGS =	-std=c++11 -g -D_DEBUG -I../../inc -c

OBJS =		set.o
OTHERSRCS =	invariant.h tuple.h set.h


run:	test_set
	./test_set

test_%.o: test_%.cpp
	$(CXX) $(CPPFLAGS) -o $@ $^ 

test_%: test_%.o $(OBJS) ../Tuple/tuple.o
	$(CXX) $(LDFLAGS) -o $@ $^ 

%.o:	%.cpp %.h $(OTHERSRCS)
	$(CXX) -c -o $@ $(CPPFLAGS) $<

clean:
	rm -f core *~ *~%~ *.o 

realclean:
	make clean ; rm -f test_set;
