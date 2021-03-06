#include <BasicUpdateManager.hxx>
#include <Core.hxx>

#include <QtCore/QtPlugin>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtCore/QtGlobal>

namespace Core
{
namespace UpdateManager
{

static const char* NAME = "UED.Core.UpdateManager.BasicUpdateManager";
static const char* SERVER = "http://users.v-lo.krakow.pl/~evil92c/UED/";

#if QT_POINTER_SIZE==4
#ifdef Q_OS_WIN32
#define PLATFORM "WIN32.32"
#elif defined(Q_OS_LINUX)
#define PLATFORM "LINUX.32"
#endif
#elif QT_POINTER_SIZE==8
#ifdef Q_OS_WIN32
#define PLATFORM "WIN32.64"
#elif defined(Q_OS_LINUX)
#define PLATFORM "LINUX.64"
#endif
#endif

void BasicUpdateManager::install()
{
	core->setUpdateManager(this);
	registerPlugin(this);
}

void BasicUpdateManager::uninstall()
{
	core->setUpdateManager(0);
	unregisterPlugin(this);
}

int BasicUpdateManager::getVersion() const
{
	return VERSION;
}

QString BasicUpdateManager::getName() const
{
	return NAME;
}

QStringList BasicUpdateManager::getFilesNames() const
{
	return QStringList(CORE_EXECUTABLE);
}

QStringList BasicUpdateManager::getPureLibraryFilesNames() const
{
	return QStringList();
}

QList< PluginInterface* > BasicUpdateManager::installUpdates( QList< PluginInterface* > plugins )
{
	QStringList files, library, downloaded;
	foreach(PluginInterface* plugin,plugins)
		{
			DownloadFile download(this, QString(SERVER) + BasicUpdateManager::parseName(plugin)
					+ ".dir/.filesList");
			if( download.reply->error() )
			{
				plugins.removeAll(plugin);
				continue;
			}
			QStringList filesList;
			filesList = QString(download.reply->readAll()).split('\n', QString::SkipEmptyParts);
			foreach(QString name,filesList)
				{
					if( QFile(qApp->applicationDirPath() + "/" + name + ".file").exists() ) continue;
					DownloadFile(this, QString(SERVER) + BasicUpdateManager::parseName(plugin) + ".dir/"
							+ name, qApp->applicationDirPath() + "/" + name + ".file");
					if( !QFile(qApp->applicationDirPath() + "/" + name + ".file").exists() )
					{
						plugins.removeAll(plugin);
						continue;
					}
					downloaded << qApp->applicationDirPath() + "/" + name + ".file";
				}
		}
	foreach(PluginInterface* plugin,plugins)
		{
			files << plugin->getFilesNames();
			library << plugin->getLibraryFilesNames();
		}
	files.sort();
	library.sort();
	files.removeDuplicates();
	library.removeDuplicates();
	bool newCore = false; ///< Czy dokonano aktualizacji CORE.
	foreach(PluginInterface* plugin,plugins)
			if( !plugin->getFilesNames().contains(CORE_EXECUTABLE) )
			{
				/** TODO:
				 * Po usuni??ciu plugin-??w nie nast??puje ich deinstalacja w sencie QPluginLoader.
				 * Obej??ciem tego problemu jest zignorowanie przestarza??ych uchwyt??w i liczenie
				 * na to, ??e ich kod pozosta?? w pami??ci gdy fizyczne pliki zosta??y wykasowane.
				 * Po uruchomieniu destruktora interfejscu plugin-u nie ma mo??liwo??ci za??adowania
				 * go z powrotem.
				 * WORKAROUND:
				 * Pluginy w sensie QPluginLoader sk??adaj?? si?? z dok??adnie jednej biblioteki
				 * wsp????dzielonej. Nale??y pozby?? si?? plugin-??w wi??zanych statycznie na rzecz
				 * dynamicznych oraz stworzy?? kolejn?? metod?? interfejsu PluginInterface zwracaj??c??
				 * nazw?? tej biblioteki w formacie zale??nym od platformy. Korzystaj??c z tej nazwy
				 * mo??na nakaza?? QPluginLoader deinstalacje plugin-u. Po zako??czeniu mo??na za??adowa??
				 * go ponownie.
				 */
				//delete plugin;
				core->getUpdateManager()->unregisterPlugin(plugin); //WORKAROUND
			}
			else
				newCore = true;
	QStringList newFiles;
	foreach(QString file,files) // FIXME Przetestowa?? na Windowsie
			QFile(file).remove();
	foreach(QString lib,library)
			QFile(lib).remove();
	foreach(QString file,downloaded)
		{
			QFile fileHandler(file);
			QString newName = file;
			newName.remove(file.length() - 5, 5);
			QFile::remove(newName);
			fileHandler.rename(newName);
		}
	//if(!newCore)
	//	core->loadPlugins();
	return plugins;
}

void BasicUpdateManager::registerPlugin( PluginInterface* plugin )
{
	plugins << plugin;
}

void BasicUpdateManager::unregisterPlugin( PluginInterface* plugin )
{
	plugins.removeAll(plugin);
}

CheckUpdates::CheckUpdates( QList< PluginInterface* > plugins, QObject* parent ) :
	QEventLoop(parent), plugins(plugins), networkReply(0)
{
	connect(this, SIGNAL(checkNext()), this, SLOT(getNext()));
}

int CheckUpdates::exec()
{
	emit checkNext();
	return QEventLoop::exec();
}

void CheckUpdates::getNext()
{
	if( !plugins.isEmpty() )
	{
		QUrl *url = new QUrl(QString(SERVER) + BasicUpdateManager::parseName(plugins.back()) + ".check");
		QNetworkRequest *request = new QNetworkRequest( *url);
		networkReply = core->getNetworkAccessManager()->get( *request);
		connect(networkReply, SIGNAL(finished()), this, SLOT(gotNext()));
	}
	else
		quit();
}

void CheckUpdates::gotNext()
{
	fprintf(stderr, "f");
	int currentVersion = plugins.back()->getVersion();
	int availableVersion = networkReply->readAll().toInt(); // TODO bool* ok;
	if( availableVersion > currentVersion ) result << plugins.back();
	plugins.pop_back();
	networkReply->deleteLater();
	emit checkNext();
}

QString BasicUpdateManager::parseName( PluginInterface* plugin )
{
	QString parsed=PLATFORM ".";
	parsed += plugin->getName();
	parsed.replace('.', '/');
	return parsed;
}

QList< PluginInterface* > BasicUpdateManager::checkUpdates()
{
	CheckUpdates check(plugins, this);
	check.exec();
	return check.result;
}

}

}

Q_EXPORT_PLUGIN2(ued_basic_update_manager,Core::UpdateManager::BasicUpdateManager)
