QTDIR=/opt/qt5/

CC=g++
CCFLAGS=-g -std=c++11 -pedantic -Wall
INCLUDE=-I$(QTDIR)include/ -I$(QTDIR)include/QtCore -I$(QTDIR)include/QtWidgets -I$(QTDIR)include/QtGui 
DEFINES=-fPIC

LDFLAGS="-Wl,-rpath,/opt/qt5/lib"
LIBS=-L$(QTDIR)/lib -l Qt5Core -l Qt5Widgets -l Qt5Gui -lQt5PrintSupport

MOC=$(QTDIR)bin/moc
UID=$(QTDIR)bin/uic


UIS=preferences.ui propertiesDlg.ui randomgraph.ui \

OBJS=Linux/config.o \
     Linux/edge.o \
     Linux/graph.o \
     Linux/graphPropertiesDlg.o \
     Linux/main.o \
     Linux/node.o \
     Linux/preferences.o \
     Linux/pugixml.o \
     Linux/randomgraph.o \
     Linux/utility.o \
     Linux/graphDistroDlg.o \
     Linux/graphModelPropsDlg.o \
     Linux/matrixViewDlg.o \
     Linux/qcustomplot.o \
     Linux/widget.o

MOCS=Linux/moc_graphPropertiesDlg.o Linux/moc_preferences.o Linux/moc_randomgraph.o Linux/moc_graphDistroDlg.o \
     Linux/moc_graphModelPropsDlg.o Linux/moc_matrixViewDlg.o Linux/moc_qcustomplot.o Linux/moc_widgets.o

PROG=RandomGraph

$(PROG) : $(MOCS) $(OBJS)
	$(CC) $(MOCS) $(OBJS) $(LDFLAGS) $(LIBS) -o $(PROG)

all: clean $(PROG)


Linux/moc_graphPropertiesDlg.o : graphPropertiesDlg.h
	$(MOC) graphPropertiesDlg.h -o Linux/moc_graphPropertiesDlg.cpp
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) Linux/moc_graphPropertiesDlg.cpp -o Linux/moc_graphPropertiesDlg.o

Linux/moc_preferences.o : preferences.h
	$(MOC) preferences.h -o Linux/moc_preferences.cpp
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) Linux/moc_preferences.cpp -o Linux/moc_preferences.o

Linux/moc_randomgraph.o : randomgraph.h
	$(MOC) randomgraph.h -o Linux/moc_randomgraph.cpp
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) Linux/moc_randomgraph.cpp -o Linux/moc_randomgraph.o

Linux/moc_graphDistroDlg.o : graphDistroDlg.h
	$(MOC) graphDistroDlg.h -o Linux/moc_graphDistroDlg.cpp
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) Linux/moc_graphDistroDlg.cpp -o Linux/moc_graphDistroDlg.o

Linux/moc_graphModelPropsDlg.o : graphModelPropsDlg.h
	$(MOC) graphModelPropsDlg.h -o Linux/moc_graphModelPropsDlg.cpp
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) Linux/moc_graphModelPropsDlg.cpp -o Linux/moc_graphModelPropsDlg.o

Linux/moc_matrixViewDlg.o : matrixViewDlg.h
	$(MOC) matrixViewDlg.h -o Linux/moc_matrixViewDlg.cpp
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) Linux/moc_matrixViewDlg.cpp -o Linux/moc_matrixViewDlg.o

Linux/moc_qcustomplot.o : qcustomplot.h
	$(MOC) qcustomplot.h -o Linux/moc_qcustomplot.cpp
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) Linux/moc_qcustomplot.cpp -o Linux/moc_qcustomplot.o

Linux/moc_widgets.o : widgets.h    
	$(MOC)  widgets.h -o Linux/moc_widgets.cpp
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) Linux/moc_widgets.cpp -o Linux/moc_widgets.o

Linux/main.o : main.cpp 
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) main.cpp -o Linux/main.o

Linux/graph.o : graph.cpp graph.h
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) graph.cpp -o Linux/graph.o

Linux/config.o : config.cpp config.h
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) config.cpp -o Linux/config.o

Linux/edge.o : edge.cpp edge.h
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) edge.cpp -o Linux/edge.o

Linux/node.o : node.cpp node.h
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) node.cpp -o Linux/node.o

Linux/pugixml.o : pugixml.cpp pugixml.hpp pugiconfig.hpp
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) pugixml.cpp -o Linux/pugixml.o

Linux/preferences.o : preferences.cpp preferences.h
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) preferences.cpp -o Linux/preferences.o

Linux/graphPropertiesDlg.o : graphPropertiesDlg.cpp graphPropertiesDlg.h
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) graphPropertiesDlg.cpp -o Linux/graphPropertiesDlg.o

Linux/utility.o : utility.cpp utility.h
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) utility.cpp -o Linux/utility.o

Linux/randomgraph.o : randomgraph.cpp randomgraph.h
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) randomgraph.cpp -o Linux/randomgraph.o

Linux/graphDistroDlg.o : graphDistroDlg.cpp graphDistroDlg.h
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) graphDistroDlg.cpp -o Linux/graphDistroDlg.o

Linux/graphModelPropsDlg.o : graphModelPropsDlg.cpp graphModelPropsDlg.h
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) graphModelPropsDlg.cpp -o Linux/graphModelPropsDlg.o

Linux/matrixViewDlg.o : matrixViewDlg.cpp matrixViewDlg.h
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) matrixViewDlg.cpp -o Linux/matrixViewDlg.o

Linux/qcustomplot.o : qcustomplot.cpp qcustomplot.h
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) qcustomplot.cpp -o Linux/qcustomplot.o

Linux/widget.o : widget.cpp widgets.h
	$(CC) -c $(CCFLAGS) $(DEFINES) $(INCLUDE) widget.cpp -o Linux/widget.o


clean:
	rm -f Linux/moc_*
	rm -f Linux/*.o
	rm -f *.*~
	rm -f $(PROG)








