#pragma once

#include <iostream>
#include <bitset>
#include <cstring>
#include <fstream>
#include <memory>
#include <vector>

const int kBitSizeOfByte = 8;
const int kSizeofChar = 1;
const int kSizeofFileID = 3;
const int kSizeofFileVersion = 2;
const int kSizeofFileFlags = 1;
const int kCountSizeBytes = 4;
const int kSignBits = 7;
const int kSizeofFrameID = 4;
const int kSizeofFrameFlags = 2;
const int kSizeofFrameHeader = 10;

class ID3v2Header {
    public:
        void ReadID3v2Header(FILE* file);

        size_t GetSize() const;

    private:
        char id[kSizeofFrameID];
        char version[kSizeofFileVersion];
        size_t tag_size;
        char flags[kSizeofFileFlags];
};

class ID3v2Frame {
    public:
        ID3v2Frame() = default;

        ID3v2Frame(const ID3v2Frame& other);

        void ReadFrame(FILE* file);

        void PrintHeaderFrame(std::ostream& out) const;

        virtual void PrintFrame(std::ostream& out) const;

        virtual void ParseFrameData(FILE* file);

        virtual ~ID3v2Frame();

        size_t GetSize() const;

        void SetName(const std::string& n);

    protected:
        std::string name;
        size_t size;
        char flags[kSizeofFrameFlags];
        char* data;
};

std::ostream& operator<<(std::ostream& out, const ID3v2Frame& frame);

FILE* operator>>(FILE* in, ID3v2Frame& frame);

std::vector<ID3v2Frame*> ParseMP3File(const std::string& filename);

class UniqueFileIDFrame : public ID3v2Frame {
    public:
        UniqueFileIDFrame() = default;

        UniqueFileIDFrame(const UniqueFileIDFrame& other);

        void PrintFrame(std::ostream& out) const override;

        void ParseFrameData(FILE* file) override;

        ~UniqueFileIDFrame() override;

    private:
        std::string owner_identifier;
        size_t size_of_identifier;
        char* identifier;
};

class TextFrame : public ID3v2Frame {
    public:
        TextFrame() = default;

        TextFrame(const TextFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~TextFrame() override;

    private:
        char encoding;
        char* text;
        size_t text_size;

};

class URLFrame : public ID3v2Frame {
    public:
        URLFrame() = default;

        URLFrame(const URLFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~URLFrame() override = default;

    private:
        std::string url;
};

class EventTimingFrame : public ID3v2Frame {
    public:
        EventTimingFrame() = default;

        EventTimingFrame(const EventTimingFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        void printEvents(std::ostream& out) const;

        ~EventTimingFrame() override;

    private:
        char time_stamp_format;

        size_t events_size;
        char* events;

        const int kTimeSize = 4;

};

class UnsyncLyricsFrame : public ID3v2Frame {
    public:
        UnsyncLyricsFrame() = default;

        UnsyncLyricsFrame(const UnsyncLyricsFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        char text_encoding;

        ~UnsyncLyricsFrame() override;

    private:
        const int kLanguageSize = 3;
        std::string language;

        std::string content_descriptor;

        size_t lyrics_size;
        char* lyrics;
};

class SyncLyricsFrame : public ID3v2Frame {
    public:
        SyncLyricsFrame() = default;

        SyncLyricsFrame(const SyncLyricsFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        void PrintSynchroLyrics(std::ostream& out) const;

        ~SyncLyricsFrame() override;

    private:
        char text_encoding;

        const int kLanguageSize = 3;
        std::string language;

        char time_stamp_format;
        char content_type;
        std::string content_descriptor;

        char sync_identifier;
        size_t lyrics_size;
        char* lyrics;

        const int kTimeSize = 4;
};

class CommentsFrame : public ID3v2Frame {
    public:
        CommentsFrame() = default;

        CommentsFrame(const CommentsFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~CommentsFrame() override;

    private:
        char text_encoding;

        const int kLanguageSize = 3;
        std::string language;

        std::string short_descrip;

        size_t text_size;
        char* text;
};

class RelativeVolumeFrame : public ID3v2Frame {
    public:
        RelativeVolumeFrame() = default;

        RelativeVolumeFrame(const RelativeVolumeFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~RelativeVolumeFrame() override;

    private:
        std::string identification;
        const int kSizeOfVolAdj = 2;
        size_t volume_data_size;
        char* volume_data;

        void PrintData(std::ostream& out) const;
};

class EqualisationFrame : public ID3v2Frame {
    public:

        EqualisationFrame() = default;

        EqualisationFrame(const EqualisationFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~EqualisationFrame() override;

    private:
        char interpol_method;
        std::string identification;

        size_t eq_data_size;
        char* eq_data;

        const int kFreqSize = 2;
        const int kVolSize = 2;

        void PrintData(std::ostream& out) const;
};

class PlayCounterFrame : public ID3v2Frame {
    public:
        PlayCounterFrame() = default;

        PlayCounterFrame(const PlayCounterFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~PlayCounterFrame() override = default;

    private:
        unsigned int counter;
};

class PopularimeterFrame : public ID3v2Frame {
    public:
        PopularimeterFrame() = default;

        PopularimeterFrame(const PopularimeterFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~PopularimeterFrame() override = default;

    private:
        std::string email_to_user;
        char rating;

        size_t size_counter;
        unsigned int counter;
};

class BufSizeFrame : public ID3v2Frame {
    public:
        BufSizeFrame() = default;

        BufSizeFrame(const BufSizeFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~BufSizeFrame() override = default;

    private:
        const int kBufSizeByte = 3;
        unsigned int buffer_size;

        char info_flag;

        const int kOffsetSize = 4;
        unsigned int offset;
};

class LinkedInfoFrame : public ID3v2Frame {
    public:
        LinkedInfoFrame() = default;

        LinkedInfoFrame(const LinkedInfoFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~LinkedInfoFrame() override;

    private:
        std::string frame_identifier;
        std::string url;
        size_t add_data_size;
        char* add_data;
};

class PosSynchroFrame : public ID3v2Frame {
    public:
        PosSynchroFrame() = default;

        PosSynchroFrame(const PosSynchroFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~PosSynchroFrame() override = default;

    private:
        char time_stamp_format;
        size_t position_size;
        unsigned int position;
};

class TermsOfUseFrame : public ID3v2Frame {
    public:
        TermsOfUseFrame() = default;

        TermsOfUseFrame(const TermsOfUseFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~TermsOfUseFrame() override;

    private:
        char text_encoding;

        const int kLanguageSize = 3;
        std::string language;

        size_t text_size;
        char* text;
};

class OwnershipFrame : public ID3v2Frame {
    public:
        OwnershipFrame() = default;

        OwnershipFrame(const OwnershipFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~OwnershipFrame() override = default;

    private:
        char text_encoding;
        std::string price_paid;

        const int kSizeDate = 8;
        std::string date_of_purch;
        std::string seller;
};

class CommercialFrame : public ID3v2Frame {
    public:
        CommercialFrame() = default;

        CommercialFrame(const CommercialFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~CommercialFrame() override;

    private:
        char text_encoding;
        std::string price_string;

        const int kSizeDate = 8;
        std::string valid_until;
        std::string contact_url;

        char received_as;

        std::string name_of_seller;
        std::string description;
        std::string picture_type;

        size_t size_of_logo;
        char* picture_logo;
};

class EncryptionMethodFrame : public ID3v2Frame {
    public:
        EncryptionMethodFrame() = default;

        EncryptionMethodFrame(const EncryptionMethodFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~EncryptionMethodFrame() override;

    private:
        std::string owner_identifier;
        char method_symbol;

        size_t encryption_data_size;
        char* encryption_data;
};

class GroupIDFrame : public ID3v2Frame {
    public:
        GroupIDFrame() = default;

        GroupIDFrame(const GroupIDFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~GroupIDFrame() override;

    private:
        std::string owner_identifier;
        char group_symbol;

        size_t group_data_size;
        char* group_data;
};

class PrivateFrame : public ID3v2Frame {
    public:
        PrivateFrame() = default;

        PrivateFrame(const PrivateFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~PrivateFrame() override;

    private:
        std::string owner_identifier;

        size_t private_data_size;
        char* private_data;
};

class SeekFrame : public ID3v2Frame {
    public:
        SeekFrame() = default;

        SeekFrame(const SeekFrame& other);

        void ParseFrameData(FILE* file) override;

        void PrintFrame(std::ostream& out) const override;

        ~SeekFrame() override = default;

    private:
        unsigned int offset;
};

unsigned int BytesToUint(char* bytes, size_t size);

ID3v2Frame* CreateObjectByKey(const std::string& key);
