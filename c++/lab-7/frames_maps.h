#pragma once
#include <map>

std::map<uint8_t, std::string> etco_type_map = {
    {0x00, "padding (has no meaning)"},
    {0x01, "end of initial silence"},
    {0x02, "intro start"},
    {0x03, "main part start"},
    {0x04, "outro start"},
    {0x05, "outro end"},
    {0x06, "verse start"},
    {0x07, "refrain start"},
    {0x08, "interlude start"},
    {0x09, "theme start"},
    {0x0A, "variation start"},
    {0x0B, "key change"},
    {0x0C, "time change"},
    {0x0D, "momentary unwanted noise (Snap, Crackle & Pop)"},
    {0x0E, "sustained noise"},
    {0x0F, "sustained noise end"},
    {0x10, "intro end"},
    {0x11, "main part end"},
    {0x12, "verse end"},
    {0x13, "refrain end"},
    {0x14, "theme end"},
    {0x15, "profanity"},
    {0x16, "profanity end"},
    {0xFD, "audio end (start of silence)"},
    {0xFE, "audio file ends"},
    {0xFF, "one more byte of events follows (all the following bytes with the value $FF have the same function)"}
};

std::map<uint8_t, std::string> time_stamps_format_map = {
    {0x01, "Absolute time, 32 bit sized, using MPEG frames as unit"},
    {0x02, "Absolute time, 32 bit sized, using milliseconds as unit"},
};

std::map<uint8_t, std::string> received_description = {
    {0x00, "Other"},
    {0x01, "Standard CD album with other songs"},
    {0x02, "Compressed audio on CD"},
    {0x03, "File over the Internet"},
    {0x04, "Stream over the Internet"},
    {0x05, "As note sheets"},
    {0x06, "As note sheets in a book with other sheets"},
    {0x07, "Music on other media"},
    {0x08, "Non-musical merchandise"}
};

std::map<uint8_t, std::string> content_type_map = {
    {0x00, "other"},
    {0x01, "lyrics"},
    {0x02, "text transcription"},
    {0x03, "movement/part name"},
    {0x04, "events"},
    {0x05, "chord"},
    {0x06, "trivia/pop up information"},
    {0x07, "URLs to webpages"},
    {0x08, "URLs to images"}
};

std::map<uint8_t, std::string> interpol_method_map = {
    {0x00, "Band\n"
           "     No interpolation is made. A jump from one adjustment level to\n"
           "     another occurs in the middle between two adjustment points."},
    {0x01, "Linear\n"
           "     Interpolation between adjustment points is linear."},
};

std::map<uint8_t, std::string> type_of_channel_map = {
    {0x00, "Other"},
    {0x01, "Master volume"},
    {0x02, "Front right"},
    {0x03, "Front left"},
    {0x04, "Back right"},
    {0x05, "Back left"},
    {0x06, "Front centre"},
    {0x07, "Back centre"},
    {0x08, "Subwoofer"}
};
