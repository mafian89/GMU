/*
 * FileUtils.h
 *
 *  Created on: 21.12.2014
 *      Author: Tomas
 */
#include <jni.h>
#include "Common.h"

#ifndef FILEUTILS_H_
#define FILEUTILS_H_


#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_example_utils_FileUtils
 * Method:    myNative
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_example_utils_FileUtils_myNative
  (JNIEnv *, jclass, jobject);

FileData get_asset_data(const char* relative_path);

void release_asset_data(const FileData* file_data);

#ifdef __cplusplus
}
#endif
#endif /* FILEUTILS_H_ */
