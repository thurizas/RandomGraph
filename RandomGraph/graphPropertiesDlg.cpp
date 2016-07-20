#include "graphPropertiesDlg.h"
#include "graph.h"



/*************************************************************************************************************
* Function: ctor
*
* Abstract: constructs and instance of the class
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
CPropertiesDlg::CPropertiesDlg(QWidget* parent) : QDialog(parent), m_tableView(nullptr)
{
    setupUi();
    m_pParent = dynamic_cast<RandomGraph*>(parent);

}


/*************************************************************************************************************
* Function: setupUi 
*
* Abstract: This function builds the user interface for the dialog
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CPropertiesDlg::setupUi()
{
    QDialogButtonBox *buttonBox;

    this->resize(600,350);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setGeometry(QRect(260, 320, 341, 32));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
    
    m_btnClear = new QPushButton(this);
    m_btnClear->setObjectName(QStringLiteral("m_btnClear"));
    m_btnClear->setGeometry(QRect(10, 320, 75, 23));
    m_btnClear->setText("Clear");
    
    m_btnSave = new QPushButton(this);
    m_btnSave->setObjectName(QStringLiteral("m_btnSave"));
    m_btnSave->setGeometry(QRect(100, 320, 75, 23));
    m_btnSave->setEnabled(false);
    m_btnSave->setText("Save");

    m_tableView = new QTableWidget(this);
    m_tableView->setObjectName(QStringLiteral("m_tableView"));
    m_tableView->setGeometry(QRect(0, 10, 601, 281));
    m_tableView->setColumnCount(6);
    m_tableView->setHorizontalHeaderItem(0, new QTableWidgetItem("algorithm"));
    m_tableView->setHorizontalHeaderItem(1, new QTableWidgetItem("nodes"));
    m_tableView->setHorizontalHeaderItem(2, new QTableWidgetItem("edges"));
    m_tableView->setHorizontalHeaderItem(3, new QTableWidgetItem("min degree"));
    m_tableView->setHorizontalHeaderItem(4, new QTableWidgetItem("avg degree"));
    m_tableView->setHorizontalHeaderItem(5, new QTableWidgetItem("max degree"));

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(m_btnClear, SIGNAL(clicked()), this, SLOT(onClear()));
    connect(m_btnSave, SIGNAL(clicked()), this, SLOT(onSave()));

    QMetaObject::connectSlotsByName(this);
}



/*************************************************************************************************************
* Function: setGraph
*
* Abstract: This function sets the graph that we are looking to extract the statistics on.  We call calcDegree
*           on the graph object so that it calculates the min, avg and max degrees.  We then extract those
*           values and add it to the table
*
* Params  : pGraph -- [in] pointer to a graph structure to extract information from
*
* Returns : voic 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CPropertiesDlg::setGraph(CGraph* pGraph)
{    
    // calculate the statistics for the graph...
    pGraph->calcDegrees();
    
    // the the various statistics for the graph...
    QString   qstrAlgo = pGraph->getMethod();
    int       cntNodes = pGraph->getOrder();
    int       cntEdges = pGraph->getSize();
    int       minDeg = pGraph->getMinDeg();
    float     avgDeg = pGraph->getAvgDeg();
    int       maxDeg = pGraph->getMaxDeg();

    // get number of rows in the widget...
    int   cntRows = m_tableView->rowCount();

    m_tableView->insertRow(cntRows);
    m_tableView->setItem(cntRows, 0, new QTableWidgetItem(tr("%1").arg(qstrAlgo)));
    m_tableView->setItem(cntRows, 1, new QTableWidgetItem(tr("%1").arg(cntNodes)));
    m_tableView->setItem(cntRows, 2, new QTableWidgetItem(tr("%1").arg(cntEdges)));
    m_tableView->setItem(cntRows, 3, new QTableWidgetItem(tr("%1").arg(minDeg)));
    m_tableView->setItem(cntRows, 4, new QTableWidgetItem(tr("%1").arg(avgDeg)));
    m_tableView->setItem(cntRows, 5, new QTableWidgetItem(tr("%1").arg(maxDeg)));
}



/*************************************************************************************************************
* Function: onClear
*
* Abstract: This function clears all data from the table view, as well signalling the parent object to have
*           the histogram display reset itself.
*
* Params  : void 
*
* Returns : void
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CPropertiesDlg::onClear()
{
    m_tableView->clearContents();

    for(int i = m_tableView->rowCount()-1; i >= 0; i--)
    {
        m_tableView->removeRow(i);
    }

    // we need to clear the histogram display...
    m_pParent->clearDisto();
}



/*************************************************************************************************************
* Function: onSave
*
* Abstract: not yet implemented 
*
* Params  : 
*
* Returns : 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CPropertiesDlg::onSave()
{

}


