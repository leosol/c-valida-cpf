PROJECT_ROOT = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

OBJS = c-valida-cpf.o

#ifeq ($(BUILD_MODE),debug)
#CFLAGS += -g
#else ifeq ($(BUILD_MODE),run)
#CFLAGS += -O2
#else
#$(error Build mode $(BUILD_MODE) not supported by this Makefile)
#endif

all:	c-valida-cpf

c-valida-cpf:	$(OBJS)
	$(CXX) -o $@ $^

%.o:	$(PROJECT_ROOT)%.cpp
	$(CXX) -c $(CFLAGS) $(CXXFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	$(PROJECT_ROOT)%.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

clean:
	rm -fr c-valida-cpf $(OBJS)
