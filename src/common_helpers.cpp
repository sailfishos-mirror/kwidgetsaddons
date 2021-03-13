/*
    This file is part of the KDE libraries
    SPDX-FileCopyrightText: 2008 Chusslove Illich <caslav.ilic@gmx.net>

    SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include <common_helpers_p.h>

// If pos points to alphanumeric X in "...(X)...", which is preceded or
// followed only by non-alphanumerics, then "(X)" gets removed.
static QString removeReducedCJKAccMark(const QString &label, int pos)
{
    if (pos > 0 && pos + 1 < label.length() //
        && label[pos - 1] == QLatin1Char('(') //
        && label[pos + 1] == QLatin1Char(')') //
        && label[pos].isLetterOrNumber()) {
        // Check if at start or end, ignoring non-alphanumerics.
        int len = label.length();
        int p1 = pos - 2;
        while (p1 >= 0 && !label[p1].isLetterOrNumber()) {
            --p1;
        }
        ++p1;
        int p2 = pos + 2;
        while (p2 < len && !label[p2].isLetterOrNumber()) {
            ++p2;
        }
        --p2;

        if (p1 == 0) {
            return label.leftRef(pos - 1) + label.midRef(p2 + 1);
        } else if (p2 + 1 == len) {
            return label.leftRef(p1) + label.midRef(pos + 2);
        }
    }
    return label;
}

QString removeAcceleratorMarker(const QString &label_)
{
    QString label = label_;

    int p = 0;
    bool accmarkRemoved = false;
    while (true) {
        p = label.indexOf(QLatin1Char('&'), p);
        if (p < 0 || p + 1 == label.length()) {
            break;
        }

        if (label[p + 1].isLetterOrNumber()) {
            // Valid accelerator.
            label = QString(label.leftRef(p) + label.midRef(p + 1));

            // May have been an accelerator in CJK-style "(&X)"
            // at the start or end of text.
            label = removeReducedCJKAccMark(label, p);

            accmarkRemoved = true;
        } else if (label[p + 1] == QLatin1Char('&')) {
            // Escaped accelerator marker.
            label = QString(label.leftRef(p) + label.midRef(p + 1));
        }

        ++p;
    }

    // If no marker was removed, and there are CJK characters in the label,
    // also try to remove reduced CJK marker -- something may have removed
    // ampersand beforehand.
    if (!accmarkRemoved) {
        bool hasCJK = false;
        for (const QChar c : qAsConst(label)) {
            if (c.unicode() >= 0x2e00) { // rough, but should be sufficient
                hasCJK = true;
                break;
            }
        }
        if (hasCJK) {
            p = 0;
            while (true) {
                p = label.indexOf(QLatin1Char('('), p);
                if (p < 0) {
                    break;
                }
                label = removeReducedCJKAccMark(label, p + 1);
                ++p;
            }
        }
    }

    return label;
}
