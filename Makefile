MPICC=/home/leon3cs/mpich-install/bin/mpicc
MPIEXEC=/home/leon3cs/mpich-install/bin/mpiexec
DEPS=/home/leon3cs/mpich-install/include/mpi.h
SAMPLE1=helloworld_mpi_example
SAMPLE2=blocking_messages_example
SAMPLE3=non_blocking_messages_example
SAMPLE4=broadcast_example
SAMPLE5=scatter_example
SAMPLE6=reduce_example
SAMPLE7=estimate_pi

%.o: %.c $(DEPS)
	$(MPICC) -c -o $@ $<

all: $(SAMPLE1) $(SAMPLE2) $(SAMPLE3) $(SAMPLE4) $(SAMPLE5) $(SAMPLE6) $(SAMPLE7)
	
$(SAMPLE1): $(SAMPLE1).o
	$(MPICC) -o $(SAMPLE1) $(SAMPLE1).o

$(SAMPLE2): $(SAMPLE2).o
	$(MPICC) -o $(SAMPLE2) $(SAMPLE2).o
	
$(SAMPLE3): $(SAMPLE3).o
	$(MPICC) -o $(SAMPLE3) $(SAMPLE3).o
	
$(SAMPLE4): $(SAMPLE4).o
	$(MPICC) -o $(SAMPLE4) $(SAMPLE4).o
	
$(SAMPLE5): $(SAMPLE5).o
	$(MPICC) -o $(SAMPLE5) $(SAMPLE5).o
	
$(SAMPLE6): $(SAMPLE6).o
	$(MPICC) -o $(SAMPLE6) $(SAMPLE6).o
	
$(SAMPLE7): $(SAMPLE7).o
	$(MPICC) -o $(SAMPLE7) $(SAMPLE7).o -lm

exec_1:
	$(MPIEXEC) -n 5 ./$(SAMPLE1)
	
exec_2:
	$(MPIEXEC) -n 5 ./$(SAMPLE2)

exec_3:
	$(MPIEXEC) -n 5 ./$(SAMPLE3)

exec_4:
	$(MPIEXEC) -n 5 ./$(SAMPLE4)

exec_5:
	$(MPIEXEC) -n 5 ./$(SAMPLE5)

exec_6: 
	$(MPIEXEC) -n 5 ./$(SAMPLE6)

pi:
	$(MPIEXEC) -n 5 ./$(SAMPLE7)
	
clean:
	rm *.o 
	rm $(SAMPLE1) $(SAMPLE2) $(SAMPLE3) $(SAMPLE4) $(SAMPLE5) $(SAMPLE6) $(SAMPLE7)