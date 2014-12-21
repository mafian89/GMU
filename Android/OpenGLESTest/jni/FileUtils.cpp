/*
 * FileUtils.cpp
 *
 *  Created on: 21.12.2014
 *      Author: Tomas
 */

#include "FileUtils.h"

static AAssetManager* asset_manager;

JNIEXPORT void JNICALL Java_com_example_utils_FileUtils_myNative
  (JNIEnv * env, jclass clazz, jobject java_asset_manager) {
	asset_manager = AAssetManager_fromJava(env, java_asset_manager);
}

FileData get_asset_data(const char* relative_path) {
    AAsset* asset =
        AAssetManager_open(asset_manager, relative_path, AASSET_MODE_STREAMING);

    return (FileData) { AAsset_getLength(asset), AAsset_getBuffer(asset), asset };
}

void release_asset_data(const FileData* file_data) {
    AAsset_close((AAsset*)file_data->file_handle);
}


