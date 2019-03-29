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



#include <QString>
#include <QPainter>
#include <QPair>
#include "jkqtplotter/jkqtpgraphsbase.h"

#ifndef jkqtpgraphspeakstream_H_INCLUDED
#define jkqtpgraphspeakstream_H_INCLUDED

// forward declarations
class JKQTBasePlotter;
class JKQTPlotter;
class JKQTPCoordinateAxis;
class JKQTPDatastore;


/*! \brief interprets data as a stream of x- or y-positions \f$ p_i \f$ (depending in \a yPeaks ) ans plots a line on the height
           \a baseline and upright lines from baseline to baseline+peakHeight at each position \f$ p_i \f$. This can be used to
           display a stream of photons with given arrivaltimes \f$ p_i \f$.
    \ingroup jkqtplotter_diverse

    \image html JKQTPPeakStreamGraphY.png "yPeaks=true"
    \image html JKQTPPeakStreamGraphX.png "yPeaks=false"
 */
class JKQTP_LIB_EXPORT JKQTPPeakStreamGraph: public JKQTPSingleColumnGraph {
        Q_OBJECT
    public:
        /** \brief class constructor */
        JKQTPPeakStreamGraph(JKQTBasePlotter* parent=nullptr);
        JKQTPPeakStreamGraph(int dataColumn, double baseline, double peakHeight, QColor color, JKQTBasePlotter* parent=nullptr);
        JKQTPPeakStreamGraph(int dataColumn, double baseline, double peakHeight, JKQTBasePlotter* parent=nullptr);
        JKQTPPeakStreamGraph(JKQTPlotter* parent);
        JKQTPPeakStreamGraph(int dataColumn, double baseline, double peakHeight, QColor color, JKQTPlotter* parent);
        JKQTPPeakStreamGraph(int dataColumn, double baseline, double peakHeight, JKQTPlotter* parent);

        /** \brief get the maximum and minimum x-value of the graph
         *
         * The result is given in the two parameters which are call-by-reference parameters!
         */
        virtual bool getXMinMax(double& minx, double& maxx, double& smallestGreaterZero) override;
        /** \brief get the maximum and minimum y-value of the graph
         *
         * The result is given in the two parameters which are call-by-reference parameters!
         */
        virtual bool getYMinMax(double& miny, double& maxy, double& smallestGreaterZero) override;


        /** \brief plots the graph to the plotter object specified as parent */
        virtual void draw(JKQTPEnhancedPainter& painter) override;
        /** \brief plots a key marker inside the specified rectangle \a rect */
        virtual void drawKeyMarker(JKQTPEnhancedPainter& painter, QRectF& rect) override;

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
        /*! \copydoc peakHeight
            \see see peakHeight for details */ 
        inline virtual void setPeakHeight(double __value)  
        {
            this->peakHeight = __value;
        } 
        /*! \copydoc peakHeight
            \see see peakHeight for details */ 
        inline virtual double getPeakHeight() const  
        {
            return this->peakHeight; 
        }
        /*! \copydoc yPeaks
            \see see yPeaks for details */ 
        inline virtual void setYPeaks(bool __value)  
        {
            this->yPeaks = __value;
        } 
        /*! \copydoc yPeaks
            \see see yPeaks for details */ 
        inline virtual bool getYPeaks() const  
        {
            return this->yPeaks; 
        }
        /*! \copydoc drawBaseline
            \see see drawBaseline for details */ 
        inline virtual void setDrawBaseline(bool __value)  
        {
            this->drawBaseline = __value;
        } 
        /*! \copydoc drawBaseline
            \see see drawBaseline for details */ 
        inline virtual bool getDrawBaseline() const  
        {
            return this->drawBaseline; 
        }

    protected:

        /** \brief position of the baseline */
        double baseline;
        /** \brief height of each peak */
        double peakHeight;
        /** \brief if set \c true the peaks are in Y direction (default: true)*/
        bool yPeaks;
        /** \brief indicates whether to draw the basleine (default: \c true ) */
        bool drawBaseline;

};




#endif // jkqtpgraphspeakstream_H_INCLUDED
