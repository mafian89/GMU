package com.example.utils;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import android.content.Context;

/**
 * taken from: https://github.com/learnopengles/Learn-OpenGLES-Tutorials/blob/master/android/AndroidOpenGLESLessons/src/com/learnopengles/android/common/RawResourceReader.java
 */
public class RawResourceReader
{
	public static String readTextFileFromRawResource(final Context context,
			final int resourceId)
	{
		final InputStream inputStream = context.getResources().openRawResource(
				resourceId);
		final InputStreamReader inputStreamReader = new InputStreamReader(
				inputStream);
		final BufferedReader bufferedReader = new BufferedReader(
				inputStreamReader);

		String nextLine;
		final StringBuilder body = new StringBuilder();

		try
		{
			while ((nextLine = bufferedReader.readLine()) != null)
			{
				body.append(nextLine);
				body.append('\n');
			}
		}
		catch (IOException e)
		{
			return null;
		}

		return body.toString();
	}
}