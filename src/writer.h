#pragma once

#include "memory.h"

static const char csvExtension[] = ".csv";

typedef void (*CustomWriteFunction)(char *filename, char *extension, char *contents, int numBytes);

struct buffer_file
{
  char *buffer;
  int bufferPos;
  int bufferSize;
};
typedef struct buffer_file BUFFER_FILE;

struct write_context
{
  int bufferSize;
  char *outputDirectory;
  char *filingId;
  char **filenames;
  char **extensions;
  BUFFER_FILE **bufferFiles;
  FILE **files;
  int nfiles;
  char *lastname;
  BUFFER_FILE *lastBufferFile;
  FILE *lastfile;
  int local;
  STRING *localBuffer;
  int localBufferPosition;
  CustomWriteFunction customWriteFunction;
};
typedef struct write_context WRITE_CONTEXT;

BUFFER_FILE *newBufferFile(int bufferSize);

void freeBufferFile(BUFFER_FILE *bufferFile);

WRITE_CONTEXT *newWriteContext(char *outputDirectory, char *filingId, int bufferSize, CustomWriteFunction customWriteFunction);

void initializeLocalWriteContext(WRITE_CONTEXT *writeContext, STRING *line);

// Return 0 if file is cached, or 1 if it is newly created for writing
int getFile(WRITE_CONTEXT *context, char *filename, const char *extension);

void writeN(WRITE_CONTEXT *context, char *filename, const char *extension, char *string, int nchars);

void writeString(WRITE_CONTEXT *context, char *filename, const char *extension, char *string);

void writeChar(WRITE_CONTEXT *context, char *filename, const char *extension, char c);

void writeDouble(WRITE_CONTEXT *context, char *filename, const char *extension, double d);

void freeWriteContext(WRITE_CONTEXT *context);
