#include "id3v2parser.h"

ID3v2Frame* CreateObjectByKey(const std::string& key) {
    if (key == "UFID") return new UniqueFileIDFrame();
    if (key[0] == 'T') return new TextFrame();
    if (key == "COMM") return new CommentsFrame();
    if (key[0] == 'W') return new URLFrame();
    if (key == "POPM") return new PopularimeterFrame();
    if (key == "USLT") return new UnsyncLyricsFrame();
    if (key == "SEEK") return new SeekFrame();
    if (key == "PCNT") return new PlayCounterFrame();
    if (key == "USER") return new TermsOfUseFrame();
    if (key == "OWNE") return new OwnershipFrame();
    if (key == "ENCR") return new EncryptionMethodFrame();
    if (key == "PRIV") return new PrivateFrame();
    if (key == "GRID") return new GroupIDFrame();
    if (key == "LINK") return new LinkedInfoFrame();
    if (key == "ETCO") return new EventTimingFrame();
    if (key == "RBUF") return new BufSizeFrame();
    if (key == "POSS") return new PosSynchroFrame();
    if (key == "COMR") return new CommercialFrame();
    if (key == "SYLT") return new SyncLyricsFrame();
    if (key == "EQU2") return new EqualisationFrame();
    if (key == "RVA2") return new RelativeVolumeFrame();
    return new ID3v2Frame();
}

std::vector<ID3v2Frame*> ParseMP3File(const std::string& filename) {
    std::vector<ID3v2Frame*> frames;

    FILE* file = fopen(filename.c_str(), "rb");
    if (file == nullptr) {
        std::cerr << "No such file found" << std::endl;
        return frames;
    }
    ID3v2Header header;
    header.ReadID3v2Header(file);
    int frames_size = header.GetSize();
    while (frames_size > 0) {
        char buffer[kCountSizeBytes];
        fread(buffer, kSizeofChar, kCountSizeBytes, file);
        std::string frame_name = std::string(buffer, kCountSizeBytes);
        auto* frame = CreateObjectByKey(frame_name);
        frame->SetName(frame_name);
        frame->ParseFrameData(file);
        frames.emplace_back(frame);
        frames_size -= kSizeofFrameHeader + frame->GetSize();
    }
    fclose(file);
    return frames;
}

size_t ID3v2Header::GetSize() const {
    return tag_size;
}

ID3v2Frame::ID3v2Frame(const ID3v2Frame& other) : name(other.name), size(other.size) {
    std::memcpy(flags, other.flags, kSizeofFrameFlags);
    if (other.data != nullptr) {
        data = new char[size];
        std::memcpy(data, other.data, size - kSizeofFrameFlags);
    }
}

ID3v2Frame::~ID3v2Frame() {
    delete[] data;
}

size_t ID3v2Frame::GetSize() const {
    return size;
}

void ID3v2Frame::SetName(const std::string& n) {
    name = n;
}

UniqueFileIDFrame::UniqueFileIDFrame(const UniqueFileIDFrame& other) : ID3v2Frame(other),
                                                                       owner_identifier(other.owner_identifier),
                                                                       size_of_identifier(other.size_of_identifier) {
    identifier = new char[size_of_identifier];
    memcpy(identifier, other.identifier, size_of_identifier);
}

UniqueFileIDFrame::~UniqueFileIDFrame() {
    delete[] identifier;
}

TextFrame::TextFrame(const TextFrame& other) : ID3v2Frame(other), encoding(other.encoding), text_size(other.text_size) {
    text = new char[text_size];
    std::memcpy(text, other.text, text_size);
}

TextFrame::~TextFrame() {
    delete[] text;
}

URLFrame::URLFrame(const URLFrame& other) : ID3v2Frame(other), url(other.url) {}

UnsyncLyricsFrame::UnsyncLyricsFrame(const UnsyncLyricsFrame& other)
    : ID3v2Frame(other),
      text_encoding(other.text_encoding),
      kLanguageSize(other.kLanguageSize),
      language(other.language),
      content_descriptor(other.content_descriptor),
      lyrics_size(other.lyrics_size) {
    lyrics = new char[lyrics_size];
    std::memcpy(lyrics, other.lyrics, lyrics_size);
}

UnsyncLyricsFrame::~UnsyncLyricsFrame() {
    delete[] lyrics;
}

CommentsFrame::CommentsFrame(const CommentsFrame& other)
    : ID3v2Frame(other), text_encoding(other.text_encoding),
      language(other.language), short_descrip(other.short_descrip),
      text_size(other.text_size), text(new char[other.text_size]) {
    std::memcpy(text, other.text, text_size);
}

CommentsFrame::~CommentsFrame() {
    delete[] text;
}

PopularimeterFrame::PopularimeterFrame(const PopularimeterFrame& other)
    : email_to_user(other.email_to_user),
      rating(other.rating),
      size_counter(other.size_counter),
      counter(other.counter) {}

SeekFrame::SeekFrame(const SeekFrame& other) : ID3v2Frame(other), offset(other.offset) {}

PlayCounterFrame::PlayCounterFrame(const PlayCounterFrame& other)
    : ID3v2Frame(other),
      counter(other.counter) {}

TermsOfUseFrame::TermsOfUseFrame(const TermsOfUseFrame& other)
    : ID3v2Frame(other), text_encoding(other.text_encoding),
      language(other.language), text_size(other.text_size),
      text(new char[text_size]) {
    std::memcpy(text, other.text, text_size);
}

TermsOfUseFrame::~TermsOfUseFrame() {
    delete[] text;
}

OwnershipFrame::OwnershipFrame(const OwnershipFrame& other)
    : ID3v2Frame(other), text_encoding(other.text_encoding), price_paid(other.price_paid),
      date_of_purch(other.date_of_purch), seller(other.seller) {
}

EncryptionMethodFrame::EncryptionMethodFrame(const EncryptionMethodFrame& other)
    : ID3v2Frame(other),
      owner_identifier(other.owner_identifier),
      method_symbol(other.method_symbol),
      encryption_data_size(other.encryption_data_size),
      encryption_data(new char[encryption_data_size]) {
    std::memcpy(encryption_data, other.encryption_data, encryption_data_size);
}

EncryptionMethodFrame::~EncryptionMethodFrame() {
    delete[] encryption_data;
}

PrivateFrame::PrivateFrame(const PrivateFrame& other)
    : ID3v2Frame(other), owner_identifier(other.owner_identifier),
      private_data_size(other.private_data_size),
      private_data(new char[private_data_size]) {
    std::memcpy(private_data, other.private_data, private_data_size);
}

PrivateFrame::~PrivateFrame() {
    delete[] private_data;
}

GroupIDFrame::GroupIDFrame(const GroupIDFrame& other) :
    ID3v2Frame(other),
    owner_identifier(other.owner_identifier),
    group_symbol(other.group_symbol),
    group_data_size(other.group_data_size),
    group_data(new char[group_data_size]) {
    std::memcpy(group_data, other.group_data, group_data_size);
}

GroupIDFrame::~GroupIDFrame() {
    delete[] group_data;
}

LinkedInfoFrame::LinkedInfoFrame(const LinkedInfoFrame& other) :
    ID3v2Frame(other),
    frame_identifier(other.frame_identifier),
    url(other.url),
    add_data_size(other.add_data_size),
    add_data(new char[other.add_data_size]) {
    std::memcpy(add_data, other.add_data, add_data_size);
}

LinkedInfoFrame::~LinkedInfoFrame() {
    delete[] add_data;
}

EventTimingFrame::EventTimingFrame(const EventTimingFrame& other)
    : ID3v2Frame(other),
      time_stamp_format(other.time_stamp_format),
      events_size(other.events_size),
      kTimeSize(other.kTimeSize) {
    events = new char[events_size];
    std::memcpy(events, other.events, events_size);
}

EventTimingFrame::~EventTimingFrame() {
    delete[] events;
}

BufSizeFrame::BufSizeFrame(const BufSizeFrame& other) :
    ID3v2Frame(other),
    buffer_size(other.buffer_size),
    info_flag(other.info_flag),
    offset(other.offset) {}

PosSynchroFrame::PosSynchroFrame(const PosSynchroFrame& other)
    : ID3v2Frame(other), time_stamp_format(other.time_stamp_format),
      position_size(other.position_size), position(other.position) {
}

CommercialFrame::CommercialFrame(const CommercialFrame& other)
    : ID3v2Frame(other), text_encoding(other.text_encoding), price_string(other.price_string),
      valid_until(other.valid_until), contact_url(other.contact_url),
      received_as(other.received_as), name_of_seller(other.name_of_seller),
      description(other.description), picture_type(other.picture_type),
      size_of_logo(other.size_of_logo), picture_logo(new char[size_of_logo]) {
    std::memcpy(picture_logo, other.picture_logo, size_of_logo);
}

CommercialFrame::~CommercialFrame() {
    delete[] picture_logo;
}

SyncLyricsFrame::SyncLyricsFrame(const SyncLyricsFrame& other)
    : ID3v2Frame(other),
      text_encoding(other.text_encoding),
      language(other.language),
      time_stamp_format(other.time_stamp_format),
      content_type(other.content_type),
      content_descriptor(other.content_descriptor),
      sync_identifier(other.sync_identifier),
      lyrics_size(other.lyrics_size),
      kTimeSize(other.kTimeSize) {
    if (lyrics_size > 0) {
        lyrics = new char[lyrics_size];
        std::memcpy(lyrics, other.lyrics, lyrics_size);
    } else {
        lyrics = nullptr;
    }
}
SyncLyricsFrame::~SyncLyricsFrame() {
    delete[] lyrics;
}

EqualisationFrame::EqualisationFrame(const EqualisationFrame& other)
    : interpol_method(other.interpol_method),
      identification(other.identification),
      eq_data_size(other.eq_data_size),
      eq_data(new char[other.eq_data_size]) {
    std::memcpy(eq_data, other.eq_data, other.eq_data_size);
}

EqualisationFrame::~EqualisationFrame() {
    delete[] eq_data;
}

RelativeVolumeFrame::RelativeVolumeFrame(const RelativeVolumeFrame& other)
    : ID3v2Frame(other),
      identification(other.identification),
      volume_data_size(other.volume_data_size) {
    volume_data = new char[volume_data_size];
    std::memcpy(volume_data, other.volume_data, volume_data_size);
}

RelativeVolumeFrame::~RelativeVolumeFrame() {
    delete[] volume_data;
}
