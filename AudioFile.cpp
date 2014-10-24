#include "AudioFile.h"
#include <stdexcept>
#include <sndfile.h>



void AudioFile::init()
{
    if(snd_pcm_open(&pcm_hdl, "default",SND_PCM_STREAM_PLAYBACK,0) < 0)
        throw std::runtime_error("can't open pcm device 'default'");
    snd_pcm_hw_params_alloca(&params);
    snd_pcm_hw_params_any(pcm_hdl, params);
    if
    (
        (snd_pcm_hw_params_set_access(pcm_hdl, params,SND_PCM_ACCESS_RW_INTERLEAVED) < 0) ||
        (snd_pcm_hw_params_set_format(pcm_hdl, params,SND_PCM_FORMAT_S16_LE) < 0)         ||
        (snd_pcm_hw_params_set_channels(pcm_hdl, params, _ch) < 0)                        ||
        (snd_pcm_hw_params_set_rate_near(pcm_hdl, params, &_rate, 0) < 0)                 ||
        (snd_pcm_hw_params(pcm_hdl, params) < 0)
    )
        throw std::runtime_error("can't set pcm parameters'");
}

void AudioFile::close()
{
    snd_pcm_drain(pcm_hdl);
    snd_pcm_close(pcm_hdl); 
}

AudioFile::AudioFile(const std::string &filename) : 
    _filename(filename)
{
    SF_INFO  info;
    auto sf = sf_open(filename.c_str(),SFM_READ,&info);
    if(!sf)
        throw std::runtime_error("can't open wav file");
    _ch = info.channels;
    _rate = info.samplerate;
    auto size = info.frames *  info.channels; 
    std::cout << "LOAD WAV: " << filename << " rate: " << info.samplerate << "; ch: " << info.channels << "; size: " << size << " bytes;" <<std::endl;
    _buffer.resize(size);
    sf_read_raw(sf,&_buffer[0],size);
    sf_close(sf);
}

AudioFile::~AudioFile()
{}   

void AudioFile::play()
{
        init();
        std::cout << "PLAY WAV: " << _filename << " rate: " << getRate() << "; ch: " << getChannels() << "; size: " << _buffer.size() << " bytes;" <<std::endl;
        auto pcm = snd_pcm_writei(pcm_hdl, &_buffer[0], _buffer.size());
       
        if(pcm == -EPIPE) {std::cout << "underun!" << std::endl; snd_pcm_prepare(pcm_hdl);}
        if(pcm < 0)
            throw std::runtime_error("playback error");  
        close();
}

uint AudioFile::getChannels()
{
    uint ch;
    if(snd_pcm_hw_params_get_channels(params, &ch) < 0) {ch = 0;}
    return ch;
}
uint AudioFile::getRate()
{
    uint rate, val;
    if(snd_pcm_hw_params_get_rate(params, &rate, (int*)&val) < 0) {rate = 0;}
    return rate;
}

