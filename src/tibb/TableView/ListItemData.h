/**
 * Appcelerator Titanium Mobile
 * Copyright (c) 2013 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License
 * Please see the LICENSE included with this distribution for details.
 */

#ifndef TI_LIST_ITEM_DATA_H
#define TI_LIST_ITEM_DATA_H

#include <QObject>
#include <QString>
#include <QUrl>

class ListItemData : public QObject {
    Q_OBJECT

    Q_PROPERTY(QUrl leftImage READ leftImage WRITE setLeftImage NOTIFY leftImageChanged)
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)

public:
    QUrl leftImage() const {
        return leftImage_;
    }

    void setLeftImage(const QUrl& image) {
        leftImage_ = image;
        emit leftImageChanged(image);
    }

    QString title() const {
        return title_;
    }

    void setTitle(const QString& title) {
        title_ = title;
        emit titleChanged(title);
    }

signals:
    void leftImageChanged(const QUrl& image);
    void titleChanged(const QString& title);

private:
    QUrl leftImage_;
    QString title_;
};

#endif
