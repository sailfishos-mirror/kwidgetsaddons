/*
    This file is part of the KDE libraries
    SPDX-FileCopyrightText: 1998 Kurt Granroth <granroth@kde.org>
    SPDX-FileCopyrightText: 2000 Peter Putzer <putzer@kde.org>
    SPDX-FileCopyrightText: 2005 Jarosław Staniek <staniek@kde.org>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#ifndef KURLLABEL_H
#define KURLLABEL_H

#include <kwidgetsaddons_export.h>

#include <QColor>
#include <QLabel>
#include <QPixmap>
#include <memory>

class QCursor;

/*!
 * \class KUrlLabel
 *
 * \brief A drop-in replacement for QLabel that displays hyperlinks.
 *
 * KUrlLabel is a drop-in replacement for QLabel that handles text
 * in a fashion similar to how an HTML widget handles hyperlinks.  The
 * text can be underlined (or not) and set to different colors.  It
 * can also "glow" (cycle colors) when the mouse passes over it.
 *
 * KUrlLabel also provides signals for several events, including
 * the mouse leaving and entering the text area and all forms of
 * mouse clicking.
 *
 * By default KUrlLabel accepts focus. When focused, standard
 * focus rectangle is displayed as in HTML widget.
 * Pressing Enter key accepts the focused label.
 *
 * A typical usage would be something like so:
 *
 * \code
 * KUrlLabel *address = new KUrlLabel(this);
 * address->setText("My homepage");
 * address->setUrl("http://www.home.com/~me");
 * connect(address, &KUrlLabel::leftClickedUrl, this, [this](cont QString &url) { processMyUrl(url); };
 * \endcode
 *
 * In this example, the text "My homepage" would be displayed
 * as blue, underlined text.  When the mouse passed over it,
 * it would "glow" red.  When the user clicks on the text, the
 * signal leftClickedUrl() would be emitted with "http://www.home.com/~me"
 * as its argument.
 *
 * \image kurllabel.png "KUrlLabel Widget"
 */
class KWIDGETSADDONS_EXPORT KUrlLabel : public QLabel
{
    Q_OBJECT

    /*!
     * \property KUrlLabel::url
     */
    Q_PROPERTY(QString url READ url WRITE setUrl)

    /*!
     * \property KUrlLabel::tipText
     */
    Q_PROPERTY(QString tipText READ tipText WRITE setTipText)

    /*!
     * \property KUrlLabel::alternatePixmap
     */
    Q_PROPERTY(QPixmap alternatePixmap READ alternatePixmap WRITE setAlternatePixmap)

    /*!
     * \property KUrlLabel::glowEnabled
     */
    Q_PROPERTY(bool glowEnabled READ isGlowEnabled WRITE setGlowEnabled)

    /*!
     * \property KUrlLabel::floatEnabled
     */
    Q_PROPERTY(bool floatEnabled READ isFloatEnabled WRITE setFloatEnabled)

    /*!
     * \property KUrlLabel::useTips
     */
    Q_PROPERTY(bool useTips READ useTips WRITE setUseTips)

    /*!
     * \property KUrlLabel::useCursor
     */
    Q_PROPERTY(bool useCursor READ useCursor WRITE setUseCursor)

public:
    /*!
     * Default constructor.
     *
     * Use setUrl() and setText() or QListView::setPixmap()
     * to set the resp. properties.
     */
    explicit KUrlLabel(QWidget *parent = nullptr);

    /*!
     * Convenience constructor.
     *
     * \a url is the URL emitted when the label is clicked.
     *
     * \a text is the displayed string. If it's equal to QString()
     * the \a url will be used instead.
     *
     * \a parent Passed to lower level constructor
     *
     * @p parent and @p name are passed to QLabel, which in turn passes
     * them further down
     */
    explicit KUrlLabel(const QString &url, const QString &text = QString(), QWidget *parent = nullptr);

    ~KUrlLabel() override;

    /*!
     * Returns the URL.
     */
    QString url() const;

    /*!
     * Returns the current tooltip text.
     */
    QString tipText() const;

    /*!
     * Returns \c true if a tooltip will be displayed.
     *
     * \sa setTipText()
     */
    bool useTips() const;

    /*!
     * Returns \c true if the cursor will change while over the URL.
     *
     * \sa setUseCursor()
     */
    bool useCursor() const;

    /*!
     * When this is on, the text will switch to the selected
     * color whenever the mouse passes over it.
     */
    bool isGlowEnabled() const;

    /*!
     * This feature is very similar to the "glow" feature in that the color of the
     * label switches to the selected color when the cursor passes
     * over it. In addition, underlining is turned on for as
     * long as the mouse is overhead. Note that if "glow" and
     * underlining are both already turned on, this feature
     * will have no visible effect.
     */
    bool isFloatEnabled() const;

    /*!
     * Returns the alternate pixmap (may be a null pointer if none was set)
     */
    const QPixmap *alternatePixmap() const;

public Q_SLOTS:
    /*!
     * Turns on or off the underlining.
     *
     *  When this is on, the
     * text will be underlined.  By default, it is \a true.
     */
    void setUnderline(bool on = true);

    /*!
     * Sets the URL for this label to \a url.
     *
     * \sa url
     */
    void setUrl(const QString &url);

    virtual void setFont(const QFont &font);

    /*!
     * Turns on or off the tool tip feature.
     *
     * When this is on, the URL will be displayed as a
     * tooltip whenever the mouse passes passes over it.
     * By default, it is \a false.
     */
    void setUseTips(bool on = true);

    /*!
     * Specifies what text to display when tooltips are turned on.
     *
     * If this is not used, the tip will default to the URL.
     *
     * \sa setUseTips()
     */
    void setTipText(const QString &tip);

    /*!
     * Sets the highlight color.
     *
     * This is the default foreground
     * color (non-selected).  By default, it is \a blue.
     */
    void setHighlightedColor(const QColor &highcolor);

    /*!
     * This is an overloaded version for convenience.
     *
     * \sa setHighlightedColor()
     */
    void setHighlightedColor(const QString &highcolor);

    /*!
     * Sets the selected color.
     *
     * This is the color the text will change
     * to when either a mouse passes over it and "glow" mode is on or
     * when it is selected (clicked).  By default, it is \a red.
     */
    void setSelectedColor(const QColor &color);

    /*!
     * This is an overloaded version for convenience.
     *
     * \sa setSelectedColor()
     */
    void setSelectedColor(const QString &color);

    /*!
     * Turns the custom cursor feature on or off.
     *
     * When this is on, the cursor will change to a custom cursor
     * (default is a "pointing hand") whenever the cursor passes
     * over the label. By default, it is on.
     *
     * \a on whether a custom cursor should be displayed.
     *
     * \a cursor the custom cursor. A null pointer indicates the default "hand cursor".
     */
    void setUseCursor(bool on, QCursor *cursor = nullptr);

    /*!
     * Turns on or off the "glow" feature.
     *
     * When this is on, the text will switch to the
     * selected color whenever the mouse
     * passes over it. By default, it is \a true.
     */
    void setGlowEnabled(bool glow = true);

    /*!
     * Turns on or off the "float" feature.
     *
     * This feature is very similar to the "glow" feature in
     * that the color of the label switches to the selected
     * color when the cursor passes over it. In addition,
     * underlining is turned on for as long as the mouse is overhead.
     * Note that if "glow" and underlining are both already turned
     * on, this feature will have no visible effect.
     * By default, it is \a false.
     */
    void setFloatEnabled(bool do_float = true);

    /*!
     * Sets the "alt" pixmap.
     *
     * This pixmap will be displayed when the
     * cursor passes over the label.  The effect is similar to the
     * trick done with 'onMouseOver' in javascript.
     *
     * \sa alternatePixmap()
     */
    void setAlternatePixmap(const QPixmap &pixmap);

Q_SIGNALS:

    /*!
     * Emitted when the mouse has passed over the label.
     */
    void enteredUrl();

    /*!
     * Emitted when the mouse is no longer over the label.
     */
    void leftUrl();

    /*!
     * Emitted when the user clicked the left mouse button on this label.
     */
    void leftClickedUrl();

    /*!
     * Emitted when the user clicked the right mouse button on this label.
     */
    void rightClickedUrl();

    /*!
     * Emitted when the user clicked the left mouse button on this label.
     */
    void middleClickedUrl();

protected:
    void mouseReleaseEvent(QMouseEvent *) override;

    void enterEvent(QEnterEvent *event) override;

    void leaveEvent(QEvent *) override;

    bool event(QEvent *) override;

private:
    std::unique_ptr<class KUrlLabelPrivate> const d;
};

#endif
