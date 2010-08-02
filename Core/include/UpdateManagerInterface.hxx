#ifndef UPDATEMANAGERINTERFACE_HXX
#define UPDATEMANAGERINTERFACE_HXX

#include <QtCore/QObject>
#include <QtCore/QList>
#include "PluginInterface.hxx"

/** Interfejs menadżera aktualizacji.
* Klasa implementująca ten interfejs musi odpowiadać za całość procesu utrzymywania oprogramowania aktualnego.
*/
class UpdateManagerInterface
{
    public:
	virtual ~UpdateManagerInterface() {};
	
    public:
	/** Wykonuje instalację aktualizacji dla danego plugin-u od A od Z.
	* @param plugins Lista plugin-ów któree zostaną zaaktualizowane.
	*/
	virtual void installUpdates(QList<PluginInterface*> plugins) const=0;
	
	/** Rejestruje dany plugin w menadżerze aktualizacji. Od tej pory będzie on zarządzał aktualizacjami dla tego plugin-u.
	* @param plugin Plugin który zostanie zarejestrowany.
	*/
	virtual void registerPlugin(PluginInterface* plugin)=0;
	
	/** Wyrejestrowuje dany plugin w menadżerze aktualizacji.
	* @param plugin Plugin ktry zostanie wyrejestrowany.
	*/
	virtual void unregisterPlugin(PluginInterface* plugin)=0;
	
	/** Sprawdza czy są dostępne jakieś aktualizacje dla wszystkich zarejestrowanych pluginów.
	* @return Lista plugin-ów wymagających aktualizacji.
	*/
	virtual QList<PluginInterface*> checkUpdates()=0;
	
};

Q_DECLARE_INTERFACE(UpdateManagerInterface,"UED.core.UpdateManagerInterface/1.0")

#endif // UPDATEMANAGERINTERFACE_HXX