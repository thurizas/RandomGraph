/*************************************************************************************************************
*  File    : preferences.h                                                                        
*                                                                                                    
*  Abstract: This file contains the declaration of the configuration class.  In this class we maintain the
*            various configuration parameters the application needs.
*                                                                                                    
*  Signals :                                                                                         
*                                                                                                    
*  Slots   :                                                                                         
*                                                                                                    
*  Written : Created Jul 2016 (G.K.Huber)         
*************************************************************************************************************/
#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>



class CDlgPreferences : public QDialog
{
    Q_OBJECT

public:
    CDlgPreferences(QWidget* parent); 

public slots: 
    void onApply(); 
    void onAccept();
    void onReject();
    void OnGetFont();
    void OnGetColor();
    void OnGetBkgColor();
    void OnChangeEdgeWeight(int);

private:

    QLineEdit*   m_edtBkgColor;
    QLineEdit*   m_edtNodeColor;
    QLineEdit*   m_edtNodeFont;
    QSpinBox*    m_spnEdgeWeight;
    QPushButton* m_btnBkgColor;
    QPushButton* m_btnNodeColor;
    QPushButton* m_btnFontPicker;
    QPushButton* m_btnApplyButton;

    // parameters for holding values that have chaagned...
    QColor*       m_pNewBkgColor;
    QColor*       m_pNewNodeColor;
    QColor*       m_pNewEdgeColor;
    QFont*        m_pNewNodeFont;
    int*          m_pNewEdgeWeight;

    void setupUi();
    void cleanup();
};

