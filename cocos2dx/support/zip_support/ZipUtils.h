/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef __SUPPORT_ZIPUTILS_H__
#define __SUPPORT_ZIPUTILS_H__

#include <string>

namespace cocos2d
{
    /* XXX: pragma pack ??? */
    /** @struct CCZHeader
    */
    struct CCZHeader {
        unsigned char            sig[4];                // signature. Should be 'CCZ!' 4 bytes  签名（标示位）
        unsigned short            compression_type;    // should 0                              压缩类型
        unsigned short            version;            // should be 2 (although version type==1 is also supported)   版本
        unsigned int             reserved;            // Reserved for users.                    保留位
        unsigned int            len;                // size of the uncompressed file            长度（未压缩）
    };

    enum {
        CCZ_COMPRESSION_ZLIB,                // zlib format.    压缩支持格式
        CCZ_COMPRESSION_BZIP2,                // bzip2 format (not supported yet)
        CCZ_COMPRESSION_GZIP,                // gzip format (not supported yet)
        CCZ_COMPRESSION_NONE,                // plain (not supported yet)
    };

    class ZipUtils
    {
    public:
        /** 
        * Inflates either zlib or gzip deflated memory. The inflated memory is
        * expected to be freed by the caller.
        *
        * It will allocate 256k for the destination buffer. If it is not enough it will multiply the previous buffer size per 2, until there is enough memory.
        * @returns the length of the deflated buffer
        *
        @since v0.8.1
        */
        // 非配内存。内存有调度者释放；会分配256k的目标缓冲区； 返回分配的缓冲区长度
        static int ccInflateMemory(unsigned char *in, unsigned int inLength, unsigned char **out);

        /** 
        * Inflates either zlib or gzip deflated memory. The inflated memory is
        * expected to be freed by the caller.
        *
        * outLenghtHint is assumed to be the needed room to allocate the inflated buffer.
        *
        * @returns the length of the deflated buffer
        *
        @since v1.0.0
        */
        // 返回缓冲区的长度，
        static int ccInflateMemoryWithHint(unsigned char *in, unsigned int inLength, unsigned char **out, unsigned int outLenghtHint);

        /** inflates a GZip file into memory
        *
        * @returns the length of the deflated buffer
        *
        * @since v0.99.5
        */
        // 解压一个gzip文件到内存，返回缓冲区的长度
        static int ccInflateGZipFile(const char *filename, unsigned char **out);

        /** inflates a CCZ file into memory
        *
        * @returns the length of the deflated buffer
        *
        * @since v0.99.5
        */
        // 解压/膨胀一个ccz文件到内存，返回缓冲区的长度
        static int ccInflateCCZFile(const char *filename, unsigned char **out);

    private:
        static int ccInflateMemoryWithHint(unsigned char *in, unsigned int inLength, unsigned char **out, unsigned int *outLength, 
            unsigned int outLenghtHint);
    };

    // forward declaration
    // 声明
    class ZipFilePrivate;

    /**
    * Zip file - reader helper class.
    *
    * It will cache the file list of a particular zip file with positions inside an archive,
    * so it would be much faster to read some particular files or to check their existance.
    *
    * @since v2.0.5
    */
    // 会缓存特定zip文件到指定位置在存档列表内，因此可以更加快速的读取指定文件或检测其存在
    class ZipFile
    {
    public:
        /**
        * Constructor, open zip file and store file list.
        *
        * @param zipFile Zip file name
        * @param filter The first part of file names, which should be accessible.
        *               For example, "assets/". Other files will be missed.
        *
        * @since v2.0.5
        */
        // 构造，打开zip文件和存储文件列表，使用文件名称，过滤器为参数
        ZipFile(const std::string &zipFile, const std::string &filter = std::string());
        virtual ~ZipFile();

        /**
        * Regenerate accessible file list based on a new filter string.
        *
        * @param filter New filter string (first part of files names)
        * @return true whenever zip file is open successfully and it is possible to locate
        *              at least the first file, false otherwise
        *
        * @since v2.0.5
        */
        // 基于新的过滤器字符串，访问文件列表
        bool setFilter(const std::string &filter);

        /**
        * Check does a file exists or not in zip file
        *
        * @param fileName File to be checked on existance
        * @return true whenever file exists, false otherwise
        *
        * @since v2.0.5
        */
        // 检测一个文件是否存在在zip文件中
        bool fileExists(const std::string &fileName) const;

        /**
        * Get resource file data from a zip file.
        * @param fileName File name
        * @param[out] pSize If the file read operation succeeds, it will be the data size, otherwise 0.
        * @return Upon success, a pointer to the data is returned, otherwise NULL.
        * @warning Recall: you are responsible for calling delete[] on any Non-NULL pointer returned.
        *
        * @since v2.0.5
        */
        // 获取资源文件数据从zip文件中，使用文件名称，文件大小（文件读取操作成功，则有大小，否则为0）
        unsigned char *getFileData(const std::string &fileName, unsigned long *pSize);

    private:
        /** Internal data like zip file pointer / file list array and so on */
        // 内部数据，如文件指针，列表数组等
        ZipFilePrivate *m_data;
    };
} // end of namespace cocos2d
#endif // __SUPPORT_ZIPUTILS_H__

