/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_TABLEVIEWMANAGER_H_
#define TI_TABLEVIEWMANAGER_H_


#include "TiCore.h"
#include "../TiUITableView.h"

namespace bb
{
namespace cascades
{
class ListItemProvider;
class ListItemTypeMapper;
class VisualNode;
class ListView;
}
}
namespace TiUI {

class TableViewManager :
		public bb::cascades::ListItemProvider,
        public bb::cascades::ListItemTypeMapper
{
public:
	TableViewManager(TiUITableView*);
	bb::cascades::VisualNode * createItem(bb::cascades::ListView*, const QString &);
	void updateItem(	bb::cascades::ListView*,
						bb::cascades::VisualNode *,
						const QString &,
						const QVariantList &,
						const QVariant &);
	QString itemType(const QVariant &data, const QVariantList &indexPath);
private:
	TiUITableView *_tableView;
};

} /* namespace TiUI */
#endif /* TABLEVIEWMANAGER_H_ */
