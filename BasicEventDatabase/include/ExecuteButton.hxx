/*
 * ExecuteButton.hxx
 *
 *  Created on: 30-08-2010
 *      Author: evil
 */

#ifndef EXECUTEBUTTON_HXX_
#define EXECUTEBUTTON_HXX_

#include <QtGui/QPushButton>

#include <BasicEvent.hxx>

class ExecuteButton : public QPushButton
{
Q_OBJECT
Q_DISABLE_COPY(ExecuteButton)
public:
	ExecuteButton( EventDatabase::BasicEvent *event, QWidget *parent = 0 ) :
		QPushButton(tr("EXECUTE"), parent), event(event)
	{
		connect(this, SIGNAL(clicked()), this, SLOT(doClick()));

	}
	virtual ~ExecuteButton()
	{
	}

signals:
	void clicked( EventDatabase::BasicEvent* );

private slots:
	void doClick()
	{
		emit clicked(event);
	}

private:
	EventDatabase::BasicEvent *event;
};

#endif /* EXECUTEBUTTON_HXX_ */
