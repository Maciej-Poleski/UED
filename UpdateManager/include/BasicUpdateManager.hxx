#ifndef BASICUPDATEMANAGER_HXX
#define BASICUPDATEMANAGER_HXX

#include <Core.hxx>

#include <QtCore/QObject>
#include <QtCore/QFile>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <UpdateManagerInterface.hxx>
#include <PluginInterface.hxx>

namespace Core
{
namespace UpdateManager
{

class CheckUpdates : protected QEventLoop
{
Q_OBJECT

	QList< PluginInterface* > plugins;
	QNetworkReply* networkReply;
public:
	QList< PluginInterface* > result;

	CheckUpdates( QList< PluginInterface* > plugins, QObject* parent );
	int exec();

signals:
	void checkNext();

private slots:
	void getNext();
	void gotNext();
};

class DownloadFile : protected QEventLoop
{
Q_OBJECT
private:
	QString destination;

public:
	QNetworkReply* reply;
	DownloadFile( QObject* parent, QString name, QString destination =
			QString() ) :
		QEventLoop(parent), destination(destination)
	{
		reply
				= core->getNetworkAccessManager()->get(
													   QNetworkRequest(
																	   QUrl(
																			name)));
		connect(reply, SIGNAL(finished()), this, SLOT(done()));
		exec();
	}
	~DownloadFile()
	{
		reply->deleteLater();
	}

public slots:
	void done()
	{
		if(reply->error())
			exit(reply->error());
		if( destination != QString() )
		{
			QFile dest(destination);
			dest.open(QFile::WriteOnly);
			dest.write(reply->readAll());
		}
		quit();
	}
};

/** Klasa realizująca podstawowe wymagania interfejsu UpdateManagerInterface. */
class BasicUpdateManager : public QObject,
						   public UpdateManagerInterface,
						   public PluginInterface
{
Q_OBJECT
Q_DISABLE_COPY(BasicUpdateManager)Q_INTERFACES(Core::PluginInterface)

	QList< PluginInterface* > plugins; ///< Lista plugin-ów zarządzanych przez ten menadżer.

public:
	BasicUpdateManager( QObject* parent = 0 ) :
		QObject(parent)
	{
	}
	~BasicUpdateManager()
	{
		uninstall();
	}
	virtual QString getName() const;
	virtual int getVersion() const;
	virtual void install();
	virtual void uninstall();
	virtual QStringList getFilesNames() const;
	virtual QStringList getPureLibraryFilesNames() const;

public:
	virtual QList< PluginInterface* > installUpdates( QList< PluginInterface* > plugins );
	virtual void registerPlugin( PluginInterface *plugin );
	virtual void unregisterPlugin( PluginInterface* plugin );
	virtual QList< PluginInterface* > checkUpdates();
	static QString parseName( PluginInterface *plugin );

};

}

}

#endif // BASICUPDATEMANAGER_HXX
