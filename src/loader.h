#ifndef __LOADER_H__
#define __LOADER_H__

#include <stdint.h>
#include <unistd.h>
#include "propconnection.h"
#include "loadelf.h"

#define DEFAULT_BAUDRATE    115200

class Loader {
public:
    Loader() : m_connection(0), m_baudrate(DEFAULT_BAUDRATE) {}
    Loader(PropConnection *connection) : m_connection(connection), m_baudrate(DEFAULT_BAUDRATE) {}
    ~Loader() {}
    void setConnection(PropConnection *connection) { m_connection = connection; }
    void setBaudrate(int baudrate);
    int identify(int *pVersion);
    int loadFile(const char *file, LoadType loadType = ltDownloadAndRun);
    int fastLoadFile(const char *file, LoadType loadType = ltDownloadAndRun);
    int loadImage(const uint8_t *image, int imageSize, LoadType loadType = ltDownloadAndRun);
    int fastLoadImage(const uint8_t *image, int imageSize, LoadType loadType = ltDownloadAndRun);
private:
    uint8_t *generateInitialLoaderImage(int packetID, int *pLength);
    int loadSecondStageLoader(uint8_t *packet, int packetSize);
    int transmitPacket(int id, const uint8_t *payload, int payloadSize, int *pResult, int timeout = 2000);
    static uint8_t *readFile(const char *file, int *pImageSize);
    static uint8_t *readSpinBinaryFile(FILE *fp, int *pLength);
    static uint8_t *readElfFile(FILE *fp, ElfHdr *hdr, int *pImageSize);
    PropConnection *m_connection;
    int m_baudrate;
};

inline void msleep(int ms)
{
    usleep(ms * 1000);
}

#endif
