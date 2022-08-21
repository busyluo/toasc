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
#include <sstream>

#include <Vector/ASC/Most25AllocTable.h>
#include <Vector/ASC/MostCommon.h>
#include <Vector/ASC/MostSymbolsRegEx.h>

namespace Vector {
namespace ASC {

Most25AllocTable * Most25AllocTable::read(File & /*file*/, std::string & line) {
    std::regex regex(REGEX_STOL REGEX_MOST_Time REGEX_WS REGEX_MOST_Channel REGEX_WS "AllocTab:"
                     REGEX_ws REGEX_MOST_AllocTableSize "((" REGEX_WS REGEX_MOST_DxAT ")*)" REGEX_ENDL);
    std::smatch match;
    if (std::regex_match(line, match, regex)) {
        auto * most25AllocTable = new Most25AllocTable;
        most25AllocTable->time = std::stod(match[1]);
        most25AllocTable->channel = std::stoul(match[2]);
        most25AllocTable->allocTableSize = std::stoul(match[3], nullptr, 16);
        std::istringstream iss(match[4]);
        iss >> std::hex;
        while (!iss.eof()) {
            unsigned short s;
            iss >> s;
            most25AllocTable->data.push_back(s);
        }
        return most25AllocTable;
    }

    return nullptr;
}

void Most25AllocTable::write(File & file, std::ostream & stream) {
    writeMostTime(file, stream, time);
    writeMostChannel(file, stream, channel);

    /* format: "AllocTab: %04X  " */
    stream
            << "AllocTab: "
            << std::setfill('0') << std::setw(4) << std::uppercase << std::hex << allocTableSize
            << "  ";

    writeMostData(file, stream, data);

    stream << endl;
}

}
}
