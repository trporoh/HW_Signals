binfirst := receiver
binsecond := sender
obj1 := sender.o
obj2 := receiver.o

all: $(binfirst) $(binsecond) 

$(binfirst): $(obj1) 
	gcc $< -o $(binfirst) -lpthread -lrt 

$(binsecond): $(obj2) 
	gcc $< -o $(binsecond) -lpthread -lrt 

%.o: %.c
	gcc -c $< -o $@ -g

clean:
	rm $(binfirst) $(obj1) $(binsecond) $(obj2)