#include "graphDistroDlg.h"
#include "utility.h"


/*************************************************************************************************************
* Function: ctor
*
* Abstract: This creates and instance of the distribution dialog, which is used to display a histogram of
*           frequences in some observable.
*
* Params  : void 
*
* Returns : void
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
CDistroDlg::CDistroDlg(QWidget* p) : QDialog(p), m_model(""), m_order(-1)
{ 
    setupUi();
    setupPlotWidget();
}



/*************************************************************************************************************
* Function: dtor
*
* Abstract: destroys an instance of the distribution dialo
*
* Params  : 
*
* Returns : 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
CDistroDlg::~CDistroDlg() 
{ 

}



/*************************************************************************************************************
* Function: setupUi
*
* Abstract: This function sets up the user interface of the dialog
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CDistroDlg::setupUi()
{
    QDialogButtonBox *buttonBox;

     if (this->objectName().isEmpty())
        setObjectName(QStringLiteral("Dialog"));
    resize(400, 300);
    setWindowTitle("Graph Property Distribution");
    
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setGeometry(QRect(40, 260, 341, 32));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    m_plotWidget = new QCustomPlot(this);
    m_plotWidget->setObjectName(QStringLiteral("widget"));
    m_plotWidget->setGeometry(QRect(9, 9, 371, 251));

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
} // setupUi



/*************************************************************************************************************
* Function: setGraph
*
* Abstract: This function accepts a pointer to a graph instance, and extracts the observable we are tracking.
*           We append this data to the current data so we can modifiy the histogram as new graphs are
*           generated.
*           If the model or order of teh graph changes, we clear the accumulators and start a new display
*
* Params  : 
*
* Returns : 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CDistroDlg::setGraph(CGraph* pGraph)
{
    QString model = pGraph->getMethod();
    int     order = pGraph->getOrder();
    int     maxFreq = 0;

    // see if model or order has changed, if so start a new statistic collection, otherwise just append.
    if((model != m_model) || (order != m_order))                
    {
        m_model = model;
        m_order = order;
        clearData();
    }

    // get the appropriate statistic from the graph...
    std::vector<int>::iterator   dsIter;
    std::vector<int>             deg = pGraph->getDegreeSequence();

    dsIter = deg.begin();
    while(deg.end() != dsIter)
    {
        int nodeDeg = (*dsIter);
        m_valueData[nodeDeg]++;

        if(maxFreq < m_valueData.at(nodeDeg)) maxFreq = m_valueData.at(nodeDeg);
        ++dsIter;
    }
    
    m_plotWidget->xAxis->setRange(0, order);
    m_plotWidget->yAxis->setRange(0, (maxFreq+3));

    m_bars->setData(m_keyData, m_valueData);

    m_plotWidget->replot();
}



/*************************************************************************************************************
* Function: setupPlotWidget
*
* Abstract: This function sets up the plotting widget
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CDistroDlg::setupPlotWidget()
{
     // create empty bar chart objects:
    m_bars = new QCPBars(m_plotWidget->xAxis, m_plotWidget->yAxis);
    m_plotWidget->addPlottable(m_bars);
        
    // set names and colors:    
    QPen pen;
    m_bars->setName("frequencies");
    pen.setColor(QColor(150, 222, 0));
    m_bars->setPen(pen);
    m_bars->setBrush(QColor(150, 222, 0, 70));
    
    m_plotWidget->xAxis->setAutoTicks(true);
    m_plotWidget->xAxis->setAutoTickLabels(true);
    m_plotWidget->xAxis->setTickLength(0, 4);
    m_plotWidget->xAxis->grid()->setVisible(true);
 
    // prepare y axis:
    m_plotWidget->yAxis->setPadding(5); // a bit more space to the left border
    m_plotWidget->yAxis->setLabel("Frequence");
    m_plotWidget->yAxis->grid()->setSubGridVisible(true);
}



/*************************************************************************************************************
* Function: clearData
*
* Abstract: This is a utility function that is used to clear all accumulate data, and also reset the
*           display widget to its initial state
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CDistroDlg::clearData()
{
    displayMsg("resetting accumulated data");
    m_valueData.erase(m_valueData.begin(), m_valueData.end());
    m_keyData.erase(m_keyData.begin(), m_keyData.end());
    m_valueData.resize(m_order);
    m_keyData.resize(m_order);

    for(int ndx = 0; ndx < m_order; ndx++)
    {
        m_keyData[ndx] = (double)ndx;
        m_valueData[ndx] = 0;
    }

    m_bars->clearData();
    m_plotWidget->replot();
}
