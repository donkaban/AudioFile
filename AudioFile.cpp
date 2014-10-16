#include "AudioFile.h"
#include <stdexcept>
#include <sndfile.h>


snd_pcm_t           * AudioFile::pcm_hdl;
snd_pcm_hw_params_t * AudioFile::params;
uint                  AudioFile::_rate;
uint                  AudioFile::_ch ;


void AudioFile::initAudioSystem()
{
    _rate = 44100;
    _ch = 2;
    if(snd_pcm_open(&pcm_hdl, "default",SND_PCM_STREAM_PLAYBACK,0) < 0)
        throw std::runtime_error("can't open pcm device 'default'");
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(pcm_hdl, params);
    if
    (
        (snd_pcm_hw_params_set_access(pcm_hdl, params,SND_PCM_ACCESS_RW_INTERLEAVED) < 0) ||
        (snd_pcm_hw_params_set_format(pcm_hdl, params,SND_PCM_FORMAT_S16_LE) < 0)         ||
        (snd_pcm_hw_params_set_channels(pcm_hdl, params, _ch) < 0)                        ||
        (snd_pcm_hw_params_set_rate_near(pcm_hdl, params, &AudioFile::_rate, 0) < 0)                  ||
        (snd_pcm_hw_params(pcm_hdl, params) < 0)
    )
        throw std::runtime_error("can't set pcm parameters'");

     snd_pcm_prepare(pcm_hdl);
}

void AudioFile::closeAudioSystem()
{
    snd_pcm_drain(pcm_hdl);
    snd_pcm_close(pcm_hdl); 
}

AudioFile::AudioFile(const std::string &filename)
{
    SF_INFO  info;
    auto sf = sf_open(filename.c_str(),SFM_READ,&info);
    if(!sf)
        throw std::runtime_error("can't open wav file");
    auto size = info.frames *  info.channels; 
    if(info.samplerate != 44100 || info.channels != 2)
        throw std::runtime_error("bad WAV file format, not 44100hz x 2");
    std::cout << "LOAD WAV: " << filename << " rate: " << info.samplerate << "; ch: " << info.channels << "; size: " << size << " bytes;" <<std::endl;
    _buffer.resize(size);
    sf_read_raw(sf,&_buffer[0],size);
    sf_close(sf);
}

AudioFile::~AudioFile()
{}   

void AudioFile::play()
{
        if(snd_pcm_writei(pcm_hdl, &_buffer[0], _buffer.size()) < 0) 
            throw std::runtime_error("playback error!");  


}
