/**
*************************************************************************************************************
* @file    ring_buffer.h
* @brief   Ring buffer template class
*************************************************************************************************************
* @attention
*
* <h2><center>Copyright (c)2016 Christie Digital Systems USA, Inc. All rights reserved</center></h2>
*
* IN NO EVENT WILL CHRISTIE DIGITAL SYSTEMS USA, INC. (HEREAFTER THE "COMPANY") BE LIABLE TO ANY
* PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST
* PROFITS, LOST REVENUES AND LOST DATA ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
* EVEN IF THE COMPANY HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* THE COMPANY SPECIFICALLY DISCLAIMS ANY WARRANTIES OR CONDITIONS, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OR CONDITIONS OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
* EXCEPT AS OTHERWISE EXPRESSLY PROVIDED IN A WRITTEN AGREEMENT SIGNED BY THE COMPANY, THIS SOFTWARE AND
* ACCOMPANYING DOCUMENTATION, IF ANY, IS PROVIDED "AS IS" AND COMPANY HAS NO OBLIGATION TO PROVIDE
* MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
*
*************************************************************************************************************
* @code
* RingBuffer<uint8_t> rxBuf(256); // A ring buffer named rxBuf for data type uint8_t, buffer size 256
* @endcode
*************************************************************************************************************
*/

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <string.h>

/*!
 * @brief Ring buffer template
 */
template<typename T> class RingBuffer
{
public:

    /*!
     * @brief Ring buffer constructor
     */
    RingBuffer(uint32_t size) : _size(size), _first(0), _last(0)
    {
        _pBuffer = new T[_size];
    }

    /*!
     * @brief Ring buffer copy constructor
     */
    RingBuffer(const RingBuffer<T> &ringBuffer)
    {
        _size = ringBuffer._size;
        _pBuffer = new T[_size];
        _first = ringBuffer._first;
        _last = ringBuffer._last;
        memcpy(_pBuffer, ringBuffer._pBuffer, sizeof(T) * _size);
    }

    /*!
     * @brief Ring buffer destructor
     */
    ~RingBuffer()
    {
        delete[] _pBuffer;
    }

    /*!
     * @brief  Ring buffer push() method
     * @param  pData [in] : Data to be pushed
     * @return bool, true for success, false for fail (buffer is full?)
     */
    bool push(const T *pData)
    {
        if (full())
        {
            return false;
        }
        memcpy(&(_pBuffer[_last]), pData, sizeof(T));
        _last++;
        if (_last >= _size)
        {
            _last = 0;
        }
        return true;
    }

    /*!
     * @brief  Ring buffer pop() method
     * @param  pData [out] : Buffer to hold the data popped
     * @return bool, true for success, false for fail (buffer is empty?)
     */
    bool pop(T *pData)
    {
        if (empty())
        {
            return false;
        }
        memcpy(pData, &(_pBuffer[_first]), sizeof(T));
        _first++;
        if (_first >= _size)
        {
            _first = 0;
        }
        return true;
    }

    /*!
     * @brief  Ring buffer full() method, check if buffer is full
     * @return bool, true for buffer full, false otherwise
     */
    bool full(void)
    {
        uint32_t next = _last + 1;
        if (next >= _size)
        {
            next = 0;
        }
        return (next == _first);
    }

    /*!
     * @brief  Ring buffer empty() method, check if buffer is empty
     * @return bool, true for buffer empty, false otherwise
     */
    bool empty(void)
    {
        return (_last == _first);
    }

private:
    T *_pBuffer;
    uint32_t _size;
    uint32_t _first;
    uint32_t _last;
};

#endif // RINGBUFFER_H
