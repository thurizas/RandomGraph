#include "randomgraph.h"
#include "config.h"


#include <QApplication>
#include <QSettings>

bool   firstRun();
void   setupDefaultConfiguration();


// values used for configurations...
const char* pszOrg = "JHU-EP";
const char* pszApp = "EP635-436";



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(firstRun())
    {
        setupDefaultConfiguration();
    }

    CConfig::getInstance()->setPath(pszOrg, pszApp);
    CConfig::getInstance()->readConfig();

    RandomGraph w;
    w.show();
    return a.exec();
}



/************************************************************************************************************
 * function: firstRun
 *
 * abstract: This function attempts to load the configuration for the four locations that it could be stored 
 *           in, if all of these attempts fail, we assume that this is the first time that this application
 *           has been run on this host, and we then setup a base-line configuratin.
 *
 * input   :  void 
 *
 * returns :  bool -- returns false if we can find a configuation, true if not configuration is found.
 *
 * written : Created Jul 2016 (G.K.Huber)
 ***********************************************************************************************************/
bool firstRun()
{
    QSettings app(pszOrg, pszApp);

    return !app.contains(QString("configSet"));
}



/*************************************************************************************************************
* Function: setupDefaultConfiguration
*
* Abstract: This function builds a default configuration with, in my opinion, sensible default values
*
* Params  : void 
*
* Returns : void 
*
* Written : Created Jul 2016 (G.K.Huber)
*************************************************************************************************************/
void setupDefaultConfiguration()
{
    QSettings   app(pszOrg, pszApp);
    QColor      colorBlack(0,0,0,255);
    QColor      colorPYellow(255,255,128,255);

    app.setValue("configSet", true);

    app.setValue("font/fontFamily", "Courier New");
    app.setValue("font/fontSize", 10);
    app.setValue("font/fontWeight", 50);
    app.setValue("font/fontBold", false);

    app.setValue("display/bkgColor", colorPYellow);
    app.setValue("display/edgeColor", colorBlack);
    app.setValue("display/nodeColor", colorBlack);
    app.setValue("display/edgeWeight", 1);

}
