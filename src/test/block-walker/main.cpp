#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <ios>
#include <iostream>
#include <memory>
#include <stdio.h>
#include <unistd.h>

const char* filename = "/home/aksenofo/PROJECT/mnt/LEXA/orp/1_123_1088442028.dbf";

#pragma pack(push, 1)
typedef struct file_header_0 {
    uint32_t unknown0[5];
    uint32_t blocksize;  // Размер блока, 512/1024...
    uint32_t blockcount; // Общее количество блоков текущего файла
    uint32_t unknown1[2];
    uint32_t zero[119];
} Redo_fh0;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct redo_block_header {
    uint32_t signature; // подпись
    uint32_t blocknum;  // Номер блока
    uint32_t filenum;   // Порядковый номер
    uint16_t offset;    // В позиции, с которой начинается первая запись повтора текущего блока, старший бит отбрасывается
    uint16_t checksum;  // Контрольная сумма блока, обновляемая при записи
} Redo_bh;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct RBA { // Информация о местоположении в файле повтора
    uint32_t sequence;
    uint32_t blocknum;
    uint32_t offset;
} Redo_RBA;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct scn {
    uint32_t scnbase;
    uint32_t scnwrapper;
} Redo_scn;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct file_header_1 {
    Redo_bh blockheader;
    uint32_t unknown0;
    uint32_t Compatibility_Vsn;
    uint32_t db_id;
    uint64_t db_name; // Угадайте имя, используемое для представления базы данных
    uint32_t control_seq;
    uint32_t file_size;
    uint32_t blksize;
    uint16_t file_number;
    uint16_t file_type;
    uint32_t activation_id;
    uint8_t zero[36];
    uint8_t unknown1[64];
    uint32_t nab; // Последний блок текущего файла содержит следующий блок реального блока записи
    uint32_t resetlogs_count;
    Redo_scn resetlos_scn;
    uint16_t _0; //?????
    uint32_t hws;
    uint32_t thread;
    Redo_scn low_scn;
    uint16_t __0; //?????
    uint32_t low_scn_time;
    Redo_scn next_scn;
    uint16_t ___0; //?????
    uint32_t nex_cn_time;
    uint32_t unknown2;
    Redo_scn enabled_scn;
    uint16_t ____0; //?????
    uint32_t enabled_scn_time;
    Redo_scn thread_closed_scn;
    uint16_t _____0;
    uint32_t thread_closed_scn_time;
    uint8_t unknown3[52];
    Redo_scn prev_resetlogs_scn;
    uint16_t ______0;
    uint32_t prev_resetlogs_count;
    uint8_t unknown4[216];
} Redo_fh1;
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct block {
    Redo_bh blockheader;
    uint8_t redo_record[496]; // redo record，Регистрация
} Redo_block;
#pragma pack(pop)

#pragma pack(push, 1)
struct file_block_1 {
    Redo_bh blockheader;
    char r[28 - 16];
    char name[16 * 4];
    char desc[64];
    uint8_t rest[512 -
        sizeof(Redo_bh) -
        sizeof(name) -
        sizeof(r) -
        sizeof(desc)];
};
#pragma pack(pop)

uint16_t calcChSum(const uint8_t* buffer, uint64_t size, uint16_t check )
{
    uint64_t sum = 0;

    for (uint64_t i = 0; i < size / 8; ++i, buffer += 8)
        sum ^= *(reinterpret_cast<const uint64_t*>(buffer));
    sum ^= (sum >> 32);
    sum ^= (sum >> 16);
    sum ^= check;

    return static_cast<uint16_t>(sum);
}

int main()
{
    int handler = open(filename, O_RDONLY);
    int current_offset = 0;
    file_header_0 file_hdr_0;
    file_block_1 file_hdr_1;

    char buffer4[4];

    int block_size;
    lseek(handler, current_offset, SEEK_SET);

    current_offset += read(handler, &file_hdr_0, sizeof(file_hdr_0));
    assert(sizeof(file_block_1));
    auto buffer = std::make_unique<uint8_t[]>(file_hdr_0.blocksize);

    for (size_t t = 0; t < file_hdr_0.blockcount; ++t) {
        auto len = read(handler, buffer.get(), file_hdr_0.blocksize);
        assert(len == file_hdr_0.blocksize);
        current_offset += len;
        const Redo_bh& blockheader = *reinterpret_cast<Redo_bh*>(buffer.get());
        
        assert(blockheader.signature == 8705);
        assert(blockheader.blocknum - 1 == t);

        auto cs = calcChSum(buffer.get(), file_hdr_0.blocksize, blockheader.checksum );
        assert(cs == blockheader.checksum);

        std::cout << "sign :" << blockheader.signature << std::endl;
        std::cout << "block:" << blockheader.blocknum << std::endl;
        std::cout << "file :" << blockheader.filenum << std::endl;

        //        std::cout << file_hdr_1.name << std::endl;
        //        std::cout << file_hdr_1.desc << std::endl;
        std::cout << "-----------------------------------" << std::endl;
    }

    close(handler);
}
