#ifndef BASICUPDATEMANAGER_HXX
#define BASICUPDATEMANAGER_HXX

#include <QtCore/QObject>
#include <UpdateManagerInterface.hxx>
#include <PluginInterface.hxx>
#include <Core.hxx>

namespace Core
{
    namespace UpdateManager
    {
	
	class CheckUpdates : protected QEventLoop
	{
	    Q_OBJECT
	    
	    QList<PluginInterface*> plugins;
	    QNetworkReply*          networkReply;
	    public:
		QList<PluginInterface*> result;
		
		CheckUpdates(QList<PluginInterface*> plugins, QObject* parent);
		int exec();
		
	    signals:
		void checkNext();
		
	    private slots:
		void getNext();
		void gotNext();
		
	    private:
		QString parseCheckName(PluginInterface* plugin) const;
	};
	
	/** Klasa realizująca podstawowe wymagania interfejsu UpdateManagerInterface. */
	class BasicUpdateManager : public QObject, public UpdateManagerInterface, public PluginInterface
	{
	    Q_OBJECT
	    Q_DISABLE_COPY(BasicUpdateManager)
	    Q_INTERFACES(UpdateManagerInterface PluginInterface)
	    
	    QList<PluginInterface*> plugins;            ///< Lista plugin-ów zarządzanych przez ten menadżer.
	    
	    public:
		BasicUpdateManager(QObject* parent = 0) : QObject(parent) {}
		~BasicUpdateManager() {}
		virtual QString getName() const;
		virtual int getVersion() const;
		virtual void install();
		virtual void uninstall();
                virtual QStringList getFilesNames() const;
                virtual QStringList getLibraryFilesNames() const;
		
	    public:
		virtual void installUpdates(QList< PluginInterface* > plugins) const;
		virtual void registerPlugin(PluginInterface *plugin);
		virtual void unregisterPlugin(PluginInterface* plugin);
		virtual QList< PluginInterface* > checkUpdates();
		
	};
	
    }
    
}

#endif // BASICUPDATEMANAGER_HXX
