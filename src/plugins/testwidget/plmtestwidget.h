#ifndef PLMTESTWIDGET_H
#define PLMTESTWIDGET_H

#include <QLabel>
#include <QList>
#include <QObject>
#include <QString>

 #include "plmdockwidgetinterface.h"

// #include "plugininterface.h"

class PLMTestWidget : public QObject,
                      public PLMDockWidgetInterface {
    Q_OBJECT
    Q_PLUGIN_METADATA(
        IID "com.PlumeSoft.Plume-Creator.DockWidgetInterface/1.0" FILE
        "plmtestwidget.json")
    Q_INTERFACES(PLMDockWidgetInterface)

public:

    PLMTestWidget(QObject *parent = nullptr);
    ~PLMTestWidget();

    // BaseInterface

    QString use() const;
    QString name() const
    {
        return "TestWidget";
    }

    QString displayedName() const
    {
        return tr("Test Widget");
    }

    PLMBaseDockWidget* dockBodyWidget(QWidget *parent);

    QWidget          * dockHeaderWidget(QWidget *parent);

    Qt::Edge           getEdges() {
        return Qt::LeftEdge;
    }

    QString getParentWindowName() const {
        return "WriteWindow";
    }

    PLMDockWidgetInterface* clone() const;

private slots:

    void setText();

private:

    void instanciate(QWidget *parent);

    QString m_name;
    QLabel *m_label;
};

#endif // TESTWIDGET_H
