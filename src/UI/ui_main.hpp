/*
 * @name Disk Usage Viewer
 * @author Branden Lee
 * @version 1.00
 * @license GNU LGPL v3
 * @brief Graphical User Interface for analyzing disk usage

 * Icons and images owned by their respective owners
 */

#ifndef UI_MAIN_H
#define UI_MAIN_H

/* boost 1.72.0
 * License: Boost Software License (similar to BSD and MIT)
 */
#include <boost/signals2.hpp>

/* QT 5.13.2-1
 * License: LGPLv3
 */
#include <QObject>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

namespace Ui {

class main : public QObject {
    Q_OBJECT
public:
  QAction *actionAbout;
  QAction *actionSave_As;
  QWidget *centralwidget;
  QHBoxLayout *horizontalLayout;
  QMenuBar *menubar;
  QMenu *menuFile;
  QMenu *menuHelp;
  QStatusBar *statusbar;
  QMainWindow *mainWindow;
  void setupUi(QMainWindow *main) {
    mainWindow = main;
    if (main->objectName().isEmpty())
      main->setObjectName(QString::fromUtf8("main"));
    main->resize(800, 600);
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/icons/file/icons8-pie-chart-30.png"),
                 QSize(), QIcon::Normal, QIcon::Off);
    main->setWindowIcon(icon);
    actionAbout = new QAction(main);
    actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
    actionSave_As = new QAction(main);
    actionSave_As->setObjectName(QString::fromUtf8("actionSave_As"));
    centralwidget = new QWidget(main);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    centralwidget->setAcceptDrops(false);
    horizontalLayout = new QHBoxLayout(centralwidget);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
    horizontalLayout->setSizeConstraint(QLayout::SetMaximumSize);
    main->setCentralWidget(centralwidget);
    menubar = new QMenuBar(main);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 21));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuHelp = new QMenu(menubar);
    menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
    main->setMenuBar(menubar);
    statusbar = new QStatusBar(main);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    main->setStatusBar(statusbar);

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuHelp->menuAction());
    menuFile->addAction(actionSave_As);
    menuHelp->addAction(actionAbout);

    connect(actionAbout, &QAction::triggered, this, &main::About);

    retranslateUi(main);

    QMetaObject::connectSlotsByName(main);

  } // setupUi

  void retranslateUi(QMainWindow *main) {
    main->setWindowTitle(
        QCoreApplication::translate("main", "Disk Usage Viewer", nullptr));
    actionAbout->setText(QCoreApplication::translate("main", "About", nullptr));
    actionSave_As->setText(
        QCoreApplication::translate("main", "Save As...", nullptr));
#if QT_CONFIG(tooltip)
    actionSave_As->setToolTip(
        QCoreApplication::translate("main", "Save As...", nullptr));
#endif // QT_CONFIG(tooltip)
    menuFile->setTitle(QCoreApplication::translate("main", "File", nullptr));
    menuHelp->setTitle(QCoreApplication::translate("main", "Help", nullptr));
  } // retranslateUi

  void About() {
    QMessageBox::about(mainWindow, "About Disk Usage Viewer",
                       "<h2>Disk Usage Viewer 1.0</h2><p>Author: Branded Lee "
                       "</p>"
                       "<p>Icons made by <a "
                       "href=\"https://icons8.com\" "
                       "title=\"ICONS8\">ICONS8</a> and <a "
                       "href=\"https://octicons.github.com/\" "
                       "title=\"Github\">Github</a></p>");
  }
};

} // namespace Ui

#endif // UI_MAIN_H
