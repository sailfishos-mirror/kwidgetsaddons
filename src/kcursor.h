/*
    This file is part of the KDE libraries
    SPDX-FileCopyrightText: 1998 Kurt Granroth <granroth@kde.org>
    SPDX-FileCopyrightText: 2000 Carsten Pfeiffer <pfeiffer@kde.org>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#ifndef KCURSOR_H
#define KCURSOR_H

#include <kwidgetsaddons_export.h>

class QEvent;
class QObject;
class QWidget;

/*!
 * \class KCursor
 * \inmodule KWidgetsAddons
 *
 * \brief The KCursor class provides a set of static
 * convenience methods for auto-hiding cursors on widgets.
 */
class KWIDGETSADDONS_EXPORT KCursor
{
public:
    /*!
     * Sets auto-hiding the cursor for widget \a w. Enabling it will result in
     * the cursor being hidden when
     * \list
     * \li a key-event happens
     * \li there are no key-events for a configured time-frame (see
     * setHideCursorDelay())
     * \endlist
     *
     * The cursor will be shown again when the focus is lost or a mouse-event
     * happens.
     *
     * Side effect: when enabling auto-hide, mouseTracking is enabled for the
     * specified widget, because it's needed to get mouse-move-events. So
     * don't disable mouseTracking for a widget while using auto-hide for it.
     *
     * When disabling auto-hide, mouseTracking will be disabled, so if you need
     * mouseTracking after disabling auto-hide, you have to re-enable
     * mouseTracking.
     *
     * If you want to use auto-hiding for widgets that don't take focus, e.g.
     * a QCanvasView, then you have to pass all key-events that should trigger
     * auto-hiding to autoHideEventFilter().
     */
    static void setAutoHideCursor(QWidget *w, bool enable, bool customEventFilter = false);

    /*!
     * Sets the delay time in milliseconds for auto-hiding. When no keyboard
     * events arrive for that time-frame, the cursor will be hidden.
     *
     * Default is 5000, i.e. 5 seconds.
     */
    static void setHideCursorDelay(int ms);

    /*!
     * Returns the current auto-hide delay time.
     *
     * Default is 5000, i.e. 5 seconds.
     */
    static int hideCursorDelay();

    /*!
     * KCursor has to install an eventFilter over the widget you want to
     * auto-hide. If you have an own eventFilter() on that widget and stop
     * some events by returning true, you might break auto-hiding, because
     * KCursor doesn't get those events.
     *
     * In this case, you need to call setAutoHideCursor( widget, true, true );
     * to tell KCursor not to install an eventFilter. Then you call this method
     * from the beginning of your eventFilter, for example:
     * \code
     * edit = new KEdit( this, "some edit widget" );
     * edit->installEventFilter( this );
     * KCursor::setAutoHideCursor( edit, true, true );
     *
     * [...]
     *
     * bool YourClass::eventFilter( QObject *o, QEvent *e )
     * {
     *     if ( o == edit ) // only that widget where you enabled auto-hide!
     *         KCursor::autoHideEventFilter( o, e );
     *
     *     // now you can do your own event-processing
     *     [...]
     * }
     * \endcode
     *
     * Note that you must not call KCursor::autoHideEventFilter() when you
     * didn't enable or after disabling auto-hiding.
     */
    static void autoHideEventFilter(QObject *, QEvent *);

private:
    KCursor() = delete;
};

#endif // _KCURSOR_H
