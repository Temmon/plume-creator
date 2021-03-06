/***************************************************************************
*   Copyright (C) 2016 by Cyril Jacquet                                 *
*   cyril.jacquet@plume-creator.eu                                        *
*                                                                         *
*  Filename: plmproject.h                                                   *
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

#ifndef PLMDATABASE_H
#define PLMDATABASE_H

#include <QObject>
#include <QHash>
#include <QtSql/QSqlDatabase>

#include "plmproperty.h"
#include "tree/plmtree.h"
#include "tree/plmsheettree.h"
#include "tree/plmnotetree.h"
#include "plmerror.h"
#include "plume_creator_data_global.h"

class EXPORT PLMProject : public QObject {
    Q_OBJECT

public:

    enum DBType { ProjectDB, UserDB };
    Q_ENUM(DBType)

    explicit PLMProject(QObject       *parent,
                        int            projectId,
                        const QString& fileName);
    ~PLMProject();
    PLMProperty * getProperty(const QString& tableName);
    PLMTree     * getTree(const QString& tableName);
    PLMSheetTree* sheetTree();
    PLMNoteTree * noteTree();
    QString       getType() const;
    void          setType(const QString& value);
    int           id() const;

    QString       getTempFileName() const;
    QString       getUserDBTempFileName() const;

    QString       getPath() const;
    PLMError      setPath(const QString& value);

    QString       getUserDBPath() const;

    QSqlDatabase  getSqlDb() const;
    QSqlDatabase  getUserSqlDb() const;
    QString       getIdNameFromTable(const QString    & tableName,
                                     PLMProject::DBType dbType = PLMProject::ProjectDB);

signals:

public slots:

private:

    QHash<QString, PLMProperty *>m_plmPropertyForTableNameHash;
    QHash<QString, PLMTree *>m_plmTreeForTableNameHash;
    QSqlDatabase m_sqlDb, m_userSqlDb;
    int m_projectId;
    PLMSheetTree *m_sheetTree;
    PLMNoteTree *m_noteTree;
    QString m_type, m_path;
};

#endif // PLMDATABASE_H
