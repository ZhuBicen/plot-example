/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011-2022 Emanuel Eichhammer                            **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: https://www.qcustomplot.com/                         **
**             Date: 06.11.22                                             **
**          Version: 2.1.1                                                **
****************************************************************************/

#ifndef QCUSTOMPLOT_H
#define QCUSTOMPLOT_H

#include <QtCore/qglobal.h>

// some Qt version/configuration dependent macros to include or exclude certain code paths:
#ifdef QCUSTOMPLOT_USE_OPENGL
#  if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#    define QCP_OPENGL_PBUFFER
#  else
#    define QCP_OPENGL_FBO
#  endif
#  if QT_VERSION >= QT_VERSION_CHECK(5, 3, 0)
#    define QCP_OPENGL_OFFSCREENSURFACE
#  endif
#endif

#if QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)
#  define QCP_DEVICEPIXELRATIO_SUPPORTED
#  if QT_VERSION >= QT_VERSION_CHECK(5, 6, 0)
#    define QCP_DEVICEPIXELRATIO_FLOAT
#  endif
#endif

#include <QtCore/QObject>
#include <QtCore/QPointer>
#include <QtCore/QSharedPointer>
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtGui/QPaintEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QWheelEvent>
#include <QtGui/QPixmap>
#include <QtCore/QVector>
#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtCore/QMultiMap>
#include <QtCore/QFlags>
#include <QtCore/QDebug>
#include <QtCore/QStack>
#include <QtCore/QCache>
#include <QtCore/QMargins>
#include <qmath.h>
#include <limits>
#include <algorithm>
#ifdef QCP_OPENGL_FBO
#  include <QtGui/QOpenGLContext>
#  if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
#    include <QtGui/QOpenGLFramebufferObject>
#  else
#    include <QOpenGLFramebufferObject>
#    include <QOpenGLPaintDevice>
#  endif
#  ifdef QCP_OPENGL_OFFSCREENSURFACE
#    include <QtGui/QOffscreenSurface>
#  else
#    include <QtGui/QWindow>
#  endif
#endif
#ifdef QCP_OPENGL_PBUFFER
#  include <QtOpenGL/QGLPixelBuffer>
#endif
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
#  include <qnumeric.h>
#  include <QtGui/QWidget>
#  include <QtGui/QPrinter>
#  include <QtGui/QPrintEngine>
#else
#  include <QtNumeric>
#  include <QtWidgets/QWidget>
#  include <QtPrintSupport/QtPrintSupport>
#endif
#if QT_VERSION >= QT_VERSION_CHECK(4, 8, 0)
#  include <QtCore/QElapsedTimer>
#endif
# if QT_VERSION >= QT_VERSION_CHECK(5, 2, 0)
#  include <QtCore/QTimeZone>
#endif

class QCPPainter;
class QCustomPlot;
class QCPLayerable;
class QCPLayoutElement;
class QCPLayout;
class QCPAxis;
class QCPAxisRect;
class QCPAxisPainterPrivate;
class QCPAbstractPlottable;
class QCPGraph;
class QCPAbstractItem;
class QCPPlottableInterface1D;
class QCPLegend;
class QCPItemPosition;
class QCPLayer;
class QCPAbstractLegendItem;
class QCPSelectionRect;
class QCPColorMap;
class QCPColorScale;
class QCPBars;
class QCPPolarAxisRadial;
class QCPPolarAxisAngular;
class QCPPolarGrid;
class QCPPolarGraph;

#include <src/global.h>
#include <src/vector2d.h>
#include <src/painter.h>
#include <src/paintbuffer.h>
#include <src/layer.h>
#include <src/axis/range.h>
#include <src/selection.h>
#include <src/selectionrect.h>
#include <src/layout.h>
#include <src/lineending.h>
#include <src/axis/labelpainter.h>
#include <src/axis/axisticker.h>
#include <src/axis/axistickerdatetime.h>
#include <src/axis/axistickertime.h>
#include <src/axis/axistickerfixed.h>
#include <src/axis/axistickertext.h>
#include <src/axis/axistickerpi.h>
#include <src/axis/axistickerlog.h>
#include <src/axis/axis.h>
#include <src/scatterstyle.h>
#include <src/datacontainer.h>
#include <src/plottable.h>
#include <src/item.h>
#include <src/core.h>
#include <src/plottable1d.h>
#include <src/colorgradient.h>
#include <src/selectiondecorator-bracket.h>
#include <src/layoutelements/layoutelement-axisrect.h>
#include <src/layoutelements/layoutelement-legend.h>
#include <src/layoutelements/layoutelement-textelement.h>
#include <src/layoutelements/layoutelement-colorscale.h>
#include <src/plottables/plottable-graph.h>
#include <src/plottables/plottable-curve.h>
#include <src/plottables/plottable-bars.h>
#include <src/plottables/plottable-statisticalbox.h>
#include <src/plottables/plottable-colormap.h>
#include <src/plottables/plottable-financial.h>
#include <src/plottables/plottable-errorbar.h>
#include <src/items/item-straightline.h>
#include <src/items/item-line.h>
#include <src/items/item-curve.h>
#include <src/items/item-rect.h>
#include <src/items/item-text.h>
#include <src/items/item-ellipse.h>
#include <src/items/item-pixmap.h>
#include <src/items/item-tracer.h>
#include <src/items/item-bracket.h>
#include <src/polar/radialaxis.h>
#include <src/polar/layoutelement-angularaxis.h>
#include <src/polar/polargrid.h>
#include <src/polar/polargraph.h>


#endif // QCUSTOMPLOT_H

