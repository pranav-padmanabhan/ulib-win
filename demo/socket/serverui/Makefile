#
TOPDIR = ../../..
#
include $(TOPDIR)/make.inc

#
INCS = -I"$(TOPDIR)/inc"
LIBS = -L"$(TOPDIR)/lib" -luwin -lws2_32
CFLAGS +=
CXXFLAGS += -DBUILD_EXE -g

#
OBJ = server_ui_sock.o client_ui_sock.o
BIN = server_ui_sock.exe client_ui_sock.exe
RC  = sock.rc
RES = ${RC:.rc=.res}
#
HEADER =
#
all: $(BIN) 

#
server_ui_sock.exe : server_ui_sock.o $(RES)
	$(CXX) -o $@ $^ $(LIBS)
	cp -vf $@ $(BINDIR)/$@
#
client_ui_sock.exe : client_ui_sock.o $(RES)
	$(CXX) -o $@ $^ $(LIBS) -lgdi32
	cp -vf $@ $(BINDIR)/$@
 
#
.PHONY : test
test :
	@echo Please run by yourself.
#	$(WINE) $(BINDIR)/$(BIN)
    
#
clean :
	$(RM) ${OBJ} ${RES} ${BIN}
