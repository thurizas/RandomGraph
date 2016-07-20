#include "graphModelPropsDlg.h"
#include "utility.h"
#include "widgets.h"



/*************************************************************************************************************
* Function: ctor for the model properties dialog box
*
* Abstract: constructs and instance of the model properties dialox box
*
* Params  : pcurProps -- [in] pointer to a model property strucure with the current model properties
*           parent    -- [in] pointer to the parent object of this dialog
*
* Returns : void
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
CModelPropsDlg::CModelPropsDlg(pModelProps pcurProps, QWidget* parent) : QDialog(parent)
{
    setupUi();

    m_wControls[0] = nullptr;
    m_wControls[1] = new ERWidget(this, "erwidget");
    m_wControls[2] = new BAWidget(this, "bawidget");
    m_wControls[3] = new WSWidget(this, "wswidget");

    m_wControls[1]->hide();
    m_wControls[2]->hide();
    m_wControls[3]->hide();

    // TODO : if we have model properties, get the appropriate control visible
    // TODO : populate the control with the current values.
}



/*************************************************************************************************************
* Function: setupUi 
*
* Abstract: This function builds the user interface of the dialog and sets up the signals-slot relationships
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CModelPropsDlg::setupUi()
{    
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QLabel *label;

    QFont font;
    font.setFamily(QStringLiteral("Courier New"));
    font.setPointSize(12);

    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("Dialog"));
    resize(400, 300);
    setFont(font);
    setWindowTitle("Model Properties");
    
    layoutWidget = new QWidget(this);
    layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
    layoutWidget->setGeometry(QRect(20, 250, 351, 33));
    
    hboxLayout = new QHBoxLayout(layoutWidget);
    hboxLayout->setSpacing(6);
    hboxLayout->setObjectName(QStringLiteral("hboxLayout"));
    hboxLayout->setContentsMargins(0, 0, 0, 0);
    spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);
    hboxLayout->addItem(spacerItem);

    m_btnOK = new QPushButton(layoutWidget);
    m_btnOK->setObjectName(QStringLiteral("m_btnOK"));
    m_btnOK->setText("OK");

    m_btnCancel = new QPushButton(layoutWidget);
    m_btnCancel->setObjectName(QStringLiteral("m_btnCancel"));
    m_btnCancel->setText("Cancel");
    
    label = new QLabel(this);
    label->setObjectName(QStringLiteral("label"));
    label->setGeometry(QRect(20, 20, 121, 21));
    label->setFont(font);
    label->setText("Choose Model:");

    m_cboModel = new QComboBox(this);
    m_cboModel->setObjectName(QStringLiteral("m_cboModel"));
    m_cboModel->setGeometry(QRect(180, 20, 201, 31));
    m_cboModel->addItem("                  ");
    m_cboModel->addItem("erdos / renayi");
    m_cboModel->addItem("Barabasi / Albert");
    m_cboModel->addItem("Watts / Strogatz");

    m_frmPlaceholder = new QFrame(this);
    m_frmPlaceholder->setObjectName(QStringLiteral("m_frmPlaceholder"));
    m_frmPlaceholder->setGeometry(QRect(20, 70, 351, 171));
    m_frmPlaceholder->setFrameShape(QFrame::StyledPanel);
    m_frmPlaceholder->setFrameShadow(QFrame::Raised);

    hboxLayout->addWidget(m_btnCancel);
    hboxLayout->addWidget(m_btnOK);

    connect(m_btnOK, SIGNAL(clicked()), this, SLOT(accept()));
    connect(m_btnCancel, SIGNAL(clicked()), this, SLOT(reject()));
    connect(m_cboModel, SIGNAL(currentIndexChanged(int)), this, SLOT(onSelModel(int)));
    QMetaObject::connectSlotsByName(this);
} 



/*************************************************************************************************************
* Function: onSelModel
*
* Abstract: This function responds to the user chaning the currently selected item in the combo box.  We
*           make the correct control widget visible, and hide the others.
*
* Params  : model -- [in] index of currently selected model type
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CModelPropsDlg::onSelModel(int model)
{
    QRectF rect = m_frmPlaceholder->geometry();              // area we are going to paste our new widget

    displayMsg("in onSelModel index is %d", model);
    switch(model)
    {
    case 0:                        // blank space on top
        m_wControls[1]->hide();
        m_wControls[2]->hide();
        m_wControls[3]->hide();
        break;

    case 1:                       //Erdor / Renyi model
        m_wControls[1]->show();
        m_wControls[1]->move(rect.x(), rect.y());
        m_wControls[2]->hide();
        m_wControls[3]->hide();
        break;

    case 2:                       // Barabasi / Albert model
        m_wControls[1]->hide();
        m_wControls[2]->show();
        m_wControls[2]->move(rect.x(), rect.y());
        m_wControls[3]->hide();
        break;

    case 3:                       // Watts / Strogatz
        m_wControls[1]->hide();
        m_wControls[2]->hide();
        m_wControls[3]->show();
        m_wControls[3]->move(rect.x(), rect.y());
        break;
    }
}



/*************************************************************************************************************
* Function: getModelType
*
* Abstract: gets the currently selected model from the combo box
*
* Params  : void 
*
* Returns : int, the index of the currently selected model.
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
int CModelPropsDlg::getModelType()
{
    return m_cboModel->currentIndex();
}



/*************************************************************************************************************
* Function:  getNodeCnt
*
* Abstract: gets the initial size of the random graph, used in all models
*
* Params  : model -- [in] model being used
*
* Returns : number of nodes to use
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
int CModelPropsDlg::getNodeCnt(int model)
{
    int nodeCnt = -1;
    switch(model)
    {
        case 1:
            nodeCnt = ((ERWidget*)m_wControls[1])->getNodeCnt();
            break;
        case 2:
            nodeCnt = ((BAWidget*)m_wControls[2])->getNodeCnt();
            break;
        case 3:
            nodeCnt = ((WSWidget*)m_wControls[3])->getNodeCnt();
            break;
    }

    return nodeCnt;
}



/*************************************************************************************************************
* Function: doClear
*
* Abstract: Clears all fields in the currently selected model
*
* Params  :  model -- [in] index of currently selected model
*
* Returns : 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
bool CModelPropsDlg::doClear(int model)
{
    bool      bRet = false;
    switch(model)
    {
        case 1:
            bRet = ((ERWidget*)m_wControls[1])->doClear();
            break;
        case 2:
            bRet = ((BAWidget*)m_wControls[2])->doClear();
            break;
        case 3:
            bRet = ((WSWidget*)m_wControls[3])->doClear();
            break;
    }

    return bRet;
}



/*************************************************************************************************************
* Function: getNodesTooAdd
*
* Abstract: Gets the number of nodes to add in the Barabasi-Albert model
*
* Params  : model -- [in] index of the selected model
*
* Returns : number of nodes to add, or negative one
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
int CModelPropsDlg::getNodesTooAdd(int model)
{
    int val = -1;

    if(2 == model)
    {
        val = ((BAWidget*)m_wControls[model])->getNodesTooAdd();
    }

    return val;
}



/*************************************************************************************************************
* Function: getDegree
*
* Abstract: Gets the node degree in he Watts-Strogatz model
*
* Params  : model -- [in] index of the selected model
*
* Returns : number of nodes to add, or negative one
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
int CModelPropsDlg::getDegree(int model)
{
    int val = -1;

    if(3 == model)
    {
        val = ((WSWidget*)m_wControls[model])->getDegree();
    }

    return val;
}



/*************************************************************************************************************
* Function: getEdgeProp
*
* Abstract: Gets the edge probability in the Erdos-Renyi model
*
* Params  : model -- [in] index of the selected model
*
* Returns : number of nodes to add, or negative one
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
float CModelPropsDlg::getEdgeProp(int model)
{
    float   fVal = -1.0;
    if(1 == model)
    {
        fVal = ((ERWidget*)m_wControls[model])->getEdgeProb();
    }

    return fVal;
}



/*************************************************************************************************************
* Function: getBeta
*
* Abstract: Gets the beta parameter in the Watts-Strogatz model
*
* Params  : model -- [in] index of the selected model
*
* Returns : number of nodes to add, or negative one
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
float CModelPropsDlg::getBeta(int model)
{
    float   fVal = -1.0;
    if(3 == model)
    {
        fVal = ((WSWidget*)m_wControls[model])->getBetaParm();
    }

     return fVal;
}
