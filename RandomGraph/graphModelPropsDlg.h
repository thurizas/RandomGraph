/*************************************************************************************************************
*  File    : graphModelPropsDlg.h                                                                        
*                                                                                                    
*  Abstract: This file contains the declaration of the model properties dialog.  THis dialog makes use of
*            several custom controls to collect the required infomation for each type of graph model.
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
#include <QComboBox>
#include <QDialog>
#include <QFrame>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QSpacerItem>
#include <QWidget>


#include "common.h"

class CModelPropsDlg : public QDialog
{
    Q_OBJECT

public:
    CModelPropsDlg(pModelProps, QWidget* parent);

    void setupUi();

    int   getModelType();

    bool  doClear(int model);           // used by all
    int   getNodeCnt(int model);        // used by all
    int   getNodesTooAdd(int model);    // used only with BA
    int   getDegree(int model);         // used only with WS


    float getEdgeProp(int model);       // used only with ER
    float getBeta(int model);           // used only with WS

private slots:
    void onSelModel(int);

private:
    QWidget*     m_wControls[4];
    QFrame*      m_frmPlaceholder;
    QPushButton* m_btnCancel;
    QPushButton* m_btnOK;
    QComboBox*   m_cboModel;

   
};

