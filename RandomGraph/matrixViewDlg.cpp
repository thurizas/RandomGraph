#include "matrixViewDlg.h"

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QDialog>
#include <QDialogButtonBox>
#include <QHeaderView>
#include <QTableWidget>
#include <QPushButton>
#include <QSizePolicy>



/*************************************************************************************************************
* Function: ctor
*
* Abstract: this function creates an instance of the matrix view dialog
*
* Params  : 
*
* Returns : 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
CMatrixViewDlg::CMatrixViewDlg(QWidget* parent) : QDialog(parent)
{
    setupUi();
}



/*************************************************************************************************************
* Function: 
*
* Abstract: 
*
* Params  : 
*
* Returns : 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
CMatrixViewDlg::~CMatrixViewDlg()
{

}



/*************************************************************************************************************
* Function: setMatrix
*
* Abstract: passes in the appropriate matrix (a n-by-n character array) to the dialog, and populates the
*           table view with the values in the matix
*
* Params  : matrix --[in] pointer to an n x n matrix
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CMatrixViewDlg::setMatrix(const char* matrix, int nodes)
{
    m_tableView->setColumnCount(nodes);
    
    for(int ndx = 0; ndx < nodes; ndx++)
    {
        m_tableView->setHorizontalHeaderItem(ndx, new QTableWidgetItem(QString("N%1").arg(ndx)));  
    }

    for(int rdx = 0; rdx < nodes; rdx++)
    {
        m_tableView->insertRow(rdx);
        for(int cdx = 0; cdx < nodes; cdx++)
        {
            m_tableView->setVerticalHeaderItem(rdx, new QTableWidgetItem(QString("N%1").arg(rdx)));
            int val = matrix[rdx*nodes + cdx];
            m_tableView->setItem(rdx, cdx, new QTableWidgetItem(tr("%1").arg(val)));
        }
    }
}



/*************************************************************************************************************
* Function: setupUi
*
* Abstract: creates the user interface for the dialog
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CMatrixViewDlg::setupUi()
{
    QDialogButtonBox *buttonBox;

    this->resize(600,350);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setGeometry(QRect(260, 320, 341, 32));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

    m_tableView = new QTableWidget(this);
    m_tableView->setObjectName(QStringLiteral("m_tableView"));
    m_tableView->setGeometry(QRect(0, 10, 600, 281));

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
}
