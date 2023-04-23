include config.mk

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^
	$(CC) $(SFLAGS) *.c

main.o: listin.h is.h dirtoname.h mkdir.h \
		concat_name.h detect.h listin.o is.o \
		dirtoname.o mkdir.o concat_name.o detect.o

listin.o: listin.h is.h cp.h mkdir.h \
		  concat_name.h dirtoname.h \
		  is.o cp.o mkdir.o concat_name.o \
		  dirtoname.o

cp.o: cp.h

mkdir.o: mkdir.h

detect.o: config.h

clean: cleanobj

cleanobj:
	$(RM) $(RMFLAGS) $(OBJECTS)

cleanall: cleanobj
	$(RM) $(RMFLAGS) $(TARGET)
	$(RM) $(RMFLAGS) *.o *.s *.gch

.SILENT: clean cleanobj cleanall
.IGNORE: cleanobj cleanall
.PHONY: cleanobj cleanall
