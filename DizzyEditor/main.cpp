#include "cmainwindow.h"
#include <QApplication>

int main(int argc,char *argv[])
{
 //для работы без установленной Qt требуется такая инициализация
 QStringList paths=QCoreApplication::libraryPaths();
 paths.append(".");
 paths.append("platforms");

 QApplication qApplication(argc,argv);
 qApplication.setStyle("motiff");
 CMainWindow cMainWindow;
 cMainWindow.show();
 return(qApplication.exec());
}
