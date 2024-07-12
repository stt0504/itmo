#include "id3v2parser.h"
#include "frames_maps.h"

std::ostream& operator<<(std::ostream& out, const ID3v2Frame& frame) {
    frame.PrintFrame(out);
    return out;
}

unsigned int BytesToUint(char* bytes, size_t size) {
    unsigned int result = 0;
    for (size_t i = 0; i < size; i++) {
        result = (result << kBitSizeOfByte) | std::bitset<kBitSizeOfByte>(bytes[i]).to_ulong();
    }
    return result;
}

void PrintCharSymbols(const char* data, unsigned int size, std::ostream& out) {
    for (unsigned int i = 0; i < size; i++) {
        out << data[i];
    }
    out << std::endl;
}

void ID3v2Frame::PrintHeaderFrame(std::ostream& out) const {
    out << "Name:    " << name << std::endl;
    out << "Size:    " << size << " bytes" << std::endl;
    out << "Flags:    ";
    for (char flag : flags) {
        for (int j = kBitSizeOfByte - 1; j >= 0; j--) {
            out << ((flag >> j) & 1);
        }
        out << ' ';
    }
    out << std::endl;
}

void ID3v2Frame::PrintFrame(std::ostream& out) const {}

void UniqueFileIDFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Owner identifier:    " << owner_identifier << std::endl;
    out << "Identifier:    ";
    PrintCharSymbols(identifier, size_of_identifier, out);
    out << std::endl << std::endl;
}

void TextFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Text encoding:    " << static_cast<int>(encoding) << std::endl;
    out << "Info:    ";
    PrintCharSymbols(text, text_size, out);
    out << std::endl << std::endl;
}

void URLFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "URL:    " << url << std::endl;
    out << std::endl << std::endl;
}

void UnsyncLyricsFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Language:    " << language << std::endl;
    out << "Text encoding:    " << static_cast<int>(text_encoding) << std::endl;
    out << "Content descriptor:    " << content_descriptor << std::endl;
    out << "Lyrics/text:    ";
    PrintCharSymbols(lyrics, lyrics_size, out);
    out << std::endl << std::endl;
}

void CommentsFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Text encoding:    " << static_cast<int>(text_encoding) << std::endl;
    out << "Language:    " << language << std::endl;
    out << "Short content descriptors:    " << short_descrip << std::endl;
    out << "Text:    ";
    PrintCharSymbols(text, text_size, out);
    out << std::endl << std::endl;
}

void PopularimeterFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Email to user:    " << email_to_user << std::endl;
    out << "Rating:    " << static_cast<int>(rating) << std::endl;
    out << "Counter:    " << counter << std::endl;
    out << std::endl << std::endl;
}

void SeekFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Offset:    " << offset << std::endl;
    out << std::endl << std::endl;
}

void PlayCounterFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Counter:    " << counter << std::endl;
    out << std::endl << std::endl;
}

void TermsOfUseFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Text encoding:    " << static_cast<int>(text_encoding) << std::endl;
    out << "Language:    " << language << std::endl;
    out << "Text:    ";
    PrintCharSymbols(text, text_size, out);
    out << std::endl << std::endl;
}

void OwnershipFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Text encoding:    " << static_cast<int>(text_encoding) << std::endl;
    out << "Price paid:    " << price_paid << std::endl;
    out << "Date of purchase:    " << date_of_purch << std::endl;
    out << "Seller:    " << seller << std::endl;
    out << std::endl << std::endl;
}

void EncryptionMethodFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Owner identifier:    " << owner_identifier << std::endl;
    out << "Method symbol:    " << static_cast<int>(method_symbol) << std::endl;
    out << "Encryption data:    ";
    PrintCharSymbols(encryption_data, encryption_data_size, out);
    out << std::endl << std::endl;
}

void PrivateFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Owner identifier:    " << owner_identifier << std::endl;
    out << "Private data:    ";
    PrintCharSymbols(private_data, private_data_size, out);
    out << std::endl << std::endl;
}

void GroupIDFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Owner identifier:    " << owner_identifier << std::endl;
    out << "Method symbol:    " << static_cast<int>(group_symbol) << std::endl;
    out << "Encryption data:    ";
    PrintCharSymbols(group_data, group_data_size, out);
    out << std::endl << std::endl;
}

void LinkedInfoFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Frame identifier:    " << frame_identifier << std::endl;
    out << "Url:    " << url << std::endl;
    out << "Add data:    ";
    PrintCharSymbols(add_data, add_data_size, out);
    out << std::endl << std::endl;
}

void EventTimingFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Time stamp format:    " << time_stamps_format_map[time_stamp_format] << std::endl;
    out << "Events: " << std::endl;
    printEvents(out);
    out << std::endl << std::endl;
}

void EventTimingFrame::printEvents(std::ostream& out) const {
    size_t i = 0;
    while (i < events_size) {
        out << etco_type_map[events[i]] << ":    ";
        i++;
        char time[kTimeSize];
        for (int k = 0; k < kTimeSize; k++) {
            time[k] = events[i];
            i++;
        }
        out << BytesToUint(time, kTimeSize) << std::endl;
    }
}

void BufSizeFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Buffer size:    " << buffer_size << std::endl;
    out << "Info flag: " << static_cast<int>(info_flag) << std::endl;
    out << "Offset:   " << offset << std::endl;
    out << std::endl << std::endl;
}

void PosSynchroFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Time stamp format:    " << time_stamps_format_map[time_stamp_format] << std::endl;
    out << "Position:   " << position << std::endl;
    out << std::endl << std::endl;
}

void CommercialFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Text encoding:    " << static_cast<int>(text_encoding) << std::endl;
    out << "Price string:   " << price_string << std::endl;
    out << "Valid until:    " << valid_until << std::endl;
    out << "Contact URL:    " << contact_url << std::endl;
    out << "Received as:    " << received_description[received_as] << std::endl;
    out << "Name of seller:    " << name_of_seller << std::endl;
    out << "Description:    " << description << std::endl;
    out << "Picture MIME type:    " << picture_type << std::endl;
    out << "Seller logo:    ";
    PrintCharSymbols(picture_logo, size_of_logo, out);
    out << std::endl << std::endl;
}

void SyncLyricsFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Text encoding:    " << static_cast<int>(text_encoding) << std::endl;
    out << "Language:   " << language << std::endl;
    out << "Time stamp format:    " << time_stamps_format_map[time_stamp_format] << std::endl;
    out << "Content type:    " << content_type_map[content_type] << std::endl;
    out << "Content descriptor:    " << content_descriptor << std::endl;
    PrintSynchroLyrics(out);
    out << std::endl << std::endl;
}

void SyncLyricsFrame::PrintSynchroLyrics(std::ostream& out) const {
    size_t i = 0;
    while (i < lyrics_size) {
        std::string text;
        while (lyrics[i] != '\0') {
            text += lyrics[i];
            i++;
        }
        i++;
        size_t count = 0;
        char time_buf[kTimeSize];
        while (count < kTimeSize) {
            time_buf[count] = lyrics[i];
            i++;
            count++;
        }
        i++;
        out << BytesToUint(time_buf, kTimeSize) << ":   " << text << std::endl;
    }
}

void EqualisationFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Interpolation method:    " << interpol_method_map[interpol_method] << std::endl;
    out << "Identification:   " << identification << std::endl;
    PrintData(out);
    out << std::endl << std::endl;
}

void EqualisationFrame::PrintData(std::ostream& out) const {
    size_t i = 0;
    char freq_buf[kFreqSize];
    char vol_buf[kVolSize];
    while (i < eq_data_size) {
        freq_buf[0] = eq_data[i];
        freq_buf[1] = eq_data[i + 1];
        vol_buf[0] = static_cast<char>(eq_data[i + kFreqSize]);
        vol_buf[1] = static_cast<char>(eq_data[i + 1 + kFreqSize]);
        i += kVolSize + kFreqSize;
        out << BytesToUint(freq_buf, kFreqSize) << "    " << BytesToUint(vol_buf, kVolSize) << std::endl;
    }
}

void RelativeVolumeFrame::PrintFrame(std::ostream& out) const {
    PrintHeaderFrame(out);
    out << "Identification:   " << identification << std::endl;
    PrintData(out);
    out << std::endl << std::endl;
}

void RelativeVolumeFrame::PrintData(std::ostream& out) const {
    char type_channel;
    char volume_adjustment[kSizeOfVolAdj];
    char bits_representing_peak;
    char peak_volume;
    size_t i = 0;
    while (i < volume_data_size) {
        type_channel = volume_data[i];
        i++;
        volume_adjustment[0] = volume_data[i];
        volume_adjustment[1] = volume_data[i + 1];
        i += kSizeOfVolAdj;
        bits_representing_peak = volume_data[i];
        i++;
        peak_volume = volume_data[i];
        i++;
        out << "Type of channel:    " << type_of_channel_map[type_channel] << std::endl;
        out << "Volume adjustment:   " << BytesToUint(volume_adjustment, kSizeOfVolAdj) << std::endl;
        out << "Bits representing peak:    " << static_cast<int>(bits_representing_peak) << std::endl;
        out << "Peak volume:    " << static_cast<int>(peak_volume) << std::endl;
        out << std::endl;
    }
}
