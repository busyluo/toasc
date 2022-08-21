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

#include <cstdint>
#include <ctime>
#include <fstream>

// #undef yyFlexLexer
// #define yyFlexLexer ascFlexLexer
// #if ! defined(yyFlexLexerOnce)
// #include <FlexLexer.h>
// #endif

#include <Vector/ASC/Event.h>

#include <Vector/ASC/vector_asc_export.h>

namespace Vector {
namespace ASC {

/* forward declaration */
class Event;

/**
 * File
 *
 * This is similar to std::fstream for ASCs
 */
class VECTOR_ASC_EXPORT File final {
public:
    virtual ~File();

    /** enumeration for openMode */
    enum class OpenMode {
        /** Read */
        Read,

        /** Write */
        Write
    };

    /** open mode */
    OpenMode openMode {OpenMode::Read};

    /** Date */
    struct tm date {};

    /** Language */
    enum Language : uint8_t {
        /** English */
        En = 0,

        /** German */
        De = 1
    };

    /** Language */
    Language language {Language::En};

    /** Number base */
    enum Base : uint8_t {
        /** decimal mode */
        Dec = 10,

        /** hexadecimal mode */
        Hex = 16,
    };

    /** Number base */
    Base base {Base::Dec};

    /** Timestamps are written absolute or relative to the preceding event. */
    enum class Timestamps : uint8_t {
        /** absolute */
        Absolute = 0,

        /** relative to preceding event */
        Relative = 1
    };

    /** Timestamps are written absolute or relative to the preceding event. */
    Timestamps timestamps {Timestamps::Absolute};

    /** internal events logged */
    bool internalEventsLogged {true};

    /** Version */
    enum Version : uint32_t {
        Ver_5_2     = (5 << 24) | (2 << 16) | ( 0),
        Ver_6_0     = (6 << 24) | (0 << 16) | ( 0),
        Ver_6_1     = (6 << 24) | (1 << 16) | ( 0),
        Ver_7_0     = (7 << 24) | (0 << 16) | ( 0),
        Ver_7_1_SP3 = (7 << 24) | (1 << 16) | (65),
        Ver_7_2     = (7 << 24) | (2 << 16) | ( 0),
        Ver_7_2_SP2 = (7 << 24) | (2 << 16) | (59), // don't know, but 42<x<60
        Ver_7_2_SP3 = (7 << 24) | (2 << 16) | (60),
        Ver_7_5     = (7 << 24) | (5 << 16) | ( 0),
        Ver_8_0     = (8 << 24) | (0 << 16) | ( 0),
        Ver_8_1     = (8 << 24) | (1 << 16) | ( 0)
    };

    /** Version */
    uint32_t version {Version::Ver_8_1};

    /**
     * time stamp precision
     *
     * Old versions used to have precision 4 and newer versions use to have 6.
     * If left at default 0, the precision is automatically set dependent on file version.
     */
    uint8_t timestampPrecision {6};

    /**
     * open file
     *
     * @param filename file name
     */
    void open(const char * filename, OpenMode openMode = OpenMode::Read);

    /**
     * open file
     *
     * @param filename file name
     */
    void open(const std::string & filename, OpenMode openMode = OpenMode::Read);

    /**
     * is file open?
     *
     * @return true if file is open
     */
    bool is_open() const;

    /** close file */
    void close();

    /**
     * check for end-of-file
     *
     * @return true if end-of-file reached
     */
    bool eof();

    /**
     * read object from file
     *
     * @return read object or nullptr
     */
    Event * read();

    /**
     * write object to file
     *
     * @param event object
     */
    void write(Event * event);

private:
    /** file */
    std::fstream file {};

    /** scanner */
    // ascFlexLexer * scanner {nullptr};

    /** end of file */
    bool endOfFile {false};
};

}
}
