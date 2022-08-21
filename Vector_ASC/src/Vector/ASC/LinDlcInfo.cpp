/*
 * Copyright (C) 2014-2015 Tobias Lorenz.
 * Contact: tobias.lorenz@gmx.net
 *
 * This file is part of Tobias Lorenz's Toolkit.
 *
 * Commercial License Usage
 * Licensees holding valid commercial licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and Tobias Lorenz.
 *
 * GNU General Public License 3.0 Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 */

#include <iomanip>
#include <regex>

#include <Vector/ASC/LinCommon.h>
#include <Vector/ASC/LinDlcInfo.h>
#include <Vector/ASC/LinSymbolsRegEx.h>

namespace Vector {
namespace ASC {

LinDlcInfo * LinDlcInfo::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_LIN_Time REGEX_WS REGEX_LIN_Channel REGEX_WS REGEX_LIN_ID REGEX_WS "DlcInfo"
                     REGEX_WS REGEX_LIN_DLC REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * linDlcInfo = new LinDlcInfo;
        linDlcInfo->time = std::stod(match[1]);
        linDlcInfo->channel = ((match[2] == 'i') ? 1 : std::stoul(match[2]));
        linDlcInfo->id = match[3];
        linDlcInfo->dlc = std::stoul(match[4]);
        return linDlcInfo;
    }

    return nullptr;
}

void LinDlcInfo::write(File & file, std::ostream & stream) {
    writeLinTime(file, stream, time);
    stream << ' ';

    /* format: "%s %-12.1x DlcInfo   %d" */
    /* format: "%s %-12.1d DlcInfo   %d" */
    /* format: "%s %s DlcInfo   %d" */
    writeLinChannel(file, stream, channel);
    stream
            << ' '
            << std::left << std::setw(12) << id
            << " DlcInfo   "
            << std::right << std::dec << (uint16_t) dlc;

    stream << endl;
}

}
}
