/****************************************************************************

   Ras library FreeBSD Version

   CopyRight(C) 2003 Sean Kim All Rights reserved.
   Author : Sean Kim (sean@0x31.com)

   $Id: stringbuffer.cpp,v 1.1 2007/03/21 06:14:07 miracle Exp $

   Redistribution and use in source and binary forms, with or with out
   modification, are not permitted without author's permission.

 ****************************************************************************/

#include <string.h>
#include "stringbuffer.h"

namespace SDSocket
{
  size_t StringBuffer::size() const throw()
  {
    return buffer.length() + 1;
  }

  char* StringBuffer::pointer() throw()
  {
    return ptrToBuffer;
  }

  const char* StringBuffer::pointer() const throw()
  {
    return buffer.c_str();
  }

  void StringBuffer::prepare() throw()
  {
    buffer.resize(bufferSize-1);

    delete[] ptrToBuffer;

    ptrToBuffer = new char[bufferSize];

    memset(ptrToBuffer, 0, bufferSize);
  }

  void StringBuffer::update(size_t) throw()
  {
    buffer = ptrToBuffer;

    delete[] ptrToBuffer;
    ptrToBuffer = NULL;
  }

  StringBuffer::StringBuffer(const string& text) throw()
    : buffer(text)
    , ptrToBuffer(NULL)
    , bufferSize(DEFAULT_BUFFER_SIZE)
  {}

  StringBuffer::StringBuffer(size_t tempBufferSize) throw()
    : ptrToBuffer(NULL)
    , bufferSize(tempBufferSize)
  {
    buffer.resize(bufferSize-1);
  }

  StringBuffer::~StringBuffer() throw()
  {
    delete[] ptrToBuffer;
  }

  StringBuffer::operator string&() throw()
  {
    return buffer;
  }
}
