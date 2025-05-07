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

#include "qcustomplot.h"

#include <src/vector2d.cpp>
#include <src/painter.cpp>
#include <src/paintbuffer.cpp>
#include <src/layer.cpp>
#include <src/axis/range.cpp>
#include <src/selection.cpp>
#include <src/selectionrect.cpp>
#include <src/layout.cpp>
#include <src/lineending.cpp>
#include <src/axis/labelpainter.cpp>
#include <src/axis/axisticker.cpp>
#include <src/axis/axistickerdatetime.cpp>
#include <src/axis/axistickertime.cpp>
#include <src/axis/axistickerfixed.cpp>
#include <src/axis/axistickertext.cpp>
#include <src/axis/axistickerpi.cpp>
#include <src/axis/axistickerlog.cpp>
#include <src/axis/axis.cpp>
#include <src/scatterstyle.cpp>
#include <src/plottable.cpp>
#include <src/item.cpp>
#include <src/core.cpp>
#include <src/colorgradient.cpp>
#include <src/selectiondecorator-bracket.cpp>
#include <src/layoutelements/layoutelement-axisrect.cpp>
#include <src/layoutelements/layoutelement-legend.cpp>
#include <src/layoutelements/layoutelement-textelement.cpp>
#include <src/layoutelements/layoutelement-colorscale.cpp>
#include <src/plottables/plottable-graph.cpp>
#include <src/plottables/plottable-curve.cpp>
#include <src/plottables/plottable-bars.cpp>
#include <src/plottables/plottable-statisticalbox.cpp>
#include <src/plottables/plottable-colormap.cpp>
#include <src/plottables/plottable-financial.cpp>
#include <src/plottables/plottable-errorbar.cpp>
#include <src/items/item-straightline.cpp>
#include <src/items/item-line.cpp>
#include <src/items/item-curve.cpp>
#include <src/items/item-rect.cpp>
#include <src/items/item-text.cpp>
#include <src/items/item-ellipse.cpp>
#include <src/items/item-pixmap.cpp>
#include <src/items/item-tracer.cpp>
#include <src/items/item-bracket.cpp>
#include <src/polar/radialaxis.cpp>
#include <src/polar/layoutelement-angularaxis.cpp>
#include <src/polar/polargrid.cpp>
#include <src/polar/polargraph.cpp>