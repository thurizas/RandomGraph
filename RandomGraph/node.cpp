#include "node.h"
#include "utility.h"
#include "config.h"


#include <QFontMetrics>


/*************************************************************************************************************
* Function: ctor
*
* Abstract: constructor for a node object, we set the label, all other details are set to default values.
*
* Params  : l -- [in] label for the node
*           pScene -- [in] pointer to the graphic scene that will hold the node
*
* Returns : 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
CNode::CNode(std::string l, QGraphicsScene* pScene): m_label(l), m_index(-1), m_X(0), m_Y(0), m_deg(0), m_distance(-1), m_parent(-1), m_pScene(pScene)
{

}



/*************************************************************************************************************
* Function: ctor
*
* Abstract: constructor for a node object.  We provide all the required information for the node
*
* Params  : n -- [in] the node identifier
*           l -- [in] std::string containing the label of the node
*           pt -- [in] a qpoint object containing the suggest location of the node
*
* Returns : 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
CNode::CNode(int n, std::string l, QPoint pt, QGraphicsScene* pScene) : m_label(l), m_index(n), m_X(pt.x()), m_Y(pt.y()), m_deg(0), m_pScene(pScene)
{

}



/*************************************************************************************************************
* Function: printNode
*
* Abstract: a utility function to print node parameters to a terminal window
*
* Params  : void 
*
* Returns : void
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CNode::printNode()
{
    displayMsg("Id: %d, label: %s, degree: %d suggested location (%d, %d)\n", m_index, m_label.c_str(), m_deg, m_X, m_Y);
}



/*************************************************************************************************************
* Function: addToScene
*
* Abstract: This function is responsible for creating the underlying graphics item, setting background color
*           and set the label on the node.
*
* Params  : pGraph -- [in] pointer to the display window that will render the scene
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CNode::addToScene(RandomGraph* pGraph)            
{
    //QGraphicsRectItem     node(nullptr);

    // Get the current font we are using ...
    QFont           curFont = m_pScene->font();
    QFontMetrics    qfmetrics(curFont);
    
    // Get bounding rectangle for the label ...
    QRectF     rect;
    rect = qfmetrics.boundingRect(QRect(0,0,250,50), Qt::AlignLeft, QString(m_label.c_str()), 0, 0);
    
    // build a circle for our node, and add to scene...
    int radius = rect.width() > rect.height() ? rect.width() : rect.height();

    /*QGraphicsEllipseItem */ m_pNode = m_pScene->addEllipse(m_X - radius, m_Y-radius, 2*radius, 2*radius);
    m_pNode->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIgnoresParentOpacity | QGraphicsItem::ItemStacksBehindParent);
    m_pNode->setBrush(CConfig::getInstance()->getNodeColor());
    m_pNode->setZValue(2.0);
    m_pNode->topLevelItem();

    // text location.  top left corner of text box is at center of node..
    if(pGraph->showLabels())
    {
        QGraphicsTextItem*    pText = new QGraphicsTextItem(QString(m_label.c_str()), m_pNode);
        pText->setDefaultTextColor(Qt::green);
        pText->setFont(curFont);
        int xOffset = ceil((m_label.size() + 1.0)/2.0);
        pText->setPos(m_X - xOffset* qfmetrics.averageCharWidth(), m_Y - (3*qfmetrics.height()/4));
    }
}

