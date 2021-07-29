/********************************************************************************
** Form generated from reading UI file 'cmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMAINWINDOW_H
#define UI_CMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "cmapeditor.h"

QT_BEGIN_NAMESPACE

class Ui_CMainWindow
{
public:
    QAction *cAction_SaveMap;
    QAction *cAction_LoadMap;
    QAction *cAction_ExportMap;
    QAction *cAction_SaveMapAs;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_basic;
    CMapEditor *cMapEditor;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QCheckBox *cCheckBox_Matherial_Barrier;
    QCheckBox *cCheckBox_Matherial_FirstPlane;
    QLineEdit *cLineEdit_PartName;
    QPushButton *cPushButton_SetPartName;
    QCheckBox *cCheckBox_Matherial_BeforeBackground;
    QScrollArea *cScrollArea_Tiles;
    QWidget *cScrollAreaWidgetContents_Tiles;
    QMenuBar *menuBar;
    QMenu *menu;
    QStatusBar *statusBar;
    QToolBar *cToolBar_Main;

    void setupUi(QMainWindow *CMainWindow)
    {
        if (CMainWindow->objectName().isEmpty())
            CMainWindow->setObjectName(QStringLiteral("CMainWindow"));
        CMainWindow->resize(679, 554);
        cAction_SaveMap = new QAction(CMainWindow);
        cAction_SaveMap->setObjectName(QStringLiteral("cAction_SaveMap"));
        cAction_LoadMap = new QAction(CMainWindow);
        cAction_LoadMap->setObjectName(QStringLiteral("cAction_LoadMap"));
        cAction_ExportMap = new QAction(CMainWindow);
        cAction_ExportMap->setObjectName(QStringLiteral("cAction_ExportMap"));
        cAction_SaveMapAs = new QAction(CMainWindow);
        cAction_SaveMapAs->setObjectName(QStringLiteral("cAction_SaveMapAs"));
        centralWidget = new QWidget(CMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_basic = new QGridLayout();
        gridLayout_basic->setSpacing(6);
        gridLayout_basic->setObjectName(QStringLiteral("gridLayout_basic"));
        cMapEditor = new CMapEditor(centralWidget);
        cMapEditor->setObjectName(QStringLiteral("cMapEditor"));

        gridLayout_basic->addWidget(cMapEditor, 0, 1, 3, 1);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        cCheckBox_Matherial_Barrier = new QCheckBox(groupBox);
        cCheckBox_Matherial_Barrier->setObjectName(QStringLiteral("cCheckBox_Matherial_Barrier"));
        cCheckBox_Matherial_Barrier->setGeometry(QRect(10, 20, 181, 18));
        cCheckBox_Matherial_FirstPlane = new QCheckBox(groupBox);
        cCheckBox_Matherial_FirstPlane->setObjectName(QStringLiteral("cCheckBox_Matherial_FirstPlane"));
        cCheckBox_Matherial_FirstPlane->setGeometry(QRect(10, 40, 181, 18));
        cLineEdit_PartName = new QLineEdit(groupBox);
        cLineEdit_PartName->setObjectName(QStringLiteral("cLineEdit_PartName"));
        cLineEdit_PartName->setGeometry(QRect(10, 80, 181, 20));
        cPushButton_SetPartName = new QPushButton(groupBox);
        cPushButton_SetPartName->setObjectName(QStringLiteral("cPushButton_SetPartName"));
        cPushButton_SetPartName->setGeometry(QRect(10, 110, 181, 21));
        cCheckBox_Matherial_BeforeBackground = new QCheckBox(groupBox);
        cCheckBox_Matherial_BeforeBackground->setObjectName(QStringLiteral("cCheckBox_Matherial_BeforeBackground"));
        cCheckBox_Matherial_BeforeBackground->setGeometry(QRect(10, 60, 181, 18));

        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);


        gridLayout_basic->addWidget(widget, 2, 0, 1, 1);

        cScrollArea_Tiles = new QScrollArea(centralWidget);
        cScrollArea_Tiles->setObjectName(QStringLiteral("cScrollArea_Tiles"));
        cScrollArea_Tiles->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        cScrollArea_Tiles->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        cScrollArea_Tiles->setWidgetResizable(true);
        cScrollAreaWidgetContents_Tiles = new QWidget();
        cScrollAreaWidgetContents_Tiles->setObjectName(QStringLiteral("cScrollAreaWidgetContents_Tiles"));
        cScrollAreaWidgetContents_Tiles->setGeometry(QRect(0, 0, 198, 299));
        cScrollArea_Tiles->setWidget(cScrollAreaWidgetContents_Tiles);

        gridLayout_basic->addWidget(cScrollArea_Tiles, 0, 0, 2, 1);

        gridLayout_basic->setRowStretch(0, 10);
        gridLayout_basic->setRowStretch(1, 10);
        gridLayout_basic->setRowStretch(2, 10);
        gridLayout_basic->setColumnStretch(0, 5);
        gridLayout_basic->setColumnStretch(1, 10);

        gridLayout->addLayout(gridLayout_basic, 0, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);
        CMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 679, 18));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        CMainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(CMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CMainWindow->setStatusBar(statusBar);
        cToolBar_Main = new QToolBar(CMainWindow);
        cToolBar_Main->setObjectName(QStringLiteral("cToolBar_Main"));
        CMainWindow->addToolBar(Qt::TopToolBarArea, cToolBar_Main);

        menuBar->addAction(menu->menuAction());
        menu->addAction(cAction_LoadMap);
        menu->addSeparator();
        menu->addAction(cAction_SaveMap);
        menu->addAction(cAction_SaveMapAs);
        menu->addSeparator();
        menu->addAction(cAction_ExportMap);
        cToolBar_Main->addSeparator();

        retranslateUi(CMainWindow);

        QMetaObject::connectSlotsByName(CMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CMainWindow)
    {
        CMainWindow->setWindowTitle(QApplication::translate("CMainWindow", "Dizzy Map Editor v1.0", 0));
        cAction_SaveMap->setText(QApplication::translate("CMainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\321\200\321\202\321\203..", 0));
        cAction_LoadMap->setText(QApplication::translate("CMainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\272\320\260\321\200\321\202\321\203..", 0));
        cAction_ExportMap->setText(QApplication::translate("CMainWindow", "\320\255\320\272\321\201\320\277\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\272\320\260\321\200\321\202\321\203", 0));
        cAction_SaveMapAs->setText(QApplication::translate("CMainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\260\321\200\321\202\321\203 \320\272\320\260\320\272..", 0));
        groupBox->setTitle(QApplication::translate("CMainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\261\320\273\320\276\320\272\320\276\320\262", 0));
        cCheckBox_Matherial_Barrier->setText(QApplication::translate("CMainWindow", "\320\237\321\200\320\265\320\263\321\200\320\260\320\264\320\260", 0));
        cCheckBox_Matherial_FirstPlane->setText(QApplication::translate("CMainWindow", "\320\237\320\265\321\200\320\265\320\264\320\275\320\270\320\271 \320\277\320\273\320\260\320\275", 0));
        cPushButton_SetPartName->setText(QApplication::translate("CMainWindow", "\320\227\320\260\320\264\320\260\321\202\321\214 \320\270\320\274\321\217 \320\274\320\260\321\202\320\265\321\200\320\270\320\260\320\273\321\203", 0));
        cCheckBox_Matherial_BeforeBackground->setText(QApplication::translate("CMainWindow", "\320\222\321\213\320\262\320\276\320\264\320\270\321\202\321\201\321\217 \320\277\320\265\321\200\320\265\320\264 \321\204\320\276\320\275\320\276\320\274", 0));
        menu->setTitle(QApplication::translate("CMainWindow", "\320\244\320\260\320\271\320\273", 0));
        cToolBar_Main->setWindowTitle(QApplication::translate("CMainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class CMainWindow: public Ui_CMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINWINDOW_H
