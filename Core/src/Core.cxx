#include "Core.hxx"
#include <QtCore/QtPlugin>
#include <QtCore/QPluginLoader>
#include <QtCore/QDir>
#include <QtCore/QTextCodec>
#include <QtCore/QTranslator>
#include <QtCore/QLibraryInfo>
#include <QtGui/QMessageBox>
#include <cstdio>
#include <QtCore/QDebug>
Q_IMPORT_PLUGIN(ued_basic_update_manager)

namespace Core
{

static const char* NAME = "UED.Core"; ///< Unikalna nazwa plugin-u.
static const char *FILES[ ] =
	{ CORE_EXECUTABLE };
/** Użyj QLibrary aby uzyskać właściwy prefiks i sufiks */
static const char *LIBRARY[ ] =
	{ };

Core *core = 0;

QStringList Core::getFilesNames() const
{
	int s = sizeof ( FILES ) / QT_POINTER_SIZE;
	QStringList result;
	for( int i = 0 ; i < s ; ++i )
	{
		result << FILES[i];
	}
	return result;
}

QStringList Core::getPureLibraryFilesNames() const
{
	int s = sizeof ( LIBRARY ) / QT_POINTER_SIZE;
	QStringList result;
	for( int i = 0 ; i < s ; ++i )
	{
		result << LIBRARY[i];
	}
	return result;
}

void Core::uninstall()
{
	updateManager->unregisterPlugin(this);
	core = 0; ///< Nie wiem czy ten kod zadziała. EDIT: powinien zadziałać
}

void Core::install()
{
	core = this;
	mainWindow = new MainWindow();
	loadPlugins();
	mainWindow->show();

	updateManager->registerPlugin(this); ///< Rejestruje główny moduł w menadżerze aktualizacji
}

void Core::loadPlugins()
{
	foreach(QObject *pluginInstance, QPluginLoader::staticInstances())
		{
			PluginInterface* plugin = qobject_cast< PluginInterface* > (pluginInstance);
			if( plugin )
			{
				plugin->install();
				qDebug() << plugin->getFilesNames() << plugin->getLibraryFilesNames() << plugin->getName();
			}
			else
			{
				// TODO Tutaj przydałby się wyjątek
			}
		}
	QDir pluginsDir(qApp->applicationDirPath());
	foreach (QString fileName, pluginsDir.entryList(QDir::Files))
		{
			QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
			QObject *objectPlugin = loader.instance();
			if( objectPlugin )
			{
				PluginInterface* plugin = qobject_cast< PluginInterface* > (objectPlugin);
				if( plugin )
				{
					//try
					//{
					plugin->install();
					qDebug() << plugin->getFilesNames() << plugin->getLibraryFilesNames()
							<< plugin->getName();
					//}
					//catch( Exception e )
					//{
					//	qDebug() << e.what();
					//}
				}
				else
				{
					qDebug() << "Nie powiodło się " << pluginsDir.absoluteFilePath(fileName).toLocal8Bit()
							<< " Załadowane, ale nie posiada interfejsu";
				}
			} // ELSE jest niepotrzebne - interesują nas tylko poprawne pliki bibliotek współdzielonych
			else
			{
				qDebug() << "Nie powiodło się " << pluginsDir.absoluteFilePath(fileName).toLocal8Bit();
			}
		}
}

Core::Core() throw( Exception ) :
	database(0), marksDatabase(0), eventsDatabase(0), mainWindow(0)
{
	//loadLocalization();
	//initializeQt();

	if( core )
		throw Exception(tr("Core already exist!"));
	networkAccessManager = new QNetworkAccessManager(this);
}
/*
 void Core::initializeQt()
 {
 QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
 QTextCodec::setCodecForTr(QTextCodec::codecForCStrings());
 }

 void Core::loadLocalization()
 {
 qDebug() << "Ładowanie lokalizacji";
 QTranslator qtTranslator;
 qtTranslator.load("qt_" + QLocale::system().name(),
 QLibraryInfo::location(QLibraryInfo::TranslationsPath));
 installTranslator( &qtTranslator);

 QTranslator myappTranslator;
 if( !myappTranslator.load("ued_core_" + QLocale::system().name()) )
 throw "aaa";
 installTranslator( &myappTranslator);
 }*/

Core::~Core() throw()
{
}

int Core::getVersion() const
{
	return VERSION;
}

QString Core::getName() const
{
	return NAME;
}

void Core::about()
{
	QMessageBox::about(mainWindow, tr("Underground Electronic Diary"), tr(
		"This version is under development. Report bugs and suggestions via e-mail, GG, whatever."));
}

temporary void Core::doUpdate()
{
	QList< PluginInterface* > needUpdate = updateManager->checkUpdates();
	fprintf(stderr, "A");
	if( needUpdate.isEmpty() )
		return;
	QString message = QString::fromUtf8("Dostępne są aktualizacje następujących modułów:\n");
	foreach(PluginInterface* plugin,needUpdate)
			message += plugin->getName() + "\n";
	message += QString::fromUtf8("Instalować?");
	if( QMessageBox::information(mainWindow, QString::fromUtf8("Dostępne są aktualizacje"), message,
		QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes )
	{
		QList< PluginInterface* > list = updateManager->installUpdates(needUpdate);
		foreach(PluginInterface* plugin,list)
			{
				qDebug() << plugin->getName();
			}
	}
}

}
