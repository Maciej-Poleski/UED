/*
 * MainWindow.hxx
 *
 *  Created on: 08-08-2010
 *      Author: evil
 */

#ifndef MAINWINDOW_HXX_
#define MAINWINDOW_HXX_

#include <QtGui/QMainWindow>
#include <QtGui/QTabWidget>

namespace Core
{

class MainWindow : public QMainWindow
{
Q_OBJECT
Q_DISABLE_COPY(MainWindow)

	QTabWidget *tabWidget;

public:
	MainWindow( QWidget *parent = 0 );
	virtual ~MainWindow();
	void addTab1( QWidget* page, QString label )
	{
		tabWidget->addTab(page, label);
	}
	void delTab1( QWidget* page )
	{
		tabWidget->removeTab(tabWidget->indexOf(page));
	}

private:
	void createMenuBar();
	void createStatusBar();
	void createCentralWidget();
	void closeEvent( QCloseEvent *event );

private slots:
	void aboutToQuit();
	void currentTabChanged( int index );
};

}

#endif /* MAINWINDOW_HXX_ */
