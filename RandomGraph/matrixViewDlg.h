/*************************************************************************************************************
*  File    : matrixViewDlg.h                                                                        
*                                                                                                    
*  Abstract: This file contains the declaration of the matrix view dialog.  This dialog is designed to
*            display the contents of a n-by-n matrix in a table view.  This dialog has been designd t o
*            work with either of the adjacency or distance matricies.
*                                                                                                    
*  Signals :                                                                                         
*                                                                                                    
*  Slots   :                                                                                         
*                                                                                                    
*  Written : Created Jul 2016 (G.K.Huber)         
*************************************************************************************************************/
#pragma once

#include  <QDialog>

class QTableWidget;

class CMatrixViewDlg : public QDialog
{
    Q_OBJECT
public:
    CMatrixViewDlg(QWidget* parent = nullptr);
    ~CMatrixViewDlg();

    void setMatrix(const char* matrix, int nodes);
    void setTitle(QString t) {this->setWindowTitle(QString("showing %1 matrix").arg(t));}

private:
    void setupUi();

    QTableWidget* m_tableView;
};
