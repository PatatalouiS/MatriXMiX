
#include "Error.h"
#include <QMessageBox>

void Error::showError(const QString& title, const QString& body, QWidget* parent)
{
    QMessageBox* error = new QMessageBox(parent);
    error->setAttribute(Qt::WA_DeleteOnClose, true);
    error->setFixedSize(650,200);
    error->setIcon(QMessageBox::Critical);
    error->setText(title);
    error->setInformativeText(body);
    error->show();
}
