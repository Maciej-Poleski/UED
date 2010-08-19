/*
 * AddMarkButton.hxx
 *
 *  Created on: 19-08-2010
 *      Author: evil
 */

#ifndef ADDMARKBUTTON_HXX_
#define ADDMARKBUTTON_HXX_

#include <QtGui/QPushButton>

#include <TypeInterface.hxx>

namespace MarkDatabase
{

class AddMarkButton : public QPushButton
{
Q_OBJECT
Q_DISABLE_COPY(AddMarkButton)
public:
	AddMarkButton( TypeInterface* type, QString text, QWidget* parent = 0 );
	~AddMarkButton()
	{
		// TODO Auto-generated destructor stub
	}
signals:
	void clicked( TypeInterface* );

private slots:
	void doClick();

private:
	TypeInterface* type;
};

}

#endif /* ADDMARKBUTTON_HXX_ */
