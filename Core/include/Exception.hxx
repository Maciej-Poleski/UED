#ifndef EXCEPTION_HXX
#define EXCEPTION_HXX

class Exception
{
	QString message;
public:
	Exception( QString msg ) :
		message(msg)
	{
	}
	QString what() const
	{
		return message;
	}
};

#endif
