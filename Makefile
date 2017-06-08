EXE=fiji_workout
HCCBINDIR=/opt/rocm/hcc/bin

CXX = $(HCCBINDIR)/hcc
CXXFLAGS = $(shell $(HCCBINDIR)/hcc-config --cxxflags) -g
LDFLAGS = $(shell $(HCCBINDIR)/hcc-config --ldflags) -lhc_am

CXXFLAGS += -O3

OBJECTS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
DEPS =  $(patsubst %.o,%.d,$(OBJECTS))

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@
	$(CXX) -MM $(CXXFLAGS) $*.cpp -o $*.d

$(EXE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

isa: $(EXE)
	extractkernel -i $(EXE)
	rm *.bundle *.hsaco

clean:
	rm -f $(EXE) *.o *.d *~ *.bundle *.hsaco *.isa


-include $(DEPS)
