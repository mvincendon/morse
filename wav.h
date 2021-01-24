#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdint>
#include <algorithm>

#include "Correspondance/corres.h"

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::fstream;

// Unité de temps, en ms
#define UNIT 300
// Seuil de silence
#define SEUIL 2
// Intervalle de temps dans lequel on peut fluctuer sans changer l'interprétation du son ou du silence, en ms
#define FLUCT 10

typedef struct  WAV_HEADER
{
    /* RIFF Chunk Descriptor */
    uint8_t         RIFF[4] = {'R','I','F','F'};        // RIFF Header Magic header
    uint32_t        ChunkSize;// = fsize + 36;          // RIFF Chunk Size
    uint8_t         WAVE[4] = {'W','A','V','E'};        // WAVE Header
    /* "fmt" sub-chunk */
    uint8_t         fmt[4] = {'f','m','t',' '};         // FMT header
    uint32_t        Subchunk1Size = 16;                 // Size of the fmt chunk
    uint16_t        AudioFormat = 1;                    // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
    uint16_t        NumOfChan = 1;                      // Number of channels 1=Mono 2=Sterio
    uint32_t        SamplesPerSec = 44100;              // Sampling Frequency in Hz
    uint32_t        bytesPerSec = 44100*2;              // bytes per second
    uint16_t        blockAlign = 2;                     // 2=16-bit mono, 4=16-bit stereo
    uint16_t        bitsPerSample = 8;                  // Number of bits per sample
    /* "data" sub-chunk */
    uint8_t         Subchunk2ID[4] = {'d', 'a', 't', 'a'}; // "data"  string
    uint32_t        Subchunk2Size;                      // Sampled data length
} wav_hdr;

class Wav{

    protected:
        wav_hdr _header;
        vector<double> _data;
        long unsigned int fluct;

        double sous_mediane(const long unsigned int debut, const long unsigned int fin) const;

        bool ecoute(const double val, const bool silence) const;

        // int periode(const long unsigned int debut, const bool silence) const;


    public:
        Wav(){}

        void ecrire(vector<double> tableau);

        int periode(const long unsigned int debut, const bool silence) const;

        string interpreter() const;

        void lire(const string source);

        vector<double> get_data() const;     //Temporaire pour le debugging
};

