/*****************************************************************************
 *
 * Copyright (C) 2009 Thomas Volkert <thomas@homer-conferencing.com>
 *
 * This software is free software.
 * Your are allowed to redistribute it and/or modify it under the terms of
 * the GNU General Public License version 2 as published by the Free Software
 * Foundation.
 *
 * This source is published in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License version 2
 * along with this program. Otherwise, you can write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111, USA.
 * Alternatively, you find an online version of the license text under
 * http://www.gnu.org/licenses/gpl-2.0.html.
 *
 *****************************************************************************/

/*
 * Purpose: ffmpeg based local file source
 * Author:  Thomas Volkert
 * Since:   2009-02-24
 */

#ifndef _MULTIMEDIA_MEDIA_SOURCE_FILE_
#define _MULTIMEDIA_MEDIA_SOURCE_FILE_

#include <Header_Ffmpeg.h>
#include <MediaSourceMem.h>
#include <MediaFifo.h>

#include <vector>
#include <string.h>

namespace Homer { namespace Multimedia {

///////////////////////////////////////////////////////////////////////////////

class MediaSourceFile:
    public MediaSourceMem
{
public:
    MediaSourceFile(std::string pSourceFile, bool pGrabInRealTime = true /* 1 = frame rate emulation, 0 = grab as fast as possible */);

    virtual ~MediaSourceFile();

    /* pseudo device control */
    virtual void getVideoDevices(VideoDevices &pVList);
    virtual void getAudioDevices(AudioDevices &pAList);

    /* recording */
    virtual bool SupportsRecording();

    /* seek interface */
    virtual bool SupportsSeeking();
    virtual float GetSeekEnd(); // get maximum seek time in seconds
    virtual bool Seek(float pSeconds, bool pOnlyKeyFrames = true); // seek to absolute position which is given in seconds
    virtual bool SeekRelative(float pSeconds, bool pOnlyKeyFrames = true); // seeks relative to the current position, distance is given in seconds
    virtual float GetSeekPos(); // in seconds

    /* multi channel input interface */
    virtual bool SupportsMultipleInputStreams();
    virtual bool SelectInputStream(int pIndex);
    virtual std::string CurrentInputStream();
    virtual std::vector<std::string> GetInputStreams();

public:
    virtual bool OpenVideoGrabDevice(int pResX = 352, int pResY = 288, float pFps = 29.97);
    virtual bool OpenAudioGrabDevice(int pSampleRate = 44100, int pChannels = 2);
    virtual bool CloseGrabDevice();

private:

    std::vector<string> mInputChannels;
};

///////////////////////////////////////////////////////////////////////////////

}} // namepsaces

#endif
