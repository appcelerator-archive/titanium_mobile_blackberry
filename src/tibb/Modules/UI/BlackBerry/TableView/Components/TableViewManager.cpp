/*
 * Appcelerator Titanium Mobile
 * Copyright (c) 2014 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#include "TableViewManager.h"

#include <bb/cascades/ListItemProvider>
#include <bb/cascades/ListItemTypeMapper>
#include <bb/cascades/VisualNode>
#include <bb/cascades/ListView>
#include <bb/cascades/StandardListItem>
#include <bb/cascades/Header>

#include "TableViewRow.h"
#include "TableViewRowContainer.h"

static QString const LIST_ITEM_HEADER = "header";
static QString const LIST_ITEM_SIMPLE = "simple";
static QString const LIST_ITEM_CUSTOM = "custom";

namespace TiUI {

TableViewManager::TableViewManager(TiUITableView *tableView) : _tableView(tableView)
{

}

bb::cascades::VisualNode * TableViewManager::createItem(bb::cascades::ListView*, const QString &type)
{

	if(type == LIST_ITEM_SIMPLE)
	{
		bb::cascades::StandardListItem* a = new bb::cascades::StandardListItem();
		return a;
	}
	else if(type == LIST_ITEM_HEADER)
	{
		return new bb::cascades::Header();
	}

	return new TableViewRow(_tableView);
}
void TableViewManager::updateItem(	bb::cascades::ListView*,
									bb::cascades::VisualNode *control,
									const QString &type,
									const QVariantList & variantList,
									const QVariant &data)
{
	TableViewRowContainer* cell = qvariant_cast<TableViewRowContainer*>(data);

	if(type == LIST_ITEM_SIMPLE)
	{
		bb::cascades::StandardListItem* row = static_cast<bb::cascades::StandardListItem*>(control);

		QString title = cell->getTitle();
		QString image = cell->getLeftImage();

		if(title.isEmpty() || title.isNull() || title.length() == 0)
		{
			row->resetTitle();
		}
		else
		{
			row->setTitle(title);
		}
		if(image.isEmpty() || image.isNull() || image.length() == 0)
		{
			row->resetImage();
		}
		else
		{
			row->setImageSource(QUrl(Ti::TiHelper::getAssetPath(image)));
		}
	}
	else if(type == LIST_ITEM_HEADER)
	{
		bb::cascades::Header* row = static_cast<bb::cascades::Header*>(control);
		QString header = cell->getHeader();
		QString subHeader = cell->getSubHeader();

		if(header.isEmpty() || header.isNull() || header.length() == 0)
		{
			row->resetTitle();
		}
		else
		{
			row->setTitle(header);
		}
		if(subHeader.isEmpty() || subHeader.isNull() || subHeader.length() == 0)
		{
			row->resetSubtitle();
		}
		else
		{
			row->setSubtitle(subHeader);
		}

	}
	else
	{
		TableViewRow* row = static_cast<TableViewRow*>(control);
		row->replaceView(cell->getView());
	}
};

QString TableViewManager::itemType(const QVariant &data, const QVariantList &)
{
	TableViewRowContainer* cell = qvariant_cast<TableViewRowContainer*>(data);
	return cell->getType();
}

} /* namespace TiUI */
