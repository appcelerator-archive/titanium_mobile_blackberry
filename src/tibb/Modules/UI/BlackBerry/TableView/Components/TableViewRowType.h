/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TABLEVIEWROWTYPE_H_
#define TABLEVIEWROWTYPE_H_

namespace TiUI {

class TableViewRowType {
public:
	enum Type{
		Row,
		Section
	};
	virtual ~TableViewRowType(){}
	virtual TableViewRowType::Type getType() = 0;
};


} /* namespace TiUI */
#endif /* TABLEVIEWROWTYPE_H_ */
