/*************************************************************************************************************
*  File    : randomgraph.h                                                                        
*                                                                                                    
*  Abstract: This is the declaration of the RandomGraph class, the class defining the main window, this class
*            is responsible for allowing the user to select a model to use, getting the necessary parameters
*            for teh model as well as displaying the model.  In addition to this, this class is responsible
*            for performing various house-keeping dutes.
*                                                                                                    
*  Signals :                                                                                         
*                                                                                                    
*  Slots   :                                                                                         
*                                                                                                    
*  Written : Created Jul 2016 (G.K.Huber)         
*************************************************************************************************************/
#ifndef RANDOMGRAPH_H
#define RANDOMGRAPH_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>

#include <string>

#include "common.h"

class CGraphItem;
class CGraph;
class CPropertiesDlg;
class CDistroDlg;


class RandomGraph : public QMainWindow
{
    Q_OBJECT

public:

    enum {ErdosRenyi=1, BarabasiAlbert=2, WattsStrogatz=3};

    RandomGraph(QWidget *parent = 0);
    ~RandomGraph();

    bool showLabels() {return m_bShowLabels;}
    static bool getConsoleState() {return m_isConsoleActive;}
    static void setConsoleState(bool state) {m_isConsoleActive = state;}
     

    QGraphicsScene* getScene() {return m_scene;}
    void clearDisto(); 


private slots:
    void onFileNew();
    void onFileOpen();
    void onFileSave();
    void onFileImport();
    void onFileExit();
    void onViewSummary();
    void onViewDMatrix();
    void onViewAMatrix();
    void onViewConsole(bool);
    void onViewStatusBar();
    void onViewToolbar();
    void onViewLabels();
    void onViewOptions();
    void onHelpAbout();
    void onHelpHelp();
    void onGenGraph();

private:
    void createActions();
    void createMenus();
    void createToolbars();
    void createStatusbar();

    void parseXMLFile();
    void configureView();

    void newErdosRenyi(int, float);
    void newBarabasiAlbert(int, int, int);
    void newWattsStrogatz(int, int, float);

    // menu actions
    QAction*    m_fileNew;
    QAction*    m_fileOpen;
    QAction*    m_fileSave;
    QAction*    m_fileImport;
    QAction*    m_fileExit;

    QAction*    m_viewSummary;
    QAction*    m_viewDMatrix;
    QAction*    m_viewAMatrix;
    QAction*    m_viewConsole;
    QAction*    m_viewStatusBar;
    QAction*    m_viewToolBar;
    QAction*    m_viewLabels;
    QAction*    m_viewOptions;

    QAction*    m_helpAbout;
    QAction*    m_helpHelp;

    // menu bars
    QMenu*      m_fileMenu;
    QMenu*      m_viewMenu;
    QMenu*      m_helpMenu;
    
    // tool bar elements...
    QToolBar*   m_mainToolbar;
    QAction*    m_newGraph;

    // status bar elements
    QStatusBar* m_statusBar;
    QLabel*     m_actionLabel;

    // view/scene elements
    QGraphicsView*      m_view;
    QGraphicsScene*     m_scene;

    // state variables
    static bool        m_isConsoleActive;
    std::string        m_fileName;
    bool               m_isDirty;
    CGraph*            m_pGraph;
    bool               m_bOptModifed;
    bool               m_bShowLabels;
    pModelProps        m_pModelProperties;                  // current model properties

    // persistant dialogs
    CPropertiesDlg*    m_pGraphProperties;
    CDistroDlg*        m_pGraphPropertiesDistro;
};

#endif // RANDOMGRAPH_H
