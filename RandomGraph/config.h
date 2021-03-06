/*************************************************************************************************************
*  File    : config.h                                                                        
*                                                                                                    
*  Abstract: This file contains the interface for teh configurtion class
*                                                                                                    
*  Signals :                                                                                         
*                                                                                                    
*  Slots   :                                                                                         
*                                                                                                    
*  Written : Created Jul 2016 (G.K.Huber)         
*************************************************************************************************************/
#pragma once

#include <QColor>
#include <QString>
#include <QFont>


class CConfig
{
public:

    void       setBkgColor(QColor clr) {m_bkgColor = clr;}
    QColor     getBkgColor() {return m_bkgColor;}

    void       setNodeColor(QColor clr) {m_nodeColor = clr;}
    QColor     getNodeColor() {return m_nodeColor;}

    void       setEdgeWeight(int n) {m_edgeWeight = n;}
    int        getEdgeWeight() {return m_edgeWeight;}

    void       setEdgeColor(QColor clr) {m_edgeColor = clr;}
    QColor     getEdgeColor() {return m_edgeColor;}

    void       setFont(QFont);
    QFont*     getFont();

    static CConfig*   getInstance();

    void   setPath(const char* org, const char* app);
    void   readConfig();
    void   writeConfig();

private:
    CConfig();
    CConfig(const CConfig&) {}
    CConfig& operator=(const CConfig&) {return *this;}

    // parameters for font...
    QString       m_strFontFamily;
    int           m_nFontSize;
    int           m_nFontWeight;
    bool          m_bIsBold;

    // parameters for QGraphicsView...
    QColor        m_bkgColor;

    // parameters for graph items..
    QColor        m_nodeColor;
    QColor        m_edgeColor;
    int           m_edgeWeight;

    // parameters for QSettigns
    QString       qstOrg;
    QString       qstApp;

    static CConfig*   m_pThis;
};
