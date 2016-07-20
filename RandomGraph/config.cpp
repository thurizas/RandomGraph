#include "config.h"

#include <QSettings>

// initialize static data member
CConfig* CConfig::m_pThis = nullptr;



/*************************************************************************************************************
* Function: getInstance
*
* Abstract: returns a pointer to an instance of this class.  This class expresses the singleton design
*           pattern.  If the static variable, m_pThis, we create an instace of this class and return that
*           pointer, otherwise we return the previously created value.
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
CConfig* CConfig::getInstance()
{
    if(m_pThis == nullptr)
    {
        m_pThis = new CConfig;
    }

    return m_pThis;
}



/*************************************************************************************************************
* Function: ctor for the class
*
* Abstract: constructs an instace of the class.  
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
CConfig::CConfig() : qstOrg(""), qstApp("")
{

}



/*************************************************************************************************************
* Function: setPath
*
* Abstract: set the two components of the path, used to determine under what registry hive the config
*           information will be stored (windows) or the directory name for the configuration informaion
*           (linux)
*
* Params  : org -- [in] null-terminated string containing the organization name
*           app -- [in] null-terminated string containing the application name
*
* Returns : 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CConfig::setPath(const char* org, const char* app)
{
    qstOrg = org;
    qstApp = app;
}



/*************************************************************************************************************
* Function: readConfig
*
* Abstract: This function reads the configuration information from the defalut location into he appropriae
*           member variables
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CConfig::readConfig()
{
    QSettings     settings(qstOrg, qstApp);

    // read in font settings.....
    m_strFontFamily = settings.value("font/fontFamily").toString();
    m_nFontSize = settings.value("font/fontSize").toInt();
    m_nFontWeight = settings.value("font/fontWeight").toInt();
    m_bIsBold = settings.value("font/fontBold").toBool();

    // read in display settings ....
    m_bkgColor = settings.value("display/bkgColor").value<QColor>();
    m_nodeColor = settings.value("display/nodeColor").value<QColor>();
    m_edgeColor = settings.value("display/edgeColor").value<QColor>();
    m_edgeWeight = settings.value("display/edgeWeight").toInt();
}



/*************************************************************************************************************
* Function: wrieConfig
*
* Abstract: This function writes the configuration to the defalut location 
*
* Params  : 
*
* Returns : 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void CConfig::writeConfig()
{
    QSettings   app(qstOrg, qstApp);

    app.setValue("configSet", true);

    app.setValue("font/fontFamily", m_strFontFamily);
    app.setValue("font/fontSize", m_nFontSize);
    app.setValue("font/fontWeight", m_nFontWeight);
    app.setValue("font/fontBold", m_bIsBold);

    app.setValue("display/bkgColor", m_bkgColor);
    app.setValue("display/edgeColor", m_edgeColor);
    app.setValue("display/nodeColor", m_nodeColor);
    app.setValue("display/edgeWeight", m_edgeWeight);
}



 /************************************************************************************************************
  * function: getFont
  *
  * abstract: returns an instance of QFont based on the parameters specified in the config class.
  *
  * input   :  void 
  *
  * returns : null if a font object could not be created, otherwise an instance of a QFont object.
  *
  * written : (G.K.Huber)
  ***********************************************************************************************************/
QFont* CConfig::getFont()
{
    QFont*   newFont = nullptr;
    
    newFont = new QFont;
    newFont->setFamily(m_strFontFamily);
    newFont->setPointSize(m_nFontSize);
    newFont->setWeight(m_nFontWeight);
    newFont->setBold(m_bIsBold);

    return newFont;
}



/************************************************************************************************************
 * function: setFont
 *
 * abstract: This function translates from a QFont structure to the various fields we maintain/
 *
 * input   :  QFont -- [in] a QFont structure representing the current fon
 *
 * returns :  void 
 *
 * written : (G.K.Huber)
 ***********************************************************************************************************/
void CConfig::setFont(QFont font)
{
    m_strFontFamily = font.family();
    m_nFontSize = font.pointSize();
    m_nFontWeight = font.weight();
    m_bIsBold = font.bold();
}
