#include <QtCore/QLibraryInfo>
#include <QtCore/QLocale>
#include <QtCore/QTranslator>
#include <QtCore/QTextCodec>
#include <QtGui/QApplication>
#include <Core.hxx>

int main( int argc, char *argv[ ] )
{
	QApplication app(argc, argv);

	QTranslator qtTranslator;
	qtTranslator.load("qt_" + QLocale::system().name(),
		QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	app.installTranslator( &qtTranslator);

	QTranslator myappTranslator;
	myappTranslator.load("ued_core_" + QLocale::system().name());
	app.installTranslator( &myappTranslator);
	QTranslator myappTranslator1;
	myappTranslator1.load("ued_update_manager_" + QLocale::system().name(), qApp->applicationDirPath());
	app.installTranslator( &myappTranslator1);
	QTranslator myappTranslator2;
	myappTranslator2.load("ued_basicmarkdatabase_" + QLocale::system().name(), qApp->applicationDirPath());
	app.installTranslator( &myappTranslator2);
	QTranslator myappTranslator3;
	myappTranslator3.load("ued_basiceventdatabase_" + QLocale::system().name(), qApp->applicationDirPath());
	app.installTranslator( &myappTranslator3);
	QTranslator myappTranslator4;
	myappTranslator4.load("ued_basicdatabase_" + QLocale::system().name(), qApp->applicationDirPath());
	app.installTranslator( &myappTranslator4);

	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForTr(QTextCodec::codecForCStrings());

	( new Core::Core )->install();
	return app.exec();
}
