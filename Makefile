# Source files & target
EXEC := redistricting
SRC  := redistricting.cxx
OBJ  := $(patsubst %.cxx,%.o,$(SRC))

# Options
FCC = icpc
FFLAGS = -O2 -axCORE-AVX512,MIC-AVX512

#Rules
$(EXEC): $(OBJ)
	$(FCC) $(FFLAGS) -o $@ $^
%.o: %.cxx
	$(FCC) $(FFLAGS) -c $<

#Useful phony targets
clean : neat
	$(RM) $(OBJ) $(EXEC) out.*
neat :
	$(RM) *~ .*~
echo :
	@echo $(OBJ)
