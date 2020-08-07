/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionClose;
    QAction *actionCloseAll;
    QAction *actionTile;
    QAction *actionCascade;
    QAction *actionNext;
    QAction *actionPrevious;
    QAction *actionAbout;
    QAction *actionAboutQt;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    QMenuBar *menuBar;
    QMenu *menuF;
    QMenu *menuE;
    QMenu *menuW;
    QMenu *menuH;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(761, 543);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/myImage/images/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("images/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName(QStringLiteral("actionSaveAs"));
        QIcon icon3;
        icon3.addFile(QStringLiteral("images/saveAs.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaveAs->setIcon(icon3);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon4;
        icon4.addFile(QStringLiteral("images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon4);
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        QIcon icon5;
        icon5.addFile(QStringLiteral("images/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon5);
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        QIcon icon6;
        icon6.addFile(QStringLiteral("images/redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon6);
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName(QStringLiteral("actionCut"));
        QIcon icon7;
        icon7.addFile(QStringLiteral("images/cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCut->setIcon(icon7);
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName(QStringLiteral("actionCopy"));
        QIcon icon8;
        icon8.addFile(QStringLiteral("images/copy.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy->setIcon(icon8);
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName(QStringLiteral("actionPaste"));
        QIcon icon9;
        icon9.addFile(QStringLiteral("images/paste.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPaste->setIcon(icon9);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionCloseAll = new QAction(MainWindow);
        actionCloseAll->setObjectName(QStringLiteral("actionCloseAll"));
        actionTile = new QAction(MainWindow);
        actionTile->setObjectName(QStringLiteral("actionTile"));
        actionCascade = new QAction(MainWindow);
        actionCascade->setObjectName(QStringLiteral("actionCascade"));
        actionNext = new QAction(MainWindow);
        actionNext->setObjectName(QStringLiteral("actionNext"));
        QIcon icon10;
        icon10.addFile(QStringLiteral("images/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNext->setIcon(icon10);
        actionPrevious = new QAction(MainWindow);
        actionPrevious->setObjectName(QStringLiteral("actionPrevious"));
        QIcon icon11;
        icon11.addFile(QStringLiteral("images/previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPrevious->setIcon(icon11);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon12;
        icon12.addFile(QStringLiteral("images/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon12);
        actionAboutQt = new QAction(MainWindow);
        actionAboutQt->setObjectName(QStringLiteral("actionAboutQt"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QStringLiteral("mdiArea"));

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 761, 26));
        menuF = new QMenu(menuBar);
        menuF->setObjectName(QStringLiteral("menuF"));
        menuE = new QMenu(menuBar);
        menuE->setObjectName(QStringLiteral("menuE"));
        menuW = new QMenu(menuBar);
        menuW->setObjectName(QStringLiteral("menuW"));
        menuH = new QMenu(menuBar);
        menuH->setObjectName(QStringLiteral("menuH"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuF->menuAction());
        menuBar->addAction(menuE->menuAction());
        menuBar->addAction(menuW->menuAction());
        menuBar->addAction(menuH->menuAction());
        menuF->addAction(actionNew);
        menuF->addAction(actionOpen);
        menuF->addAction(actionSave);
        menuF->addAction(actionSaveAs);
        menuF->addAction(actionExit);
        menuE->addAction(actionUndo);
        menuE->addAction(actionRedo);
        menuE->addAction(actionCut);
        menuE->addAction(actionCopy);
        menuE->addAction(actionPaste);
        menuW->addAction(actionClose);
        menuW->addAction(actionCloseAll);
        menuW->addAction(actionTile);
        menuW->addAction(actionCascade);
        menuW->addAction(actionNext);
        menuW->addAction(actionPrevious);
        menuH->addAction(actionAbout);
        menuH->addAction(actionAboutQt);
        mainToolBar->addAction(actionNew);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionOpen);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionSaveAs);
        mainToolBar->addAction(actionCut);
        mainToolBar->addAction(actionCopy);
        mainToolBar->addAction(actionPaste);
        mainToolBar->addAction(actionUndo);
        mainToolBar->addAction(actionRedo);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionNew->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272\346\226\207\344\273\266(&N)", 0));
#ifndef QT_NO_TOOLTIP
        actionNew->setToolTip(QApplication::translate("MainWindow", "\346\226\260\345\273\272\346\226\207\344\273\266(N)", 0));
#endif // QT_NO_TOOLTIP
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266(&O)", 0));
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
        actionSave->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230(&S)", 0));
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0));
        actionSaveAs->setText(QApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272(&A)", 0));
        actionExit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272(&X)", 0));
        actionUndo->setText(QApplication::translate("MainWindow", "\346\222\244\351\224\200(&U)", 0));
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", 0));
        actionRedo->setText(QApplication::translate("MainWindow", "\346\201\242\345\244\215&(R)", 0));
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Y", 0));
        actionCut->setText(QApplication::translate("MainWindow", "\345\211\252\345\210\207(&T)", 0));
        actionCut->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0));
        actionCopy->setText(QApplication::translate("MainWindow", "\345\244\215\345\210\266(&C)", 0));
        actionCopy->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", 0));
        actionPaste->setText(QApplication::translate("MainWindow", "\347\262\230\350\264\264(&V)", 0));
        actionPaste->setShortcut(QApplication::translate("MainWindow", "Ctrl+V", 0));
        actionClose->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255(&O)", 0));
        actionCloseAll->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\346\211\200\346\234\211\347\252\227\345\217\243(&A)", 0));
        actionTile->setText(QApplication::translate("MainWindow", "\345\271\263\351\223\272(&T)", 0));
        actionCascade->setText(QApplication::translate("MainWindow", "\345\261\202\345\217\240(&C)", 0));
        actionNext->setText(QApplication::translate("MainWindow", "\344\270\213\344\270\200\344\270\252(&X)", 0));
        actionNext->setShortcut(QApplication::translate("MainWindow", "Ctrl+Tab", 0));
        actionPrevious->setText(QApplication::translate("MainWindow", "\345\211\215\344\270\200\344\270\252(&V)", 0));
        actionPrevious->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Backtab", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216(&A)", 0));
        actionAboutQt->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216Qt(&Q)", 0));
        menuF->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", 0));
        menuE->setTitle(QApplication::translate("MainWindow", "\347\274\226\350\276\221(&E)", 0));
        menuW->setTitle(QApplication::translate("MainWindow", "\347\252\227\345\217\243(&Y)", 0));
        menuH->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251(&H)", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
