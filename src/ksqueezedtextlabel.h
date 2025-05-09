/*
    This file is part of the KDE libraries
    SPDX-FileCopyrightText: 2000 Ronny Standtke <Ronny.Standtke@gmx.de>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#ifndef KSQUEEZEDTEXTLABEL_H
#define KSQUEEZEDTEXTLABEL_H

#include <QLabel>
#include <kwidgetsaddons_export.h>
#include <memory>

// TODO KF6:
//   - make more functions virtual (to benefit subclasses of KSqueezedTextLabel)
//   - try to eliminate need for non-virtual-warning (to benefit use as QLabel),
//     see https://phabricator.kde.org/D7164 for some ideas/considerations
/*!
 * \class KSqueezedTextLabel
 * \inmodule KWidgetsAddons
 *
 * \brief A replacement for QLabel that squeezes its text into the label.
 *
 * If the text is too long to fit into the label it is divided into
 * remaining left and right parts which are separated by three dots.
 * Hovering the mouse over the label shows the full text in a tooltip.
 *
 * Example:
 * http://www.kde.org/documentation/index.html could be squeezed to
 * http://www.kde...ion/index.html
 *
 * \image ksqueezedtextlabel.png "KSqueezedTextLabel Widget"
 *
 * To change the position of the elision mark to the left or right end
 * of the text, use setTextElideMode().
 *
 * \note Several functions of KSqueezedTextLabel (indicated by a warning
 * in their description) reimplement non-virtual functions of QLabel.
 * Therefore, you may need to cast the object to KSqueezedTextLabel in
 * some situations:
 * \code
 * KSqueezedTextLabel* squeezed = new KSqueezedTextLabel("text", parent);
 * QLabel* label = squeezed;
 * label->setText("new text");    // this will not work
 * squeezed->setText("new text"); // works as expected
 * static_cast<KSqueezedTextLabel*>(label)->setText("new text");  // works as expected
 * \endcode
 */
class KWIDGETSADDONS_EXPORT KSqueezedTextLabel : public QLabel
{
    Q_OBJECT

    /*!
     * \property KSqueezedTextLabel::textElideMode
     */
    Q_PROPERTY(Qt::TextElideMode textElideMode READ textElideMode WRITE setTextElideMode)

    /*!
     * \property KSqueezedTextLabel::indent
     */
    Q_PROPERTY(int indent READ indent WRITE setIndent)

    /*!
     * \property KSqueezedTextLabel::margin
     */
    Q_PROPERTY(int margin READ margin WRITE setMargin)

public:
    /*!
     * Default constructor.
     *
     * \a parent the label's parent object
     */
    explicit KSqueezedTextLabel(QWidget *parent = nullptr);

    /*!
     * \a text the text that will be displayed
     *
     * \a parent the label's parent object
     */
    explicit KSqueezedTextLabel(const QString &text, QWidget *parent = nullptr);

    ~KSqueezedTextLabel() override;

    /*!
     * Returnss the label's minimum size, where the horizontal component
     * will be -1 to indicate the label's ability to shrink its width
     * by squeezing the text
     */
    QSize minimumSizeHint() const override;

    /*!
     * Returns the label's preferred size, which is wide enough
     * to display the text without squeezing it
     */
    QSize sizeHint() const override;

    /*!
     * Sets the indentation of the label.
     *
     * \a indent the amount of indentation in pixels
     *
     * Reimplementation of QLabel::setIndent().
     *
     * \warning The corresponding function in the base class is not virtual.
     * Therefore make sure to call this function on objects of type KSqueezedTextLabel,
     * as shown in the example in the class description.
     *
     * \since 5.39
     */
    void setIndent(int indent);

    /*!
     * Sets the margin of the label.
     *
     * \a margin the margin size in pixels
     *
     * Reimplementation of QLabel::setMargin().
     *
     * \warning The corresponding function in the base class is not virtual.
     * Therefore make sure to call this function on objects of type KSqueezedTextLabel,
     * as shown in the example in the class description.
     *
     * \since 5.39
     */
    void setMargin(int margin);

    virtual void setAlignment(Qt::Alignment);

    /*!
     * Returns the text elide mode
     */
    Qt::TextElideMode textElideMode() const;

    /*!
     * Sets the text elide mode.
     *
     * \a mode The text elide mode.
     */
    void setTextElideMode(Qt::TextElideMode mode);

    /*!
     * Returns the full text set via setText()
     *
     * \since 4.4
     */
    QString fullText() const;

    /*!
     * Returns \c true if the text displayed is currently squeezed,
     * i.e. the original text does not fit inside the space available
     * and elide mode is set to a value other than Qt::ElideNone.
     *
     * \since 5.38
     */
    bool isSqueezed() const;

    /*!
     * Returns the rectangle to squeeze the text into
     *
     * Reimplementation of QLabel::contentsRect().
     *
     * \warning The corresponding function in the base class is not virtual.
     * Therefore make sure to call this function on objects of type KSqueezedTextLabel,
     * as shown in the example in the class description.
     *
     * \since 5.39
     */
    QRect contentsRect() const;

public Q_SLOTS:
    /*!
     * Sets the text.
     *
     * \a text The new text.
     *
     * Reimplementation of QLabel::setText().
     *
     * \warning The corresponding function in the base class is not virtual.
     * Therefore make sure to call this function on objects of type KSqueezedTextLabel,
     * as shown in the example in the class description.
     */
    void setText(const QString &text);

    /*!
     * Clears the text.
     *
     * Reimplementation of QLabel::clear().
     *
     * \warning The corresponding function in the base class is not virtual.
     * Therefore make sure to call this function on objects of type KSqueezedTextLabel,
     * as shown in the example in the class description.
     */
    void clear();

protected:
    void mouseReleaseEvent(QMouseEvent *) override;

    void resizeEvent(QResizeEvent *) override;

    void contextMenuEvent(QContextMenuEvent *) override;

    void squeezeTextToLabel();

private:
    std::unique_ptr<class KSqueezedTextLabelPrivate> const d;
};

#endif // KSQUEEZEDTEXTLABEL_H
