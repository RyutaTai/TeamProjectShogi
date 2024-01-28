#pragma once
#include <Windows.h>
#include <mmsystem.h>
#include <cmath>
#include <algorithm>
#include <vector>
#include <Mmdeviceapi.h>
#include <Endpointvolume.h>
#include <thread>
#include <future>
#include <chrono>
#include "GamePad.h"

#pragma comment(lib, "winmm.lib")

class Microphone
{
public:
    Microphone();
    ~Microphone();
    static Microphone& instance() {
        static Microphone instance;
        return instance;
    }

    struct param {
        double _db;
    };
public:
    // �������� (second)
    void startRecording(float timer);

    // �X�g�b�v
    void stopRecording();

    //�o�^
    void Register(param p, std::vector<param> n) { _mic.emplace_back(p); }

    // �\�[�g 
    float Sort();

    float getDecibel() { return _mic.at(_timer-1)._db; }

    float getTimer() { return _timer; }

    void setTimer(float timer) { _timer = timer; }

    bool getOnRecording() { return _isRecording; }

    void setIsRecording(bool recording) { _isRecording = recording; }

    bool threadstoped() { return _stoped; }

    bool isStart() { return _started; }

private:
    // �~���[�g���m�F
    bool CheckMuteStatus();

    // �^��
    void recordThread(float timer);

public:
    std::vector<param> _mic; // �S��

private:
    bool _muted = true;
    WAVEFORMATEX _format;
    HWAVEIN _hWaveIn;
    UINT _deviceCount;
    float _timer = 0;
    bool _isRecording = false;
    bool _stoped = false;
    bool _started = false;

    const int _bufferSize = 4096;
    const int _bufferCount = 3;

    std::vector<std::vector<char>> _bufferData;
    std::vector<WAVEHDR> _bufferHeaders;
    std::thread _recordingThread;

};
