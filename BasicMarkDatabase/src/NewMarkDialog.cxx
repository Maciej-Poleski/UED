#include <NewMarkDialog.hxx>

#include <QtGui/QMessageBox>

NewMarkDialog::NewMarkDialog( QWidget *parent ) :
	QDialog(parent)
{
	setupUi(this);
	leftWidget->setFixedWidth(leftWidget->minimumSizeHint().width());
	resize(minimumSizeHint().width() + 200, minimumSizeHint().height());

	dateEdit->setDate(QDate::currentDate());

	QChar com = QLocale::system().decimalPoint();

	QRegExp rx1(QString("\\d+(") + com + "\\d+)?/\\d+(" + com + "\\d+)?");
	QRegExpValidator* validator = new QRegExpValidator(rx1, this);
	absoluteLineEdit->setValidator(validator);

	QRegExp rx2(QString("([1-6](|\\+|\\-)?)|(\\d+(") + com + "\\d+)?)");
	validator = new QRegExpValidator(rx2, this);
	markLineEdit->setValidator(validator);

	connect(markLineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(checkMarkLineEdit(const QString&)));
}

NewMarkDialog::~NewMarkDialog()
{

}

void NewMarkDialog::check()
{
	if( ( classicRadioButton->isChecked() || modernRadioButton->isChecked() ) == false )
		QMessageBox::critical(this, tr("Select type"), tr("Select type of this mark!"));
	else if( absoluteCheckBox->isChecked() && !absoluteLineEdit->hasAcceptableInput() )
		QMessageBox::critical(this, tr("Absolute mark"), tr("Type correct absolute mark (fraction)!"));
	else if( !markLineEdit->hasAcceptableInput() )
		QMessageBox::critical(this, tr("Mark"), tr("Type correct mark!"));
	else
		accept();
}

void NewMarkDialog::checkMarkLineEdit( const QString &text )
{
	QChar com = QLocale::system().decimalPoint();
	QRegExp classicRx("[1-6](\\+|\\-)?");
	QRegExp modernRx(QString("\\d+(") + com + "\\d+)?");
	if( classicRx.exactMatch(text) && !modernRx.exactMatch(text) )
		classicRadioButton->toggle();
	else if( modernRx.exactMatch(text) && !classicRx.exactMatch(text) ) modernRadioButton->toggle();
}
