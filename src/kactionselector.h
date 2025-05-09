/*
    This file is part of the KDE project
    SPDX-FileCopyrightText: 2002 Anders Lund <anders.lund@lund.tdcadsl.dk>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#ifndef _KACTION_SELECTOR_H_
#define _KACTION_SELECTOR_H_

#include <QWidget>
#include <kwidgetsaddons_export.h>
#include <memory>

class QListWidget;
class QListWidgetItem;
class QKeyEvent;
class QEvent;
class QIcon;

/*!
    \class KActionSelector
    \inmodule KWidgetsAddons

    \brief A widget for selecting and arranging actions/objects.

    This widget allows the user to select from a set of objects and arrange
    the order of the selected ones using two list boxes labeled "Available"
    and "Used" with horizontal arrows in between to move selected objects between
    the two, and vertical arrows on the right to arrange the order of the selected
    objects.

    The widget moves objects to the other listbox when doubleclicked if
    the property moveOnDoubleClick is set to true (default). See moveOnDoubleClick()
    and setMoveOnDoubleClick().

    The user control the widget using the keyboard if enabled (default),
    see keyboardEnabled.

    Note that this may conflict with keyboard selection in the selected list box,
    if you set that to anything else than QListWidget::Single (which is the default).

    To use it, simply construct an instance and then add items to the two listboxes,
    available through lbAvailable() and lbSelected(). Whenever you want, you can retrieve
    the selected options using QListWidget methods on lbSelected().

    This way, you can use your own QListWidgetItem class, allowing you to easily
    store object data in those.

    When an item is moved to a listbox, it is placed below the current item
    of that listbox.

    Standard arrow icons are used, but you can use icons of your own choice if desired,
    see setButtonIcon(). It is also possible to set tooltips and whatsthis help
    for the buttons. See setButtonTooltip() and setButtonWhatsThis().

    To set whatsthis or tooltips for the listboxes, access them through
    availableListWidget() and selectedListWidget().

    All the moving buttons are automatically set enabled as expected.

    Signals are sent each time an item is moved, allowing you to follow the
    users actions if you need to. See addedToSelection(), removedFromSelection(),
    movedUp() and movedDown()

    \image kactionselector.png "KActionSelector Widget"
*/
class KWIDGETSADDONS_EXPORT KActionSelector : public QWidget
{
    Q_OBJECT

    /*!
     * \property KActionSelector::moveOnDoubleClick
     */
    Q_PROPERTY(bool moveOnDoubleClick READ moveOnDoubleClick WRITE setMoveOnDoubleClick)

    /*!
     * \property KActionSelector::keyboardEnabled
     */
    Q_PROPERTY(bool keyboardEnabled READ keyboardEnabled WRITE setKeyboardEnabled)

    /*!
     * \property KActionSelector::availableLabel
     */
    Q_PROPERTY(QString availableLabel READ availableLabel WRITE setAvailableLabel)

    /*!
     * \property KActionSelector::selectedLabel
     */
    Q_PROPERTY(QString selectedLabel READ selectedLabel WRITE setSelectedLabel)

    /*!
     * \property KActionSelector::availableInsertionPolicy
     */
    Q_PROPERTY(InsertionPolicy availableInsertionPolicy READ availableInsertionPolicy WRITE setAvailableInsertionPolicy)

    /*!
     * \property KActionSelector::selectedInsertionPolicy
     */
    Q_PROPERTY(InsertionPolicy selectedInsertionPolicy READ selectedInsertionPolicy WRITE setSelectedInsertionPolicy)

    /*!
     * \property KActionSelector::showUpDownButtons
     */
    Q_PROPERTY(bool showUpDownButtons READ showUpDownButtons WRITE setShowUpDownButtons)

public:
    /*!
     *
     */
    explicit KActionSelector(QWidget *parent = nullptr);
    ~KActionSelector() override;

    /*!
     * Returns The QListWidget holding the available actions
     */
    QListWidget *availableListWidget() const;

    /*!
     * Returns The QListWidget holding the selected actions
     */
    QListWidget *selectedListWidget() const;

    /*!
     * This enum identifies the moving buttons
     *
     * \value ButtonAdd
     * \value ButtonRemove
     * \value ButtonUp
     * \value ButtonDown
     */
    enum MoveButton {
        ButtonAdd,
        ButtonRemove,
        ButtonUp,
        ButtonDown,
    };
    Q_ENUM(MoveButton)

    /*!
     * This enum defines policies for where to insert moved items in a listbox.
     *
     * \sa availableInsertionPolicy(), setAvailableInsertionPolicy(),
     * selectedInsertionPolicy(), setSelectedInsertionPolicy()
     *
     * \value BelowCurrent The item is inserted below the listbox' currentItem() or at the end if there is no current item.
     * \value Sorted The listbox is sort()ed after one or more items are inserted.
     * \value AtTop The item is inserted at index 0 in the listbox.
     * \value AtBottom The item is inserted at the end of the listbox.
     */
    enum InsertionPolicy {
        BelowCurrent,
        Sorted,
        AtTop,
        AtBottom,
    };
    Q_ENUM(InsertionPolicy)

    /*!
     * Returns Whether moveOnDoubleClick is enabled.
     *
     * If enabled, an item in any listbox will be moved to the other one whenever
     * double-clicked.
     *
     * This feature is enabled by default.
     * \sa setMoveOnDoubleClick()
     */
    bool moveOnDoubleClick() const;

    /*!
     * Sets moveOnDoubleClick to \a enable
     * \sa moveOnDoubleClick()
     */
    void setMoveOnDoubleClick(bool enable);

    /*!
     * Returns Whether keyboard control is enabled.
     *
     * When Keyboard control is enabled, the widget will react to
     * the following keyboard actions:
     * \list
     * \li CTRL + Right - simulate clicking the add button
     * \li CTRL + Left - simulate clicking the remove button
     * \li CTRL + Up - simulate clicking the up button
     * \li CTRL + Down - simulate clicking the down button
     * \endlist
     *
     * Additionally, pressing RETURN or ENTER on one of the list boxes
     * will cause the current item of that listbox to be moved to the other
     * listbox.
     *
     * The keyboard actions are enabled by default.
     *
     * \sa setKeyboardEnabled()
     */
    bool keyboardEnabled() const;

    /*!
     * Sets the keyboard enabled depending on \a enable.
     * \sa keyboardEnabled()
     */
    void setKeyboardEnabled(bool enable);

    /*!
     * Returns The text of the label for the available items listbox.
     */
    QString availableLabel() const;

    /*!
     * Sets the label for the available items listbox to \a text.
     * Note that this label has the listbox as its buddy, so that
     * if you have a single ampersand in the text, the following character
     * will become the accelerator to focus the listbox.
     */
    void setAvailableLabel(const QString &text);

    /*!
     * Returns the label of the selected items listbox.
     */
    QString selectedLabel() const;

    /*!
     * Sets the label for the selected items listbox to \a text.
     * Note that this label has the listbox as its buddy, so that
     * if you have a single ampersand in the text, the following character
     * will become the accelerator to focus the listbox.
     */
    void setSelectedLabel(const QString &text);

    /*!
     * Returns The current insertion policy for the available listbox.
     *
     * The default policy for the available listbox is Sorted.
     *
     * \sa InsertionPolicy, setAvailableInsertionPolicy()
     */
    InsertionPolicy availableInsertionPolicy() const;

    /*!
     * Sets the insertion policy for the available listbox.
     *
     * \sa InsertionPolicy, availableInsertionPolicy()
     */
    void setAvailableInsertionPolicy(InsertionPolicy policy);

    /*!
     * Returns The current insertion policy for the selected listbox.
     *
     * The default policy for the selected listbox is BelowCurrent.
     *
     * \sa InsertionPolicy, setSelectedInsertionPolicy()
     */
    InsertionPolicy selectedInsertionPolicy() const;

    /*!
     * Sets the insertion policy for the selected listbox.
     *
     * \sa InsertionPolicy, selectedInsertionPolicy()
     */
    void setSelectedInsertionPolicy(InsertionPolicy policy);

    /*!
     * Returns whether the Up and Down buttons should be displayed.
     */
    bool showUpDownButtons() const;

    /*!
     * Sets whether the Up and Down buttons should be displayed
     * according to \a show
     */
    void setShowUpDownButtons(bool show);

    /*!
     * Sets the pixmap of the button \a button to \a icon.
     * It calls SmallIconSet(pm) to generate the icon set.
     */
    void setButtonIcon(const QString &icon, MoveButton button);

    /*!
     * Sets the iconset for button \a button to \a iconset.
     * You can use this method to set a custom icon set. Either
     * created by QIconSet, or use the application instance of
     * KIconLoader (recommended).
     */
    void setButtonIconSet(const QIcon &iconset, MoveButton button);

    /*!
     * Sets the tooltip for the button \a button to \a tip.
     */
    void setButtonTooltip(const QString &tip, MoveButton button);

    /*!
     * Sets the whatsthis help for button \a button to \a text.
     */
    void setButtonWhatsThis(const QString &text, MoveButton button);

Q_SIGNALS:
    /*!
     * Emitted when an item is moved to the "selected" listbox.
     */
    void added(QListWidgetItem *item);

    /*!
     * Emitted when an item is moved out of the "selected" listbox.
     */
    void removed(QListWidgetItem *item);

    /*!
     * Emitted when an item is moved upwards in the "selected" listbox.
     */
    void movedUp(QListWidgetItem *item);

    /*!
     * Emitted when an item is moved downwards in the "selected" listbox.
     */
    void movedDown(QListWidgetItem *item);

    /*
     * Emitted when an item is moved to the "selected" listbox.
     */
    //  void addedToSelection( QListWidgetItem *item );

public Q_SLOTS:
    /*!
     * Sets the enabled state of all moving buttons to reflect the current
     * options.
     *
     * Be sure to call this if you add or removes items to either listbox after the
     * widget is shown
     */
    void setButtonsEnabled();

protected:
    void keyPressEvent(QKeyEvent *) override;

    bool eventFilter(QObject *, QEvent *) override;

private:
    friend class KActionSelectorPrivate;
    std::unique_ptr<class KActionSelectorPrivate> const d;

    Q_DISABLE_COPY(KActionSelector)
};

#endif // _KACTION_SELECTOR_H_
