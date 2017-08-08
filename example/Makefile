TEXTBIN :=getopt
LIBNAME :=getopt
SOURCES := Test.C

all:$(TEXTBIN)

clean:clear ;

clear:
	rm -rf $(TEXTBIN)

$(TEXTBIN):../../pf_ob/lib/lib$(LIBNAME).a Makefile $(SOURCES)
	set -e
	gcc $(SOURCES) -L ../../pf_ob/lib/ -l$(LIBNAME) -lstdc++ -o $(TEXTBIN)
	echo "+      Successfully generated test file $(shell pwd)/$(TEXTBIN)."
	echo "+"



