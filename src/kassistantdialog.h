/*
    This file is part of the KDE libraries
    SPDX-FileCopyrightText: 2006 Olivier Goffart <ogoffart at kde.org>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#ifndef KASSISTANTDIALOG_H
#define KASSISTANTDIALOG_H

#include <kpagedialog.h>

#include <kwidgetsaddons_export.h>

class KAssistantDialogPrivate;

/*!
 * \class KAssistantDialog
 * \inmodule KWidgetsAddons
 *
 * \brief This class provides a framework for assistant dialogs.
 *
 * An assistant dialog consists of a sequence of pages.
 * Its purpose is to guide the user (assist) through a process step by step.
 * Assistant dialogs are useful for complex or infrequently occurring tasks
 * that people may find difficult to learn or do.
 * Sometimes a task requires too many input fields to fit them on a single dialog.
 *
 * Create and populate dialog pages that inherit from QWidget and add them
 * to the assistant dialog using addPage().
 *
 * The functions next() and back() are virtual and may be reimplemented to
 * override the default actions of the next and back buttons.
 *
 * \image kassistantdialog.png "KAssistantDialog"
 */
class KWIDGETSADDONS_EXPORT KAssistantDialog : public KPageDialog
{
    Q_OBJECT
public:
    /*!
     * Construct a new assistant dialog with \a parent as parent.
     *
     * \a parent is the parent of the widget.
     *
     * \a flags the window flags to give to the assistant dialog. The
     * default of zero is usually what you want.
     */
    explicit KAssistantDialog(QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    ~KAssistantDialog() override;

    /*!
     * Specify if the content of the page is valid, and if the next button may be enabled on this page.
     * By default all pages are valid.
     *
     * This will disable or enable the next button on the specified page
     *
     * \a page the page on which the next button will be enabled/disable
     *
     * \a enable if true the next button will be enabled, if false it will be disabled
     */
    void setValid(KPageWidgetItem *page, bool enable);

    /*!
     * return if a page is valid
     *
     * \a page the page to check the validity of
     * \sa setValid()
     */
    bool isValid(KPageWidgetItem *page) const;

    /*!
     * Specify whether a page is appropriate.
     *
     * A page is considered inappropriate if it should not be shown due to
     * the contents of other pages making it inappropriate.
     *
     * A page which is inappropriate will not be shown.
     *
     * The last page in an assistant dialog should always be appropriate
     *
     * \a page the page to set as appropriate
     *
     * \a appropriate flag indicating the appropriateness of the page.
     *
     * If \a appropriate is true, then \a page is appropriate and will be
     * shown in the assistant dialog. If false, \a page will not be shown.
     */
    void setAppropriate(KPageWidgetItem *page, bool appropriate);

    /*!
     * Check if a page is appropriate for use in the assistant dialog.
     *
     * \a page is the page to check the appropriateness of.
     *
     * Returns \c true if \a page is appropriate, false if it is not
     */
    bool isAppropriate(KPageWidgetItem *page) const;

    /*!
     * Returns the next button
     */
    QPushButton *nextButton() const;

    /*!
     * Returns the finish button
     */
    QPushButton *backButton() const;

    /*!
     * Returns the finish button
     */
    QPushButton *finishButton() const;

public Q_SLOTS:
    /*!
     * Called when the user clicks the Back button.
     *
     * This function will show the preceding relevant page in the sequence.
     * Do nothing if the current page is the first page in the sequence.
     */
    virtual void back();

    /*!
     * Called when the user clicks the Next/Finish button.
     *
     * This function will show the next relevant page in the sequence.
     * If the current page is the last page, it will call accept()
     */
    virtual void next();

protected:
    /*!
     * Construct an assistant dialog from a single widget.
     *
     * \a widget the widget to construct the dialog with
     *
     * \a parent the parent of the assistant dialog
     *
     * \a flags the window flags to use when creating the widget. The default
     * of zero is usually fine.
     *
     * Calls the KPageDialog(KPageWidget *widget, QWidget *parent, Qt::WindowFlags flags) constructor
     */
    explicit KAssistantDialog(KPageWidget *widget, QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());

    void showEvent(QShowEvent *event) override;

private:
    Q_DECLARE_PRIVATE(KAssistantDialog)

    Q_DISABLE_COPY(KAssistantDialog)
};

#endif
