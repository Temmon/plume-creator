/***************************************************************************
*   Copyright (C) 2019 by Cyril Jacquet                                 *
*   cyril.jacquet@plume-creator.eu                                        *
*                                                                         *
*  Filename: writingwindow.h                                                   *
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
#ifndef WRITINGWINDOW_H
#define WRITINGWINDOW_H

#include "plmwritingzone.h"
#include "plmbasesubwindow.h"

namespace Ui {
class PLMWritingWindow;
}

class PLMWritingWindow : public PLMBaseSubWindow {
    Q_OBJECT

public:

    explicit PLMWritingWindow(int id);
    ~PLMWritingWindow();
    void addDocument(int projectId,
                     int paperId);

signals:

public slots:

private slots:

private:

    void setupActions();

private:

    Ui::PLMWritingWindow *ui;
};

#endif // WRITINGWINDOW_H
