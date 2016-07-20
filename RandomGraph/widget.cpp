#include "widgets.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QCheckBox>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QWidget>


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// implementation of the Erdos-Renyi control
/*************************************************************************************************************
* Function: ctor
*
* Abstract: constructs and instance of the Erdos-Renyi control
*
* Params  : void
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
ERWidget::ERWidget(QWidget* parent, const char* name) : QWidget(parent)
{
    QLabel *label;
    QLabel *label_2;
    
    if (objectName().isEmpty())
        setObjectName(QStringLiteral("Form"));
    resize(261, 145);

    label = new QLabel(this);
    label->setObjectName(QStringLiteral("label"));
    label->setGeometry(QRect(10, 15, 170, 17));
    label->setText("number of nodes:");

    m_edtNodeCnt = new QLineEdit(this);
    m_edtNodeCnt->setObjectName(QStringLiteral("m_edtNodeCnt"));
    m_edtNodeCnt->setGeometry(QRect(185, 10, 113, 27));
        
    label_2 = new QLabel(this);
    label_2->setObjectName(QStringLiteral("label_2"));
    label_2->setGeometry(QRect(10, 50, 170, 17));
    label_2->setText("edge probability:");
    
    m_edtEdgeProb = new QLineEdit(this);
    m_edtEdgeProb->setObjectName(QStringLiteral("m_edtEdgeProb"));
    m_edtEdgeProb->setGeometry(QRect(185, 45, 113, 27));

    m_cbClear = new QCheckBox(this);
    m_cbClear->setObjectName(QStringLiteral("checkBox"));
    m_cbClear->setGeometry(QRect(10, 120, 300, 22));
    m_cbClear->setText("Clear statistic window");
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
ERWidget::~ERWidget() { }



/*************************************************************************************************************
* Function: getNodeCnt
*
* Abstract: returns the number of nodes to use
*
* Params  : void
*
* Returns : int, number of nodes in the graph
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
int ERWidget::getNodeCnt()
{
    QString   str = m_edtNodeCnt->text();
    return atoi(str.toStdString().c_str());
}



/*************************************************************************************************************
* Function: getEdgeProb
*
* Abstract: returns the edge probablility
*
* Params  : void
*
* Returns : float, the edge probability
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
float ERWidget::getEdgeProb()
{
    QString   str = m_edtEdgeProb->text();
    return atof(str.toStdString().c_str());
}



/*************************************************************************************************************
* Function:  doClear
*
* Abstract: returns the state of the clear statistics check box
*
* Params  : void
*
* Returns : bool, returns true if the check box is checked, false otherwise
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
bool ERWidget::doClear()
{
    return m_cbClear->isChecked();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// implementation of the barabasi-albert control
/*************************************************************************************************************
* Function: ctor
*
* Abstract: constructs and instance of the barabasi-albert control
*
* Params  : 
*
* Returns : 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
BAWidget::BAWidget(QWidget* parent, const char* name) : QWidget(parent)
{
    QLabel *label;
    QLabel *label_2;

    if (objectName().isEmpty())
        setObjectName(QStringLiteral("Form"));
    resize(261, 145);

    label = new QLabel(this);
    label->setObjectName(QStringLiteral("label"));
    label->setGeometry(QRect(10, 15, 170, 17));
    label->setText("initial size:");

    m_edtNodeCnt = new QLineEdit(this);
    m_edtNodeCnt->setObjectName(QStringLiteral("m_edtNodeCnt"));
    m_edtNodeCnt->setGeometry(QRect(185, 10, 113, 27));
        
    label_2 = new QLabel(this);
    label_2->setObjectName(QStringLiteral("label_2"));
    label_2->setGeometry(QRect(10, 50, 170, 17));
    label_2->setText("nodes to add:");
    
    m_edtAddtNodes = new QLineEdit(this);
    m_edtAddtNodes->setObjectName(QStringLiteral("m_edtEdgeProb"));
    m_edtAddtNodes->setGeometry(QRect(185, 45, 113, 27));
    
    m_cbClear = new QCheckBox(this);
    m_cbClear->setObjectName(QStringLiteral("checkBox"));
    m_cbClear->setGeometry(QRect(10, 120, 300, 22));
    m_cbClear->setText("Clear statistic window");

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
BAWidget::~BAWidget() { }



/*************************************************************************************************************
* Function: getNodeCnt
*
* Abstract: returns the initial number of node (m_0) to use.
*
* Params  : void 
*
* Returns : int, number of initial nodes
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
int BAWidget::getNodeCnt()
{
    QString   str = m_edtNodeCnt->text();
    return atoi(str.toStdString().c_str());
}



/*************************************************************************************************************
* Function: getNodesTooAdd
*
* Abstract: gets the number of nodes to add to the graph
*
* Params  : void
*
* Returns : int, number of nodes to add
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
int BAWidget::getNodesTooAdd()
{
    QString   str = m_edtAddtNodes->text();
    return atoi(str.toStdString().c_str());
}



/*************************************************************************************************************
* Function: doClear
*
* Abstract: returns the state of the clear statistics check box.
*
* Params  : void
*
* Returns : bool, true if the check box is checked, false otherwise
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
bool BAWidget::doClear()
{
    return m_cbClear->isChecked();
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// implementation of the Watts-Strogatz control
/*************************************************************************************************************
* Function: ctor 
*
* Abstract: constructs an instance of the conrol
*
* Params  : parent -- [in] pointer to the widget that owns this dialog
*           name --[in] ***unused***
*
* Returns : 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
WSWidget::WSWidget(QWidget* parent, const char* name) : QWidget(parent)
{
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    if (objectName().isEmpty())
        setObjectName(QStringLiteral("Form"));
    resize(261, 145);

    label = new QLabel(this);
    label->setObjectName(QStringLiteral("label"));
    label->setGeometry(QRect(10, 15, 170, 17));
    label->setText("number of nodes:");

    m_edtNodeCnt = new QLineEdit(this);
    m_edtNodeCnt->setObjectName(QStringLiteral("m_edtNodeCnt"));
    m_edtNodeCnt->setGeometry(QRect(185, 10, 113, 27));
        
    label_2 = new QLabel(this);
    label_2->setObjectName(QStringLiteral("label_2"));
    label_2->setGeometry(QRect(10, 50, 170, 17));
    label_2->setText("degree (even):");
    
    m_edtDegree = new QLineEdit(this);
    m_edtDegree->setObjectName(QStringLiteral("m_edtEdgeProb"));
    m_edtDegree->setGeometry(QRect(185, 45, 113, 27));
    
    label_3 = new QLabel(this);
    label_3->setObjectName(QStringLiteral("label_3"));
    label_3->setGeometry(QRect(10, 85, 170, 17));
    label_3->setText(QApplication::translate("Form", "beta parameter:", 0));

    m_edtBetaPram = new QLineEdit(this);
    m_edtBetaPram->setObjectName(QStringLiteral("lineEdit"));
    m_edtBetaPram->setGeometry(QRect(185, 80, 113, 27));

    m_cbClear = new QCheckBox(this);
    m_cbClear->setObjectName(QStringLiteral("checkBox"));
    m_cbClear->setGeometry(QRect(10, 120, 300, 22));
    m_cbClear->setText("Clear statistic window");

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
WSWidget::~WSWidget() { }



/*************************************************************************************************************
* Function: getNodeCnt
*
* Abstract: returns the number of nodes in the cyclic lattice to start with
*
* Params  : void
*
* Returns : int, number of nodes to use
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
int WSWidget::getNodeCnt()
{
    QString  str = m_edtNodeCnt->text();
    return atoi(str.toStdString().c_str());
}



/*************************************************************************************************************
* Function: getDegree
*
* Abstract: returns the degree to use for each node
*
* Params  : void
*
* Returns : int, degree of each node
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
int WSWidget::getDegree()
{
    QString  str = m_edtDegree->text();
    return atoi(str.toStdString().c_str());
}



/*************************************************************************************************************
* Function: getBetaparm
*
* Abstract: this function returns the rewiring parameter
*
* Params  : void
*
* Returns : float, the rewiring parameter
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
float WSWidget::getBetaParm()
{
    QString  str = m_edtBetaPram->text();
    return atof(str.toStdString().c_str());
}



/*************************************************************************************************************
* Function: doClear
*
* Abstract: returns the state of the clear statistics check box
*
* Params  : void 
*
* Returns : bool. true if the checkbox is checked, false otherwise
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
bool WSWidget::doClear()
{
    return m_cbClear->isChecked();
}
