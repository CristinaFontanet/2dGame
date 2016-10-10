/***********************************************************************
	created:	21/2/2004
	author:		Paul D Turner
	
	purpose:	Main system include for client code
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2006 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#ifndef _CEGUI_h_
#define _CEGUI_h_

// base stuff
#include "Affector.h"
#include "Animation.h"
#include "AnimationInstance.h"
#include "AnimationManager.h"
#include "BasicImage.h"
#include "BasicRenderedStringParser.h"
#include "BidiVisualMapping.h"
#include "BoundSlot.h"
#include "CentredRenderedString.h"
#include "Clipboard.h"
#include "Colour.h"
#include "ColourRect.h"
#include "CoordConverter.h"
#include "DataContainer.h"
#include "DefaultLogger.h"
#include "DefaultRenderedStringParser.h"
#include "DefaultResourceProvider.h"
#include "DynamicModule.h"
#include "Element.h"
#include "Event.h"
#include "EventArgs.h"
#include "EventSet.h"
#include "Exceptions.h"
#include "FactoryModule.h"
#include "FactoryRegisterer.h"
#include "Font.h"
#include "FontGlyph.h"
#include "FontManager.h"
#include "FormattedRenderedString.h"
#include "GeometryBuffer.h"
#include "GlobalEventSet.h"
#include "GUIContext.h"
#include "Image.h"
#include "ImageCodec.h"
#include "ImageManager.h"
#include "InputEvent.h"
#include "Interpolator.h"
#include "JustifiedRenderedString.h"
#include "KeyFrame.h"
#include "LeftAlignedRenderedString.h"
#include "LinkedEvent.h"
#include "Logger.h"
#include "MouseCursor.h"
#include "NamedElement.h"
#include "Property.h"
#include "PropertyHelper.h"
#include "PropertySet.h"
#include "Quaternion.h"
#include "Rect.h"
#include "RegexMatcher.h"
#include "RenderedString.h"
#include "RenderedStringImageComponent.h"
#include "RenderedStringParser.h"
#include "RenderedStringTextComponent.h"
#include "RenderedStringWidgetComponent.h"
#include "RenderedStringWordWrapper.h"
#include "RenderEffect.h"
#include "RenderEffectManager.h"
#include "Renderer.h"
#include "RenderingContext.h"
#include "RenderingSurface.h"
#include "RenderingWindow.h"
#include "RenderQueue.h"
#include "RenderTarget.h"
#include "RightAlignedRenderedString.h"
#include "Scheme.h"
#include "SchemeManager.h"
#include "ScriptModule.h"
#include "SimpleTimer.h"
#include "Size.h"
#include "String.h"
#include "StringTranscoder.h"
#include "System.h"
#include "SystemKeys.h"
#include "Texture.h"
#include "TextureTarget.h"
#include "TextUtils.h"
#include "TplInterpolators.h"
#include "TplWindowFactory.h"
#include "TplWindowRendererFactory.h"
#include "TplWindowFactoryRegisterer.h"
#include "TplWRFactoryRegisterer.h"
#include "Vector.h"
#include "Version.h"
#include "Vertex.h"
#include "WindowFactory.h"
#include "WindowFactoryManager.h"
#include "Window.h"
#include "WindowManager.h"
#include "WindowRendererManager.h"
#include "XMLAttributes.h"
#include "XMLHandler.h"
#include "XMLParser.h"
#include "XMLSerializer.h"

// Falagard core system include
#include "falagard/WidgetLookManager.h"

// gui elements
#include "widgets/All.h"

#endif	// end of guard _CEGUI_h_
