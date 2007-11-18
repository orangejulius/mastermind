.SUFFIXES: .cc .o
APP=proj03
LIBS=# -lpthread
GCC=g++ -Wall -O3 -ffast-math -fomit-frame-pointer -march=native ${INCLUDE}

SRCS:= $(wildcard *.cc)
OBJS=${SRCS:.cc=.o}


${APP}: ${OBJS}
	${GCC} -o $@ ${OBJS} ${LIBS}

.cc.o:
	${GCC} -c $<

clean:
	rm -rf *.o ${APP}
depend:
	makedepend ${SRCS}
# DO NOT DELETE

agent.o: agent.h environment.h state.h
environment.o: environment.h state.h
main.o: agent.h environment.h state.h
state.o: state.h
