MEM_DIR?=./mem
INCLUDES += -I$(MEM_DIR)/include

MEM_OBJS:= \
	objs/mem_t.o

objs/mem_t.o: $(MEM_DIR)/src/mem_t.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c -o $@ $<;
