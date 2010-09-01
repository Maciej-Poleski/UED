/*
 * Storeable.hxx
 *
 *  Created on: 31-08-2010
 *      Author: evil
 */

#ifndef STOREABLE_HXX_
#define STOREABLE_HXX_

class Storeable
{
public:
	virtual ~Storeable()
	{
		// TODO Auto-generated destructor stub
	}

	virtual void store() const=0;

	virtual void restore()=0;
};

#endif /* STOREABLE_HXX_ */
