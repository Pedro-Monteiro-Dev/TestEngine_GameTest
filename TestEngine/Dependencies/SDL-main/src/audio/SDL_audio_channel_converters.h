/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2023 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

// DO NOT EDIT, THIS FILE WAS GENERATED BY build-scripts/gen_audio_channel_conversion.c


typedef void (*SDL_AudioChannelConverter)(float *dst, const float *src, int num_frames);

static void SDL_ConvertMonoToStereo(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("mono", "stereo");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1);
    dst += (num_frames-1) * 2;
    for (i = num_frames; i; i--, src--, dst -= 2) {
        const float srcFC = src[0];
        dst[1] /* FR */ = srcFC;
        dst[0] /* FL */ = srcFC;
    }

}

static void SDL_ConvertMonoTo21(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("mono", "2.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1);
    dst += (num_frames-1) * 3;
    for (i = num_frames; i; i--, src--, dst -= 3) {
        const float srcFC = src[0];
        dst[2] /* LFE */ = 0.0f;
        dst[1] /* FR */ = srcFC;
        dst[0] /* FL */ = srcFC;
    }

}

static void SDL_ConvertMonoToQuad(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("mono", "quad");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1);
    dst += (num_frames-1) * 4;
    for (i = num_frames; i; i--, src--, dst -= 4) {
        const float srcFC = src[0];
        dst[3] /* BR */ = 0.0f;
        dst[2] /* BL */ = 0.0f;
        dst[1] /* FR */ = srcFC;
        dst[0] /* FL */ = srcFC;
    }

}

static void SDL_ConvertMonoTo41(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("mono", "4.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1);
    dst += (num_frames-1) * 5;
    for (i = num_frames; i; i--, src--, dst -= 5) {
        const float srcFC = src[0];
        dst[4] /* BR */ = 0.0f;
        dst[3] /* BL */ = 0.0f;
        dst[2] /* LFE */ = 0.0f;
        dst[1] /* FR */ = srcFC;
        dst[0] /* FL */ = srcFC;
    }

}

static void SDL_ConvertMonoTo51(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("mono", "5.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1);
    dst += (num_frames-1) * 6;
    for (i = num_frames; i; i--, src--, dst -= 6) {
        const float srcFC = src[0];
        dst[5] /* BR */ = 0.0f;
        dst[4] /* BL */ = 0.0f;
        dst[3] /* LFE */ = 0.0f;
        dst[2] /* FC */ = 0.0f;
        dst[1] /* FR */ = srcFC;
        dst[0] /* FL */ = srcFC;
    }

}

static void SDL_ConvertMonoTo61(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("mono", "6.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1);
    dst += (num_frames-1) * 7;
    for (i = num_frames; i; i--, src--, dst -= 7) {
        const float srcFC = src[0];
        dst[6] /* SR */ = 0.0f;
        dst[5] /* SL */ = 0.0f;
        dst[4] /* BC */ = 0.0f;
        dst[3] /* LFE */ = 0.0f;
        dst[2] /* FC */ = 0.0f;
        dst[1] /* FR */ = srcFC;
        dst[0] /* FL */ = srcFC;
    }

}

static void SDL_ConvertMonoTo71(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("mono", "7.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1);
    dst += (num_frames-1) * 8;
    for (i = num_frames; i; i--, src--, dst -= 8) {
        const float srcFC = src[0];
        dst[7] /* SR */ = 0.0f;
        dst[6] /* SL */ = 0.0f;
        dst[5] /* BR */ = 0.0f;
        dst[4] /* BL */ = 0.0f;
        dst[3] /* LFE */ = 0.0f;
        dst[2] /* FC */ = 0.0f;
        dst[1] /* FR */ = srcFC;
        dst[0] /* FL */ = srcFC;
    }

}

static void SDL_ConvertStereoToMono(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("stereo", "mono");

    for (i = num_frames; i; i--, src += 2, dst++) {
        dst[0] /* FC */ = (src[0] * 0.500000000f) + (src[1] * 0.500000000f);
    }

}

static void SDL_ConvertStereoTo21(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("stereo", "2.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 2;
    dst += (num_frames-1) * 3;
    for (i = num_frames; i; i--, src -= 2, dst -= 3) {
        dst[2] /* LFE */ = 0.0f;
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_ConvertStereoToQuad(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("stereo", "quad");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 2;
    dst += (num_frames-1) * 4;
    for (i = num_frames; i; i--, src -= 2, dst -= 4) {
        dst[3] /* BR */ = 0.0f;
        dst[2] /* BL */ = 0.0f;
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_ConvertStereoTo41(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("stereo", "4.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 2;
    dst += (num_frames-1) * 5;
    for (i = num_frames; i; i--, src -= 2, dst -= 5) {
        dst[4] /* BR */ = 0.0f;
        dst[3] /* BL */ = 0.0f;
        dst[2] /* LFE */ = 0.0f;
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_ConvertStereoTo51(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("stereo", "5.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 2;
    dst += (num_frames-1) * 6;
    for (i = num_frames; i; i--, src -= 2, dst -= 6) {
        dst[5] /* BR */ = 0.0f;
        dst[4] /* BL */ = 0.0f;
        dst[3] /* LFE */ = 0.0f;
        dst[2] /* FC */ = 0.0f;
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_ConvertStereoTo61(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("stereo", "6.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 2;
    dst += (num_frames-1) * 7;
    for (i = num_frames; i; i--, src -= 2, dst -= 7) {
        dst[6] /* SR */ = 0.0f;
        dst[5] /* SL */ = 0.0f;
        dst[4] /* BC */ = 0.0f;
        dst[3] /* LFE */ = 0.0f;
        dst[2] /* FC */ = 0.0f;
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_ConvertStereoTo71(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("stereo", "7.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 2;
    dst += (num_frames-1) * 8;
    for (i = num_frames; i; i--, src -= 2, dst -= 8) {
        dst[7] /* SR */ = 0.0f;
        dst[6] /* SL */ = 0.0f;
        dst[5] /* BR */ = 0.0f;
        dst[4] /* BL */ = 0.0f;
        dst[3] /* LFE */ = 0.0f;
        dst[2] /* FC */ = 0.0f;
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_Convert21ToMono(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("2.1", "mono");

    for (i = num_frames; i; i--, src += 3, dst++) {
        dst[0] /* FC */ = (src[0] * 0.333333343f) + (src[1] * 0.333333343f) + (src[2] * 0.333333343f);
    }

}

static void SDL_Convert21ToStereo(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("2.1", "stereo");

    for (i = num_frames; i; i--, src += 3, dst += 2) {
        const float srcLFE = src[2];
        dst[0] /* FL */ = (src[0] * 0.800000012f) + (srcLFE * 0.200000003f);
        dst[1] /* FR */ = (src[1] * 0.800000012f) + (srcLFE * 0.200000003f);
    }

}

static void SDL_Convert21ToQuad(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("2.1", "quad");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 3;
    dst += (num_frames-1) * 4;
    for (i = num_frames; i; i--, src -= 3, dst -= 4) {
        const float srcLFE = src[2];
        dst[3] /* BR */ = (srcLFE * 0.111111112f);
        dst[2] /* BL */ = (srcLFE * 0.111111112f);
        dst[1] /* FR */ = (srcLFE * 0.111111112f) + (src[1] * 0.888888896f);
        dst[0] /* FL */ = (srcLFE * 0.111111112f) + (src[0] * 0.888888896f);
    }

}

static void SDL_Convert21To41(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("2.1", "4.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 3;
    dst += (num_frames-1) * 5;
    for (i = num_frames; i; i--, src -= 3, dst -= 5) {
        dst[4] /* BR */ = 0.0f;
        dst[3] /* BL */ = 0.0f;
        dst[2] /* LFE */ = src[2];
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_Convert21To51(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("2.1", "5.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 3;
    dst += (num_frames-1) * 6;
    for (i = num_frames; i; i--, src -= 3, dst -= 6) {
        dst[5] /* BR */ = 0.0f;
        dst[4] /* BL */ = 0.0f;
        dst[3] /* LFE */ = src[2];
        dst[2] /* FC */ = 0.0f;
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_Convert21To61(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("2.1", "6.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 3;
    dst += (num_frames-1) * 7;
    for (i = num_frames; i; i--, src -= 3, dst -= 7) {
        dst[6] /* SR */ = 0.0f;
        dst[5] /* SL */ = 0.0f;
        dst[4] /* BC */ = 0.0f;
        dst[3] /* LFE */ = src[2];
        dst[2] /* FC */ = 0.0f;
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_Convert21To71(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("2.1", "7.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 3;
    dst += (num_frames-1) * 8;
    for (i = num_frames; i; i--, src -= 3, dst -= 8) {
        dst[7] /* SR */ = 0.0f;
        dst[6] /* SL */ = 0.0f;
        dst[5] /* BR */ = 0.0f;
        dst[4] /* BL */ = 0.0f;
        dst[3] /* LFE */ = src[2];
        dst[2] /* FC */ = 0.0f;
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_ConvertQuadToMono(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("quad", "mono");

    for (i = num_frames; i; i--, src += 4, dst++) {
        dst[0] /* FC */ = (src[0] * 0.250000000f) + (src[1] * 0.250000000f) + (src[2] * 0.250000000f) + (src[3] * 0.250000000f);
    }

}

static void SDL_ConvertQuadToStereo(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("quad", "stereo");

    for (i = num_frames; i; i--, src += 4, dst += 2) {
        const float srcBL = src[2];
        const float srcBR = src[3];
        dst[0] /* FL */ = (src[0] * 0.421000004f) + (srcBL * 0.358999997f) + (srcBR * 0.219999999f);
        dst[1] /* FR */ = (src[1] * 0.421000004f) + (srcBL * 0.219999999f) + (srcBR * 0.358999997f);
    }

}

static void SDL_ConvertQuadTo21(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("quad", "2.1");

    for (i = num_frames; i; i--, src += 4, dst += 3) {
        const float srcBL = src[2];
        const float srcBR = src[3];
        dst[0] /* FL */ = (src[0] * 0.421000004f) + (srcBL * 0.358999997f) + (srcBR * 0.219999999f);
        dst[1] /* FR */ = (src[1] * 0.421000004f) + (srcBL * 0.219999999f) + (srcBR * 0.358999997f);
        dst[2] /* LFE */ = 0.0f;
    }

}

static void SDL_ConvertQuadTo41(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("quad", "4.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 4;
    dst += (num_frames-1) * 5;
    for (i = num_frames; i; i--, src -= 4, dst -= 5) {
        dst[4] /* BR */ = src[3];
        dst[3] /* BL */ = src[2];
        dst[2] /* LFE */ = 0.0f;
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_ConvertQuadTo51(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("quad", "5.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 4;
    dst += (num_frames-1) * 6;
    for (i = num_frames; i; i--, src -= 4, dst -= 6) {
        dst[5] /* BR */ = src[3];
        dst[4] /* BL */ = src[2];
        dst[3] /* LFE */ = 0.0f;
        dst[2] /* FC */ = 0.0f;
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_ConvertQuadTo61(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("quad", "6.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 4;
    dst += (num_frames-1) * 7;
    for (i = num_frames; i; i--, src -= 4, dst -= 7) {
        const float srcBL = src[2];
        const float srcBR = src[3];
        dst[6] /* SR */ = (srcBR * 0.796000004f);
        dst[5] /* SL */ = (srcBL * 0.796000004f);
        dst[4] /* BC */ = (srcBR * 0.500000000f) + (srcBL * 0.500000000f);
        dst[3] /* LFE */ = 0.0f;
        dst[2] /* FC */ = 0.0f;
        dst[1] /* FR */ = (src[1] * 0.939999998f);
        dst[0] /* FL */ = (src[0] * 0.939999998f);
    }

}

static void SDL_ConvertQuadTo71(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("quad", "7.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 4;
    dst += (num_frames-1) * 8;
    for (i = num_frames; i; i--, src -= 4, dst -= 8) {
        dst[7] /* SR */ = 0.0f;
        dst[6] /* SL */ = 0.0f;
        dst[5] /* BR */ = src[3];
        dst[4] /* BL */ = src[2];
        dst[3] /* LFE */ = 0.0f;
        dst[2] /* FC */ = 0.0f;
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_Convert41ToMono(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("4.1", "mono");

    for (i = num_frames; i; i--, src += 5, dst++) {
        dst[0] /* FC */ = (src[0] * 0.200000003f) + (src[1] * 0.200000003f) + (src[2] * 0.200000003f) + (src[3] * 0.200000003f) + (src[4] * 0.200000003f);
    }

}

static void SDL_Convert41ToStereo(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("4.1", "stereo");

    for (i = num_frames; i; i--, src += 5, dst += 2) {
        const float srcLFE = src[2];
        const float srcBL = src[3];
        const float srcBR = src[4];
        dst[0] /* FL */ = (src[0] * 0.374222219f) + (srcLFE * 0.111111112f) + (srcBL * 0.319111109f) + (srcBR * 0.195555553f);
        dst[1] /* FR */ = (src[1] * 0.374222219f) + (srcLFE * 0.111111112f) + (srcBL * 0.195555553f) + (srcBR * 0.319111109f);
    }

}

static void SDL_Convert41To21(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("4.1", "2.1");

    for (i = num_frames; i; i--, src += 5, dst += 3) {
        const float srcBL = src[3];
        const float srcBR = src[4];
        dst[0] /* FL */ = (src[0] * 0.421000004f) + (srcBL * 0.358999997f) + (srcBR * 0.219999999f);
        dst[1] /* FR */ = (src[1] * 0.421000004f) + (srcBL * 0.219999999f) + (srcBR * 0.358999997f);
        dst[2] /* LFE */ = src[2];
    }

}

static void SDL_Convert41ToQuad(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("4.1", "quad");

    for (i = num_frames; i; i--, src += 5, dst += 4) {
        const float srcLFE = src[2];
        dst[0] /* FL */ = (src[0] * 0.941176474f) + (srcLFE * 0.058823530f);
        dst[1] /* FR */ = (src[1] * 0.941176474f) + (srcLFE * 0.058823530f);
        dst[2] /* BL */ = (srcLFE * 0.058823530f) + (src[3] * 0.941176474f);
        dst[3] /* BR */ = (srcLFE * 0.058823530f) + (src[4] * 0.941176474f);
    }

}

static void SDL_Convert41To51(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("4.1", "5.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 5;
    dst += (num_frames-1) * 6;
    for (i = num_frames; i; i--, src -= 5, dst -= 6) {
        dst[5] /* BR */ = src[4];
        dst[4] /* BL */ = src[3];
        dst[3] /* LFE */ = src[2];
        dst[2] /* FC */ = 0.0f;
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_Convert41To61(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("4.1", "6.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 5;
    dst += (num_frames-1) * 7;
    for (i = num_frames; i; i--, src -= 5, dst -= 7) {
        const float srcBL = src[3];
        const float srcBR = src[4];
        dst[6] /* SR */ = (srcBR * 0.796000004f);
        dst[5] /* SL */ = (srcBL * 0.796000004f);
        dst[4] /* BC */ = (srcBR * 0.500000000f) + (srcBL * 0.500000000f);
        dst[3] /* LFE */ = src[2];
        dst[2] /* FC */ = 0.0f;
        dst[1] /* FR */ = (src[1] * 0.939999998f);
        dst[0] /* FL */ = (src[0] * 0.939999998f);
    }

}

static void SDL_Convert41To71(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("4.1", "7.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 5;
    dst += (num_frames-1) * 8;
    for (i = num_frames; i; i--, src -= 5, dst -= 8) {
        dst[7] /* SR */ = 0.0f;
        dst[6] /* SL */ = 0.0f;
        dst[5] /* BR */ = src[4];
        dst[4] /* BL */ = src[3];
        dst[3] /* LFE */ = src[2];
        dst[2] /* FC */ = 0.0f;
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_Convert51ToMono(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("5.1", "mono");

    for (i = num_frames; i; i--, src += 6, dst++) {
        dst[0] /* FC */ = (src[0] * 0.166666672f) + (src[1] * 0.166666672f) + (src[2] * 0.166666672f) + (src[3] * 0.166666672f) + (src[4] * 0.166666672f) + (src[5] * 0.166666672f);
    }

}

static void SDL_Convert51ToStereo(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("5.1", "stereo");

    for (i = num_frames; i; i--, src += 6, dst += 2) {
        const float srcFC = src[2];
        const float srcLFE = src[3];
        const float srcBL = src[4];
        const float srcBR = src[5];
        dst[0] /* FL */ = (src[0] * 0.294545442f) + (srcFC * 0.208181813f) + (srcLFE * 0.090909094f) + (srcBL * 0.251818180f) + (srcBR * 0.154545456f);
        dst[1] /* FR */ = (src[1] * 0.294545442f) + (srcFC * 0.208181813f) + (srcLFE * 0.090909094f) + (srcBL * 0.154545456f) + (srcBR * 0.251818180f);
    }

}

static void SDL_Convert51To21(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("5.1", "2.1");

    for (i = num_frames; i; i--, src += 6, dst += 3) {
        const float srcFC = src[2];
        const float srcBL = src[4];
        const float srcBR = src[5];
        dst[0] /* FL */ = (src[0] * 0.324000001f) + (srcFC * 0.229000002f) + (srcBL * 0.277000010f) + (srcBR * 0.170000002f);
        dst[1] /* FR */ = (src[1] * 0.324000001f) + (srcFC * 0.229000002f) + (srcBL * 0.170000002f) + (srcBR * 0.277000010f);
        dst[2] /* LFE */ = src[3];
    }

}

static void SDL_Convert51ToQuad(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("5.1", "quad");

    for (i = num_frames; i; i--, src += 6, dst += 4) {
        const float srcFC = src[2];
        const float srcLFE = src[3];
        dst[0] /* FL */ = (src[0] * 0.558095276f) + (srcFC * 0.394285709f) + (srcLFE * 0.047619049f);
        dst[1] /* FR */ = (src[1] * 0.558095276f) + (srcFC * 0.394285709f) + (srcLFE * 0.047619049f);
        dst[2] /* BL */ = (srcLFE * 0.047619049f) + (src[4] * 0.558095276f);
        dst[3] /* BR */ = (srcLFE * 0.047619049f) + (src[5] * 0.558095276f);
    }

}

static void SDL_Convert51To41(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("5.1", "4.1");

    for (i = num_frames; i; i--, src += 6, dst += 5) {
        const float srcFC = src[2];
        dst[0] /* FL */ = (src[0] * 0.586000025f) + (srcFC * 0.414000005f);
        dst[1] /* FR */ = (src[1] * 0.586000025f) + (srcFC * 0.414000005f);
        dst[2] /* LFE */ = src[3];
        dst[3] /* BL */ = (src[4] * 0.586000025f);
        dst[4] /* BR */ = (src[5] * 0.586000025f);
    }

}

static void SDL_Convert51To61(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("5.1", "6.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 6;
    dst += (num_frames-1) * 7;
    for (i = num_frames; i; i--, src -= 6, dst -= 7) {
        const float srcBL = src[4];
        const float srcBR = src[5];
        dst[6] /* SR */ = (srcBR * 0.796000004f);
        dst[5] /* SL */ = (srcBL * 0.796000004f);
        dst[4] /* BC */ = (srcBR * 0.500000000f) + (srcBL * 0.500000000f);
        dst[3] /* LFE */ = src[3];
        dst[2] /* FC */ = (src[2] * 0.939999998f);
        dst[1] /* FR */ = (src[1] * 0.939999998f);
        dst[0] /* FL */ = (src[0] * 0.939999998f);
    }

}

static void SDL_Convert51To71(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("5.1", "7.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 6;
    dst += (num_frames-1) * 8;
    for (i = num_frames; i; i--, src -= 6, dst -= 8) {
        dst[7] /* SR */ = 0.0f;
        dst[6] /* SL */ = 0.0f;
        dst[5] /* BR */ = src[5];
        dst[4] /* BL */ = src[4];
        dst[3] /* LFE */ = src[3];
        dst[2] /* FC */ = src[2];
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_Convert61ToMono(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("6.1", "mono");

    for (i = num_frames; i; i--, src += 7, dst++) {
        dst[0] /* FC */ = (src[0] * 0.143142849f) + (src[1] * 0.143142849f) + (src[2] * 0.143142849f) + (src[3] * 0.142857149f) + (src[4] * 0.143142849f) + (src[5] * 0.143142849f) + (src[6] * 0.143142849f);
    }

}

static void SDL_Convert61ToStereo(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("6.1", "stereo");

    for (i = num_frames; i; i--, src += 7, dst += 2) {
        const float srcFC = src[2];
        const float srcLFE = src[3];
        const float srcBC = src[4];
        const float srcSL = src[5];
        const float srcSR = src[6];
        dst[0] /* FL */ = (src[0] * 0.247384623f) + (srcFC * 0.174461529f) + (srcLFE * 0.076923080f) + (srcBC * 0.174461529f) + (srcSL * 0.226153851f) + (srcSR * 0.100615382f);
        dst[1] /* FR */ = (src[1] * 0.247384623f) + (srcFC * 0.174461529f) + (srcLFE * 0.076923080f) + (srcBC * 0.174461529f) + (srcSL * 0.100615382f) + (srcSR * 0.226153851f);
    }

}

static void SDL_Convert61To21(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("6.1", "2.1");

    for (i = num_frames; i; i--, src += 7, dst += 3) {
        const float srcFC = src[2];
        const float srcBC = src[4];
        const float srcSL = src[5];
        const float srcSR = src[6];
        dst[0] /* FL */ = (src[0] * 0.268000007f) + (srcFC * 0.188999996f) + (srcBC * 0.188999996f) + (srcSL * 0.245000005f) + (srcSR * 0.108999997f);
        dst[1] /* FR */ = (src[1] * 0.268000007f) + (srcFC * 0.188999996f) + (srcBC * 0.188999996f) + (srcSL * 0.108999997f) + (srcSR * 0.245000005f);
        dst[2] /* LFE */ = src[3];
    }

}

static void SDL_Convert61ToQuad(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("6.1", "quad");

    for (i = num_frames; i; i--, src += 7, dst += 4) {
        const float srcFC = src[2];
        const float srcLFE = src[3];
        const float srcBC = src[4];
        const float srcSL = src[5];
        const float srcSR = src[6];
        dst[0] /* FL */ = (src[0] * 0.463679999f) + (srcFC * 0.327360004f) + (srcLFE * 0.040000003f) + (srcSL * 0.168960005f);
        dst[1] /* FR */ = (src[1] * 0.463679999f) + (srcFC * 0.327360004f) + (srcLFE * 0.040000003f) + (srcSR * 0.168960005f);
        dst[2] /* BL */ = (srcLFE * 0.040000003f) + (srcBC * 0.327360004f) + (srcSL * 0.431039989f);
        dst[3] /* BR */ = (srcLFE * 0.040000003f) + (srcBC * 0.327360004f) + (srcSR * 0.431039989f);
    }

}

static void SDL_Convert61To41(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("6.1", "4.1");

    for (i = num_frames; i; i--, src += 7, dst += 5) {
        const float srcFC = src[2];
        const float srcBC = src[4];
        const float srcSL = src[5];
        const float srcSR = src[6];
        dst[0] /* FL */ = (src[0] * 0.483000010f) + (srcFC * 0.340999991f) + (srcSL * 0.175999999f);
        dst[1] /* FR */ = (src[1] * 0.483000010f) + (srcFC * 0.340999991f) + (srcSR * 0.175999999f);
        dst[2] /* LFE */ = src[3];
        dst[3] /* BL */ = (srcBC * 0.340999991f) + (srcSL * 0.449000001f);
        dst[4] /* BR */ = (srcBC * 0.340999991f) + (srcSR * 0.449000001f);
    }

}

static void SDL_Convert61To51(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("6.1", "5.1");

    for (i = num_frames; i; i--, src += 7, dst += 6) {
        const float srcBC = src[4];
        const float srcSL = src[5];
        const float srcSR = src[6];
        dst[0] /* FL */ = (src[0] * 0.611000001f) + (srcSL * 0.223000005f);
        dst[1] /* FR */ = (src[1] * 0.611000001f) + (srcSR * 0.223000005f);
        dst[2] /* FC */ = (src[2] * 0.611000001f);
        dst[3] /* LFE */ = src[3];
        dst[4] /* BL */ = (srcBC * 0.432000011f) + (srcSL * 0.568000019f);
        dst[5] /* BR */ = (srcBC * 0.432000011f) + (srcSR * 0.568000019f);
    }

}

static void SDL_Convert61To71(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("6.1", "7.1");

    // convert backwards, since output is growing in-place.
    src += (num_frames-1) * 7;
    dst += (num_frames-1) * 8;
    for (i = num_frames; i; i--, src -= 7, dst -= 8) {
        const float srcBC = src[4];
        dst[7] /* SR */ = src[6];
        dst[6] /* SL */ = src[5];
        dst[5] /* BR */ = (srcBC * 0.707000017f);
        dst[4] /* BL */ = (srcBC * 0.707000017f);
        dst[3] /* LFE */ = src[3];
        dst[2] /* FC */ = src[2];
        dst[1] /* FR */ = src[1];
        dst[0] /* FL */ = src[0];
    }

}

static void SDL_Convert71ToMono(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("7.1", "mono");

    for (i = num_frames; i; i--, src += 8, dst++) {
        dst[0] /* FC */ = (src[0] * 0.125125006f) + (src[1] * 0.125125006f) + (src[2] * 0.125125006f) + (src[3] * 0.125000000f) + (src[4] * 0.125125006f) + (src[5] * 0.125125006f) + (src[6] * 0.125125006f) + (src[7] * 0.125125006f);
    }

}

static void SDL_Convert71ToStereo(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("7.1", "stereo");

    for (i = num_frames; i; i--, src += 8, dst += 2) {
        const float srcFC = src[2];
        const float srcLFE = src[3];
        const float srcBL = src[4];
        const float srcBR = src[5];
        const float srcSL = src[6];
        const float srcSR = src[7];
        dst[0] /* FL */ = (src[0] * 0.211866662f) + (srcFC * 0.150266662f) + (srcLFE * 0.066666670f) + (srcBL * 0.181066677f) + (srcBR * 0.111066669f) + (srcSL * 0.194133341f) + (srcSR * 0.085866667f);
        dst[1] /* FR */ = (src[1] * 0.211866662f) + (srcFC * 0.150266662f) + (srcLFE * 0.066666670f) + (srcBL * 0.111066669f) + (srcBR * 0.181066677f) + (srcSL * 0.085866667f) + (srcSR * 0.194133341f);
    }

}

static void SDL_Convert71To21(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("7.1", "2.1");

    for (i = num_frames; i; i--, src += 8, dst += 3) {
        const float srcFC = src[2];
        const float srcBL = src[4];
        const float srcBR = src[5];
        const float srcSL = src[6];
        const float srcSR = src[7];
        dst[0] /* FL */ = (src[0] * 0.226999998f) + (srcFC * 0.160999998f) + (srcBL * 0.194000006f) + (srcBR * 0.119000003f) + (srcSL * 0.208000004f) + (srcSR * 0.092000000f);
        dst[1] /* FR */ = (src[1] * 0.226999998f) + (srcFC * 0.160999998f) + (srcBL * 0.119000003f) + (srcBR * 0.194000006f) + (srcSL * 0.092000000f) + (srcSR * 0.208000004f);
        dst[2] /* LFE */ = src[3];
    }

}

static void SDL_Convert71ToQuad(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("7.1", "quad");

    for (i = num_frames; i; i--, src += 8, dst += 4) {
        const float srcFC = src[2];
        const float srcLFE = src[3];
        const float srcSL = src[6];
        const float srcSR = src[7];
        dst[0] /* FL */ = (src[0] * 0.466344833f) + (srcFC * 0.329241365f) + (srcLFE * 0.034482758f) + (srcSL * 0.169931039f);
        dst[1] /* FR */ = (src[1] * 0.466344833f) + (srcFC * 0.329241365f) + (srcLFE * 0.034482758f) + (srcSR * 0.169931039f);
        dst[2] /* BL */ = (srcLFE * 0.034482758f) + (src[4] * 0.466344833f) + (srcSL * 0.433517247f);
        dst[3] /* BR */ = (srcLFE * 0.034482758f) + (src[5] * 0.466344833f) + (srcSR * 0.433517247f);
    }

}

static void SDL_Convert71To41(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("7.1", "4.1");

    for (i = num_frames; i; i--, src += 8, dst += 5) {
        const float srcFC = src[2];
        const float srcSL = src[6];
        const float srcSR = src[7];
        dst[0] /* FL */ = (src[0] * 0.483000010f) + (srcFC * 0.340999991f) + (srcSL * 0.175999999f);
        dst[1] /* FR */ = (src[1] * 0.483000010f) + (srcFC * 0.340999991f) + (srcSR * 0.175999999f);
        dst[2] /* LFE */ = src[3];
        dst[3] /* BL */ = (src[4] * 0.483000010f) + (srcSL * 0.449000001f);
        dst[4] /* BR */ = (src[5] * 0.483000010f) + (srcSR * 0.449000001f);
    }

}

static void SDL_Convert71To51(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("7.1", "5.1");

    for (i = num_frames; i; i--, src += 8, dst += 6) {
        const float srcSL = src[6];
        const float srcSR = src[7];
        dst[0] /* FL */ = (src[0] * 0.518000007f) + (srcSL * 0.188999996f);
        dst[1] /* FR */ = (src[1] * 0.518000007f) + (srcSR * 0.188999996f);
        dst[2] /* FC */ = (src[2] * 0.518000007f);
        dst[3] /* LFE */ = src[3];
        dst[4] /* BL */ = (src[4] * 0.518000007f) + (srcSL * 0.481999993f);
        dst[5] /* BR */ = (src[5] * 0.518000007f) + (srcSR * 0.481999993f);
    }

}

static void SDL_Convert71To61(float *dst, const float *src, int num_frames)
{
    int i;

    LOG_DEBUG_AUDIO_CONVERT("7.1", "6.1");

    for (i = num_frames; i; i--, src += 8, dst += 7) {
        const float srcBL = src[4];
        const float srcBR = src[5];
        dst[0] /* FL */ = (src[0] * 0.541000009f);
        dst[1] /* FR */ = (src[1] * 0.541000009f);
        dst[2] /* FC */ = (src[2] * 0.541000009f);
        dst[3] /* LFE */ = src[3];
        dst[4] /* BC */ = (srcBL * 0.287999988f) + (srcBR * 0.287999988f);
        dst[5] /* SL */ = (srcBL * 0.458999991f) + (src[6] * 0.541000009f);
        dst[6] /* SR */ = (srcBR * 0.458999991f) + (src[7] * 0.541000009f);
    }

}

static const SDL_AudioChannelConverter channel_converters[8][8] = {   /* [from][to] */
    { NULL, SDL_ConvertMonoToStereo, SDL_ConvertMonoTo21, SDL_ConvertMonoToQuad, SDL_ConvertMonoTo41, SDL_ConvertMonoTo51, SDL_ConvertMonoTo61, SDL_ConvertMonoTo71 },
    { SDL_ConvertStereoToMono, NULL, SDL_ConvertStereoTo21, SDL_ConvertStereoToQuad, SDL_ConvertStereoTo41, SDL_ConvertStereoTo51, SDL_ConvertStereoTo61, SDL_ConvertStereoTo71 },
    { SDL_Convert21ToMono, SDL_Convert21ToStereo, NULL, SDL_Convert21ToQuad, SDL_Convert21To41, SDL_Convert21To51, SDL_Convert21To61, SDL_Convert21To71 },
    { SDL_ConvertQuadToMono, SDL_ConvertQuadToStereo, SDL_ConvertQuadTo21, NULL, SDL_ConvertQuadTo41, SDL_ConvertQuadTo51, SDL_ConvertQuadTo61, SDL_ConvertQuadTo71 },
    { SDL_Convert41ToMono, SDL_Convert41ToStereo, SDL_Convert41To21, SDL_Convert41ToQuad, NULL, SDL_Convert41To51, SDL_Convert41To61, SDL_Convert41To71 },
    { SDL_Convert51ToMono, SDL_Convert51ToStereo, SDL_Convert51To21, SDL_Convert51ToQuad, SDL_Convert51To41, NULL, SDL_Convert51To61, SDL_Convert51To71 },
    { SDL_Convert61ToMono, SDL_Convert61ToStereo, SDL_Convert61To21, SDL_Convert61ToQuad, SDL_Convert61To41, SDL_Convert61To51, NULL, SDL_Convert61To71 },
    { SDL_Convert71ToMono, SDL_Convert71ToStereo, SDL_Convert71To21, SDL_Convert71ToQuad, SDL_Convert71To41, SDL_Convert71To51, SDL_Convert71To61, NULL }
};
