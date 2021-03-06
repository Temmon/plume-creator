#include "plmtestwidget.h"
#include "plmwidget.h"
#include "plmdata.h"
#include <QToolButton>
#include <QVBoxLayout>

PLMTestWidget::PLMTestWidget(QObject *parent) : QObject(parent),
    m_name("TestWidget")
{
    this->setProperty("name", m_name);
}

// -------------------------------------------------------------------

PLMTestWidget::~PLMTestWidget()
{}

// -------------------------------------------------------------------

QString PLMTestWidget::use() const
{
    return m_name;
}

void PLMTestWidget::setText()
{
    m_label->setText("loadedd");
}

// -------------------------------------------------------------------


void PLMTestWidget::instanciate(QWidget *parent)
{
    // dockBody

    m_dockBody = new PLMWidget(parent);
    QVBoxLayout *layout = new QVBoxLayout();

    m_dockBody->setLayout(layout);

    m_label = new QLabel();
    m_label->setText("label !");
    layout->addWidget(m_label);
    QLabel *lab = new QLabel();
    lab->setText("lab");
    layout->addWidget(lab);

    // dockHeader


    m_dockHeader = new QWidget(parent);
    QHBoxLayout *hlayout = new QHBoxLayout();

    m_dockHeader->setLayout(hlayout);
    QLabel *label = new QLabel();
    label->setText("label :-)");
    hlayout->addWidget(label);
    QToolButton *button = new QToolButton();
    button->setText("action");
    hlayout->addWidget(button);

    // connections

    connect(plmdata->projectHub(),
            &PLMProjectHub::projectLoaded,
            this,
            &PLMTestWidget::setText);
}

// -------------------------------------------------------------------

PLMBaseDockWidget * PLMTestWidget::dockBodyWidget(QWidget *parent)
{
    if (!m_dockBody) this->instanciate(parent);

    Q_ASSERT(!m_dockBody.isNull());
    return m_dockBody.data();
}

// -------------------------------------------------------------------
QWidget * PLMTestWidget::dockHeaderWidget(QWidget *parent)
{
    if (!m_dockHeader) this->instanciate(parent);

    Q_ASSERT(!m_dockHeader.isNull());
    return m_dockHeader.data();
}

PLMDockWidgetInterface * PLMTestWidget::clone() const
{
    return new PLMTestWidget(nullptr);
}
