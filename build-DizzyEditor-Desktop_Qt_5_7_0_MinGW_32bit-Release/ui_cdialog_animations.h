/********************************************************************************
** Form generated from reading UI file 'cdialog_animations.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CDIALOG_ANIMATIONS_H
#define UI_CDIALOG_ANIMATIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CDialog_Animations
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QScrollArea *cScrollArea_Tiles;
    QWidget *cScrollAreaWidgetContents_Tiles;
    QPushButton *cPushButton_Delete;
    QPushButton *cPushButton_Clear;
    QScrollArea *cScrollArea_TilesSequence;
    QWidget *cScrollAreaWidgetContents_TilesSequence;
    QPushButton *cPushButton_Add;
    QPushButton *cPushButton_Apply;
    QPushButton *cPushButton_Cancel;
    QSpacerItem *horizontalSpacer;
    QComboBox *cComboBox_AnimationMode;

    void setupUi(QDialog *CDialog_Animations)
    {
        if (CDialog_Animations->objectName().isEmpty())
            CDialog_Animations->setObjectName(QStringLiteral("CDialog_Animations"));
        CDialog_Animations->resize(571, 377);
        gridLayout_2 = new QGridLayout(CDialog_Animations);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        cScrollArea_Tiles = new QScrollArea(CDialog_Animations);
        cScrollArea_Tiles->setObjectName(QStringLiteral("cScrollArea_Tiles"));
        cScrollArea_Tiles->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        cScrollArea_Tiles->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        cScrollArea_Tiles->setWidgetResizable(true);
        cScrollAreaWidgetContents_Tiles = new QWidget();
        cScrollAreaWidgetContents_Tiles->setObjectName(QStringLiteral("cScrollAreaWidgetContents_Tiles"));
        cScrollAreaWidgetContents_Tiles->setGeometry(QRect(0, 0, 359, 280));
        cScrollArea_Tiles->setWidget(cScrollAreaWidgetContents_Tiles);

        gridLayout->addWidget(cScrollArea_Tiles, 0, 0, 3, 2);

        cPushButton_Delete = new QPushButton(CDialog_Animations);
        cPushButton_Delete->setObjectName(QStringLiteral("cPushButton_Delete"));

        gridLayout->addWidget(cPushButton_Delete, 2, 4, 1, 1);

        cPushButton_Clear = new QPushButton(CDialog_Animations);
        cPushButton_Clear->setObjectName(QStringLiteral("cPushButton_Clear"));

        gridLayout->addWidget(cPushButton_Clear, 2, 2, 1, 1);

        cScrollArea_TilesSequence = new QScrollArea(CDialog_Animations);
        cScrollArea_TilesSequence->setObjectName(QStringLiteral("cScrollArea_TilesSequence"));
        cScrollArea_TilesSequence->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        cScrollArea_TilesSequence->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        cScrollArea_TilesSequence->setWidgetResizable(true);
        cScrollAreaWidgetContents_TilesSequence = new QWidget();
        cScrollAreaWidgetContents_TilesSequence->setObjectName(QStringLiteral("cScrollAreaWidgetContents_TilesSequence"));
        cScrollAreaWidgetContents_TilesSequence->setGeometry(QRect(0, 0, 146, 218));
        cScrollArea_TilesSequence->setWidget(cScrollAreaWidgetContents_TilesSequence);

        gridLayout->addWidget(cScrollArea_TilesSequence, 0, 2, 1, 3);

        cPushButton_Add = new QPushButton(CDialog_Animations);
        cPushButton_Add->setObjectName(QStringLiteral("cPushButton_Add"));

        gridLayout->addWidget(cPushButton_Add, 1, 2, 1, 3);

        cPushButton_Apply = new QPushButton(CDialog_Animations);
        cPushButton_Apply->setObjectName(QStringLiteral("cPushButton_Apply"));

        gridLayout->addWidget(cPushButton_Apply, 4, 2, 1, 3);

        cPushButton_Cancel = new QPushButton(CDialog_Animations);
        cPushButton_Cancel->setObjectName(QStringLiteral("cPushButton_Cancel"));

        gridLayout->addWidget(cPushButton_Cancel, 4, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 0, 1, 1);

        cComboBox_AnimationMode = new QComboBox(CDialog_Animations);
        cComboBox_AnimationMode->setObjectName(QStringLiteral("cComboBox_AnimationMode"));

        gridLayout->addWidget(cComboBox_AnimationMode, 3, 2, 1, 3);

        gridLayout->setColumnStretch(0, 1);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(CDialog_Animations);

        QMetaObject::connectSlotsByName(CDialog_Animations);
    } // setupUi

    void retranslateUi(QDialog *CDialog_Animations)
    {
        CDialog_Animations->setWindowTitle(QApplication::translate("CDialog_Animations", "\320\237\320\276\321\201\320\273\320\265\320\264\320\276\320\262\320\260\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\321\214 \320\260\320\275\320\270\320\274\320\260\321\206\320\270\320\270 \321\202\320\260\320\271\320\273\320\276\320\262", 0));
        cPushButton_Delete->setText(QApplication::translate("CDialog_Animations", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", 0));
        cPushButton_Clear->setText(QApplication::translate("CDialog_Animations", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\262\321\201\320\265", 0));
        cPushButton_Add->setText(QApplication::translate("CDialog_Animations", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", 0));
        cPushButton_Apply->setText(QApplication::translate("CDialog_Animations", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", 0));
        cPushButton_Cancel->setText(QApplication::translate("CDialog_Animations", "\320\236\321\202\320\274\320\265\320\275\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class CDialog_Animations: public Ui_CDialog_Animations {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CDIALOG_ANIMATIONS_H
