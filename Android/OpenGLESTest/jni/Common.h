/*
 * Common.h
 *
 *  Created on: 20.12.2014
 *      Author: Tomas
 */

#ifndef COMMON_H_
#define COMMON_H_


#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <android/log.h>

typedef struct {
	const long data_length;
	const void* data;
	const void* file_handle;
} FileData;


enum effectType {
	BASIC = 0,
	THRESHOLD = 1,
	BITWISE_AND = 2
};

#endif /* COMMON_H_ */
