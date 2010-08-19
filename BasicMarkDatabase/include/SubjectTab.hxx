/*
 * SubjectTab.hxx
 *
 *  Created on: 19-08-2010
 *      Author: evil
 */

#ifndef SUBJECTTAB_HXX_
#define SUBJECTTAB_HXX_

#include <QtGui/QWidget>

#include <QtGui/QGridLayout>
#include <QtCore/QDate>

#include <SubjectInterface.hxx>
#include <TypeInterface.hxx>
#include <MarkInterface.hxx>
#include <AbstractBasicMark.hxx>
#include <BasicMarkDatabase.hxx>

namespace MarkDatabase
{

class SubjectTab : public QWidget
{
Q_OBJECT
Q_DISABLE_COPY(SubjectTab)

public:
	SubjectTab( BasicMarkDatabase* database, SubjectInterface* subject, QWidget* parent = 0, bool clean =
			false );
	~SubjectTab()
	{
		// TODO Auto-generated destructor stub
	}

	SubjectInterface* getSubject() const
	{
		return subject;
	}

public slots:
	void update();

private slots:
	void addMark( TypeInterface* );

private:
	BasicMarkDatabase* database;
	SubjectInterface* subject;
	QGridLayout *layout;

	void populate();
};

}

#endif /* SUBJECTTAB_HXX_ */
