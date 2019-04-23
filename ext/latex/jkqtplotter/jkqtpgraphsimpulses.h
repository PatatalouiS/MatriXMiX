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

#include "jkqtplottertools/jkqtp_imexport.h"
#include "jkqtplotter/jkqtpgraphsbase.h"
#include "jkqtplotter/jkqtpgraphsbaseerrors.h"

#ifndef jkqtpgraphsimpulses_H
#define jkqtpgraphsimpulses_H



/*! \brief This implements an impulse plot with impulses in direction of the X axis (i.e. from y=0 to y=f(x) )
    \ingroup jkqtplotter_barssticks

    \image html plot_impulsesxplots.png
 */
class JKQTP_LIB_EXPORT JKQTPImpulsesHorizontalGraph: public JKQTPXYGraph {
        Q_OBJECT
    public:
        /** \brief class constructor */
        JKQTPImpulsesHorizontalGraph(JKQTBasePlotter* parent=nullptr);
        /** \brief class constructor */
        JKQTPImpulsesHorizontalGraph(JKQTPlotter* parent);

        /** \brief plots the graph to the plotter object specified as parent */
        virtual void draw(JKQTPEnhancedPainter& painter) override;
        /** \brief plots a key marker inside the specified rectangle \a rect */
        virtual void drawKeyMarker(JKQTPEnhancedPainter& painter, QRectF& rect) override;
        /** \brief returns the color to be used for the key label */
        virtual QColor getKeyLabelColor() override;

        /*! \copydoc color
            \see see color for details */ 
        inline virtual void setColor(const QColor & __value)  
        {
            this->color = __value;
        } 
        /*! \copydoc color
            \see see color for details */ 
        inline virtual QColor getColor() const  
        {
            return this->color; 
        }
        /*! \copydoc lineWidth
            \see see lineWidth for details */ 
        inline virtual void setLineWidth(double __value)  
        {
            this->lineWidth = __value;
        } 
        /*! \copydoc lineWidth
            \see see lineWidth for details */ 
        inline virtual double getLineWidth() const  
        {
            return this->lineWidth; 
        }
        /*! \copydoc baseline
            \see see baseline for details */ 
        inline virtual void setBaseline(double __value)  
        {
            this->baseline = __value;
        } 
        /*! \copydoc baseline
            \see see baseline for details */ 
        inline virtual double getBaseline() const  
        {
            return this->baseline; 
        }

        /** \brief color of the graph */
        QColor color;
        /** \brief width (pixels) of the lines */
        double lineWidth;

    protected:
        /** \brief which plot style to use from the parent plotter (via JKQTBasePlotter::getPlotStyle() and JKQTBasePlotter::getNextStyle() ) */
        int parentPlotStyle;

        /** \brief baseline of the plot (NOTE: 0 is interpreted as until plot border in log-mode!!!)
         */
        double baseline;
        QPen getPen(JKQTPEnhancedPainter &painter) const;
};



/*! \brief This implements an impulse plot with impulses in direction of the X axis (i.e. from x=0 to x=f(y) )
    \ingroup jkqtplotter_barssticks

    \image html plot_impulsesxerrorsplots.png
 */
class JKQTP_LIB_EXPORT JKQTPImpulsesHorizontalErrorGraph: public JKQTPImpulsesHorizontalGraph, public JKQTPXGraphErrors {
        Q_OBJECT
    public:
        /** \brief class constructor */
        JKQTPImpulsesHorizontalErrorGraph(JKQTBasePlotter* parent=nullptr);
        JKQTPImpulsesHorizontalErrorGraph(JKQTPlotter* parent);
        /** \copydoc JKQTPGraph::usesColumn() */
        virtual bool usesColumn(int c) const override;

    protected:
        /** \brief this function is used to plot error inidcators before plotting the graphs. */
        virtual void drawErrorsAfter(JKQTPEnhancedPainter& painter) override ;

};




/*! \brief This implements an impulse plot with impulses in direction of the Y axis (i.e. from y=0 to y=f(x) )
    \ingroup jkqtplotter_barssticks

    \image html plot_impulsesyplots.png
 */
class JKQTP_LIB_EXPORT JKQTPImpulsesVerticalGraph: public JKQTPImpulsesHorizontalGraph {
        Q_OBJECT
    public:
        /** \brief class constructor */
        JKQTPImpulsesVerticalGraph(JKQTBasePlotter* parent=nullptr);
        /** \brief class constructor */
        JKQTPImpulsesVerticalGraph(JKQTPlotter* parent);

        /** \brief plots the graph to the plotter object specified as parent */
        virtual void draw(JKQTPEnhancedPainter& painter) override;
};



/*! \brief This implements an impulse plot with impulses in direction of the X axis (i.e. from x=0 to x=f(y) )
    \ingroup jkqtplotter_barssticks

    \image html plot_impulsesyerrorsplots.png
 */
class JKQTP_LIB_EXPORT JKQTPImpulsesVerticalErrorGraph: public JKQTPImpulsesVerticalGraph, public JKQTPYGraphErrors {
        Q_OBJECT
    public:
        /** \brief class constructor */
        JKQTPImpulsesVerticalErrorGraph(JKQTBasePlotter* parent=nullptr);
        /** \brief class constructor */
        JKQTPImpulsesVerticalErrorGraph(JKQTPlotter* parent);
        /** \copydoc JKQTPGraph::usesColumn() */
        virtual bool usesColumn(int c) const override;

    protected:
        /** \brief this function is used to plot error inidcators before plotting the graphs. */
        virtual void drawErrorsAfter(JKQTPEnhancedPainter& painter) override ;

};




#endif // jkqtpgraphsimpulses_H
