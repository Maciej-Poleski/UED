/*
 * AddMarkButton.cxx
 *
 *  Created on: 19-08-2010
 *      Author: evil
 */

#include "../include/AddMarkButton.hxx"

namespace MarkDatabase
{

AddMarkButton::AddMarkButton( TypeInterface* type, QString text, QWidget* parent ) :
	QPushButton(text, parent), type(type)
{
	connect(this, SIGNAL(clicked()), this, SLOT(doClick()));
}

void AddMarkButton::doClick()
{
	emit clicked(type);
}

}
