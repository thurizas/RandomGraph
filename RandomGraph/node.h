#pragma once

#include "randomgraph.h"

#include<QPoint>
#include <QGraphicsItem>
#include <QGraphicsScene>

#include<string>

class CNode 
{
public:
    CNode(std::string, QGraphicsScene*);
    CNode(int, std::string, QPoint, QGraphicsScene*);

    void        setLabel(std::string label) {m_label = label;}
    std::string getLabel() {return m_label;}

    void        setIndex(int n) {m_index = n;}
    int         getIndex() {return m_index;}

    void        setTempLoc(QPoint pt) {m_X = pt.x(); m_Y = pt.y();}
    QPoint      getTempLoc() {return QPoint(m_X, m_Y);}

    void        incDegree() {++m_deg;}
    int         getDegree() {return m_deg;}

    void        setParent(int p) {m_parent = p;}
    int         getParent() {return m_parent;}

    void        setDistance(int d) {m_distance = d;}
    int         getDistance() {return m_distance;}

    QGraphicsEllipseItem* getItemPtr() {return m_pNode;}

    void        printNode();

    void        addToScene(RandomGraph*);

private:
    std::string     m_label;
    int             m_index;
    int             m_X;
    int             m_Y;
    int             m_deg;
    int             m_distance;            // distance value, used in BFS
    int             m_parent;              // parent node ID, used in BFS
    QGraphicsScene* m_pScene;
    QGraphicsEllipseItem*  m_pNode;               // underlying graphics item, if we need...

    QRectF         outlineRect() const;
};
