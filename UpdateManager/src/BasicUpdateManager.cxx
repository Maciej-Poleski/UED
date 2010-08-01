#include "BasicUpdateManager.hxx"
#include <Core.hpp>

#include <QtCore/QtPlugin>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtCore/QtGlobal>

namespace Core
{
    namespace UpdateManager
    {
	
	static const char* NAME="UED.Core.UpdateManager.BasicUpdateManager";
	static const char* SERVER="http://users.v-lo.krakow.pl/~evil92c/UED/";
	
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
	}
	
	int BasicUpdateManager::getVersion() const
	{
	    return VERSION;
	}
	
	QString BasicUpdateManager::getName() const
	{
	    return NAME;
	}
	
	void BasicUpdateManager::installUpdates(QList<PluginInterface*> plugins) const
	{
	    // STUB
	}
	
	void BasicUpdateManager::registerPlugin(PluginInterface* plugin)
	{
	    plugins<<plugin;
	}
	
	void BasicUpdateManager::unregisterPlugin(PluginInterface* plugin)
	{
	    plugins.removeAll(plugin);
	}
	
	CheckUpdates::CheckUpdates(QList<PluginInterface*> plugins, QObject* parent) : QEventLoop(parent), plugins(plugins)
	{
	    connect(this,SIGNAL(checkNext()),this,SLOT(getNext()));
	}
	
	int CheckUpdates::exec()
	{
	    emit checkNext();
	    return QEventLoop::exec();
	}
	
	void CheckUpdates::getNext()
	{
	    if(!plugins.isEmpty())
	    {
		networkReply=core->getNetworkAccessManager()->get(QNetworkRequest(QUrl(QString(SERVER)+parseCheckName(plugins.back()))));
		connect(networkReply,SIGNAL(finished()),this,SLOT(gotNext()));
	    }
	    else
		quit();
	}
	
	void CheckUpdates::gotNext()
	{
	    int currentVersion=plugins.back()->getVersion();
	    int availableVersion=networkReply->readAll().toInt();   // FIXME bool* ok;
	    if(availableVersion>currentVersion)
		result<<plugins.back();
	    plugins.pop_back();
	    networkReply->deleteLater();
	    emit checkNext();
	}
	
	QString CheckUpdates::parseCheckName(PluginInterface* plugin) const
	{
	    QString parsed=PLATFORM ".";
	    parsed+=plugin->getName();
	    parsed.replace('.','/');
	    return parsed+".check";
	}
	
	QList<PluginInterface*> BasicUpdateManager::checkUpdates()
	{
	    CheckUpdates check(plugins,this);
	    check.exec();
	    return check.result;
	}
	
    }
    
}

Q_EXPORT_PLUGIN2(ued_basic_update_manager,Core::UpdateManager::BasicUpdateManager)