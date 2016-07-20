/*************************************************************************************************************
*  File    : graphDistroDlg.h                                                                        
*                                                                                                    
*  Abstract: The file contains the definition of the graph distribution dialog, a dialog designed to
*            display the node distribution as a histogram.  The display will also keep a running total for
*            a set of graphs, displaying the cumulative distribution.
*                                                                                                    
*  Signals :                                                                                         
*                                                                                                    
*  Slots   :                                                                                         
*                                                                                                    
*  Written : Created Jul 2016 (G.K.Huber)         
*************************************************************************************************************/
#pragma once


#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QDialogButtonBox>
#include <QHeaderView>
#include "qcustomplot.h"
#include "graph.h"

class CDistroDlg : public QDialog
{
    Q_OBJECT
public:
    CDistroDlg(QWidget* parent = nullptr);
    ~CDistroDlg();

    void setupUi();

    void setGraph(CGraph*);
    void clearData();


private:
    void            setupPlotWidget();

    QCustomPlot*    m_plotWidget;
    QCPBars*        m_bars;
    QString         m_model;
    int             m_order;
    QVector<double> m_keyData;
    QVector<double> m_valueData;
};
