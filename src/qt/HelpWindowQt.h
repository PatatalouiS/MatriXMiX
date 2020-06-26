/*
 __  __       _        ___  ____  __ ___  __
|  \/  | __ _| |_ _ __(_) \/ /  \/  (_) \/ /
| |\/| |/ _` | __| '__| |\  /| |\/| | |\  /
| |  | | (_| | |_| |  | |/  \| |  | | |/  \
|_|  |_|\__,_|\__|_|  |_/_/\_\_|  |_|_/_/\_\

Copyright (C) 2019-2020, Sebia Hana, Cerbulean Ana-Maria, Boumaza Tarik, Olivié Maxime.

This file is part of MatriXMiX.

MatriXMiX is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MatriXMiX is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MatriXMiX.  If not, see <https://www.gnu.org/licenses/>

*/

#ifndef HELPWINDOWQT_H
#define HELPWINDOWQT_H
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>

/**
@class HelpWindowQT The class HelpWindowQT generate a new Window that must to
inform the user about the extern library QT used to generate the
graphic interface.
*/
class HelpWindowQt : public QDialog
{
    Q_OBJECT

private:
    QLabel* title;
    QLabel* logo;
    QGroupBox* introduction;
    QGroupBox* documentation;

public:
    /**
     * @brief Default constructor
     * @param [in] parent (\e pointer of QWidget)
     */
    HelpWindowQt(QWidget* parent);
    /**
     * @brief Default destructor
     */
    ~HelpWindowQt();
};

#endif
