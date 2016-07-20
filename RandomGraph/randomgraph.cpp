#include "randomgraph.h"
#include "graph.h"
#include "utility.h"
#include "pugixml.hpp"
#include "graphPropertiesDlg.h"
#include "graphModelPropsDlg.h"
#include "graphDistroDlg.h"
#include "preferences.h"
#include "config.h"
#include "common.h"
#include "matrixViewDlg.h"


#include <QVariant>
#include <QWidget>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QHeaderView>
#include <QMainWindow>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QWidget>
#include <QFileDialog>
#include <QMessageBox>

#include <map>
#include <vector>

#include <time.h>

bool RandomGraph::m_isConsoleActive = false;


const int vpWidth = 1400;
const int vpHeigth = 800;



/*************************************************************************************************************
* Function: ctor
*
* Abstract: This function creates an instance of the RandomGraph class.  We setup the actions, menus,
*           toolbar and statusbar as well as building the graphics view and graphics scene.
*
* Params  : parent -- [in] pointer to the parent widget
*
* Returns : an instance of the RandomGraph class
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
RandomGraph::RandomGraph(QWidget *parent) : QMainWindow(parent), m_fileName(""), m_isDirty(false), m_pGraph(nullptr), m_bOptModifed(false), m_bShowLabels(true), m_pGraphProperties(nullptr)
{
    // set up graphicsview and scene...
    m_view = new QGraphicsView;
    m_scene = new QGraphicsScene(0, 0, vpWidth, vpHeigth, this);

    // configure default font and background color...
    configureView();

    // set up our main windoe ....
    m_view->setScene(m_scene);                               
    this->setCentralWidget(m_view);
    this->resize(1400, 800);
    
    // create our gui elemetns.
    createActions();
    createMenus();
    createToolbars();
    createStatusbar();

    // construct a new graph object..
    m_pGraph = new CGraph(this);
    m_pModelProperties = nullptr;

    // construct our persistant dialog object...
    m_pGraphProperties = new CPropertiesDlg(this);
    m_pGraphPropertiesDistro = new CDistroDlg(this);

    // potentially we will be generating random number...seed the generator here
    srand((unsigned)time(nullptr));
}



/*************************************************************************************************************
* Function: dtor 
*
* Abstract: 
*
* Params  : 
*
* Returns : 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
RandomGraph::~RandomGraph()
{

}



/*************************************************************************************************************
* Function: createActions
*
* Abstract: This function creates action objects associated with all menu and tool bar items
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void RandomGraph::createActions()
{
    m_fileNew = new QAction(tr("&New"), this);
    //fileNew->setIcon(QIcon(":/images/new.png);
    m_fileNew->setShortcut(QKeySequence::New);
    m_fileNew->setStatusTip(tr("Creates a new random graph"));
    connect(m_fileNew, SIGNAL(triggered()), this, SLOT(onFileNew()));

    m_fileOpen = new QAction(tr("&Open"), this);
    //fileOpen->setIcon(QIcon(":/images/open.png);
    m_fileOpen->setShortcut(QKeySequence::Open);
    m_fileOpen->setStatusTip(tr("Opens a data file"));
    connect(m_fileOpen, SIGNAL(triggered()), this, SLOT(onFileOpen()));

    m_fileSave = new QAction(tr("&Save"), this);
    //fileSave->setIcon(QIcon(":/images/save.png);
    m_fileSave->setShortcut(QKeySequence::Save);
    m_fileSave->setStatusTip(tr("Saves the current graph"));
    connect(m_fileSave, SIGNAL(triggered()), this, SLOT(onFileSave()));

    m_fileImport = new QAction(tr("Import"), this);
    //fileImport->setIcon(QIcon":/images/import.png");
    //fileImport->setShortcut(QKeySequence::Import);
    m_fileImport->setStatusTip(tr("Imports a graph defination from an XML file"));
    connect(m_fileImport, SIGNAL(triggered()), this, SLOT(onFileImport()));

    m_fileExit = new QAction(tr("e&Xit"), this);
    //fileExit->setIcon(QIcon(":/images/Exit.png);
    m_fileExit->setShortcut(QKeySequence::Quit);
    m_fileExit->setStatusTip(tr("Terminates the application"));
    //connect(fileExit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
    connect(m_fileExit, SIGNAL(triggered()), this, SLOT(onFileExit()));

    m_viewSummary = new QAction(tr("Summary"), this);
    //viewSummary->setIcon(QIcon(":/images/summary.png");
    //viewSummary->setShortcut(QKeySequence::Import);
    m_viewSummary->setStatusTip(tr("View the summary statistics for the graph"));
    connect(m_viewSummary, SIGNAL(triggered()), this, SLOT(onViewSummary()));
    
    m_viewDMatrix = new QAction(tr("Distance matrix"), this);
    //m_viewDMatrix->setICon(QIcon(":/imates/dmatrix.png");
    //m_viewDMatrix->setShortcut();
    m_viewDMatrix->setStatusTip(tr("view the distance matrix associated with this graph"));
    connect(m_viewDMatrix, SIGNAL(triggered()), this, SLOT(onViewDMatrix()));

    m_viewAMatrix = new QAction(tr("Adjacency matrix"), this);
    //m_viewDMatrix->setICon(QIcon(":/imates/amatrix.png");
    //m_viewDMatrix->setShortcut();
    m_viewAMatrix->setStatusTip(tr("view the adjacency matrix associated with this graph"));
    connect(m_viewAMatrix, SIGNAL(triggered()), this, SLOT(onViewAMatrix()));

    m_viewConsole = new QAction(tr("Console"), this);
    //viewConsole->setIcon(QIcon(":/images/console.png");
    //viewConsole->setShortcut(QKeySequence::Console);
    m_viewConsole->setCheckable(true);
    m_viewConsole->setStatusTip(tr("View the diagnostic console"));
    connect(m_viewConsole, SIGNAL(toggled(bool)), this, SLOT(onViewConsole(bool)));;
    
    m_viewStatusBar = new QAction(tr("Status Bar"), this);
    m_viewStatusBar->setCheckable(true);
    m_viewStatusBar->setChecked(true);
    m_viewStatusBar->setStatusTip(tr("Shows or hides the status bar"));
    connect(m_viewStatusBar, SIGNAL(toggled(bool)), this, SLOT(onViewStatusBar()));;

    m_viewToolBar = new QAction(tr("Tool Bar"), this);
    m_viewToolBar->setCheckable(true);
    m_viewToolBar->setChecked(true);
    m_viewToolBar->setStatusTip(tr("Shows or hides the main tool bar bar"));
    connect(m_viewToolBar, SIGNAL(toggled(bool)), this, SLOT(onViewToolbar()));;

    m_viewLabels = new QAction(tr("Node Labels"), this);
    m_viewLabels->setCheckable(true);
    m_viewLabels->setChecked(m_bShowLabels);
    m_viewLabels->setStatusTip(tr("Shows or hides the status bar"));
    connect(m_viewLabels, SIGNAL(toggled(bool)), this, SLOT(onViewLabels()));;

    m_viewOptions = new QAction(tr("Options"), this);
    //viewOptions->setIcon(QIcon(":/images/options.png");
    m_viewOptions->setShortcut(QKeySequence::Preferences);
    m_viewOptions->setStatusTip(tr("View and set user defined optiosn"));
    connect(m_viewOptions, SIGNAL(triggered()), this, SLOT(onViewOptions()));;

    m_helpAbout= new QAction(tr("About"), this);
    //viewOptions->setIcon(QIcon(":/images/About.png");
    //viewOptions->setShortcut(QKeySequence::Preferences);
    m_helpAbout->setStatusTip(tr("View about application information"));
    connect(m_helpAbout, SIGNAL(triggered()), this, SLOT(onHelpAbout()));;;

    m_helpHelp = new QAction(tr("Help"), this);
    //helpHelp->setIcon(QIcon(":/images/help.png");
    m_helpHelp->setShortcut(QKeySequence::HelpContents);
    m_helpHelp->setStatusTip(tr("View application specific help"));
    connect(m_helpHelp, SIGNAL(triggered()), this, SLOT(onHelpHelp()));;;
    
    // actions for toolbar specific command
     m_newGraph = new QAction(tr("new graph"), this);
     //m_newGraph->setShortcut(QKeySequence(ctrl + G));
     m_newGraph->setStatusTip(tr("generate a new random graph using current parameters"));
     connect(m_newGraph, SIGNAL(triggered()), this, SLOT(onGenGraph()));
}



/*************************************************************************************************************
* Function: createMenus
*
* Abstract: this function creates the various menus 
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void RandomGraph::createMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_fileNew);
    m_fileMenu->addAction(m_fileOpen);
    m_fileMenu->addAction(m_fileSave);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_fileImport);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_fileExit);

    m_viewMenu = menuBar()->addMenu(tr("&View"));
    m_viewMenu->addAction(m_viewSummary);
    m_viewMenu->addAction(m_viewAMatrix);
    m_viewMenu->addAction(m_viewDMatrix);
    m_viewMenu->addSeparator();
    m_viewMenu->addAction(m_viewConsole);
    m_viewMenu->addSeparator();
    m_viewMenu->addAction(m_viewStatusBar);
    m_viewMenu->addAction(m_viewToolBar);
    m_viewMenu->addAction(m_viewLabels);
    m_viewMenu->addSeparator();
    m_viewMenu->addAction(m_viewOptions);

    m_helpMenu = menuBar()->addMenu(tr("&Help"));
    m_helpMenu->addAction(m_helpAbout);
    m_helpMenu->addAction(m_helpHelp);
}



/*************************************************************************************************************
* Function: createToolbars()
*
* Abstract: This function creates the various toolbars used
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void RandomGraph::createToolbars()
{
    m_mainToolbar = addToolBar("&File");
    m_mainToolbar->addAction(m_fileNew);
    m_mainToolbar->addAction(m_fileOpen);
    m_mainToolbar->addAction(m_fileSave);
    m_mainToolbar->addSeparator();
    m_mainToolbar->addAction(m_fileImport);
    m_mainToolbar->addSeparator();
    m_mainToolbar->addAction(m_viewSummary);
    m_mainToolbar->addAction(m_viewAMatrix);
    m_mainToolbar->addAction(m_viewDMatrix);
    m_mainToolbar->addAction(m_viewConsole);
    m_mainToolbar->addAction(m_viewOptions);
    m_mainToolbar->addSeparator();
    m_mainToolbar->addAction(m_newGraph);
}



/*************************************************************************************************************
* Function: createStatusbar
*
* Abstract: This function creates the status bar
*
* Params  : void
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void RandomGraph::createStatusbar()
{
    m_actionLabel = new QLabel("                                                      ");
    (m_statusBar = statusBar())->addWidget(m_actionLabel);
}



/************************************************************************************************************
 * function: parseXMLFile
 *
 * abstract:  This function performs the actual parsing of an XML file containing a graph definition, and
 *            builds the required nodes and edges and adds them to a graph object.  The base schema for
 *            the XML file is:
 *
 *           <graph>
 *               <nodes  count=<num>>
 *                   <node> 
 *                       <node_id> id </node_id>
 *                       <node_label> label </node_label>
 *                       <x_loc> coordinate </x_loc>
 *                       <y_loc> coordiante </y_loc>
 *                   </node>
 *              </nodes>
 *              <edges count=num>
 *                 <edge directed=<bool>>
 *                    <id>id</id>
 *                    <label>label</label>
 *                    <src>node_id</src>
 *                    <dst>node_id</src>
 *                 </edge>
 *              </edges>
 *           </graph>
 *
 * input   :  
 *
 * returns :  
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void RandomGraph::parseXMLFile()
{
    pugi::xml_document     doc;

    if(nullptr == m_pGraph)
    {
        m_pGraph = new CGraph(this);
    }
    else
    {
        m_pGraph->clear();
    }

    pugi::xml_parse_result    result = doc.load_file(m_fileName.c_str());

    if(result)
    {
        pugi::xml_node nodes = doc.child("graph").child("nodes");
        // TODO : get node count

        for(pugi::xml_node node = nodes.first_child(); node; node = node.next_sibling())
        {
		  #ifdef __WIN32
            int nodeID = node.find_child([&node](const pugi::xml_node node){return (0 == strcmp(node.name(), "node_id"));}).text().as_int();
            std::string strLabel = node.find_child([&node](const pugi::xml_node node){return (0 == strcmp(node.name(), "node_label"));}).text().as_string();
            int Xloc = node.find_child([&node](const pugi::xml_node node){return (0 == strcmp(node.name(), "x_loc"));}).text().as_int();
            int Yloc = node.find_child([&node](const pugi::xml_node node){return (0 == strcmp(node.name(), "y_loc"));}).text().as_int();   
          #else
            int nodeID = node.find_child([=](const pugi::xml_node node){return (0 == strcmp(node.name(), "node_id"));}).text().as_int();
            std::string strLabel = node.find_child([=](const pugi::xml_node node){return (0 == strcmp(node.name(), "node_label"));}).text().as_string();
            int Xloc = node.find_child([=](const pugi::xml_node node){return (0 == strcmp(node.name(), "x_loc"));}).text().as_int();
            int Yloc = node.find_child([=](const pugi::xml_node node){return (0 == strcmp(node.name(), "y_loc"));}).text().as_int();  
          #endif
			
            CNode* pNewNode = m_pGraph->addNode(nodeID, strLabel, QPoint(Xloc, Yloc));
            pNewNode->addToScene(this);                                                            // add the node to emerging scene
        }

        pugi::xml_node edges = doc.child("graph").child("edges");
        for(pugi::xml_node gedge = edges.first_child(); gedge; gedge = gedge.next_sibling())
        {
		  #ifdef __win32
            // TODO : get attribute for edge, is it directed
            int srcID = gedge.find_child([&gedge](const pugi::xml_node node){return (0 == strcmp(node.name(), "src"));}).text().as_int();
            int dstID = gedge.find_child([&gedge](const pugi::xml_node node){return (0 == strcmp(node.name(), "dst"));}).text().as_int();
          #else
	        int srcID = gedge.find_child([=](const pugi::xml_node node){return (0 == strcmp(node.name(), "src"));}).text().as_int();
	        int dstID = gedge.find_child([=](const pugi::xml_node node){return (0 == strcmp(node.name(), "dst"));}).text().as_int();
          #endif
			
            CEdge* pNewEdge = m_pGraph->addEdge(srcID, dstID, false, "?");
            pNewEdge->addToScene(m_scene);
        }
        m_view->viewport()->update();
    }
    else
    {
        displayMsg("failed to parse XML file, error is: %s\n", result.description());
    }
}


/************************************************************************************************************
 * function: configureView
 *
 * abstract: configure the base properties of the view, particularly the font and background color used.  
 *           these values can be changed in the configuation settings.
 *
 * input   :  void
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void RandomGraph::configureView()
{
    // get the configured backgroun color...
    QColor   bkgColor = CConfig::getInstance()->getBkgColor();
    QBrush   bkgBrush(bkgColor);
    m_view->setBackgroundBrush(bkgBrush);

    // get the configured background font...
    QFont*   font = CConfig::getInstance()->getFont();
    m_view->setFont(*font);

    m_scene->setFont(*font);
}



/************************************************************************************************************
 * function: newErdosRenyi
 *
 * abstract: This function constructs a new random graph using the Erdos-Renyi model.  We construct n 
 *           vertices and then consider all possible edges between these n vertices.  We allow each edge in 
 *           the graph with a probability of P (i.e. if a randomly choosen number in the range [0,1] is 
 *           less than P we add that edge to the graph).
 *
 * input   :  void 
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
const float PI=3.1415926535897932384626433832795;
const float DEG2RAD=PI/180;
void RandomGraph::newErdosRenyi(int cntNodes, float edgeProb) 
{
    QPoint    graphCnt(vpWidth/2, vpHeigth/2); //graphCnt(330, 350);
    int       graphRadius = (vpHeigth/2)-40; //graphRadius = 290;
    float     deltaTheta = 360.0 / cntNodes;

    m_actionLabel->setText(QString("generating a %1 node graph by Erdos-Renyi model").arg(cntNodes));
    m_pGraph->setMethod("Erdos-Renyi");

    // generate the nodes and their locations....
    for(int ndx = 0; ndx < cntNodes; ndx++)
    {
        char      buf[4];

        // build the node label...
        sprintf(buf, "%02d", ndx);

        // calculate the initial location of nodes...
        QPoint    nodeLoc;
        nodeLoc.setX(graphCnt.x() + graphRadius * cos((ndx * deltaTheta)*DEG2RAD));
        nodeLoc.setY(graphCnt.y() + graphRadius * sin((ndx * deltaTheta)*DEG2RAD));
        
        CNode* pNode = m_pGraph->addNode(ndx, buf, nodeLoc);
        pNode->addToScene(this);
        
    }

    // generate the edges                                       
    for(int src = 0; src <= cntNodes-2; src++)                   
    {
        for(int dst = src + 1; dst <= cntNodes-1; dst++) 
        {
            double chance = ((double)rand()/(double)RAND_MAX);

            if(chance < edgeProb)
            {
                CEdge* pEdge = m_pGraph->addEdge(src, dst, false, "?");
                pEdge->addToScene(m_scene);
            }
        }
    }

    m_view->viewport()->update();
    if(nullptr != m_pGraphProperties)
    {
        m_pGraphProperties->setGraph(m_pGraph);
    }

    if(nullptr != m_pGraphPropertiesDistro)
    {
        m_pGraphPropertiesDistro->setGraph(m_pGraph);
    }
    m_isDirty = true;
}



/************************************************************************************************************
 * function: newBarabasiAlbert
 *
 * abstract: builds a random graph using the Barabasi-Albert model.  This model is:
 *              (a) start with a small, connected graph, this is m_0
 *              (b) add a node at a time, building m <= m_0 edges.  The probability of an edge going from the
 *                  node to an existing node, v_i, is P(v_i) = d(v_i) / sum d(v_i)
 *           doing this allowed for the possibility of lone verticies.  The problem is that we need to be 
 *           able to use a uniformly random number into a selection of a node, which has a non-uniform 
 *           distribution of degrees.  We do this via normalization.  We accomplish this via:
 *              (a) build a degree sequence of the node in the base graph for any step, we use 
 *                  std::pair<int, int> for this where the first value is the node id and the second is the 
 *                  current degree.
 *              (b) sort this sequence from low degree to high degree.
 *              (c) calculate the sum of the degrees, call it sumDeg.
 *              (c) generate a random number in the range 1....sumDeg.
 *              (d) pick the node to form an edge to.  This is done by assigning each node to a bin and 
 *                  seeing which bin the random number picked.  The bottom value of the bin is the partial 
 *                  sum of degrees up to the bin, and the top value is teh bottom value plus the degree of 
 *                  the node.
 *                  huh? say what??!!?
 *                  Suppose, our degree sequence is: 
 *                       ((0, 1),(5, 1),(6, 1),(7, 1),(9, 1),(1, 2),(2, 2),(4, 2),(3, 3),(8, 4))
 *                  thus our bins would look like:
 *                  +--------+--------+--------+
 *                  | bottom | top    | node   |
 *                  +--------+--------+--------+
 *                  |   0    |   1    |   0    |
 *                  +--------+--------+--------+
 *                  |   1    |   2    |   1    |
 *                  +--------+--------+--------+
 *                  |   2    |   3    |   2    |      so, if our roll was 15, we would look for the bin that 
 *                  +--------+--------+--------+      contains 15.  i.e.
 *                  |   3    |   4    |   3    |         bottom < roll <= top
 *                  +--------+--------+--------+      so we would choose the ninth bin, which corresponds to  
 *                  |   4    |   5    |   4    |      theninth node in the original graph and we make an edge 
 *                  +--------+--------+--------+      between the new node and the ninth node.
 *                  |   5    |   7    |   5    |
 *                  +--------+--------+--------+
 *                  |   7    |   9    |   6    |
 *                  +--------+--------+--------+
 *                  |   9    |  11    |   7    |
 *                  +--------+--------+--------+
 *                  |  11    |  14    |   8    |
 *                  +--------+--------+--------+
 *                  |  14    |  18    |   9    |
 *                  +--------+--------+--------+
 *
 * input   :  void
 *
 * returns :  void
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void RandomGraph::newBarabasiAlbert(int cntNodes, int toAdd, int edgesToAdd) 
{
    QPoint                            graphCnt(vpWidth/2, vpHeigth/2); //graphCnt(330, 350);
    int                               graphRadius = 200;
    float                             deltaTheta = 360.0 / cntNodes;

    m_actionLabel->setText(QString("generating a Barabasi-Albert model, from a %1 node seed graph").arg(cntNodes));
    m_pGraph->setMethod("Barabasi-Albert");

    // generate the nodes and their locations....
    for(int ndx = 0; ndx < cntNodes; ndx++)
    {
        char      buf[4];

        // build the node label...
        sprintf(buf, "%02d", ndx);

        // calculate the initial location of nodes...
        QPoint    nodeLoc;
        nodeLoc.setX(graphCnt.x() + graphRadius * cos((ndx * deltaTheta)*DEG2RAD));
        nodeLoc.setY(graphCnt.y() + graphRadius * sin((ndx * deltaTheta)*DEG2RAD));
        
        CNode* pNode = m_pGraph->addNode(ndx, buf, nodeLoc);
        pNode->addToScene(this);
    }

    m_pGraph->doKruskal(m_scene);       // build a random spanning tree from a complete graph of initial seed graph...
    
    // perform n iterations, adding a new node each time
    graphRadius *= 2;
    deltaTheta = 360.0 / toAdd;
    for(int ndx = 0; ndx < toAdd; ndx++)
    {
        int  newNodeNdx = ndx + cntNodes;
        char buf[4];

        // build the node label...
        sprintf(buf, "%02d", newNodeNdx);

        // calculate the initial location of nodes...
        QPoint    nodeLoc;
        nodeLoc.setX(graphCnt.x() + graphRadius * cos((30 + (ndx * deltaTheta))*DEG2RAD));
        nodeLoc.setY(graphCnt.y() + graphRadius * sin((30 + (ndx * deltaTheta))*DEG2RAD));

        CNode* pNode = m_pGraph->addNode(newNodeNdx, buf, nodeLoc);
        pNode->addToScene(this);

        // build a degree sequence of the current graph...
        std::vector<std::pair<int, int>>            degreeSequence;
        int graphOrder = m_pGraph->getOrder();
        int     sumDeg = 0;
        for(int nodeNdx = 0; nodeNdx < graphOrder-1; nodeNdx++)               // we subtract one so that we do not look at the node we just added.
        {    
            int degree = m_pGraph->getNodeDeg(nodeNdx);
            sumDeg += degree;
            degreeSequence.push_back(std::pair<int, int>(nodeNdx, degree));
        }
        int dsLen = degreeSequence.size();

        
        for(int edgeNdx = 0; edgeNdx < edgesToAdd; edgeNdx++)
        {
            std::vector<std::pair<int, int>>::iterator   dsIter;
            int    cumulativeDeg = 0;
            int roll = rand() % sumDeg + 1;                                        // roll is in range (0, sumDeg]

            // sort the degree sequence
            std::sort(degreeSequence.begin(), degreeSequence.end(), [](std::pair<int,int> lhs, std::pair<int,int> rhs)-> bool{return (lhs.second < rhs.second);});
            
            for(int dsNdx = 0; dsNdx < dsLen; dsNdx++)
            {
                int    bottomLimit = cumulativeDeg;
                int    topLimit = cumulativeDeg + degreeSequence.at(dsNdx).second;

                if((bottomLimit < roll) && (roll <= topLimit))                              // found our node...
                {
                    // add an edge between our new node and the choosen node...
                    CEdge* pEdge = m_pGraph->addEdge(newNodeNdx, degreeSequence.at(dsNdx).first, false, "?");
                    pEdge->addToScene(m_scene);

                    // update degree sequene and sumDeg
                    degreeSequence.at(dsNdx).second++;                                     // increase the degree of the choosen node
                    sumDeg += 1;                                                             // increase the sum of the degrees of the original graph...
                    break;
                }
                cumulativeDeg = topLimit;
            }
        }
    }

    // add graph to statistics window...
    m_view->viewport()->update();
    if(nullptr != m_pGraphProperties)
    {
        m_pGraphProperties->setGraph(m_pGraph);
    }

    if(nullptr != m_pGraphPropertiesDistro)
    {
        m_pGraphPropertiesDistro->setGraph(m_pGraph);
    }
    m_isDirty = true;
}



/************************************************************************************************************
 * function: newWattsStrogatz
 *
 * abstract: This function generates a new random graph using the Watts Strogatz model.  In this model we 
 *           connect a circular lattace of verticies and connect each vertex to the k/2 nearest neighbors 
 *           in a clockwise and counter-clockwise direction.  We then rewire each edge with a probability 
 *           P.  To do a rewiring of the edge (v_i,v_j) we move pick a new endpoint from the verticies 
 *           in the graph, with two restrictions: 
 *                    (a) we do not allow loops
 *                    (b) we do not allow multiple edges
 *
 * input   :  void 
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void RandomGraph::newWattsStrogatz(int cntNodes, int degree, float beta) 
{
    QPoint                            graphCnt(vpWidth/2, vpHeigth/2); //graphCnt(330, 350);
    int                               graphRadius = (vpHeigth/2)-40;
    float                             deltaTheta = 360.0 / cntNodes;
    std::vector<std::pair<int, int>>  edgeList;

    m_actionLabel->setText(QString("generating a %1 node graph by Watts-Strogatz model").arg(cntNodes));
    m_pGraph->setMethod("Watts-Strogatz");

    // generate the nodes and their locations....
    for(int ndx = 0; ndx < cntNodes; ndx++)
    {
        char      buf[4];

        // build the node label...
        sprintf(buf, "%02d", ndx);

        // calculate the initial location of nodes...
        QPoint    nodeLoc;
        nodeLoc.setX(graphCnt.x() + graphRadius * cos((ndx * deltaTheta)*DEG2RAD));
        nodeLoc.setY(graphCnt.y() + graphRadius * sin((ndx * deltaTheta)*DEG2RAD));
        
        CNode* pNode = m_pGraph->addNode(ndx, buf, nodeLoc);
        pNode->addToScene(this);
        
    }

    // build the initial edges as needed
    for(int ndx = 0; ndx < cntNodes; ndx++)
    {
        for(int jdx = 1/*-degree/2*/; jdx <= degree/2; jdx++)
        {
            int dstNode = jdx + ndx;

            if(dstNode >= cntNodes)
                dstNode -= cntNodes;                  // we need to loop around at the top end as well

            edgeList.push_back(std::pair<int, int>(ndx, dstNode));

        }
    }

    // preform rewiring
    std::vector<std::pair<int, int>>::iterator    vIter;
    vIter = edgeList.begin();
    while(edgeList.end() != vIter)
    {
        double chance = ((double)rand()/(double)RAND_MAX);                 // generate a random number [0,1)
        if(chance < beta)
        {
            int src = (*vIter).first;
            
            bool    isGood = true;
            do
            {
                // generate a random number in range [0, cntNodes)
                int tNode = rand() % cntNodes;

                // verify new node is valid
                if(tNode == src)                                           // disallow loop
                    isGood = false;
                else                                                       // check for edge duplication
                {
                    (*vIter).second = tNode;
                    isGood = true;
                }
            } while(!isGood);
        }  // end of rewire check

        // add edge to the scene...
        CEdge* pEdge = m_pGraph->addEdge((*vIter).first, (*vIter).second, false, "?");
        pEdge->addToScene(m_scene);
        ++vIter;
    }

    // add graph to statistics window...
    m_view->viewport()->update();
    if(nullptr != m_pGraphProperties)
    {
        m_pGraphProperties->setGraph(m_pGraph);
    }

    if(nullptr != m_pGraphPropertiesDistro)
    {
        m_pGraphPropertiesDistro->setGraph(m_pGraph);
    }
    m_isDirty = true;
}


////////////////////////////////////////////////////////////////////////////////////////////
// private slots
/************************************************************************************************************
 * function: onFileNew
 *
 * abstract: THis function responds to the File | New menu item.  In this function we perform the following
 *            (1) if the graph has not been saved, we prompt for the user to save it.
 *            (2) we clear the existing graph object as well as he display and scene
 *            (3) in instantiate a model property structure and initialize it, if needed
 *            (4) show the model properties dialog box to get the parameters of the model
 *            (5) call gengraph to generate the requested type of grapm.
 *
 * input   :  void
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void RandomGraph::onFileNew() 
{
    // if we have an existing graph model, delete it, and reset the scene...
    if(nullptr != m_pGraph)
    {
        if(m_isDirty)
        {
            if(QMessageBox::Yes == QMessageBox::question(this, "Save file", "The graph has been modified, do you wish to save?", QMessageBox::Yes | QMessageBox::No))
            {
                onFileSave();
            }
        }

        m_pGraph->clear();    
        m_scene->clear();
        (m_view->viewport())->update();
    }

    // if we do not have a model properties, creae one...
    if(m_pModelProperties == nullptr)
    {
        m_pModelProperties = new modelProps;
        memset((void*)m_pModelProperties, 0, sizeof(modelProps));
        m_pModelProperties->nModel = 0xff;
    }

    CModelPropsDlg             dlg(m_pModelProperties, this);
    if(QDialog::Accepted == dlg.exec())
    {
        // get the graph type and associate properties...
        int   modelType = dlg.getModelType();
        m_pModelProperties->nModel = modelType;

        // check to see if the clear check box is checked..
        if(dlg.doClear(modelType))
        {
            if(nullptr != m_pGraphProperties)
            {
                m_pGraphProperties->reset();
            }
        }

        switch(modelType)
        {
            case RandomGraph::ErdosRenyi:
                
                m_pModelProperties->cntNodes = dlg.getNodeCnt(modelType);
                m_pModelProperties->edgeProb = dlg.getEdgeProp(modelType);

                break;
            case RandomGraph::BarabasiAlbert:
                m_pModelProperties->cntNodes = dlg.getNodeCnt(modelType);
                m_pModelProperties->nodesToAdd = dlg.getNodesTooAdd(modelType);
            
            case RandomGraph::WattsStrogatz:
                m_pModelProperties->cntNodes = dlg.getNodeCnt(modelType);
                m_pModelProperties->beta = dlg.getBeta(modelType);
                m_pModelProperties->degree = dlg.getDegree(modelType);
            default:
                ;
        }
    }

    onGenGraph();

}



/*************************************************************************************************************
* Function: clearDisto
*
* Abstract: function to poke the distribution dialog to clear itsel
*
* Params  : void 
*
* Returns : void
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void RandomGraph::clearDisto()
{
    if(nullptr != m_pGraphPropertiesDistro)
        m_pGraphPropertiesDistro->clearData();
}



/************************************************************************************************************
 * function: onFileOpen
 *
 * abstract:  This function responds to the File | Open menu item.  We perfom the following actions:
 *              (1) prompt to save the existing file, if needed
 *              (2) show the open file dialog box to get the file name
 *              (3) clear the scene, display and the graph object
 *              (4) invoke the readFile function of the graph object to read the file.
 *
 *
 * input   :  void 
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void RandomGraph::onFileOpen()
{
    if(nullptr != m_pGraph)
    {
        if(m_isDirty)
        {
            onFileSave();
        }

        m_pGraph->clear();
        m_scene->clear();
        (m_view->viewport())->update();
    }
    else
    {
        m_pGraph = new CGraph(this);
    }

    QString  fileName = QFileDialog::getOpenFileName(this, "graph files", "./", "graph files (*.gph);; all files (*.*)", nullptr, QFileDialog::ReadOnly);
    if(!fileName.isNull())
    {
        m_pGraph->readFile(fileName);
    }
}                                                                                          



/************************************************************************************************************
 * function: onFileSave
 *
 * abstract:  This function responds to the File | Save menu item.  IF the graph needs saving, we prompt for
 *            the file to save it in, and then call the writeFile method of the graph object.
 *
 * input   :  void 
 *
 * returns :  
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void RandomGraph::onFileSave() 
{
    if(nullptr != m_pGraph)
    {
        if(m_isDirty)
        {
            QString defExt("graph files (*.gph)");
            QString fileName = QFileDialog::getSaveFileName(this, "graph files", "./", "graph files (*.gph);; all files (*.*)", &defExt);
            if(!fileName.isNull())
            {
                m_pGraph->writeFile(fileName);
            }
            m_isDirty = false;
        }
    }
}



/************************************************************************************************************
 * function: onFileInput
 *
 * abstract: This file inports a graph described in a simple XML-scheme.  The scheme is as follows:
 *
 *           <graph>
 *               <nodes  count=<num>>
 *                   <node> 
 *                       <node_id> id </node_id>
 *                       <node_label> label </node_label>
 *                       <x_loc> coordinate </x_loc>
 *                       <y_loc> coordiante </y_loc>
 *                   </node>
 *              </nodes>
 *              <edges count=num>
 *                 <edge directed=<bool>>
 *                    <id>id</id>
 *                    <label>label</label>
 *                    <src>node_id</src>
 *                    <dst>node_id</src>
 *                 </edge>
 *              </edges>
 *           </graph>
 *
 *           id is an integer field, label is a string field.
 *
 * input   :  nothing.
 *
 * returns : void, will set the member variable `fileName' to the file being opened 
 *
 * written : (G.K.Huber)                                                                                                
 ***********************************************************************************************************/
void RandomGraph::onFileImport() 
{
    QString    fileName;

    if(m_isDirty)
    {
        if(QMessageBox::Yes == QMessageBox::question(nullptr, "save graph", "do you wish to save this graph?", QMessageBox::Yes | QMessageBox::No))
        {
            this->onFileSave();
        }
    }

    // if we have an existing graph model, delete it, and reset the scene...
    if(nullptr != m_pGraph)
    {
        m_pGraph->clear();    
        m_scene->clear();
        (m_view->viewport())->update();
    }

    // get the file name to open
    fileName = QFileDialog::getOpenFileName(this, tr("Import Graph"), "./", tr("Graph Files (*.xml);;Text files (*.txt)"));
    m_pGraph->setMethod("import");

    if(!fileName.isNull())
    {
        m_actionLabel->setText(fileName);
        m_fileName = fileName.toStdString();

        parseXMLFile();
        m_pGraph->printGraph();
        if(nullptr != m_pGraphProperties)
        {
            m_pGraphProperties->setGraph(m_pGraph);
        }
        if(nullptr != m_pGraphPropertiesDistro)
        {
            m_pGraphPropertiesDistro->setGraph(m_pGraph);
        }
        m_isDirty = true;
    }
}



/*************************************************************************************************************
* Function: onFileExit
*
* Abstract: responds to the File | Exit menu item.  we check to see if the user wants the cofiguration saved
*           (if modified) and then exits the application
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void RandomGraph::onFileExit()
{
    if(m_bOptModifed)
    {
        int ret = QMessageBox::question(this, "save preferences", "preferences were modified, do you want to save them?", QMessageBox::Yes | QMessageBox::No);

        if(QMessageBox::Yes == ret)
        {
            CConfig::getInstance()->writeConfig();
        }
    }

    qApp->closeAllWindows();
}


/************************************************************************************************************
 * function: onViewSummary
 *
 * abstract: The function responds to the View | Summary menu item.  We instantiage both the graph properties
 *           dialog and the distribution dialog (if needed) and then show both of them modelessly.
 *
 * input   : void             
 *
 * returns : void                                                                                            
 *
 * written : (G.K.Huber)                                                                                           
 ***********************************************************************************************************/
void RandomGraph::onViewSummary()
{
    if(nullptr == m_pGraphProperties)
    {
        m_pGraphProperties = new CPropertiesDlg(this);
        m_pGraphProperties->setGraph(m_pGraph);
    }

    if(nullptr == m_pGraphPropertiesDistro)
    {
        m_pGraphPropertiesDistro = new CDistroDlg(this);
        m_pGraphPropertiesDistro->setGraph(m_pGraph);
    }

    if(!m_pGraphProperties->isVisible()) m_pGraphProperties->show();
    
    if(!m_pGraphPropertiesDistro->isVisible()) m_pGraphPropertiesDistro->show();
}



/*************************************************************************************************************
* Function: onViewAMatrix
*
* Abstract: This functions displays the viewMatrix dialog box, with the distance matrix loaded in it.  The
*           dialog is displayed modally. 
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void RandomGraph::onViewAMatrix()
{
    CMatrixViewDlg    dlg(this);

    dlg.setTitle("Adjacency");
    if(nullptr != m_pGraph)
    {
        dlg.setMatrix(m_pGraph->getAdjacencyMatrix(), m_pGraph->getOrder());
        dlg.exec();
    }
    else
    {
        QMessageBox::warning(nullptr, "Warning", "You need to load or generate a graph first", QMessageBox::Ok);
    }
}



/*************************************************************************************************************
* Function: onViewDmatrix 
*
* Abstract: This functions displays the viewMatrix dialog box, with the distance matrix loaded in it.  The
*           dialog is displayed modally.
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void RandomGraph::onViewDMatrix()
{
    CMatrixViewDlg    dlg(this);

    dlg.setTitle("Distance");
    if(nullptr != m_pGraph)
    {
        dlg.setMatrix(m_pGraph->getDistanceMatrix(), m_pGraph->getOrder());
        dlg.exec();
    }
    else
    {
        QMessageBox::warning(nullptr, "Warning", "You need to load or generate a graph first", QMessageBox::Ok);
    }
}



/************************************************************************************************************
 * function: onViewConsole
 *
 * abstract:  this function responds to the view | console menu item and, on windows, will cause a console
 *            terminal to be configured and displayed (or hidden).  THe console is designed for simple
 *            outpu.
 *
 * input   :  isChecked -- [in] boolean value that holds the checked state of the menu item prior to when
 *                         then menu item was selected
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void RandomGraph::onViewConsole(bool isChecked)
{
    if(isChecked)
    {
        showConsole();
        m_isConsoleActive = true;
    }
    else
    {
        hideConsole();
        m_isConsoleActive = false;
    }

}



/************************************************************************************************************
 * function: onViewStatusBar
 *
 * abstract: This function toggles viewing node labels on and off.  Note, that the `isChecked' function returns 
 *           the state after the menu item was clicked, and thus returns the new state of the item.  This means
 *           that if the menubar was visible (and the menu item checked), this function will return false because
 *           the visual state is changed on selecting the menu item.
 *
 * input   : void   
 *
 * returns : void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void RandomGraph::onViewStatusBar()
{
    bool state = m_viewStatusBar->isChecked();

    if(state)                                  // bar is currently visible
    {
        m_statusBar->show();

    }
    else
    {
        m_statusBar->hide();
    }
}




/************************************************************************************************************
 * function: onViewToolbar
 *
 * abstract: This function toggles viewing node labels on and off.  Note, that the `isChecked' function returns 
 *           the state after the menu item was clicked, and thus returns the new state of the item.  This means
 *           that if the toolbar was visible (and the menu item checked), this function will return false because
 *           the visual state is changed on selecting the menu item.
 *
 * input   : void   
 *
 * returns : void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void RandomGraph::onViewToolbar()
{
    bool state = m_viewToolBar->isChecked();

    if(state)                                  
    {
        m_mainToolbar->show();
    }
    else
    {
        m_mainToolbar->hide();
    }
}



/************************************************************************************************************
 * function: onViewLabels
 *
 * abstract: This function toggles viewing node labels on and off.  Note, that the `isChecked' function returns 
 *           the state after the menu item was clicked, and thus returns the new state of the item.  This means
 *           that if the nodes were visible (and the menu item checked), this function will return false because
 *           the visual state is changed on selecting the menu item.
 *
 * input   : void   
 *
 * returns : void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void RandomGraph::onViewLabels()
{
    bool state = m_viewLabels->isChecked();      // gets the state after the item was selected.

    if(state)                                  
    {
        m_bShowLabels = true;
    }
    else
    {
        m_bShowLabels = false;
    }

    // clear the scene and redraw as needed.
    m_scene->clear();
    m_pGraph->redrawGraph(m_scene);
    (m_view->viewport())->update(); 
}



/************************************************************************************************************
 * function: onViewOptions
 *
 * abstract:  THis function responds to the view | option menu item and displays the options dialog.
 *
 * input   :  void 
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void RandomGraph::onViewOptions()
{
    CDlgPreferences   dlg(this);

    if(QDialog::Accepted == dlg.exec())
    {
        configureView();

        m_scene->clear();
        m_pGraph->redrawGraph(m_scene);
        (m_view->viewport())->update();                  // update view as needed....

        m_bOptModifed = true;
    }
}



/*************************************************************************************************************
* Function: onHelpAbout
*
* Abstract: 
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void RandomGraph::onHelpAbout()
{
  QMessageBox::information(nullptr, "Information", "function not yet implimented", QMessageBox::Yes);
}



/*************************************************************************************************************
* Function: onHelpHelp
*
* Abstract: 
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void RandomGraph::onHelpHelp()
{
  QMessageBox::information(nullptr, "Information", "function not yet implimented", QMessageBox::Yes); 
}



/************************************************************************************************************
 * function: onGenGraph
 *
 * abstract: This function get the needed parameters (based on model type) from teh model property
 *           structure, and then calls the appropriate graph generation function
 *
 * input   :  
 *
 * returns :  
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void RandomGraph::onGenGraph()
{
    if(nullptr != m_pModelProperties)
    {
        int   modelType = m_pModelProperties->nModel;


        // if we have an existing graph model, delete it, and reset the scene...
        if(nullptr != m_pGraph)
        {
            m_pGraph->clear();
            m_scene->clear();
            (m_view->viewport())->update();
        }

        switch(modelType)
        {
            case ErdosRenyi:
            {
                int nodeCnt = m_pModelProperties->cntNodes;
                float edgeProb = m_pModelProperties->edgeProb;
                m_actionLabel->setText(QString("Generating Edros/Renyi graph with %1 nodea and %2 edge probability").arg(nodeCnt).arg(edgeProb));
                newErdosRenyi(nodeCnt, edgeProb);
            }
                break;

            case BarabasiAlbert:
            {
                int nodeCnt = m_pModelProperties->cntNodes;
                int toAdd = m_pModelProperties->nodesToAdd;
                m_actionLabel->setText(QString("Generating Barabasi/Albert graph starting with %1 nodea and adding %2 nodesy").arg(nodeCnt).arg(toAdd));
                newBarabasiAlbert(nodeCnt, toAdd, 3);  
            }
                break;
            
            case WattsStrogatz:
            {
                int nodeCnt = m_pModelProperties->cntNodes;
                int degree = m_pModelProperties->degree;
                float beta = m_pModelProperties->beta;
                m_actionLabel->setText(QString("generaing Watts/Strogatz graph, nodes: %1, degree %2 and beta factor %3").arg(nodeCnt).arg(degree).arg(beta));

                newWattsStrogatz(m_pModelProperties->cntNodes, degree, beta);
            }
                break;

            default:
                QMessageBox::warning(this, "unknown model", QString("Unknown model type %1").arg(modelType));
        }
    }
    else
    {
        QMessageBox::warning(this, "missing model", "You must specify the model paramerts first");
    }

    displayMsg("in randomgraph::ongengraph");
}
