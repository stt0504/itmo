#include "id3v2parser.h"

FILE* operator>>(FILE* in, ID3v2Frame& frame) {
    frame.ReadFrame(in);
    return in;
}

void ID3v2Header::ReadID3v2Header(FILE* file) {
    fread(id, kSizeofChar, kSizeofFileID, file);
    fread(version, kSizeofChar, kSizeofFileVersion, file);
    fread(flags, kSizeofChar, kSizeofFileFlags, file);

    char size_bytes[kCountSizeBytes];
    fread(size_bytes, kSizeofChar, kCountSizeBytes, file);
    tag_size = 0;
    for (int i = 0; i < kCountSizeBytes; i++) {
        tag_size += size_bytes[i];
        if (i < kCountSizeBytes - 1) {
            tag_size <<= kSignBits;
        }
    }
}

void ID3v2Frame::ReadFrame(FILE* file) {
    char size_bytes[kCountSizeBytes];
    fread(size_bytes, kSizeofChar, kCountSizeBytes, file);
    size = 0;
    for (char size_byte : size_bytes) {
        size = (size << kSignBits) | size_byte;
    }
    fread(flags, kSizeofChar, kSizeofFrameFlags, file);
    data = new char[size];
    fread(data, kSizeofChar, size, file);
}

void ID3v2Frame::ParseFrameData(FILE* file) {
    file >> *this;
}

void UniqueFileIDFrame::ParseFrameData(FILE* file) {
    file >> *this;
    size_t i = 0;
    while (data[i] != '\0') {
        owner_identifier += data[i];
        i++;
    }
    size_of_identifier = size - i - 1;
    identifier = new char[size_of_identifier];
    size_t count = 0;
    i++;
    while (i != size) {
        identifier[count] = data[i];
        i++;
        count++;
    }
}

void TextFrame::ParseFrameData(FILE* file) {
    file >> *this;
    size_t i = 0;
    encoding = data[i];

    text_size = size - i - 1;
    i++;

    text = new char[text_size];
    size_t k = 0;

    while (i != size) {
        text[k] = data[i];
        i++;
        k++;
    }
}

void URLFrame::ParseFrameData(FILE* file) {
    file >> *this;;
    size_t i = 0;
    while (i != size) {
        url += data[i];
        i++;
    }
}

void UnsyncLyricsFrame::ParseFrameData(FILE* file) {
    file >> *this;;
    size_t i = 0;

    text_encoding = data[i];
    i++;

    size_t count = 0;
    while (count != kLanguageSize) {
        language += data[i];
        i++;
        count++;
    }

    while (data[i] != '\0') {
        content_descriptor += data[i];
        i++;
    }

    lyrics_size = size - i - 1;
    lyrics = new char[lyrics_size];
    i++;

    count = 0;
    while (i != size) {
        lyrics[count] = data[i];
        count++;
        i++;
    }
}

void CommentsFrame::ParseFrameData(FILE* file) {
    file >> *this;;

    size_t i = 0;
    text_encoding = data[i];
    i++;

    size_t count = 0;
    while (count != kLanguageSize) {
        language += data[i];
        i++;
        count++;
    }

    while (data[i] != '\0') {
        short_descrip += data[i];
        i++;
    }

    text_size = size - i - 1;
    text = new char[text_size];
    i++;
    count = 0;
    while (i != size) {
        text[count] = data[i];
        i++;
        count++;
    }
}

void PopularimeterFrame::ParseFrameData(FILE* file) {
    file >> *this;;

    size_t i = 0;
    while (data[i] != '\0') {
        email_to_user += data[i];
        i++;
    }

    i++;
    rating = data[i];

    size_counter = size - i - 1;
    auto* counter_buf = new char[size_counter];

    i++;

    size_t count = 0;
    while (i < size) {
        counter_buf[count] = data[i];
        i++;
        count++;
    }
    counter = BytesToUint(counter_buf, size_counter);
}

void SeekFrame::ParseFrameData(FILE* file) {
    file >> *this;;
    offset = BytesToUint(data, size);
}

void PlayCounterFrame::ParseFrameData(FILE* file) {
    file >> *this;;
    counter = BytesToUint(data, size);
}

void TermsOfUseFrame::ParseFrameData(FILE* file) {
    file >> *this;;

    size_t i = 0;
    text_encoding = data[i];
    i++;

    size_t count = 0;
    while (count != kLanguageSize) {
        language += data[i];
        i++;
        count++;
    }

    text_size = size - i;
    text = new char[text_size];
    count = 0;
    while (i != size) {
        text[count] = data[i];
        i++;
        count++;
    }
}

void OwnershipFrame::ParseFrameData(FILE* file) {
    file >> *this;;

    size_t i = 0;
    text_encoding = data[i];
    i++;

    while (data[i] != '\0') {
        price_paid += data[i];
        i++;
    }
    i++;

    size_t count = 0;
    while (count != kSizeDate) {
        date_of_purch += data[i];
        i++;
        count++;
    }

    while (i != size) {
        seller += data[i];
        i++;
    }
}

void EncryptionMethodFrame::ParseFrameData(FILE* file) {
    file >> *this;;

    size_t i = 0;

    while (data[i] != '\0') {
        owner_identifier += data[i];
        i++;
    }
    i++;

    method_symbol = data[i];

    encryption_data_size = size - i - 1;
    encryption_data = new char[encryption_data_size];
    i++;

    size_t count = 0;
    while (i != size) {
        encryption_data[count] = data[i];
        count++;
        i++;
    }
}

void PrivateFrame::ParseFrameData(FILE* file) {
    file >> *this;;

    size_t i = 0;

    while (data[i] != '\0') {
        owner_identifier += data[i];
        i++;
    }

    private_data_size = size - i - 1;
    private_data = new char[private_data_size];

    size_t count = 0;

    while (i != size) {
        private_data[count] = data[i];
        count++;
        i++;
    }
}

void GroupIDFrame::ParseFrameData(FILE* file) {
    file >> *this;;

    size_t i = 0;

    while (data[i] != '\0') {
        owner_identifier += data[i];
        i++;
    }
    i++;

    group_symbol = data[i];

    group_data = new char[size - i - 1];
    i++;

    size_t count = 0;

    while (i != size) {
        group_data[count] = data[i];
        count++;
        i++;
    }
}

void LinkedInfoFrame::ParseFrameData(FILE* file) {
    file >> *this;;

    size_t i = 0;
    size_t count = 0;

    while (count != kSizeofFrameID) {
        frame_identifier += data[i];
        i++;
        count++;
    }

    while (data[i] != '\0') {
        url += data[i];
        i++;
    }

    add_data_size = size - i - 1;
    add_data = new char[add_data_size];
    i++;
    count = 0;

    while (i != size) {
        add_data[count] = data[i];
        count++;
        i++;
    }
}

void EventTimingFrame::ParseFrameData(FILE* file) {
    file >> *this;;

    size_t i = 0;
    time_stamp_format = data[i];

    events_size = size - i - 1;
    i++;

    events = new char[events_size];
    size_t count = 0;
    while (i != size) {
        events[count] = data[i];
        count++;
        i++;
    }
}

void BufSizeFrame::ParseFrameData(FILE* file) {
    file >> *this;;

    size_t i = 0;
    size_t count = 0;
    char size_buf[kBufSizeByte];
    while (count != kBufSizeByte) {
        size_buf[count] = data[i];
        i++;
        count++;
    }
    buffer_size = BytesToUint(size_buf, kBufSizeByte);

    info_flag = data[i];
    i++;

    count = 0;
    char offset_buf[kOffsetSize];
    while (count != kOffsetSize) {
        offset_buf[count] = data[i];
        i++;
        count++;
    }

    offset = BytesToUint(offset_buf, kOffsetSize);
}

void PosSynchroFrame::ParseFrameData(FILE* file) {
    file >> *this;;
    size_t i = 0;
    time_stamp_format = data[i];

    position_size = size - i - 1;
    i++;

    char position_buf[position_size];
    size_t count = 0;
    while (data[i] != '\0') {
        position_buf[count] = data[i];
        i++;
        count++;
    }
    position = BytesToUint(position_buf, position_size);
}

void CommercialFrame::ParseFrameData(FILE* file) {
    file >> *this;;
    size_t i = 0;
    text_encoding = data[i];
    i++;
    while (data[i] != '\0') {
        price_string += data[i];
        i++;
    }
    i++;

    size_t count = 0;
    while (count != kSizeDate) {
        valid_until += data[i];
        i++;
        count++;
    }
    while (data[i] != '\0') {
        contact_url += data[i];
        i++;
    }
    i++;
    received_as = data[i];
    i++;
    while (data[i] != '\0') {
        name_of_seller += data[i];
        i++;
    }
    i++;
    while (data[i] != '\0') {
        description += data[i];
        i++;
    }
    if (i < size - 1) i++;
    while (i < size && data[i] != '\0') {
        picture_type += data[i];
        i++;
    }
    size_of_logo = size - i - 1;
    picture_logo = new char[size_of_logo];
    i++;
    count = 0;
    while (i < size) {
        picture_logo[count] = data[i];
        i++;
        count++;
    }
}

void SyncLyricsFrame::ParseFrameData(FILE* file) {
    file >> *this;;
    size_t i = 0;
    text_encoding = data[i];
    i++;

    size_t count = 0;
    while (count < kLanguageSize) {
        language += data[i];
        i++;
        count++;
    }

    time_stamp_format = data[i];
    i++;

    content_type = data[i];
    i++;

    while (data[i] != '\0') {
        content_descriptor += data[i];
        i++;
    }

    i++;
    sync_identifier = data[i];

    lyrics_size = size - i - 1;
    i++;
    lyrics = new char[lyrics_size];

    count = 0;
    while (i < size) {
        lyrics[count] = data[i];
        i++;
        count++;
    }
}

void EqualisationFrame::ParseFrameData(FILE* file) {
    file >> *this;;
    size_t i = 0;
    interpol_method = data[i];
    i++;

    while (data[i] != '\0') {
        identification += data[i];
        i++;
    }

    eq_data_size = size - i - 1;
    eq_data = new char[eq_data_size];
    i++;

    size_t count = 0;
    while (i < size) {
        eq_data[count] = data[i];
        i++;
        count++;
    }
}

void RelativeVolumeFrame::ParseFrameData(FILE* file) {
    file >> *this;;
    size_t i = 0;

    while (data[i] != '\0') {
        identification += data[i];
        i++;
    }

    volume_data_size = size - i - 1;
    volume_data = new char[volume_data_size];
    i++;

    size_t count = 0;
    while (i < size) {
        volume_data[count] = data[i];
        i++;
        count++;
    }
}
