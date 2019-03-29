/*
    Copyright (c) 2008-2019 Jan W. Krieger (<jan@jkrieger.de>)

    

    This software is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License (LGPL) as published by
    the Free Software Foundation, either version 2.1 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License (LGPL) for more details.

    You should have received a copy of the GNU Lesser General Public License (LGPL)
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



#include "jkqtplotter/jkqtpgraphssinglecolumnsymbols.h"
#include "jkqtplotter/jkqtpbaseplotter.h"
#include <stdlib.h>
#include <QDebug>
#include <iostream>
#include "jkqtplottertools/jkqtptools.h"
#include "jkqtplotter/jkqtpbaseelements.h"
#include "jkqtplotter/jkqtplotter.h"
#include "jkqtplottertools/jkqtpdrawingtools.h"
#include <random>

#define SmallestGreaterZeroCompare_xvsgz() if ((xvsgz>10.0*DBL_MIN)&&((smallestGreaterZero<10.0*DBL_MIN) || (xvsgz<smallestGreaterZero))) smallestGreaterZero=xvsgz;




JKQTPSingleColumnSymbolsGraph::JKQTPSingleColumnSymbolsGraph(JKQTBasePlotter *parent):
    JKQTPSingleColumnGraph(parent), seedValue(123456)
{
    color=QColor("red");
    style=Qt::SolidLine;
    lineWidth=2;
    parentPlotStyle=-1;
    symbolSize=12;
    symbolWidth=1;
    symbol=JKQTPNoSymbol;
    dataDirection=DataDirection::Y;
    position=0;

    if (parent) { // get style settings from parent object
        parentPlotStyle=parent->getNextStyle();
        //std::cout<<"got style settings from parent: "<<parentPlotStyle<<std::endl;
        int parentPlotStyle=parent->getNextStyle();
        color=parent->getPlotStyle(parentPlotStyle).color();
        fillColor=parent->getPlotStyle(parentPlotStyle).fillColor();
        style=parent->getPlotStyle(parentPlotStyle).style();
        lineWidth=parent->getPlotStyle(parentPlotStyle).widthF();
        symbolSize=parent->getPlotStyle(parentPlotStyle).symbolSize();
        symbolWidth=parent->getPlotStyle(parentPlotStyle).symbolLineWidthF();
        symbol=parent->getPlotStyle(parentPlotStyle).symbol();
    }
    fillColor=color;
}



JKQTPSingleColumnSymbolsGraph::JKQTPSingleColumnSymbolsGraph(JKQTPlotter *parent):
    JKQTPSingleColumnSymbolsGraph(parent->getPlotter())
{

}


bool JKQTPSingleColumnSymbolsGraph::getXMinMax(double &minx, double &maxx, double &smallestGreaterZero)
{
    if (dataDirection==DataDirection::X) {
        return getDataMinMax(dataColumn, minx, maxx, smallestGreaterZero);
    } else {
        minx=position;
        maxx=position;
        if (positionScatterStyle!=NoScatter) {
            minx=position-width/2;
            maxx=position+width/2;
        }
        return true;
        //smallestGreaterZero=qMax(double(0.0), qMin(baseline, baseline+peakHeight));
    }
}

bool JKQTPSingleColumnSymbolsGraph::getYMinMax(double &miny, double &maxy, double &smallestGreaterZero)
{
    if (dataDirection==DataDirection::Y) {
        return getDataMinMax(dataColumn, miny, maxy, smallestGreaterZero);
    } else {
        miny=position;
        maxy=position;
        if (positionScatterStyle!=NoScatter) {
            miny=position-width/2;
            maxy=position+width/2;
        }
        return true;
        //smallestGreaterZero=qMax(double(0.0), qMin(baseline, baseline+peakHeight));
    }
}

void JKQTPSingleColumnSymbolsGraph::draw(JKQTPEnhancedPainter &painter)
{
#ifdef JKQTBP_AUTOTIMER
    JKQTPAutoOutputTimer jkaaot("JKQTPSingleColumnSymbolsGraph::draw");
#endif
    if (parent==nullptr) return;
    JKQTPDatastore* datastore=parent->getDatastore();
    if (datastore==nullptr) return;
    if (dataColumn<0) return;

    drawErrorsBefore(painter);
    {
        painter.save(); auto __finalpaint=JKQTPFinally([&painter]() {painter.restore();});

        int imax=static_cast<int>(datastore->getColumn(static_cast<size_t>(dataColumn)).getRows());
        int imin=0;
        if (imax<imin) {
            int h=imin;
            imin=imax;
            imax=h;
        }
        if (imin<0) imin=0;
        if (imax<0) imax=0;

        std::random_device rd; // random number generators:
        std::minstd_rand gen{rd()};
        gen.seed(seedValue);
        std::uniform_real_distribution<> dRandomScatter{position-width/2.0, position+width/2.0};

        const double symSize=parent->pt2px(painter, symbolSize);


        QVector<QPointF> plotSymbols; // collects symbol locations e.g. for BeeSwarmScatter-plots
        plotSymbols.reserve(qMax(100,imax-imin));
        auto doesCollide=[&plotSymbols,&symSize](double x, double y)->bool {
            for (auto& p: plotSymbols) {
                if (fabs(p.x()-x)<symSize && fabs(p.y()-y)<symSize) {
                    return true;
                }
            }
            return false;
        };

        if (dataDirection==DataDirection::X) {
            intSortData();
            for (int iii=imin; iii<imax; iii++) {
                int i=qBound<int>(imin, getDataIndex(static_cast<int>(iii)), imax);
                const double xv=datastore->get(dataColumn,i);
                double yv=position;
                if (positionScatterStyle==RandomScatter) {
                    yv=dRandomScatter(gen);
                }
                const double x=transformX(xv);
                double y=transformY(yv);
                if (positionScatterStyle==BeeSwarmScatter) {
                    while (doesCollide(x,y)) {
                        if (i%2==0) {
                            y=y-symSize;
                        } else {
                            y=y+symSize;
                        }
                    }
                }
                plotSymbols.append(QPointF(x,y));
                if (JKQTPIsOKFloat(xv) && JKQTPIsOKFloat(yv)) {
                    JKQTPPlotSymbol(painter, x, y, symbol, symSize, parent->pt2px(painter, symbolWidth*parent->getLineWidthMultiplier()), color, fillColor);
                }
            }
        } else {
            intSortData();
            for (int iii=imin; iii<imax; iii++) {
                int i=qBound<int>(imin, getDataIndex(static_cast<int>(iii)), imax);
                double xv=position;
                if (positionScatterStyle==RandomScatter) {
                    xv=dRandomScatter(gen);
                }
                const double yv=datastore->get(dataColumn,i);
                double x=transformX(xv);
                const double y=transformY(yv);
                if (positionScatterStyle==BeeSwarmScatter) {
                    while (doesCollide(x,y)) {
                        if (i%2==0) {
                            x=x-symSize;
                        } else {
                            x=x+symSize;
                        }
                    }
                }
                plotSymbols.append(QPointF(x,y));
                if (JKQTPIsOKFloat(xv) && JKQTPIsOKFloat(yv)) {
                    plotSymbols.append(QPointF(x,y));
                    JKQTPPlotSymbol(painter, x, y, symbol, symSize, parent->pt2px(painter, symbolWidth*parent->getLineWidthMultiplier()), color, fillColor);
                }
            }
        }



    }

    drawErrorsAfter(painter);
}

void JKQTPSingleColumnSymbolsGraph::drawKeyMarker(JKQTPEnhancedPainter &painter, QRectF &rect)
{
    const double minSize=qMin(rect.width(), rect.height());
    const double maxSize=qMax(rect.width(), rect.height());
    double symbolSize=parent->pt2px(painter, this->symbolSize);
    if (symbolSize>minSize*0.9) symbolSize=minSize*0.9;
    double symbolWidth=parent->pt2px(painter, this->symbolWidth*parent->getLineWidthMultiplier());
    if (symbolWidth>0.3*symbolSize) symbolWidth=0.3*symbolSize;
    double lineWidth=parent->pt2px(painter, this->lineWidth*parent->getLineWidthMultiplier());
    if (lineWidth>0.5*maxSize) lineWidth=0.5*maxSize;

    painter.save(); auto __finalpaint=JKQTPFinally([&painter]() {painter.restore();});
    QPen p=painter.pen();
    p.setColor(getKeyLabelColor());
    p.setStyle(style);
    p.setWidthF(lineWidth);
    painter.setPen(p);
    JKQTPPlotSymbol(painter, rect.left()+rect.width()/2.0, rect.top()+rect.height()/2.0, symbol, symbolSize, symbolWidth, getKeyLabelColor(), fillColor);

}



QPen JKQTPSingleColumnSymbolsGraph::getSymbolPen(JKQTPEnhancedPainter& painter) const {
    QPen p;
    p.setColor(color);
    p.setWidthF(qMax(JKQTPlotterDrawinTools::ABS_MIN_LINEWIDTH,parent->pt2px(painter, parent->getLineWidthMultiplier()*symbolWidth)));
    p.setStyle(style);
    p.setJoinStyle(Qt::RoundJoin);
    p.setCapStyle(Qt::RoundCap);
    return p;
}

QBrush JKQTPSingleColumnSymbolsGraph::getBrush(JKQTPEnhancedPainter& /*painter*/) const {
    QBrush b;
    b.setColor(fillColor);
    return b;
}



