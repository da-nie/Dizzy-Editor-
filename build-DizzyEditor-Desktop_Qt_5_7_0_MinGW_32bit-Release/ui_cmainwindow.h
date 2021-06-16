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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "cmapeditor.h"

QT_BEGIN_NAMESPACE

class Ui_CMainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_basic;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QCheckBox *cCheckBox_Matherial_Barrier;
    QScrollArea *cScrollArea_Map;
    QWidget *cScrollAreaWidgetContents_Map;
    QScrollArea *CScrollArea_Tiles;
    QWidget *cScrollAreaWidgetContents_Tiles;
    CMapEditor *cMapEditor;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CMainWindow)
    {
        if (CMainWindow->objectName().isEmpty())
            CMainWindow->setObjectName(QStringLiteral("CMainWindow"));
        CMainWindow->resize(679, 554);
        centralWidget = new QWidget(CMainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_basic = new QGridLayout();
        gridLayout_basic->setSpacing(6);
        gridLayout_basic->setObjectName(QStringLiteral("gridLayout_basic"));
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

        gridLayout_3->addWidget(groupBox, 0, 0, 1, 1);


        gridLayout_basic->addWidget(widget, 1, 0, 1, 1);

        cScrollArea_Map = new QScrollArea(centralWidget);
        cScrollArea_Map->setObjectName(QStringLiteral("cScrollArea_Map"));
        cScrollArea_Map->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        cScrollArea_Map->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        cScrollArea_Map->setWidgetResizable(true);
        cScrollAreaWidgetContents_Map = new QWidget();
        cScrollAreaWidgetContents_Map->setObjectName(QStringLiteral("cScrollAreaWidgetContents_Map"));
        cScrollAreaWidgetContents_Map->setGeometry(QRect(0, 0, 198, 142));
        cScrollArea_Map->setWidget(cScrollAreaWidgetContents_Map);

        gridLayout_basic->addWidget(cScrollArea_Map, 2, 0, 1, 1);

        CScrollArea_Tiles = new QScrollArea(centralWidget);
        CScrollArea_Tiles->setObjectName(QStringLiteral("CScrollArea_Tiles"));
        CScrollArea_Tiles->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        CScrollArea_Tiles->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        CScrollArea_Tiles->setWidgetResizable(true);
        cScrollAreaWidgetContents_Tiles = new QWidget();
        cScrollAreaWidgetContents_Tiles->setObjectName(QStringLiteral("cScrollAreaWidgetContents_Tiles"));
        cScrollAreaWidgetContents_Tiles->setGeometry(QRect(0, 0, 198, 142));
        CScrollArea_Tiles->setWidget(cScrollAreaWidgetContents_Tiles);

        gridLayout_basic->addWidget(CScrollArea_Tiles, 0, 0, 1, 1);

        cMapEditor = new CMapEditor(centralWidget);
        cMapEditor->setObjectName(QStringLiteral("cMapEditor"));

        gridLayout_basic->addWidget(cMapEditor, 0, 1, 3, 1);

        gridLayout_basic->setRowStretch(0, 10);
        gridLayout_basic->setRowStretch(1, 10);
        gridLayout_basic->setRowStretch(2, 10);
        gridLayout_basic->setColumnStretch(0, 5);
        gridLayout_basic->setColumnStretch(1, 10);

        gridLayout->addLayout(gridLayout_basic, 0, 0, 1, 1);

        CMainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CMainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 679, 18));
        CMainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(CMainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CMainWindow->setStatusBar(statusBar);

        retranslateUi(CMainWindow);

        QMetaObject::connectSlotsByName(CMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CMainWindow)
    {
        CMainWindow->setWindowTitle(QApplication::translate("CMainWindow", "CMainWindow", 0));
        groupBox->setTitle(QApplication::translate("CMainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270 \320\274\320\260\321\202\320\265\321\200\320\270\320\260\320\273\320\260", 0));
        cCheckBox_Matherial_Barrier->setText(QApplication::translate("CMainWindow", "\320\237\321\200\320\265\320\263\321\200\320\260\320\264\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class CMainWindow: public Ui_CMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINWINDOW_H
