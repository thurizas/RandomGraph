/*************************************************************************************************************
*  File    : edge.h                                                                        
*                                                                                                    
*  Abstract: This file contains the interface for the edge class.  We model an edge as a line between the
*            souce vertex and the end vertex (which are maintained as member variables), as well as if the
*            edge is directed.
*                                                                                                    
*  Signals :                                                                                         
*                                                                                                    
*  Slots   :                                                                                         
*                                                                                                    
*  Written : Created Jul 2016 (G.K.Huber)         
*************************************************************************************************************/
#pragma once

#include <QGraphicsItem>

#include <string>

#include "node.h"

class CEdge 
{
public:
    //CEdge(int, int, std::string l="", bool d=false);
    CEdge(CNode*, CNode*, std::string l="?", bool d=false);

    void printEdge();
    void addToScene(QGraphicsScene*);                    // TODO: this should be consistent with the CNode::addToScene

    void        setLabel(std::string s) {m_strLabel = s;}
    std::string getLabel() {return m_strLabel;}

    void        setDirected(bool b) {m_bDirected = b;}
    bool        getDirected() {return m_bDirected;}

    void        setSrc(CNode* ptemp) {m_src = ptemp;}
    CNode*      getSrc() {return m_src;}

    void        setDst(CNode* ptemp) {m_dst = ptemp;}
    CNode*      getDst() {return m_dst;}

private:
    //int            m_src;
    //int            m_dst;
    CNode*         m_src;
    CNode*         m_dst;
    bool           m_bDirected;
    std::string    m_strLabel;
};
