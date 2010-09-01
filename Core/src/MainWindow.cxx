/*
 * MainWindow.cxx
 *
 *  Created on: 08-08-2010
 *      Author: evil
 */

#include <MainWindow.hxx>

#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QCloseEvent>
#include <QtGui/QLabel>
#include <QtGui/QTabWidget>

#include <Core.hxx>
#include <Repopulateable.hxx>

namespace Core
{

MainWindow::MainWindow( QWidget* parent ) :
	QMainWindow(parent)
{
	resize(600, 300);
	createMenuBar();
	createStatusBar();
	createCentralWidget();
}

MainWindow::~MainWindow()
{
	// TODO Auto-generated destructor stub
}

void MainWindow::createMenuBar()
{
	// Menu APPLICATION
	QMenu* applicationMenu = menuBar()->addMenu(tr("&Application"));
	applicationMenu->addAction(tr("&Update"), core, SLOT(doUpdate()));
	applicationMenu->addAction(tr("&Quit"), this, SLOT(aboutToQuit()), QKeySequence::Quit);

	// Menu HELP
	QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(tr("&About"), core, SLOT(about()));
}

void MainWindow::createStatusBar()
{
	statusBar()->addWidget(new QLabel(tr("Development Version")));
}

void MainWindow::createCentralWidget()
{
	tabWidget = new QTabWidget(this);
	setCentralWidget(tabWidget);
	connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged(int)));
}

void MainWindow::currentTabChanged( int index )
{
	Repopulateable* tab = dynamic_cast< Repopulateable* > (tabWidget->widget(index));
	if( tab )
		tab->repopulate();
}

void MainWindow::closeEvent( QCloseEvent *event )
{
	core->storePlugins();
	core->deletePlugins();
	event->accept();
}

void MainWindow::aboutToQuit()
{
	close();
}

}
