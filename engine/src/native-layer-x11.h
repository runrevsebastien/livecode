/* Copyright (C) 2015 LiveCode Ltd.
 
 This file is part of LiveCode.
 
 LiveCode is free software; you can redistribute it and/or modify it under
 the terms of the GNU General Public License v3 as published by the Free
 Software Foundation.
 
 LiveCode is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or
 FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 for more details.
 
 You should have received a copy of the GNU General Public License
 along with LiveCode.  If not see <http://www.gnu.org/licenses/>.  */

#ifndef __MC_NATIVE_LAYER_X11__
#define __MC_NATIVE_LAYER_X11__

#include "native-layer.h"

#include <gtk/gtk.h>

namespace x11
{
#include <gdk/gdkx.h>
}

class MCNativeLayerX11 : public MCNativeLayer
{
public:
    
    virtual void OnOpen();
    virtual void OnClose();
    virtual void OnAttach();
    virtual void OnDetach();
    virtual void OnPaint(MCGContextRef);
    virtual void OnGeometryChanged(const MCRectangle& p_old_rect);
    virtual void OnVisibilityChanged(bool p_visible);
    virtual void OnToolChanged(Tool p_new_tool);
    virtual void OnLayerChanged();
    
    virtual bool GetNativeView(void *&r_view);
    
    MCNativeLayerX11(MCWidgetRef p_widget, x11::Window p_view);
    ~MCNativeLayerX11();
    
private:
    
    MCWidgetRef m_widget;
    GtkWindow* m_child_window;
    GdkRegion* m_input_shape;
    GtkSocket* m_socket;
    x11::Window m_widget_xid;
    
    // Returns the handle for the stack containing this widget
    x11::Window getStackX11Window();
    GdkWindow* getStackGdkWindow();
    
    // Returns the GtkFixed used for layouts within the stack
    GtkFixed* getStackLayout();
    
    // Performs the attach/detach operations
    void doAttach();
    void doDetach();
    
    // Performs a relayering operation
    void doRelayer();
    
    // Updates the input mask for the widget (used to implement edit mode)
    void updateInputShape();
};

#endif // ifndef __MC_NATIVE_LAYER_X11__
