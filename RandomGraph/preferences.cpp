#include "preferences.h"
#include "utility.h"
#include "config.h"

#include <QColorDialog>
#include <QFontDialog>

// TODO : edge color modification is not yet implememented.

/*************************************************************************************************************
* Function: ctor for the preferences dialog
*
* Abstract: displays the current preferences and allows the user to modify them
*
* Params  : parent -- [in] parent of the dialog
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
CDlgPreferences::CDlgPreferences(QWidget* parent) : QDialog(parent), m_pNewBkgColor(nullptr), m_pNewNodeColor(nullptr), m_pNewEdgeColor(nullptr), m_pNewNodeFont(nullptr), m_pNewEdgeWeight(nullptr) 
{ 
    setupUi();

    // get currently configured background color...
    QColor    bkgColor = CConfig::getInstance()->getBkgColor();
    m_edtBkgColor->setText(bkgColor.name());

    // get currently configured node color...
    QColor    nodeColor = CConfig::getInstance()->getNodeColor();
    m_edtNodeColor->setText(nodeColor.name());

    // get currently configured node font...
    QFont*  newFont = CConfig::getInstance()->getFont();
    m_edtNodeFont->setText(newFont->family());

    int   edgeWeight = CConfig::getInstance()->getEdgeWeight();
    m_spnEdgeWeight->setValue(edgeWeight);
}



/*************************************************************************************************************
* Function: setupUi
*
* Abstract: builds the user interface for the dialog
*
* Params  : void 
*
* Returns : void
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CDlgPreferences::setupUi()
{
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    
    // basic dialog setup...
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("Dialog"));
    this->resize(306, 172);
    this->setWindowTitle(QApplication::translate("Dialog", "Preferences", 0));

    // build default font for dialog...
    QFont font;
    font.setFamily(QStringLiteral("Courier New"));
    font.setPointSize(12);
    this->setFont(font);
    this->setContextMenuPolicy(Qt::NoContextMenu);

    // build font for chooser buttons
    QFont font2;
    font2.setFamily(QStringLiteral("Raavi"));
    font2.setPointSize(11);
    font2.setBold(true);
    font2.setWeight(75);

    // command button box...
    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setGeometry(QRect(50, 130, 241, 32));
    buttonBox->setFont(font);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    m_btnApplyButton = buttonBox->addButton(QDialogButtonBox::Apply);
    m_btnApplyButton->setEnabled(false);

    // dialog items for the background color picker....
    label = new QLabel(this);
    label->setObjectName(QStringLiteral("label"));
    label->setGeometry(QRect(10, 10, 101, 22));
    label->setFont(font);
    label->setText(QApplication::translate("Dialog", "Background Color", 0));

    m_edtBkgColor = new QLineEdit(this);
    m_edtBkgColor->setObjectName(QStringLiteral("m_edtBkgColor"));
    m_edtBkgColor->setGeometry(QRect(130, 10, 113, 20));
    m_edtBkgColor->setFont(font);
    m_edtBkgColor->setEnabled(false);
    
    m_btnBkgColor = new QPushButton(this);
    m_btnBkgColor->setObjectName(QStringLiteral("m_btnBkgColor"));
    m_btnBkgColor->setGeometry(QRect(240, 10, 31, 23));    
    m_btnBkgColor->setFont(font2);
    m_btnBkgColor->setText(QApplication::translate("Dialog", "...", 0));
   
    // dialog items for the node color picker...
    label_2 = new QLabel(this);
    label_2->setObjectName(QStringLiteral("label_2"));
    label_2->setGeometry(QRect(10, 40, 101, 22));
    label_2->setFont(font);
    label_2->setText(QApplication::translate("Dialog", "Node Color", 0));

    m_edtNodeColor = new QLineEdit(this);
    m_edtNodeColor->setObjectName(QStringLiteral("m_edtNodeColor"));
    m_edtNodeColor->setGeometry(QRect(130, 40, 113, 20));
    m_edtNodeColor->setFont(font);
    m_edtNodeColor->setEnabled(false);

    m_btnNodeColor = new QPushButton(this);
    m_btnNodeColor->setObjectName(QStringLiteral("m_btnNodeColor"));
    m_btnNodeColor->setGeometry(QRect(240, 40, 31, 23));
    m_btnNodeColor->setFont(font2);
    m_btnNodeColor->setText(QApplication::translate("Dialog", "...", 0));

    // dialog items for the node font picker ....
    label_3 = new QLabel(this);
    label_3->setObjectName(QStringLiteral("label_3"));
    label_3->setGeometry(QRect(10, 70, 101, 22));
    label_3->setFont(font);
    label_3->setText(QApplication::translate("Dialog", "Node Font", 0));

    m_edtNodeFont = new QLineEdit(this);
    m_edtNodeFont->setObjectName(QStringLiteral("m_edtNodeFont"));
    m_edtNodeFont->setGeometry(QRect(130, 70, 113, 20));
    m_edtNodeFont->setFont(font);
    m_edtNodeFont->setEnabled(false);

    m_btnFontPicker = new QPushButton(this);
    m_btnFontPicker->setObjectName(QStringLiteral("m_btnFontPicker"));
    m_btnFontPicker->setGeometry(QRect(240, 70, 31, 23));
    m_btnFontPicker->setFont(font2);
    m_btnFontPicker->setText(QApplication::translate("Dialog", "...", 0));

    // dialog items for the edge weight controls ....
    label_4 = new QLabel(this);
    label_4->setObjectName(QStringLiteral("label_4"));
    label_4->setGeometry(QRect(10, 100, 101, 22));
    label_4->setFont(font);    
    label_4->setText(QApplication::translate("Dialog", "Edge Weight", 0));

    m_spnEdgeWeight = new QSpinBox(this);
    m_spnEdgeWeight->setMinimum(1);
    m_spnEdgeWeight->setMaximum(20);
    m_spnEdgeWeight->setObjectName(QStringLiteral("m_spnEdgeWeight"));
    m_spnEdgeWeight->setGeometry(QRect(130, 100, 42, 22));
    m_spnEdgeWeight->setFont(font);

    // set up signals and slots for this dialog...
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(onAccept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(onReject()));
    QObject::connect(m_btnApplyButton, SIGNAL(clicked()), this, SLOT(onApply()));
    QObject::connect(m_btnFontPicker, SIGNAL(clicked()), this, SLOT(OnGetFont()));
    QObject::connect(m_btnNodeColor, SIGNAL(clicked()), this, SLOT(OnGetColor()));
    QObject::connect(m_btnBkgColor, SIGNAL(clicked()), this, SLOT(OnGetBkgColor()));
    connect(m_spnEdgeWeight, SIGNAL(valueChanged(int)), this, SLOT(OnChangeEdgeWeight(int)));

    QMetaObject::connectSlotsByName(this);
 }   



 /************************************************************************************************************
  * function: onAccept 
  *
  * abstract:  User has clicked the OK button, if the apply button is 'enabled' we have changes waiting to be 
  *            save, go ahead and do this for him.  Also, as he clicked, ok lets write these changes out to the 
  *            persistant configuration location.
  *
  * input   :  void 
  *
  * returns :  void
  *
  * written : (G.K.Huber)
  ***********************************************************************************************************/
 void CDlgPreferences::onAccept()
 {
     if(m_btnApplyButton->isEnabled())                    // changes waiting to be applied, do it now.
     {
         onApply();
         m_btnApplyButton->setEnabled(false);
     }

     cleanup();
     this->accept();                                      // call base case 
 }



/************************************************************************************************************
 * function: onReject
 *
 * abstract: User clicked cancelled, we exit now.  We discard any changes he may have made since his last 
 *           clicking the 'apply' button.  Prior to calling the defalut reject method we cleanup our temporary
 *           variables
 *
 * input   :  void 
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
 void CDlgPreferences::onReject()
 {
     cleanup();
     this->reject();                                    // call base case 
 }



 /************************************************************************************************************
  * function: onApply
  *
  * abstract: We write any changes the user has made out to the configuation class, and we delete the temporary
  *           object holding the new value.  As the user can click the 'apply' button at any time after making 
  *           a change, we need to check every temporary value to see if a new value has been set.  At the 
  *           end we deactive the apply button as a visual clue to he user that he has applied all his changes.
  *           N.B.  The changes will not show up till after he closes the preference dialog box, and  the 
  *                 scene is redrawn.
  *
  * input   :  void 
  *
  * returns :  void 
  *
  * written : (G.K.Huber)
  ***********************************************************************************************************/
void CDlgPreferences::onApply() 
{
    if(nullptr != m_pNewBkgColor)
    {
        CConfig::getInstance()->setBkgColor(*m_pNewBkgColor);
        delete m_pNewBkgColor;
        m_pNewBkgColor = nullptr;
    }
    
    if(nullptr != m_pNewNodeColor)
    {
        CConfig::getInstance()->setNodeColor(*m_pNewNodeColor);
        delete m_pNewNodeColor;
        m_pNewNodeColor = nullptr;
    }

    if(nullptr != m_pNewEdgeColor)
    {
        CConfig::getInstance()->setEdgeColor(*m_pNewEdgeColor);
        delete m_pNewEdgeColor;
        m_pNewEdgeColor = nullptr;
    }

    if(nullptr != m_pNewNodeFont)
    {
        CConfig::getInstance()->setFont(*m_pNewNodeFont);
        delete m_pNewNodeFont;
        m_pNewNodeFont = nullptr;
    }

    if(nullptr != m_pNewEdgeWeight)
    {
        CConfig::getInstance()->setEdgeWeight(*m_pNewEdgeWeight);
        delete m_pNewEdgeWeight;
        m_pNewEdgeWeight = nullptr;
    }

    m_btnApplyButton->setEnabled(false);
}


/************************************************************************************************************
 * function: OnGetFont
 *
 * abstract:  This button handles clicking on the search button next to the font field, it brings up the 
 *            standard QFontDialog to allow the user to select a new font.
 *
 * input   :  void 
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CDlgPreferences::OnGetFont()
{
    QFont*          oldFont = CConfig::getInstance()->getFont();
    QFontDialog     dlg(*oldFont, this);

    if(QDialog::Accepted == dlg.exec())
    {
        if(nullptr != m_pNewNodeFont)
            delete m_pNewNodeFont;

        m_pNewNodeFont = new QFont(dlg.currentFont());
        m_edtNodeFont->setText(m_pNewNodeFont->family());
        m_btnApplyButton->setEnabled(true);
    }
}



/************************************************************************************************************
 * function: OnGetColor
 *
 * abstract:  This function handles the user clicking on the search button to the right of the text field 
 *            for the background color.  We bring up the standard QColorDialog to allow the user to select 
 *            a new background color.
 *
 * input   :  void 
 *
 * returns :  void
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CDlgPreferences::OnGetColor()
{
    QColorDialog   dlg(CConfig::getInstance()->getNodeColor(), this);

    if(QDialog::Accepted == dlg.exec())
    {
        if(nullptr != m_pNewNodeColor)
            delete m_pNewNodeColor;

        m_pNewNodeColor = new QColor(dlg.currentColor());
        m_edtNodeColor->setText(m_pNewNodeColor->name());
        m_btnApplyButton->setEnabled(true);
    }
}


/************************************************************************************************************
 * function: OnGetBkgColor
 *
 * abstract:  This function handles the user clicking on the search button to the right of the text field 
 *            for the background color.  We bring up the standard QColorDialog to allow the user to select 
 *            a new background color.
 *
 * input   :  void 
 *
 * returns :  void
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CDlgPreferences::OnGetBkgColor()
{
    QColorDialog   dlg(CConfig::getInstance()->getBkgColor(), this);

    if(QDialog::Accepted == dlg.exec())
    {
        if(nullptr != m_pNewBkgColor)
            delete m_pNewBkgColor;

        m_pNewBkgColor = new QColor(dlg.currentColor());
        m_edtBkgColor->setText(m_pNewBkgColor->name());
        m_btnApplyButton->setEnabled(true);
    }
}



/************************************************************************************************************
 * function: onChangeEdgeWeight
 *
 * abstract:  this responds to the user changing the value of the edge weight by the spinner contol.
 *
 * input   :  void 
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CDlgPreferences::OnChangeEdgeWeight(int newValue)
{
    if(nullptr != m_pNewEdgeWeight)
    {
        delete m_pNewEdgeWeight;
        m_pNewEdgeWeight = nullptr;
    }

    m_pNewEdgeWeight = new int;
    *m_pNewEdgeWeight = newValue;
    m_btnApplyButton->setEnabled(true);
}



/************************************************************************************************************
 * function: cleanup
 *
 * abstract: Free up heap memory for the stuff we are responsible for (i.e. those things we did not pass to 
 *           a QObject derived class as children.
 *
 * input   :  void 
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CDlgPreferences::cleanup()
{
    if(nullptr != m_pNewBkgColor) delete m_pNewBkgColor;
    if(nullptr != m_pNewNodeColor) delete m_pNewNodeColor;
    if(nullptr != m_pNewEdgeColor) delete m_pNewEdgeColor;
    if(nullptr != m_pNewNodeFont) delete m_pNewNodeFont;
    if(nullptr != m_pNewEdgeWeight) delete m_pNewEdgeWeight;
}


