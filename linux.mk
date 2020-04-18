TARGET = UsbDumper
RM = rm
RMFLAGS = -f -v
srcdir = .
prefix = /usr
exec_prefix = $(prefix)
srvdir = /etc/init.d
bindir = $(exec_prefix)/bin
mandir = $(prefix)/share/man
man1dir = $(mandir)/man1
INSTALL = install
INSTALL_PROGRAM = $(INSTALL) -m 0751 -v -C
INSTALL_DATA = $(INSTALL) -m 0644 -v -C

include general.mk

install: all
	$(INSTALL) -v -d "$(prefix)"
	$(INSTALL) -v -d "$(exec_prefix)"
	$(INSTALL) -v -d "$(bindir)"
	$(INSTALL) -v -d "$(mandir)"
	$(INSTALL) -v -d "$(man1dir)"
	
	$(INSTALL_PROGRAM) "$(srcdir)/$(TARGET)" "$(bindir)"
	-$(INSTALL_PROGRAM) "$(srcdir)/install/$(TARGET)" "$(srvdir)"

	if ! [ -f "$(srcdir)/doc/$(TARGET).1.gz" ] ; \
	then \
		gzip "$(srcdir)/doc/$(TARGET).1" ; \
	fi;

	-$(INSTALL_DATA) "$(srcdir)/doc/$(TARGET).1.gz" "$(man1dir)"
	-systemctl daemon-reload
	-$(srvdir)/$(TARGET) restart
	-systemctl enable $(TARGET)


uninstall:
	-$(RM) $(RMFLAGS) "$(bindir)/$(TARGET)"
	-$(RM) $(RMFLAGS) "$(man1dir)/$(TARGET).1.gz"
	-$(RM) $(RMFLAGS) "$(srvdir)/$(TARGET)"

.PHONY: install uninstall
.SILENT: uninstall
