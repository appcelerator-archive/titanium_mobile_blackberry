/*
 * TiEvent.h
 *
 *  Created on: Jul 12, 2013
 *      Author: penrique
 */

#ifndef TI_TIEVENT_H_
#define TI_TIEVENT_H_

#include <v8.h>
#include "Ti_Helper.h"

using namespace v8;
namespace Ti
{
class TiEventParameters;
class TiEvent {
public:
	TiEvent(Handle<Function>);
	virtual ~TiEvent();
	void fireWithParameters(Handle<Object>, Ti::TiEventParameters*);
	Persistent<Function> callback;
};
}
#endif /* TIEVENT_H_ */
