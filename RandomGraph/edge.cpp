#include "edge.h"
#include "utility.h"
#include "config.h"

#include <QBrush>

//CEdge::CEdge(int src, int dst, std::string l, bool d) : m_src(src), m_dst(dst), m_bDirected(d), m_strLabel(l)
//{

//}

CEdge::CEdge(CNode* src, CNode* dst, std::string l, bool d): m_src(src), m_dst(dst)//, m_bDirected(d), m_strLabel(l)
{
    m_strLabel = l;
    m_bDirected = d;
}



void CEdge::printEdge()
{
    displayMsg("edge from %s to %s, directed: %d, label: %s\n", m_src->getLabel().c_str(), m_dst->getLabel().c_str(), m_bDirected, m_strLabel.c_str());
}


void  CEdge::addToScene(QGraphicsScene* pScene)
{
    QBrush   brush(Qt::black);
    QPen     pen(brush, CConfig::getInstance()->getEdgeWeight());

    QPoint   ptTail = m_src->getTempLoc();
    QPoint   ptHead = m_dst->getTempLoc();

    QGraphicsLineItem* pline = pScene->addLine(ptTail.x(), ptTail.y(), ptHead.x(), ptHead.y());
    pline->setPen(pen);

}