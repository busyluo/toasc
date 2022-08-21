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

#pragma once

#include <Vector/ASC/platform.h>

#include <ctime>

#include <Vector/ASC/Event.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/** File Split Information */
struct VECTOR_ASC_EXPORT FileSplitInformation final : Event {
    FileSplitInformation() : Event(EventType::FileSplitInformation) {}

    /** last absolute time stamp of the previous log file */
    double time {0.0};

    /** filename of the previous log file without path information */
    std::string fileName {};

    /** @copydoc Event::read() */
    static FileSplitInformation * read(File & file, std::string & line);

    virtual void write(File & file, std::ostream & stream) override;
};

}
}
