################################################################################
#
# Change history:
# Created: 25 March 2018 ; PASW
#

CPPFLAGS =	-std=c++11 -g -D_DEBUG -I../../inc 

OBJS =		matrix.o
OTHERSRCS =	invariant.h matrix.h


all:	$(OBJS) test_matrix

test_%: test_%.cpp $(OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $^ 

%.o:	%.cpp %.h $(OTHERSRCS)
	$(CXX) -c -o $@ $(CPPFLAGS) $<

clean:
	rm -f core *~ *~%~ *.o 

realclean:
	make clean ; rm -f test_matrix ; rm -rf test_matrix.dSYM
