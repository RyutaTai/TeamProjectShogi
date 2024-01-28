#include "Microphone.h"

void CALLBACK WaveInProc(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2);

//  �R���X�g���N�^
Microphone::Microphone()
{
    // WAVEFORMATEX �\���̂̏�����
    _format.wFormatTag = WAVE_FORMAT_PCM;
    _format.nChannels = 1;  // ���m����
    _format.nSamplesPerSec = /*11025;*/ 44100;  // �T���v�����O���[�g

    _format.wBitsPerSample = 16;  // �T���v��������̃r�b�g��
    _format.nBlockAlign = _format.nChannels * (_format.wBitsPerSample / 8);
    _format.nAvgBytesPerSec = _format.nSamplesPerSec * _format.nBlockAlign;
    _deviceCount = waveInGetNumDevs();//
    
}

//  �f�X�g���N�^
Microphone::~Microphone()
{
    StopRecording();
}

//  �^��
void Microphone::RecordThread(float timer)
{
    // waveInStart �Ř^�����J�n
    MMRESULT result = waveInStart(_hWaveIn);

    // timer �b�~�߂�
    std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(timer)));

    // waveInStop �Ř^�����~
    result = waveInStop(_hWaveIn);
    _stoped = true;
}

//  �^���J�n
void Microphone::StartRecording(float timer)
{
    // �o�b�t�@�̏�����
    _bufferData.resize(_bufferCount, std::vector<char>(_bufferSize));
    _bufferHeaders.resize(_bufferCount);
    if (!_mic.empty())_mic.clear();
    _mic.resize(0);
    _stoped = false;
    _started = true;

    // waveInOpen �Ń}�C�N���I�[�v��
    waveInOpen(&_hWaveIn, WAVE_MAPPER, &_format, (DWORD_PTR)WaveInProc, 0, CALLBACK_FUNCTION);

    // �}�C�N���~���[�g���m�F
    CheckMuteStatus();

    // �o�b�t�@�̓o�^
    for (int i = 0; i < _bufferCount; ++i) {
        _bufferHeaders[i].lpData = _bufferData[i].data();
        _bufferHeaders[i].dwBufferLength = _bufferSize;
        _bufferHeaders[i].dwFlags = 0;
        _bufferHeaders[i].dwLoops = 0;

        waveInPrepareHeader(_hWaveIn, &_bufferHeaders[i], sizeof(WAVEHDR));

        waveInAddBuffer(_hWaveIn, &_bufferHeaders[i], sizeof(WAVEHDR));
    }
    
    _recordingThread = std::thread(&Microphone::RecordThread, this, timer);
}

//  �^���I��
void Microphone::StopRecording() {
    // �X���b�h�҂�
    if (_recordingThread.joinable()) {
        _recordingThread.join();
    }

    // �o�b�t�@�̉��
    for (int i = 0; i < _bufferCount; ++i) {
        waveInUnprepareHeader(_hWaveIn, &_bufferHeaders[i], sizeof(WAVEHDR));
    }

    // waveInClose �Ń}�C�N���N���[�Y
    MMRESULT result = waveInClose(_hWaveIn);
    _started = false;
    _isRecording = false;
    _timer = 0;
}

void CALLBACK WaveInProc(HWAVEIN hwi, UINT uMsg, DWORD_PTR dwInstance, DWORD_PTR dwParam1, DWORD_PTR dwParam2) {
    // dwParam1 �ɂ͘^���f�[�^���܂܂�Ă���
    if (uMsg == WIM_DATA) {
        WAVEHDR* pWaveHdr = reinterpret_cast<WAVEHDR*>(dwParam1);
        Microphone::Instance().SetIsRecording(false);
        // pWaveHdr->lpData ���^���f�[�^�ւ̃|�C���^
        // pWaveHdr->dwBufferLength ���o�b�t�@�̃T�C�Y

        // �ŏ��̃T���v���̐U�����擾���ăf�V�x���ɕϊ����ĕ\��
        int16_t* data = reinterpret_cast<int16_t*>(pWaveHdr->lpData);
        size_t numSamples = pWaveHdr->dwBufferLength / sizeof(int16_t);

        double rms = 0.0;
        for (size_t i = 0; i < numSamples; ++i) {
            rms += static_cast<double>(data[i] * data[i]);
        }
        rms = sqrt(rms / numSamples);

        float decibels = 20.0 * log10(rms);
        if (decibels < 0)decibels = 0.0;

        Microphone::Param db;
        db._db = decibels;


        Microphone::Instance().Register(db, Microphone::Instance()._mic);
        Microphone::Instance().SetIsRecording(true);
        Microphone::Instance().SetTimer(Microphone::Instance().GetTimer() + 1);

        // �V�����o�b�t�@���w�肵�čēx�^�����J�n����
        MMRESULT result = waveInAddBuffer(hwi, pWaveHdr, sizeof(WAVEHDR));
        
    }
}

// �~���[�g���ǂ����m�F
bool Microphone::CheckMuteStatus() {
    CoInitialize(nullptr);

    IMMDeviceEnumerator* pEnumerator = nullptr;
    IMMDevice* pDevice = nullptr;
    IAudioEndpointVolume* pEndpointVolume = nullptr;

    // �f�o�C�X�񋓊���쐬
    HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (LPVOID*)&pEnumerator);
    if (SUCCEEDED(hr)) {
        // �f�t�H���g�̘^���f�o�C�X�i�}�C�N�j���擾
        hr = pEnumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &pDevice);
        if (SUCCEEDED(hr)) {
            // �I�[�f�B�I�G���h�|�C���g�{�����[�� �C���^�[�t�F�[�X���擾
            hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, nullptr, (LPVOID*)&pEndpointVolume);
            if (SUCCEEDED(hr)) {
                // �}�C�N�̃~���[�g��Ԃ��i�[����ϐ�
                BOOL muteState;

                // GetMute���\�b�h��BOOL�|�C���^��n���ă}�C�N�̃~���[�g��Ԃ��擾
                hr = pEndpointVolume->GetMute(&muteState);
                if (SUCCEEDED(hr)) {
                    (muteState ? pEndpointVolume->SetMute(FALSE, nullptr) : _muted = false);
                }
                //FAILED(hr, "failed");

                // �C���^�[�t�F�[�X�̉��
                pEndpointVolume->Release();
            }
            //FAILED(hr, "failed");

            // �f�o�C�X�̉��
            pDevice->Release();
        }
        //FAILED(hr, "failed");

        // �f�o�C�X�񋓊�̉��
        pEnumerator->Release();
    }
    //FAILED(hr, "failed");

    CoUninitialize();

    return hr == S_OK; // ����ɏI���������ǂ�����Ԃ�
}

// �\�[�g (����)
auto sort_func = [](Microphone::Param& lhs, Microphone::Param& rhs)-> bool {
    return lhs._db < rhs._db;
};

// �\�[�g(�f�V�x���̍ő�l���擾)
float Microphone::Sort()
{
    std::sort(_mic.begin(), _mic.end(), sort_func);
    return _mic.back()._db;
}
