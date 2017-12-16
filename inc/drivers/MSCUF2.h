/*
The MIT License (MIT)

Copyright (c) 2017 Lancaster University.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef DEVICE_MSCUF2_H
#define DEVICE_MSCUF2_H

#include "USBMSC.h"

#if CONFIG_ENABLED(DEVICE_USB)

namespace codal
{

struct UF2FileEntry
{
    UF2FileEntry *next;
    uint32_t size;
    uint16_t id;
    uint16_t startCluster;
    uint8_t attrs;
    uint8_t flags;
    char filename[0];
};

class MSCUF2 : public USBMSC
{
    void buildBlock(uint32_t block_no, uint8_t *data);
    void readDirData(uint8_t *dest, UF2FileEntry *dirdata, int blkno);

protected:
    UF2FileEntry *files;

    virtual void readFileBlock(uint16_t id, int blockAddr, char *dst);

public:
    MSCUF2();

    virtual void addFiles();
    virtual uint32_t getCapacity();
    virtual void readBlocks(int blockAddr, int numBlocks);
    virtual void writeBlocks(int blockAddr, int numBlocks);

    virtual uint32_t flashSize() { return 256 * 1024; } // for current.uf2
    virtual const char *volumeLabel() { return "UF2BOOT"; }

    void addFile(uint16_t id, const char *filename, uint32_t size);
};
}

#endif

#endif
