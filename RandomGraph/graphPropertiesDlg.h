/*************************************************************************************************************
*  File    : graphPropertiesDlg.h                                                                        
*                                                                                                    
*  Abstract: This file contains the declaration of the graph propeties dialog.  This dialog captures and
*            displays the min, avg, max degree of each graph.  It will maintain a running averag of these.
*            This dialog is displayed at the same time as the graph distributin dialog.
*                                                                                                    
*  Signals :                                                                                         
*                                                                                                    
*  Slots   :                                                                                         
*                                                                                                    
*  Written : Created Jul 2016 (G.K.Huber)         
*************************************************************************************************************/
#pragma once

#include "randomgraph.h"

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QTableWidget>
#include <QPushButton>

class CGraph;

class CPropertiesDlg : public QDialog
{
    Q_OBJECT

public:
    CPropertiesDlg(QWidget*);

    void   setGraph(CGraph*);

    void   reset() {onClear();}

private slots:
    void onClear();
    void onSave();

private:
    void setupUi();

    QTableWidget* m_tableView;
    QPushButton*  m_btnClear;
    QPushButton*  m_btnSave;
    RandomGraph*  m_pParent;

};
