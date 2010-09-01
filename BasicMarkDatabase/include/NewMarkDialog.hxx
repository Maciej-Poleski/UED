#ifndef NEWMARKDIALOG_H
#define NEWMARKDIALOG_H

#include <QtGui/QDialog>
#include "ui_NewMarkDialog.h"

class NewMarkDialog : public QDialog, public Ui::NewMarkDialog
{
Q_OBJECT
Q_DISABLE_COPY(NewMarkDialog)

public:
	NewMarkDialog( QWidget *parent = 0 );
	~NewMarkDialog();

	void disableDateEdit();

private slots:
	void check();
	void checkMarkLineEdit( const QString& );
};

inline void NewMarkDialog::disableDateEdit()
{
	dateEdit->setEnabled(false);
}

#endif // NEWMARKDIALOG_H
