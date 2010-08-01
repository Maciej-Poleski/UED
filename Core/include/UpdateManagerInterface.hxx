#ifndef UPDATEMANAGERINTERFACE_HXX
#define UPDATEMANAGERINTERFACE_HXX

#include <QtCore/QObject>
#include "PluginInterface.hxx"

/** Interfejs menadżera aktualizacji.
  * Klasa implementująca ten interfejs musi odpowiadać za całość procesu utrzymywania oprogramowania aktualnego.
  */
class UpdateManagerInterface : public QObject
{
    Q_OBJECT

public:
    explicit UpdateManager(QObject *parent = 0)=0;
    virtual ~UpdateManager()=0;

signals:
    /** Sygnał emitowany w razie znalezienia aktualizacji do jakiegoś plugin-u.
      * @param plugin Plugin dla którego znaleziono aktualizacje.
      */
    void updateIsAvailable(PluginInterface* plugin);

public slots:
    /** Wykonuje instalację aktualizacji dla danego plugin-u od A od Z.
      * @param plugin Plugin którego aktualizacja zostanie zainstalowana.
      */
    virtual void installUpdate(PluginInterface* plugin) const=0;

    /** Rejestruje dany plugin w menadżerze aktualizacji. Od tej pory będzie on zarządzał aktualizacjami dla tego plugin-u.
      * @param plugin Plugin który zostanie zarejestrowany.
      */
    virtual void registerPlugin(PluginInterface* plugin)=0;

    /** Sprawdza czy są dostępne jakieś aktualizacje dla wszystkich zarejestrowanych pluginów. */
    virtual void checkUpdates() const=0;

};

Q_DECLARE_INTERFACE(UpdateManagerInterface,"UED.core.UpdateManagerInterface/1.0")

#endif // UPDATEMANAGERINTERFACE_HXX
