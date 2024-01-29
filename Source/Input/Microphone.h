#pragma once

#include "GamePad.h"

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

#pragma comment(lib, "winmm.lib")

class Microphone
{
public: //  �\����
    struct Param {
        double _db;
    };

public:
    Microphone();
    ~Microphone();

public:
    //  �C���X�^���X�擾
    static Microphone& Instance() {
        static Microphone instance_;
        return instance_;
    }

    // �������� (second)
    void StartRecording(float timer);

    // �^���I���@�o�b�t�@�̊J���Ȃǂ�����
    void StopRecording();

    //  �o�^
    void Register(Param p, std::vector<Param> n) { _mic.emplace_back(p); }

    // �\�[�g(�f�V�x���̍ő�l���擾)
    float Sort();

    //  �f�V�x���擾
    float GetDecibel() { return _mic.at(_timer-1)._db; }

    //  �^�C�}�[�擾
    float GetTimer() { return _timer; }

    //  �^�C�}�[�ݒ�
    void SetTimer(float timer) { _timer = timer; }

    //  �^������
    bool GetOnRecording() { return _isRecording; }

    //  �^���t���O�ݒ�
    void SetIsRecording(bool recording) { _isRecording = recording; }

    //  �X���b�h���I�����Ă��邩
    bool ThreadStoped() { return _stoped; }

    //  ?
    bool IsStart() { return _started; }

private:
    // �~���[�g���ǂ����m�F
    bool CheckMuteStatus();
    // �^��
    void RecordThread(float timer);

public:
    std::vector<Param> _mic; // �S��

private:
    WAVEFORMATEX    _format;
    HWAVEIN         _hWaveIn;
    UINT            _deviceCount;
    float           _timer          = 0;
    bool            _muted          = true;     //  �~���[�g�H
    bool            _isRecording    = false;    //  �^������
    bool            _started        = false;    //  �^����������true ������x���s�����̂�h��
    bool            _stoped         = false;    //  �X���b�h���I�����Ă��邩�H

    const int _bufferSize = 4096;               //  
    const int _bufferCount = 3;                 //  

    std::vector<std::vector<char>>  _bufferData;        //  
    std::vector<WAVEHDR>            _bufferHeaders;     //  
    std::thread                     _recordingThread;   //  �^���X���b�h

};
