/***************************************************************************
*   Copyright (C) 2019 by Cyril Jacquet                                 *
*   cyril.jacquet@plume-creator.eu                                        *
*                                                                         *
*  Filename: writetreeview.h                                                   *
*  This file is part of Plume Creator.                                    *
*                                                                         *
*  Plume Creator is free software: you can redistribute it and/or modify  *
*  it under the terms of the GNU General Public License as published by   *
*  the Free Software Foundation, either version 3 of the License, or      *
*  (at your option) any later version.                                    *
*                                                                         *
*  Plume Creator is distributed in the hope that it will be useful,       *
*  but WITHOUT ANY WARRANTY; without even the implied warranty of         *
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
*  GNU General Public License for more details.                           *
*                                                                         *
*  You should have received a copy of the GNU General Public License      *
*  along with Plume Creator.  If not, see <http://www.gnu.org/licenses/>. *
***************************************************************************/
#ifndef WRITETREEVIEW_H
#define WRITETREEVIEW_H

#include <QObject>
#include <QTreeView>
#include "plmsheetproxymodel.h"

class WriteTreeView : public QTreeView {
public:

    WriteTreeView(QWidget *parent = nullptr);

private slots:

    void              setExpandStateToItems();
    QList<QModelIndex>allIndexesFromModel();
    QItemSelection    selectChildren(const QModelIndex& parent,
                                     bool               recursively) const;
    void              itemCollapsedSlot(QModelIndex index);
    void              itemExpandedSlot(QModelIndex index);
    void              itemClicked(QModelIndex index);

private:

    QString m_parentDockName;

    // clicks :
    int m_clicksCount;
    QModelIndex m_oldIndex;
    PLMSheetProxyModel *m_model;
};

#endif // WRITETREEVIEW_H
